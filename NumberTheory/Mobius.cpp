int mob[N];
void mobius(){
for(int i = 1; i < N; i++) mob[i] = 3;mob[1] = 1;
for (int i = 2; i < N; i++){
if (mob[i] == 3){
mob[i] = -1;
for (int j = 2 * i; j < N; j += i)
mob[j] = (mob[j] == 3 ? -1 : mob[j] * (-1));
if (i < N / i) for (int j = i * i; j < N; j += i * i)
mob[j] = 0;
}}}