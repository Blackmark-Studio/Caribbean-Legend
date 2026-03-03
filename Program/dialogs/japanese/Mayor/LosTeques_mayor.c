void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("ここに来るとは大胆だな！？勇気ある行動だ……","「どうしてあの愚か者どもが敵の侵入を許したのだ！？私には理解できません……」","さて、私の護衛たちも、どこぞの愚か者が私の邸宅内をうろついているようでは役に立ちませんな……"),LinkRandPhrase("何の用だ、この野郎！？俺の兵士たちはすでにお前を追い詰めたんだ、もう逃げられねえぞ。"+GetSexPhrase("、汚らわしい海賊め"," 汚らわしい海賊")+"!","「汚らわしい殺人者め、私の邸宅から出て行け！衛兵たち！！！」","俺はお前なんか怖くねえぞ、この野郎！お前は絞首刑だ、逃げられやしねえ…"));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("兵士たちには費用がかからぬ……","奴らに俺は絶対捕まらねえ。"),RandPhraseSimple("「黙れ」 "+GetWorkTypeOfMan(npchar,"")+"……さもなくば、お前の舌を切り落として喉に突っ込んでやるぞ……","教えてやるよ、相棒。おとなしく座ってりゃ、まだ生き延びられるかもしれねえぜ…"));
				link.l1.go = "fight";
				break;
			}
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
    			dialog.text = "私の邸宅に敵がいる！警報だ！！！";
				link.l1 = "くそっ！";
				link.l1.go = "fight"; 
				break;
			}			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = TimeGreeting()+" 旦那。私は "+GetFullName(npchar)+"「ロスト・テケス鉱山の司令官であり、それは」 "+NationKingsName(npchar)+"。さて、いかがなさいましたか、ご用件をお聞かせいただけますか、 "+GetAddress_Form(NPChar)+".";
				link.l1 = "ここに来るのは初めてなので、この居留地やその法についてもっと知りたいのですが…";
				link.l1.go = "info";
				link.l2 = "ご挨拶だけしたくて参りましたが、もう失礼いたします。";
				link.l2.go = "exit";
				npchar.quest.meeting = "1";
				break;
			}
			dialog.text = "またお前か、旦那？他に何の用だ？";
			link.l1 = "たいしたことではありません。失礼いたします。";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "info":
			dialog.text = "そのような規律を尊敬いたします。さて、それほどご興味がおありなら、事情をお教えしましょう。\nロス・テケス鉱山はスペイン王室の所有物でございます。ここでは銀や金の鉱石、さらに銀塊や金塊も採掘しております。 すべての金銀はスペインのものとなり、旧大陸へ運ばれます。\n鉱山は厳重に警備されており、常にスペイン精鋭兵士の部隊が駐屯しております。 海賊どもが何度か鉱山を襲撃しようといたしましたが、結果は常に――彼らにとって――悲惨なものでした。\nご覧の通り、ここは小さな町でございます。酒場と店がございますので、 そこで金銀の延べ棒を良い値段でお買い求めいただけます。また、店の商人でもある物資係が、 他にも興味深い金属や鉱石を販売しております。\n労働者の大半は罪人でございますが、黒人奴隷も少数おります。ご覧の通り、常に新たな労働力が必要なのです――毎日、最低でも一人はこの忌々しい罪人が死にますので。\nですから、奴隷をお連れいただければ、金塊と交換いたします。その件は主任技師にご相談ください。 坑道内でお会いになれます。\nここではお行儀よくなさってください。決闘や喧嘩を起こしたり、何かを盗もうとしたり――特に金や銀を――してはなりません。ここには牢獄はありませんが、軍法会議はございます。\n以上が大体の説明です。この簡単な規則を守っていただければ、何の問題もございません。鉱山内は自由に移動できます。 酒場にもぜひお立ち寄りください――私の許可のもと、特別な…サービスもございます。ようこそお越しくださいました！";
			link.l1 = "感謝いたします！";			
			link.l1.go = "exit";
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = "強盗だと！！！それは許されぬ！覚悟なさい、 "+GetSexPhrase("相棒","少女")+"...";
			link.l1 = LinkRandPhrase("「くそっ！」","「カランバ！！」","くそっ！");
			link.l1.go = "PL_Q3_fight";
		break;
		
		case "fight":
            Pchar.quest.ArestInResidenceEnd.win_condition.l1          = "ExitFromLocation";
		    Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		    Pchar.quest.ArestInResidenceEnd.win_condition             = "ArestInResidenceEnd";
		    Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

			LAi_LockFightMode(Pchar, true); // ножками путь убегает
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		    LAi_group_Attack(NPChar, Pchar); // не работает на бессмертного мера :(
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;
	}
}
