/*
 * Open Issues:
 * - works on all filesystems/OS?
 */

#ifndef CANVASIMPL_H
#define CANVASIMPL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/types.h>

#define STBI_ONLY_PNG                       //reduces loaded library code to essentials
#define STB_IMAGE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG                //Makes error msgs more user friendly
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"

#include "utils.h"

#define NUM_CHANNELS 3

#ifdef _WIN32
#include <direct.h>
void make_directory(const char* path, int _)
{
    _mkdir(path);
}
#else
#include <sys/stat.h>
void make_directory(const char* path, mode_t mode)
{
    mkdir(path, mode);
}
#endif

typedef struct Canvas_ {
    int32_t width;
    int32_t height;
    uint8_t* buffer;
    char* name;
    size_t debug_counter;
    bool supplied_invalid_coordinates;
    int32_t first_invalid_x;
    int32_t first_invalid_y;
} Canvas_;

/*
Return the length of the buffer of the given canvas.
*/
size_t canvas_size(Canvas_ * c) {
    return c->width * c->height * NUM_CHANNELS;
}

/*
 * Validate arguments and create a white canvas.
 */
Canvas_* canvas_new_color (int32_t width, int32_t height, char* name, uint8_t color){
    if (width < 1) {
        printf("Canvasbreite darf nicht negativ oder 0 sein. Erhielt aber %d.\n", width);
    }

    if (height < 1) {
        printf("Canvashöhe darf nicht negativ oder 0 sein. Erhielt aber %d.\n", height);
    }

    if (is_invalid_filename(name)) {
        printf("Canvasname darf kein /, \\, <, >, |, :, *, ? oder \" enthalten.");
    }
    
    //Memory for struct
    Canvas_* c = mallocx(sizeof(Canvas_));
    c->width = width;
    c->height = height;
    //Memory for name
    size_t name_length = strlen(name)+1;
    c->name = mallocx(name_length * sizeof(char));
    strncpy(c->name,name,name_length);
    //Memory for array
    size_t len = canvas_size(c);
    c->buffer = mallocx(len);

    for (size_t i = 0; i < len; i++) {
        c->buffer[i] = color;
    }
    c->debug_counter = 1;

    c->supplied_invalid_coordinates = false;
    c->first_invalid_x = 0;
    c->first_invalid_y = 0;
    return c;
}

Canvas_* canvas_new (int32_t width, int32_t height, char* name){
    return canvas_new_color(width, height, name, 255);

}

Canvas_* canvas_new_black (int32_t width, int32_t height, char* name){
    return canvas_new_color(width, height, name, 0);
}

/*
 * Free all allocated memory associated with a Canvas.
 */
void canvas_free (Canvas_* c){
    if(c != NULL){
        free(c->name);
        free(c->buffer);
        free(c);
    }
}

/*
 * Try to read an image as a canvas, abort if it fails.
 */
Canvas_* canvas_load_image (char* filename){
    stbi_set_flip_vertically_on_load(1);

    Canvas_ *c = mallocx(sizeof(Canvas_));
    int32_t num_channels_input = 0;
    c->buffer = stbi_load(filename, &(c->width), &(c->height), &num_channels_input, NUM_CHANNELS);

    // Handle failure to load.
    if (c->buffer == NULL) {
        printf("Konnte Bilddatei nicht laden: %s\n", filename);
        puts(stbi_failure_reason());
        abort();
    }

    // Handle unsupported number of channels.
    if (num_channels_input != NUM_CHANNELS) {
        printf("Konnte Bilddatei nicht nutzen: %s\n", filename);
        printf("Wir unterstützen ausschließlich Bilder mit drei Farbkanälen, aber das geladene Bild hatte %d Kanäle.\n",
               num_channels_input);
        abort();
    }

    size_t name_len = strlen(filename) + 1;
    c->name = mallocx(name_len * sizeof(char));
    strncpy(c->name,filename, name_len);

    c->supplied_invalid_coordinates = false;
    c->first_invalid_x = 0;
    c->first_invalid_y = 0;

    return c;
}

/*
 * Save a Canvas as a PNG image at the given filename.
 */
void canvas_save_path (Canvas_* c, char *filename){
    stbi_flip_vertically_on_write(1);

    int stride_bytes = NUM_CHANNELS * c->width;

    if(!stbi_write_png(filename, c->width, c->height, NUM_CHANNELS, c->buffer, stride_bytes)){
        printf("Konnte Bilddatei nicht speichern: %s\n", filename);
        puts(stbi_failure_reason());
        abort();
    }
}

/*
 * Save a Canvas as a PNG image in the same folder as the source code.
 */
void canvas_save_auto (Canvas_* c){
    /* Concatenating ".png" to the name.
     * Initial nullbyte is going to be overridden, so we need
     * 5 extra bytes for .png and a new nullbyte
     */
    char* filename = mallocx(strlen(c->name)+5);
    strncpy(filename,c->name,strlen(c->name)+1);
    strcat(filename,".png");

    canvas_save_path(c, filename);
    free(filename);
}

/*
 * Save the current state of the Canvas as a PNG image with a name signalling its for debug purposes.
 */
void canvas_save_debug (Canvas_* c){

    if(c->debug_counter > 100){
        printf("Du hast das Limit an Debug-Bildern für diesen Canvas erreicht.\n"
               "Um deinen Speicher zu schonen wurde kein Bild erstellt.\n");
        return;
    }

    //Creates a Debug directory if one doesnt already exist
    make_directory("Debug", 0777);

    size_t len = strlen("Debug/debug_") + strlen(c->name) + strlen("_") +  3 /*for counter*/ + strlen(".png") + 1 /*for \0*/;
    char* filename = mallocx(len);
    snprintf(filename, len, "Debug/debug_%s_%lu.png", c->name, c->debug_counter);

    canvas_save_path(c, filename);
    free(filename);
    c->debug_counter++;
}
/*
 * Saves a given Canvas in the absolute folder path(if absolute) or relative subfolder (which doesnt need to exist yet)
 */
void canvas_save_folder (Canvas_* c, char* folder_name){

    //Creates a new directory if one doesnt already exist with that name
    make_directory(folder_name, 0777);

    size_t len = strlen(folder_name) + strlen("/") + strlen(c->name) + strlen(".png") + 1 /*for null byte*/;
    char* filename = mallocx(len);
    snprintf(filename, len, "%s/%s.png",folder_name, c->name);

    canvas_save_path(c, filename);
    free(filename);
}

/*
 * Save a given Canvas as a Feedback image. Called by the canvas_feedback function.
 */
void canvas_save_feedback (Canvas_* c){
    canvas_save_folder(c, "Feedback");
}


/*
Return whether two Canvasses have equal width and height.
*/
bool canvas_dimensions_eq(Canvas_* c1, Canvas_* c2) {
    return c1->width == c2->width && c1->height == c2->height;
}

/*
 * Return whether two Canvasses are equal.
 */
int canvas_eq (Canvas_* c1, Canvas_* c2){
    if (!canvas_dimensions_eq(c1, c2)) {
        return false;
    }

    size_t len = canvas_size(c1);
    for(size_t i = 0; i < len; i++){
        if(c1->buffer[i] != c2->buffer[i]) {
            return false;
        }
    }

    return true;
}

/*
 * Return whether two Canvasses are approximately equal (each channel of each pixel may be off by one).
 */
int canvas_eq_approx (Canvas_* c1, Canvas_* c2){
    if (!canvas_dimensions_eq(c1, c2)) {
        return false;
    }

    size_t len = canvas_size(c1);
    for(size_t i = 0; i < len; i++){
        if((c1->buffer[i] != c2->buffer[i]) && (c1->buffer[i] != c2->buffer[i] + 1) && (c1->buffer[i] != c2->buffer[i] - 1)) {
            return false;
        }
    }

    return true;
}

/*
Return whether two Canvasses have equal pixels at the same position.
*/
bool canvas_pixel_eq(Canvas_* c1, Canvas_* c2, size_t pos) {
    return c1->buffer[pos] == c2->buffer[pos] && c1->buffer[pos + 1] == c2->buffer[pos + 1] &&
           c1->buffer[pos + 2] == c2->buffer[pos + 2];
}

/*
 * Return a Canvas that visualizes the differences between two given Canvasses of equal dimensions.
 */
Canvas_* canvas_diff(Canvas_* c1, Canvas_* c2) {
    if (!canvas_dimensions_eq(c1, c2)) {
        fprintf(stderr, "Für Canvasses mit unterschiedlichen Dimensionen können die Unterschiede nicht visualisiert werden.\n");
        fprintf(stderr, "Erste Canvas: Breite %d, Höhe %d\n", c1->width, c1->height);
        fprintf(stderr, "Zweite Canvas: Breite %d, Höhe %d\n", c2->width, c2->height);
        abort();
    }

    Canvas_* differential = canvas_new(c1->width, c1->height, "CanvasDifferential");

    size_t len = canvas_size(c1);
    for (int i = 0; i < len; i += NUM_CHANNELS) {
        if (!canvas_pixel_eq(c1, c2, i)) {
                if (c1->buffer[i] == 0) {
                    differential->buffer[i] = 242;
                    differential->buffer[i + 1] = 125;
                    differential->buffer[i + 2] = 15;
                } else {
                    differential->buffer[i] = 15;
                    differential->buffer[i + 1] = 90;
                    differential->buffer[i + 2] = 242;
                }
        } else {
            differential->buffer[i] = c1->buffer[i];
            differential->buffer[i + 1] = c1->buffer[i + 1];
            differential->buffer[i + 2] = c1->buffer[i + 2];
        }
    }

    return differential;
}

/*
 * Save an image that contains both the two given Canvasses and a visualization of their differences.
 */
void canvas_feedback(Canvas_* c1, Canvas_* c2, char* name, bool did_error) {
    uint8_t divider_color_r = 110;
    uint8_t divider_color_g = 110;
    uint8_t divider_color_b = 110;
    if (did_error) {
        divider_color_r = 200;
        divider_color_g = 16;
        divider_color_b = 0;
    }

    Canvas_* diff = canvas_diff(c1,c2);
    Canvas_* feedback = canvas_new(c1->width,(c1->height*NUM_CHANNELS) + 10 , name);

    size_t len = canvas_size(c1);

    size_t shared_index = 0;
    size_t cell_amount = c1->width * c1->height * NUM_CHANNELS;

    /* Copy diff */
    for(size_t i = 0; i < len; i=i+NUM_CHANNELS){
        feedback->buffer[shared_index] = diff->buffer[i];
        feedback->buffer[shared_index+1] = diff->buffer[i+1];
        feedback->buffer[shared_index+2] = diff->buffer[i+2];
        shared_index = shared_index +NUM_CHANNELS;
    }

    /* Draw second divider */
    for(size_t i = 0; i < (5*c1->width*NUM_CHANNELS); i= i+NUM_CHANNELS){
        feedback->buffer[shared_index] = divider_color_r;
        feedback->buffer[shared_index+1] = divider_color_g;
        feedback->buffer[shared_index+2] = divider_color_b;
        shared_index = shared_index +NUM_CHANNELS;
    }

    /* Copy c2 */
    for(size_t i = 0; i < len; i=i+NUM_CHANNELS){
        feedback->buffer[shared_index] = c2->buffer[i];
        feedback->buffer[shared_index+1] = c2->buffer[i+1];
        feedback->buffer[shared_index+2] = c2->buffer[i+2];
        shared_index = shared_index +NUM_CHANNELS;
    }

    /* Draw first divider */
    for(size_t i = 0; i < (5*c2->width*NUM_CHANNELS); i= i+NUM_CHANNELS){
        feedback->buffer[shared_index] = divider_color_r;
        feedback->buffer[shared_index+1] = divider_color_g;
        feedback->buffer[shared_index+2] = divider_color_b;
        shared_index = shared_index +NUM_CHANNELS;
    }

    /* Copy c1 */
    for(size_t i = 0; i < cell_amount;i=i+NUM_CHANNELS){
        feedback->buffer[shared_index] = c1->buffer[i];
        feedback->buffer[shared_index+1] = c1->buffer[i+1];
        feedback->buffer[shared_index+2] = c1->buffer[i+2];
        shared_index = shared_index +NUM_CHANNELS;
    }

    canvas_save_feedback(feedback);
    canvas_free(feedback);
    canvas_free(diff);
}


/*
 * Determine whether the given coordinate is outside the given canvas.
 */
bool canvas_check_coordinate_inside(Canvas_ *c, int32_t x, int32_t y) {
    if (c->supplied_invalid_coordinates) {
        /* We don't want to change the canvas if we ever got invalid coordinates */
        return false;
    } else if (x < 0 || y < 0 || x >= c->width || y >= c->height) {
        c->supplied_invalid_coordinates = true;
        c->first_invalid_x = x;
        c->first_invalid_y = y;
        return false;
    } else {

        return true;
    }
}

/*
 * Set a pixel at the given coordinate to the given color.
 * 0 is no amount of color, 255 is maximum amount of color channel present.
 */
Canvas_* canvas_set_rgb(Canvas_* c, int32_t x, int32_t y, uint8_t red, uint8_t green, uint8_t blue){
    if (!canvas_check_coordinate_inside(c,x,y)) {
        return c;
    }

    int offset = (c->width * y*NUM_CHANNELS) + (x*NUM_CHANNELS);
    c->buffer[offset] = red;
    c->buffer[offset+1] = green;
    c->buffer[offset+2] = blue;

    return c;
}

/*
 * Set a pixel at the given coordinate to the given grey value.
 */
Canvas_* canvas_set_grey(Canvas_* c, int32_t x, int32_t y, uint8_t value){
    return canvas_set_rgb(c, x, y, value, value, value);
}

Canvas_* canvas_set_black(Canvas_* c, int32_t x, int32_t y){
    return canvas_set_rgb(c, x, y, 0,0,0);
}

Canvas_* canvas_set_white(Canvas_* c, int32_t x, int32_t y){
    return canvas_set_rgb(c, x, y, 255,255,255);
}

int canvas_width(Canvas_* c){
    return c->width;
}

int canvas_height(Canvas_* c){
    return c->height;
}

/*
 * Return `1` if the pixel at the given coordinate has the corresponding color, `0` otherwise.
 */
int pixel_is_color(Canvas_* c, int x, int y, uint8_t* rgb_values){
    if (!canvas_check_coordinate_inside(c,x,y)) {
        return 0;
    }

    int target_pixel = (c->width * y*NUM_CHANNELS) + (x*NUM_CHANNELS);
    uint8_t pixel_values[3];
    pixel_values[0] = c->buffer[target_pixel];
    pixel_values[1] = c->buffer[target_pixel+1];
    pixel_values[2] = c->buffer[target_pixel+2];

    return pixel_values[0] == rgb_values[0] && pixel_values[1] == rgb_values[1] &&
            pixel_values[2] == rgb_values[2];
}

/*
 * Return `1` if the pixel at the given coordinate is white, `0` otherwise.
 */
int pixel_is_black(Canvas_* c, int x, int y){
    uint8_t rgb_values[3] = {0,0,0};
    return pixel_is_color(c,x,y,rgb_values);
}

/*
 * Return `1` if the pixel at the given coordinate is white, `0` otherwise.
 */
int pixel_is_white(Canvas_* c, int x, int y){
    uint8_t rgb_values[3] = {255,255,255};
    return pixel_is_color(c,x,y,rgb_values);
}

typedef struct color_{
    int16_t red;
    int16_t green;
    int16_t blue;
} rgb_color;

/*
 * Function returns a color struct with the color values at the
 * specified coordinates.
 * 0 <= x < canvas width
 * 0 <= y < canvas height
 * The color struct contains -1 as channel values if coordinates are outside the canvas
 */
rgb_color get_color_pixel(Canvas_* c, int x, int y){
    //uint8_t* channel_values = mallocx(NUM_CHANNELS * sizeof(uint8_t));
    rgb_color channel_values;
    channel_values.red = -1;
    channel_values.green = -1;
    channel_values.blue = -1;

    if (!canvas_check_coordinate_inside(c,x,y)) {
        return channel_values;
    }

    int target_pixel = (c->width * y*NUM_CHANNELS) + (x*NUM_CHANNELS);
    channel_values.red = c->buffer[target_pixel];
    channel_values.green = c->buffer[target_pixel+1];
    channel_values.blue = c->buffer[target_pixel+2];

    return channel_values;
}

/*
 * Retrieves the color value of the 'red' channel at a given coordinate and converts it into a normalised float value
 *
 * 0 <= x < canvas width
 * 0 <= y < canvas height
 */
float canvas_get_r (Canvas_* c, int x, int y){
    rgb_color values = get_color_pixel(c,x,y);
    if(values.red == -1) {
        return -1.0;
    }
    return values.red/255.0;
}

/*
 * Retrieves the color value of the 'green' channel at a given coordinate and converts it into a normalised float value
 *
 * 0 <= x < canvas width
 * 0 <= y < canvas height
 */
float canvas_get_g (Canvas_* c, int x, int y){
    rgb_color values = get_color_pixel(c,x,y);
    if(values.green == -1) {
        return -1.0;
    }
    return values.green/255.0;
}

/*
 * Retrieves the color value of the 'blue' channel at a given coordinate and converts it into a normalised float value
 *
 * 0 <= x < canvas width
 * 0 <= y < canvas height
 */
float canvas_get_b (Canvas_* c, int x, int y){
    rgb_color values = get_color_pixel(c,x,y);
    if(values.blue == -1) {
        return -1.0;
    }
    return values.blue/255.0;
}

/*
 * Set the 'red' channel at the given coordinate to the given value.
 * 0.0 is no amount of color, 1.0 is maximum amount of color channel present.
 */
Canvas_* canvas_set_r(Canvas_* c, int x, int y, float r){
    if (!canvas_check_coordinate_inside(c,x,y)) {
        return c;
    }
    if(r < 0.0) r = 0.0;
    if(r > 1.0) r = 1.0;
    int red = r * 255;
    int offset = (c->width * y*NUM_CHANNELS) + (x*NUM_CHANNELS);
    c->buffer[offset] = red;

    return c;
}

/*
 * Set the 'green' channel at the given coordinate to the given value.
 * 0.0 is no amount of color, 1.0 is maximum amount of color channel present.
 */
Canvas_* canvas_set_g(Canvas_* c, int x, int y, float g){
    if (!canvas_check_coordinate_inside(c,x,y)) {
        return c;
    }
    if(g < 0.0) g = 0.0;
    if(g > 1.0) g = 1.0;
    int green = g * 255;
    int offset = (c->width * y*NUM_CHANNELS) + (x*NUM_CHANNELS);
    c->buffer[offset+1] = green;

    return c;
}

/*
 * Set the 'blue' channel at the given coordinate to the given value.
 * 0.0 is no amount of color, 1.0 is maximum amount of color channel present.
 */
Canvas_* canvas_set_b(Canvas_* c, int x, int y, float b){
    if (!canvas_check_coordinate_inside(c,x,y)) {
        return c;
    }
    if(b < 0.0) b = 0.0;
    if(b > 1.0) b = 1.0;
    int blue = b * 255;
    int offset = (c->width * y*NUM_CHANNELS) + (x*NUM_CHANNELS);
    c->buffer[offset+2] = blue;

    return c;
}


/*
 * Converts the array into a canvas, with each array index represented as a column of height equal to its value.
 * For that, the canvas needs a height which is at least as big as the biggest value in the array. This is given as a
 * parameter to prevent forced canvas size changes when array values are modified.
 * One index of the array can optionally be highlighted in a bright color. If the highlight_index is -1, no highlighting
 * occurs.
 */
Canvas_* array_to_canvas (int32_t* array, size_t len, size_t min_height, int32_t highlight_index){

    size_t column_width = 2;
    size_t gap_width = 1;
    size_t canvas_width = ((column_width + gap_width) * len) - gap_width /*last gap unnecessary*/;

    size_t visual_padding = (0.2 * min_height) > 20 ? 20 : (0.2 * min_height); /*padding for clarity*/
    size_t canvas_height = min_height + visual_padding;

    Canvas_* array_canvas = canvas_new(canvas_width, canvas_height, "array_canvas");

    size_t canvas_x = 0;
    for(size_t x = 0; x < len; x++){
        if(x == highlight_index){
            for(size_t y = 0; y < array[x]; y++){
                for(size_t offset = 0; offset < column_width; offset++){
                    canvas_set_rgb(array_canvas, canvas_x+offset, y, 15, 90, 242);
                }
            }
        } else {
            for(size_t y = 0; y < array[x]; y++){
                for(size_t offset = 0; offset < column_width; offset++){
                    canvas_set_black(array_canvas, canvas_x+offset, y);
                }
            }
        }
        canvas_x += column_width + gap_width;
    }
    return array_canvas;
}

// /*
//  * Function returns the color value at the specified coordinates.
//  * Only gives satisfactory values if all channels have the same value.
//  * 0 <= x < canvas width
//  * 0 <= y < canvas height
//  */
// uint8_t get_grey_pixel(Canvas_* a_canvas, int x, int y){
//     int validated = validate_pixel(a_canvas,x,y);

//     if(!validated){
//         fprintf(stderr,"Pixel-Coordinates are not within Canvas!\n");
//         fprintf(stderr,"Aborting program..\n");
//         abort();
//     }
//     int target_pixel = (a_canvas->width * y*NUM_CHANNELS) + (x*NUM_CHANNELS);

//     return a_canvas->buffer[target_pixel];
// }



// uint8_t get_pixel(Canvas_* a_canvas, int x, int y){
//     return get_grey_pixel(a_canvas,x,y);
// }

#endif