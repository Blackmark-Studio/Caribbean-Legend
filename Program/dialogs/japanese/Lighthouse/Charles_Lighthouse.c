// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("何の用だ？","何を知りたいんだ？"),"何か用か、 "+GetAddress_Form(NPChar)+"?","「それはもう三度目だぞ、お前が俺に聞こうとしたのは……」","もううんざりだ、消え失せろ！","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("悪いが、気が変わったんだ。","なんでもねえ、悪かったな。"),"忘れてしまった、すまねえ…","三度目の正直ってやつだな、え？失礼するぜ…","すまん、すまん！じゃあ、俺はこれで失礼するぜ……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}
