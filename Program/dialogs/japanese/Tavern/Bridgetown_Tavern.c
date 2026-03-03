// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("何か質問があるか？","「どうなさいましたか、」 "+GetAddress_Form(NPChar)+"?"),"「さっき俺に質問しようとしたじゃねえか、」 "+GetAddress_Form(NPChar)+"...","もうこれで三度目だぞ、俺にちょっかい出すのは……","「まだ質問があるんだろう？」","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("気が変わったんだ……","今は話すことは何もねえぜ。"),"うーん、俺の記憶はどこに行っちまったんだ……","ああ、本当にこれで三度目だな……","いや、何の質問だって…",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит /за Англию/
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "酒をくれ。お前んとこの一番いいラムを注いでくれ。";
                link.l1.go = "TavernDone";
            }
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "toBarbados")
            {
                link.l1 = "聞けよ、カロウ・ガストンはどこにいるんだ？";
                link.l1.go = "Tonzag_Letter";
            }
			//Голландский гамбит /против всех/
			if (!CheckAttribute(npchar, "quest.HWICTake") && CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Self") && !CheckAttribute(pchar, "questTemp.HWIC.Eng") && !CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
                link.l1 = "何か仕事はないか？それとも、何か提案できることがあるか？";
                link.l1.go = "Tonzag_check";
            }
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "FernandoDie")
			{
                link.l1 = "仕事は終わったぜ。フェルナンド・ロドリゲスは死んだ。";
                link.l1.go = "Task_check";
            }
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
			{
				link.l1 = "聞いてくれ、この町に錬金術師が来てないか？医者だ。イタリア人で三十歳くらい、 名前はジーノ・グヴィネリっていうんだ。何か聞いてないか？";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//Голландский гамбит /за Англию/
		case "TavernDone":
			dialog.text = "ほら、酒だ。新しいお客さんには最高のラムを！\n何か特別な祝い事かい？それとも、ただ喉を潤しに来ただけか？";
			link.l1 = "ああ、特別な用事と言ってもいいだろうな。俺は奴隷をブルーウェルドまで運ぶんだ。最近、 新しいブリッグの船倉をこのために改造したばかりさ。さっきプランテーションに寄って監督と話したんだが、 奴は俺に上等な“黒い象牙”を注文してきた。だから、お前は自分の酒場で待っててくれ。ブルーウェルドに品物を届けたら、 またバルバドスで商売を続けるぜ、ヨーホー！";
			link.l1.go = "TavernDone_1";
		break;
		
		case "TavernDone_1":
			dialog.text = "本当かい？まあ、いい取引のために飲むのは恥じゃねえさ！で、バルバドスで商売するってのか？そりゃあいいな！船長、 乾杯だぜ！";
			link.l1 = "どうもありがとうよ、相棒。よし…どこか腰を下ろせる場所を探してくるぜ。";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-12");
			DelLandQuestMark(npchar);
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
				AddQuestRecord("Holl_Gambit", "2-6");
				pchar.questTemp.HWIC.Eng = "SeekVanBerg";
				pchar.quest.GotoBridgetownOver.over = "yes";//снять таймер
				DelMapQuestMarkCity("Bridgetown");
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
			}
		break;
		
		case "Tonzag_Letter":
			dialog.text = "ガストンはお前が「商人」を演じた二日後に町を出ていったぜ。ここでずいぶん派手にやってくれたな、はは！だが、 お前のごまかしはすぐにバレた。この町は狭いし、噂もすぐ広まるからな。それでガストンも早々 に姿を消したってわけさ。それ以来、誰もここで奴を見てねえ。ただし、お前宛てに手紙を残していったぞ。\nもしガストンが戻る前にお前がここに来たら、俺が直接渡せって頼まれてたんだ。実はな、 ガストンを探してるのはお前が初めてじゃねえ。細い目をしたでかい男と、 年寄りでスペイン人かポルトガル人っぽい奴も来た。はっきりとは言えねえが、あの顔は忘れられねえ……何か、すげえ不気味な奴だったぜ……";
			link.l1 = "その手紙を渡せ……ありがとな！";
			link.l1.go = "Tonzag_Letter_1";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Bridgetown");
		break;
		
		case "Tonzag_Letter_1":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-22");
			AddQuestRecordInfo("LetterFromGaston", "1");
			pchar.questTemp.HWIC.Eng = "toCuracao";
			LocatorReloadEnterDisable("SentJons_town", "houseSP3", true);//закрыть дом Флитвуда
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", true);//закрыть аптеку
			LocatorReloadEnterDisable("SentJons_town", "basement1_back", true);//закрыть подземелье
			pchar.quest.Knippel_Shore.win_condition.l1 = "location";
			pchar.quest.Knippel_Shore.win_condition.l1.location = "Shore24";
			pchar.quest.Knippel_Shore.function = "KnippelOnCuracao";
			AddMapQuestMarkShore("Shore24", true);
		break;
		
		//Голландский гамбит /против всех/
		case "Tonzag_check"://начинаем проверять нашего ГГ по всем статьям
			if(sti(pchar.reputation.nobility) > 48)//высокая репа
			{
				// belamour legendary edition покажем критерии
				Notification_Reputation(false, 48, "high");
				PlaySound("Voice\English\hambit\Ercule Tongzag-03.wav");
				dialog.text = "俺は悪党の世話にはならねえ。お前に頼める仕事は何もねえんだ。";
				link.l1 = "おいおい、言葉遣いに気をつけろよ、相棒！";
				link.l1.go = "exit";
				break;
			}
			bool bOk = GetSummonSkillFromName(pchar, SKILL_F_LIGHT) > 34 || GetSummonSkillFromName(pchar, SKILL_FENCING) > 34 || GetSummonSkillFromName(pchar, SKILL_F_HEAVY) > 34 || GetSummonSkillFromName(pchar, SKILL_PISTOL) > 34;
			if(!bOk)//слабое фехтование
			{
				// belamour legendary edition покажем критерии -->
				Notification_Skill(false, 35, SKILL_F_LIGHT);
				Notification_Skill(false, 35, SKILL_FENCING);
				Notification_Skill(false, 35, SKILL_F_HEAVY);
				Notification_Skill(false, 35, SKILL_PISTOL);
				// <--
				dialog.text = "船長、あんたは甘すぎるぜ。俺が欲しいのは、もう少し評判のいい戦士だ。 腰にぶら下げてるその剣の使い方を覚えたらまた来な。\nそれに、射撃の腕ももうちょいマシになった方がいいぜ。";
				link.l1 = "なるほどな。じゃあ、後でお前のところに寄らせてもらうぜ。";
				link.l1.go = "exit";
				break;
			}
			PlaySound("Voice\English\hambit\Ercule Tongzag-02.wav");
			dialog.text = "ふむ……ちゃんと時間通りに来たな。今すぐ片付けなきゃならねえ用事が一つあるんだ。うまくやれば、 顔の利く連中に紹介してやるぜ。さて、よく聞け、これからやるべきことを教える。";
			link.l1 = "聞かせてくれ。";
			link.l1.go = "Tonzag_task";
		break;
		
		case "Tonzag_task":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Bridgetown");
			pchar.questTemp.HWIC.Self.SpainCity = FindSpainCity();
			log_Testinfo(pchar.questTemp.HWIC.Self.SpainCity);
			dialog.text = "最近、セビリアから一人のイダルゴがやって来た。ヨーロッパでの決闘の厄介な後始末を避けるためらしいが、 復讐に限界はねえ。あるスペイン貴族の家がそのイダルゴの命を狙ってるんだ。どんな手を使ってもいい、 やつを始末してくれ。\n証拠として指輪付きの指を持ち帰れ。他にも死体から見つけた物は全部持ってこい。仕事を引き受ける覚悟はできてるか？ ";
			link.l1 = "支払いが良けりゃ、俺も乗るぜ。";
			link.l1.go = "Tonzag_task_1";
			link.l2 = "暗殺者として働く？そんなの絶対に嫌だぜ！";
			link.l2.go = "Tonzag_exit";
			npchar.quest.HWICTake = "true";
			pchar.questTemp.HWIC.CanTake.Self = "true";//признак, что против всех уже бралась
		break;
		
		case "Tonzag_exit":
			dialog.text = "だったら、とっとと失せろ。今話したことは全部忘れな。";
			link.l1 = "俺は行くぜ。";
			link.l1.go = "exit";	
			DeleteAttribute(pchar, "questTemp.HWIC.Self");//откат к двум другим вариантам
			pchar.questTemp.HWIC.Fail3 = "true";
			if(!CheckAttribute(pchar, "questTemp.HWIC.Fail1"))
			{
				AddMapQuestMarkCity("Villemstad", false);
				AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			}
			if(!CheckAttribute(pchar, "questTemp.HWIC.Fail2"))
			{
				AddMapQuestMarkCity("SentJons", false);
				AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
			}
		break;
		
		case "Tonzag_task_1":
			dialog.text = "報酬は3万エイト、悪くない金だ。その上、奴の死体から見つけた金貨は全部持っていっていい。さて、詳しい話をしよう。 名はドン・フェルナンド・ロドリゲス、35歳、背が高く浅黒い肌、軍人のような服装をしている。腕の立つ船乗りで剣術にも長けている\nどこにいるかは分からねえが、カリブのどこかにいることだけは確かだ\nスペインの街を片っ端から探して奴を見つけろ。猶予は二ヶ月だ。最後に一つだけ言っておく。 奴が持っている物は全部把握しているから、俺に隠そうなんて考えるなよ。質問はあるか？";
			link.l1 = "質問はねえ。もう行くぜ！";
			link.l1.go = "Tonzag_task_2";	
		break;
		
		case "Tonzag_task_2":
			DialogExit();
			pchar.questTemp.HWIC.Self = "start";
			SetFunctionTimerCondition("TargetFernandoOver", 0, 0, 60, false); //таймер
			//SetFunctionExitFromLocationCondition("CreateMapMarksTonzag", pchar.location, false);
			AddQuestRecord("Holl_Gambit", "3-1");
			ReOpenQuestHeader("Holl_Gambit"); // данила . чтобы вышел из архива																				  
			Log_TestInfo(""+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Self.SpainCity)+"");
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Lucas"));
			DelLandQuestMark(characterFromId("Knippel"));
			DelMapQuestMarkCity("Bridgetown");
			DelMapQuestMarkCity("Villemstad");
			DelMapQuestMarkCity("SentJons");
			AddMapQuestMarkCity(pchar.questTemp.HWIC.Self.SpainCity, true);
			AddLandQuestMark(characterFromId(pchar.questTemp.HWIC.Self.SpainCity+"_tavernkeeper"), "questmarkmain");
		break;
		
		case "Task_check":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("bridgetown");
			dialog.text = "指輪のついた指を持ってきたのか？見せてくれ。";
			if (CheckCharacterItem(pchar, "Finger"))
			{
				link.l1 = "ああ、もちろんだ。ほら、これだ。";
				link.l1.go = "Task_check_1";	
			}
			else
			{
				link.l1 = "いいや。フェルナンドは自分の船と一緒に海に沈んじまったし、指もフェルナンドと一緒に沈んだぜ。";
				link.l1.go = "Task_fail";	
			}
		break;
		
		case "Task_fail":
			dialog.text = "指輪をはめた指は契約の必須条件だったんだ。依頼人の死を証明するためのものさ。 ロドリゲスが沈没船から岸にたどり着いたかどうかなんて、誰にも分からねえだろ？確認したのか？してないな。つまり、 お前は任務を果たせなかったってことだ。だから俺たちの取り決めはこれで終わりだ。達者でな。";
			link.l1 = "だが、俺があいつを始末したんだ。もういねえ！くそっ……お前なんか……カリブには他にもやることが山ほどあるんだ。じゃあな。";
			link.l1.go = "exit";
			if(!CheckAttribute(pchar, "questTemp.HWIC.Fail1"))
			{
				AddMapQuestMarkCity("Villemstad", false);
				AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			}
			if(!CheckAttribute(pchar, "questTemp.HWIC.Fail2"))
			{
				AddMapQuestMarkCity("SentJons", false);
				AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
			}
			pchar.questTemp.HWIC.Fail3 = "true";
			AddQuestRecord("Holl_Gambit", "3-8");
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.Self");//зачищаем для возможности отката к голландскому варианту
		break;
		
		case "Task_check_1":
			RemoveItems(PChar, "Finger", 1);
			dialog.text = "素晴らしい！指は俺がもらっておくぜ。さて、あいつのポケットには何があるかな。お前が持ってきたものも見せてくれ。 ";
			link.l1 = "さあ、見ていきな。";
			link.l1.go = "Task_check_2";	
		break;
		
		case "Task_check_2":
			if (CheckCharacterItem(pchar, "jewelry7") && CheckCharacterItem(pchar, "totem_05") && CheckCharacterItem(pchar, "amulet_1"))
			{
				dialog.text = "ああ、それで十分だ。よくやったな！いい働きだったぜ。お前にはとても満足してるぞ。";
				link.l1 = "ありがとう！仕事をきちんとやったと褒められるのは、いつだって嬉しいもんだぜ。";
				link.l1.go = "Task_complete";	
			}
			else
			{
				dialog.text = "ふん…警告したはずだぜ、ロドリゲスが絶対に手放さない物を俺は知ってるんだ。だが、 ここには俺が必要としてる物が見当たらねえ。お前、あれをくすねたのか？それとも失くしたのか？どっちでもいいさ。 もうお前と関わる気はねえ。さっさと出て行け。";
				link.l1 = "「くそっ、てめえ……」";
				link.l1.go = "exit";
				pchar.questTemp.HWIC.Fail3 = "true";
				if(!CheckAttribute(pchar, "questTemp.HWIC.Fail1"))
				{
					AddMapQuestMarkCity("Villemstad", false);
					AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
				}
				if(!CheckAttribute(pchar, "questTemp.HWIC.Fail2"))
				{
					AddMapQuestMarkCity("SentJons", false);
					AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
				}
				AddQuestRecord("Holl_Gambit", "3-9");
				CloseQuestHeader("Holl_Gambit");
				DeleteAttribute(pchar, "questTemp.HWIC.Self");//зачищаем для возможности отката к голландскому варианту
			}
		break;
		
		case "Task_complete":
			RemoveItems(PChar, "jewelry7", 1);
			RemoveItems(PChar, "totem_05", 1);
			RemoveItems(PChar, "amulet_1", 1);
			AddMoneyToCharacter(pchar, 30000);
			dialog.text = "約束通り、これが報酬だ、三万だ。\nそれと、もう一つ追加で責任もリスクも高い仕事があるが、その分報酬も上がるぜ――四万ペソだ。";
			link.l1 = "聞いてるぜ。次の客は誰だ？";
			link.l1.go = "Fleetwood_house";	
		break;
		
		//2 задание
		case "Fleetwood_house":
			PlaySound("Voice\English\hambit\Ercule Tongzag-05.wav");
			dialog.text = "今回は、人間じゃなくて物を狩るんだ。アンティグアにあるリチャード・フリートウッドの家に忍び込んで、 彼の航海日誌を盗み出せ。奴はイギリスの船長だ。その家は厳重に警備されていて、 リチャード自身も滅多に家に戻らねえ\n計画は単純だ。十日後、セントジョンズの総督が私的な宴を開く。その席にフリートウッドも出席する。 お前は夜中の一時から三時の間に家へ忍び込め。中には兵士が一人だけいるはずだ\nそいつを始末しろ。リチャードの部屋の中を探して日誌を見つけろ。この鍵を持っていけ。";
			link.l1 = "ふむ……面白いな。やるべきことは分かったぜ。もう出発する準備はできてる！";
			link.l1.go = "Fleetwood_house_1";	
		break;
		
		case "Fleetwood_house_1":
			GiveItem2Character(pchar, "key3");
			dialog.text = "気をつけろ。俺が指定した日付より前に家に忍び込むんじゃねえぞ。\nさもないと、運が良くても追い出されるだけだし、最悪の場合はブタ箱行きだぜ。\nもう一度、日付と時間を俺に言ってみろ。";
			link.l1 = "ちょうど十日後、午前一時から三時の間だ。";
			link.l1.go = "Fleetwood_house_2";	
		break;
		
		case "Fleetwood_house_2":
			dialog.text = "よし、行っていいぜ。幸運を祈る！";
			link.l1 = "ありがとう、Gaston。";
			link.l1.go = "Fleetwood_house_3";
		break;
		
		case "Fleetwood_house_3":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-10");
			pchar.questTemp.HWIC.Self = "theft";
			DeleteAttribute(pchar, "questTemp.HWIC.CanTake");//иные варианты более невозможны
			LocatorReloadEnterDisable("SentJons_houseSP3", "reload2", true);//комнату закроем
			pchar.GenQuestBox.SentJons_houseSP3_room = true;
			pchar.GenQuestBox.SentJons_houseSP3_room.box1.items.FleetwoodJournal = 1;//положим в комод СЖ
			pchar.GenQuestBox.SentJons_houseSP3_room.box1.items.sand_clock = 1;//и песочные часы
			AddDialogExitQuestFunction("CreateFleetwoodSoldiers");//4 солдат в доме
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("FleetwoodJournalOver", 0, 0, 11, false);//таймер
			pchar.quest.Fleetwood_Journal.win_condition.l1 = "Timer";
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 9);
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 9);
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 9);
			pchar.quest.Fleetwood_Journal.win_condition.l2 = "Hour";
			pchar.quest.Fleetwood_Journal.win_condition.l2.start.hour = 0;
			pchar.quest.Fleetwood_Journal.win_condition.l2.finish.hour = 3;
			pchar.quest.Fleetwood_Journal.win_condition.l3 = "locator";
			pchar.quest.Fleetwood_Journal.win_condition.l3.location = "SentJons_town";
			pchar.quest.Fleetwood_Journal.win_condition.l3.locator_group = "reload";
			pchar.quest.Fleetwood_Journal.win_condition.l3.locator = "houseSP3";//доступно открывание двери
			pchar.quest.Fleetwood_Journal.function = "FleetwoodHouseEnter";
			pchar.quest.Fleetwood_Soldier.win_condition.l1 = "location";
			pchar.quest.Fleetwood_Soldier.win_condition.l1.location = "SentJons_houseSP3";
			pchar.quest.Fleetwood_Soldier.function = "Fleetwood_Soldier";//если надумает раньше заявиться
			AddMapQuestMarkCity("sentjons", true);
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("いいや、知らねえな。薬草師や医者はいるが、その名前の奴はいねえよ。","こんな奇妙な名前は初めて聞いたぜ。いや、あんたの言う男がここに来たことは一度もねえな。","錬金術師なんて全くいねえよ。医者ならいるが、そんな変な呼び名の奴はいねえな。");
			link.l1 = "なるほど。残念だな。引き続き探してみるぜ！";
			link.l1.go = "exit";
			npchar.quest.jino = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

string FindSpainCity()//Jason выбрать радномный испанский город - пусть побегает
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].nation == SPAIN && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].nation != "none")
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hrand(howStore-1)];
	return colonies[nation].id;
}
