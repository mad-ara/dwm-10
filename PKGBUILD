pkgname=dwm
gitname=dwm
pkgver=0.8.2
pkgrel=1
pkgdesc='Dynamic Window Manager for X'
arch=('x86_64')
#makedepends=('ncurses' 'libxext' 'git')
source=('git+https://github.com/SearyBlue/dwm')
sha1sums=('SKIP')
provides=('dwm')
conflicts=('dwm' 'dwm-git')

build() 
{
    cat ../source/config.h > "$gitname/config.h"
	cd "$srcdir/$gitname"
	# git commit -m "updated config.h"
	make
}

package() 
{
  	cd "$srcdir/$gitname"
  	make PREFIX=/usr DESTDIR="${pkgdir}" install
    install -Dm644 LICENSE "${pkgdir}/usr/share/licenses/${pkgname}/LICENSE"
    # install -Dm644 README.md "${pkgdir}/usr/share/doc/${pkgname}/README"
}
