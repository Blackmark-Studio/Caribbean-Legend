// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("何の用だ？","何を知りたいんだ？"),"何か用か、 "+GetAddress_Form(NPChar)+"?","「それで三度目だぞ、俺に聞こうとしたのは……」","もううんざりだ、消え失せろ！","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("悪いが、気が変わったんだ。","なんでもねえ、すまねえな。"),"忘れてた、すまねえ…","三度目の正直ってやつだな、え？失礼するぜ…","すまん、すまん！じゃあ、俺はこれで失礼するぜ……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "聞いてくれ――ジョアキム・メリマンという名の男がここに来たことはあるか？中年のポルトガルの旦那で、口ひげとあごひげ、 鋭い目をしてるんだ。入り江か灯台の近くで上陸したかもしれねえ。そんな奴を見かけなかったか？";
				link.l1.go = "merriman";
			}
		break;
		
		// калеуче
		case "merriman":
			dialog.text = "いや、そんな奴は見てねえな。いたら気づくはずだぜ。";
			link.l1 = "なるほど、残念だな。時間を取ってくれてありがとう。それじゃあ、引き続き探してみるぜ。";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}
