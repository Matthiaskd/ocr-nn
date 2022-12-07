#include<stdio.h>
#include<stdlib.h>
#include<math.h>


const size_t INPUT_NBR=2;
const size_t HIDDEN_NBR=4;
const size_t OUTPUT_NBR=1;

const double Learning_Rate=0.1;

double ReLU(double x){
    if (0>x)
        return 0;
    return x;
}

double ReLU_deriv(double x){
    if (0>x)
        return 0;
    return 1;
}


//double softmax(double m[], size_t i);


double rnd(){
    return ((double)rand()) / ((double) RAND_MAX);
}


void init_column(double m[], size_t length){
    for (size_t i =0; i< length; i++){
        m[i]=rnd();
    }
}





int setup(double Input_Nodes[2], double expected_output, double Hidden_Nodes[HIDDEN_NBR], double Output_Nodes[OUTPUT_NBR], double Weights_ih[INPUT_NBR][HIDDEN_NBR], double Weights_ho[HIDDEN_NBR][OUTPUT_NBR], double Hidden_Bias[HIDDEN_NBR], double Output_Bias[OUTPUT_NBR]){

    
    //------------------------------FEED FORWARD------------------------------------------//
    //hidden layer activation
    for (size_t i=0; i< HIDDEN_NBR; i++){
        double sum = Hidden_Bias[i];
        for(size_t j = 0; j< INPUT_NBR; j++){
            sum+=Input_Nodes[j]*Weights_ih[j][i];
        }
        Hidden_Nodes[i]=ReLU(sum);
    }

    //output layer activation
    for (size_t i=0; i< OUTPUT_NBR; i++){
        double sum = Output_Bias[i];
        for(size_t j = 0; j< INPUT_NBR; j++){
            sum+=Hidden_Nodes[j] * Weights_ho[j][i];
        }
        Output_Nodes[i]=ReLU(sum);
    }
    //------------------------------back propagation-------------------------------------//
    
    //output gradient calculation
    double  Output_gradient[OUTPUT_NBR];
    for (size_t i =0; i<OUTPUT_NBR; i++)
        Output_gradient[i]=Learning_Rate*(expected_output - Output_Nodes[i]) * ReLU_deriv(Output_Nodes[i]);
    
    //hidden gradient calculation: Hidden_Nodes^(T)*Output_err*lr
    double Hidden_gradient[HIDDEN_NBR];
    for(size_t i=0; i< HIDDEN_NBR; i++){
        double err=0;
        for(size_t j=0; j<OUTPUT_NBR; j++)
            err+=Output_gradient[j]*Weights_ho[i][j];
        Hidden_gradient[i]=Learning_Rate*err*ReLU_deriv(Hidden_Nodes[i]);
    }

    //backpropagate of the error***
    //output weights
    for(size_t i =0; i < OUTPUT_NBR; i++){
        Output_Bias[i]+=Output_gradient[i];
        for(size_t j=0; j < HIDDEN_NBR; j++){
            Weights_ho[j][i]+=Hidden_Nodes[j]*Output_gradient[i];
        }
    }

    //hidden weigths
    for(size_t i =0; i < HIDDEN_NBR; i++){
        Hidden_Bias[i]+=Hidden_gradient[i];
        for(size_t j=0; j < OUTPUT_NBR; j++){
            Weights_ih[j][i]+=expected_output *Hidden_gradient[i];
        }
    }


   /*for(size_t i=0; i< OUTPUT_NBR; i++){
   	printf("Output:%f, expected:%f\n", Output_Nodes[i], expected_output);
   }*/
   return 0;

}




int main(){

    //Nodes
    double Hidden_Nodes[HIDDEN_NBR];
    double Output_Nodes[OUTPUT_NBR];
    //weights
    double Weights_ih[INPUT_NBR][HIDDEN_NBR];
    double Weights_ho[HIDDEN_NBR][OUTPUT_NBR]; 
    //bias
    double Hidden_Bias[HIDDEN_NBR];
    double Output_Bias[OUTPUT_NBR];

    //initialisation
    init_column(Hidden_Nodes, HIDDEN_NBR);
    init_column(Hidden_Bias, HIDDEN_NBR);
    init_column(Output_Bias, OUTPUT_NBR);
    //weights_ih initialisation
    for (size_t i=0; i< INPUT_NBR; i++){
        for(size_t j=0; j<HIDDEN_NBR; j++){
            Weights_ih[i][j]=rnd();
        }
    }
    //weights_ho initialisation
    for (size_t i=0; i< HIDDEN_NBR; i++){
        for(size_t j=0; j<OUTPUT_NBR;j++){
            Weights_ho[i][j]=rnd();
        }
    }

    double Training[4][2]={
                {0, 0},
                {0, 1},
                {1, 0},
                {1, 1}
                };

    double output[4]={
                    0,
                    1,
                    1,
                    0
                 };



    for (size_t test=0; test<10000; test++){
        int random=(int)(rnd()*3);
        //printf("%i\n", random);
        setup(Training[random], output[random], Hidden_Nodes, Output_Nodes, Weights_ih, Weights_ho, Hidden_Bias, Output_Bias);
        
    }


    return 0;
}
