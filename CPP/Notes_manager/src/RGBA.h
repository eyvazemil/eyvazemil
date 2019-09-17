#ifndef PA2_PROJECT_RGBA_H
#define PA2_PROJECT_RGBA_H

class RGBA {
public:
    int m_r, m_g, m_b, m_a;
    //! constructors
    RGBA() = default;
    RGBA(int, int, int, int);
    RGBA(const RGBA &);
    RGBA & operator=(const RGBA &);
};

#endif //PA2_PROJECT_RGBA_H
