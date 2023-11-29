interface A{
    a: string,
    b: number,
    c?:string
}
type B = {
    [P in keyof A]?: Record<Exclude<keyof A, P>, never>
} & { [P in Exclude<keyof A, keyof any[]> as `${P}${Extract<keyof A, P>}`]?: never };
