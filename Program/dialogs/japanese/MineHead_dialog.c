// диалог начальника шахты
void ProcessDialogEvent()
{
	ref NPChar, sld, location;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		location = &Locations[FindLocation(pchar.location)];
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("ここに顔を出すとは、よくもまあ大胆な野郎だな！？お前が勇敢なのか、それともただの馬鹿なのか、俺にはわからねえ……","「どうしてこの怠け者どもが敵に俺の屋敷へ侵入させちまったんだ？俺には理解できねえ……」","「こんな野郎どもがうろついてやがるなら、俺の護衛なんざ銅貨一枚の価値もねえな……」"),LinkRandPhrase("何の用だ？"+GetSexPhrase("ろくでなし","くせえ野郎")+"？！俺の兵士たちはすでにお前の後を追っているぞ、 "+GetSexPhrase("、汚い海賊め","")+"!","汚い殺人者め、今すぐ私の屋敷から出て行け！\n衛兵！","俺はお前なんか怖くねえぞ。 "+GetSexPhrase("「ネズミ」","尻軽女")+"！すぐにお前は俺たちの砦で絞首刑にされるんだ、その後はどこにも行けやしねえぞ…"));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("こいつら兵隊なんざ、一ペソの価値もねえ……","奴らに俺は絶対捕まらねえ。"),RandPhraseSimple("黙れ "+GetWorkTypeOfMan(npchar,"")+"、さもないとその汚ねえ舌を引き抜いてやるぞ！","おとなしく座ってろ、そうすりゃ生きて乗り切れるかもしれねえぞ……"));
				link.l1.go = "fight";
				break;
			}
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
    			dialog.text = "鉱山に敵だ！警報だ！";
				link.l1 = "ああっ、悪魔め！";
				link.l1.go = "fight"; 
				break;
			}	
			dialog.text = LinkRandPhrase(""+TimeGreeting()+"、旦那。私は "+GetFullName(npchar)+"、ロス・テケス鉱山の鉱山技師だ。何の用でここに来たんだ？","こんにちは、旦那。何のご用だ？","ふむ……俺に何か用かい、旦那？聞いてやるぜ。");
			if (!CheckAttribute(location, "quest.info"))
			{
				link.l9 = "俺はここに来たばかりなんだが、この鉱山についてもっと知りたいんだ…";
				link.l9.go = "info";
			}
			if (GetSquadronGoods(pchar, GOOD_SLAVES) > 4)
			{
				link.l2 = "俺の船倉にあんたが興味を持ちそうな積荷があるぜ。正確には、あんたの鉱山用の奴隷だ。値段の交渉でもするかい？";
				if (!CheckAttribute(location, "quest.slaves")) link.l2.go = "slaves_0";
				else link.l2.go = "slaves";
			}
			link.l1 = "ちょっと挨拶しに来ただけなのに、もう出ていくんだ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "info":
			dialog.text = "ロス・テケス鉱山はスペイン王室のために金を採掘している。ここで採れるものはすべてスペインのものだ。 ここでは金だけでなく、銀の塊や貴重な宝石も見つかる。金はここで売っていない。採れたものはすべて、 護衛付きの船団で旧世界へ送られる。ただし、金と銀の塊については二つの例外がある。第一に、 一定量なら現地の倉庫番から店で買うことができる。時には給料が遅れることもあるので、 そういう時のために多少の現金をここに残しておく必要がある。だから、地元での取引は許可されているのだ。第二に、 常に労働力が不足しているので、塊を奴隷と交換している。だから、 何か提供できるものがあれば私に話しかけてくれれば取引しよう。鉱山での規律は言うまでもないと思うが――盗みを働くな、囚人の邪魔をするな、兵士にちょっかいを出すな。さもないと、ひどい目に遭うぞ。";
			link.l1 = "「元気だ、ありがとう！」";			
			link.l1.go = "exit";
			location.quest.info = "true";
		break;
		
		// генератор купли-продажи рабов
		case "slaves_0":
			location.quest.slaves.qty = 200; // стартовая потребность
			dialog.text = "もちろんだよ、旦那！いくつ持ってるんだ？";
			link.l1 = "私は持っている "+FindRussianQtyString(GetSquadronGoods(pchar,GOOD_SLAVES))+".";
			link.l1.go = "slaves_1";
		break;
		
		case "slaves":
			location.quest.slaves.qty = sti(location.quest.slaves.qty)+GetNpcQuestPastDayParam(location, "slave_date"); // каждый день даёт +1 потребности
			if (sti(location.quest.slaves.qty) > 350) location.quest.slaves.qty = 350; // максимум потребности
			if (sti(location.quest.slaves.qty) < 5)
			{
				dialog.text = "旦那、残念だが、今はこれ以上奴隷は必要ないんだ。しかし状況はいつでも変わるから、 数週間後かまた別の時に来てくれ。";
				link.l1 = "わかったよ、旦那。今は必要ないが、そのうち必要になるかもしれねえぜ。";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "もちろんだよ、旦那！いくつ持ってるんだ？";
				link.l1 = "私は持っている "+FindRussianQtyString(GetSquadronGoods(pchar,GOOD_SLAVES))+".";
				link.l1.go = "slaves_1";
			}
		break;
		
		case "slaves_1":
			dialog.text = "奴隷一人につき、金の延べ棒一つか銀の延べ棒二つ、どちらかを支払う用意がある。どちらを選ぶ？";
			link.l1 = "金の延べ棒。";
			link.l1.go = "slaves_g";
			link.l2 = "銀の延べ棒。";
			link.l2.go = "slaves_s";
			link.l3 = "申し訳ないが、旦那、今気が変わったんだ。別の機会にな。";
			link.l3.go = "slaves_exit";
		break;
		
		case "slaves_g":
			location.quest.slaves.type = "gold";
			dialog.text = "いいだろう。俺に奴隷を何人売るつもりだ？";
			link.l1 = "";
			link.l1.edit = 6;
			link.l1.go = "slaves_trade";
		break;
		
		case "slaves_s":
			location.quest.slaves.type = "silver";
			dialog.text = "いいだろう。俺に何人の奴隷を売るつもりだ？";
			link.l1 = "";
			link.l1.edit = 6;
			link.l1.go = "slaves_trade";
		break;
		
		case "slaves_trade":
			iTotalTemp = sti(dialogEditStrings[6]);
			if (iTotalTemp < 1)
			{
				dialog.text = "旦那、くだらない冗談に付き合ってる暇はないんだ。ふざけたいなら酒場にでも行きな！";
				link.l1 = "ふむ……";
				link.l1.go = "slaves_exit";
				break;
			}
			if (iTotalTemp > GetSquadronGoods(pchar, GOOD_SLAVES))
			{
				dialog.text = "旦那、休んだほうがいいと思いますぜ。たぶん、かなり疲れてるか、日射病にでもなったんじゃねえですか。 酒場に行って休んでから、また取引を続けましょうや。";
				link.l1 = "ふむ……";
				link.l1.go = "slaves_exit";
				break;
			}
			if (iTotalTemp > sti(location.quest.slaves.qty))
			{
				dialog.text = "残念だが、旦那、今はそんなに多くの奴隷はいらねえんだ。鉱山が今必要としているのは "+FindRussianQtyString(sti(location.quest.slaves.qty))+"「そんなにたくさん売るつもりか？」";
				link.l1 = "「ああ、もちろんだ！」";
				link.l1.go = "slaves_max";
				link.l2 = "ふむ……まあ、俺はそうじゃねえな。";
				link.l2.go = "slaves_exit";
				break;
			}
			dialog.text = ""+FindRussianQtyString(iTotalTemp)+"？素晴らしい。町の門まで彼らを連れてくるよう命令を出してください。私の部下を迎えに行かせます。";
			link.l1 = "心配するな、旦那。奴隷どもはちゃんと時間通りに届けるぜ。すぐに必要な指示を出しておく。";
			link.l1.go = "slaves_calk";
		break;
		
		case "slaves_max":
			iTotalTemp = sti(location.quest.slaves.qty);
			dialog.text = "素晴らしい。彼らを町の門まで連れてくるよう命じてください。私の部下を迎えに行かせます。";
			link.l1 = "心配するな、旦那。奴隷たちはちゃんと時間通りに届けるぜ。すぐに必要な指示を出しておく。";
			link.l1.go = "slaves_calk";
		break;
		
		case "slaves_calk":
			DialogExit();
			Log_Info("Exchange of slaves for ingots has been completed");
			PlaySound("interface\important_item.wav");
			LAi_Fade("", "");
			WaitDate("",0,0,0,5,10);
			RemoveCharacterGoods(pchar, GOOD_SLAVES, iTotalTemp);
			if (location.quest.slaves.type == "gold") TakeNItems(pchar, "jewelry5", iTotalTemp);
			else TakeNItems(pchar, "jewelry6", iTotalTemp*2);
			DeleteAttribute(location, "slave_date");
			SaveCurrentNpcQuestDateParam(location, "slave_date");
			location.quest.slaves.qty = sti(location.quest.slaves.qty)-iTotalTemp;
		break;
		
		case "slaves_exit":
			DialogExit();
			DeleteAttribute(location, "slave_date");
			SaveCurrentNpcQuestDateParam(location, "slave_date");
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		    LAi_group_Attack(NPChar, Pchar);
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
