// диалог каторжников в шахте
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = NPCStringReactionRepeat("悪いけど、これ以上お互いに話さない方が二人のためだよ。俺は罰を受けるし、あんたも追い出されることになるからな。 ","もう全部話しただろ、友よ。まさか俺のせいで鞭打たれたいのか？","俺は聞いちゃいねえ……","スパードが打ちつけられ、つるはしがカンカンと鳴る…","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("ここはずいぶん厳しい規則があるんだな……","いや、もちろん欲しくねえよ。","ふむ……","パパ、聞こえるかい……",npchar,Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
			
		case "CitizenNotBlade":
			dialog.text = "船長、何をしているんだ？面倒なことになる前に武器をしまえ！";
			link.l1 = LinkRandPhrase("「いいだろう。」","「いいだろう。」","心配するな、ちゃんと隠してあるからな……");
			link.l1.go = "exit";
		break;  
	}
}
