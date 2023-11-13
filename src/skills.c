#include "skills.h"

/* SKILLS */
int leggere_bombardamento_aereo(skills varianti)
{
    return varianti.bombardamento_aereo;
}

int leggere_colpo_largo_raggio(skills varianti)
{
    return varianti.colpo_largo_raggio;
}

int leggere_radar(skills varianti)
{
    return varianti.radar;
}

skills scrivere_bombardamento_aereo(skills varianti,int bombardamento_aereo)
{
    varianti.bombardamento_aereo=bombardamento_aereo;
    return varianti;
}

skills scrivere_colpo_largo_raggio(skills varianti,int colpo_largo_raggio)
{
    varianti.colpo_largo_raggio=colpo_largo_raggio;
    return varianti;
}

skills scrivere_radar(skills varianti,int radar)
{
    varianti.radar=radar;
    return varianti;
}

