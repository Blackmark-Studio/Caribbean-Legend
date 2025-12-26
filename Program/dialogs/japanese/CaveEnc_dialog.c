// пещерные энкаунтеры
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp, sGroup;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	sTemp = "CaveBandos" + locations[FindLocation(npchar.location)].index + "_";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "何か用か？";
			link.l1 = "いいや、何もない。";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "CaveBanditosSit":
			if (hrand(2) == 1) 
			{
				dialog.text = NPCStringReactionRepeat("おおっと、誰が来たかと思えば！今日は運がいいな、相棒。俺たちはいい奴らさ、ちょっと飯でも作ってるだけでよ……まあ、お前を晩飯に誘う気はねえが、今のうちにとっとと消えた方が身のためだぜ。","今すぐ消え失せろ、俺たちの邪魔をするんじゃねえ。明日また来い――財布を忘れずにな、ははは！","俺を怒らせるなよ、水夫！洞窟の入り口がどこか、まだ覚えてるだろうな？今すぐ、いや、 ものすごく急いでそこへ行くんだ…","さて、とうとう一線を越えやがったな、相棒！仕方ねえ、俺の用事を中断してでもお前を片付けてやるぜ、この野郎！","ブロック",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("お前さん、本当に親切だな……","お前、なかなか冗談がうまいじゃねえか……","よし、それじゃあ、お前はそのまま平たいケーキでも焼き続けてな…","やっと話が通じたな、ははっ！",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit_talk", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = LinkRandPhrase("おっと、なんてこった！獲物を探しに行く必要はねえな……もうここにいるぜ。おい、野郎ども――この気取った野郎から巻き上げてやろうじゃねえか！","ここには誰もお前を招いてねえぜ、相棒……だが、まあ来てくれて嬉しいもんだ。さて、どれだけ懐が重いか見せてもらおうじゃねえか！","誰もお前を無理やりここに連れてきたわけじゃねえぜ、へっへっ…だがもう来ちまったからには、ちょいとくすぐってみて、ポケットから何が出てくるか見せてもらうぜ…");
				link.l1 = LinkRandPhrase("今からお前の舌を少し短くしてやるぜ……","お前の剣の腕前がその口の達者さに見合ってるといいがな、べらべら野郎！","さて、お前の腐りかけの体にもう二つほど穴を開ける時が来たようだな…");
				link.l1.go = "fight";
			}
			NextDiag.TempNode = "CaveBanditosSit";
		break;
		
		case "CaveBanditosStay":
			dialog.text = LinkRandPhrase("おお、なんてこった！獲物を探しに行く必要はねえな……もうここにいるじゃねえか。おい、野郎ども――この気取った野郎をゆすってやろうぜ、どうだ？","ここには誰もお前を招いてねえぜ、相棒……だが、まあ来てくれてよかったさ。さてと、お前の財布がどれだけ重いか見せてもらおうか！","誰もお前を無理やりここに連れてきたわけじゃねえぜ、へへ……だが、せっかく来たんだ、ちょっとくすぐってみて、ポケットから何が出てくるか見てやろうじゃねえか……");
			link.l1 = LinkRandPhrase("今からお前の舌を少し短くしてやるぜ……","お前の剣の腕前が、その減らず口と同じくらいだといいがな、べらべら野郎！","さて、お前の朽ちる体にもう二つほど穴を開ける時が来たようだな…");
			link.l1.go = "fight";
		break;
		
		case "CaveBanditosTreasure":
			dialog.text = NPCStringReactionRepeat("消えな、相棒。ここにお前の出る幕はねえぞ！","おい、優しく言ってやってるんだ。とっとと消えな。何が起こるかわからねえぜ……","最後の警告だ。今すぐ消え失せねえと、ここに来たことを一生後悔するぜ。","それまでだぜ、相棒、トラブルを自分で呼び込んだんだ。","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("俺に指図するんじゃねえ、わかったか？","「で、そこに何が特別なんだ？ただの洞窟だろ、他に何もねえ……」","「おいおい、勘弁してくれよ……」","はっ！さて、どっちが上か見せてやるぜ、クソ野郎！",npchar,Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "CaveBanditosTreasure";
		break;
		
		case "CaveCaribSit":
			if (hrand(2) == 2) 
			{
				dialog.text = NPCStringReactionRepeat("色白のやつ、どっか行け。あいつは喜ぶぞ。 "+npchar.name+"  親切だな。今日は神々があんたに哀れみをかけてくださるぞ。","俺と兄弟たちが怒る前に、この洞窟から出ていけ！","出ていけ、この青白い野郎！","貴様の運も命もここまでだ、白い犬め！","ブロック",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("「おう、ありがとうよ、相棒、そりゃあ親切だな…」","この洞窟はお前のものじゃねえし、俺は好きなところに行くぜ。","落ち着けよ、沼のガキ。","今からその言葉をそのままお前の喉に叩き込んでやるぜ、この野郎……",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit_talk", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = LinkRandPhrase("呪われた白い顔が俺たちの焚き火に来やがった！うひゃー！お前はもう終わりだぜ！","間抜けな白顔め、ジャガーの巣に迷い込んだな。お前の肝を焼いてやるぞ！","生意気な白い顔が俺の洞窟に来やがったか？なら、生きては帰れねえぞ！");
				link.l1 = LinkRandPhrase("今からお前の舌を引き抜いてやる……","これで人食いどもが少し減るってわけだな……","さて、お前の腐りかけの体にもう二つほど穴を開けてやる時が来たようだな、この赤っ面の猿め。");
				link.l1.go = "fight";
			}
			NextDiag.TempNode = "CaveCaribSit";
		break;
		
		case "CaveCaribStay":
			dialog.text = LinkRandPhrase("汚らわしい白い顔が俺たちの洞窟に来やがったな！ひひっ！てめえの舌を切り取って焼いてやるぜ！","愚かな白顔がジャガーの巣に来やがったぞ。兄弟たち、この呪われた白い野郎をぶった斬れ！","生意気な白顔が俺の洞窟に来やがったか？なら、生きては帰れねえぞ！");
			link.l1 = LinkRandPhrase("てめえの血まみれの首をぶった切ってやる……","これで世の中の人食いどもが少し減るな……","さあ、覚悟しろよ、赤肌野郎。地獄へ落ちやがれ！");
			link.l1.go = "fight";
		break;
		
		case "exit_talk":
			DialogExit();
			sGroup = "CaveGroup_" + locations[FindLocation(pchar.location)].index;
			for(i=0; i<4; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_CharacterDisableDialog(sld);
			}
			LAi_CharacterEnableDialog(npchar);
		break;
		
		case "fight":
			DialogExit();
			sGroup = "CaveGroup_" + locations[FindLocation(pchar.location)].index;
			for(i=0; i<4; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "CaveEnc_RaidersAfrer");
			chrDisableReloadToLocation = true;
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
