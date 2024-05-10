*Circumradius of a triangle: (Triangle er baire
circle)
1. a/sinA=2R
2. Triangle area=(1/2)*bcsinA
3. R=(abc)/(4*area)
*Incircle radius: (triangle er vitore circle)
1. R=(2*area)/(a+b+c)
*Excircle radius: (triagle er ek bahur baire lagano
circle)
1. R=((incircle radius)*(a+b+c))/ (b+c-a);
** Trigonometry:
1. a/sinA=b/sinB=c/sinC=2R where R=Circumradius of a
triangle
2. sq(a)=sq(b)+sq(c)-2bc*cosA
** k method of circle
1. (x-x1)(x-x2)+(y-y1)(y-y2)+
k*(x-x1)(y1-y2)-(y-y1)*(x1-x2)=0
** conical frustum:
1. volume=(pi/3)*height*(sq(r1)+sq(r2)+r1*r2)
** eqn of line between two points
if(fabs(p1.x-p2.x)<eps) { l.a=1.0;l.b=0.0,l.c=-p1.x; }
else { l.a=-(double)(p1.y-p2.y)/(p1.x-p2.x);
l.b=1.0; l.c=-(double)(l.a*p1.x)-p1.y; }
** picks theorem
I=A-(B/2)+1