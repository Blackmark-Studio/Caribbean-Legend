//Jason общий диалог индейцев на улицах
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
			dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Paleface","「白い女インディアン」")+" 話がしたいのか？","またお前か。 "+GetSexPhrase("青白い顔","「白い女インディアン」")+".",""+GetSexPhrase("青白い顔はよくしゃべるな。まるで女みたいだ。","白い女インディアンはおしゃべりが好きだ。")+"","偉大なる精霊が白人を連れてきた"+GetSexPhrase("兄弟","姉妹")+" 私に。","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("「ああ。」","ああ、また俺だぜ。","とても詩的だな。","私もあなたに会えて嬉しいです。",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "やあ、白い兄弟。インディアンと話したいのか？";
				link.l1 = "ごきげんよう、ジャングルの息子よ。会えて嬉しいが、私は行かねばならぬ。";
				link.l1.go = "exit";
				npchar.quest.meeting = "1";
			}
			NextDiag.TempNode = "First time";
		break;

		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"精霊を怒らせるな、顔の白い奴！その長いナイフをしまえ！","死に急ぐなよ、色白野郎！その長いナイフをしまえ！");
			link.l1 = LinkRandPhrase("結構だ。","ご希望の通りに。","おっしゃる通りです。");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
