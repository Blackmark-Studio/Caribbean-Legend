// boal 25/04/04 общий диалог солдат форта
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
    /* // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Fort\" + NPChar.City + "_Fort.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <-- */
    int iTest, iTemp;
	string sTemp;
    iTest = FindColony(NPChar.City); // город
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			sTemp = npchar.location;
			if (findsubstr(sTemp, "_townhall" , 0) != -1) AddDialogExitQuest("MainHeroFightModeOff");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "First time":			
            NextDiag.TempNode = "First time";
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				dialog.text = RandPhraseSimple("スパイか！武器を捨てて俺について来い！","敵の間者だ！捕まえろ "+GetSexPhrase("彼","彼女")+"!");
				link.l1 = RandPhraseSimple("黙れ、この腰抜け！","くたばれ！");
				link.l1.go = "fight"; 
			}
			else
			{
				// eddy. проверяем, не казачок ли. -->
				if (GetRelation2BaseNation(sti(npchar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
					dialog.text = RandPhraseSimple("お前は誰だ、ここで何をしている？","動くな！お前は誰だ？なぜ砦に入ろうとしているんだ？");
					//==> по лицензии
					if (CheckNationLicence(HOLLAND))
					{
						link.l1 = "士官、俺には "+GetRusNameNationLicence(sti(npchar.nation))+"、それゆえ私は合法的にここにいるんだ。ほら、これを見てくれ…";
						link.l1.go = "LicenceOk";
					}
					else
					{
						//==> по флагу
						// заглушка на пирата
						if (sti(pchar.nation) == PIRATE)
						{
    						dialog.text = RandPhraseSimple("海賊が砦にいるのか！？捕まえろ"+GetSexPhrase("彼","彼女")+"!","あいつは海賊だ、我々の砦をうろついてやがる！牢屋にぶち込め！！");
							link.l1 = RandPhraseSimple("ああ、俺は海賊だ。それがどうした？","へっ、できるもんなら捕まえてみろよ……");
							link.l1.go = "fight"; 
							break;
						}
						if (findsubstr(pchar.location.from_sea, "_town" , 0) != -1) //если причалил в городе
						{
							link.l1 = "「の旗が見えないのか」 "+NationNameGenitive(sti(pchar.nation))+" 俺の船のマストに！？";
						}
						else //если причалил не в городе
						{
							link.l1 = "俺は近くに錨を下ろした "+XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen")+" ～の旗の下で"+NationNameGenitive(sti(pchar.nation))+"！他に何か必要か？";
						}
						// belamour legendary edition вызываюий доверие даёт возможность обмануть стражу
						if(sti(pchar.reputation.fame) < 41 && CheckCharacterPerk(pchar, "Trustworthy"))
						{
							Notification_Perk(true, "Trustworthy");
							link.l1.go = "NotPegYou";
						}
						else
						{
							if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < (10+rand(50)+rand(50)))
							{
								notification("Skill Check Failed", SKILL_SNEAK);
								link.l1.go = "PegYou";
							}
							else
							{
								link.l1.go = "NotPegYou";
							}
						}
					}
				}
				// <-- eddy. проверяем, не казачок ли.
				else
				{
					if (sti(NPChar.nation) == PIRATE)
					{
						if (sti(rColony.HeroOwn)) // наш горожанин
						{
			         		switch (rand(10))
							{
								case 0:
									dialog.text = "ああ、船長、あなたと一緒に海で過ごした時間は本当に素晴らしかったぜ！あなたの指揮の下で、 俺たちは何隻もの船を沈めてきたんだ！そしてここで…";
									link.l1 = "ここではな、相棒、海じゃお目にかかれねえ魅力的な女たちをたっぷり拝めるぜ。";
									link.l1.go = "exit";
								break;

								case 1:
									dialog.text = "船長、俺たちが何をしたっていうんだ！？俺たちは陸のネズミじゃねえだろ？";
									link.l1 = "静かにしろ、水夫！お前の持ち場はとても重要で名誉ある役目だ、だから文句を言うのはやめろ。";
									link.l1.go = "exit";
								break;

								case 2:
									dialog.text = "海で何が起きてるんだ、船長？俺たちはまた海を見ることができるのか？";
									link.l1 = "もちろんだとも、水夫！任務が終わったら桟橋へ行って、好きなだけ海を満喫してくれ。";
									link.l1.go = "exit";
								break;

								case 3:
									dialog.text = "文句を言いたいんだ、船長。俺たち全員、海が恋しいんだよ。この陸での任務にはもううんざりだ！";
									link.l1 = "この泣き言にはうんざりだ！ラム酒ならここにもたっぷりあるぜ！船長が命じた場所で働け、 さもねえと見せしめに誰かが吊るされることになるぞ。";
									link.l1.go = "exit";
								break;

								case 4:
									dialog.text = "内緒で話すがな、船長、新しい総督は賄賂好きで横領野郎だぜ。だが、それは俺には関係ないことさ……";
									link.l1 = "その通りだ、コルセア。お前の仕事は持ち場を守って秩序を保つことだ。 そして総督をヤードアームに吊るすのは俺の仕事だ。よくやったな！";
									link.l1.go = "exit";
								break;

								case 5:
									dialog.text = "忘れずにいてくれてありがとうございます、船長！俺たちは火の中水の中でもついていきますぜ！";
									link.l1 = "お前らみたいな悪党のことはよく知ってるぜ！結局のところ、お前らが本当に気にしてるのは金だけだろ。 今夜は酒場で宴がある、酒は俺のおごりだ。忘れずに来いよ。";
									link.l1.go = "exit";
								break;

								case 6:
									dialog.text = "へっ、船長！考えてみろよ、コルセアが本当に秩序の守り手になれると思うか！？本当の仕事をしたのは、 もうずいぶん前じゃねえか！";
									link.l1 = "くつろいでる暇はねえぞ、コルセア！敵の艦隊が俺たちの島の近くの海をくまなく探ってやがる。 いつ血みどろの戦いになってもおかしくねえ、覚悟しとけよ。";
									link.l1.go = "exit";
								break;

								case 7:
									dialog.text = "船長、王冠がまたこちらに艦隊を送り込んできたって聞いたぜ？";
									link.l1 = "もちろんだ、コルセア。生きている限り、俺たちに安息はねえ。地獄に落ちても、悪魔どもと戦い続けるのさ！";
									link.l1.go = "exit";
								break;

								case 8:
									dialog.text = "ヨーホーホー！くそっ、昨日の酒は本当に強烈だったぜ、船長！あんたがいなかったのが残念だ。";
									link.l1 = "大したことじゃねえ、俺が埋め合わせてやるさ。\nそれに、お前らのことはうらやましくもねえぜ。";
									link.l1.go = "exit";
								break;

								case 9:
									dialog.text = "内緒で話すぜ、船長。あんたはいつも俺たちに親切にしてくれるからな。 昨日は本当に可愛い娘といい時間を過ごしたんだ……";
									link.l1 = "へっ、コルセア、お前にはまさに縄がふさわしいぜ！";
									link.l1.go = "exit";
								break;

								case 10:
									dialog.text = "船長！頼む、この呪われた役目から解放してくれ！もう秩序の番人なんて務まらないんだ。";
									link.l1 = "船の夜間見張りも楽じゃねえよ。友よ、義務は義務、どこであろうと何であろうとな。";
									link.l1.go = "exit";
								break;
							}
							// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
							/* link.l2 = RandPhraseSimple("大事な用件だ！","お前に用がある。");
							link.l2.go = "quests";//(перессылка в файл города) */
							break;
						}
					}
					
					//Jason --> мини-квест Дефицитный товар
					if (!CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && sti(pchar.rank) < 4 && !CheckAttribute(pchar, "questTemp.Wine") && npchar.location.group == "soldiers")
					{// Addon 2016-1 Jason пиратская линейка
						string wineCity = "FortFrance";
						if(SandboxMode)
						{
							if(CheckAttribute(pchar,"HeroParam.ToCityId"))
							{
								wineCity = pchar.HeroParam.ToCityId;	
							}
						}
						if(GetCityNameByIsland(LoadedLocation.islandId) ==  wineCity && npchar.location.locator == "protector1")
						{
							dialog.text = "おい、相棒！ちょっと頼みを聞いてくれないか？";
							link.l1 = "やるべきことによるな。";
							link.l1.go = "Wine_soldier";
							link.l2 = "こんなことに付き合ってる暇はねえ。";
							link.l2.go = "exit";
							pchar.questTemp.Wine = "true";
							DelLandQuestMark(npchar);
							break;
						}
						if(StartHeroType == 2)
						{
							if(LoadedLocation.id == "Santiago_fort")
							{
								dialog.text = "おい、相棒！ちょっと頼みを聞いてくれないか？";
								link.l1 = "やるべきことによるな。";
								link.l1.go = "Wine_soldier";
								link.l2 = "こんなことにかまってる暇はねえ。";
								link.l2.go = "exit";
								pchar.questTemp.Wine = "true";
								DelLandQuestMark(npchar);
								break;
							}
						}
					}
					// <-- мини-квест Дефицитный товар
					
					//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
					
					// Шарль де Мор генерал-губернатор французских колоний
					if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
					{
						switch(rand(2))
						{
							case 0: 
							dialog.text = "閣下、総督様！いかようにお仕えいたしましょうか？";
							link.l1 = "何もいりません、ありがとう。";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "これは大変光栄でございます、総督閣下！どうお手伝いできますか？";
								link.l1 = "しっかりと任務を果たせ――それ以上は何も求めていない。";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "お目にかかれて光栄です、閣下！我々の植民地の総督閣下のために、この卑しい兵士に何かできることはございますか？";
								link.l1 = "個人的にはお前に用はねえ。引き続き働け。";
								link.l1.go = "exit";
							break;
						}
						break;
					}
					// Вице-адмирал на службе нации узнается без мундира
					if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
					{
						switch(rand(2))
						{
							case 0: 
							dialog.text = "副提督閣下、ご報告いたします！私の当直中に…";
							link.l1 = "落ち着け、兵士。お前の報告はいらん。上官に報告しろ。";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "お会いできて嬉しいです、副提督！何かお手伝いできることがありますか？";
								link.l1 = "いや、ちょっとお前がどれだけ注意深いか確かめてみただけだ。俺のことを見抜いてくれて嬉しいぜ。";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "副提督、これは光栄です！私に何かご用でしょうか？";
								link.l1 = "Serve "+NationNameGenitive(sti(npchar.nation))+"、兵士よ！それが一番いいことだ。";
								link.l1.go = "exit";
							break;
						}
						break;
					}
					// Офицер с патентом
					if(IsOfficerFullEquip() && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
					{
						switch(rand(2))
						{
							case 0: 
							dialog.text = "ごきげんよう、船長！何かご指示があればお申し付けください。ただし、私は仕えておりますが、どうかご容赦を。 "+NationNameGenitive(sti(npchar.nation))+"、私は司令官と総督にしか答えません。"; 
							link.l1 = "俺の指揮下には士官も乗組員もいる。任務を果たせ、兵士。";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "船長、あなたの船で働かせていただけませんか？同じ奉公を "+NationNameGenitive(sti(npchar.nation))+"、だが俺は海の方が好きだ。"; 
								link.l1 = "任務を与えられた場所で必要とされているのだ、だから誇りを持って職務を果たせ。\n少しの間だけ目を閉じれば、彼らがそれを海へ運んでくれるだろう。";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "おお、運がいいな。お前は"+GetAddress_Form(npchar)+"のために仕える船の船長じゃねえか "+NationNameGenitive(sti(npchar.nation))+"……そして俺は一日中ここに足止めされてるんだ。"; 
								link.l1 = "俺がカリブに来て、たった一週間で船長になったと思ってるのか？これは何年も必死に働いた結果なんだぜ…";
								link.l1.go = "exit";
							break;
						}
						break;
					}
					// <-- legendary edition

					switch (rand(10))
					{
						case 0: ////////////////////////////////////////
							dialog.text = "見てわからねえのか？俺は今、勤務中だ。邪魔するんじゃねえ。";
							link.l1 = "「わかった、わかった……」";
							link.l1.go = "exit";
						break;

						case 1:
							dialog.text = "何か怪しい動きについて話すつもりか？";
							link.l1 = "いや、全くない。それと、俺は船長だぜ。もう聞いてないみたいだな？じゃあな。";
							link.l1.go = "exit";
						break;

						case 2: ///////////////////////////////////////////
							dialog.text = "ここは軍の施設だから、あまり騒がないでくれ。";
							link.l1 = "わかった、覚えておくぜ。";
							link.l1.go = "exit";
						break;

						case 3:
							dialog.text = "こんなに天気がいいのに、俺はここで突っ立ってるだけだ。\n町なら少なくとも女の子がいるが、ここには何がある？ネズミしかいねえよ。";
							link.l1 = ""+GetSexPhrase("同情はするが、俺にできることは何もない――結局それはお前の義務だからな。","おい！私の何がいけないの？あたしは女じゃないのか？")+"";
							link.l1.go = "exit";
						break;

						case 4: ///////////////////////////////////////////
							dialog.text = "話がしたいなら他を当たれ。俺はここで秩序を守らなきゃならねえ、くだらねえおしゃべりに付き合う暇はないんだ。";
							link.l1 = "ああ、いや、ただ君がまだ生きてるか確認しただけさ。まるで彫像みたいに立ってたからな。";
							link.l1.go = "exit";
						break;

						case 5: ////////////////////////////////////////////
							dialog.text = "お前はたぶん駐屯任務なんて楽勝だと思ってるんだろう？全然違うぜ！これは大変で重要な仕事なんだ。俺が昔…… ";
							link.l1 = "その話はまた今度聞かせてくれ。今はちょっと急いでいるんだ。";
							link.l1.go = "exit";
						break;

						case 6: ////////////////////////////////////////////
							dialog.text = "ここは要塞だ、気をつけろ！ネズミのように静かにしていろ！";
							link.l1 = "お前の言う通りだ、兵士。";
							link.l1.go = "exit";
						break;

						case 7:
							dialog.text = "おい！もしかして水を持ってないか？喉が渇いて死にそうだ。";
							link.l1 = "いや、相棒、落ち着けよ……";
							link.l1.go = "exit";
						break;

						case 8://///////////////////////////////////////////
							dialog.text = "駐屯地の生活はなんて退屈なんだ、周りにいるのはお前みたいな田舎者ばかりだぜ！ 町の守備隊の方がきっともっと楽しい時を過ごしてるんだろうな……";
							link.l1 = "「これで“勤務中”だと言うのか？この調子じゃ、間違いなくスパイを見逃すぞ！」";
							link.l1.go = "exit";
						break;

						case 9://///////////////////////////////////////////
							dialog.text = ""+GetSexPhrase("お前、なかなか強そうな奴じゃねえか？砦の守備隊に入隊しねえか？広い兵舎に、日に二度の飯、 それに酒も飲み放題だぜ。","ああ、お嬢さん、この辺鄙な場所でこんなに美しい乙女に出会えるなんて、どれほど嬉しいことかご存じないでしょう！")+"";
							link.l1 = ""+GetSexPhrase("それは確かに魅力的だが、やっぱり断らせてもらうぜ。あの兵舎での訓練は俺には向いてねえんだよ。","お褒めいただきありがとうございます、兵士。")+".";
							link.l1.go = "exit";
						break;

						case 10:
							dialog.text = "このクソ暑さ……半分の命をくれてやってもヨーロッパに帰りてえよ。";
							link.l1 = "そうですね、この土地の気候はあなたの健康には合っていないようですね。";
							link.l1.go = "exit";
						break;
					}
					// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
					/* link.l3 = "ふむ……なるほど。こういうことだ "+GetSexPhrase("「欲しかった」","「欲しかった」")+" 尋ねる…";
					link.l3.go = "quests";//(перессылка в файл города) */
				}
			}
		break;
		
		//Jason --> мини-квест Дефицитный товар
		case "Wine_soldier":
			dialog.text = "あのな、俺はどうしてもワインが飲みたいんだ……だが、腐った果物から作った地元の安酒なんかじゃなくて、一樽二ペソで売ってるあれじゃなくてな、 本物のヨーロッパ産ワインが欲しいんだよ。町の商人から手に入るはずだ。かなり高いが、代金は全部払うし、 さらに三百ペソ上乗せするぜ。どうだ、持ってきてくれるか？";
			link.l1 = "「それを自分で取りに行けない理由は何だ？余計な金を払う必要もねえし、 任務が終わるまで待ってから行けばいいだろう。何か裏があるのか？」";
			link.l1.go = "Wine_soldier_1";
		break;
		
		case "Wine_soldier_1":
			dialog.text = "裏はないさ。俺は休暇をもらうまでは砦を出て町に行けないんだが、その休暇がいつになるか分からないんだよ。\nそれに、我々の司令官が砦内での飲酒を厳禁しやがったんだ、ちくしょうめ！\nだから、兵士の俺を助けてくれないか？";
			link.l1 = "まあ、いいだろう？そのワインを持ってきてやるよ、どうせ暇なんだ。";
			link.l1.go = "Wine_soldier_2";
			link.l2 = "悪いな、相棒。でもそれはできねえ。他の奴に頼んでくれ。";
			link.l2.go = "exit";
		break;
		
		case "Wine_soldier_2":
			dialog.text = "素晴らしい！ありがとうございます！今日は俺が見張り番だから、明日来てくれ。砦の上にいるから、 誰にも気付かれずに瓶を渡せるぞ…";
			link.l1 = "わかった。待っててくれ、明日会いに行くからな。";
			link.l1.go = "exit";
			pchar.questTemp.Wine.id = npchar.ID;
			pchar.questTemp.Wine.SName = GetFullName(npchar);
			pchar.questTemp.Wine.bottle = "true";
			npchar.lifeday = 5;
			SetFunctionTimerCondition("Wine_Exchange", 0, 0, 1, false);
			pchar.questTemp.Wine.City = GetCityNameByIsland(LoadedLocation.islandId);
			if(StartHeroType == 2) pchar.questTemp.Wine.City = "Santiago";
			Log_TestInfo(pchar.questTemp.Wine.City);
			SaveCurrentQuestDateParam("questTemp.Wine_bottle");
			AddQuestRecord("Wine", "0");
			SetFunctionLocationCondition("WineTraderQM", pchar.questTemp.Wine.City+"_town", 0);
		break;
		// <-- мини-квест Дефицитный товар
		
		//============================== ноды на разборки при распознавании =========================
		case "PegYou":
			dialog.text = RandPhraseSimple("これは何か企みがあるようだな。司令官に話をしよう、 "+GetSexPhrase("相棒","おチビちゃん")+"、そしてすべてを解決して……","ふむ……どうもお前は自分で名乗っている人物じゃねえ気がするな……武器を渡せ "+GetAddress_Form(npchar)+"、それから俺についてきてさらに調査するんだ！");
			link.l1 = RandPhraseSimple("くたばれ！","「一週間に日曜日が二回ある時に…」");
			link.l1.go = "fight";
			if (sti(pchar.questTemp.stels.landFort) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40);
				pchar.questTemp.stels.landFort = GetDataDay();
			}
		break;
		case "NotPegYou":
			dialog.text = RandPhraseSimple("「ああ、なるほど……すべて問題ないようだ、行ってよいぞ。」 "+GetAddress_Form(pchar)+".","見張りをしていてちょっと疲れたみたいだ……すべて問題なさそうだ、 "+GetAddress_Form(pchar)+"、申し訳ない。");
			link.l1 = "問題ないぜ！";
			link.l1.go = "exit";
			if (sti(pchar.questTemp.stels.landFort) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80);
				pchar.questTemp.stels.landFort = GetDataDay();
			}
		break;
		case "LicenceOk":
			iTemp = GetDaysContinueNationLicence(HOLLAND);
			if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -12)
			{
				dialog.text = "考えてみろよ！なんて無礼だ！商人のふりをしてここに来やがって！てめえの顔はどこの兵舎にも貼り出されてるんだ、 この野郎！今度は逃がさねえぞ！捕まえろ！";
				link.l1 = RandPhraseSimple("ああっ…","……まあ、自分で望んだことだぜ……");
				link.l1.go = "fight";	
				break;
			}
			if (findsubstr(pchar.location.from_sea, "_town" , 0) == -1) //если причалил не в городе
			{
				dialog.text = "ここに交易しに来たのか？どうやって来たのか聞いてもいいか？お前の船はどこだ？\n分かるか、全部がとても怪しく見えるんだ。だから、事情がはっきりするまで拘束させてもらう。武器を渡して、 俺について来い！";
				link.l1 = RandPhraseSimple("くたばれ！","「一週間に日曜日が二回来たら……」");
				link.l1.go = "fight";	
				break;
			}
			if (iTemp == -1)
			{
				dialog.text = "あなたの免許は期限切れで無効だから、取り消さなければならん。武器を渡して、これからの調査に同行しろ！";
				link.l1 = RandPhraseSimple("くたばれ！","「一週間に日曜日が二回来る時に……」");
				link.l1.go = "fight";	
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "ふむ……すべて問題ないようだな。ただし、君の許可証は今日で期限切れになることを指摘しておこう。今回は通してやるが、 新しい許可証を取得する必要があるぞ。";
				link.l1 = "ありがとうございます、できるだけ早くやります。";
				link.l1.go = "exit";			
			}
			if (iTemp > 0 && iTemp <= 10)
			{
				dialog.text = "ふむ……すべて問題なさそうだな。ただし、君の免許はもうすぐ期限切れになることを伝えておこう。 これはあとわずかしか有効じゃない。 "+FindRussianDaysString(iTemp)+"。だから、それを覚えておけ、 "+GetAddress_Form(npchar)+".";
				link.l1 = "ありがとうございます。できるだけ早く新しいものを手に入れます。";
				link.l1.go = "exit";			
			}
			if (iTemp > 10)
			{
				dialog.text = LinkRandPhrase("まあ、すべて問題なさそうだ。あなたの免許は有効だ "+FindRussianDaysString(iTemp)+"。通ってよい。","「すべて了解した」 "+GetAddress_Form(npchar)+"。町への出入りは自由だ、お前の許可証はあと  "+FindRussianDaysString(iTemp)+"。お邪魔してすみません。","「すべて問題なさそうだ」 "+GetAddress_Form(npchar)+"、もうあなたをここに引き止めはしません。");
				link.l1 = RandPhraseSimple("素晴らしい。よろしくお願いします。","ありがとうございます、士官殿。");
				link.l1.go = "exit";
			}
		break;

		//замечение по обнажённому оружию
		case "SoldierNotBlade":
			// belamour legendary edition если у герой офицер нации -->
			if(IsOfficerFullEquip())
			{
				dialog.text = "船長、武器をしまっていただきたい。我々の街では抜刀は禁止されているのだ。";
				link.l1 = LinkRandPhrase("わかった、しまっておくよ……","もう済んだ。","おっしゃる通りだな……");
				link.l1.go = "exit";
				link.l2 = LinkRandPhrase("くたばれ！","俺が使わせてもらうぜ！","時が来たらしまっておくぜ。");
				link.l2.go = "fight";
				npchar.greeting = "soldier_common";
				NextDiag.TempNode = "First Time";
				break;
			}
			// <-- legendary edition
			dialog.text = LinkRandPhrase("なんでお前は抜き身の刃を振り回してるんだ！？今すぐ武器をしまえ！","今すぐ武器を収めるよう命じる！","「おい、」 "+GetSexPhrase("相棒","娘")+"「おい、みんなを怖がらせるのはやめろ！武器を収めろ。」");
			link.l1 = LinkRandPhrase("「いいだろう。」","結構だ。","おっしゃる通りだな……");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("くたばれ！","夢を見るくらい、害はないさ……","一週間に日曜日が二回来る時だ。");
			link.l2.go = "fight";
			npchar.greeting = "soldier_common";
			NextDiag.TempNode = "First Time";
		break;
	}
}
