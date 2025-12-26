// диалог освобожденных каторжников рудника
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = NPCStringReactionRepeat("またお前か、旦那？","聞けよ、旦那、ここは引き下がった方がいいぜ……","邪魔しないでくれ、旦那！頼むからさ。","ああ、それは耐えられねえ……ガレー船を漕ぐ方がまだマシだったぜ。","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("「ああ、また俺だ。」","俺に指図するんじゃねえ。","「それでも俺がしつこくしたらどうするんだ？」","じゃあ、さっさと厨房に戻れ！",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "何の用だ、旦那？";
				link.l1 = "お前からか？何もないと思うぜ。ちょっと挨拶したかっただけだ。";
				link.l1.go = "exit";
				npchar.quest.meeting = "1";
			}
			NextDiag.TempNode = "First time";
		break;

		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"運命を甘く見るな、相棒！武器をしまえ！","聞いてくれ、俺はこの町の市民だ。だから剣を収めてくれ。");
			link.l1 = LinkRandPhrase("……いいだろう……","ご希望のままに……","おっしゃる通りで…");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
