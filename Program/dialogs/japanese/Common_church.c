// boal 25/04/04 общий диалог церковь
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Church\" + NPChar.City + "_Church.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06
    
    string iDay, iMonth, lastspeak_date, eggStr;
    string sTemp, sTitle;

	iDay           = environment.date.day;
	iMonth         = environment.date.month;
	lastspeak_date = iday + " " + iMonth;
	int iMoneyToCharacter;

	if (!CheckAttribute(npchar, "quest.HealthMonth"))
    {
        npchar.quest.HealthMonth = "";
    }
	
    if (!CheckAttribute(npchar, "quest.BadMeeting"))
    {	
        npchar.quest.BadMeeting = "";
    }
    if (!CheckAttribute(npchar, "quest.GhostShipMonth"))
    {
        npchar.quest.GhostShipMonth = "";
    }
    
	if (!CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.GiveQuestDateParam"))
	{
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = "";
	}
	
	if(!CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.GiveQuestDay"))
	{
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDay = "";
	}
	
	if (!CheckAttribute(NPChar, "GenQuest.ChurchQuest_1.GiveQuestDateParam"))
	{
		NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = "";
	}
	
	if(!CheckAttribute(NPChar, "GenQuest.ChurchQuest_1.GiveQuestDay"))
	{
		NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = "";
	}
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase(""+GetSexPhrase("息子よ","娘よ")+"残念ながら、あなたをかくまうことはできません。逃げて！","「市の衛兵がお前を探して町中を捜索しているぞ。」 "+GetSexPhrase("息子よ","娘よ")+"。私の教会の扉は苦しむ者たちに常に開かれておりますが、あなたに宿を提供することはできません……",""+GetSexPhrase("息子よ","娘よ")+"、逃げなきゃいけない！ぐずぐずするな、頼むから！"),LinkRandPhrase("教会で何をしているんだ、迷える魂よ？すぐに出て行くのだ、兵士たちに見つかって虐殺が起きる前にな！","今すぐこの寺院を出て行け、この嘲笑者め！お前のような悪党を守るつもりは決してないぞ！","今すぐ我らが主の神殿から出て行け！ここに殺人者など必要ない！"));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("「おいおい、神父さん……」","どうせお前の助けなんかいらねえよ……"),LinkRandPhrase("俺の邪魔だけはしないでくれよ、神父……","俺が行く、心配すんな…","神父、うるさくしないでくれ――本当にそんな暇はないんだ"));
				link.l1.go = "fight";
				break;
			} 
            if (npchar.quest.BadMeeting != lastspeak_date)
			{
				if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_2.StartQuest") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_1.StartQuest") && NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam != iMonth && NPChar.GenQuest.ChurchQuest_2.GiveQuestDay != lastspeak_date && NPChar.location != "Panama_church" && NPChar.location != "LosTeques_church" && rand(5) == 1 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock")) // 280313
				{
					dialog.text = "…奴らは永遠に業火の地獄で焼かれるのだ！決して見ることはない…";
					link.l1 = RandPhraseSimple("「ゴホン！邪魔してるかい、神父？」","それが演説だ！");
					link.l1.go = "GenQuest_Church_2_Start_1";
					NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth; // Предлагает квест не чаще раза в месяц
					break;
				}
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.QuestTown") && PChar.GenQuest.ChurchQuest_2.QuestTown == NPChar.city && CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete"))
				{
					Dialog.Text = ""+GetSexPhrase("息子よ","娘よ")+"、また会えて嬉しいぞ！";
					link.l1 = "「そして、元気そうな姿を見られて嬉しいですよ、神父」 "+NPChar.name+"...";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1";
					break;
				}
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.QuestTown") && PChar.GenQuest.ChurchQuest_1.QuestTown == NPChar.city && CheckAttribute(PChar, "GenQuest.ChurchQuest_1.Complete"))
				{
					Dialog.Text = ""+GetSexPhrase("息子よ","娘よ")+"！また元気な姿で会えて嬉しいぞ。主が我々の件で助けてくださったに違いないな、そうだろう？";
					link.l1 = "「はい」 "+RandPhraseSimple("神父","聖なる神父")+"…だが、風が常に俺の背中にあったわけじゃねえし、時間も労力も金も余計にかかったが――お前の任務は果たしたぜ。";
					link.l1.go = "GenQuest_Church_1_Complete_1";
					break;
				}
				Dialog.Text = "「我らの聖なる住まいへようこそ」 "+GetSexPhrase("息子よ","娘よ")+".";
				link.l1 = "「こんにちは、神父様。」";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_church")
				{
					dialog.text = "「ごきげんよう、エレン、私の子よ。」";
					link.l1 = "「あなたにも、神父。」";
				}
				link.l1.go = "node_3";
				Link.l2 = "お前は俺の父親じゃねえ、二度とそんな呼び方をするな。";
				Link.l2.go = "node_2";
				NPChar.GenQuest.ChurchQuest_2.GiveQuestDay = lastspeak_date;	// Если не дал сегодня, то токо на след день.
			}
			else
			{
				Dialog.Text = "主の神殿から出て行け、冒涜者め！我々に話すことなど何もない！";
				Link.l1 = "俺は最初からやりたくもなかったんだ。";
				Link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "node_2":
			dialog.text = "「ああ、不信心者め！出て行け！お前ごときが我らの主の神殿を汚すことは許さんぞ！」";
			link.l1 = "俺はここにとどまるつもりなんてなかったんだ。";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -0.25);
			npchar.quest.BadMeeting = lastspeak_date;
		break;

		case "node_3":
			if(startHeroType == 4 && NPChar.location == "SantaCatalina_church")
			{
				dialog.text = "ジャンとの…関係にもかかわらず、あなたが我らの主とその御家を忘れずにいてくれて嬉しいです。 何かお手伝いできることはありますか？";
			}
			else
			{
				dialog.text = "主があなたとあなたの事業を祝福されますように……何か特別なご用で私のところに来られましたか？";
			}
    		link.l1 = RandPhraseSimple("寄付をしたいんだ。","良い目的のために寄付したいんだ。");
    		link.l1.go = "donation";
    		link.l2 = RandPhraseSimple("そろそろ告解の時間だと思う。","「告解したい」 "+RandPhraseSimple("神父。","「神父様。」"));
    		link.l2.go = "ispoved";
    		link.l3 = RandPhraseSimple("「お前に用がある」 "+RandPhraseSimple("神父。","「聖なる神父様。」"),"「仕事で来たんだ」 "+RandPhraseSimple("神父。","「聖なる神父様。」"));
    		link.l3.go = "work";
			
			//--> Сага
			// Картахена, Чика Гонсалес
			if(CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "cartahena" && pchar.location == "Cartahena_church" && sti(pchar.money) >= 1000)
			{
				link.l4 = "ご婦人の魂の安息のために祈祷をお願いしたいのですが。";
				link.l4.go = "saga";				
			}
			// поиски исцеления от заклятий
			if(CheckAttribute(pchar, "questTemp.Saga.JessSeekTreatment") && pchar.location != "Bridgetown_church" && !CheckAttribute(npchar, "quest.seektreatment"))
			{ // все церкви, кроме Бриджтауна
				link.l4 = "神父様、助けが必要です。本当に病気なんです。何か忌まわしい異教の呪いにかかってしまいました。どうか、 助けてください、お願いします！";
				link.l4.go = "seektreatment";
			}
			if(CheckAttribute(pchar, "questTemp.Saga.JessSeekTreatment") && pchar.location == "Bridgetown_church")
			{ // попал в Бриджтаун
				link.l4 = "父上、助けが必要です。私は本当に病気なんです。何か邪悪な異教の呪いにかかってしまいました。どうか、 助けてください、お願いします！";
				link.l4.go = "findtreatment";
			}
			if(CheckAttribute(pchar, "questTemp.Saga.JessFindTreatment") && pchar.location == "Bridgetown_church")
			{ // пришёл в Бриджтаун по направлению
				link.l4 = "父上、助けが必要です。本当に病気なんです。何か邪悪な異教の呪いにかかってしまいました。 あなたなら助けてくれると聞きました。どうかお願いします…";
				link.l4.go = "findtreatment";
			}
			// исцеление от заклятий Джесс
			if(CheckAttribute(pchar, "questTemp.Saga.JessTreatment") && pchar.location == "Bridgetown_church")
			{
				link.l4 = "父上、助けが必要です。私は本当に病気なんです。何か忌まわしい異教の呪いにかかってしまいました。 ジェシカ・ローズに言われてここに来ました。彼女が、あなたなら私を助けてくれると教えてくれました。";
				link.l4.go = "treatment";
			}
			if(CheckAttribute(npchar, "quest.candle"))
			{
				link.l4 = "「ろうそくのことだが……」";
				link.l4.go = "candle";
			}
			if(CheckAttribute(npchar, "quest.prayer") && GetNpcQuestPastDayParam(npchar, "prayer_date") >= 1 && stf(environment.time) >= 22.0)
			{
				link.l4 = "私はお祈りの準備ができています、神父様。";
				link.l4.go = "prayer";
			}
			//<-- Сага
			
			// Warship, 30.05.11. Миниквест из дел чести "Divine justice".
			if(CheckAttribute(Pchar, "QuestTemp.AffairOfHonor.GodJudgement.CanSpeakPriest") && AffairOfHonor_GetCurQuest() == "GodJudgement" &&
				NPChar.city == PChar.QuestTemp.AffairOfHonor.GodJudgement.CityId)
			{
				link.l5 = "恐ろしいことが起きています、神父様。";
				link.l5.go = "AffairOfHonor_GodJudgement_1";
			}
			
			link.l6 = "失礼しますが、もう行かなくてはなりません。";
			link.l6.go = "exit";
		break;

		case "AffairOfHonor_GodJudgement_1":
			dialog.text = "心配するな、息子よ。主はお前の苦しみを見ておられ、必ず救いの手を差し伸べてくださる。信仰を強めるために、 いつも十字架を身につけていなさい。";
			Link.l1 = "ありがとうございます、神父様。";
			Link.l1.go = "exit";
			AddItems(PChar, "amulet_3", 15);
			DeleteAttribute(Pchar, "QuestTemp.AffairOfHonor.GodJudgement.CanSpeakPriest");
		break;

// Jason-------------------------------------------------Сага----------------------------------------------
		//--> Чика Гонсалес
		case "saga" :
			dialog.text = "1,000ペソで謹んでご命令を承ります。";
			Link.l1 = "どうぞ、神父様―このコインをお受け取りください。";
			Link.l1.go = "saga_1";
		break;
		
		case "saga_1" :
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "ありがとう、息子よ。祈りを捧げるそのセニョーラの名前は何ですか？";
			Link.l1 = "彼女の名はチカ・ゴンザレス、そして彼女は何年も前にこの世を去った。";
			Link.l1.go = "saga_2";
		break;
		
		case "saga_2" :
			dialog.text = "それは妙だな……アルバレスに何かあったのか？それでお前にこのことを聞いたのか？";
			Link.l1 = "「それで、そのアルバレスってのは誰だ？俺の頼みのどこがそんなにおかしいんだ？」";
			Link.l1.go = "saga_3";
		break;
		
		case "saga_3" :
			dialog.text = "ほうほう！毎月、二十年も灯台を守ってきたアルバレスが、このご婦人の魂の安息を願って祈祷を頼むんだ。 他に誰もゴンザレス夫人のことなんて気にしちゃいなかったさ。で、今度はあんたがここに来たってわけだ。 そう思ったんだが……まあ、俺の知ったことじゃねえ。もちろん、さまよえる魂が安らぎと天国への道を見つけられるよう、 謹んであんたのご希望に従わせてもらうよ。";
			Link.l1 = "ありがとうございます、神父様。";
			Link.l1.go = "saga_4";
		break;
		
		case "saga_4" :
			DialogExit();
			if(CheckAttribute(pchar,"questTemp.Saga7"))
			{
				AddQuestRecord("Saga", "151");
				DeleteAttribute(pchar,"questTemp.Saga7");
			}
			else AddQuestRecord("Saga", "15");
			Saga_SetOrtega();
			pchar.questTemp.Saga = "ortega";
			pchar.quest.Saga_Gonsales1.over = "yes"; //снять возможное прерывание
			if (GetCharacterIndex("SagaGonsalesB") != -1)
			{
				sld = characterFromId("SagaGonsalesB");
				sld.lifeday = 0;
			}
		break;
		
		// belamour участвовал в событиях Картахены
		case "saga_5" :
			dialog.text = "他に誰かの魂のために鎮魂ミサを頼みたい者はいるか？";
			Link.l1 = "うーん……いや、そうは思わねえな。他の誰かの分も注文しなきゃならねえのか？";
			Link.l1.go = "saga_6";
		break;
		
		case "saga_6" :
			dialog.text = "さて、あなたやあなたの神を恐れぬ仲間たちがこの哀れな街を略奪したとき、 あなたの手や刃によって倒れた何百人もの罪なき人々のために、ということかもしれませんね…\nしかし、慎ましい神父ごときが、 何の呵責もなく善良で平和な市民を殺した男の良心に訴えかけられるとは到底思えません…";
			Link.l1 = "「お父さん、分かってくれないんだ……それはすべて過去のことさ。今ここで、誰かを傷つけるつもりはないよ。」";
			Link.l1.go = "saga_7";
		break;
		
		case "saga_7" :
			pchar.questTemp.saga7 = true;
			dialog.text = "あなたの言葉を信じてもよいのですか……？しかし、いずれにせよ、ここは血で汚してはならぬ聖なる地です。だから、衛兵は呼びません。 安らかに立ち去りなさい。おそらく、神の裁きを受ける前に、少しでも罪を償う時間があるでしょう。";
			Link.l1 = "たぶんね。神の御心のままに。";
			Link.l1.go = "saga_4";
		break;
		// <-- Чика Гонсалес
		
		// --> исцеление от заклятий
		case "treatment":
			dialog.text = "ジェシカか？覚えてるよ。かわいそうな罪人だ。でも、彼女は死んだんじゃなかったか？";
			link.l1 = "彼女は亡くなりました、神父様。今はもうこの世にいません。主が彼女の魂を安らかにしてくださいますように。しかし、 彼女はあなたなら私を助けてくださると約束してくれました。";
			link.l1.go = "treatment_1";
			DeleteAttribute(pchar, "questTemp.Saga.JessTreatment");
		break;
		
		case "treatment_1":
			dialog.text = "誰がこんな呪いをお前にかけたのだ、息子よ？正直に話してくれ。";
			link.l1 = "彼女が…彼女がやったんだ。ジェシカだ。";
			link.l1.go = "treatment_2";
		break;
		
		case "treatment_2":
			dialog.text = "神よ、お救いください！やはりそう思いました。異教の儀式に深入りすれば、 どんな強い魂でも闇の奈落に落ちかねません……しかし……彼女は本当に死んだのでしょうか？それとも……完全には死んでいないのか？";
			link.l1 = "神父様、あなたは本当に鋭いですね。これで彼女は本当に死んだのです。";
			link.l1.go = "treatment_3";
		break;
		
		case "treatment_3":
			dialog.text = "この哀れな罪人は何度も私に告白しました。憎しみが彼女の内側から完全に蝕んでいたのです。 私は彼女の企みを知っていました。止めようとし、正しい道を歩ませようとしましたが、私の努力はすべて無駄でした。 私は彼女に、その不浄な行いがもたらす恐ろしい危険と悲惨な結果について警告したのですが……";
			link.l1 = "はい、神父様。私が見たものは本当に恐ろしいものでした。しかし…どうすれば癒されるのでしょうか？";
			link.l1.go = "treatment_4";
		break;
		
		case "treatment_4":
			dialog.text = "祈りの力によってだ、息子よ。我らの寺院での聖なる清めの祈りの力によってな。\nとても長い間祈らねばならんぞ、それも自分のためだけではない。\n彼女のためにも祈らねばならんのだ。";
			link.l1 = "ジェシカのためか？";
			link.l1.go = "treatment_5";
		break;
		
		case "treatment_5":
			dialog.text = "そうだ。あなた自身のため、そして彼女の魂のためにだ。夜十時までにここへ来なさい、誰にも邪魔されないように。 夜通し祈ることになるぞ。太い蜜蝋のろうそくを二十本持ってきて、それに火を灯し、 すべて燃え尽きるまで祈り続けなさい。";
			link.l1 = "「それで俺は治るのか？」";
			link.l1.go = "treatment_6";
		break;
		
		case "treatment_6":
			dialog.text = "すべては主の御手の中にあります。あなたに祈りの仕方を教え、聖書をお渡ししましょう。 聖なる祈りの力があなたにかけられた邪悪な呪いを打ち破り、哀れなジェシカの魂も清めてくれるでしょう。";
			if (GetCharacterItem(pchar, "mineral3") >= 20)
			{
				link.l1 = "俺は蝋燭を二十本持ってるぜ。寺院に泊まって祈り始める準備はできてる。";
				link.l1.go = "treatment_9";
			}
			else
			{
				link.l1 = "まだ二十本のろうそくは持ってねえ。今から集めてくるぜ！";
				link.l1.go = "treatment_7";
			}
		break;
		
		case "treatment_7":
			dialog.text = "よし、息子よ。待っておるぞ。時間を無駄にするでないぞ！";
			link.l1 = "すぐにここに来るぜ……";
			link.l1.go = "treatment_8";
		break;
		
		case "treatment_8":
			DialogExit();
			npchar.quest.candle = "true";
		break;
		
		case "candle":
			dialog.text = "「二十本のろうそくを持ってきたかい、わが子よ？」";
			if (GetCharacterItem(pchar, "mineral3") >= 20)
			{
				link.l1 = "はい、神父様。私の手元には蝋燭が二十本あります。寺院に留まり、祈りを始める準備はできています。";
				link.l1.go = "treatment_9";
				DeleteAttribute(npchar, "quest.candle");
			}
			else
			{
				link.l1 = "まだだ――だが、どんな手を使ってでも必ず手に入れてやる。";
				link.l1.go = "exit";
			}
		break;
		
		case "treatment_9":
			dialog.text = "さて、息子よ。私にそれらを渡しなさい。そして明日の夜十時以降に戻ってきなさい。必要な祈りを教え、 今夜は教会に泊まらせてあげよう。";
			link.l1 = "ありがとうございます、神父様。また明日お会いしましょう！";
			link.l1.go = "treatment_10";
		break;
		
		case "treatment_10":
			DialogExit();
			RemoveItems(pchar, "mineral3", 20);
			LAi_RemoveLoginTime(npchar);
			LAi_SetLoginTime(npchar, 6.0, 22.99);
			npchar.quest.prayer = "true";
			SaveCurrentNpcQuestDateParam(npchar, "prayer_date");
		break;
		
		case "prayer":
			dialog.text = "息子よ、あなたのために祈りの文を用意しておいた。それから、二十本のろうそくと聖書も置いておいたぞ。 ろうそくに火を灯し、祈りを始めなさい。止まることなく祈りなさい。あなた自身の回復と、 この哀れな罪人ジェシカの魂のために祈るのだ。もし何かを忘れたり、わからないことがあっても、気にすることはない。 心から祈りなさい。主にとって大切なのは、あなたの誠実な願いなのだ。";
			link.l1 = "ありがとうございます、神父様。わかりました。";
			link.l1.go = "prayer_1";
		break;
		
		case "prayer_1":
			dialog.text = "朝になったら戻ってきます。あなたのためにも祈っていますよ……";
			link.l1 = "「ありがとうございます、神父様。」";
			link.l1.go = "prayer_2";
		break;
		
		case "prayer_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Saga_BarbadosTreatment", -1);
			chrDisableReloadToLocation = true;//закрыть локацию
		break;
		
		case "seektreatment":
			dialog.text = "「どんな異教の呪いにかかったんだ、息子よ？」";
			link.l1 = "どう呼ばれているのかは知らねえ。俺は弱っていて体もだるいんだ。走り回ることもできねえし、 戦うのもとてもきついんだ。";
			link.l1.go = "seektreatment_1";
		break;
		
		case "seektreatment_1":
			if (sti(pchar.questTemp.Saga.JessSeekTreatment) == 3)
			{
				dialog.text = "俺もその話は聞いたことがある……あれは、この赤い肌の異教徒どもの邪悪な魔女たちによって我々の世界にもたらされたんだ。\nブリッジタウンの教会の院長神父に会いに行くことを勧めるぜ――あの方は、インディアンの呪いがキリスト教徒の肉体と魂に及ぼす悪しき影響について、何年も研究してきたんだ。";
				link.l1 = "「そいつが俺を助けてくれるってのか！？」";
				link.l1.go = "seektreatment_4";
			}
			else
			{
				dialog.text = "あれらのことは聞いたことがある……それはこの赤い肌の異教徒たちの邪悪な魔女によって我々の世界にもたらされたのだ。残念だが、 私が君に与えられる助言はただ一つ、息子よ、もっと祈りの時間を増やし、主の御慈悲に希望を託すことだ。";
				link.l1 = "「でも、本当にどうにもならないんですか、神父様！？私はこのまま……一生を終えることになるんですか？」";
				link.l1.go = "seektreatment_2";
			}
		break;
		
		case "seektreatment_2":
			dialog.text = "絶望してはいけません、息子よ。主はあなたの声を聞き、助けを送ってくださるでしょう。しかし、 他の聖なる場所でも尋ねてみることをお勧めします――異教の呪いを解く方法を知っている神父がいるかもしれません。";
			link.l1 = "ありがとうございます、神父様！私は癒されます――たとえ諸島中の教会をすべて巡ることになっても！";
			link.l1.go = "seektreatment_3";
		break;
		
		case "seektreatment_3":
			dialog.text = "行きなさい、息子よ、主があなたを見守ってくださいますように。";
			link.l1 = "「さようなら、神父。」";
			link.l1.go = "exit";
			npchar.quest.seektreatment = "true";
			pchar.questTemp.Saga.JessSeekTreatment = sti(pchar.questTemp.Saga.JessSeekTreatment)+1;
		break;
		
		case "seektreatment_4":
			dialog.text = "主だけがあなたを助けられる――そして自分自身もだ、息子よ。神父は何をどうすべきか教えることしかできん。会いに行きなさい。";
			link.l1 = "ありがとうございます、神父様！あなたに救われました！すぐにバルバドスへ出航します！";
			link.l1.go = "seektreatment_5";
		break;
		
		case "seektreatment_5":
			dialog.text = "さあ行きなさい、主があなたを見守ってくださいますように。";
			link.l1 = "「さようなら、お父さま。」";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Saga.JessSeekTreatment");
			pchar.questTemp.Saga.JessFindTreatment = "true";
		break;
		
		case "findtreatment":
			dialog.text = "どんな異教徒の呪いにかかったんだ、息子よ？当ててみようか――走れなくなったし、サーベルは重すぎて、動きも鈍くなっているんだろう？";
			link.l1 = "「どうしてそれを知っていたのですか、神父？」";
			link.l1.go = "findtreatment_1";
		break;
		
		case "findtreatment_1":
			dialog.text = "お前が近づいてくる足取りを見れば、すぐに分かったぞ、息子よ。主が我ら罪深き魂に慈悲を与えてくださいますように……さあ、息子よ、正直に言いなさい——誰がそのような呪いをお前にかけたのだ？";
			link.l1 = "名前が必要ですか、神父？";
			link.l1.go = "findtreatment_2";
		break;
		
		case "findtreatment_2":
			dialog.text = "名前を知っているなら、言ってみろ。";
			link.l1 = "彼女の名前は……ジェシカ・ローズだった。";
			link.l1.go = "findtreatment_3";
		break;
		
		case "findtreatment_3":
			dialog.text = "神よお救いください！異教の儀式に深入りすれば、どんな強き魂も闇の奈落へと落ちてしまうかもしれません……彼女に、いや、この哀れな魂に何が起こったのですか？";
			link.l1 = "「彼女は亡くなりました、神父。」";
			link.l1.go = "findtreatment_4";
		break;
		
		case "findtreatment_4":
			dialog.text = "しかし…本当に彼女は死んだのか？それとも…完全には死んでいないのか？";
			link.l1 = "「さすがに聡明ですね、神父様。これで彼女は本当に死んだというわけだ。」";
			link.l1.go = "treatment_3";
			DeleteAttribute(pchar, "questTemp.Saga.JessSeekTreatment"); // если было
			DeleteAttribute(pchar, "questTemp.Saga.JessFindTreatment"); // если было
		break;
		//<-- Сага
		
		// Church GenQuest_2 -->	
		case "GenQuest_Church_2_Start_1":
			dialog.text = "「……そして主の慈悲を！彼らの罪のために、万物の闇がその魂を呑み込まんことを……」";
			link.l1 = LinkRandPhrase("聖父","Padre","Father")+"、ちょっと熱心すぎじゃねえか？そんなに頑張ると倒れちまうぞ……";
			link.l1.go = "GenQuest_Church_2_Start_2";
			link.l2 = "……ちくしょう。じゃあな。";
			link.l2.go = "exit";
		break;
			
		case "GenQuest_Church_2_Start_2":
			dialog.text = "「ああ、」 "+GetSexPhrase("息子よ","娘よ")+"「なんという冒涜、最も忌まわしい罪が今しがた起きたのだ！教会から盗みを働くとは！！！ まるで主ご自身の懐に手を突っ込むようなものだ！」";
			link.l1 = "ああ、そうか……どうしてそんなことになったんだ？";
			link.l1.go = "GenQuest_Church_2_Start_3";
			link.l2 = LinkRandPhrase("とても悲しいけど、俺は本当に行かなきゃならねえんだ……","ご愁傷様です、神父。しかし、私はもう行かねばなりません……","お前さんは全能の神に頼りすぎたんじゃねえか。もっとしっかりした錠前を使うべきだったな。さて、 俺は行かなくちゃな…");
			link.l2.go = "exit";
		break;
			
		case "GenQuest_Church_2_Start_3":
			dialog.text = "夜の闇に紛れて、何者かが教区で集めたものをすべて盗みやがった！この冒涜者どもは、 奉納用の聖杯まで持ち去ったんだ！";
			link.l1 = "おお時よ、風習よ……しかし、手がかりがまだ新しいうちに何か行動を起こしたんだろうな？";
			link.l1.go = "GenQuest_Church_2_Start_4";
		break;
			
		case "GenQuest_Church_2_Start_4":
			dialog.text = "もちろんですとも！私はこの冒涜的な盗賊どもを破門にし、今まさに彼らに呪詛を宣告しているのです！";
			link.l1 = "それが非常に効果的な手段であることは疑っていません。\nしかし、私が言いたかったのはもっと実際的なことです。\n例えば追跡隊を組織するとか。";
			link.l1.go = "GenQuest_Church_2_Start_5";
		break;
			
		case "GenQuest_Church_2_Start_5":
			dialog.text = "ああ、悪に抵抗しないという誓いに縛られたただの神父に何ができようか？あの悪党どもはきっともうここから遠く離れ、 盗んだ金で酒場で飲み明かしたり、堕落した女たちと放蕩にふけっているに違いない！ あそこでやつらが破滅することを願うばかりだ！";
			link.l1 = RandPhraseSimple("私は確信している、そんな最期の方が絞首刑よりずっと魅力的だとな。\nしかし、これ以上は邪魔しないぜ。\n健闘を祈る。","まあ、いつかは俺たちもご先祖様のもとへ行くことになるが、 あいつらにはもっと早い最期を迎えてもらっても構わねえな。\nだが、俺はもう行かなくちゃならねえ。幸運を祈るぜ。");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("聖父","Padre","Father")+"しかし、私は何の誓いにも縛られておらず、喜んで主と共に報いの時をもたらすお手伝いをいたします。";
			link.l2.go = "GenQuest_Church_2_Start_5_1";
		break;
		
		case "GenQuest_Church_2_Start_5_1": //выше - выход из диалога без подтверждения - странно, однако
			dialog.text = "お前のために祈っているぞ、息子よ！さあ行け、そしてこの詐欺師どもに報いを与えてやれ！";
			link.l1 = "疑うなよ、神父";
			link.l1.go = "GenQuest_Church_2_Start_6";
		break;
			
		case "GenQuest_Church_2_Start_6":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_2.StartQuest = true;
			PChar.GenQuest.ChurchQuest_2.QuestTown = NPChar.City;	// Город, в котором спрашиваем
			PChar.GenQuest.ChurchQuest_2.QuestTown.PriestName = NPChar.name;
			PChar.GenQuest.ChurchQuest_2.IslandId = locations[FindLocation(NPChar.location)].islandId; // На каком острове опрашиваем бандюков
			PChar.GenQuest.ChurchQuest_2.Nation = sti(NPChar.nation);
			PChar.GenQuest.ChurchQuest_2.AskPeople = true;
			PChar.GenQuest.ChurchQuest_2.AskBarmen = true;
			PChar.GenQuest.ChurchQuest_2.AskAlcash = true;
			PChar.GenQuest.ChurchQuest_2.MoneyCount = (sti(pchar.rank)+8)*543+3210;
			PChar.GenQuest.ChurchQuest_2.MoneyToCharacter = makeint(sti(PChar.GenQuest.ChurchQuest_2.MoneyCount)/3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			ReOpenQuestHeader(sQuestTitle);
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "1");
			AddQuestUserDataForTitle(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
		break;
			
		case "GenQuest_Church_2_Thief_2":
			dialog.text = "そうだな、もしかすると全能の創造主は、愚かな子供たちをその罪の罰として疫病や飢えに送り込むのかもしれん……";
				link.l1 = "誇りのためとか、欲のためとか……どうした、神父、顔色が悪いぞ？";
				link.l1.go = "GenQuest_Church_2_Thief_3";
			break;
			
		case "GenQuest_Church_2_Thief_3":
			if(rand(1) == 0) // Священник искренне раскаивается...
			{
				dialog.text = "イエス様、主よ、罪深き僕にお慈悲を……あなたは……盗賊たちを見つけましたか？彼らを討ち果たしたのですか？";
					link.l1 = "十戒を思い出しましょう、善良なキリスト教徒なら幼い頃から知っているはずです。「汝、殺すなかれ。汝、盗むなかれ。 汝、偽証するなかれ。」神を畏れる者がこれらを破ることができるでしょうか――ましてや、霊的な神父が……？！";
					link.l1.go = "GenQuest_Church_2_Thief_4_1_1";
			}
			else
			{
				dialog.text = "ここは空気が重いな……それで、盗賊たちを見つけたのか？奴らを倒したのか？";
					link.l1 = "十戒を思い出しましょう。善良なキリスト教徒なら幼い頃から知っているはずです――殺してはならない、盗んではならない、偽証してはならない。神を畏れる者がこれらを破ることができるでしょうか――ましてや、霊的な神父が！？..";
					link.l1.go = "GenQuest_Church_2_Thief_4_2_1";
			}
		break;
			
		case "GenQuest_Church_2_Thief_4_1_1":
			dialog.text = ""+GetSexPhrase("息子よ","娘よ")+"…神よ、お許しください…あれほどの金、あれほどの誘惑…人間は弱い、本当に弱い！耐えられなかった…正気を失っていた…昼も夜も祈り、悔い改め、厳しく断食し、肉体を苦しめた…この身に値しない私が、ただ天に願ったのは、 自分の欲に駆られて誘惑してしまったあの哀れな男たちだけはどうかお救いくださいということだけでした…";
			link.l1 = LinkRandPhrase("Father","Padre","Father")+"、落ち着いてください。彼らはそのことについて何も言っていません……そして、きっとこれからも言わないでしょう。ちなみに、彼らは自発的に聖体拝領用の聖杯を私に返してくれましたので、 それをあなたにお返しします。";
			link.l1.go = "GenQuest_Church_2_Thief_4_1_2";
		break;
			
		case "GenQuest_Church_2_Thief_4_1_2":
			dialog.text = "主よ、感謝いたします！神よ、あなたはこの取るに足らぬ僕、汚れと悪徳にまみれた罪人の祈りをお聞きくださいました…";
			link.l1 = "誰でもつまずくことはある……だが、あなたの悔い改めが本物のようだから、こう言わせてもらう。あなたは立派な男であり、良い神父だ。 裁判にかけられれば、良い結果にはならないだろう。主の御業にとどまるか否か、それを決めるのはあなた自身だ――それを教え、導くことができるのは主だけなのだから……\n";
			link.l1.go = "GenQuest_Church_2_Thief_4_1_3";
		break;
			
		case "GenQuest_Church_2_Thief_4_1_3":
			if(rand(1) == 0) // Священник хочет всучить ГГ бабло
			{
				dialog.text = ""+GetSexPhrase("息子よ","娘よ")+"…悔い改めと感謝の涙をもって、この聖杯をあなたからお受けいたします。あなたの魂の清らかさと高貴さに、 私は心から感動いたしました。心より祝福をお贈りし、 このささやかな印を謹んでお受け取りいただけますようお願い申し上げます\n "+FindRussianMoneyString(iMoneyToCharacter)+"…これで費用の足しになるといいんだが？";
				// ГГ не берёт деньги. Плюсанем репу
				link.l1 = "これは不要です、神父様 "+NPChar.name+"。私は決して貧しい者ではありませんから、この金はあなたの教区のために有効に使ってください。";
				link.l1.go = "GenQuest_Church_2_Thief_4_1_4";
				// ГГ берёт деньги
				link.l2 = "ありがとうございます。 "+LinkRandPhrase("Father","神父","聖なる神父")+"、それで十分だ。";
				link.l2.go = "GenQuest_Church_2_Thief_4_1_5";
			}
			else
			{
				dialog.text = ""+GetSexPhrase("息子よ","「娘よ」")+"…悔い改めと感謝の涙をもって、この聖杯を主の慈悲と赦しのしるしとしてあなたから受け取ります。 あなたの魂の清らかさと高貴さに、私は本当に心を打たれました。心からあなたに祝福を授けます！";
				link.l1 = "「祝福をありがとうございます。」 "+LinkRandPhrase("神父。","「父上。」")+".";
				link.l1.go = "GenQuest_Church_2_Thief_4_1_4";
				link.l1 = "祝福は確かに必要だが、俺がかなりの出費をしたことを考えると、もう少し具体的な支援があっても悪くはないだろう……";
				link.l1.go = "GenQuest_Church_2_Thief_4_1_6";
			}
			ChurchGenQuest2_RemoveCup();
		break;
			
		case "GenQuest_Church_2_Thief_4_1_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", 3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_1");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_1_5":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_2");
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_1_6":
			iMoneyToCharacter = sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter);
			dialog.text = "ああ、子よ、本当にすまない……このささやかな支援が\n "+FindRussianMoneyString(iMoneyToCharacter)+" お前の費用をまかなうのに十分か？";
			link.l1 = "「はい」 "+LinkRandPhrase("神父。","「父上。」")+"「もう十分だ、ありがとう。」";
			link.l1.go = "GenQuest_Church_2_Thief_4_1_6_1";
		break;
			
		case "GenQuest_Church_2_Thief_4_1_6_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_3");
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_2_1":
			dialog.text = "「あなたのほのめかしがよくわからないな」 "+GetSexPhrase("息子よ","娘よ")+"、何の話をしているんだ！？";
			link.l1 = "俺が言ってるのは、強欲が人間にどんな恐ろしいことをさせるかって話だぜ。それに、 あんたの教会を盗んだっていうボロ服野郎どもから聞いたこともな。\n何か言いたいことでもあるのか？";
			link.l1.go = "GenQuest_Church_2_Thief_4_2_2";
		break;
			
		case "GenQuest_Church_2_Thief_4_2_2":
			dialog.text = "お前に言っておくがな、子供よ、今話している相手は聖職者だぞ。もう少し敬意を払ったほうがいい、 さもないと後悔することになるかもしれんぞ。さて、この聖杯についてだが――わしは見たことがないが、もし教区に寄付するつもりならば……";
			link.l1 = "待てよ、神父。ちゃんと説明しない限り渡さねえぞ。";
			link.l1.go = "GenQuest_Church_2_Thief_4_2_3";
		break;
			
		case "GenQuest_Church_2_Thief_4_2_3":
			if(rand(1) == 0) // Просто несколько разные варианты диалога
			{
				dialog.text = "説明することなんてあるか！？さあ、見ろ――お前は "+GetSexPhrase("賢い男","賢い娘")+"、そしてあなたもきっとお分かりでしょうが、あの悪党どもが何を言おうと――私が彼らを雇ったなどという話はまったくの嘘です！主は、 彼らの冒涜だけでなく偽証の罪についても必ず罰を下されますぞ！";
				link.l1 = "主を放っておけ！お前が俺にけしかけたあの哀れな連中が、俺に何を話したかなんてどうして分かる？もしかしたら、 奴らがあんたの悪口を言う前に、俺が殺しちまったかもしれねえだろう？";
				link.l1.go = "GenQuest_Church_2_Thief_4_2_4_1";
			}
			else
			{
				dialog.text = "お前と話すことなんて何もねえ！主の御前での義務を果たしていないし、寺院で罵詈雑言を吐き、神父を脅そうとして、 教会の器具まで見せびらかしている――それをどうやって手に入れたかもまだ分からん！今ここで侍者たちを呼んで現行犯で捕まえさせないだけ、 神に感謝するんだな！";
				link.l1 = "ふむ……お前はもう人の裁きを恐れぬほど罪に溺れてしまったようだな。だが、まだ神の正義は残っている。我々は皆、 遅かれ早かれそれに答えねばならんのだ。\nさあ、「教会の器具」を持っていけ、そして自分がそれに触れるに値する者かどうか、よく考えるのだぞ、神父 "+NPChar.name+".";
				link.l1.go = "GenQuest_Church_2_Thief_4_2_4_2_1";
				link.l2 = "どうか私の疑念をお許しください、神父様。人の心は弱く、魂は迷うものです。どうか聖杯を受け取り、 私に祝福を授けてください。";
				link.l2.go = "GenQuest_Church_2_Thief_4_2_4_2_2";
			}
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_1":
			dialog.text = "うーん…… "+GetSexPhrase("息子よ……旦那……旦那……","「娘よ……お嬢さん……お嬢様……」")+" "+PChar.name+"…私はあなたの前で頭を下げる覚悟です…そして、いわば我々の意見の相違について話し合い…このささやかな金額であなたのご損失を補償いたします "+FindRussianMoneyString(iMoneyToCharacter)+"…もちろん、この件に他の者を巻き込まないのであれば…";
			// При этом варианте репу плюсуем
			link.l1 = "誰も巻き込むつもりはない。聖杯を持っていけ！それから、信者たちの懐からこっそり盗んだ金なんて、 俺が受け取ると思うなよ！";
			link.l1.go = "GenQuest_Church_2_Thief_4_2_4_1_1";
			// При этом - минусуем
			link.l2 = "誰も巻き込むつもりはない。杯を持っていけ！俺がこの金を受け取るのは、お前にたっぷり時間と金を使ったからだ。";
			link.l2.go = "GenQuest_Church_2_Thief_4_2_4_1_2";
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_1_1":
			DialogExit();
			iMoneyToCharacter = PChar.GenQuest.ChurchQuest_2.MoneyToCharacter;
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_5");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex2", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(iMoneyToCharacter));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", 3);
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_4");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_2_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_RemoveCup();
			ChangeCharacterComplexReputation(PChar,"nobility", 3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_6");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_2_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_7");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1":
			// ничего не принесли священнику.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Without_All"))
			{
				link.l1 = "「恐ろしい知らせだ」 "+LinkRandPhrase("Father","Padre","Father")+"：盗賊どもはあまりにも狡猾で手強かったから、教会の金を取り戻すことができなかったんだ……";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_1";
				break;
			}
			// Принесли священнику только чашу.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Only_With_Cup"))
			{
				link.l1 = "「重大な知らせだ」、 "+LinkRandPhrase("Father","Padre","Father")+"：盗賊どもには追いつけたが、俺の唯一の戦利品はこの聖杯だけだったぜ。";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1";
				ChurchGenQuest2_RemoveCup();
				break;
			}
			// Принесли священнику и деньги и чашу.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.With_All"))
			{
				if(sti(PChar.money) >= sti(PChar.GenQuest.ChurchQuest_2.MoneyCount))
				{
					link.l1 = "きっとこの知らせはお気に召すでしょう――私は盗賊どもをしかるべく罰し、教区のお金とこの聖杯を取り戻しました。";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_1";
				}
				// Деньги можно заныкать.
				link.l2 = LinkRandPhrase("Father","Padre","Father")+"…悪い知らせを持ってきたぜ…あの悪党どもを追い詰めるのに、ずいぶん時間も手間も資金もかかったんだが、やっと見つけた時には、 こいつら全部飲んじまって、残ったのはこの聖杯だけだったんだ…";
				link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1";
				ChurchGenQuest2_RemoveCup();
				break;
			}
			// Священник - вор.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.PriestIsThief"))
			{
				dialog.text = "「ああ、」 "+GetSexPhrase("息子よ","娘よ")+"、私に一体何が起こるというのです？危険や不安に満ちているのはあなたの道であり、 私の静かな独房は思索と祈りの領域、人間の激情が渦巻く荒れ狂う海の中の静かな島なのです…";
					link.l1 = "「そして、あなたの至福の孤独の静けさを乱すものは何もないのですか？」";
					link.l1.go = "GenQuest_Church_2_Thief_2";
				break;
			}
			// Короткий вариант прохождения квеста.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Short_With_Mon"))
			{
				if(sti(PChar.money) >= sti(PChar.GenQuest.ChurchQuest_2.MoneyCount))
				{
					link.l1 = "きっとこの知らせはあなたを喜ばせるでしょう――盗賊どもを懲らしめて教区のお金を取り戻しました。";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_1";
				}
				// Деньги можно заныкать.
				link.l2 = LinkRandPhrase("Father","Padre","Father")+"…残念ながら、あなたをがっかりさせねばなりません。私は群島中で盗賊どもを追い回し、数々の危険や障害を乗り越え、 ほとんど自分を滅ぼしかけ、それでもついに奴らを捕まえたのですが、あいにく…すでに教会の金は使い果たされていました。";
				link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1";
			}
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1": // ГГ решил заныкать деньги...
			if(rand(1) == 0)	// Священник верит ГГ но не даёт денег...
			{
				if(rand(4) == 3) // Более "мягкий" исход событий.
				{
					dialog.text = "「ああ」 "+GetSexPhrase("息子よ","娘よ")+"。あなたの言葉に私は深い悲しみに沈みました――しかし絶望はしていません、絶望は大罪ですから！主は私たちの信仰を強めるため、 また新たな試練をお与えになったのです。";
						link.l1 = "アーメン、神父様……";
						link.l1.go = "exit";
						sQuestTitle = NPChar.City + "ChurchGenQuest2";
						AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_9");
						AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
						CloseQuestHeader(sQuestTitle);
						ChangeCharacterComplexReputation(PChar,"nobility", -2);
						DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
						NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
				}
				else
				{
					dialog.text = ""+GetSexPhrase("息子よ","娘よ")+"、お前の魂の牧者に嘘をつくんじゃないぞ。";
						link.l1 = "本当に申し訳ありません、神父様。しかし、私は誓って本当のことを話しています。";
						link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3";
				}
			}
			else
			{
				// Священник даёт деньги ГГ...
				iMoneyToCharacter = sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter);
				dialog.text = "「ああ、」 "+GetSexPhrase("息子よ","娘よ")+"。あなたの言葉は私を深い悲しみに沈めました――しかし絶望はしません、絶望は大罪ですから！主は我々の信仰を強めるために新たな試練をお与えになったのです。 しかし、あなたの努力と出費は、たとえ結果が実らなかったとしても報われるべきです。どうか、 このささやかな金額をお受け取りください―― "+FindRussianMoneyString(iMoneyToCharacter)+" - そして正しき道を歩み続けてください！";
					link.l1 = "ふむ！…ありがとうございます、神父様。このお金は善き目的のために使わせていただきます。";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_1";
					link.l2 = LinkRandPhrase("Father","Padre","Father")+"…私はまだ仕事を終えていないのに報酬を受け取るわけにはいきません。 このお金は祭壇の修復に使ったほうがいいでしょう。";
					link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1_2";
			}
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_3":
			if(rand(6) == 3)
			{
				dialog.text = "「よし、信じるぜ」 "+GetSexPhrase("息子よ","娘よ")+"。主は我らの信仰を強めるため、また新たな試練をお与えになったのです。";
				link.l1 = "アーメン……";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3_1"
				break;
			}
				dialog.text = "卑劣な奴め！本当に我らが主を欺けると思ったのか！？呪われよ"+GetSexPhrase("、ろくでなし","、あばずれ")+"「出て行け！それから、この金はお前に何の得にもならねえことを覚えておけ！」";
				link.l1 = "どういうことだ！？神父！..";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3_2";
			break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_3_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "5");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			AddCharacterExpToSkill(PChar, "Sneak", 20);
			ChangeCharacterComplexReputation(PChar,"nobility", -3);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_3_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "6");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			ChangeCharacterComplexReputation(PChar, "nobility", -6);
			AddCharacterExpToSkill(PChar, "Leadership", -50);
			AddCharacterExpToSkill(PChar, "Fortune", -70);
			AddCharacterExpToSkill(PChar, "Sneak", 20);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			npchar.quest.BadMeeting = lastspeak_date;
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_4_1":
			if(rand(1) == 0) // Поверил.
			{
				dialog.text = "「ああ、」 "+GetSexPhrase("息子よ","娘よ")+"。あなたの言葉に深い悲しみを覚えましたが、絶望はしておりません。絶望は大罪ですから！ 主は私たちの信仰を強めるために、また新たな試練をお与えになったのです。";
				link.l1 = "アーメン、神父様……";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_2"; // Переход сюда, т.к. одно и тоже.
			}
			else
			{
				dialog.text = "そうだ、その聖杯こそ金と一緒に盗まれたものだ……だが……もしそれを持っているなら、なぜ金は戻ってこないんだ？かなりの大金だったし、 あの悪党どもがそんなに早く全部使い果たせるはずがないだろう…… "+GetSexPhrase("息子よ","娘よ")+"、霊的な導き手に嘘をつき、神の御前で神殿にて偽証することほど大きな罪はないと覚えておきなさい！";
				link.l1 = "聖父 "+NPChar.name+"、この花瓶を手に入れるために命を落としかけたんだぜ、お前を喜ばせたくてな。全部にどれだけ金を使ったかなんて、 言うまでもねえよ！";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1_2";
			}
			break;
			
		case "GenQuest_Church_2_Finally_Complete_1_4_1_2":
			dialog.text = "出ていけ、そして全能の神に感謝しろ。俺に寛大な心を授けてくださったからこそ、 お前がまだ盗人や悪党として扱われていないんだぞ！";
			link.l1 = "それはどういうことだ！？ "+LinkRandPhrase("「聖なる父」","Padre","Father")+"!..";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1_2_1";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_4_1_2_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -5);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_12");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.quest.BadMeeting = lastspeak_date;
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_1":
			DialogExit();
			iMoneyToCharacter = PChar.GenQuest.ChurchQuest_2.MoneyToCharacter;
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			AddMoneyToCharacter(PChar, iMoneyToCharacter);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -1);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_11");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_1_1":
			dialog.text = "「ああ、」 "+GetSexPhrase("息子よ","娘よ")+"。あなたの言葉に私は深い悲しみに沈みました――しかし絶望はしません、絶望は大罪ですから！主は私たちの信仰を強めるために、 また新たな試練をお与えになったのです。";
			link.l1 = "アーメン、神父様……";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_2";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_8");
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_2_1":
			dialog.text = "主よ、感謝いたします！本当に、あなたは御方の御手となったのですよ、わが子よ！天の父があなたに道を示し、 必要な助けを与えてくださると私は信じていました。私は絶えず祈っておりました、そして…";
			link.l1 = "なあ、神父さん、こういう時は祈りよりも武器の方が役に立つもんだぜ。\nだが、どうやらあんたの祈りもちゃんと届いたらしいな。";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_2";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_2_2":
			dialog.text = ""+GetSexPhrase("息子よ","娘よ")+"、ちゃんと報酬を渡したいんだ、お前に"+GetSexPhrase("、まさに聖母教会の真の騎士のように、","")+" 自分の力の限りを尽くして乗り越えようとした…";
			link.l1 = "神父様、私のささやかな功績を本当に大げさにおっしゃいますね。これで私は失礼しますので、 どうぞ主を讃えていてください…";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_3";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_2_3":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", 5);
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_2.MoneyCount));
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "4");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
		// <-- квесты церкви

		case "donation":
			dialog.Text = "「もちろん」 "+GetSexPhrase("息子よ","娘よ")+"。聖なる教会にいくら寄付なさいますか？";
			Link.l1 = "申し訳ありません、神父様、しかし考えが変わりました。";
			Link.l1.go = "No donation";
			if(makeint(PChar.money)>=100)
			{
				Link.l2 = "私の寄付は控えめなものだ――たったの100ペソさ。";
				Link.l2.go = "donation paid_100";
			}
			if(makeint(PChar.money)>=1000)
			{
				Link.l3 = "1000ペソだ。それで十分だと思うぜ。";
				Link.l3.go = "donation paid_1000";
			}
			if(makeint(PChar.money)>=5000)
			{
				Link.l4 = "俺は金運がいいから、5,000ペソを寄付するぜ。";
				Link.l4.go = "donation paid_5000";
			}
			//-->> квест пожертвования хозяйки борделя
			if(pchar.questTemp.different == "HostessChurch_toChurch" && pchar.questTemp.different.HostessChurch.city == npchar.city && sti(pchar.money) >= sti(pchar.questTemp.different.HostessChurch.money))
			{
				Link.l5 = "神父様、今回は自分のためではなく、他の方の依頼で寄付をしたいのです。";
				Link.l5.go = "HostessChurch";
			}
			//<<-- квест пожертвования хозяйки борделя
		break;

		case "No donation":
			dialog.Text = "ふむ……まあ、これはあなたの決断ですし、気が変わっても構いません。そして、 最後の審判の日にはこれも考慮されることを忘れないでください。";
			Link.l1 = "他にもいろいろなことがそうなるさ。話題を変えよう。";
			Link.l1.go = "node_3";
			Link.l2 = "申し訳ありません、神父様、でももう出発しなければなりません。";
			Link.l2.go = "exit";
		break;

		case "donation paid_100":
			AddMoneyToCharacter(pchar, -100);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 100;
			dialog.Text = "聖なる教会を代表して、感謝いたします。 "+GetSexPhrase("息子よ","娘よ")+"、贈り物をありがとうございます。";
			Link.l1 = "「お話ししたいことがあります、神父様。」";
			Link.l1.go = "node_3";
			Link.l2 = "申し訳ありません、神父様、でももう出発の時間です。";
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "donation paid_1000":
			AddMoneyToCharacter(pchar, -1000);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 1000;
			dialog.Text = "聖なる教会を代表して、感謝いたします。";
            Link.l1 = "「お話ししたいことがあります、神父様。」";
			Link.l1.go = "node_3";
			Link.l2 = "申し訳ありません、神父様、でももう出発しなければなりません。";
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "donation paid_5000":
			AddMoneyToCharacter(pchar, -5000);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 5000;
			dialog.Text = "聖なる教会を代表して、あなたの贈り物に感謝いたします。";
            Link.l1 = "「お話ししたいことがあります、神父様。」";
			Link.l1.go = "node_3";
			Link.l2 = "申し訳ありません、神父様、でもそろそろお暇しなければなりません。";
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "ispoved":
			dialog.text = "「もちろん」 "+GetSexPhrase("息子よ","娘よ")+"、話を聞こう。";
			link.l1 = "気が変わった。次の機会にしよう。";
			link.l1.go = "exit";
			link.l2 = "私は罪深い人間です、神父様。私の悪事をすべて挙げるには一日では足りません……";
			link.l2.go = "ispoved_1";
		break;

		case "ispoved_1":
			dialog.text = "我々は皆、罪人なのだよ、子よ……";
			link.l1 = "ああ、しかし、俺の良心には何千もの死の重みがのしかかっているんだ。俺は船を襲い、沈めてきた……";
			link.l1.go = "ispoved_2";
		break;

		case "ispoved_2":
			dialog.text = "「その旗の下で航海した者たちの中に誰もいなかったことを願う」 "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "いいえ、もちろん違います、神父様。";
			link.l1.go = "ispoved_3";
			link.l2 = "いろんな奴らですよ、神父様……";
			link.l2.go = "ispoved_4";
		break;

		case "ispoved_3":
			dialog.text = "それなら主がその罪をお赦しくださるでしょう。この時代は残酷ですから、あなたが主君の敵を滅ぼすことで、 忠実な臣民たちの命を救っているのです。";
			link.l1 = "ありがとうございます、神父様、とても慰められました……それでは、これで失礼します。";
			link.l1.go = "exit";
		break;

		case "ispoved_4":
			dialog.text = "主はそのような罪をお許しにはならぬぞ！祈り、悔い改めよ、悔い改めて祈れ！今のお前に残された道は一つ――修道院へ行くことだ！";
			link.l1 = "修道院は後回しだな。少なくとも今生では無理だ。さらば……";
			link.l1.go = "exit";
			npchar.quest.BadMeeting = lastspeak_date;
		break;

        case "work":
        	if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.AskOwner") && NPChar.location == PChar.GenQuest.ChurchQuest_1.ToColony + "_church")
        	{
        		dialog.text = "申し訳ない。 "+GetSexPhrase("息子よ","娘よ")+"、しかし今はすべての告解室が埋まっております。早くてもあと30分ほどであなたの告解をお聞きできます。";
				link.l1 = "「失礼します」 "+RandPhraseSimple("神父","Father")+"、これは別の話だ。神父 "+PChar.GenQuest.ChurchQuest_1.PriestName+"、から "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown+"Gen")+"、かつて神学図書館の貴重な宝をあなたに託した者です。彼はそれらを返してほしいと私に頼みました。";
				link.l1.go = "GenQuest_Church_1_Dialog_1";
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.AskOwner");
				break;
        	}
			dialog.text = "「どんな用件でここに来たんだ、」 "+GetSexPhrase("息子よ","娘よ")+"?";
			link.l1 = "「一つお聞きしたいことがあるんだ、神父様……」";
			link.l1.go = "quests"; // ссылка к НПС
            link.l2 = RandPhraseSimple("「教会のために働くことについて話したかったんだ」 "+NationNameGenitive(sti(NPChar.nation))+".","教区の様子はどうだ？何か手伝いが必要か？");
			link.l2.go = "prihod";
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
	            link.l3 = RandPhraseSimple("Padre","Father")+"、金銭のことについて話したいんだ。"; //(пересылка в кредиты)
	            link.l3.go = "LoanForAll";
            }
			// -->
            if (stf(pchar.Health.HP) < 60.0)
            {
                link.l4 = "治療が必要だ。";
                link.l4.go = "healthAdd_1";
            }
            
			//квест мэра - на связь с нашим шпионом
			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "")
			{
	            link.l7 = RandPhraseSimple("Padre","「聖父」")+"、俺はある男の頼みでここに来た。その名は総督だ "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".";
	            link.l7.go = "IntelligenceForAll";
            }
			//--> Jason Церковная депеша
			if (CheckAttribute(pchar, "GenQuest.Monkletter") && npchar.city == pchar.GenQuest.Monkletter.City)
			{
	            link.l10 = "神父様、町の修道士から書類をお持ちしました "+XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.StartCity)+".";
	            link.l10.go = "Monkletter";
            }
			//<-- Церковная депеша
			//--> Jason Доставка молитвенников
			if (CheckAttribute(pchar, "GenQuest.Churchbooks") && pchar.GenQuest.Churchbooks == "go" && sti(npchar.nation) == sti(pchar.GenQuest.Churchbooks.Nation) && npchar.city != pchar.GenQuest.Churchbooks.StartCity)
			{
	            link.l11 = "神父様、私は植民地から来ました "+XI_ConvertString("Colony"+pchar.GenQuest.Churchbooks.StartCity)+"。地元の教会ではもっと祈祷書が必要でして、この件については地元の修道士があなたに相談するよう勧めてくれました。 ";
	            link.l11.go = "Churchbooks";
            }
			if (CheckAttribute(pchar, "GenQuest.Churchbooks") && pchar.GenQuest.Churchbooks == "return" && npchar.city == pchar.GenQuest.Churchbooks.StartCity)
			{
	            link.l11 = "神父様、あなたの教区のために祈祷書を持ってきました。";
	            link.l11.go = "Churchbooks_2";
            }
			//<-- Доставка молитвенников
			link.l99 = "気が変わった、やることが山ほどあるんだ。";
			link.l99.go = "exit";
		break;

		case "prihod":
			if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.StartQuest") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_2.StartQuest") && NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam != iMonth && NPChar.GenQuest.ChurchQuest_1.GiveQuestDay != lastspeak_date && NPChar.location != "Panama_church" && rand(5) == 1)
		    {
		        dialog.text = "それは素晴らしい。しかし、この暗い時代にも、 "+GetSexPhrase("息子よ","娘よ")+"「すべての寺院の訪問者が我らが聖母教会の役に立つわけではありません。」";
				link.l1 = LinkRandPhrase("Father","Padre","Father")+"、私は真のキリスト教徒であり、聖母教会に仕えるという私の意思は誠に真摯なものです。"+GetSexPhrase(" 彼女を支えるのは、俺のような忠実な騎士以外に誰がいるんだ？","")+"";
				link.l1.go = "GenQuest_Church_1_Start_1";
				NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = iMonth; // Предлагает квест не чаще раза в месяц
		    }
			else
			{
				NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = lastspeak_date;	// Если не дал сегодня, то токо на след день.
			}	
            dialog.text = "「今のところ教区は静かだ」 "+GetSexPhrase("息子よ","娘よ")+"。申し出に感謝します。";
    		link.l2 = "「まあ、問題なければ、俺は自分の用事に戻るとするか。」";
    		link.l2.go = "exit";
			DeleteAttribute(npchar, "quest.add");
			NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = lastspeak_date;	// Если не дал сегодня, то токо на след день.
		break;
		
		// Church GenQuest_1 -->
		case "GenQuest_Church_1_Start_1":
			dialog.text = "さて、私には繊細な任務があるのです。それには純粋な意志だけでなく、 大いなる勇気とかなりの慎重さも必要なのですよ…";
			link.l1 = LinkRandPhrase("Father","Padre","Father")+"、どんなご用でも喜んでお引き受けしますぜ、たとえそのために地獄へ突っ込むことになろうとも！ 俺の不敬な言葉を神よ、お許しください。";
			link.l1.go = "GenQuest_Church_1_Start_2";
		break;
			
		case "GenQuest_Church_1_Start_2":
			PChar.GenQuest.ChurchQuest_1.QuestTown = NPChar.City;
			Church_GenQuest1_InitStartParam(NPChar);
			dialog.text = "おお！よかった……しかし、またしても、これはとても繊細な問題でして……少し前に、修道院長が "+PChar.GenQuest.ChurchQuest_1.ToName+" から "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.ToColony+"Gen")+" 上 "+XI_ConvertString(PChar.GenQuest.ChurchQuest_1.ToIsland+"Voc")+"しばらくの間、教会の図書館から神学書や古い写本を何冊か私のために借りてくれました。大司教が 「知識という素晴らしい光の普及を妨げてはならぬ」と強く主張してくださったため、私は断ることができませんでした。 ですが、海の旅の苦労を思えば、彼が写本を期日通りに返せるとは思えません……この問題の解決に力を貸していただけませんか？";
			link.l1 = "「恐れ入りますが、」 "+LinkRandPhrase("Father","神父","聖なる神父")+"、それはあなたのためにはできません。これは非常に繊細な案件でして、本物の外交官だけが解決できるでしょう。";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Father","Padre","Father")+"、お前の任務は俺にはそんなに難しくは見えねえな。すぐに向かうぜ。";
			link.l2.go = "GenQuest_Church_1_Start_3";
		break;
			
		case "GenQuest_Church_1_Start_3":	// Квест взят
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.StartQuest = true;
			PChar.GenQuest.ChurchQuest_1.PriestName = NPChar.name;
			PChar.GenQuest.ChurchQuest_1.Nation = sti(NPChar.nation);
			PChar.GenQuest.ChurchQuest_1.AskOwner = true;
			sQuestTitle = NPChar.City + "ChurchGenQuest1";
			ReOpenQuestHeader(sQuestTitle);
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "1");
			AddQuestUserDataForTitle(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			AddQuestUserData(sQuestTitle, "sOwnerCity", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Gen"));
		break;
			
		case "GenQuest_Church_1_Dialog_1":
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.2A_Scene"))	// Сцена 2а
			{
				dialog.text = "「あっ！そうだ…確かに、今思い出した…でも、」 "+GetSexPhrase("息子よ","娘よ")+"、これらの宝は物質的なものよりも精神的な価値があるのです！すでに私の教区民たちに大いに役立ちましたし、 今後もきっと役立つことでしょう！";
				link.l1 = "しかし、 "+LinkRandPhrase("Father","Padre","Father")+"、神父の信徒たち "+PChar.GenQuest.ChurchQuest_1.PriestName+" 「救済を必要としているのは同じであり、これらの行いがなければ、神学の柱の支えを失い、 彼の説教にも霊感が欠けることになる。」";
				link.l1.go = "GenQuest_Church_1_Dialog_1_1";
			}
			else	// Сцена 2б-а и 2б-б
			{
				dialog.text = "ああ、そうだな！…本当に… "+GetSexPhrase("息子よ","娘よ")+"、これらの宝は物質的というより精神的なものなのです！すでに私の教区民たちに大いに役立っておりますので、 恥ずかしながら、正当な持ち主に返すのを「うっかり」忘れてしまいました……";
				link.l1 = "「確かに」 "+RandPhraseSimple("Father","Padre","Father")+"、確かに。そのために神父が "+PChar.GenQuest.ChurchQuest_1.PriestName+" これらの本を本人に直接届けてほしいと頼まれた。";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2";
			}
		break;
			
		case "GenQuest_Church_1_Dialog_1_1": // Сцена 2а
			dialog.text = "わかりますよ、我が子よ。しかし、私たちは毎日主にこう祈っているではありませんか。「我らの罪をお赦しください。 我らもまた、我らに罪を犯す者を赦します」と。そしてこの教会は\n "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown+"Gen")+" 俺のつつましい教区よりも裕福だ。";
			link.l1 = "確かにその通りです、神父様。しかし、今ふと思い出した聖書の別の一節があります。「安易な道を求めるな、 そこにこそ悪魔が待ち受けている。その声はより巧妙になり、道が易しければ易しいほど誘惑は強くなる！」 そして神父様\n "+PChar.GenQuest.ChurchQuest_1.PriestName+" あなたの物忘れについて大司教に手紙を送ろうとしていたところだった――なんとか思いとどまらせることができた。";
			link.l1.go = "GenQuest_Church_1_Dialog_1_1_1";
		break;
			
		case "GenQuest_Church_1_Dialog_1_1_1":
			dialog.text = "「だ、大司教様のところへ？！こんな些細なことで…！なぜだ？本当に？私はこれらの著作をいずれにせよ、キリストにある最愛の兄弟に送るつもりだったのだ――ただ、彼に届ける良い機会がなかっただけだ。だが、あなたに、」 "+GetSexPhrase("息子よ","娘よ")+"、私は本当に主にふさわしい忠実なしもべを見ております。さあ、これらの書物と写本を受け取って、 どうか神父様にお届けください "+PChar.GenQuest.ChurchQuest_1.PriestName+" 無事で何よりだ。それに加えて、心からの感謝を伝えたい。";
			link.l1 = "「もちろん」 "+LinkRandPhrase("Father","Padre","Father")+"……もちろん……";
			link.l1.go = "GenQuest_Church_1_Dialog_1_1_2";
		break;
			
		case "GenQuest_Church_1_Dialog_1_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.Complete.Short = true;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "2");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			// Предмет "рукопись" -->
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			// <-- Предмет "рукопись"
		break;
			
		case "GenQuest_Church_1_Dialog_1_2":	// Сцена 2б-а и 2б-б
			// Генерим кэпа -->
			sld = GetCharacter(NPC_GenerateCharacter("ChurchGenQuest1_Cap", "mercen_" + (rand(14)+14), "man", "man", 15, NPChar.nation, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 40, 35, "blade_13", "pistol3", "grapeshot", 30);
			FantomMakeCoolSailor(sld, 7 + rand(2), "", CANNON_TYPE_CANNON_LBS16, 75, 70, 65);
			sld.Abordage.Enable = false;
			sld.ShipEnemyDisable  = true; // флаг не обижаться на выстрелы
			LAi_SetImmortal(sld, true);
			sld.Dialog.FileName = "GenQuests_Dialog.c";
			sld.Dialog.CurrentNode = "ChurchGenQuest_1_DeckDialog_1";
			Group_FindOrCreateGroup("ChurchGenQuest1_CapGroup");
			Group_AddCharacter("ChurchGenQuest1_CapGroup", "ChurchGenQuest1_Cap");
			Group_SetType("ChurchGenQuest1_CapGroup", "trade");
			Group_SetGroupCommander("ChurchGenQuest1_CapGroup", "ChurchGenQuest1_Cap");
			Group_SetTaskNone("ChurchGenQuest1_CapGroup");
			Group_LockTask("ChurchGenQuest1_CapGroup");
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.CurPortManColony = "";
			PChar.GenQuest.ChurchQuest_1.CapFullName = GetFullname(sld);
			PChar.GenQuest.ChurchQuest_1.CapShipName = sld.Ship.Name;
			PChar.GenQuest.ChurchQuest_1.NoCapColony = NPChar.city;
			PChar.GenQuest.ChurchQuest_1.CapColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
			// <-- Генерим кэпа
			
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.2BA_Scene")) // Сцена 2б-а
			{
				dialog.text = "しかし、 "+GetSexPhrase("息子よ","娘よ")+"…実はな、先週俺は船『"+sld.Ship.Name+"「……そこで死にかけていた水夫に聖餐を授けるよう呼ばれました。大変嬉しいことに、船長」 "+GetFullName(sld)+" 「彼は～へ行くつもりだと私に言った」 "+XI_ConvertString("Colony"+GetColonyExpect2Colonies(NPChar.city,PChar.GenQuest.ChurchQuest_1.QuestTown))+"。そして、奴は何の条件も受ける資格がなかったが、それでも協力を承諾し、「港」 のことは任せてくれると保証してくれた "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown+"Gen")+" 彼はきっと訪れるでしょう。だから私はこの機会を利用して、その親切な方に本を託し、 今後の運命を主にお任せしました。";
				link.l1 = "ふむ、この船長は本当に信用できるのか？彼は託された品々の価値と、この任務の重要性を理解しているのか？";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2_1";
			}
			else // Сцена 2б-б
			{
				dialog.text = "「ああ、」 "+GetSexPhrase("息子よ","娘よ")+"！お前は数時間遅かったな！父上の本はもう送ってしまったぞ "+PChar.GenQuest.ChurchQuest_1.PriestName+" 船長と一緒に "+PChar.GenQuest.ChurchQuest_1.CapFullName+"。今朝、あの敬虔な男が告解に来て、今日自分の船が出航することを話していたんだ\n "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.CapColony)+"。そして船長は何の条件も必要なかったが、それでも助けることに同意し、さらに港のことを保証してくれた "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown+"Gen")+" きっと訪れるだろう。";
				link.l1 = LinkRandPhrase("Father","Padre","Father")+"…本当にこの船長を信用しても大丈夫なのか？それと、彼の船の名前も知りたいんだ。";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_1";
			}
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_1":	// 2б-а
			dialog.text = "俺は人を信じてるぜ。 "+GetSexPhrase("息子よ","娘よ")+"「我ら一人ひとりが主の御姿と似姿に創られ、その聖なる炎がすべての魂に燃えておるのじゃ！」";
			link.l1 = "ううむ。それは確かに重い理屈だな。まあ……それじゃあ、神父様、俺に祝福をくれよ。そしてあの船長を探す俺に幸運を祈ってくれ。";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_1_1";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_1_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = NPChar.city;
			PChar.GenQuest.ChurchQuest_1.CapFullInfo = true; // Полная инфа о кэпе
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "3_1");
			AddQuestUserData(sQuestTitle, "sCapName", PChar.GenQuest.ChurchQuest_1.CapFullName);
			AddQuestUserData(sQuestTitle, "sShipName", PChar.GenQuest.ChurchQuest_1.CapShipName);
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_1":
			dialog.text = "人を信じるべきだぜ "+GetSexPhrase("息子よ","娘よ")+"。彼の船については、俺から言うことは何もねえ。";
			link.l1 = "しかも、お前はその船の名前すら知らずに、貴重な写本をどこかの船長に渡したのか？！！";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_2";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_2":
			dialog.text = "「ご覧の通り、」 "+GetSexPhrase("息子よ","娘よ")+"、船長 "+PChar.GenQuest.ChurchQuest_1.CapFullName+" とても神を畏れる…";
			link.l1 = "もうそれは聞いたぜ。";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_3";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_3":
			dialog.text = "「我慢だ」 "+GetSexPhrase("若者","お嬢さん")+"「おい！船長」 "+PChar.GenQuest.ChurchQuest_1.CapFullName+" 非常に敬虔な人物で、今日まで彼の船には聖職者が口にしてはならぬ、 いや心の中でさえ思ってはならぬ名が付けられていたのです！ましてや声に出すなどもってのほかです！ そして今日の告解の際に、私はそのことを彼に指摘しました。なぜなら聖書にもある通り、 魂の清らかさは肉体の清らかさ以上に、我々罪人が守らねばならぬものであり、 主は汚れた言葉を使う者に御国をお与えにならないのですから……";
			link.l1 = "なるほど。 "+LinkRandPhrase("Father","Padre","Father")+"、なるほど！ "+PChar.GenQuest.ChurchQuest_1.CapFullName+"カリブ中で悪名高い賭博師であり大酒飲みの奴が、あなたの提案で自分のオンボロ船の名前を変えることにしたのか？";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_4";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_4":
			dialog.text = "「お前はなかなか鋭いな」 "+GetSexPhrase("息子よ","娘よ")+"。俺はこの船の新しい名前は知らねえが、きっと高貴な何かに違いねえ。";
			link.l1 = "「ああ、」 "+RandPhraseSimple("Father","Padre","Father")+"…すべてに感謝します。そして、私の罪深い魂のために祈ってください…";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_5";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_5":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = NPChar.city;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "3_2");
			AddQuestUserData(sQuestTitle, "sCapName", PChar.GenQuest.ChurchQuest_1.CapFullName);
		break;
			
		case "GenQuest_Church_1_Complete_1":
			dialog.text = "「ああ、我が子よ！私は熱心に祈っていたのだが、すべてが最善の形で解決したようだ！あなたの助けと信仰に感謝して、 」 "+GetSexPhrase("息子よ","娘よ")+"、楽園と天使の歌声がきっと待っているだろう…";
			link.l1 = RandPhraseSimple("神父。","「父上。」")+"、わしはまだしばらく聖ペテロに会うつもりはないぞ、神よお許しを。生きている者たちは、天国の約束だけじゃなく、 色々と現世の物も必要なんじゃ…";
			link.l1.go = "GenQuest_Church_1_Complete_2";
		break;
			
		case "GenQuest_Church_1_Complete_2":
			dialog.text = "「ああ、ああ、」 "+GetSexPhrase("息子よ","娘よ")+"、もちろんだ。お前には相応の報酬をやるぜ。ほら、これを受け取れ。そして、我らの主は地上の祝福を貪り、 黄色い悪魔を崇拝する愚かな魂を罰することを忘れるな！";
			link.l1 = "ありがとうございます。 "+LinkRandPhrase("Father","Padre","聖なる神父")+"。お待ちかねの本と写本をどうぞお受け取りになり、私の罪深い魂のために祈ってください……さらば！";
			link.l1.go = "GenQuest_Church_1_Complete_3";
		break;
			
		case "GenQuest_Church_1_Complete_3":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			RemoveItems(PChar, "Bible", 1);
			items[FindItem("Bible")].Name = "itmname_bible";
			BackItemDescribe("Bible");
			DeleteAttribute(items[FindItem("Bible")], "City");
			ChangeCharacterComplexReputation(PChar,"nobility", 5);
			AddCharacterExpToSkill(PChar, "Leadership", 50); // Бонус в авторитет
			AddCharacterExpToSkill(PChar, "Fortune", 50); // Бонус в удачу
			TakeNItems(pchar, "chest", 3+hrand(1));
			PlaySound("interface\important_item.wav");
			sQuestTitle = NPChar.City + "ChurchGenQuest1";
			characters[GetCharacterIndex("ChurchGenQuest1_Cap")].LifeDay = 0;
			Group_DeleteGroup("ChurchGenQuest1_CapGroup"); // Трем кэпа
			PChar.Quest.Church_GenQuest1_ChangeCapitanLocation.over = true; // Завершаем, если вдруг осталось
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "7");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			AddQuestUserData(sQuestTitle, "sSumm", FindRussianMoneyString(sti(PChar.GenQuest.ChurchQuest_1.AwardSumm)));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1");
			NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
			break;
		// <-- Church GenQuest_1

        case "healthAdd_1":
            if (stf(pchar.Health.maxHP) == 60.0) // отлично
            {
                dialog.text = "あなたの体調は "+GetHealthNameMaxSmall(pchar)+"、そして傷は自然に治るさ。流血を避けて、自分の体を大事にすることだ。";
    			link.l1 = "ありがとうございます、それは本当に安心しました。しばらくは喧嘩を控えるようにします。";
    			link.l1.go = "exit";
            }
            else
            {
    			dialog.text = "あなたの健康は "+GetHealthNameMaxSmall(pchar)+"、そして傷は自然に治るが、ちゃんと手当てしたほうがいいぞ。";
    			link.l1 = "それには何が必要だ？";
    			link.l1.go = "healthAdd_2";
			}
			link.l2 = "「それに、どうして俺の体調が悪くなってるんだ？」";
    		link.l2.go = "healthAdd_info";
		break;

		case "healthAdd_info":
			dialog.text = "「それはとても簡単だ」 "+GetSexPhrase("息子よ","娘よ")+"。傷を負うたびにダメージを受ける。そのことは見過ごされない。傷が増えるごとに体調が悪化し、その結果、 弱くなっていく。弱った船長を見た仲間たちは、お前への敬意を失う。しかし、その分だけ慎重になり、 一時的に自分を守る力が高まる。休息し、傷を避けることで強さを保てるぞ。";
			link.l1 = "ご教示いただき、ありがとうございます。";
			link.l1.go = "exit";
		break;

		case "healthAdd_2":
			dialog.text = "「祈りと暴力の自制」 "+GetSexPhrase("息子よ","娘よ")+"。そうすれば、主があなたの失ったものを返してくださるでしょう。";
			link.l1 = "でも、俺のために祈ってくれないか？";
			link.l1.go = "healthAdd_3";
			link.l2 = "そうか、方法はないのか？ふむ……本当に安心した、ありがとう。";
			link.l2.go = "exit";
		break;

		case "healthAdd_3":
            if (npchar.quest.HealthMonth != iMonth)
            {
    			dialog.text = "俺か？それは確かに可能だぜ。だが、うちの教区に寄付してもらわねえとな。";
    			link.l1 = pcharrepphrase("いくらだ？","喜んで！いくらだ？");
    			link.l1.go = "healthAdd_4";
    			link.l2 = "まあ、俺一人でもなんとかやっていけるだろう…";
    			link.l2.go = "exit";
			}
			else
			{
                dialog.text = ""+GetSexPhrase("息子よ","娘よ")+"、私はすでにあなたのご健康のために祈っております。この祈りは今月末まで私の時間をすべて費やすことでしょう。";
    			link.l1 = "ありがとうございます。 "+RandPhraseSimple("神父。","「聖なる神父。」");
    			link.l1.go = "exit";
			}
		break;

		case "healthAdd_4":
			dialog.text = "十万ペソあれば、癒しの奇跡への十分な報酬になるだろう。";
			link.l1 = pcharrepphrase("何だと！？お前、正気じゃねえのか？そんな大金、教会を二つ三つ襲ってからじゃねえと払えねえよ！","俺には高すぎるぜ。金で健康は買えないってのは本当らしいな。");
			link.l1.go = "exit";
            if (sti(pchar.Money) >= 100000)
            {
    			link.l2 = "同意だ！";
    			link.l2.go = "healthAdd_5";
			}
		break;

		case "healthAdd_5":
            AddMoneyToCharacter(pchar, -100000);
            AddCharacterMaxHealth(pchar, 4); // можно не проверять, тк явно меньше 51
            npchar.quest.HealthMonth = iMonth;
			dialog.text = "よろしい。少しは健康が回復します。しかし、まだ小競り合いを避け、自分の体を大切にしなければ、 この効果はすぐに消えてしまいます。あなたの朽ちゆく肉体のために、私は丸一ヶ月祈りを捧げなければなりません。";
			link.l1 = "ありがとう。何かあったら、また一か月後に会いに来るよ。";
			link.l1.go = "exit";
		break;
		
		//квест пожертвования хозяйки борделя
		case "HostessChurch":
			dialog.text = "「それで、その金を寄付してくれる親切な方は誰なんだ？」";
			link.l1 = "ふむ……あれはこの町の娼館の女主人だ。";
			link.l1.go = "HostessChurch_call";
			link.l2 = "できれば名前は伏せておきたいんだ。匿名で寄付することもできるだろう？";
			link.l2.go = "HostessChurch_notCall";
			pchar.questTemp.different = "HostessChurch_return"; //флаг на возвращение
		break;
		
		case "HostessChurch_call":
			if (isBadReputation(pchar, 5)) 
			{
				if (rand(100) < GetCharacterSkill(pchar, "Fortune")) //рендом вешаем на удачу
				{
					dialog.text = "お前は罪人なのに、さらに罪人を求めるのか？まずは自分の魂のことを考えた方がいいぞ。実のところ、我々 全員が主の御前に立つことになるのだからな！";
					link.l1 = "確かにそうですね。主が私に慈悲をお与えくださることを願っています……それで、寄付の件はいかがなさいますか？";
					link.l1.go = "HostessChurch_ok";
				}
				else
				{
					dialog.text = "「退け、サタンめ！！！その穢れた金を持ってさっさと出ていけ！」";
					link.l1 = "どうしてですか、神父様！？私たちは心を開いてあなたのもとに来たのに、あなたは……";
					link.l1.go = "HostessChurch_bad";
				}
			}
			else
			{
				if (rand(10) < GetCharacterSPECIAL(pchar, "Charisma")) //рендом вешаем на харизму
				{
					dialog.text = "あなたが罪人たちを我らの主のもとへ導く手助けをしてくれて嬉しく思います。その働きにより、 天国でしかるべき報いを受けるでしょう！";
					link.l1 = "それはありがたいぜ！で、寄付の話はどうなってるんだ？";
					link.l1.go = "HostessChurch_ok";
				}
				else
				{
					dialog.text = "私は罪によって得られた金を受け取ることはできません。その堕ちた女に返しなさい。 "+GetSexPhrase("息子よ","娘よ")+"。金で神への道を見つけることは誰にもできない。";
					link.l1 = "彼女を拒むとは残念だな。本当に残念だ。";
					link.l1.go = "HostessChurch_bad_1";
				}
			}
		break;
		
		case "HostessChurch_notCall":
			if (rand(10) < GetCharacterSPECIAL(pchar, "Charisma"))
			{
				dialog.text = "この金を受け取るなんて、どこから来たものかも知らずに……";
				link.l1 = "はい、神父様、その通りです。どうか、心からのこの寄付をお受け取りください！";
				link.l1.go = "HostessChurch_ok_1";
			}
			else
			{
				dialog.text = "この金を受け取るってのか、どこから来たかも知らずに？頭がおかしいのか！？ もしこの金が血で汚れてたらどうするんだ！";
				link.l1 = "「神父様、お金というものはすべて血で汚れているのです……」";
				link.l1.go = "HostessChurch_bad_2";
			}
		break;

		case "HostessChurch_ok":
			dialog.text = "受け入れる。 "+GetSexPhrase("息子よ","娘よ")+"。そのことをお前の堕ちた女にでも言ってこい。";
			link.l1 = "わかった、神父さん。ありがとう。";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.HostessChurch.money));
			AddCharacterExpToSkill(pchar, "Fortune", 20);
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "yes";
		break;
		
		case "HostessChurch_ok_1":
			dialog.text = "受け入れる。 "+GetSexPhrase("息子よ","娘よ")+"。お前の恩人にそのことを伝えてくれ。";
			link.l1 = "わかった、神父。ありがとう。";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.HostessChurch.money));
			AddCharacterExpToSkill(pchar, "Fortune", 20);
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "yes";
		break;
		
		case "HostessChurch_bad":
			dialog.text = "地獄の落とし子め、出て行け！二度とここに顔を出すんじゃねえぞ！";
			link.l1 = "へっ、好きにしな。";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			npchar.quest.BadMeeting = lastspeak_date;
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;
		
		case "HostessChurch_bad_1":
			dialog.text = "これは私の決断だ。安らかに行きなさい。 "+GetSexPhrase("息子よ","娘よ")+".";
			link.l1 = "さらばだ、神父。";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;
		
		case "HostessChurch_bad_2":
			dialog.text = "それが貴様の考えか、冒涜者め！？今すぐ神殿から出て行け、二度とここに顔を出すんじゃないぞ！";
			link.l1 = "「ああ、そうかい？まあいい、俺は行くぜ……」";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			npchar.quest.BadMeeting = lastspeak_date;
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;

		//--> Jason Церковная депеша
		case "Monkletter":
			if (CheckAttribute(pchar, "GenQuest.Monkletter.Late"))
			{
				dialog.text = "この書類をまた見ることはほとんど諦めかけていたぞ。なぜそんなに時間がかかったのだ、息子よ？";
				link.l1 = "「それは……予想外の展開でした、神父様。」";
				link.l1.go = "Monkletter_1";
			}
			else
			{
				dialog.text = "この書類を待っていたんだ、息子よ。迅速な配達に感謝する。これらのコインを受け取って、私の祝福と共に行きなさい。 ";
				link.l1 = "ありがとうございます、神父様。聖なる教会のお手伝いができて光栄でした！";
				link.l1.go = "Monkletter_3";
			}
		break;
		
		case "Monkletter_1":
			dialog.text = "俺たちはみんな神の御手の中にいるんだ、息子よ……人は計画を立てるが、決めるのは神だ。そこの書類を渡して、安心して行きなさい。";
			link.l1 = "はい、どうぞ、神父さん。ご多幸を祈ります！";
			link.l1.go = "Monkletter_2";
		break;
		
		case "Monkletter_2":
			DialogExit();
			RemoveItems(PChar, "letter_church", 1);//заменить на нужный
			AddQuestRecord("Monkletter", "2");
			CloseQuestHeader("Monkletter");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			DeleteAttribute(pchar, "GenQuest.Monkletter");
		break;
		
		case "Monkletter_3":
			dialog.text = "神のご加護を、息子よ。全能なる御方が旅路でお前を見守ってくださるように！";
			link.l1 = "「さようなら、お父さま。」";
			link.l1.go = "Monkletter_4";
		break;
		
		case "Monkletter_4":
			pchar.quest.Monkletter_Over.over = "yes"; //снять таймер
			DialogExit();
			RemoveItems(PChar, "letter_church", 1);//заменить на нужный
			AddQuestRecord("Monkletter", "3");
			CloseQuestHeader("Monkletter");
			TakeNItems(pchar, "gold_dublon", 10+rand(5));
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 5);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			DeleteAttribute(pchar, "GenQuest.Monkletter");
			addLiberMisBonus();
		break;
		//<-- Церковная депеша
		
		//--> Jason Доставить молитвенники
		case "Churchbooks":
			dialog.text = "お前さんは俺たちから祈祷書を持っていくように言われたんだろう――あの教会のために "+XI_ConvertString("Colony"+pchar.GenQuest.Churchbooks.StartCity+"Gen")+"？そうか。三十冊の祈祷書の包みがある。受け取りなさい、息子よ。";
			link.l1 = "ありがとうございます、神父様。さようなら！";
			link.l1.go = "Churchbooks_1";
		break;
		
		case "Churchbooks_1":
			dialog.text = "ご旅行の道中、主があなたを見守ってくださいますように！平安のうちにお行きなさい…";
			link.l1 = "...";
			link.l1.go = "exit";
			AddQuestRecord("Churchbooks", "2");
			pchar.GenQuest.Churchbooks = "return";
			GiveItem2Character(pchar, "prayer_book");//поставить соотв.предмет
		break;
		
		case "Churchbooks_2":
			if (CheckAttribute(pchar, "GenQuest.Churchbooks.Late"))
			{
				dialog.text = "助けてくれてありがとう、息子よ、少し遅れてしまったがな。";
				link.l1 = "予想外の出来事で遅れてしまいました、神父様。";
				link.l1.go = "Churchbooks_3";
			}
			else
			{
				dialog.text = "助けてくれてありがとう、息子よ。君はちょうどいい時にこれらの本を持ってきてくれた。どうか、 この聖別されたお守りを報酬として受け取ってくれ――きっと最も危険な時に君を救ってくれるだろう。";
				link.l1 = "ありがとうございます、神父様。聖なる教会のお手伝いができて光栄でした！";
				link.l1.go = "Churchbooks_4";
			}
		break;
		
		case "Churchbooks_3":
			dialog.text = "すべては神の御手に委ねられている、息子よ。安らかに行きなさい！";
			link.l1 = "さようなら、神父。";
			link.l1.go = "exit";
			RemoveItems(PChar, "prayer_book", 1);//заменить на нужный
			AddQuestRecord("Churchbooks", "3");
			CloseQuestHeader("Churchbooks");
			DeleteAttribute(pchar, "GenQuest.Churchbooks");
		break;
		
		case "Churchbooks_4":
			dialog.text = "神のご加護を、息子よ。全能の神が道中の災いからお前を守ってくださいますように！";
			link.l1 = "「さようなら、お父さま。」";
			link.l1.go = "Churchbooks_5";
		break;
		
		case "Churchbooks_5":
			pchar.quest.Churchbooks_Over.over = "yes"; //снять таймер patch-5
			DialogExit();
			RemoveItems(PChar, "prayer_book", 1);//заменить на нужный
			GiveItem2Character(pchar, pchar.GenQuest.Churchbooks.Item);
			Log_Info("You have received '"+XI_ConvertString(pchar.GenQuest.Churchbooks.Item)+"'");
			AddQuestRecord("Churchbooks", "4");
			CloseQuestHeader("Churchbooks");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 1);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			DeleteAttribute(pchar, "GenQuest.Churchbooks");
			addLiberMisBonus();
		break;
	}
}

void ChurchGenQuest2_RemoveCup()
{
	RemoveItems(PChar, "Bible", 1);
	ref rItem = ItemsFromID("Bible");
	DeleteAttribute(rItem, "City");
	rItem.Weight = 2;
	rItem.Name = "itmname_Bible";
	rItem.picIndex = 6;
	rItem.picTexture = "ITEMS_9";
	BackItemDescribe("Bible");
}

void Church_GenQuest1_InitStartParam(ref chr)
{
	string sColony = SelectNotEnemyColony(chr); 
	PChar.GenQuest.ChurchQuest_1.IslandId = colonies[FindColony(PChar.GenQuest.ChurchQuest_1.QuestTown)].Island;
	PChar.GenQuest.ChurchQuest_1.ToColony = sColony;
	PChar.GenQuest.ChurchQuest_1.ToIsland = colonies[FindColony(sColony)].Island;
	PChar.GenQuest.ChurchQuest_1.ToName = characters[GetCharacterIndex(sColony + "_Priest")].Name;
	
	// Чтоб жизнь медом не казалась... Какие сцены будут в квесте, определяем в самом начале.
	int iRand = Rand(2);
	switch(iRand)
	{
		case "0":
			PChar.GenQuest.ChurchQuest_1.2A_Scene = true;
			Log_TestInfo("Church generator 1: key scene - 2A (just pick up the manuscript from the priest)."); 
		break;
		
		case "1":
			PChar.GenQuest.ChurchQuest_1.2BA_Scene = true;
			Log_TestInfo("Church generator 1: key scene - 2B-A (search for a cap. There is full information about him).");
		break;
		
		case "2": // Этот флаг уже не проверяем, т.к. если нет тех, что выше, по-любому есть этот
			PChar.GenQuest.ChurchQuest_1.2BB_Scene = true;
			Log_TestInfo("Church generator 1: key scene - 2B-B (search for a cap. The name of the ship is unknown)."); 
		break;
	}
}
