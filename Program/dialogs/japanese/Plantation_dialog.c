// диалоги обитателей плантаций
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp, i, n;
	string sTemp;
	bool bOk;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "何かご用ですか？";
			link.l1 = "いや、知らねえ。";
			link.l1.go = "exit";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// рабы
		case "plantation_slave":
			dialog.text = RandPhraseSimple(RandPhraseSimple("もう疲れ果てて、今にも倒れそうだ……","こんな生活、もう続けられねえ！"),RandPhraseSimple("この仕事は俺を殺しそうだ。","衛兵どもは俺たち全員を殺したがってやがる！"));				
			link.l1 = RandPhraseSimple("なんて残念だ。","申し訳ない。");
			link.l1.go = "exit";				
		break;
		
		// рабы-пираты по пиратской линейке
		case "pirate_slave":
			dialog.text = RandPhraseSimple(RandPhraseSimple("聞け、どっか行け！","失せろ！"),RandPhraseSimple("何の用だ！？","ここからとっとと失せろ！"));				
			link.l1 = RandPhraseSimple("ふむ……","「さて……」");
			link.l1.go = "exit";				
		break;
		
		// охрана - солдаты
		case "plantation_soldier":
            dialog.text = RandPhraseSimple(RandPhraseSimple("「農園の責任者にでも迷惑かけてこい」","奴隷たちの邪魔をするなよ、相棒。"),RandPhraseSimple("俺の仕事はこいつら怠け者どもにやる気を出させることだ。","くそっ、今日もいつも通り暑すぎるぜ……"));
			link.l1 = RandPhraseSimple("なるほど……","確かに……");
			link.l1.go = "exit";
		break;
		
		// охрана - протектор
		case "plantation_protector":
            if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				if (sti(pchar.nation) == PIRATE)
				{
					PlaySound("Voice\English\soldier_arest_1.wav");
    				dialog.text = RandPhraseSimple("「海賊だと！？捕まえろ！」","奴は海賊だ！攻撃しろ！");
					link.l1 = RandPhraseSimple("海賊だ。それがどうした？","へっ、やれるもんならやってみろ。");
					link.l1.go = "fight"; 
					break;
				}
				PlaySound("Voice\English\soldier_arest_2.wav");
				dialog.text = RandPhraseSimple("ほうほう、お前さんは～の旗の下で航海してるんだな "+NationNameGenitive(sti(pchar.nation))+"！うちの司令官はあなたと話せて喜ぶと思うぜ！","ほうほう、匂うな "+NationNameAblative(sti(pchar.nation))+" ここだ！スパイだと！？お前には我々の司令官と話してもらう時だ。");
				link.l1 = RandPhraseSimple("まずは、お前を地獄に送ってやる！","俺の刃と語る時が来たぜ！");
				link.l1.go = "fight"; 
			}
			else
			{
				if (GetNationRelation(sti(NPChar.nation), GetBaseHeroNation()) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
					if (sti(pchar.nation) == PIRATE)
					{
						PlaySound("Voice\English\soldier_arest_1.wav");
						dialog.text = RandPhraseSimple("「海賊だと！？捕まえろ！」","奴は海賊だ！攻撃しろ！");
						link.l1 = RandPhraseSimple("海賊だと！？どこだ？","へっ、やれるもんならやってみろ。");
						link.l1.go = "fight"; 
						break;
					}
					PlaySound("Voice\English\soldier_arest_4.wav");
					dialog.text = RandPhraseSimple("お前は誰だ、ここで何の用だ？","止まれ！ここで何の用だ？");
					if (CheckNationLicence(HOLLAND))
					{
						link.l1 = "この場所の責任者に会って商談がしたい。取引許可証を持っている。";
						link.l1.go = "Licence";
					}
					else
					{
						link.l1 = "この場所の責任者に会って、商談をしたいんだ。";
						if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < (10+rand(50)+rand(50))) link.l1.go = "PegYou";
						else link.l1.go = "NotPegYou";
					}
					if (IsCharacterPerkOn(pchar, "Trustworthy"))
					{
						link.l2 = "（信頼できる）ご立派な旦那方、公正かつ互恵的な取引のために参りました。どうか、農園主にお目通り願えますか。";
						link.l2.go = "mtraxx_soldier_1";
						Notification_Perk(true, "Trustworthy");
					}
				}
				else
				{
					PlaySound("Voice\English\soldier_arest_4.wav");
					dialog.text = RandPhraseSimple("お前は何者だ、ここで何の用だ？","止まれ！ここで何の用だ？");
					link.l1 = "ここで責任者に会って、商談をしたい。";
					link.l1.go = "NotPegYou";
				}
			}
		break;
		
		case "Licence":
			iTemp = GetDaysContinueNationLicence(HOLLAND);
			if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -12)
			{
				PlaySound("Voice\English\soldier_arest_2.wav");
				dialog.text = "免許だと？ちょっと待てよ……ははっ、こりゃ笑えるぜ！お前が誰か知ってるんだ。お尋ね者じゃねえか、相棒！しかも首にかかった賞金はでかい！ 野郎ども、こいつを捕まえろ！";
				link.l1 = RandPhraseSimple("ならば俺の剣に会ってもらうしかねえな！","くたばれ。");
				link.l1.go = "fight";	
				break;
			}
			if (iTemp == -1)
			{
				PlaySound("Voice\English\soldier_arest_1.wav");
				dialog.text = "さてと……はっ！お前の免許は期限切れだ。ついて来い、司令官のところへ連れていくぞ……";
				link.l1 = RandPhraseSimple("くそっ！そろそろ俺の刃に会う時だな、相棒。","そうは思わねえな……");
				link.l1.go = "fight";	
				break;
			}
			dialog.text = "よし。中に入っていいぜ。おとなしくして、奴隷たちにちょっかい出すんじゃねえぞ。";
			link.l1 = "心配するな、友よ。";
			link.l1.go = "plantation_exit";
		break;
		
		case "PegYou":
			PlaySound("Voice\English\soldier_arest_2.wav");
            dialog.text = "「商売だと？ははっ！こりゃおかしいぜ！お前からは」 "+NationNameAblative(sti(GetBaseHeroNation()))+" 千里の彼方から来たんだ！そろそろ我々の司令官に会ってもらう時だ。";
			link.l1 = "いや、そろそろ俺の剣に会ってもらうぜ。";
			link.l1.go = "fight";
		break;
		
		case "NotPegYou":
            dialog.text = "よし。中に入っていいぜ。おとなしくして、奴隷たちにちょっかい出すんじゃねえぞ。";
			link.l1 = "心配するな、友よ。";
			link.l1.go = "plantation_exit";
		break;
		
		case "plantation_exit":
           DialogExit();
		   NextDiag.CurrentNode = "plantation_repeat";
		break;
		
		case "plantation_repeat":
            dialog.text = "さあ、進め！";
			link.l1 = "...";
			link.l1.go = "plantation_exit";
		break;
		
		// управляющий в Маракайбо // Addon 2016-1 Jason
		case "Plantator":
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "plant_2") // belamour legendary edition 
			{
				dialog.text = "「ここで何の用だ、旦那？」";
				link.l1 = TimeGreeting()+"、旦那。あなたに商談があるんだ。奴隷を売りたいんだ。 "+FindRussianQtyString(sti(GetSquadronGoods(pchar,GOOD_SLAVES)))+"。興味あるか？";
				link.l1.go = "mtraxx";
				break;
			}
            dialog.text = "「ここでの用件は何だ、旦那？」";
			link.l1 = "ちょっと歩いていただけだ、挨拶したくてな。";
			link.l1.go = "plantator_x";
		break;
		
		case "plantator_x":
           DialogExit();
		   npchar.dialog.currentnode = "plantator";
		break;
		
		case "plantator_1":
			bOk = GetSquadronGoods(pchar, GOOD_COFFEE) >= 500 || GetSquadronGoods(pchar, GOOD_CINNAMON) >= 500 || GetSquadronGoods(pchar, GOOD_COPRA) >= 500;
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup") && bOk) //пробуем выкупить Красавчика
			{
				dialog.text = "またお前か、旦那。元気にしてるか？";
				link.l1 = "あなたに商談を持ちかけたい。\nあなたは砂糖とカカオを生産しているな。\nあなたの商品を買いたいが、金ではなく、俺の持っている品と交換したいんだ。\n取引の話、どうだろう？";
				link.l1.go = "mtraxx_5";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "plant_6" && bOk)
			{
				dialog.text = "またお前か、旦那。調子はどうだ？";
				link.l1 = "あなたに商談を持ちかけたい。\nあなたは砂糖とカカオを生産しているな。\nあなたの商品を買いたいが、金ではなく、俺の持ち物と交換したいんだ。\n取引できるかもしれないな？";
				link.l1.go = "mtraxx_5";
				break;
			}
            dialog.text = "またお前か、旦那。元気にしてるか？";
			link.l1 = "ありがとう、俺は大丈夫だ。";
			link.l1.go = "plantator_1x";
		break;
		
		case "plantator_1x":
           DialogExit();
		   npchar.dialog.currentnode = "plantator_1";
		break;
		
		case "mtraxx":
			// belamour legendary edition возможность обмануть плантатора -->
			if(GetSquadronGoods(pchar, GOOD_SLAVES) >= 50 || CheckCharacterPerk(pchar, "Trustworthy") || ChangeCharacterHunterScore(Pchar, "spahunter", 0) <= -50)
			{
            dialog.text = "申し訳ないが、旦那、今は奴隷は必要としていないんだ。 エドゥアルド・デ・ロサダ船長が最近の襲撃で捕まえた海賊たちをすでに我々に提供してくれたからな。";
			link.l1 = "ここに海賊がいるのか？どうやってここで眠れるんだ？";
			link.l1.go = "mtraxx_1";
			}
			else
			{
				dialog.text = "ああ、では見せてもらおうか……お前の奴隷を買おう。ただな、どうもお前が自分で言っている人物とは思えんのだ。さあ、 私と一緒に司令官の執務室まで来てもらおう、旦那。もし私の思い違いなら、迷惑料はきっちり払うつもりだ。さて、 失礼する。\n衛兵！";
				link.l1 = RandPhraseSimple("夢でも見てろ、生きたまま捕まるもんか！\n俺の屍を越えてみろ！");
				link.l1.go = "mtraxx_fail";
			}
		break;
		
		case "mtraxx_fail":
            DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddQuestRecord("Roger_3", "27");
			sld = characterFromId("Mtr_plantation_boss");
			sld.lifeday = 0;
			Mtraxx_PlantPellyClear();
			Mtraxx_TerraxReset(3);
		break;
		// <-- legendary edition
		case "mtraxx_1":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(characterFromId("Fadey"));
            dialog.text = "我々には優秀な見張りがいるから、暴動の可能性は低いさ。\nだが、一つだけお前の言う通りだ――こいつらはひどい働き手だぜ。\n総督がロサダ旦那に敬意を示せって頼まれなきゃ、俺はこいつらなんか買わなかったさ。\nしかも、あいつも大して値をふっかけてこなかったしな。";
			link.l1 = "なるほど。ではロス・テケスへ航海しなければなりませんね……\n旦那、あなたのプランテーションを歩き回って見学してもよろしいですか？もしかしたら、 あなたの作物を買いたくなるかもしれません……";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "お前は商人か？";
			link.l1 = "ある意味では、そうだな。俺はプロの商人じゃねえが、うまい取引からは絶対に手を引かねえよ。";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "面白いな。よし、許可をやる。何か思いついたらまた来い。";
			link.l1 = "ありがとうございます、旦那。そうさせてもらうよ。";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
           DialogExit();
		   NextDiag.CurrentNode = "plantator_1";
		   pchar.questTemp.Mtraxx = "plant_3";
		   AddQuestRecord("Roger_3", "5");
		   Mtraxx_PlantSetMaxRocur();
		break;
		
		case "mtraxx_5":
            dialog.text = "なぜだ？どんな商品を出しているんだ？";
			if (GetSquadronGoods(pchar, GOOD_COFFEE) >= 500)
			{
				link.l1 = "コーヒー500箱。";
				link.l1.go = "mtraxx_coffee";
			}
			if (GetSquadronGoods(pchar, GOOD_CINNAMON) >= 500)
			{
				link.l2 = "バニラ500箱。";
				link.l2.go = "mtraxx_cinnamon";
			}
			if (GetSquadronGoods(pchar, GOOD_COPRA) >= 500)
			{
				link.l3 = "コプラ500箱。";
				link.l3.go = "mtraxx_copra";
			}
		break;
		
		case "mtraxx_coffee":
			i = hrand(3)+1;
			n = 5 - i;
			pchar.questTemp.Mtraxx.PlantGood.Cargo = 11;
			pchar.questTemp.Mtraxx.PlantGood.Sugar = i * 100;
			pchar.questTemp.Mtraxx.PlantGood.Cocoa = n * 100;
            dialog.text = "コーヒー五百箱だと？ほう、ほう……さてと……（数えている）君のコーヒーと交換する用意ができているのは "+sti(pchar.questTemp.Mtraxx.PlantGood.Sugar)+" 砂糖の袋と "+sti(pchar.questTemp.Mtraxx.PlantGood.Cocoa)+"  カカオの箱だ。取引するか？";
			link.l1 = "ふむ……もっといい条件を期待してたんだがな。まあ、どうでもいいさ。取引成立だ！";
			link.l1.go = "mtraxx_6";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup"))
			{
				link.l1 = "（信頼できる）尊敬する旦那、異議を唱えさせていただきます！私は最高品質の商品をお持ちしました。 私が差し上げる品も、あなたが差し出す品も、一つ一つの価値を熟知しております。 私はそちらからもう少し多くいただくに値しますし、それでもこの取引はあなたにとって十分利益となるはずです――それはよくご存知でしょう。";
				link.l1.go = "mtraxx_PlantVykup_2";
				Notification_Perk(true, "Trustworthy");
			}
		break;
		
		case "mtraxx_cinnamon":
			i = hrand(3)+1;
			n = 5 - i;
			pchar.questTemp.Mtraxx.PlantGood.Cargo = 19;
			pchar.questTemp.Mtraxx.PlantGood.Sugar = i * 106;
			pchar.questTemp.Mtraxx.PlantGood.Cocoa = n * 106;
            dialog.text = "バニラ五百箱だと？ほう、ほう……さてと……（数えている）お前のバニラと交換する準備ができているぞ "+sti(pchar.questTemp.Mtraxx.PlantGood.Sugar)+" 砂糖の袋と "+sti(pchar.questTemp.Mtraxx.PlantGood.Cocoa)+"  カカオの箱だ。取引するか？";
			link.l1 = "ふむ……もっといい条件を期待してたんだがな。まあ、どうでもいいさ。取引成立だ！";
			link.l1.go = "mtraxx_6";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup"))
			{
				link.l1 = "（信頼できる）尊敬する旦那、異議を唱えさせていただきます！私は最高品質の商品を持ってまいりました。 私が差し上げる品も、あなたがくださる品も、一つ一つの価値は熟知しております。私には、 そちらからもう少し多めの分け前をいただく資格がございますし、それでもこの取引はあなたにとって十分利益になる――そのことは、あなたもよくご存じでしょう。";
				link.l1.go = "mtraxx_PlantVykup_2";
				Notification_Perk(true, "Trustworthy");
			}
		break;
		
		case "mtraxx_copra":
			i = hrand(3)+1;
			n = 5 - i;
			pchar.questTemp.Mtraxx.PlantGood.Cargo = 20;
			pchar.questTemp.Mtraxx.PlantGood.Sugar = i * 100;
			pchar.questTemp.Mtraxx.PlantGood.Cocoa = n * 100;
            dialog.text = "コプラ五百箱だと？ほうほう……どれどれ……（数えている）お前のコプラと交換する用意ができているぞ "+sti(pchar.questTemp.Mtraxx.PlantGood.Sugar)+" 砂糖の袋と "+sti(pchar.questTemp.Mtraxx.PlantGood.Cocoa)+"  カカオの箱だ。取引するか？";
			link.l1 = "ふむ……もっといい条件を期待してたんだが……まあ、どうでもいいさ。取引成立だ！";
			link.l1.go = "mtraxx_6";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup"))
			{
				link.l1 = "（信頼できる）尊敬する旦那、異議を唱えさせていただきます！私は最高品質の商品をお持ちしました。 私が差し出す物も、あなたが差し出す物も、その一つ一つの価値を理解しております。私には、 少し多めの分け前をいただく資格がございますし、それでもなお、この取引はあなたにとって十分に利益となるはずです――そのことは、あなたもよくご存じでしょう。";
				link.l1.go = "mtraxx_PlantVykup_2";
				Notification_Perk(true, "Trustworthy");
			}
		break;
		
		case "mtraxx_6":
            dialog.text = "素晴らしい！これはお互いにとって利益のある取引だな！いつ交換を実行しようか？";
			link.l1 = "まずは俺が品物を用意しよう。あんたも同じだろう。取引は明日の夕方四時に始めよう。 俺の手下が日没前に箱を届けるぜ。";
			link.l1.go = "mtraxx_7";
		break;
		
		
		case "mtraxx_7":
            dialog.text = "取引成立だ。では、また明日会おう、旦那！";
			link.l1 = "またな……";
			link.l1.go = "mtraxx_8";
		break;
		
		case "mtraxx_8":
            DialogExit();
			NextDiag.CurrentNode = "plantator_1";
			AddQuestRecord("Roger_3", "10");
			pchar.questTemp.Mtraxx = "plant_7";
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			pchar.quest.mtraxx_plant_goods.win_condition.l1 = "ExitFromLocation";
			pchar.quest.mtraxx_plant_goods.win_condition.l1.location = pchar.location;
			pchar.quest.mtraxx_plant_goods.function = "Mtraxx_PlantFindRocurDay";
		break;
		
		case "mtraxx_9":
            dialog.text = "ここがそうだ、旦那。砂糖やカカオが必要な時は、いつでも私のところに来てくれ。いつでも大歓迎だ！";
			link.l1 = "この取引がうまくいけば、また会うことになるだろう。そろそろ行くぜ、旦那。";
			link.l1.go = "mtraxx_10";
		break;
		
		case "mtraxx_10":
            dialog.text = "さらばだ、旦那！";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantAfterTrading");
		break;
		
		case "mtraxx_soldier_1":
            dialog.text = "お前は商人には見えねえな、よそ者。許可証を見せろ。";
			link.l1 = "勘弁してくれよ！紙切れ一枚で人が商売できるかどうか決まるのか？高すぎるんだよ！ 俺は最近商売を始めたばかりだけど、もうすっかり夢中なんだ！通してくれたら、 あんたたち二人のことを店主にしっかり伝えておくからさ。";
			link.l1.go = "mtraxx_10";
		break;
		
		case "mtraxx_soldier_2":
            dialog.text = "お前は口がうまいな、ケチ野郎。よし、行けよ。だが、俺たちがあんたをボスに推薦したってこと、忘れずに伝えろよ。";
			link.l1 = "かしこまりました。ありがとうございます。";
			link.l1.go = "plantation_exit";
		break;
		
		case "mtraxx_PlantVykup_2":
            dialog.text = "お主は今の相場に詳しいな、船長！交渉の腕もなかなかだ、見た目は素人でもな。よし、お主の品が本当に一級品なら、 少し上乗せしてやろう。";
			link.l1 = "もちろん、一級品だ、誓うぜ！もう一つだけ、旦那。あんたから何か買いたいんだ。";
			link.l1.go = "mtraxx_PlantVykup_3";
		break;
		
		case "mtraxx_PlantVykup_3":
            dialog.text = "おや？それは何だ？";
			link.l1 = "誰か、人間だ。お前の奴隷の一人を私用の召使いとして買いたいんだが、可能か？";
			link.l1.go = "mtraxx_PlantVykup_4";
		break;
		
		case "mtraxx_PlantVykup_4":
            dialog.text = "問題ないぜ。あんたに合うやつを見つけてやるさ。";
			link.l1 = "私は特定の奴隷に興味があるんだ。あの愛嬌のある顔をしたやつ――公式な場に連れて行っても恥ずかしくないし、客にワインを注がせても様になる。 自分のことをジャン・ピカードと名乗っていたよ。もうすでに意気投合しているんだ。";
			link.l1.go = "mtraxx_PlantVykup_5";
		break;
		
		case "mtraxx_PlantVykup_5":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 70)
			{
				dialog.text = "ああ、ジャン・ピカードには需要があるよ――ワインを出すだけじゃない。すでに影響力のあるイギリス人が俺に連絡してきたんだ。名前は何だったか……パットーンソン？手紙を持ってきてくれたよ。";
				link.l1 = "「だが、パターンソンも依頼人もまだ現れていない。今ここでジャンをお前から買う用意ができてるぜ。値段を言え――ご婦人方が待ってるんだ！」";
				link.l1.go = "mtraxx_PlantVykup_10";
				Notification_Skill(true, 70, SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "ああ、気が合ったんだな。わかったよ。だが、残念ながら断らせてもらうぜ――ジャン・ピカールは売り物じゃねえんだ。すまねえな、旦那。";
				link.l1 = "おや？どうしてだ？たっぷり払うつもりだぜ。値を言ってみな。";
				link.l1.go = "mtraxx_PlantVykup_6";
				Notification_Skill(false, 70, SKILL_COMMERCE);
			}
		break;
		
		case "mtraxx_PlantVykup_6":
            dialog.text = "値段がつけられない品だ。すでに買い手がいる。別の者に約束してしまった。これ以上言うことはない。 最初の取引に戻って、商談を終わらせよう。";
			link.l1 = "ふむ、わかりました、旦那。";
			link.l1.go = "mtraxx_PlantVykup_7";
		break;
		
		case "mtraxx_PlantVykup_7":
            dialog.text = "素晴らしい！これはお互いにとって儲かる取引だな！いつ交換を実行するんだ？";
			link.l1 = "まずは俺が品物を用意しなきゃならねえ。\nあんたも同じだろう。\n取引は明日の夕方四時に始めよう。\n俺の手下が日没前に箱を届けるぜ。";
			link.l1.go = "mtraxx_PlantVykup_8";
		break;
		
		
		case "mtraxx_PlantVykup_8":
            dialog.text = "取引成立だ。さて、それじゃあ、また明日会おう、旦那！";
			link.l1 = "またな……";
			link.l1.go = "mtraxx_PlantVykup_9";
		break;
		
		case "mtraxx_PlantVykup_9":
            DialogExit();
			NextDiag.CurrentNode = "plantator_1";
			pchar.questTemp.mtraxx_PlantVykup2 = true;
			DeleteAttribute(pchar, "questTemp.mtraxx_PlantVykup");
			DoFunctionReloadToLocation("Shore37", "goto", "goto6", "Mtraxx_PlantPlantVykup_1");
		break;
		
		case "mtraxx_PlantVykup_10":
            dialog.text = "承知しました、旦那。しかし、分かってください、値段は高いですよ。五百ドゥブロンです。";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "それは問題ない――ほらよ。良い従者は、普通の奴隷よりも価値があるってことは、あんたもよく知ってるだろう。";
				link.l1.go = "mtraxx_PlantVykup_11";
			}
			else
			{
				link.l2 = "なかなかの値段をつけたな、旦那。しかし、この奴隷にはとても興味がある。ここで待っていろ。 もしパットーンソンが来たら、「ピカードはもう売れた」と伝えてやれ――ははは！";
				link.l2.go = "mtraxx_PlantVykup_13";
			}
		break;
		
		case "mtraxx_PlantVykup_11":
            dialog.text = "おっしゃる通りです。手配しておきます。ピカールが外であなたを待っています。";
			link.l1 = "...";
			link.l1.go = "mtraxx_PlantVykup_12";
			RemoveDublonsFromPCharTotal(500);
		break;
		
		case "mtraxx_PlantVykup_12":
            DialogExit();
			NextDiag.CurrentNode = "plantator_1";
			pchar.questTemp.mtraxx_PlantVykup3 = true;
			DeleteAttribute(pchar, "questTemp.mtraxx_PlantVykup");
			DoFunctionReloadToLocation("Maracaibo_ExitTown", "rld", "loc17", "Mtraxx_PlantPlantVykup_2");
		break;
		
		case "mtraxx_PlantVykup_13":
            dialog.text = "全額持って来るなら、俺が追い返す理由はねえだろう。だから急げよ、船長。";
			link.l1 = "すぐ戻るぜ。";
			link.l1.go = "mtraxx_PlantVykup_14";
		break;
		
		case "mtraxx_PlantVykup_14":
            DialogExit();
			NextDiag.CurrentNode = "mtraxx_PlantVykup_15";
			DeleteAttribute(pchar, "questTemp.mtraxx_PlantVykup");
		break;
		
		case "mtraxx_PlantVykup_15":
            dialog.text = "ジャン・ピカールのための金を持ってきたのか、船長？時間がないぞ。";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "そのことはよく分かっている。だから、ほら、金貨を受け取れ。そして俺の新しい召使いを渡せ。";
				link.l1.go = "mtraxx_PlantVykup_16";
			}
			else
			{
				link.l2 = "まだ集めてるところだ――そんな高い値をつけたのはあんただろう、旦那。";
				link.l2.go = "mtraxx_PlantVykup_14";
			}
		break;
		
		case "mtraxx_PlantVykup_16":
            dialog.text = "これほどまでに召使いを手に入れるために大金を使う人間は見たことがないよ。だが、その立派な身なりを見ると、 こういう豪勢な買い物には慣れているんだろうな。俺の部下たちに伝えておく、ピカールは出口で待っているぞ。";
			link.l1 = "...";
			link.l1.go = "mtraxx_PlantVykup_12";
			RemoveDublonsFromPCharTotal(500);
		break;
	}
} 
