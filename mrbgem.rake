MRuby::Gem::Specification.new('mruby-bsdgpio') do |spec|
  spec.license = 'BSD'
  spec.authors = 'Hiroki Mori'

  spec.linker.libraries << ['gpio']
end
