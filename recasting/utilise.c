#include "../parisng/cub3d.h"

float normal_ang(double angle)
{
     angle = fmod(angle,M_PI*2);
    if(angle < 0)
        angle = M_PI*2+angle;
    return angle;
}

void draw_rays2(t_player *player)
{
    double first_y=0;
    double first_x=0;
    double xa=0;
    double ya =0;
    double next_h_x;
    next_h_x =0;
    double next_h_y;
    next_h_y=0;
    double next_v_x;
    next_v_x=0;
    double next_v_y;
    next_v_y =0;
    int i=0;
        double distance_h;
        double distance_v ;
        distance_h=0;
        distance_v=0;
        double ray_length;
        ray_length =0;
        float ray_angle = (normal_ang(player->angle) -FOV/2 );
    while (i< NUM_RAYS)
    {
        ray_angle = normal_ang(ray_angle);
        distance_h=99999999999999;
        distance_v =99999999999999;
        int flag =0;

        /////H//////////////
        printf("ray_angle=%f\n",ray_angle);
        if(ray_angle > 0 && ray_angle < M_PI)//down
            first_y =(floor(player->y/PEX)*PEX)+PEX;
        else    
            first_y =(floor(player->y/PEX) *PEX)-0.0001;

        first_x = player->x+((first_y-player->y)/tan(ray_angle));

        next_h_x =first_x;
        next_h_y=first_y;

        if(ray_angle > 0 && ray_angle < M_PI)
            ya=PEX;
        else    
            ya=-PEX;
        xa = ya/tan(ray_angle);
        while (next_h_x>=0 && next_h_x<=WIDTH && next_h_y >=0 && next_h_y<=HEIGHT)
        {
            printf("x=%dy=%d\n",(int)(next_h_x/PEX),(int)(next_h_y/PEX));
            if((int)(next_h_y/PEX) <= player->map_height &&((int)(next_h_x/PEX)) < (int)ft_strlen(player->map[(int)(next_h_y/PEX)]) && player->map[(int)(next_h_y/PEX)][(int)(next_h_x/PEX)]=='1')
            {
                // printf("is wall\n");
                distance_h = (sqrt(pow(next_h_x - player->x, 2) + pow(next_h_y - player->y, 2)));
                break;
            }
            else
            {

                next_h_x+=xa;
                next_h_y+=ya;
            }
        }
        /////////////-V-//////////////
        // if(ray_angle < (0.5*M_PI) || ray_angle >(1.5*M_PI))//rigth
        if(!(ray_angle > M_PI / 2 && ray_angle < 3 * M_PI / 2))
            first_x=(floor(player->x/PEX)*PEX)+PEX;
        else    
            first_x = (floor(player->x/PEX)*PEX)-0.001;
        first_y = player->y+( first_x -player->x)*tan(ray_angle);
        next_v_x =first_x;
        next_v_y =first_y;
         if(!(ray_angle > M_PI / 2 && ray_angle < 3 * M_PI / 2))
            xa =PEX;
        else
            xa=-PEX;
        ya= xa*tan(ray_angle);
        while (next_v_x>=0 && next_v_x<=WIDTH && next_v_y >=0 && next_v_y<=HEIGHT)
        {

            if((int)(next_v_y/PEX) <= player->map_height  &&((int)(next_v_x/PEX)) < (int)ft_strlen(player->map[(int)(next_v_y/PEX)]) && player->map[(int)(next_v_y/PEX)][(int)(next_v_x/PEX)]=='1')
            {
                distance_v =(sqrt(pow(next_v_x - player->x, 2) + pow(next_v_y - player->y, 2)));
                break;
            }
            else
            {
                next_v_x+=xa;
                next_v_y+=ya;
            }
        }
        if(distance_v< distance_h)
        {
            ray_length = distance_v;
            flag =1;
        }
        else
            ray_length = distance_h;

        //////////////wall 3D
        // ray_length = (sqrt(pow(next_h_x - player->x, 2) + pow(next_h_y - player->y, 2)));
        if((next_h_x>=0 && next_h_x<=WIDTH && next_h_y >=0 && next_h_y<=HEIGHT)||(next_v_x>=0 && next_v_x<=WIDTH && next_v_y >=0 && next_v_y<=HEIGHT))
        {
            ray_length *= cos(ray_angle - player->angle);
            double wall_light =(PEX/ray_length)*(WIDTH/2)/tan(FOV/2);
            double wall_b= (HEIGHT/2)+(wall_light/2);
            double wall_t= (HEIGHT/2)-(wall_light/2);
            if(wall_b> HEIGHT)  
                wall_b =HEIGHT;
            if(wall_t<0)
                wall_t=0;
            double sq = wall_t ;
            // printf("sq=====%f\n",sq);

            while (wall_t< wall_b)
            {
                printf("{%d, %f}\n", i, wall_t);
                if(flag)
                    mlx_put_pixel(player->img, i, wall_t++, 0xFF0000FF);
                else    
                    mlx_put_pixel(player->img, i, wall_t++, 0xFFFFFFFF);
            }
            while (wall_b < WIDTH)
            {
                mlx_put_pixel(player->img, i, wall_b++, 0x00FF00FF);
            }
            while (sq>0)
            {
                mlx_put_pixel(player->img, i, sq--,0x0000FFF0);
            }
        }
        //////////
        i++;
        ray_angle+=(FOV/NUM_RAYS);
        
    }
}

void clear_screen(t_player *p)
{
    int y = 0;
    int x;
    while (y < (int)p->black->height)
    {
        x = 0;
        while (x < (int)p->black->width)
        {
            mlx_put_pixel(p->black, x, y, 0x000000FF);
            x++;
        }
        y++;
    }
}


void my_keyhook(mlx_key_data_t keydata, void* param)
{
    t_player *player = (t_player *)param;

    /////////////////////
   
    ////////
    mlx_delete_image(player->mlx,player->img);
    player->img = mlx_new_image(player->mlx, 1500, 1200);

    mlx_delete_image(player->mlx,player->ray);
    player->ray = mlx_new_image(player->mlx, 1500, 1200);
    mlx_image_to_window(player->mlx, player->ray, 0, 0);
     mlx_image_to_window(player->mlx, player->img, 0, 0);
    if (keydata.key == MLX_KEY_W  && keydata.action)  // Move forward
    {
        float x =(cos(player->angle) * MOVE_SPEED);
        float y =(sin(player->angle) * MOVE_SPEED);
 
        float ray_x = player->x + x;
        float ray_y = player->y + y;
        if(player->map[(int)(player->y/PEX)][(int)(ray_x/PEX)] !='1' && player->map[(int)(ray_y/PEX)][(int)(player->x/PEX)] !='1')
        {
   
            player->x = ray_x;
            player->y = ray_y;
        }
  
    }
    if (keydata.key == MLX_KEY_S&& keydata.action)  // Move backward
    {
        float x =(cos(player->angle) * -MOVE_SPEED);
        float y =(sin(player->angle) * -MOVE_SPEED);
         float ray_x = player->x + x;
        float ray_y = player->y + y;
        if(player->map[(int)(player->y/PEX)][(int)(ray_x/PEX)] !='1' && player->map[(int)(ray_y/PEX)][(int)(player->x/PEX)] !='1')
        {
        player->x = ray_x;
        player->y = ray_y;
        }
    }
    if(keydata.key==MLX_KEY_A&& keydata.action)
    {
        float x =(cos(player->angle -M_PI/2) * MOVE_SPEED);
        float y =(sin(player->angle -M_PI/2) * MOVE_SPEED);
         float ray_x = player->x + x;
        float ray_y = player->y + y;
        if(player->map[(int)(player->y/PEX)][(int)(ray_x/PEX)] !='1' && player->map[(int)(ray_y/PEX)][(int)(player->x/PEX)] !='1')
        {
        player->x = ray_x;
        player->y = ray_y;
        }

    }
    if(keydata.key==MLX_KEY_D && keydata.action)
    {
        float x =(cos(player->angle +M_PI/2) * MOVE_SPEED);
        float y =(sin(player->angle +M_PI/2) * MOVE_SPEED);
         float ray_x = player->x + x;
        float ray_y = player->y + y;
        if(player->map[(int)(player->y/PEX)][(int)(ray_x/PEX)] !='1' && player->map[(int)(ray_y/PEX)][(int)(player->x/PEX)] !='1')
        {
        player->x = ray_x;
        player->y = ray_y;
        }

    }
    
    if (keydata.key == MLX_KEY_LEFT && keydata.action)  // Rotate left
    {
        player->ro = -1;
    
    }
    if (keydata.key == MLX_KEY_RIGHT && keydata.action)  // Rotate right
    {
        player->ro = 1;
    }
    if (keydata.key == MLX_KEY_ESCAPE)
        exit(0);
    player->angle += player->ro * ROTATE_SPEED;

 
    clear_screen(player);
    // draw_wall(player);
    // draw_rays(player);
    draw_rays2(player);
   
    mlx_put_pixel(player->img, (player->x), (player->y), 0xFF0000FF);
}
