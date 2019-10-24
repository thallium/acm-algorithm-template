
  //THIS FILE DEFINES TS-TEX's API AND SHOULD NOT BE EDITED. IF EDITED YOU CAN REWRITE THIS FILE USING TsApiFile.rewrite(). 
  //CHANGING ANY OF THIS CONTENT WILL NOT AFFECT THE ACTUAL API THAT IS EXPOSED BY THE RUNTIME AND THEREFORE WILL HAVE NO EFFECT!
  export interface IRange 
{
  start: ILocation;
  end: ILocation;
}
export interface ILocation
{
  offset: number;
  line: number;
  column: number;
}

export type IRootNode = IFnNode | ITextNode;
export type NodeType = "fn" | "text" | "parameter" | "parametersep" | "fnname" | "parameterlist" | "typeannotation";


export interface INode
{
  range: IRange;
  type: NodeType;
}

export interface ITextNode extends INode
{
  getText(filetext: string);
}

export interface IFnNode extends INode
{
  complete: boolean;
  parameters: IParameterListNode;
  name: IFnNameNode;

  getStatementText(filetext: string);
}

export interface IFnNameNode extends INode
{
  name: string;
}

export interface IParameterListNode extends INode
{
  parameters: IParameterNode[];
}

export interface IParameterNode extends INode
{
  annotation: IAnnotationNode;
}

export interface IParameterSeperatorNode extends INode {}
export interface IAnnotationNode extends INode {}

export interface IResolver
{
  resolve<T>(type: string, key?: string);
  register(object: any, type: string, key?: string);
  unregister(object: any);
}

export interface ISourceFile
{
  path: string;
  nodes: IRootNode[];
  text: string;
}

export interface ILifecycleHookComponent
{
  _prebuild?();
  _postbuild?();
  _init?(resolver: IResolver);
  _finalize?();
}

export interface IModule extends ILifecycleHookComponent
{
}

export interface ICompletionItem
{
  name: string;
  sortText: string;
  insertText?: string;
  hasAction?: true;
  source?: string;
  isRecommended?: true;
}

export interface ICompletionItemProvider extends ILifecycleHookComponent
{
  provideCompletionItems(triggerChar: string, node: IRootNode, file: ISourceFile): ICompletionItem[];
}
