// boal 25/04/04 общий диалог солдат
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	int DeceptionChance  = 0;
	int DeceptionPenalty  = 0;
	if(CheckAttribute(pchar,"StealtDeceptionPenalty")) DeceptionPenalty = sti(pchar.StealtDeceptionPenalty);
	
	DeceptionChance = sti(GetSummonSkillFromName(pchar, SKILL_SNEAK)*100/110);
	if(DeceptionChance - DeceptionPenalty > 50) DeceptionChance -= DeceptionPenalty;
	if (false) 
	{
		DeceptionChance = sti(GetSummonSkillFromName(pchar, SKILL_SNEAK)*100/310);
		if(DeceptionChance - DeceptionPenalty > 50) DeceptionChance -= DeceptionPenalty;
	}
	if(sti(pchar.reputation.fame) < 41 && CheckCharacterPerk(pchar, "Trustworthy"))
	{
		DeceptionChance = 100;
		if(DeceptionChance - DeceptionPenalty > 50) DeceptionChance -= DeceptionPenalty;
	}
	if(DeceptionChance > 90) DeceptionChance = 90;
	// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
    /* // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Soldier\" + NPChar.City + "_Soldier.c";
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
			if (false)
			{
				// заглушка на пирата
				if (false)
				{
    				dialog.text = RandPhraseSimple("町に海賊だと！？信じられねえ……捕まえろ "+GetSexPhrase("彼","彼女")+"!!","あいつは海賊だ！捕まえろ "+GetSexPhrase("彼","彼女の")+"!!!");
					link.l1 = RandPhraseSimple("俺は海賊だ、だから何だ？","へっ、やってみな……");
					link.l1.go = "fight"; 
					break;
				}
				else
				{
					if (DeceptionChance > (10+rand(150)+rand(150)))
					{
						dialog.text = RandPhraseSimple("お前は何者だ、そしてここで何をしている？","そこまでだ！お前は何者だ、そして何の権利があってこの町に入ろうとしているんだ？");
						link.l2 = "俺は「～の近くに錨を下ろした」 "+XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen")+" の旗の下で "+NationNameGenitive(sti(npchar.nation))+"。何が分からないんだ？（詐欺の可能性 "+DeceptionChance+"%%)";
						link.l1.go = "NotPegYou";
					}
					else
					{
						dialog.text = RandPhraseSimple("スパイだ！武器を捨てて俺について来い！","敵の間者だ！捕まえろ "+GetSexPhrase("彼","彼女")+"!");
						link.l1 = RandPhraseSimple("黙れ、腰抜け野郎！","くたばれ！");
						link.l1.go = "fight"; 
					}
				}
			}
			else
			{
				// eddy. проверяем, не казачок ли. -->
				if (false)
				{
					// грамота Винсенто
					if(CheckAttribute(pchar, "questTemp.Guardoftruth") && CheckCharacterItem(pchar, "VerifyPaper") && npchar.city == "santiago")
					{
						dialog.text = RandPhraseSimple("お前は誰だ、ここで何をしている？","そこまでだ！お前は何者だ、そして何の権利があってこの町に入ろうとしているんだ？");
						link.l1 = "この書類を見ろ、兵士。俺は異端審問官、ヴィンチェンツォ神父の許可を得てここにいるんだ。";
						link.l1.go = "vincento"; 
						break;
					}
					if(CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && CheckCharacterItem(pchar, "VerifyPaper") && npchar.city == "portspein")
					{
						dialog.text = RandPhraseSimple("お前は誰だ、ここで何をしている？","そこまでだ！お前は何者だ、どんな権利でこの町に入ろうとしているんだ？");
						link.l1 = "この書類を見ろ、兵士。俺は異端審問官のヴィンチェント神父から許可を得てここに来ているんだ。";
						link.l1.go = "vincento"; 
						break;
					}
					if (PChar.location == "Maracaibo_Plantation")
					{
						dialog.text = LinkRandPhrase("おとなしくして、奴隷たちにちょっかいを出すな。","さあ、進め！","ああ、お前か。どうぞ、もうお前のことは聞いてある。");
						link.l1 = "...";
						link.l1.go = "exit";
						break;
					}
					dialog.text = RandPhraseSimple("お前は何者だ、ここで何をしている？","そこで止まれ！お前は何者だ、どんな権利でこの町に入ろうとしているんだ？");
					//==> по лицензии
					if (CheckNationLicence(HOLLAND))
					{
						link.l1 = "「士官、私は」 "+GetRusNameNationLicence(HOLLAND)+"、それゆえ私は正当な理由でここにいるんだ。ほら、これを見てくれ…";
						link.l1.go = "LicenceOk";
						if (findsubstr(pchar.location.from_sea, "_town" , 0) != -1) //если причалил в городе
						{
							link.l2 = "「の旗が見えないのか」 "+NationNameGenitive(sti(pchar.nation))+"俺の船のマストに！？（詐欺の可能性 "+DeceptionChance+"%%)";
						}
						else //если причалил не в городе
						{
							link.l2 = "俺は近くに錨を下ろした "+XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen")+" ～の旗の下で "+NationNameGenitive(sti(pchar.nation))+"。何が分からねえんだ？（欺瞞の可能性\n "+DeceptionChance+"%%)";
						}
						if (DeceptionChance < (10+rand(50)+rand(50)))
						{
							link.l2.go = "PegYou";
						}
						else
						{
							link.l2.go = "NotPegYou";
						}
					}
					else
					{
						//==> по флагу
						// заглушка на пирата
						if (false)
						{
    						dialog.text = RandPhraseSimple("町に海賊が！？信じられない……あいつを捕まえろ！","あいつは海賊だ！捕まえろ！");
							link.l1 = RandPhraseSimple("ああ、俺は海賊だ――それがどうした？","へっ、できるもんなら捕まえてみろよ……");
							link.l1.go = "fight"; 
							break;
						}
						if (findsubstr(pchar.location.from_sea, "_town" , 0) != -1) //если причалил в городе
						{
							link.l1 = "「の旗が見えないのか」 "+NationNameGenitive(sti(pchar.nation))+" 俺の船で！？（欺瞞の可能性 "+DeceptionChance+"%%)";
						}
						else //если причалил не в городе
						{
							link.l1 = "俺は近くに錨を下ろした "+XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen")+" 旗の下で "+NationNameGenitive(sti(pchar.nation))+"。何がわからないんだ？（詐欺の可能性 "+DeceptionChance+"%%)";
						}
						if (DeceptionChance < (10+rand(50)+rand(50)))
						{
							link.l1.go = "PegYou";
						}
						else
						{
							link.l1.go = "NotPegYou";
						}
					}
				}
				// <-- eddy. проверяем, не казачок ли.
				else
				{
					if (sti(NPChar.nation) == PIRATE)
					{
						if (sti(rColony.HeroOwn) == true) // наш горожанин
						{
			         		switch (rand(10))
							{
								case 0:
									dialog.text = "ああ、船長、あなたと一緒に海で過ごした時間は本当に素晴らしかったぜ！あなたの指揮の下で、 俺たちはたくさんの船を沈めてきたんだ！そしてここで…";
									link.l1 = "ここではな、相棒、海じゃお目にかかれねえ魅力的な女たちをたっぷり拝めるぜ。";
									link.l1.go = "exit";
								break;

								case 1:
									dialog.text = "船長、俺たちが何をしたっていうんだ！？俺たちは陸のネズミじゃねえだろう！？";
									link.l1 = "静かにしろ、水夫！お前の持ち場はとても重要で名誉ある仕事だ、だから愚痴を言うのはやめろ。";
									link.l1.go = "exit";
								break;

								case 2:
									dialog.text = "海で何が起きてるんだ、船長？俺たちはまた海を見ることができるのか？";
									link.l1 = "もちろんだとも、水夫！任務が終わったら桟橋に行って、好きなだけ海を楽しむといいさ。";
									link.l1.go = "exit";
								break;

								case 3:
									dialog.text = "文句を言いたいんだ、船長。俺たち全員、海が恋しくてたまらねえ。こんな陸の任務にはもううんざりだ！";
									link.l1 = "この泣き言にはもううんざりだ！ここにもラムは十分あるだろう！船長が命じた場所で働け、 さもないと見せしめに誰かが吊るされることになるぞ。";
									link.l1.go = "exit";
								break;

								case 4:
									dialog.text = "内緒で教えるがな、船長、新しい総督は賄賂を受け取るし横領もしてるんだ。\nだが、それは俺の知ったことじゃねえ……";
									link.l1 = "その通りだ、コルセア。お前の仕事は持ち場を守り、秩序を保つことだ。総督をヤードアームに吊るすのは俺の仕事さ。 よくやった！";
									link.l1.go = "exit";
								break;

								case 5:
									dialog.text = "忘れずにいてくれてありがとうございます、船長！俺たちは火の中水の中、どこまでもついていきますぜ！";
									link.l1 = "お前らみたいな悪党のことはよく知ってるぜ！結局のところ、お前らが本当に気にしてるのは金だけだろ。 今夜は酒場で宴だ、酒は俺のおごりだぜ。忘れずに顔を出せよ。";
									link.l1.go = "exit";
								break;

								case 6:
									dialog.text = "へっ、船長！考えてみろよ、コルセアが本当に秩序の守り手になれると思うか！？本当の仕事をしたのは、 もうずいぶん前のことだぜ！";
									link.l1 = "のんびりしてる暇はねえぞ、コルセア！敵の艦隊が俺たちの島の近くの海をくまなく探してやがる、 いつ血みどろの戦いになってもおかしくねえからな。";
									link.l1.go = "exit";
								break;

								case 7:
									dialog.text = "船長、王冠がまたこちらに艦隊を送ってきたと聞きましたが？";
									link.l1 = "もちろんだ、コルセア。俺たちが生きている限り、安らぎなんてねえさ。\nたとえ地獄に落ちても、悪魔どもと戦い続けるぜ！";
									link.l1.go = "exit";
								break;

								case 8:
									dialog.text = "ヨーホーホー！くそっ、昨日の酒は本当に強烈だったぜ、船長！あんたがいなかったのが残念だな。";
									link.l1 = "大したことじゃねえ、俺が埋め合わせてやるさ。お前らのことを羨ましいとも思わねえぜ。";
									link.l1.go = "exit";
								break;

								case 9:
									dialog.text = "内緒で話すぜ、船長、あんたはいつも俺たちに親切にしてくれるからな。 昨日は本当に可愛い娘と楽しい時間を過ごしたんだ……";
									link.l1 = "へっ、コルセア、お前にはまさに縄がふさわしいぜ！";
									link.l1.go = "exit";
								break;

								case 10:
									dialog.text = "船長！お願いです、この呪われた任務から解放してください！もう秩序の守り手なんて役割、俺には無理です。";
									link.l1 = "船での夜間見張りも楽じゃねえよ。友よ、義務は義務、どこで何をしていようとな。";
									link.l1.go = "exit";
								break;
							}
							// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
							/* link.l2 = RandPhraseSimple("大事なことがあるんだ！","お前に用がある。");
							link.l2.go = "quests";//(перессылка в файл города) */
							break;
						}
						else
						{ // пираты, не наши
							if (sti(pchar.GenQuest.Piratekill) > 20)
							{
								dialog.text = RandPhraseSimple("警戒しろ！武装したイカれ野郎がここにいるぞ！","武器を取れ、武器を取れ！イカれた野郎が来やがったぞ！");
								link.l1 = RandPhraseSimple("え？なんだって？","えっ、なんでこんなことするんだ？");
								link.l1.go = "pirate_fight";
							}
							else
							{
							    /* dialog.text = LinkRandPhrase(RandPhraseSimple("俺に用かい、船長？","俺はただ商売でここに来ただけだ。何か用があれば、遠慮せずに聞いてくれ。"),RandPhraseSimple("船長、俺は今とても忙しいんだ。他の奴に話しかけてくれ。","何か問題でもありますか、船長？ご質問がなければ、下がってもよろしいでしょうか？"),"どいてくれ、船長、急いでるんだ。");
							link.l1 = LinkRandPhrase("悪いな、相棒、俺は "+GetSexPhrase("見間違えた","人違いだった")+" ","よし、さっさと用事を済ませろ。","いや、何もない。");
							link.l1.go = "exit";
							link.l2 = LinkRandPhrase(RandPhraseSimple("お前にいくつか聞きたいことがあるんだ。","お前に用があるんだ。"),RandPhraseSimple("急いでいるようだな。質問は一つだけだ、それが済めば自由にしてやる。","Я "+GetSexPhrase("「欲しかった」","「欲しかった」")+" 何かを尋ねる。"),"お前の用件は後回しだ。俺から聞きたいことがあるんだ "+GetSexPhrase("「欲しかった」","欲しかった")+".");
							    link.l2.go = "quests";//(перессылка в файл города) */
								
								//Экку Korsar - что-то они больно вежливые для пиратов были...
								dialog.text = RandPhraseSimple("何の用だ？さっさと行け。","道をふさぐな、どけ。");
					            link.l1 = RandPhraseSimple("知ってるのか？叫ぶな！","熱くなるなよ。俺はそんなにすぐに冷ましてやらねえぞ！");
					            link.l1.go = "exit";
						    	/* link.l2 = LinkRandPhrase(RandPhraseSimple("お前にいくつか聞きたいことがあるんだ。","お前に用がある。"),RandPhraseSimple("急いでいるようだな。ただ一つだけ質問させてくれれば、すぐに行っていいぜ。","Я "+GetSexPhrase("「欲しかった」","「欲しかった」")+" 何か聞きたいことがある。"),"お前の用件は後回しだ。俺から聞きたいことがあるんだ "+GetSexPhrase("「欲しかった」","「欲しかった」")+".");
							link.l2.go = "quests";//(перессылка в файл города) */
							}
							break;
						}
					}
					else
					{ //если негодяй, имеющий НЗГ к дружественной или нейтральной нации
						if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -15)
						{
							dialog.text = RandPhraseSimple("見てみろ  "+GetSexPhrase("あのろくでなしめ！よくも顔を出しやがったな","あの悪党め！あの女、よくも顔を出しやがったな")+" で "+XI_ConvertString("Colony"+npchar.city)+"。拿捕せよ "+GetSexPhrase("彼","彼女の")+"!!!","「ははっ、お前のことは覚えてるぜ」 "+GetSexPhrase("ろくでなし","悪党")+"「奪え！」 "+GetSexPhrase("彼","彼女の")+"!!!");
							link.l1 = RandPhraseSimple("うおおっ…","……まあ、自分で望んだことだぜ……");
							link.l1.go = "fight";
							break;						
						}
					}

					// --> девица в джунглях
					if(rand(2) == 1 && CheckAttribute(pchar,"GenQuest.EncGirl") && CheckAttribute(pchar,"GenQuest.EncGirl.MeetSoldiers"))
					{
						if(sti(pchar.GenQuest.EncGirl.MeetSoldiers) == 1)	
						{
							dialog.text = "おや、誰が来たかと思えば！レディ "+pchar.GenQuest.EncGirl.name+" ご自身で我々にご光臨とは！よくぞここまで来られたものだな？ずっとお前を探していたんだ！さあ、地下牢へ進め——お前の独房はすでに用意してあるぞ。 ";
							link.l1 = "何を馬鹿なことを言ってやがるんだ！？俺と俺の船員たちは "+GetSexPhrase("騎士","仲間")+" ジャングルを散歩して花を摘んでいただけよ。放っておいてよ！この堅物たちには礼儀ってものがないの！？ 魅力的な女の子を見かけると、すぐにしつこくしてくるんだから！ "+GetSexPhrase("「あなた、あの間抜けどもにどこかへ行けって言って、正直な女を放っておいてもらえないかしら！」","「あなた、あの間抜けどもに伝えてちょうだい…」")+"!";
							link.l1.go = "GirlEnc_1";
						}
						if(sti(pchar.GenQuest.EncGirl.MeetSoldiers) == 2)	
						{
							dialog.text = "おお、ここにいたのか、きれいなお嬢ちゃん！お前の父親が駐屯部隊全員を動員して、 お前を探して家に連れ戻そうとしてるぞ。";
							link.l1 = "消え失せろ！俺は自分がどこへ行くか分かってるし、お前らの助けなんかいらねえ！船長、 こいつらに俺から手を離すように言ってくれ。";
							link.l1.go = "GirlEnc_2";						
						}
						DeleteAttribute(pchar,"GenQuest.EncGirl.MeetSoldiers");
					}
					// <-- девица в джунглях

					// --> belamour ночной приключенец
					if(CheckAttribute(pchar,"GenQuest.NightAdventureSolNum") && npchar.index == pchar.GenQuest.NightAdventureSolNum)
					{
						dialog.text = "兵士の人生は決まっている――見張り、巡回……何の用だ、 "+GetAddress_Form(NPChar)+"?";
						link.l1 = "聞けよ、最近ここであの酔っ払いと喧嘩したのはお前か？まあ、どうやら本当にお前だったみたいだな……";
						link.l1.go = "NightAdventure_CitizenHomieSolder";
						break;
					}
					// <-- ночной приключенец
					
					//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
					
					// Шарль де Мор генерал-губернатор французских колоний
					if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
					{
						switch(rand(2))
						{
							case 0: 
							dialog.text = "閣下、総督閣下！いかがお仕えしましょうか？";
							link.l1 = "何もいらねえ、ありがとな。";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "これは私にとって大変な名誉です、総督閣下！どうお手伝いできますか？";
								link.l1 = "しっかりと任務を果たせ。それ以上は何も求めていない。";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "お目にかかれて光栄です、閣下！我々の植民地の総督閣下のために、この卑しい兵士に何かできることはございますか？";
								link.l1 = "個人的にはお前から欲しいものは何もねえ。引き続き働け。";
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
							dialog.text = "副提督閣下、ご報告いたします！私の当直中に……";
							link.l1 = "落ち着け、兵士よ、俺はお前の報告はいらん。自分の上官に報告しろ。";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "お会いできて嬉しいです、副提督！何かお手伝いできることがありますか？";
								link.l1 = "いや、ちょっとお前がどれだけ注意深いか確かめてみただけだ。俺のことをちゃんと見抜いてくれて嬉しいぜ。";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "副提督、これは光栄です！私に何かご用でしょうか？";
								link.l1 = "Serve "+NationNameGenitive(sti(npchar.nation))+"「兵士よ！それが君にできる最善のことだ。」";
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
							dialog.text = "ごきげんよう、船長！何かご指示があればどうぞ。しかし、失礼ながら、私はたとえ仕えていても "+NationNameGenitive(sti(npchar.nation))+"、私は司令官と総督にしか答えません。"; 
							link.l1 = "俺の指揮下には士官も乗組員もいるんだ。任務を果たせ、兵士。";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "船長、あなたの船で働かせていただけますか？同じ奉公を "+NationNameGenitive(sti(npchar.nation))+"、だが俺は海の方が好きだ。"; 
								link.l1 = "任務を与えられた場所で必要とされているのだ、だから誇りを持って務めを果たせ。\n一瞬でも目を閉じれば、それは海へと持っていかれてしまうぞ。";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "おお、運がいいな。お前は仕官している船の船長じゃねえか "+NationNameGenitive(sti(npchar.nation))+"……そして俺は一日中ここに足止めされてるんだ。"; 
								link.l1 = "俺がカリブに来て、たった一週間で船長になったと思ってるのか？全部、何年もかけて必死にやってきたんだぜ…";
								link.l1.go = "exit";
							break;
						}
						break;
					}
					// <-- legendary edition
					switch (rand(10))
					{
						case 0: ////////////////////////////////////////
							dialog.text = "見てわからねえのか？俺は勤務中だ。邪魔するな。";
							link.l1 = "「わかった、わかった……」";
							link.l1.go = "exit";
						break;

						case 1:
							dialog.text = "何か怪しい動きについて話すつもりか？";
							link.l1 = "いや、全くないぜ。それと、俺は船長だ。もう聞いてねえみたいだな？じゃあな。";
							link.l1.go = "exit";
						break;

						case 2: ///////////////////////////////////////////
							dialog.text = "ここは軍の施設だから、あまり騒がないでくれ。";
							link.l1 = "わかった、それを覚えておくよ。";
							link.l1.go = "exit";
						break;

						case 3:
							dialog.text = "こんなにいい天気なのに、俺はここで突っ立ってるだけだ。\n町なら女の子もいるが、ここにいるのは何だ？ネズミしかいねえよ。";
							link.l1 = ""+GetSexPhrase("お気の毒だが、俺にはどうにもできねえ――結局はお前の義務だからな。","おい！私の何がいけないの？あたしは女じゃないのかい？")+"";
							link.l1.go = "exit";
						break;

						case 4: ///////////////////////////////////////////
							dialog.text = "話がしたいなら他を当たってくれ。俺はここで秩序を守らなきゃならねえし、無駄話をしてる暇なんてないんだ。";
							link.l1 = "ああ、いや、ただお前がまだ生きてるか確認しただけだ。まるで彫像みたいに突っ立ってたからな。";
							link.l1.go = "exit";
						break;

						case 5: ////////////////////////////////////////////
							dialog.text = "お前は駐屯任務が楽勝だと思ってるんだろう？全然違うぜ！これは大変で重要な仕事なんだ。俺が昔……\n ";
							link.l1 = "その話はまた今度聞かせてくれ。今はちょっと急いでいるんだ。";
							link.l1.go = "exit";
						break;

						case 6: ////////////////////////////////////////////
							dialog.text = "ここは要塞だ、気をつけろ！ネズミみたいに静かにしろよ！";
							link.l1 = "お前の言う通りだ、兵士。";
							link.l1.go = "exit";
						break;

						case 7:
							dialog.text = "おい！水を持ってたりしないか？喉が渇いて死にそうだ。";
							link.l1 = "いや、旦那、落ち着け……";
							link.l1.go = "exit";
						break;

						case 8://///////////////////////////////////////////
							dialog.text = "駐屯地の生活はなんて退屈なんだ、周りはお前みたいな田舎者ばかりだしな！まあ、 町の守備隊の方がきっともっと楽しい時を過ごしてるんだろうな……";
							link.l1 = "「これで“勤務中”だと言うのか？この調子じゃ、間違いなくスパイを見逃すぞ！」";
							link.l1.go = "exit";
						break;

						case 9://///////////////////////////////////////////
							dialog.text = ""+GetSexPhrase("お前、なかなか強そうな奴じゃねえか？砦の守備隊に入隊しねえか？広い兵舎に、飯は一日二回、 それに酒も飲み放題だぜ。","ああ、お嬢さん、こんな辺鄙な場所でこんなに美しい乙女に出会えるなんて、どれほど嬉しいことかご存じないでしょう！ ")+"";
							link.l1 = ""+GetSexPhrase("それは確かに魅力的だが、やっぱり断らせてもらうぜ。あの兵舎での訓練なんて、俺には向いてねえんだよ。","お褒めいただきありがとうございます、兵士。")+".";
							link.l1.go = "exit";
						break;

						case 10:
							dialog.text = "このクソ暑さ……ヨーロッパに帰れるなら命の半分だって喜んで差し出すぜ。";
							link.l1 = "はい、あなたの健康がこの土地の気候に合っていないのが見て取れます。";
							link.l1.go = "exit";
						break;

					}
					// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
					/* link.l3 = "少し待ってくれ。聞きたいことがあるんだ "+GetSexPhrase("「欲しかった」","欲しかった")+"...";
					link.l3.go = "quests";//(перессылка в файл города) */				
				}
			}
			//--> Дикая Роза
			if (CheckAttribute(pchar, "questTemp.WildRose_DialogeWithSoldierOnPier") && npchar.location.group == "soldiers" && npchar.city == "Bridgetown")
			{
				dialog.text = "「ブリッジタウンへようこそ。」 "+GetAddress_Form(NPChar)+"...";
				link.l1 = "俺の顔はフランス植民地だけじゃなく、他でも知られてると思ってたぜ…俺の名は "+GetFullName(pchar)+".";
				link.l1.go = "WildRose_Soldier_1";
				DeleteAttribute(pchar, "questTemp.WildRose_DialogeWithSoldierOnPier");
				DelLandQuestMark(npchar);
			}
			//<-- Дикая Роза
		break;
		
		//============================== ноды на разборки при распознавании =========================
		case "PegYou":
			dialog.text = RandPhraseSimple("何か企みがあるように思えるな。司令官に話をしよう、 "+GetSexPhrase("相棒","おチビちゃん")+"……そして、すべてを理解して……","ふむ……お前、どうも正体を偽ってるんじゃねえか……武器を渡せ "+GetAddress_Form(npchar)+"、それから俺についてきてさらに調査するんだ！");
			link.l1 = RandPhraseSimple("くたばれ！","「一週間に日曜日が二回来たら……」");
			link.l1.go = "fight";
			if (!CheckAttribute(pchar,"questTemp.stels.landSolder") || sti(pchar.questTemp.stels.landSolder) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40);
				pchar.questTemp.stels.landSolder = GetDataDay();
			}
		break;
		
		case "NotPegYou":
			dialog.text = RandPhraseSimple("「ああ、そうか……すべて問題なさそうだ、行っていいぞ。」 "+GetAddress_Form(pchar)+".","見張りをしていて少し疲れたのかもしれない……すべて問題なさそうだ、 "+GetAddress_Form(pchar)+"、申し訳ない。");
			link.l1 = "問題ないぜ！";
			link.l1.go = "exit";
			if (!CheckAttribute(pchar,"questTemp.stels.landSolder") || sti(pchar.questTemp.stels.landSolder) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80);
				pchar.questTemp.stels.landSolder = GetDataDay();
			}
		break;
		
		case "vincento":
			dialog.text = RandPhraseSimple("ああ、なるほど……すべて問題なさそうだ、行ってよし。 "+GetAddress_Form(pchar)+".","さてと……うむ、すべて問題なさそうだな。 "+GetAddress_Form(pchar)+"、申し訳ありません。");
			link.l1 = "これで懲りただろう！";
			link.l1.go = "exit";
		break;
		
		case "LicenceOk":
			iTemp = GetDaysContinueNationLicence(HOLLAND);
			if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -12)
			{
				dialog.text = "考えてみろよ！なんて無礼だ！商人のふりをしてここに来るなんてな！お前の顔はどこの兵舎にも貼り出されてるんだ、 この野郎！今度は逃がさねえぞ！捕まえろ！";
				link.l1 = RandPhraseSimple("ああっ…","……まあ、自分で望んだことだぜ……");
				link.l1.go = "fight";	
				break;
			}
			if (pchar.location != "LosTeques_town" && findsubstr(pchar.location.from_sea, "_town" , 0) == -1) //если причалил не в городе 300912
			{
				dialog.text = "ここに交易しに来たのか？どうやって来たのか聞いてもいいか？お前の船はどこだ？\n分かっているだろうが、どうにも怪しく見える。だから、事がはっきりするまで拘束させてもらう。武器を渡して、 俺について来い！";
				link.l1 = RandPhraseSimple("くたばれ！","「一週間に日曜日が二回来たら……」");
				link.l1.go = "fight";	
				break;
			}
			if (iTemp == -1)
			{
				dialog.text = "あなたの免許は期限切れのため無効となり、取り消されなければならない。武器を渡し、 さらに調査のため私についてきてもらう！";
				link.l1 = RandPhraseSimple("くたばれ！","「一週間に日曜日が二回来る時に……」");
				link.l1.go = "fight";	
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "ふむ……すべて問題なさそうだな。ただし、君の許可証は今日で期限切れになることを伝えておこう。今回は通してやるが、 新しい許可証を取得する必要があるぞ。";
				link.l1 = "ありがとうございます、できるだけ早く新しいものを手に入れます。";
				link.l1.go = "exit";			
			}
			if (iTemp > 0 && iTemp <= 10)
			{
				dialog.text = "ふむ……すべて問題なさそうだな。ただし、君の免許はもうすぐ期限切れになることを伝えておこう。 これはあとわずかの間しか有効ではない。 "+FindRussianDaysString(iTemp)+"。だから、それを覚えておけ、 "+GetAddress_Form(npchar)+".";
				link.l1 = "ありがとうございます、できるだけ早く新しいものを手に入れます。";
				link.l1.go = "exit";			
			}
			if (iTemp > 10)
			{
				dialog.text = LinkRandPhrase("さて、すべて問題なさそうだ。あなたの免許はあと "+FindRussianDaysString(iTemp)+"。通ってよい。","「すべて了解した」 "+GetAddress_Form(npchar)+"。町への出入りは自由だ、お前の許可証はあともうしばらく有効だ "+FindRussianDaysString(iTemp)+"。お邪魔してすみません。","「すべて問題なさそうだ」 "+GetAddress_Form(npchar)+"、もうあなたをここに引き留めはしません。");
				link.l1 = RandPhraseSimple("素晴らしい。よろしくお願いします。","ありがとうございます、士官殿。");
				link.l1.go = "exit";
			}
		break;
		//============================== ноды маяка Порт Рояля =========================
		case "PortRoyal_Mayak":
			dialog.text = RandPhraseSimple("おい、相棒、灯台の中で何も壊すんじゃねえぞ。","この灯台は町にとってとても重要なものだ。気をつけろ！");
			link.l1 = RandPhraseSimple("わかった、心配するな。","わかった、心配するな。");
			link.l1.go = "exit";
			NextDiag.TempNode = "PortRoyal_Mayak";
		break;
		case "PortRoyal_Gans":
			dialog.text = LinkRandPhrase("大砲にあまり近づくな――ここは軍事施設だぞ！","大砲の近くに見知らぬ者は近寄るな！","大砲の近くをうろついてるのを見つけたら、ただじゃおかねえぞ！");
			link.l1 = RandPhraseSimple("わかった。","わかった、了解だ。");
			link.l1.go = "exit";
			NextDiag.TempNode = "PortRoyal_Gans";
		break;

		// --> генератор "A damsel in the jungle"
		case "GirlEnc_1":
			dialog.text = "「で、あんたは何者だ、船長？ひょっとして、この居留地で一番悪名高い盗賊の仲間じゃねえだろうな？」";
			link.l1 = "誰を共犯者だと呼んだって！？頭でもやられたのか！？おい、その娘から手を離せ！";
			link.l1.go = "GirlEnc_11";
			link.l2 = "実は、俺は "+GetSexPhrase("彼女と知り合った","彼女と知り合った")+" 最近……";
			link.l2.go = "GirlEnc_12";
		break;

		case "GirlEnc_11":
			dialog.text = ""+GetSexPhrase("Sir","Miss")+"、我々には彼女を拘束して地下牢へ連行する命令が出ているんだ。もし止められると思っているなら、 それは大きな間違いだぞ。";
			link.l1 = "さて、どうするか……";
			link.l1.go = "GirlEnc_11End";
		break;

		case "GirlEnc_11End":
			DialogExit();
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			sld.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "GirlEnc_12":
			dialog.text = "おや、本当かい？それなら、自分のポケットを確かめてみることを勧めるぜ。あの女はプロだからな。";
			link.l1 = "ありがとうございます、そうします。どうして自分がこんなに馬鹿な真似をしてしまったのか……";
			link.l1.go = "GirlEnc_12End";		
		break;		
		
		case "GirlEnc_12End":
			pchar.money = sti(pchar.money) - makeint(sti(pchar.money)/20);
			NextDiag.CurrentNode = NextDiag.TempNode;
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorStay(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "GirlEnc_2":
			dialog.text = ""+GetSexPhrase("Sir","Miss")+"「俺たちはあの娘を見つけて父親のもとへ連れて行くよう命じられているんだ。」";
			link.l1 = "まあ、命令は命令だ――さあ、やってみろ。";
			link.l1.go = "GirlEnc_2End";
			link.l2 = "もう遅いぜ、だって俺はもう彼女の父親と話してるからな。";
			link.l2.go = "GirlEnc_21";
		break;
		
		case "GirlEnc_2End":
			NextDiag.CurrentNode = NextDiag.TempNode;
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorStay(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeDay = 0;	
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("JungleGirl", "11");	
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));	
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();			
		break;
		
		case "GirlEnc_21":
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < rand(100))
			{
				dialog.text = "船長、俺たちには命令があるんだ。もし止められると思ってるなら、それは大間違いだぜ。";
				link.l1 = "さて、どうするかな……";
				link.l1.go = "GirlEnc_21End";
			}
			else
			{
				dialog.text = "へっ、 "+GetSexPhrase("お前は運のいい男だ","お前は運のいい娘だよ")+"。彼女の父親は、彼女を連れ戻した者に惜しみない報酬を約束している。";
				link.l1 = "落ち込むな―これからまだたくさんの報酬が待っているぞ。";
				link.l1.go = "exit";			 
			}
		break;
		
		case "GirlEnc_21End":
			DialogExit();
			AddQuestRecord("JungleGirl", "12");
			AddQuestUserData("JungleGirl","sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			CloseQuestHeader("JungleGirl");
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			sld.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");				
		break;
		// <-- генератор "A damsel in the jungle"
		// --> belamour ночной приключенец
		case "NightAdventure_CitizenHomieSolder":
			dialog.text = "ああ、俺のところにいる。あいつには檻の中で自分の行いを反省させてやるさ。\nそれと、もしあいつのために脅しに来たってんなら、信じな。俺は砦の司令官にだって話を通せるんだぜ。";
			link.l1 = "ああ、脅しに来たわけじゃなくて、あんたに彼への要求を取り下げてもらいたくて来たんだ。\n実は、彼は俺の昔馴染みでな、ただ酔っ払っちまっただけさ。でも分かるだろ、 酔っ払いにとっちゃ海なんて膝までしかねえもんだ・・・";
			link.l1.go = "NightAdventure_CitizenHomieSolder_1";
		break;
		
		case "NightAdventure_CitizenHomieSolder_1":
			dialog.text = "つまり、俺が当番中にあいつに殴られて目の周りが黒くなったのに、今度はあいつを釈放しろって？ なんでそんなことになるんだ？";
			link.l1 = "彼の態度への謝罪として五百ペソはどうだ？";
			link.l1.go = "NightAdventure_CitizenHomieSolder_2";
		break;
		
		case "NightAdventure_CitizenHomieSolder_2":
			dialog.text = "そう思うのか？あいつは俺の名誉を侮辱したんだぞ、それを五百ペソで許せると思ってるのか？ 俺の名誉が金で買えると思ってるのか？";
			link.l1 = "...";
			link.l1.go = "NightAdventure_CitizenHomieSolder_3";
		break;
			
		case "NightAdventure_CitizenHomieSolder_3":
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieSolderNM")
			{
				DeleteAttribute(pchar,"GenQuest.NightAdventureSolNum");
				pchar.quest.NightAdventure_SeaExit.over = "yes";
				pchar.quest.NightAdventure_JungleExit.over = "yes";
				SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
				dialog.text = "いいえ、船長、公平なもんです。あいつは自業自得だ。それに、もうこれ以上俺の仕事の邪魔はしないでくれ。";
				link.l1 = "「まあ、その通りだ。」";
				link.l1.go = "exit";
			}
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieSolderGM")
			{
				dialog.text = "千だ。それ以下はまけねえぞ。";
				link.l1 = "いや、たった一つの傷のためにそんな大金を払う覚悟はまだできていないかもしれないな。";
				link.l1.go = "NightAdventure_CitizenHomieSolder_3NM";
				if (sti(pchar.money) >= 1000)
				{
					link.l2 = "ああ…わかった、ちょっと待て。すぐにペンと羊皮紙を持ってくる。友人へのいかなる要求も取り下げると書け。";
					link.l2.go = "NightAdventure_CitizenHomieSolder_3GM";
				}
			}
		break;
		
		case "NightAdventure_CitizenHomieSolder_3NM":
			DeleteAttribute(pchar,"GenQuest.NightAdventureSolNum");
			pchar.quest.NightAdventure_SeaExit.over = "yes";
			pchar.quest.NightAdventure_JungleExit.over = "yes";
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			dialog.text = "それでは、これ以上私の職務の邪魔をしないでいただきたい。";
			link.l1 = "俺はやらねえ。";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_CitizenHomieSolder_3GM":
			DeleteAttribute(pchar,"GenQuest.NightAdventureSolNum");
			pchar.GenQuest.NightAdventureToPrisoner = true;
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "「はい、どうぞ。」";
			link.l1 = "仕事、うまくいくといいな。";
			link.l1.go = "exit";
		break;
		// <-- ночной приключенец
		
		//--> Дикая Роза
		case "WildRose_Soldier_1":
			if (GetHour() >= 6 && GetHour() <= 21)
			{
				dialog.text = "ああ、あんたか、船長……太陽のせいで眠くなっちまった……この忌々しい暑さめ！";
			}
			else
			{
				dialog.text = "それは否定できねえな。\nでもよ、夜になりゃ誰だって同じに見えるもんだぜ。";
			}
			link.l1 = "どうしたんだ、兵士？普段はお前ら、俺に話しかけてこねえだろう。";
			link.l1.go = "WildRose_Soldier_2";
		break;
		
		case "WildRose_Soldier_2":
			dialog.text = "「ええ、ゴホン、」 "+GetAddress_Form(NPChar)+"。しかしウィロビー卿からの命令があるんだ。 数日前にビショップのプランテーションから奴隷の一団が逃げ出したことを、島に来た新顔全員に警告しなきゃならない。 くそったれ監督どもは、あいつらが鎖を壊してる間にぐっすり寝てやがったに違いねえ。 今日は本当なら可愛いアンジェリークの腕の中にいるはずだったのによ…";
			link.l1 = "当ててみようか。駐屯兵を派遣して農園主の財産を追い回させたんだろう？";
			link.l1.go = "WildRose_Soldier_3";
		break;
		
		case "WildRose_Soldier_3":
			dialog.text = "もちろんだ……ビショップも自分の傭兵どもを何組かジャングルに送り込んだが、それでも満足しなかったらしい。 奴隷を生きたまま連れ戻した者には立派な報酬を約束している。 普段は黒人たちが奴のために汗水流して働かされているが、最近は海軍の脱走兵の一団を連れてきた――石切り場じゃあまり役に立たねえが、頭が切れる連中で、すぐにプランテーションから逃げちまったんだ……\n";
			link.l1 = "「つまり、奴らは白人だったのか？」";
			link.l1.go = "WildRose_Soldier_4";
		break;
		
		case "WildRose_Soldier_4":
			dialog.text = "真っ白な奴らだ、畜生め！黒人どもなら逃げ出すだけだが、 こいつらは倒れた傭兵からマスケット銃やサーベルを奪い取って、すぐに使い始めやがった。 俺たちの仲間が一人やられたし、ビショップの手下も何人か倒された――それで残りの連中は発狂したんだ。\n逃亡者と間違えて、危うく味方を撃ちそうになった奴もいたぜ。それに、 何人かの民間人はジャングルで跡形もなく消えちまった。";
			link.l1 = "街の門は閉まってるのか？";
			link.l1.go = "WildRose_Soldier_5";
		break;
		
		case "WildRose_Soldier_5":
			dialog.text = "いや、もちろん違う――この街は包囲されていない。好きな場所へ自由に行っていいさ。だが、もし逃亡者を追いかけて流れ弾に当たっても、 泣き言は言うなよ。生き延びても、領主様の屋敷に文句を言いに来るな――何しろ、領主様はブリッジタウンの市民だけでなく、客人にも十分な善意を示してくださっているんだからな。";
			link.l1 = "なんと…彼は寛大だな。神よ、フランシス・ウィロビーをお守りください！";
			link.l1.go = "WildRose_Soldier_6";
			link.l2 = "ああ、もしすべての総督がウィロビー旦那のように新参者に気を配ってくれたらなあ…";
			link.l2.go = "WildRose_Soldier_7";
		break;
		
		case "WildRose_Soldier_6":
			dialog.text = "おもしろいな。行っていいぞ、船長。";
			link.l1 = "それでは、さらばだ、兵士。";
			link.l1.go = "WildRose_Soldier_8";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "WildRose_Soldier_7":
			dialog.text = "ああ、俺たちの仕事もずっと楽になるだろう。もう引き止めねえよ、船長。";
			link.l1 = "幸運を祈るぞ、兵士。";
			link.l1.go = "WildRose_Soldier_8";
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 2);
		break;
		
		case "WildRose_Soldier_8":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves");
		break;
		//<-- Дикая Роза
		
		//замечение по обнажённому оружию
		case "SoldierNotBlade":
			// belamour legendary edition если у герой офицер нации -->
			if(IsOfficerFullEquip())
			{
			dialog.text = "船長、武器をしまっていただきたい。我々の街では抜刀は禁止されているのだ。";
			link.l1 = LinkRandPhrase("わかった、しまっておくよ……","もう済んだ。","おっしゃる通りだ……");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("くたばれ！","俺が使わせてもらうぜ！","時が来たらしまっておくぜ。");
			link.l2.go = "fight";
			npchar.greeting = "soldier_common";
			NextDiag.TempNode = "First Time";
		break;
			}
			// <-- legendary edition
			dialog.text = LinkRandPhrase("おい、なんだよその武器を振り回してるのは！？今すぐしまえ！","今すぐ武器をしまえと命じる！","「おい、」 "+GetAddress_Form(NPChar)+"「やめろ、人を脅かすな！武器をしまえ。」");
			link.l1 = LinkRandPhrase("わかった、しまっておくよ……","もう済んだ。","おっしゃる通りだな……");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("くたばれ！","俺が使わせてもらうぜ！","時が来たらしまっておくぜ。");
			link.l2.go = "fight";
			npchar.greeting = "soldier_common";
			NextDiag.TempNode = "First Time";
		break;

		case "pirate_fight":
			DialogExit();
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_Attack(NPChar, Pchar);
			DoQuestFunctionDelay("TownPirate_battle", 0.5);
		break;
	}
}
