void ProcessDialogEvent()
{
	ref NPChar, sld, location;
	aref Link, NextDiag;
	string sTemp,sTemp1, str, str1;
	int	s1,s2,s3,s4,s5,p1, iColony, crewWhoreCost, charWhoreCost = 0;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
		
    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Brothel\" + NPChar.City + "_Brothel.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	crewWhoreCost = 50 + 7 * MOD_SKILL_ENEMY_RATE - hrand(40);
	charWhoreCost = 2460 + sti(pchar.rank) * 40;
	
	switch(Dialog.CurrentNode)
	{
		// ============= хозяйка борделя =============
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase(""+GetSexPhrase("何の娘たちだよ、旦那！？守備隊の半分がお前を追ってるってのに、真っ直ぐ娼館に来るとはな！","消え失せろよ、いいか？守備隊の半分がお前を追ってるぞ！")+"","今や町の衛兵全員がお前を探している。今この状況でお前にサービスなんか提供するほど俺は馬鹿じゃねえ……","ここに用はねえだろう！"),LinkRandPhrase(""+GetSexPhrase("俺の女たちに手を出してみろ、皮を剥いで生きたままにしてやるぞ！","消え失せろ、このクズ野郎！")+"","Dirty"+GetSexPhrase("","")+" 殺人者め、今すぐ俺の店から出ていけ！衛兵ども！！","俺はお前なんか怖くねえ、 "+GetSexPhrase("悪党","「ネズミ」")+"「もうすぐお前は俺たちの砦で絞首刑だ、逃げられねえぞ…」"));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("へっ、警報なんざ俺には何の問題もねえさ……","奴らに俺は絶対に捕まらねえ。"),RandPhraseSimple("黙れ、このババア。","面倒なことになりたくなけりゃ、黙ってろ……"));
				link.l1.go = "exit";
				break;
			}
			//--> Мерзкий Божок
			if (CheckAttribute(pchar, "questTemp.ChickenGod.HostessDialog")) {
				dialog.text = "ああ、なんてことだ！どうやってここに入ったんですか？親愛なる船長、お願いですからお引き取りください――お願いします！当店は現在閉店中です！";
				link.l1 = "会えて嬉しいよ、親愛なる人 "+npchar.name+"。私は招待客リストに載っていました。しかし、このような場所では招待客でも支払いが必要なので……あまり難しくしないでほしいですが、部屋代は払いたいのです。";
				link.l1.go = "chicken_god";
				
				DeleteAttribute(pchar, "questTemp.ChickenGod.HostessDialog");
				break;
			}
			//<-- Мерзкий Божок
			//--> туториал Мартиника
			if (CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") && pchar.questTemp.Sharlie.Gigolo == "start" && npchar.location == "FortFrance_SecBrRoom")
			{
				DelLandQuestMark(npchar);
				link.l1 = "聞いてくれ、オーロラ。今夜は女の子が必要なんだ。それに、その子を家に連れて帰りたい。手配できるか？";
                link.l1.go = "Gigolo";
				break;
			}
			//<-- туториал Мартиника
			//Jason --> Заносчивый аристократ
			if (!CheckAttribute(pchar, "GenQuest.Badboy") && !CheckAttribute(npchar, "quest.Badboy") && !CheckAttribute(pchar, "questTemp.ZA.Block") && makeint(environment.time) > 15.0 && makeint(environment.time) < 21.0 && sti(pchar.questTemp.HorseQty) > 4)
			{
				dialog.text = "あなたは本当に立派な方ですね。さらに、うちの娘たちもあなたのことがとても気に入っています。私の店のために、 ちょっとしたお願いをしたいのですが。";
				link.l5 = "お世辞を言われて光栄だぜ、間違いねえ。で、俺に何を手伝ってほしいんだ？";
				link.l5.go = "Badboy";
				link.l8 = "申し訳ないが、今は忙しいんだ。";
				link.l8.go = "exit";
				npchar.quest.Badboy = "true";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Badboy.Complete") || CheckAttribute(pchar, "GenQuest.Badboy.Continue"))
			{
				if (npchar.City == pchar.GenQuest.Badboy.Brothel.City)
				{
					dialog.text = "おお、戻ってきたか！あれの手配は済んだのか "+pchar.GenQuest.Badboy.Brothel.Name+" 「あたしの女たちを放っておいてくれないか？」";
					link.l5 = "ああ。もうここには二度と顔を出さないだろう。";
					link.l5.go = "Badboy_complete";
				break;
				}
			}
			// <-- Заносчивый аристократ
			
			//--> Jason Португалец
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector") || SandBoxMode)
			{
				bool bOk = (pchar.questTemp.HWIC.Detector == "holl_win") || (pchar.questTemp.HWIC.Detector == "eng_win") || (pchar.questTemp.HWIC.Detector == "self_win") || SandBoxMode;
				if (!CheckAttribute(pchar, "questTemp.Portugal") && bOk && !CheckAttribute(npchar, "quest.Portugal") && npchar.location == "Marigo_SecBrRoom" && makeint(environment.time) > 6.0 && makeint(environment.time) < 22.0 && sti(pchar.rank) >= 7)
				{
					DelMapQuestMarkCity("marigo");
					DelLandQuestMark(npchar);
					dialog.text = "船長、お願いをしてもよろしいでしょうか？";
					link.l5 = "奥様のためなら、何でもお望み通りに！私はあなたのお役に立ちますわ！";
					link.l5.go = "Portugal";
					link.l8 = "申し訳ないが、今は忙しいんだ。";
					link.l8.go = "exit";
					npchar.quest.Portugal = "true";
					DelLandQuestMark(npchar);
					break;
				}
			}
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "HostressMoney" && npchar.location == "Marigo_SecBrRoom")
			{
				DelLandQuestMark(npchar);
				dialog.text = "「ヒューゴと話しましたか、船長旦那？」";
				if (sti(pchar.money) >= 10000)
				{
					link.l1 = "さらに、奥様、こちらがお金です。すべてが最も好都合に進みました……";
					link.l1.go = "Portugal_3";
				}
				else
				{
					link.l1 = "はい、あなたのご要望は彼に伝えました。";
					link.l1.go = "Portugal_exit";
				}
				break;
			}
			//<--Португалец
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "brothel" && npchar.location == "Tortuga_SecBrRoom")
			{
				dialog.text = "おやまあ、見てごらんなさい！あの有名なコルセア、チャーリー・プリンスじゃないの！本物だわ！";
				link.l1 = RandSwear()+"やあ、ジャネット。俺はマーカス・タイレックスの任務でここに来た。";
				link.l1.go = "mtraxx_R";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "brothel_repeat" && npchar.location == "Tortuga_SecBrRoom")
			{
				dialog.text = "忘れられない回復の施術を受ける準備はできているかい、勇敢なコルセアよ？";
				if (sti(pchar.money) >= 31000)
				{
					link.l1 = "俺だよ！チャーリー・プリンスは金を浪費するほど言葉は無駄にしねえぜ、ははっ！";
					link.l1.go = "mtraxx_R2";
				}
				else
				{
					link.l1 = "もう少しで……たぶん、あんたの店で財布をなくしちまったみたいだ……金を持ってまた来るぜ！";
					link.l1.go = "exit";
				}
				break;
			}
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple(TimeGreeting()+"。愛の館へようこそ。私の名は "+npchar.name+"、そして俺が店主だ。 "+GetSexPhrase("「ご用件は何でしょうか、」 "+GetAddress_Form(NPChar)+"?","正直言って、ここであなたに会うとは少し驚いたよ。 "+GetAddress_Form(NPChar)+"、しかしご安心ください、当店は男性だけでなく女性にもサービスを提供しております。")+"",TimeGreeting()+"。歓迎するぞ、 "+GetSexPhrase("よそ者","お嬢さん")+"、私のささやかな店へようこそ。自己紹介させていただきます、私は "+NPChar.Name+" - 女のぬくもりを求める男たちのためのこの隠れ家の番人だ。 "+GetSexPhrase("ご用件は何でしょうか？","女の子にも多少は興味があるんだけどな……")+"");
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = RandPhraseSimple(TimeGreeting()+"。どうされましたか、 "+GetAddress_Form(NPChar)+"?",TimeGreeting()+"。ご用件は何でしょうか、 "+GetAddress_Form(NPChar)+"?");
			}
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Gigolo"))//не идёт квест девочки
			{
				if (!CheckAttribute(pchar, "GenQuest.BrothelLock"))// нет запрета от Мэри 280313
				{
					link.l2 = npchar.name+"、おたくの娘の一人とゆっくり楽しみたいんだ。";
					link.l2.go = "Hostess_1";
				}
			}
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock")) // не идёт старт Шарля
			{
				if (sti(pchar.ship.type) != SHIP_NOTUSED && GetCrewQuantity(pchar) > 0) // Rebbebion - а смысл, если нет как корабля, так и команды?
				{
					link.l3 = "しばらく部下たちを楽しませてやってなかったな。俺の船員のために女たちをまとめて注文できるか？";
					link.l3.go = "ForCrew";
				}
			}
			link.l4 = "質問がある。";
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakBrothelMadam"))
			{
				if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
				{
					link.l4.go = "ShipLetters_1";// генератор  "Найденные документы"
				}
				else
				{
					link.l4.go = "quests";
				}	
			}
			else
			{
				link.l4.go = "quests";//(перессылка в файл города)
			}	
			//-->> квест поиска кольца мэра
			if (pchar.questTemp.different == "TakeMayorsRing" && pchar.questTemp.different.TakeMayorsRing.city == npchar.city && GetNpcQuestPastDayWOInit(npchar, "TakeMayorsRing") > 7)
			{
				link.l5 = "「聞け、」 "+npchar.name+"、総督の指輪を探しているんだ。彼はあんたの宿に泊まっていて、たぶんここで失くしたんだろう。";
				link.l5.go = "TakeMayorsRing_H1";
				SaveCurrentNpcQuestDateParam(npchar, "TakeMayorsRing");
			}
			//<<-- квест поиска кольца мэра

			// belamour ночной приключенец -->
			if(CheckAttribute(pchar, "GenQuest.NightAdventureVar") && pchar.GenQuest.NightAdventureVar == "NightAdventure_NobleWhoreMoney")
			{
				link.l8 = "見ろよ、あんたのところで一番いい女をもらいたいんだ。";
				link.l8.go = "NA_Girl";
			}
			// <-- приключенец
			link.l9 = "気にするな、俺はもう出ていくところだ。";
			link.l9.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "ShipLetters_1":
				pchar.questTemp.different.GiveShipLetters.speakBrothelMadam = true;
				dialog.text = RandPhraseSimple("何の用だい、いい男？","お話を伺います、船長。");
				link.l1 = "「聞け、」 "+npchar.name+"…貴殿の施設の個室でこれらの書類を見つけたのですが…";
				link.l1.go = "ShipLetters_2";				
		break;
		
		case "ShipLetters_2":
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "見せてくれ！ふむ……どこかの船長が書類をなくしたんだろ？この件については港長に聞いてみるといいぜ。";
				link.l1 = "「たぶん、たぶん……」";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "見せてくれ！おお！名前から判断すると、これは私の大切なお得意様であり、この町の立派な市民のものだな。 これらの書類は私が直接お渡ししよう。";
				link.l1 = "たぶん違うな……";
				link.l1.go = "exit";
				link.l2 = "素晴らしい！良い人や立派な店にはいつでも喜んで力を貸すぜ。";
				link.l2.go = "ShipLetters_3";										
			}	
		break;
		
		case "ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "2");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters"); 
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "Hostess_1":
			if (!CheckAttribute(npchar, "quest.selected"))
			{
				if (CheckNPCQuestDate(npchar, "quest.date"))
				{
					dialog.text = ""+GetSexPhrase("お客様にご奉仕できていつも嬉しいですよ。さて、イケメンさん――もう誰かお決まりですか？それともあまり気にしないタイプですか？","そうだな、うちの娘たちは間違いなく……手伝えるぜ。もう誰か選んだのかい、それともあまり気にしないのか？")+"";
					Link.l1 = ""+GetSexPhrase("へっ、今すぐ女が欲しいんだ。誰でもいい、お前のところの女はみんな俺の目には良く見えるぜ…","もちろん、自分の務めをわきまえているなら誰でも構わんさ……")+"";
					Link.l1.go = "Hostess_NotChoice";	
					Link.l2 = "「ああ、一つあるぞ」 "+GetSexPhrase("俺の気を引いたやつで……","彼女が一番素敵な人だろうな……")+"";
					Link.l2.go = "Hostess_Choice";
				}
				else
				{
					dialog.text = "今日はお前に紹介できる娘はいないよ、もう客が多すぎて手一杯なんだ。\n明日また来な、絶対に後悔させねえぜ！";
					Link.l1 = "残念だ、やっと楽しみ始めたところだったのに。";
					Link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "ふむ。もうその娘の代金は支払われている。どうか、私の邪魔をしないでくれ。";
				Link.l1 = "よし、今行くぞ。";
				Link.l1.go = "exit";	
			}
		break;

        case "Hostess_NotChoice":
			sld = GetFreeHorseRef(npchar.city);
			location = &locations[FindLocation(npchar.city + "_Brothel")];
			if (sld.id == "none" || GetNpcQuestPastDayParam(location, "Brothel_date") > 98)
			{
				dialog.text = "今は空いている女はいないんだ、数日後にまた来てくれ。";
				Link.l1 = "「わかった、あなたの言う通りだ。」";
				Link.l1.go = "exit";	
			}
			else
			{
				// belamour legendary edition Орден Святого Людовика -->
				if(IsEquipTalisman9() && npchar.nation == FRANCE)
				{
					dialog.text = ""+GetSexPhrase("おう、野郎、それは最高だぜ！","全員腕利きだぜ、間違いねえ。")+"「」 「という名の美しい娘を紹介できる」 "+GetFullName(sld)+"、彼女はもう自由の身だよ。\nおや、そんなに控えめに隠してるのは何かな！？それはフランスの最高勲章じゃないか？ その印を持つ者は戦場だけでなく伝説的だって噂だぜ…まあ、言いたいことは分かるだろう、俺のフィリバスターよ…。それに、お前の“勲章”に触れるのは誰にとっても名誉なことさ。だから今夜はうちの店のおごりで休んでくれ。断りは受け付けないぜ、 美男さん。";
					Link.l1 = "もちろん同意するぜ、何の疑問があるってんだ！？";
					Link.l1.go = "Hostess_NotChoice_agree";	
					npchar.quest.choiceIdx = sld.index;
					break;
				}
				// <-- legendary edition
				dialog.text = ""+GetSexPhrase("よし、素晴らしいぞ、俺の暴れ馬！","奴らはみんな自分の仕事にとても長けている、疑う余地はねえぜ。")+" とても可愛い娘を紹介できるよ、名前は "+GetFullName(sld)+"、そして今なら彼女は利用可能だ。あの楽しみには料金がかかるぜ "+FindRussianMoneyString(sti(sld.quest.price)+charWhoreCost)+"。同意するか？";
				Link.l1 = "いいや。そうは思わないな。高すぎるんだ……";
				Link.l1.go = "exit";
				if (sti(pchar.money) >= (sti(sld.quest.price) + charWhoreCost))
				{
					Link.l2 = "もちろん、どうして断れるんだ！？";
					Link.l2.go = "Hostess_NotChoice_agree";	
					npchar.quest.choiceIdx = sld.index;
				}
				else
				{
					Link.l1 = "くそっ、そんな大金は今持ってねえんだよ……";
					Link.l1.go = "exit";
				}
			}
		break;
		
        case "Hostess_NotChoice_agree":
			sld = &characters[sti(npchar.quest.choiceIdx)];
			if (sti(pchar.money) >= (sti(sld.quest.price) + charWhoreCost))
			{
				dialog.text = "「いいだろう」 "+GetSexPhrase("「ハンサム」","美しい")+". "+sld.name+" 二階の個室でお待ちしております。";
				Link.l1 = ""+GetSexPhrase("わかった、行くぜ","わかった、行くぜ")+"...";
				Link.l1.go = "exit";
				// belamour legendary edition деньги только без ордена или адмиральского мундира
				if(IsEquipTalisman9())
				{
					if(npchar.nation != FRANCE) AddMoneyToCharacter(pchar, -(sti(sld.quest.price) + charWhoreCost));
				}
				else
				{
					AddMoneyToCharacter(pchar, -(sti(sld.quest.price) + charWhoreCost));
				}
				sld.dialog.currentnode = "Horse_ReadyFack";			
				//--> таймер на возврат, чтобы не вечно ждали
				str = npchar.city;
				pchar.quest.(str).win_condition.l1            = "Timer";
				pchar.quest.(str).win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
				pchar.quest.(str).win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
				pchar.quest.(str).win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
				pchar.quest.(str).win_condition               = "Brothel_checkVisitTime";	
				pchar.quest.(str).HorseId = sld.id;
				pchar.quest.(str).locator = sld.location.locator;
				//<-- таймер на возврат, чтобы не вечно ждали
				ChangeCharacterAddressGroup(sld, npchar.city + "_Brothel_room", "goto", "goto"+(rand(2)+1));
				LocatorReloadEnterDisable(npchar.city + "_Brothel", "reload2_back", false); //открываем комнату
				npchar.quest.selected = true; //флаг взял девку у хозяйки
				SetNPCQuestDate(npchar, "quest.date"); //дату взятия запишем
				for(int n=0; n<MAX_CHARACTERS; n++)
				{
					makeref(sld, Characters[n]);
					if (sld.location == npchar.city+"_Brothel" && CheckAttribute(sld, "CityType") && sld.CityType == "horse")
					{
						sld.dialog.currentnode = "Horse_4";
					}
				}
				
				// генератор найденных бумаг
				
				// belamour legendary edition не давать квесты губернатору и адмиралу
				bool MCGovernon = CheckAttribute(pchar, "questTemp.Patria.GenGovernor");
				bool MCAdmiral = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4;
				
				if ((rand(4) == 1) && (pchar.questTemp.different == "free") && (!CheckCharacterItem(pchar, "CaptainBook")) && GetNpcQuestPastDayWOInit(npchar, "questShipLetters") > 10 && !MCGovernon && !MCAdmiral ) 
				{					
					pchar.questTemp.different = "GiveShipLetters";
					pchar.questTemp.different.GiveShipLetters = "toBrothel";
					pchar.questTemp.different.GiveShipLetters.Id = GetFullName(npchar);
					pchar.questTemp.different.GiveShipLetters.city = npchar.city;	
					pchar.questTemp.different.GiveShipLetters.variant = rand(2);
					p1 = rand(20 - MOD_SKILL_ENEMY_RATE) + 1; // даем хотя бы один день
					s1 = rand(80 - pchar.rank - p1) * 50 + rand(100);
					s2 = s1 * 2;
					s3 = s1 * rand(GetCharacterSPECIAL(pchar, "Luck")) + s1;
					s4 = s2 + s3;
					s5 = s4 * GetCharacterSPECIAL(pchar, "Charisma");
					pchar.questTemp.different.GiveShipLetters.price1 = s1;
					pchar.questTemp.different.GiveShipLetters.price2 = s2;
					pchar.questTemp.different.GiveShipLetters.price3 = s3;
					pchar.questTemp.different.GiveShipLetters.price4 = s4;
					pchar.questTemp.different.GiveShipLetters.price5 = s5;
										
					sld = ItemsFromID("CaptainBook");
					sld.CityName = XI_ConvertString("Colony" + npchar.city + "Gen");
					//ложим бумаги в итем								
					sTemp = "_Brothel_room";	
					sTemp1 = "_town";					
					sld.shown = true;
					sld.startLocation = pchar.questTemp.different.GiveShipLetters.city + sTemp;
					sld.startLocator = "item" + (rand(4)+1);
					sld.endLocation = pchar.questTemp.different.GiveShipLetters.city + sTemp1;
					pchar.questTemp.different.GiveShipLetters.item = true; //флаг -  бумаги валяются в итемах
					Log_QuestInfo("The papers are in location " + sld.startLocation + ", in locator " + sld.startLocator + " p1 : " + p1);
					
					pchar.quest.CheckShipLetters.win_condition.l1 = "location";
					pchar.quest.CheckShipLetters.win_condition.l1.location = sld.endLocation;
					pchar.quest.CheckShipLetters.function = "CheckShipLetters";
					
					SetTimerFunction("GiveShipLetters_null", 0, 0, p1); //освобождаем разрешалку на миниквесты 
					SaveCurrentNpcQuestDateParam(npchar, "questShipLetters");					
				}
				// генератор - "Повод для спешки"
				if((rand(5) == 2) && !CheckAttribute(pchar, "questTemp.ReasonToFast") && GetNpcQuestPastDayWOInit(npchar, "questReasonToFast") > 20 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && !MCGovernon && !MCAdmiral) // Addon-2016 Jason
				{
					iColony = FindColony(npchar.city);	
					if( sti(Colonies[iColony].HeroOwn) == false && npchar.city != "Panama" && npchar.city != "Charles")
					{
						pchar.questTemp.ReasonToFast = "Begin";
						pchar.questTemp.ReasonToFast.city = npchar.city;
						sTemp1 = "_town";					
						pchar.quest.CheckReasonToFast.win_condition.l1 = "location";
						pchar.quest.CheckReasonToFast.win_condition.l1.location = npchar.city + sTemp1;
						pchar.quest.CheckReasonToFast.function = "ReasonToFast_CheckHorse";
						SaveCurrentNpcQuestDateParam(npchar, "questReasonToFast");	
					}	
				}				
			}
			else
			{
				dialog.text = "ああ、実は問題はね\n "+sld.name+" 安い女じゃねえ、あいつの値段は "+FindRussianMoneyString(sti(sld.quest.price)+charWhoreCost)+"。しかも、今はその船を買う余裕がないようだな。裕福になったらまた来てくれ"+GetSexPhrase("、親愛なる","")+"...";
				Link.l1 = "「これが俺の運か……」";
				Link.l1.go = "exit";
			}
		break;

        case "Hostess_Choice":
			dialog.text = "女の子とお客さんが親しくなるのを見ると、いつも嬉しくなるんですよ……彼女の名前を教えてください。";
			Link.l1.edit = 9;
			Link.l1 = "";
			Link.l1.go = "Hostess_Choice_1";	
		break;
		
        case "Hostess_Choice_1":
			sld = CheckHorsesName(npchar.city, 9);
			if (sld.id == "none")
			{
				dialog.text = "ふむ……お間違いではありませんか。うちの店にそんな娘はいませんよ。名前を勘違いされたのかもしれませんね。";
				Link.l1 = "ふむ……でも、さっき彼女と話したばかりだ。";
				Link.l1.go = "Hostess_Choice_2";				
				Link.l2 = "たぶんね。念のため、もう一度彼女の名前を聞いておいた方がいいだろう。\nこの件については後でまた話そう。";
				Link.l2.go = "exit";	
			}
			else
			{
				dialog.text = GetFullName(sld)+"、彼女のことを言ってるのか？";
				Link.l1 = "ああ、彼女のことだな。";
				Link.l1.go = "Hostess_NotChoice_agree";				
				Link.l2 = "いや、彼女じゃない。";
				Link.l2.go = "Hostess_Choice_2";
				npchar.quest.choiceIdx = sld.index;
			}
		break;
		
        case "Hostess_Choice_2":
			dialog.text = "それなら、もう一度その女の名前を言ってみろよ。もしかしたら誰のことか思い出すかもしれねえぜ。";
			Link.l1.edit = 9;
			Link.l1 = "";
			Link.l1.go = "Hostess_Choice_1";
			Link.l2 = "もしかしたらな。念のためにもう一度彼女の名前を聞いたほうがいいだろう。\nこの件については後でまた話そう。";
			Link.l2.go = "exit";	
		break;
		//==> команда
		case "ForCrew":
			dialog.text = "ふむ……部下たちに“羽目を外させたい”ってことかい？うちの店は評判のいい店でね、最高の女の子たちが揃ってるよ。でも、港の女たちも何人か知ってるし、 あんたの船乗りたちを喜ばせてくれるさ。それには金がかかるけどね\n "+FindRussianMoneyString(GetCrewQuantity(pchar)*crewWhoreCost)+".";			
			link.l1 = "よし、同意するぜ。";
			link.l1.go = "ForCrew_1";
			link.l2 = "まあ、あいつらならなくても何とかなるだろう…";
			link.l2.go = "exit";
		break;
		
		case "ForCrew_1":
		    if (sti(Pchar.money) >= GetCrewQuantity(pchar)*crewWhoreCost && GetCrewQuantity(pchar)>0)
		    {
		        AddMoneyToCharacter(Pchar, -makeint(GetCrewQuantity(pchar)*crewWhoreCost));
	            AddCrewMorale(Pchar, 10);
				ChangeCharacterComplexReputation(pchar,"authority", 1);
	            LAi_Fade("", "");
                AddTimeToCurrent(5 + rand(1), rand(30));
			    DialogExit();
		    }
		    else
		    {
		        dialog.text = "俺の知ったことじゃねえが、まずは乗組員を雇うだけの金を稼いでから、その士気を気にしたほうがいいと思うぜ。";
			    link.l1 = "たぶん君の言う通りだな……";
			    link.l1.go = "exit";
		    }
		break;
		
		case "Woman_FackYou":
			dialog.text = "あなた、いったい何をしているの！？立派な船長に見えたのに……。今度は逃がさないわよ、いい男。衛兵たちがあなたの羽をもいでやるんだから……";
			link.l1 = "黙れ、ババア。";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		
		//поиски кольца губернатора
		case "TakeMayorsRing_H1":
			dialog.text = "指輪は見つかっていない。";
			link.l1 = "「それで、お前の女たちは？」";
			link.l1.go = "TakeMayorsRing_H2";
		break;
		
		case "TakeMayorsRing_H2":
			dialog.text = "あちらも何も見つけていません。もしお客が何かを忘れたり落としたりしたら、 うちの娘たちが私のところに持ってくるんです。\nでも、誰も総督の指輪は持ってきていませんよ。";
			link.l1 = "なるほど……しかし、もしかして奴らは自分たちのものにしようと決めたんじゃねえか？";
			link.l1.go = "TakeMayorsRing_H3";
		break;
		
		case "TakeMayorsRing_H3":
			dialog.text = "ありえねえな。女たちは客からもらった贈り物を持ってていいが、それだけだ。";
			link.l1 = "なるほど。まあ、ありがとう。 "+npchar.name+".";
			link.l1.go = "exit";
		break;
		
		case "Hostess_inSexRoom":
			dialog.text = "「ああ、そこにいたのか……」";
			link.l1 = "「ここにおります、奥方様！」";
			link.l1.go = "exit";
			pchar.quest.SexWithHostess_null.over = "yes"; //нулим таймер на не пришёл
			NextDiag.TempNode = "First time";
			if (CheckAttribute(pchar, "questTemp.RomNaTroih_Pogovoril"))
			{
				sld = CharacterFromID(pchar.RomNaTroih_Shluha);
				dialog.text = ""+sld.name+"！私の英雄、下の階で時間を無駄にしなかったのね！";
				link.l1 = "この弱さをお許しいただけますか、女王様？";
				link.l1.go = "RomNaTroih_2";
			}
			AddDialogExitQuestFunction("SexWithHostess_fack");
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			DeleteAttribute(pchar, "questTemp.RomNaTroih");
            if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	
			{
				AddCharacterHealth(pchar, 10);
				AddCharacterMaxHealth(pchar, 1.0);
			}
			else AddCharacterHealth(pchar, 5);
		break;
		
		// ================================== рядовой состав =======================================
        case "Horse_talk":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("ここから出ていったほうがいいぜ！","町中の衛兵があんたを探してるぞ！早く出て行ったほうがいい…","お前が散々やらかしておいて、今さらここに現れやがったのか！？いや、今回はそうはいかねえ……"),LinkRandPhrase("失せろ！","汚い殺人者め、ここから出て行け！衛兵！","「俺はお前なんか怖くねえ」"+GetSexPhrase("悪党","「ネズミ」")+"！すぐに我々の砦で絞首刑にされるぞ、お前はもう逃げられねえ…"));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("へっ、警報なんざ俺には何の問題もねえさ……","奴らに俺は絶対捕まらねえ。"),RandPhraseSimple("へっ、なんて間抜けな女だよ……","黙れ、売女、さもねえと別のもので黙らせてやるぞ……"));
				link.l1.go = "exit";
				break;
			}
			dialog.text = NPCStringReactionRepeat("「こんにちは」 "+GetAddress_Form(NPChar)+""+GetSexPhrase("","、へへっ…")+"。旦那様に会って、注文書を記入する必要がある。","またお前か？管理人と話してくれ。彼女は自分の事務所にいるぞ。","「見ろ、」 "+GetAddress_Form(NPChar)+""+GetSexPhrase("……他のことでも、話す時と同じくらい頑固だといいんだが……またか","再び")+" 店の主人に会っていただきたい。","「ああ、」 "+GetAddress_Form(NPChar)+""+GetSexPhrase("、お前は本当に頑固だな！","、へへ……お前は頑固な奴だな？")+" 旦那、セニョーラに会って注文書を記入する必要があるぜ。","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("「よし、」 "+GetSexPhrase("「美人」 ","")+"わかった"+GetSexPhrase("","")+".","「ああ、そうかよ……」",""+GetSexPhrase("疑うなよ、お嬢ちゃん、俺は雄牛みたいに頑固で強いんだぜ！","ああ、ああ……")+"",""+GetSexPhrase("くそっ、何か見落としたみたいだ……すまないよ、あんた。","わかった、いいだろう。")+"",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			Link.l2 = "「それで、彼女はどこにいる？」";
			Link.l2.go = "Horse_1";
			Link.l3 = LinkRandPhrase(""+GetSexPhrase("ああ、美しい人よ、その瞳に溺れてしまいそうだ……","とても綺麗だよ、愛しい人！")+"",""+GetSexPhrase("なあ、こんな美しい女に会ったのは初めてだぜ！","あんた、こんな素敵なご婦人に会ったのは初めてだぜ！")+"",""+GetSexPhrase("あなた、とても美しいわ。","くそっ、あの田舎者どもにはうんざりしてたんだよ……それにあんたは本当に魅力的だな！")+"");
			if (!CheckAttribute(npchar, "quest.choice"))
			{
				Link.l3.go = "Horse_2";
			}
			else
			{
				Link.l3.go = "HorseChoice_" + npchar.quest.choice;
			}
			//-->> квест поиска кольца мэра
			if (pchar.questTemp.different == "TakeMayorsRing" && pchar.questTemp.different.TakeMayorsRing.city == npchar.city && GetNpcQuestPastDayWOInit(npchar, "TakeMayorsRing") > 7)
			{
				link.l5 = LinkRandPhrase("「聞け、」 "+GetSexPhrase("美しさ","おチビちゃん")+"、ここで結婚指輪を見かけませんでしたか？誰かが失くしたようなんです…","ねえ、あなた、このあたりで結婚指輪とかそういうものを見かけなかった？","「聞け、」 "+GetSexPhrase("私の子猫","ベイビー")+"ここらで結婚指輪を見なかったか？");
				link.l5.go = "TakeMayorsRing_S1";
				SaveCurrentNpcQuestDateParam(npchar, "TakeMayorsRing");
			}
			//<<-- квест поиска кольца мэра
			
			// Addon 2016-1 Jason пиратская линейка
			if (pchar.location == "santodomingo_brothel" && CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_1" && npchar.id == "HorseGen_"+reload_location_index+"_2")
			{
				link.l6 = "やあ、お嬢ちゃん。マーカス・タイレックスに頼まれて来たんだ、この琥珀のネックレスを見てくれよ……";
				link.l6.go = "mtraxx";
			}
			NextDiag.TempNode = "Horse_talk";
		break;
		
        case "Horse_1":
			dialog.text = "彼女は自分の執務室にいるよ。ここからなら通りへの出口の反対側にある扉を通って行けるし、 家の反対側の通りからも入れる。名前は\n "+characters[GetCharacterIndex(npchar.city+"_Hostess")].name+".";
			Link.l1 = "なるほど。 "+GetSexPhrase("恋人","「あなた」")+"、ありがとうございます。";
			Link.l1.go = "exit";			
		break;
		
        case "Horse_2":
			if (rand(1))
			{
				dialog.text = LinkRandPhrase("まあまあ、そんなことを言ってもらえて嬉しいわ！ねえ、今は暇してるから、あたしを選んだら絶対に後悔させないよ…","本当にそう思うの？なんだか嬉しいわ……ねえ、今は暇だから、あたしを選んでもいいのよ。"+GetSexPhrase(" 愛の海と抱擁の大洋を約束するよ……","")+"",""+GetSexPhrase("そう思いますか？あら、本当に光栄ですわ。こんなお褒めの言葉、滅多にいただきませんのよ……","ああ、お嬢ちゃん……田舎者にはもううんざりなんだよ……")+" おい、聞いてくれ、今は暇だから、あんたを満足させる相手にあたしを選んでいいよ。絶対にがっかりさせないから、 約束するよ…");
				if (CheckAttribute(pchar, "questTemp.RomNaTroih") && !CheckAttribute(pchar, "questTemp.RomNaTroih_Pogovoril"))
				{
					link.l1 = "お嬢様、それこそまさに私がしようとしていたことですわ！なんて幸運なのでしょう、 あなたのご主人様がすでに私との個室での面会を上の階で手配してくださったのですもの。ご一緒なさいます？";
					Link.l1.go = "RomNaTroih_1";
					pchar.questTemp.RomNaTroih_Pogovoril = true;
					break;
				}
				link.l1 = "じゃあ、お前を選ぶぜ！";
				Link.l1.go = "Horse_3";		
				Link.l2 = ""+GetSexPhrase("いや、それはただ素敵な女性へのお世辞さ。","それはただのお世辞だ")+".";
				Link.l2.go = "exit";
				npchar.quest.choice = 0; //был базар, но ГГ потом отказался
			}
			else
			{
				dialog.text = LinkRandPhrase(""+GetSexPhrase("あたしが言いたいこと、わかる？安っぽいおしゃべりはいらないよ。取引するか、出ていきな！","それだけで十分だぜ！女からの褒め言葉なんてな！")+"",""+GetSexPhrase("あんた、女は耳で恋をするとでも思ってるのかい？残念だけど、それは違うよ、旦那。あたしが欲しいなら、 マダムに金を払いな。くだらない口説き文句はやめておくれ。","嬢ちゃん、くだらねえ話で時間を無駄にするな。本気なら、金を払え…")+"",""+GetSexPhrase("あら、また快楽好きが来たのね……お金さえ払えば、あたしはあんたのものよ。余計な優しさなんていらない、ただそれだけよ！","どうしたの、あなた？快楽にふけりたいなら、お金を払って、くだらないことはやめてちょうだい！")+"");
				link.l1 = "おお、すごい握力だな！";
				Link.l1.go = "exit";
				npchar.quest.choice = 2; //ГГ послали
			}
		break;
		
        case "Horse_3":
			dialog.text = characters[GetCharacterIndex(npchar.city+"_Hostess")].name+" 彼女の執務室ですべての手続きを完了する。彼女に会いに行け"+GetSexPhrase("、私の英雄よ、","")+" そして俺の名前を言え—— "+npchar.name+"……待っているぞ……";
			Link.l1 = "なるほど、あなた、すぐ戻るわ……";
			Link.l1.go = "exit";
			npchar.quest.choice = 1; //она согласная
			SetNPCQuestDate(npchar, "quest.choice");
		break;
		
        case "Horse_4": 
			dialog.text = NPCStringReactionRepeat("あなたはすでに支払い済みだ。","上の階に行けと言っただろう。","二階だよ、若者。","「考えが遅い奴もいるんだよな……」","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("ああ、知ってるぜ。","覚えている。","「ああ、繰り返さなくていい、覚えてる。」","ふむ、どういう意味だ？",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "Horse_4";
		break;
		
		//===>> реакция на попытки пофлиртовыть, если флирт уже был
        case "HorseChoice_0": 
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				dialog.text = NPCStringReactionRepeat("どうもお前の言ってることがよくわからねえんだ。"+GetSexPhrase(" 最初はお世辞を言っておいて、すぐに約束を破るなんて。なんとも変わった奴だな……","")+"","またお世辞か？","管理人は自分の事務所にいるよ。わかったか？","お客様を侮辱しちゃいけない決まりだが、あんたは本当に言われても仕方ねえな"+GetSexPhrase("","")+"...","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("そうなっちまっただけさ……","わかった、そうするよ。","ああ、わかったぜ。","「すまないね、愛しい人。」",npchar,Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "褒めてくれてありがとう。もしあたしを買いたいなら、奥さんのところに行ってきな。いつも通りの商売さ。";
				Link.l1 = "なるほど。";
				Link.l1.go = "exit";
			}
		break;
		
        case "HorseChoice_1": 
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				if (!CheckNPCQuestDate(npchar, "quest.choice"))
				{
					dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("「あなた、もう全部話し合ったでしょ。」 ","")+"あまり長く待たせるなよ……",""+GetSexPhrase("ふむ……聞いておくれ、あんた、俺は","I")+" あんたの言葉はなかなかいいが、そろそろ本題に入ってくれないか…","もしかして、このことはマダムと話し合うつもりじゃないか？","うーん……何と言えばいいのかわからねえな……","block",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("俺がそんなことするわけねえだろ、待ってろよ！","「もちろんだ！」","もちろん、おっしゃる通りです！","俺はもうあんたの奥方に会いに走ってるところだ…",npchar,Dialog.CurrentNode);
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "お前を待ってたのに、迎えに来てくれなかったじゃねえか……それは気に入らねえな……";
					Link.l1 = "見ての通り、そうなっちまったんだよ……";
					Link.l1.go = "exit";
					npchar.quest.choice = 0; //был базар, но ГГ потом отказался
				}
			}
			else
			{
				dialog.text = "「ああ、またお前か、俺の」 "+GetSexPhrase("栄光あるコルセア","可愛い娘")+"！また俺に会いたきゃ、マダムのところに来な。後悔はさせねえぜ……"+GetSexPhrase(" ところで、あなたのことは分かっていましたよ、旦那。でも、すべてのお客様を平等に扱うように言われているんです。 ひいきはできませんので、ご了承ください……","")+"";
				Link.l1 = "心配しないで、ダーリン。もう少しだけ待っててね。 "+GetSexPhrase("かわい子ちゃん","かわい子ちゃん")+"、そしてすぐにまた二人きりで会えるだろう。";
				Link.l1.go = "exit";
				Link.l2 = "私のことを覚えていてくれるなんて、とても嬉しいけど、今夜は一緒に過ごせないんだ、ごめんね。";
				Link.l2.go = "HorseChoice_1_Add";
			}
		break;
		
        case "HorseChoice_2": 
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				dialog.text = NPCStringReactionRepeat("それで、"+GetSexPhrase(" 親愛なる友よ、","")+" 何か商売でもしていたほうがいいぜ。何もしないよりは役に立つからな。",""+GetSexPhrase("ふむ、なぜお前は ","なぜお前は")+" 同じことを何度も繰り返して言ってるのか？","おい、もう十分じゃねえか！？","ふむ、驚いたな、何も新しいことはない"+GetSexPhrase("「またしても、そのくだらない色仕掛けかい！あたしと寝たいなら、マダムのところにでも行きな、間抜け！」","...")+"","ブロック",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("ああ、聞いたぜ"+GetSexPhrase("","")+" お前……","ふむ、そういうことになるのか……","ふむ、もう十分かもしれねえし、まだ足りねえかもしれねえな……","言葉に気をつけろ"+GetSexPhrase("、ヤギ","")+"...",npchar,Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "「ああ、またお前か！」 "+GetSexPhrase("そしてまた、あのくだらない褒め言葉ばかりだ。この世は何も変わらねえ……もし ","念のために言っておくが、もし ")+"やりたい"+GetSexPhrase("楽しんでくれ","楽しんでくれ")+" 俺に言うな、店の主人に払え。お前の言葉なんざどうでもいいぜ。";
				Link.l1 = "それは別に驚くことじゃねえな……";
				Link.l1.go = "exit";
			}
		break;
		
        case "HorseChoice_1_Add":
			dialog.text = "嬉しかったとは言えねえな……残念だぜ。";
			Link.l1 = "申し訳ない……";
			Link.l1.go = "exit";
			npchar.quest.choice = 0;
		break;
		
		//===>> секс
        case "Horse_ReadyFack":
			// Addon 2016-1 Jason пиратская линейка
			if (pchar.location == "SantoDomingo_Brothel_room" && CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_2" && npchar.name == "Gabriela")
			{
				dialog.text = "ああ、やっと来たか！素晴らしい！これで自由に話せる、誰にも聞かれていないぞ…";
				Link.l1 = "そうか、青い琥珀を渡したのはあのスペイン人だったのか？";
				Link.l1.go = "mtraxx_2";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("SantoDomingo");
				break;
			}
			if (!CheckAttribute(npchar, "quest.choice")) npchar.quest.choice = 0;
			switch(npchar.quest.choice)
			{
				case "0":
					dialog.text = RandPhraseSimple("お会いできて本当に嬉しいです。 "+GetSexPhrase("それで、次はどうするんだ？","俺たちで楽しもうじゃねえか？")+"","遠慮するな"+GetSexPhrase("、少なくとも二時間はくつろいでいってくれ。","。お前さんを楽しませてやるぜ、心配はいらねえ。")+"");
					Link.l1 = RandPhraseSimple("退屈にはならないと思うぜ……",""+GetSexPhrase("楽しもうぜ、ベイビー！","時間を無駄にするな！")+"");
				break;
				case "1":
					dialog.text = "「ああ、またお前か、俺の」 "+GetSexPhrase("栄光あるコルセアよ！約束したものがある、今こそその言葉を守る時だ","可愛いお嬢ちゃん！これからの二時間は絶対に忘れられねえぜ")+"...";
					Link.l1 = "そいつはそそられる話だな……";	
				break;
				case "2":
					dialog.text = "おお、やっと来たな。時間を無駄にせず行こうぜ！";
					Link.l1 = ""+GetSexPhrase("やめておこうぜ、腰抜け……","さあ、お前の腕前を見せてみろ……")+"";
				break;
			}
			if (pchar.sex == "woman")
			{
				Link.l1.go = "exit";
				NextDiag.TempNode = "Horse_AfterSex";
				AddDialogExitQuest("PlaySex_1");
				// кач от борделя
				if (CheckNPCQuestDate(pchar, "BrothelSex"))
				{
					if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	AddCharacterHealth(pchar, 10);
					else 												AddCharacterHealth(pchar, 5);
					SetNPCQuestDate(pchar, "BrothelSex");
				}
				// изменение статусов
				ChangeCharacterComplexReputation(pchar,"nobility", -1);
				AddCharacterExpToSkill(pchar, "Leadership", 30);
				AddCharacterExpToSkill(pchar, "FencingS", -15);
				AddCharacterExpToSkill(pchar, "Pistol", -15);
			}
			else
			{
				pchar.horsekiss = npchar.id;
				Link.l1.go = "Horse_Kiss";
			}
			//--> кол-во посещений
			if (!CheckAttribute(npchar, "quest.sexHappend")) npchar.quest.sexHappend = 1;
			else npchar.quest.sexHappend = sti(npchar.quest.sexHappend) + 1;
			pchar.GenQuest.BrothelCount = sti(pchar.GenQuest.BrothelCount) + 1; // для Данек
			Achievment_SetStat(23, 1);
			//<-- кол-во посещений
			str = npchar.city;
			pchar.quest.(str).win_condition.l1 = "ExitFromLocation";
			pchar.quest.(str).win_condition.l1.location = pchar.location;
			pchar.quest.(str).win_condition = "Brothel_checkVisitTime";
			pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1; //счетчик
		break;
		
		case "Horse_Kiss":
			DialogExit();
			
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("Horse_Kiss", "");
		break;

        case "Horse_AfterSex":
			if (CheckAttribute(pchar, "questTemp.ReasonToFast") && pchar.questTemp.ReasonToFast == "Begin")
			{
				dialog.text = "船長、どうしてそんなに黙っているんだ？";
				link.l1 = LinkRandPhrase("「まあ、それが俺だ。」","次回また話そう。",RandPhraseSimple("喋るために金を払ってるわけじゃねえ。","しかし、お前は "+GetSexPhrase("美しさ","おチビちゃん")+"、その間ずっと静かだったわけじゃないんだ。"));
				link.l1.go = "exit";
				link.l2 = ""+GetSexPhrase("君は本当に素晴らしかった、俺はもう正気を失いかけたぜ！こんなに美しくて魅力的な女に出会えるなんて、 滅多にないことだ。","あら、あなたって本当に女を喜ばせるのが上手ね……とてもドキドキしちゃうわ。")+".";
				link.l2.go = "Horse_ReasonToFast_1";
			}
			else
			{
				switch(npchar.quest.choice)
				{
					case "0":
						dialog.text = LinkRandPhrase("気に入ったか？","それで、どう思う？全部うまくいったか？","「それで、」"+GetSexPhrase(" コルセア、すべてだ"," すべて")+" 「いいのか？」");
						Link.l1 = RandPhraseSimple(""+GetSexPhrase("もちろん、すべて順調だ","お前は自分の務めをよく分かってるじゃねえか")+".",""+GetSexPhrase("「大丈夫よ、ダーリン」","知ってるか、俺はけっこう満足してたんだぜ")+".");
						Link.l1.go = "exit";
					break;
					case "1":
						dialog.text = LinkRandPhrase("それで、俺は約束を守ったか？","「それで、」"+GetSexPhrase(" 俺のこと、気に入ったか？","、気に入ったか")+"?","「願わくは、」 "+GetSexPhrase("「あなたが喜んでくれて、俺はすっごく嬉しいぜ」","俺が全力を尽くしたから、あんたは満足してくれたんだ")+"...");
						Link.l1 = RandPhraseSimple("ああ、すごく気に入ったぜ。",""+GetSexPhrase("素晴らしい時間を過ごせたよ、君は本当に見事だった！","全てが本当に最高だったぜ！")+"");	
						Link.l1.go = "exit";
					break;
					
					case "2":
						dialog.text = RandPhraseSimple("さて、これで終わりだ、行かなくちゃならねえ。","「お前の時代は終わった」"+GetSexPhrase(" 「船長、」","")+".");
						Link.l1 = RandPhraseSimple("ああ、またな……","さようなら、そしてありがとう……");
						Link.l1.go = "exit";
					break;
				}
				NextDiag.TempNode = "Horse_AfterSex_2";
			}	
		break;
		
        case "Horse_AfterSex_2":
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "Bag_BrothelRoom" && !CheckCharacterItem(pchar, "leather_bag"))
			{
				dialog.text = "それで、ここはどうだった？";
				link.l1 = "教えてくれ、美人さん、この辺りでグリップサックを見なかったか？";
				link.l1.go = "EncGirl_GetBag";
			}
			else
			{
				dialog.text = LinkRandPhrase("またいつでも寄ってくれよ…","さようなら。いつでもお待ちしていますよ…","またここでお会いできるのを楽しみにしています…");
				Link.l1 = "「よし……」";
				Link.l1.go = "exit";
				NextDiag.TempNode = "Horse_AfterSex_2";
			}	
		break;
		
		case "EncGirl_GetBag":
			dialog.text = "取っ手付きのあの茶色い箱のことか？";
			link.l1 = "ああ、そんな感じだな……";
			link.l1.go = "EncGirl_GetBag1";	
		break;
		
		case "EncGirl_GetBag1":
			dialog.text = "あの箱の持ち主が現れないので、奥様が自分の私室に持っていかれました。";
			link.l1 = "ありがとう、ダーリン。じゃあな。";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "Bag_BrothelHostess";
			NextDiag.TempNode = "Horse_AfterSex_2";
		break;
		
		// --> генератор - "A reason to hurry"
		case "Horse_ReasonToFast_1":
			dialog.text = "いつでも寄ってくれ、会えるのはいつだって嬉しいぜ。お前は本当に\n "+GetSexPhrase("他の連中とは違って、穏やかだ","優しい、あの荒くれ者たちとは違う")+" 挨拶もなく、別れの言葉もなく、しかもよく傷つけようとするんだ…";
			link.l1 = "それはどういう意味だ？";
			link.l1.go = "Horse_ReasonToFast_2";
		break;
		
		case "Horse_ReasonToFast_2":
			pchar.questTemp.ReasonToFast.speakHorse = true;
			dialog.text = "あんたの前に軍曹殿が来てたんだ。普段は俺たちのところになんて来やしねえのに、 今回は悪魔にでも連れてこられたんだろうな。しかも、俺を選びやがって……しばらく俺の上でぶつぶつ文句を言って、それから「腕が悪い」って罵って、どっかの入り江に飛び出して行ったぜ。 あまりに慌ててて、ズボンを下ろしたまま忘れそうになってたんだ、ははは……";
			link.l1 = "「知らねえのか、 "+GetSexPhrase("美しさ","「あなた」")+"「男って本当に何者なんだろうな？妻には『検査』だと言って売春宿に行き、 愛人には妻のもとへ急いで帰ると言いながら、結局本当に望んでいたのはあの入り江の見回りだけだったんだ。」 "+GetSexPhrase("ははは……","「ハハハ！」")+"";
			link.l1.go = "Horse_ReasonToFast_3";
		break;
		
		case "Horse_ReasonToFast_3":
			NextDiag.TempNode = "Horse_AfterSex_2";			
			ReOpenQuestHeader("ReasonToFast");
			AddQuestRecord("ReasonToFast", "1");
			pchar.questTemp.ReasonToFast = "SpeakHorse";
			pchar.questTemp.ReasonToFast.GuardNation = npchar.nation;
			pchar.questTemp.ReasonToFast.cantSpeakOther = true;
			ReasonToFast_InitVariables();
			string TargetLocation = SelectQuestShoreLocation();
			if(TargetLocation != "")
			{ 
				Locations[FindLocation(TargetLocation)].DisableEncounters = true;
				LAi_LocationDisableOfficersGen(TargetLocation, true);
				pchar.quest.ReasonToFast_MeetPatrol.win_condition.l1 = "location";
				pchar.quest.ReasonToFast_MeetPatrol.win_condition.l1.location = TargetLocation;
				pchar.quest.ReasonToFast_MeetPatrol.function = "ReasonToFast_MeetPatrolShore";
				pchar.questTemp.ReasonToFast.PatrolLocation = TargetLocation;
			}	
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		// <-- генератор "A reason to hurry"
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//поиски кольца мэра
		case "TakeMayorsRing_S1":
			if (CheckAttribute(pchar, "questTemp.different.TakeMayorsRing.item")) //если валяется в итемах
			{
				dialog.text = LinkRandPhrase("いいえ、坊や、ごめんね、でも無理よ。喜んで助けたいけど、できないの。","「いいや」 "+GetSexPhrase("「イケメン」","お嬢さん")+"……指輪なんて見てないぞ……","悪いが、見てないな。指輪なんて見てないぜ。");
				link.l1 = "残念だな……まあ、とにかくありがとう。";
				link.l1.go = "exit";
			}
			else
			{
				if (npchar.id == "HorseGen_"+reload_location_index+"_1")
				{
					dialog.text = "総督の指輪のことか？";
					link.l1 = "まさにその通りよ、ダーリン！";
					link.l1.go = "TakeMayorsRing_S2";
				}
				else
				{
					dialog.text = LinkRandPhrase("いいえ、あなた、ごめんなさい、でも無理よ。喜んで手伝いたいけど――できないの。","いいや "+GetSexPhrase("ハンサム","お嬢さん")+"……指輪なんて見てないぞ……","悪いが、いいや。指輪なんて見てないぜ。");
					link.l1 = "残念だな……まあ、とにかくありがとう。";
					link.l1.go = "exit";
				}
			}
		break;

		case "TakeMayorsRing_S2":
			dialog.text = "申し訳ないが、その指輪は贈り物としてもらったものだから、返す義務はないんだ。";
			link.l1 = "「贈り物だと！？それをくれたのは誰だ？」";
			link.l1.go = "TakeMayorsRing_S3";
		break;
		
		case "TakeMayorsRing_S3":
			dialog.text = "もちろん、総督ご本人さ！";
			link.l1 = "しかし彼は……少なくとも酔っ払っていたんだ。何も覚えていないらしい。";
			link.l1.go = "TakeMayorsRing_S4";
		break;
		
		case "TakeMayorsRing_S4":
			dialog.text = "「それが俺に何の関係があるんだ？あいつが酔っぱらってたなら、それはあいつ自身の問題で、俺のせいじゃねえ！」";
			link.l1 = "本当に彼と喧嘩する必要があるのか？これは結婚指輪だし、分かってるだろう……返してやれよ、こんな小さな物のために揉める価値なんてないさ。";
			link.l1.go = "TakeMayorsRing_S5";
		break;
		
		case "TakeMayorsRing_S5":
			if (rand(1) && sti(pchar.money)>5000)
			{
				dialog.text = "よし、指輪は返してやるが、五千ペソ払ってもらうぜ。";
				link.l1 = "わかった、金を渡すから指輪をよこせ。";
				link.l1.go = "TakeMayorsRing_S6";
			}
			else
			{
				dialog.text = "ああ、まあいいさ。あいつにやらせておけ！";
				link.l1 = "間違いないぜ、ダーリン！";
				link.l1.go = "exit";
				GiveItem2Character(pchar, "MayorsRing");
				pchar.questTemp.different.TakeMayorsRing = "HorseTakenRing";
				AddQuestRecord("SeekMayorsRing", "3");
				AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
				AddQuestUserData("SeekMayorsRing", "sName", GetFullName(npchar));
			}
		break;
		
		case "TakeMayorsRing_S6":
			dialog.text = "「さあ、どうぞ…」";
			link.l1 = "わかったよ。手伝ってくれてありがとな、ダーリン。";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -5000);
			GiveItem2Character(pchar, "MayorsRing");
			pchar.questTemp.different.TakeMayorsRing = "HorseTakenRingMoney";
			AddQuestRecord("SeekMayorsRing", "2");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("SeekMayorsRing", "sName", GetFullName(npchar));
		break;
		
		//Jason --> Заносчивый аристократ
		case "Badboy":
			pchar.GenQuest.Badboy.Brothel.City = npchar.city; //город квестодателя
			//log_info(pchar.GenQuest.Badboy.Brothel.City); // patch-6
			pchar.GenQuest.Badboy.Brothel.nation = npchar.nation;
			pchar.GenQuest.Badboy.Brothel.Name = GenerateRandomName_Generator(sti(npchar.nation), "man");
			dialog.text = "実はな、うちには厄介な客が一人いてな― "+pchar.GenQuest.Badboy.Brothel.Name+"。それに、あいつが来るたびに本当に迷惑してるんだ！まず酒場で酔っ払ってからここに来て、 女の子を引っかけて大騒ぎを起こすんだよ\n一番厄介なのは、あいつが貴族の出だってことさ！総督の遠縁らしくて、俺たちはあいつの無茶を我慢するしかないんだ。 あんた、あの生意気な若造を……まあ……少し大人しくさせてくれないか？もう俺の店に来なくなるようにさ。";
			link.l1 = "総督の親類だって？ふむ……役人と揉め事はごめんだぜ。本当にすまねえ。";
			link.l1.go = "exit";
			link.l2 = "それは手配できると思うぜ。で、そいつの居場所を教えてくれないか？";
			link.l2.go = "Badboy_1";
		break;
		
		case "Badboy_1":
			dialog.text = "この時間になると、たいていもう酒場にいるよ。そこで酔っ払ってから、こっちに顔を出すんだ。";
			link.l1 = "なるほど。まあ、たぶんそこで彼に会うことになるだろう。";
			link.l1.go = "exit";
			//создаем дебошира
			int iRank, iType, b;
			string sBlade, sPistol;
			if (sti(pchar.rank) < 6) iType = 0;
			if (sti(pchar.rank) >= 6 && sti(pchar.rank) < 16) iType = 1;
			if (sti(pchar.rank) >= 16) iType = 2;
			switch (iType)
			{
				case 0:
					iRank = 6;
					sBlade = "blade_12";
					sPistol = "pistol1";
					b = 25;
				break;
				case 1:
					iRank = sti(pchar.rank)+10;
					sBlade = "blade_09";
					sPistol = "pistol1";
					b = 65;
				break;
				case 2:
					iRank = sti(pchar.rank)+5;
					sBlade = "blade_14";
					sPistol = "pistol1";
					b = 40;
				break;
			}
			sld = GetCharacter(NPC_GenerateCharacter("Badboy", "citiz_"+(7+rand(1)), "man", "man", iRank, HOLLAND, -1, true, "citizen"));
			FantomMakeCoolFighter(sld, iRank, b, b, sBlade, sPistol, "bullet", makeint(iRank*5));
			sld.name = pchar.GenQuest.Badboy.Brothel.Name;
			sld.lastname = "";
			sld.dialog.FileName = "Quest\Other_quests_NPC.c";
			sld.dialog.currentnode = "Badboy";
			sld.greeting = "noble_male"; // patch-6
			LAi_SetLoginTime(sld, 15, 22);
			LAi_SetSitType(sld);
			FreeSitLocator(pchar.GenQuest.Badboy.Brothel.City + "_tavern", "sit1");
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "sit", "sit1");
			pchar.GenQuest.Badboy.Brothel.Type = iType; //запомним тип
			pchar.GenQuest.Badboy.Brothel = "true";
		break;
		
		case "Badboy_complete":
			dialog.text = "おお、あんたは本当に男だな。俺は最初からあんたを頼りにできるって分かってたぜ。";
			link.l1 = "こんな素敵なご婦人とその…お世話している方々のお力になれるのは、いつでも嬉しいですわ。";
			link.l1.go = "Badboy_complete_1";
		break;
		
		case "Badboy_complete_1":
			dialog.text = "あなたは勇敢なだけでなく、とても紳士的ね。特別なお礼をしたいの――女にしかできないお礼よ。これを一生忘れられないはず。約束するわ。さあ、上の部屋へいらして、勇敢な水夫さん…";
			link.l1 = "...";
			link.l1.go = "Badboy_complete_2";
		break;
		
		case "Badboy_complete_2":
			pchar.questTemp.different.HostessSex.city = pchar.GenQuest.Badboy.Brothel.City;
			AddDialogExitQuestFunction("SexWithHostess_goToRoom");
			SetTimerFunction("SexWithHostess_null", 0, 0, 1); 
			DialogExit();
			if (sti(pchar.GenQuest.Badboy.Brothel.Type) != 2)
			{
				DeleteAttribute(pchar, "GenQuest.Badboy");
			}
			else
			{
				pchar.quest.Badboy_Brothel.win_condition.l1 = "location";
				pchar.quest.Badboy_Brothel.win_condition.l1.location = pchar.GenQuest.Badboy.Brothel.City +"_town";
				pchar.quest.Badboy_Brothel.function = "Badboy_friends";
				DeleteAttribute(pchar, "GenQuest.Badboy.Continue"); // patch-6
			}
			SaveCurrentQuestDateParam("questTemp.Badboy");
			if (!CheckAttribute(pchar, "questTemp.RomNaTroih"))
			{
				pchar.questTemp.RomNaTroih = true;
			}
		break;
		// <-- Заносчивый аристократ
		
		//Португалец
		case "Portugal":
			dialog.text = "俺に金を借りてる男がいるんだが……どう言えばいいか……";
			link.l1 = "言葉はいらねえ！あいつを見つけて、最後の一ペソまで絞り取ってやるぜ、お前の底知れぬ瞳を一目見るためにな！ 名前を教えてくれよ！";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "いやいや、違いますよ、船長！この男には……悪いことはしないでください。ただ借金を思い出させてやってください。名前はユーゴ・アヴェンデルで、 たぶん一番安い酒が売られているところにいるでしょう。お願いです、決して力ずくで何かしないでください！\nただ……支払うと約束したことを思い出させてやってください。衛兵を巻き込みたくはありませんが、 私は士官の中に友人もいますので、私が待っていると、彼に最大限の敬意を払いつつも、 明日までには行動せざるを得なくなると伝えてください。ただ約束を思い出させてやってください。";
			link.l1 = "お言葉は私の法です、奥様。喜んでご要望をお聞きいたします。";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			DialogExit();
			sld = InitHugo("Hugo","Avendell");
			FreeSitLocator("Marigo_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, "Marigo_tavern", "sit", "sit_front1");
			AddLandQuestMark(sld, "questmarkmain");
			SetFunctionTimerCondition("Portugal_BeginOver", 0, 0, 2, false);
			pchar.questTemp.Portugal = "begin";
		break;
		
		case "Portugal_exit":
			dialog.text = "ありがとうございます、船長。彼が十分な慎重さを示してくれることを願っています。";
			link.l1 = "それは確かです、奥様。では、これにて失礼いたします。";
			link.l1.go = "exit";
			sld = characterFromId("Avendel");
			sld.lifeday = 0;
			pchar.questTemp.Portugal = "end";
		break;
		
		case "Portugal_3":
			AddMoneyToCharacter(pchar, -10000);
			dialog.text = "ああ、いやだ！まさか、あの人にひどいことをしたんじゃないだろうな……彼にはお金なんてなかったし、それは私も知ってた！私たちは同じ小さな町で育ったんだ、 警備兵なんかに頼るつもりはなかった！ただ、ちょっと怖がらせて、酒に溺れる前に目を覚まさせたかっただけなんだ……";
			link.l1 = "ふむ……まあ、とにかく、これが約束の金だ。ヒューゴのことは心配するな、あいつは無事だ……少なくとも酔いが覚めればな。";
			link.l1.go = "Portugal_4";
		break;
		
		case "Portugal_4":
			dialog.text = "ああ、船長、あなたは分かっていないんだ！あいつはその……ほら、賞金稼ぎって呼ばれてる連中の一人だったんだ――傭兵で、海賊や盗賊を追い詰めて始末する奴らさ。でも、まあ、はっきり言って運のいい方じゃなかったんだよ\nつい最近、ついに無理して散財して、仲間も船も失っちまった。それからは毎日、酒の底に沈んでるんだ。昔のよしみで、 たまにここに来るのを許してるんだよ。今じゃ……本当に哀れなもんさ。昔はラ・マンシュ沿岸のこの町で一番の男前だったのに、今の姿を見てくれよ\nあいつが何か約束したのも知ってるし、あんたが自腹を切ったのも分かってる！この金は私が渡すから、頼む、船長、 あいつにひどいことだけはしないでくれ、お願いだ！";
			link.l1 = "わかった、わかったよ、奥さん。金は取っておきな、あんたのもんだ。友達のことだが、絶対に傷つけないと約束する。 さて、これで失礼するよ、ちょっと用事があるんでね。あと、こんな美しい女性を助けられて嬉しかったよ。";
			link.l1.go = "Portugal_5";
		break;
		
		case "Portugal_5":
			DialogExit();
			sld = characterFromId("Avendel");
			sld.dialog.currentnode = "Avendel_tavern_7";
			AddLandQuestMark(sld, "questmarkmain");
			pchar.questTemp.Portugal = "AvendelTavern";
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx":
            dialog.text = "しっ、声を抑えて……マダム・ロリータに俺とデートしてくれって頼んでくれ。それから上の階に来い、そこで自由に話せるから。 それまでは一言もしゃべるなよ……\nおい、水夫、マダムに金を払ってからじゃないと俺に触るんじゃねえぞ！（くすくす）";
			link.l1 = "行くぜ、可愛い子ちゃん……";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
           DialogExit();
		   chrDisableReloadToLocation = false;
		   pchar.questTemp.Mtraxx = "jewelry_2";
		break;
		
		case "mtraxx_2":
			pchar.quest.Mtraxx_JewelrySDMOver.over = "yes"; //снять таймер
            dialog.text = "いや、俺じゃねえ。全部話してやるから、邪魔すんなよ。";
			link.l1 = "俺は耳を傾けてるぜ！";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "よし、それじゃあ話そう。だいたい一週間前、軍艦がサントドミンゴに到着したんだ。嵐か戦闘かで損傷してて、 すぐ修理が始まって、乗組員たちは砦に移った。でも、その船長だけは暇さえあればずっとここにいた。 二日間ぶっ通しで飲んだりくつろいだりしてて、うちの女の子の一人を連れてたんだ。宝石を手に入れたのはその子で、 しかも一つだけじゃない。自慢げに何度も話してたよ――ロリータはお客からもらった贈り物を自分のものにしていいっていう決まりだからな。\nあの子はその贈り物の本当の価値なんて全然分かってなかったけど、俺はすぐに見抜いたよ。 酔っ払った船長が琥珀でいっぱいの山について自慢してたって聞いたとき、すぐにタイレックスに手紙を送ったんだ……";
			link.l1 = "";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
            dialog.text = "船長が次に来るまでに、俺はすべて手配しておいたんだ。あいつのお気に入りの女は別の客で忙しくさせて、俺が“仕事”をもらったってわけさ。座標を聞き出そうとしたが、残念ながら無駄だった。 やつは自分がクラッススみたいな大金持ちになって旧世界に戻るって自慢ばかりしてたよ\n場所については一言も言わなかった。唯一わかったのは、やつの船は修理が終わって、 ハバナに向けて出航するところだったってことだ。そこで目的地に向かう任務を手配しようとしてるらしい。結局、 やつは船の持ち主じゃないんだ。";
			link.l1 = "それで、今はハバナにいるのか？";
			link.l1.go = "mtraxx_5";
		break;
		
		case "mtraxx_5":
            dialog.text = "二日前の夜明けに出航したぜ。ここじゃお前が船乗りだろ、数えるのはお前の役目だ。";
			link.l1 = "船長の名前や船の種類、名前、何か分かるか？";
			link.l1.go = "mtraxx_6";
		break;
		
		case "mtraxx_6":
            dialog.text = "なんだと、俺を馬鹿にしてるのか？あいつの名前はエスベルド・カバナス、カンタブロ号の船長だ。 水夫たちはあれをスクーナーと呼んでたと思うぜ。";
			link.l1 = "「それがあんたの知ってることの全部か？」";
			link.l1.go = "mtraxx_7";
		break;
		
		case "mtraxx_7":
            dialog.text = "これ以上何を望むんだ？ハバナに着く前にあいつに追いつけるはずだぜ。だが時間を無駄にするなよ、 キューバを出て隠し場所へ向かう前に長居はしないと思うし、そうなったらもう手遅れだ。\nもっとも、考え直せば一、二時間くらいはここにいてもいいぜ。金はちゃんと払ったんだからな。";
			link.l1 = "いいところね、ダーリン。二時間くらいじゃ大して変わらないわ……";
			// belamour legendary edition -->
			link.l1.go = "mtraxx_7S";
			link.l2 = "また今度にしましょう、あなた。昼休みでも取ったらどうですか。教会に行くとか、他のことをしてもいいですよ。";
			link.l2.go = "mtraxx_7NS";
			sTotalTemp = npchar.id;
			AddMapQuestMarkCity("Havana", false);
			AddLandQuestMark(characterFromId("Havana_PortMan"), "questmarkmain");
		break;
		
		case "mtraxx_7S":
            DialogExit();
			pchar.GenQuest.BrothelCount = sti(pchar.GenQuest.BrothelCount) + 1; // для Данек
			Achievment_SetStat(23, 1);
			//<-- кол-во посещений
			str = npchar.city;
			pchar.quest.(str).win_condition.l1 = "ExitFromLocation";
			pchar.quest.(str).win_condition.l1.location = pchar.location;
			pchar.quest.(str).win_condition = "Brothel_checkVisitTime";
			pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1; //счетчик
			AddDialogExitQuest("PlaySex_1");
			// кач от борделя
			if (CheckNPCQuestDate(pchar, "BrothelSex"))
			{
				if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	
				{
					AddCharacterHealth(pchar, 10);
					AddCharacterMaxHealth(pchar, 1.0);
				}
				else AddCharacterHealth(pchar, 5);
				SetNPCQuestDate(pchar, "BrothelSex");
			}
			// изменение статусов
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "FencingS", -15);
			AddCharacterExpToSkill(pchar, "Pistol", -15);
		break;
		
		case "mtraxx_7NS":
            DialogExit();
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			AddQuestRecord("Roger_1", "3");
			pchar.questTemp.Mtraxx = "jewelry_3";
			SetFunctionTimerCondition("Mtraxx_JewelryHavanaOver", 0, 0, 7, false); // таймер
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			pchar.quest.mtr_jewelry_havana.win_condition.l1 = "location";
			pchar.quest.mtr_jewelry_havana.win_condition.l1.location = "Cuba2";
			pchar.quest.mtr_jewelry_havana.function = "Mtraxx_HavanaInfo";
			DeleteAttribute(pchar, "questTemp.Mtraxx.AffairOfHonor");
			DeleteAttribute(pchar, "questTemp.ZA.Block");
		break;
		// <-- legendary edition
		case "mtraxx_R":
            dialog.text = "お、おう……それは残念だわ。てっきり休暇で来たのかと思ってたのに。うちの娘たち、勇敢なコルセアたちに会いたがってるのよ。 まあいいわ、話して、用件は何かしら？..";
			link.l1 = "マーカスに頼まれて、あんたの店で二日間大騒ぎの宴を開くことになったんだ。酒は全部飲み干して、 女も全員抱くつもりだぜ。いつ始める？";
			link.l1.go = "mtraxx_R1";
		break;
		
		case "mtraxx_R1":
            dialog.text = "ああ、チャーリー・プリンス、そのユーモアはサーベル並みに鋭いな！危うく気分を害するところだったぜ……。\nおい、娘たち！客人だ、特別な客人だぞ！酒と食い物を持ってこい！";
			if (sti(pchar.money) >= 31000)
			{
				link.l1 = "ここにいる可愛い娘を全員呼べ！これから休んで楽しむぞ！ヨーホーホー！..";
				link.l1.go = "mtraxx_R2";
			}
			else
			{
				link.l1 = "ちょっと待ってくれ、ジャネット。お前とお前の女たちのために、俺の船から金貨を取ってくるぜ。すぐ戻るからな！";
				link.l1.go = "exit";
				pchar.questTemp.Mtraxx.Retribution = "brothel_repeat";
				chrDisableReloadToLocation = false;
			}
		break;
		
		case "mtraxx_R2":
			AddMoneyToCharacter(pchar, -30000);
            dialog.text = "あなたのように優しくて、ハンサムで、気前のいいお客様ばかりだったらいいのに……。\n最高の癒やしをご提供しますわ。\nみんな、いらっしゃい！";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionInBrothel");
		break;
		// belamour ночной приключенец
		case "NA_Girl":
            dialog.text = "おやおや、ここに目利きがいるとはな、へへ……まあまあ、ちょうどいい娘がいるぜ。ただし、安くはないぞ： "+makeint(pchar.GenQuest.NightAdventure_money)+" ペソ。"; 
			link.l1 = "取引成立だ。";
			link.l1.go = "NA_Girl_1";
		break;
		
		case "NA_Girl_1":
			AddMoneyToCharacter(pchar, -makeint(pchar.GenQuest.NightAdventure_money));
            dialog.text = "それは素晴らしいわ、あなた。愛の女神官が上の階でお待ちしていますわ。安心して、きっと後悔はさせませんのよ。"; 
			link.l1 = "もうしていない。";
			link.l1.go = "NA_Girl_2";
		break;
		
		case "NA_Girl_2":
			DialogExit();
			pchar.GenQuest.NightAdventureVar = "NightAdventure_NobleWhore"; 
			sld = characterFromId(pchar.GenQuest.NightAdventureId);
			sld.dialog.currentnode = "NightAdventure_NobleWhore_7";
		break;
		// <-- приключенец
		
		case "chicken_god":
			dialog.text = "あんたと旦那アグエイバナのために？もちろんだとも。それで一万だ、船長。";
			if (sti(pchar.money) >= 10000) {
				link.l1 = "待て、そうじゃねえってば！…くそっ！まあいい、ほら、これが報酬だ。";
				link.l1.go = "chicken_god_pay";
			} else {
				link.l2 = "借金できるか？";
				link.l2.go = "chicken_god_notpay";
			}
		break;
		
		case "chicken_god_pay":
			dialog.text = "ごゆっくりお過ごしください、船長。また営業している時にぜひお越しくださいませ。 当店は紳士淑女の皆様にあらゆる娯楽をご提供しております。";
			link.l1 = "...";
			link.l1.go = "chicken_god_pay_1";
		break;
		
		case "chicken_god_pay_1":
			dialog.text = "";
			link.l1 = "Madam "+npchar.name+"、せめてここで何が起きているのか説明してくれないか？総督は、 君たちが一ヶ月も先住民を責任者にしていたことを知っているのか？売春宿が一日でも閉まったら、 どんな入植地もやっていけないんだぜ、俺が保証するよ！";
			link.l1.go = "chicken_god_pay_2";
		break;
		
		case "chicken_god_pay_2":
			dialog.text = "部屋はあなたのものです、船長。では、失礼します。";
			link.l1 = "魅力的ですね。さようなら、奥様。";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_PayForRoom");
		break;
		
		case "chicken_god_notpay":
			dialog.text = "なぜだ、神よ、なぜなんだ！？出ていけ！どこかへ行け、もう耐えられない！この野郎！";
			link.l1 = "うまくいったな。";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_NotPayForRoom");
		break;
		
		//-->> Sinistra Ром на троих
		case "RomNaTroih_1":
			dialog.text = "うーん……普段はこんなことしねえんだが……あんたのためなら一か八かやってみるぜ。今日は運がいいな、船長！";
			link.l1 = "行くぞ！";
			link.l1.go = "exit";
			pchar.RomNaTroih_Shluha = npchar.id;
		break;
		
		case "RomNaTroih_2":
			dialog.text = "俺はお前に怒ってるんだぜ、船長……だが、ちゃんと働けば情けをかけてやるさ。";
			link.l1 = "ああ、もちろんだ。ワインでも開けようか？";
			link.l1.go = "exit";
			Achievment_Set("ach_CL_105");
		break;
		//<<-- Sinistra Ром на троих
	}
}

ref GetFreeHorseRef(string City)
{
	ref rCharacter;
    int storeArray[8];
	int howStore = 0;
	for(int n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (rCharacter.location == City+"_Brothel" && CheckAttribute(rCharacter, "CityType") && rCharacter.CityType == "horse" && rCharacter.horse == "HorseStay")
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return &NullCharacter;
	return &characters[storeArray[rand(howStore-1)]];
}

ref CheckHorsesName(string City, int num)
{
	ref rCharacter;
	string sTemp, sSeeked;
	sSeeked = GetStrSmallRegister(dialogEditStrings[num]);
	for(int n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (rCharacter.location == City+"_Brothel" && CheckAttribute(rCharacter, "CityType") && rCharacter.CityType == "horse")
		{
			sTemp = GetStrSmallRegister(rCharacter.lastname + " " + rCharacter.name);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;			
			sTemp = GetStrSmallRegister(rCharacter.lastname);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;
			sTemp = GetStrSmallRegister(rCharacter.name);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;
		}
	}
	return &NullCharacter;
}
