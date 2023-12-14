#ifndef PRACE_S_PAMETI_H_INCLUDED
#define PRACE_S_PAMETI_H_INCLUDED

void prohod_promenne_pomoci_reference(int &a, int &b);
void prohod_promenne(int *a, int *b);
char *otoc_retezec(const char *zadano, char *otoceno);
char *otoc_retezec_na_miste(char * txt);
size_t delka_retezce_adresova_aritmetika(char* txt);
void vypis_chyboveho_textu_dle_parametru(int n);
void f(int &n);
void f(int &&n);
void f(double &n);
void f(double &&n);
void reference_na_r_hodnotu();
void vypis_clenskou_slozku_z_chytry_ukazatel();
void vypis_prikladu_z_teto_sekce_09();

template <typename T>
class ChytryUkazatel
{
private:
    T *data;

public:
    ChytryUkazatel(T *ptr) : data(ptr) {}
    ~ChytryUkazatel()
    {
        delete data;
    }

    T getValue() const
    {
        return *data;
    }
    // Další metody pro práci s ukazatelem...
};

#endif // PRACE_S_PAMETI_H_INCLUDED
