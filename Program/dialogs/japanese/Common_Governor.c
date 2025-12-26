// boal 25/04/04 общий диалог Governor
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Governor\" + NationShortName(sti(NPChar.nation)) + "_Governor.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
    
    ref offref, sld;
    int i, cn;
    int qty;
    int iSumm;
    string attrLoc;

    /// выкуп колонии
    ref CaptGovenor, FortColony;
    int f, colony_money;

    int k = 1000;
    if (CheckAttribute(Nations[sti(NPChar.nation)], "Fort"))
    {
        k = (300 - sti(Nations[sti(NPChar.nation)].Fort)*10);
    }
	bool ok;
	
	attrLoc = Dialog.CurrentNode;
	if (findsubstr(attrLoc, "CityGive_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.quest.CityIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "ColonyGive";
 	}
 	
	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "First time":
            NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("総督府に顔を出すなんて、よくもまあそんな度胸があるな！？本当に正気じゃねえな……","「どうしてこの怠け者どもが敵に俺の屋敷へ侵入させちまったんだ？俺には理解できねえ……」","確かに、俺の護衛たちが役立たずなら、どこの浮浪者でもこの屋敷をうろつけるってことだな……"),LinkRandPhrase("何の用だ、 "+GetSexPhrase("這い寄る","くさい野郎")+"！？俺の兵士たちはすでにお前の後を追っているぞ、 "+GetSexPhrase("汚ねえ海賊","くさい野郎")+"!",""+GetSexPhrase("Filthy","Filthy")+" 殺人者め、今すぐ私の屋敷から出て行け！衛兵！","俺はお前なんか怖くねえぞ。 "+GetSexPhrase("悪党","悪党")+"！すぐに我々の砦で絞首刑にされるぞ、お前はもう逃げられねえ……"));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("兵士なんて役に立たねえ……","俺を捕まえることなんてできやしねえよ。"),RandPhraseSimple("黙れ、相棒、さもねえとその汚ねえ舌を引き抜いてやるぞ！","言っとくぜ、相棒。おとなしく座ってろ、さもねえと首を切り落として、 そのドアの向こうのお前の番犬どもに投げてやるぞ……"));
				link.l1.go = "fight";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "お前が面会をしつこく求めていたと聞いている。私の名は "+GetFullName(npchar)+"。私は植民地の総督です "+NationNameGenitive(sti(NPChar.nation))+"、王冠の代理人 "+NationKingsName(npchar)+" この海域で。さて、どうかご親切に教えていただけますか、ご訪問の目的は何でしょうか、 "+GetAddress_Form(NPChar)+".";
				link.l1 = "私の名前は "+GetFullName(pchar)+".";
				link.l1.go = "node_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = RandPhraseSimple("おや、またお前か？それで、総督から何の用だ？ "+NationNameGenitive(sti(NPChar.nation))+" 今回は？","「またしても、国家の重要な用事から私の気をそらすつもりですか？何の用ですか、」 "+GetAddress_Form(NPChar)+"?");
				link.l1 = "王冠の名の下で働くことについて話がしたい "+NationNameGenitive(sti(NPChar.nation));
				link.l1.go = "work";
				link.l2 = "大事な話があって、あんたに話さなきゃならねえ。";
				link.l2.go = "quests"; // файл нации
				//Jason --> Регата
				if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
				{
					link.l3 = "招待を受けてレガッタに参加しに来たんだ。これが俺の招待状だ。";
					link.l3.go = "Regata";
				}
				//<-- Регата
				link.l10 = "申し訳ないが、ちょっと用事があるんだ。";
				link.l10.go = "exit";
			}
		break;
		
		case "node_1":
			dialog.text = "「それで、何の用で私の国政の重要な仕事を邪魔しに来たのですか？」";
			link.l1 = "王冠の名の下で働くことについてあなたと話したかった "+NationNameGenitive(sti(NPChar.nation));
			link.l1.go = "work";
			link.l2 = "大事な話をしようと思っていたんだ。";
			link.l2.go = "quests";
			//Jason --> Регата
			if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
			{
				link.l3 = "私はレガッタに参加するためにここへ来た。これが私の招待状だ。";
				link.l3.go = "Regata";
			}
			//<-- Регата
			link.l10 = "ただの挨拶の訪問にすぎません、それ以上の意味はありません。 "+GetAddress_FormToNPC(NPChar);
			link.l10.go = "node_2";
		break;

		case "node_2":
			dialog.text = "その場合は、私の執務室から出ていただき、これ以上仕事の邪魔をしないでください。";
			link.l1 = "ああ、ああ、もちろんだ。邪魔して悪かったな。";
			link.l1.go = "exit";
		break;
		
		case "work":
            dialog.text = "もし仕事を探しているなら、植民地の総督たちに話しかけてみな。あいつらは賢くて勇敢な船長をよく必要としてるぜ。";
			link.l1 = "覚えておくぜ。ありがとう。";
			link.l1.go = "exit";
		break;
		
		//--> Jason регата
		case "Regata":
			dialog.text = "おお、素晴らしい、会えて嬉しいぞ、船長！ちょうどいい時に来てくれたな――数日後にレガッタが始まるところだ。使者が届けたはずの手紙でレガッタの規則を読んだか？";
			link.l1 = "はい、旦那、やりました。";
			link.l1.go = "Regata_1";
			RemoveItems(PChar, "letter_open", 1);//уберем письмо
			TakeNationLicence(HOLLAND);//уберем лицензию
			DeleteAttribute(pchar, "questTemp.Regata.ToPortRoyal"); // patch-5
		break;
		
		case "Regata_1":
			dialog.text = "「それで、五万ペソ――入場料は用意できたか？その金は賞金に充てられるんだぜ？」";
			if (makeint(Pchar.money) >= 50000)
			{
				link.l1 = "はい、もちろんです。どうぞ私の報酬をお受け取りください。";
				link.l1.go = "Regata_2";
			}
			link.l2 = "今は少し金が足りねえんだ。でも、できるだけ早く必ず持ってくるぜ。";
			link.l2.go = "Regata_nomoney";
		break;
		
		case "Regata_2":
			dialog.text = "よろしい。もし勝てば、賭け金は五倍になって返ってくるぞ。さて、レガッタの規則を破らない方法は知っておくべきだ。 \n詳細はヘンリー・スティーブンソンと相談してくれ。彼は邸宅の部屋にいるはずだ。会って話を聞けば、 すべて説明してくれるだろう。";
			link.l1 = "わかった。言われた通りにするぜ。";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -50000);
			pchar.quest.Regata_Guber.win_condition.l1 = "location";
			pchar.quest.Regata_Guber.win_condition.l1.location = "Portroyal_Roomtownhall";
			pchar.quest.Regata_Guber.function = "PrepareToRegataInPortroyal";
			pchar.questTemp.Regata.Begin = "true";
			NextDiag.TempNode = "First time";
		break;
		
		case "Regata_nomoney":
			dialog.text = "わかりましたが、あまり時間をかけないでくださいね、船長。レガッタがもうすぐ始まりますよ。";
			link.l1 = "なるほど。レガッタが始まる前にお金を持ってくるように努力します。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_1";
			pchar.questTemp.Regata.nomoney = "true";
		break;
		
		//регата-финал
		case "Regata_Final":
			dialog.text = "そしてここにレガッタの勝者がいる！こんにちは、船長 "+GetFullName(pchar)+"！この素晴らしい成功、本当におめでとうございます！レガッタの勝者はいつもイギリス植民地で人気者ですし、 それも当然ですね。";
			link.l1 = "ありがとうございます、旦那！";
			link.l1.go = "Regata_complete";
		break;
		
		case "Regata_complete":
			dialog.text = "さて、あなたにとって一番嬉しい部分に移ろう――授賞式だ。\n第一の賞は25万ペソだ。さあ、受け取ってくれ！";
			link.l1 = "ありがとう！";
			link.l1.go = "Regata_complete_1";
		break;
		
		case "Regata_complete_1":
			AddMoneyToCharacter(pchar, 250000);
			int iGift;
			string sItem1, sItem2, sItem3, sAdd;
			
			iGift = 3;
			switch (iGift)
			{
				case 0:
					sItem1 = "blade_10";//корд
					sItem2 = "cirass6";
					sItem3 = "bussol";
					sAdd = "cord, duelist's vest and boussole";
				break;
				
				case 1:
					sItem1 = "blade_15";//маринера
					sItem2 = "cirass2";//рейтарский панцирь
					sItem3 = "bussol";
					sAdd = "marinera, reiter's armour and boussole";
				break;
				
				case 2:
					sItem1 = "blade_17";//бретта
					sItem2 = "cirass7";//карацена
					sItem3 = "bussol";
					sAdd = "bretta, karacena and boussole";
				break;
				
				case 3://
					sItem1 = "blade_20";//мадонна
					sItem2 = "cirass2";//офицерская кираса
					sItem3 = "bussol";
					sAdd = "'Madonna', officer's cuirass and boussole";
				break;
			}
			GiveItem2Character(pchar, sItem1);
			GiveItem2Character(pchar, sItem2);
			GiveItem2Character(pchar, sItem3);
			dialog.text = "さらに、あなたには貴重な賞品のセットを受け取る資格があります： "+sAdd+"。さあ、あとは全部お前のものだ。";
			link.l1 = "とても嬉しいです、旦那！本当に、こんなことは思いもしませんでした。";
			link.l1.go = "Regata_complete_2";
		break;
		
		case "Regata_complete_2":
			dialog.text = "全てのイギリス植民地を代表して、レガッタへのご参加に感謝申し上げます。そして改めてご勝利おめでとうございます！ もし賭けをしていたなら、 まだ受け取っていなければ今こそヘンリー・スティーブンソン卿のところへ行って賞金を受け取る絶好の機会です。\nご武運をお祈りします、船長！";
			link.l1 = "ご親切なお言葉、ありがとうございます、旦那！\nそれに対し、このような盛大な催しに参加する機会を与えてくださったことにも感謝申し上げます。\nそれでは、これにて失礼させていただきます。";
			link.l1.go = "Regata_complete_3";
		break;
		
		case "Regata_complete_3":
			DialogExit();
			NextDiag.CurrentNode = "First time";
		break;
		//<-- регата
	}
}
