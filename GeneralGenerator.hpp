class GeneralGenerator {
public:
    GeneralGenerator() {
        srand(static_cast<unsigned>(time(NULL)));
    }
    
private:
    int randomize(int max){
        return rand() % max;
    }
};
