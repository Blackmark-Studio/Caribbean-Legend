// Жак Барбазон в Ле Франсуа
int iBarbazonTotalTemp;
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc, sTemp;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

//--> -----------------------------------------------блок angry-------------------------------------------------
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
					if (npchar.angry.name == "pirate_threat")
                    {
                        if (Dialog.CurrentNode == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                        else Dialog.CurrentNode = "AngryRepeat_1";
                    }
                break;
            }
        }
    }
//<-- -------------------------------------------блок angry------------------------------------------------------

	switch(Dialog.CurrentNode)
	{
	// ----------------------------------- Диалог первый - первая встреча---------------------------------------
		case "First time":
            if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("気でも狂ったのか？屠殺屋ごっこがしたかったのか？海賊どもはみんなお前に怒ってるぜ、坊主、 さっさとここから出ていったほうがいいぞ…","どうやらお前、頭がおかしくなったみたいだな、坊主。ちょっと腕を伸ばしたかったのか？悪いが、 ここはお前の来る場所じゃねえ。とっとと失せろ！");
				link.l1 = RandPhraseSimple("聞けよ、この状況を何とかしたいんだ…","この問題を解決するのを手伝ってくれ…");
				link.l1.go = "pirate_town";
				break;
			}
			
			link.l0 = ""+npchar.name+"、私は" + GetSexPhrase("","") + " 海での安全について話したいんだ。沿岸の兄弟団の連中が、私のつつましい身に過剰な興味を示しているんだ。 少し黙らせてもらえないか？";
			link.l0.go = "pirate_threat";
			
			dialog.text = NPCStringReactionRepeat("俺に言いたいことでもあるのか？ないのか？だったらさっさと失せろ！",
						"はっきり言ったはずだ、これ以上俺をイラつかせるな。","はっきり言ったはずだが、しつこく俺を苛立たせやがって！",
						"ああ、もうこの無礼にはうんざりだぜ。","repeat",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("もう行くぜ。",
						"ああ、"+npchar.name+"……",
						"悪いな、"+npchar.name+"…",
						"「いてっ……」",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			
		//----------------------------------Сага - искушение Барбазона---------------------------------------
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "begin")
			{
				link.l1 = "お前と話がある、ジャック……二人きりでな。";
				link.l1.go = "Temptation";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "give_silk" && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 60)
			{
				link.l1 = "俺はサン・マルタンから来たんだ、ジャック…";
				link.l1.go = "Temptation_6";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "terrax")
			{
				link.l1 = "「いつまで吠えてるつもりだ、ジャック？男らしく話す気はねえのか？俺が来るとは思わなかったか？」";
				link.l1.go = "terrax";
			}
			
			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
				{
					link.l1 = "囚人の件で来たんだ。";
					link.l1.go = "CapComission1";
					DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
				}
             	
				if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway") // лесник. новая проверка. искл. возможность сразу сдать задание,минуя 15 дней.
				{
					link.l1 = "やあ、Jacques、あんたの依頼で来たんだ。";
					link.l1.go = "CapComission3";
				}
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak") && !CheckAttribute(pchar,"GenQuest.CaptainComission.vikupzaplatil")) 
				{ // лесник . второй диалог с проверкой ,если ГГ ещё не принес деньги за выкуп.
					link.l1 = "囚人の件で来たんだ。";
					link.l1.go = "CapComission6";
				}
			}	
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin")
			{
				link.l1 = "囚人に関わる商売をやってるって聞いたぜ…";
				link.l1.go = "Marginpassenger";
			}
		break;
			

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
            if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("頭がおかしいのか？屠殺屋ごっこがしたかったのか？海賊どもはみんなお前に怒ってるぜ、坊主、 ここからさっさと消えたほうがいいぞ…","どうやら頭がおかしくなったみたいだな、坊主。ちょっと腕でも伸ばしたかったのか？悪いが、お前に用はねえ。 とっとと失せろ！");
				link.l1 = RandPhraseSimple("聞けよ、俺はこの状況を何とかしたいんだ…","「この問題を解決するのを手伝ってくれ……」");
				link.l1.go = "pirate_town";
				break;
			}
			
			link.l0 = ""+npchar.name+"、私は" + GetSexPhrase("","") + " 海での安全について話したいんだ。沿岸の兄弟団の連中が、私のつつましい身に過剰な興味を示しているんだ。 少し黙らせてもらえないか？";
			link.l0.go = "pirate_threat";
			
			dialog.text = NPCStringReactionRepeat(GetFullName(pchar)+"！今度は何の用だ？",
						"何か言い忘れたことでもあるのか？聞いてやるぜ。","いつまで続くんだ……やることがねえなら、他人の邪魔すんじゃねえ！",
						"お前は俺に礼儀正しくしろと言ったな。だが、俺も同じことをお前に要求するぜ！","repeat",10,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("たいしたことじゃねえ。ただの顔出しだ。",
						"「何も……」",
						"……いいだろう……",
						"あんたの言う通りだ。悪かったな。",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			
			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
			{
				link.l1 = "囚人の件で来たんだ。";
				link.l1.go = "CapComission1";
				DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
			}	
			if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway")//  правка лесник,новая проверка ,исключающая тут же сдачу задания
			{
				link.l1 = "やあ、Jacques、任務の件だ。";
				link.l1.go = "CapComission3";
			}
		/*	if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak")) //лишний диалог лесник
			{
				link.l1 = "囚人の件で来たんだ。";
				link.l1.go = "CapComission6";
			}*/
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin")
			{
				link.l1 = "囚人に関わる商売をやってるって聞いたぜ…";
				link.l1.go = "Marginpassenger";
			}
		break;

//--> -----------------------------------Сага - Искушение Барбазона---------------------------------------------
		case "Temptation":
			dialog.text = "俺にちょっかい出すのがどれだけ危険かわかってるか？\nまあいい、話を聞いてやる。";
			link.l1 = "俺には借金があるんだ。しかもでかい額だぜ。支払いの時がもうすぐ来るってのに、手元にゃ一文もねえ。親切な連中が、 お前は策を練るのが得意で、でかい山のありかもいつも知ってるって噂してたぞ…";
			link.l1.go = "Temptation_1";
		break;
		
		case "Temptation_1":
			dialog.text = "聞け、坊主！俺に忠実な奴にだけ、俺は“親切者ジャック”だ。他の奴らには“バルバゾン”、時にはルシファーそのものだぜ。お前を信用できるかどうか、どうやって分かるってんだ？";
			link.l1 = "やってみろよ。後悔はさせねえぜ！";
			link.l1.go = "Temptation_2";
		break;
		
		case "Temptation_2":
			dialog.text = "ふん…お前、ジャック・ザ・カインドマンが自分を騙した奴に何をするか知ってるだろうな？まあ、 細かいことは言わねえでおいてやる。ちょっとした仕事があるんだ。うまくやれば、 お前の金の悩みなんざ全部消し飛ぶぜ。";
			link.l1 = "俺を疑うな、俺はいろんな喧嘩をくぐり抜けてきたんだ、そして…";
			link.l1.go = "Temptation_3";
		break;
		
		case "Temptation_3":
			dialog.text = "黙って俺の話を聞け！数週間前、オランダの哨戒隊が俺の部下の一人をサン・マルタンの近くで捕まえやがった。 そいつはオランダ産の絹を俺に運んでたんだ。これは滅多に手に入らねえ代物でな、 オランダ野郎どもは会社の艦隊用に少量ずつしかここに持ち込まねえんだよ。\nそれで、俺はなんとか絹を六梱買い付けたんだが、サイモン・モレルが自分のブリガンティン「ソルト・ドッグ」 でそれを運ぶはずだった。だが、偶然かどうか知らねえが、途中でオランダの哨戒隊に出くわした。いや、 偶然じゃねえかもしれねえ。モレルの航海士がそう言ってた――奴は戦いで唯一生き残ったって俺に話したんだ。\nそいつはモレルの航海日誌も渡してくれた。それによれば、モレルは逃げる途中で絹を海に投げ捨てたらしい。 おかしいと思わねえか？絹なんて軽いもんだ。大砲を捨てるべきだったろうに、 どうせ哨戒隊には敵わなかったんだからよ。";
			link.l1 = "ここは本当に何かおかしいぜ。";
			link.l1.go = "Temptation_4";
		break;
		
		case "Temptation_4":
			dialog.text = "何でも可能だぜ。俺の下で働いてるのは勇敢な奴が多いが、賢い奴はずっと少ねえ。気を悪くするなよ、へっ。 モレルが積荷を処分した場所を自分で確かめろ。船長の日誌によれば、北緯21度10分、西経61度30分だ。\nオランダ野郎どもは絹をコルクの棒に巻きつけるから、梱包はまだ水面に浮いてるはずだ。梱包は六つある。 すぐに出航しろ、時間が命だぜ。";
			link.l1 = "今向かってるぜ！";
			link.l1.go = "Temptation_5";
		break;
		
		case "Temptation_5":
			DialogExit();
			SetFunctionTimerCondition("Saga_BarbTemptationOver", 0, 0, 10, false); // таймер
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			pchar.quest.BarbTemptation.win_condition.l1 = "location";
			pchar.quest.BarbTemptation.win_condition.l1.location = "SentMartin";
			pchar.quest.BarbTemptation.function = "Saga_BarbTemptationBarkas";
			pchar.questTemp.Saga.BarbTemptation = "silk";
			AddQuestRecord("BarbTemptation", "2");
		break;
		
		case "Temptation_6":
			dialog.text = "よし！俺の絹は見つけたか？";
			link.l1 = "ああ、六人だな、お前の言う通りだ。";
			link.l1.go = "temptation_wrong";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 90)
			{
				link.l2 = "ああ、そうだ。しかしお前が言ったより多かったぞ、六人じゃなくて九人だ。全員ここに連れてきたぜ。 どうしてこんなことになったのか考えるのはお前の役目だ。";
				link.l2.go = "temptation_right";
			}
		break;
		
		case "temptation_wrong":
			dialog.text = "間違った答えだな。九梱包あるはずだったんだぜ。六つ見つけたってんなら、残りも見つけたはずだろうが。つまり、 お前はネズミか、ただの怠け者のバカってことだ。俺に絹の梱包三つ分の借りがあるし、さらにもう三つ分は……「道義的補償」としてもらうぜ。俺を騙そうとした罰だ。";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 120)
			{
				link.l1 = "生意気な野郎だな！覚えておくぜ。ほら、絹だ。俺のミスのことは水に流そうじゃねえか。";
				link.l1.go = "temptation_wrong_1";
			}
			link.l2 = "六梱あったと聞いてる、それ以上は一つもねえ。見つけた分は全部渡したし、お前の考えなんざ知ったこっちゃねえ。 もう絹は持ってねえんだ。";
			link.l2.go = "temptation_wrong_2";
		break;
		
		case "temptation_wrong_1":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 120);
			dialog.text = "いいだろう。二度とこんなことが起きねえようにしろよ、俺はお前に大事な仕事を任せたいんだ。\nいくら稼ぎたいんだ？";
			link.l1 = "金はいつでも歓迎だ。今のところ五万ペソで十分だぜ。";
			link.l1.go = "junior";
		break;
		
		case "temptation_wrong_2":
			dialog.text = "おお、今度はそんな口をきくのか！このままじゃ済まさねえぞ。警告したはずだ、 俺を騙そうなんて血迷った真似はするなよ！\n衛兵ども！屋敷にクソったれのネズミが入りやがったぞ！";
			link.l1 = "くそっ！";
			link.l1.go = "temptation_wrong_fight";
		break;
		
		case "temptation_wrong_fight":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetWarriorType(npchar);
			ChangeCharacterAddressGroup(npchar, "LeFransua_townhall", "goto", "goto1");
			LAi_SetImmortal(npchar, true);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i = 1; i <= 3; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("BarbGuard_"+i, "citiz_4"+(i+6), "man", "man", 80, PIRATE, 1, true, "quest"));
				FantomMakeCoolFighter(sld, 80, 100, 100, "blade_21", "pistol4", "bullet", 3000);
				ChangeCharacterAddressGroup(sld, "LeFransua_townhall", "reload", "reload1");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "temptation_right":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 80);
			dialog.text = "よくやったな。お前の強欲さを試していたんだが、見事に合格だ。梱包は九つあったはずだ。 そのうち一つはお前のものだ。さて、本題に入ろう。いくら金が必要なんだ？";
			link.l1 = "金はいつでも歓迎だが、今は五万ペソで十分だ。";
			link.l1.go = "junior";
		break;
		
		case "junior":
			dialog.text = "もっと稼ぐチャンスがあるぜ。ある旦那が、あんたみたいに信頼できる奴を、 繊細で危険な仕事のために探してくれと俺に頼んできたんだ。その男はとんでもなく金持ちでな、 期待を裏切らなければそれ相応の報酬をくれるだろうよ。";
			link.l1 = "俺は準備できてるぜ。";
			link.l1.go = "junior_1";
		break;
		
		case "junior_1":
			dialog.text = "いいだろう。よく聞け。あいつの手下で『ナーヴ』って名のやつを探せ。そいつはポラッカ船『マーリン』の船長だ、 それしか知らねえ。カプスターヴィルで見つかるはずだ。合言葉は『狩りが始まった』だ。それを言えば、 やるべきことを教えてくれる。俺には借りなんてねえ。ただお前を助けたいだけだ。運が良けりゃ、 また会うこともあるだろう。";
			link.l1 = "助けてくれて感謝するぜ。これから向かうぞ！";
			link.l1.go = "junior_2";
		break;
		
		case "junior_2":
			DialogExit();
			AddQuestRecord("BarbTemptation", "7");
			Saga_SetJuniorInCharles(); // ставим Валета
			pchar.questTemp.Saga.BarbTemptation = "valet";
		break;
		
		case "terrax":
			dialog.text = "「なんだと！？てめえの…引き裂いてやるぞ…」";
			link.l1 = "お前にはできねえよ、バルバゾン。さあ、手札を見せてもらおうか！俺はヤン・スヴェンソンのために働いてるんだ。 お前とジャックマンの陰謀は全部暴いたぜ。お前らが何を企んでたか、そしてお前自身の役割も全部知ってる。 ジャックマンとその弟はもう死んだ。兄貴はブレイズ・シャープを殺して自分の運命を決めちまったし、 弟の方は残念ながら口が重すぎたな……";
			link.l1.go = "terrax_1";
		break;
		
		case "terrax_1":
			dialog.text = "くそっ！タイレックスは絶対に俺を許さねえだろうが、俺はまだ……";
			link.l1 = "バカな真似はするなよ、ジャック。こんな話が簡単に済むとは思っちゃいなかったからな、ちゃんと手は打ってあるぜ。 窓を見てみろ……お前の小屋は俺の銃士たちに囲まれてる。俺の手下は村中にいるし、突撃隊が門の外で待機してるんだ。 虐殺を始めたいのか？そんなの簡単にできるぜ！";
			link.l1.go = "terrax_2";
		break;
		
		case "terrax_2":
			dialog.text = "くたばれ！何の用だ？";
			link.l1 = "信じられねえだろうがな、バルバゾン。だが俺が欲しいのは……平和だけだ！俺は平和が欲しいんだ。だからこそ、タイレックスにはお前がこの陰謀に関わってることは言わねえ。 だがな、俺の言うことを聞くなら……だぜ。";
			link.l1.go = "terrax_3";
		break;
		
		case "terrax_3":
			dialog.text = "俺に何の用だ？金か？いくら欲しいんだ？";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) // Акула жив
			{
				link.l1 = "おいおい、頭の悪い手下どもに任せておけってか。俺が欲しいのは違うもんだ。 スティーブン・ドッドソンにお前の票が必要なんだよ。";
			}
			else
			{
				link.l1 = "ああ、違う、そんな脳なしの手下どもに任せておけ。俺が欲しいのは別のものだ。 マーカス・タイレックスに投票してほしいんだよ。";
			}
			link.l1.go = "terrax_4";
		break;
		
		case "terrax_4":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "And Steven Dodson is on our side.";
			else sTemp = "";
			dialog.text = "本気か？ちょっと考えさせろ……で、もし俺が断ったらどうするんだ？";
			link.l1 = "なら、お前は一人で立つことになるぜ。完全に一人だ。スヴェンソンもタイレックスもホークもお前に敵対するだろうよ。 "+sTemp+"俺が見せるのは、あの悪党の手紙とジャックマンの弟だけだ。俺の言葉も信用されるだろうさ。さて、 その後でお前がどれだけ楽に座っていられると思う？";
			link.l1.go = "terrax_5";
		break;
		
		case "terrax_5":
			dialog.text = "ホーク？あいつが生きてるのか！？";
			link.l1 = "ああ、そうだ。俺がジャックマンの仕掛けた罠から奴を救い出したんだ。だからジェイコブの一番の親友が、 今度は奴の仇になるってわけだ。そして俺もそいつらに加わる。覚えておけよ、バルバゾン。";
			link.l1.go = "terrax_6";
		break;
		
		case "terrax_6":
			dialog.text = "ジャックマンは俺の友達じゃねえ！くそっ！てめえ、俺を追い詰めやがって！";
			link.l1 = "馬鹿なことを言うな。俺が言った男に票を入れれば、お前には何も変わらねえ。もう言ったはずだ、ジャック、 俺は平和を望んでる。俺は全てのバロンどもにお前を憎ませることもできるが……まだやらねえよ。";
			link.l1.go = "terrax_7";
		break;
		
		case "terrax_7":
			GiveItem2Character(pchar, "splinter_jb"); // дать осколок
			dialog.text = "いいだろう。わかった。俺の言葉を信じろ。ほら、俺の石のかけらを持っていけ、お前が必要なんだろ？";
			link.l1 = "その通りだ。合意に至って嬉しいぜ、ジャック。あと「ナーヴ」の手紙はいい思い出として持っていけ。いや、 むしろ燃やした方がいいな――見つかったら面倒だろうからな。ああ、それともう一つだけ……";
			link.l1.go = "terrax_8";
		break;
		
		case "terrax_8":
			RemoveItems(pchar, "letter_chad", 1);
			dialog.text = "「まだ何かあるのか？！他に俺に何を望んでやがる？」";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Barbazon"))
			{
				link.l1 = "ひとつ思い出させてやるぜ。そう遠くない昔、お前はイグナシオ・マルコっていう犬っころを俺の暗殺に差し向けたよな。 そいつを殺したのは俺だ。スペインの金貨ガレオン船を襲うお前の計画を潰したのも俺だ。 サン・マルタン近くでお前の仲間どもをスペインの待ち伏せに送り込んだのも俺だ。俺の名はチャーリー・プリンスだ！ これで終わりだ、ジャック。次に会うときはもう少し礼儀をわきまえろよ。信じろよ、「坊や」、俺たちはまた会うぜ――しかも一度や二度じゃ済まねえだろうな。";
				link.l1.go = "terrax_8_1";
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Barbazon") && CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
				{
					link.l1 = "一つ思い出させてやるぜ。つい最近、お前は自分の犬っころイグナシオ・マルコを俺の暗殺に送り込んできたな。 そいつを殺したのは俺だ。スペインの金貨ガレオン船を襲うお前の計画を潰したのも俺だ。 俺の名はチャーリー・プリンスだ！これで終わりだ、ジャック。次に会う時はもう少し礼儀をわきまえろよ。信じろよ、 「坊や」、俺たちはまた会うぜ、それも一度や二度じゃ済まねえ。忘れるな、カリブの海賊男爵どもはみんな俺の味方だ。 じゃあな、バルバゾン……";
					link.l1.go = "terrax_9";
				}
				else
				{
					link.l1 = "次に会うときはもっと礼儀正しくしろよ。信じろよ、「坊主」、俺たちはまた会うぜ、 しかも一度や二度じゃ済まねえだろうな。忘れるな、俺の味方には全ての海賊男爵がついてるんだ。じゃあな、 バルバゾン…\n";
					link.l1.go = "terrax_9";
				}
			}
		break;
		
		case "terrax_8_1":
			dialog.text = "";
			link.l1 = "忘れるなよ、俺には全ての海賊男爵が味方についてるんだぜ。じゃあな、バルバゾン…";
			link.l1.go = "terrax_9";
		break;
		
		case "terrax_9":
			DialogExit();
			NextDiag.CurrentNode = "I_know_you_good";
			AddQuestRecord("BarbTemptation", "26");
			if (CheckCharacterItem(pchar, "splinter_mt") && CheckCharacterItem(pchar, "splinter_jb") && CheckCharacterItem(pchar, "splinter_zm")) Saga_GiveCalendar();
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Saga_SGM_"+i);
				LAi_SetCitizenType(sld);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
				sld.lifeday = 0;
			}
			ChangeCharacterComplexReputation(pchar, "fame", 1);
			bDisableFastReload = false;
			LAi_LocationFightDisable(&Locations[FindLocation("LeFransua_town")], false);
		break;

//-----------------------------------Поручение капитана - Выкуп-------------------------------------------------
		case "CapComission1":
			dialog.text = "ハハッ。俺がここに囚人を一人しか捕まえてねえと思ってるのか？名前を言え。";
			link.l1 = pchar.GenQuest.CaptainComission.SlaveName+"……あいつはここにいるのか？";
			link.l1.go = "CapComission2";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
		break;

		case "CapComission2":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.DaysLeft"))
			{
				dialog.text = "ああ、そうだ。あいつは一週間前にここへ来ていたバルバドスのプランテーション主、ビショップ大佐に売ったんだ。";
				link.l1 = "くそっ……";
				link.l1.go = "CapComission2_1";
			}
			else
			{
				dialog.text = "ああ、やっと来たか。バルバドスのあのプランテーションの旦那にあいつを売ろうかと思ってたんだが、あいつは一、 二週間でここに来る予定だ……身代金は持ってきたのか？";
				link.l1 = "見ろよ、ちょっとした問題があってな……実は、そんなに金を持ってねえんだ。\nだが、働く気はあるぜ。";
				link.l1.go = "CapComission2_2";
				if(makeint(pchar.money) > 150000)
				{
					link.l2 = "売らずにいてくれて助かったぜ。ほら、これがお前の金だ――十五万ペソだ。そいつはどこにいる？";
					link.l2.go = "CapComission2_3";
				}	
			}
		break;
		
		case "CapComission2_1":
			dialog.text = "お前は遅すぎたな……それに、なんであいつのことなんか気にするんだ？俺が交渉してたのは、あいつの身内だけだぜ。";
			link.l1 = "奴らが俺にここへ来いと言いやがったんだ。";
			link.l1.go = "CapComission2_11";
		break;
		
		case "CapComission2_11":
			dialog.text = "ふん、遅かったな。俺にはどうしようもねえ。";
			link.l1 = "聞けよ、いくらであいつを売ったんだ？秘密じゃなけりゃ教えろよ。"; 
			link.l1.go = "CapComission2_12";
		break;
		
		case "CapComission2_12":
			dialog.text = "へっ、違うぜ。でも教えてやらねえよ……言ったらどうせ笑うだけだろ。ハハハハハ！じゃあな。";
			link.l1 = "じゃあな。";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", "Jacques Barbazon");//правка лесник.  в СЖ запись ниже не работает																																				  
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			CaptainComission_GenerateManager();
		break;
		
		case "CapComission2_2":
			if(rand(3) == 1)
			{

				dialog.text = "「さて、」 "+pchar.name+"、いいか、世の中そんな甘くねえんだよ。金を持って戻ってきたら、あの腑抜けを返してやるさ、ハハハ。";
				link.l1 = "ああ、じゃあな。";
				link.l1.go = "CapComission2_4";
			}
			else
			{
				dialog.text = "ほう、ほう……ちょっとした用があるんだがな……どう切り出すかもわからねえ。筋を越えた海賊を沈める必要があるんだ。";
				link.l1 = "ジャングルでそいつをぶっ殺すだけじゃダメなのか？";
				link.l1.go = "CapComission2_2_1";
			}
		break;

		case "CapComission2_2_1":
			dialog.text = "商売ってのはそういうもんじゃねえんだよ……あいつを殺す必要はねえが、俺の取り分を横取りしようとする連中には思い知らせてやらなきゃな。だが、 もしあいつがサメの餌になったとしても、別に気にしねえぜ。";
			link.l1 = "「なんで自分の手下を奴の後を追わせねえんだ？」";
			link.l1.go = "CapComission2_2_2";
		break;
		
		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			sLoc = XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Dat"); // belamour gen
			dialog.text = "ふむ……さて、 "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.UnknownPirateName,NAME_NOM)+" 何人かの海賊に、自分たちの取り分の戦利品がうちの隠し場所、すぐ近くに保管されていると信じ込ませた "+XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore+"Gen")+"。奴らの二隻の船『"+pchar.GenQuest.CaptainComission.ShipName1+"「と」"+pchar.GenQuest.CaptainComission.ShipName2+"「』はついさっき錨を上げて出航し、」 "+sLoc+"。これで俺が自分の手下どもにこの仕事を任せられねえ理由がわかっただろう？";
			link.l1 = "ああ、そうだ。俺にどれくらい時間がある？";
			link.l1.go = "CapComission2_2_3";
		break;
		
		case "CapComission2_2_3":
			dialog.text = "12日から15日、それ以上はダメだ。やつらが隠し場所にたどり着かないことが重要なんだ、 そうじゃなきゃ貴重な積荷ごと沈める意味がねえ。そうなったら、むしろここに持って来させた方がマシだな…";
			link.l1 = "よし、乗ったぜ。奴らを捕まえてみせる。";
			link.l1.go = "CapComission2_2_4";
		break;
		
		case "CapComission2_2_4":
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", "Jacques Barbazon");//правка
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));// в СЖ не работает имя . лесник
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Dat")); // belamour gen
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Voc")); // belamour gen
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips"; 
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);
			
			DialogExit();
		break;
		
		case "CapComission2_3":
			dialog.text = "心配すんな。俺の部下があいつをお前の船まで連れていくぜ。で、なんであいつのことなんか気にしてんだ？";
			link.l1 = "俺は知らねえ。あいつの親族に連れて来いと頼まれただけだ。";
			link.l1.go = "CapComission2_31";
		break;
		
		case "CapComission2_31":
			dialog.text = "ああ、それでいいんだ。お前の部下にあんな安値を提示して、ちょっと悪い気がしたくらいだぜ。ハハハハ！じゃあな。";
			link.l1 = "またな。";
			link.l1.go = "CapComission2_32";
		break;
		
		case "CapComission2_32":
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc")); // belamour gen
			addMoneyToCharacter(pchar, -150000);
			pchar.GenQuest.CaptainComission.vikupzaplatil = true; // новая проверка ,если шарль заплатил выкуп за пленника. лесник																																								
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission2_4":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
			{
				AddQuestRecord("CaptainComission1", "31");
				AddQuestUserData("CaptainComission1", "sName", "Jacques Barbazon");		// лесник																												  
				//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM)); в СЖ не работает
			}	
			pchar.GenQuest.CaptainComission.RepeatSpeak = true;		
			DialogExit();
		break;
		
		case "CapComission3":
			dialog.text = "それで、 "+GetFullName(pchar)+"、俺の仲間を沈めたのか？へっへっへ……";
			if(pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = "いいや。奴らを捕まえ損ねたんだ。帰り道でも会わなかったぜ。";
				link.l1.go = "CapComission4";
			}
			if(pchar.GenQuest.CaptainComission.PirateShips == "died")	
			{
				link.l1 = "ああ、やったぜ。奴らはサメの餌にしてやった。";
				link.l1.go = "CapComission5";
			}
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
		break;
		
		case "CapComission4":
			dialog.text = "くそっ！会ったかどうかなんて、今さら関係ねえだろうが！で、次はどんな提案だ？";
			link.l1 = "「もっと楽な仕事があるんじゃねえのか？」";
			link.l1.go = "CapComission4_1";
			link.l2 = "「聞け、」 "+NPChar.name+"……囚人の値段を下げろ……";
			link.l2.go = "CapComission4_2";
		break;
		
		case "CapComission4_1":
			dialog.text = "いやだ。";
			link.l1 = "じゃあな……";
			link.l1.go = "CapComission4_3";
		break;
		
		case "CapComission4_2":
			dialog.text = "値下げしろだと！？お前の無能のせいで俺の隠し財産がパーになったんだぞ！だからこそ値上げしてやる！欲しけりゃ20万ペソ払え、嫌ならとっとと失せろ。";
			link.l1 = "高すぎるな……じゃあな……";
			link.l1.go = "CapComission4_4";
			if(sti(pchar.money) >= 200000)
			{
				link.l2 = "くそっ、コインを持っていけ。";
				link.l2.go = "CapComission4_5";
			}	
		break;
		
		case "CapComission4_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", "Barbazon"); // лесник																			  
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));// в СЖ не работает
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();
		break;
		
		case "CapComission4_4":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "28");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", "Barbazon"); // правка	// лесник																	  
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM)); в сж не работает
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
		break;
		
		case "CapComission4_5":
			dialog.text = "この腑抜けはくれてやるぜ…";
			link.l1 = "さらばだ。";
			link.l1.go = "CapComission4_6";
		break;
		
		case "CapComission4_6":
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", "Barbazon"); // правки имени в сж лесник
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));//в СЖ не работает // belamour gen : это хорошо, но закомментить нужно было)))
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			DialogExit();	
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission5":
			dialog.text = "ホッホー！やるじゃねえか！その腑抜けを連れて、とっとと失せな。";
			link.l1 = "ありがとう。じゃあな。";
			link.l1.go = "CapComission5_1";
		break;
		
		case "CapComission5_1":
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
	   	/*case "CapComission6":    // ЕСЛИ В ПЕРВЫЙ РАЗ ОТКАЗАЛ В ЗАДАНИИ ,ТО ПУСТЬ БАБКИ ИЩЕТ
		     ИНАЧЕ ПОВТОРНАЯ ДАЧА ЗАДАНИЯ ПРЕВРАЩАЕТ КВЕСТ В КАШУ.. лесник
			dialog.text = "身代金を持ってきたのか "+GetSexPhrase("","「ла」")+"？俺があいつを農園主に売り飛ばすって言ったのは冗談じゃねえぞ。";			
			link.l1 = "「聞け、」 "+NPChar.name+"「…実はな、その金は持ってねえんだ。だが、俺はやる気はあるぜ」"+GetSexPhrase("","あ")+" 働け。";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "売らずにいてくれて助かったぜ。ほらよ、１５万ペソだ。そいつはどこにいる？"link.l2.go ="CapComission2_3";
			}			
		break;*/
		  case "CapComission6":                        // лесник . пусть шарль бабло ищет,или забить на пленника.
			dialog.text = "金は持ってきたか？あの男をプランテーションに売るってのは冗談じゃねえぞ。";			
			link.l1 = "金なんて持ってねえんだ、 "+NPChar.name+"、だが今取り組んでるところだ。";
			link.l1.go = "exit";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "奴をまだ売ってねえのはいいことだ。ほらよ、これが約束の金だ――十五万ペソだぜ。奴はどこにいる？"link.l2.go ="CapComission2_3";
			}			
		break;
																																					 																																													  																																															
//--------------------------------------------Похититель------------------------------------------------------
		case "Marginpassenger":
			dialog.text = "「俺が何をしようが、お前に関係ねえだろ？なあ、さっさと消えた方が身のためだぜ…」";
			link.l1 = "チッ、落ち着けよ。お前と話があるんだ。囚人のことでな。";
			link.l1.go = "Marginpassenger_1";
		break;
		
		case "Marginpassenger_1":
			dialog.text = "ああ、いいだろう。誰を身代金で引き取りたいんだ？";
			link.l1 = "待て。俺は誰かを買い戻しに来たわけじゃねえ、囚人を買うチャンスをお前にやるために来たんだ。まあ、 そいつの身代金を手に入れる機会もあるぜ。";
			link.l1.go = "Marginpassenger_2";
		break;
		
		case "Marginpassenger_2":
			dialog.text = "ふん。それで、なんで俺の助けが必要なんだ？自分で直接金を手に入れたくねえのか？";
			link.l1 = "俺にとっちゃかなり危険だぜ。役人どもと面倒なことになるかもしれねえ。";
			link.l1.go = "Marginpassenger_3";
		break;
		
		case "Marginpassenger_3":
			dialog.text = "はっは……まあいいだろう。見せてみろ。お前の囚人は誰だ？";
			link.l1 = "これは "+pchar.GenQuest.Marginpassenger.Text+" "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City+"Gen")+".";
			link.l1.go = "Marginpassenger_4";
		break;
		
		case "Marginpassenger_4":
			int iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "なるほど……嘘をついていないなら、公平な取引だな。まあ、この男に対して金を払ってやってもいいだろう "+iTemp+" ペソか、あるいは面白い情報をやることもできるぜ。どっちにするかはお前の選択だ。";
			link.l1 = "ペソをもらった方がいいな。こんな商売はもううんざりだ……";
			link.l1.go = "Marginpassenger_money";
			link.l2 = "はっ！もっと話してみろよ。どうせ俺にとって面白いネタがあるんだろうな。";
			link.l2.go = "Marginpassenger_offer";
		break;
		
		case "Marginpassenger_money":
			dialog.text = "金だな。持っていけ。もうお前の問題じゃねえ。ここで売り物を渡せ。";
			link.l1 = "今ごろは町の門の近くにいるはずだ。\nありがとう！本当に助かったぜ。";
			link.l1.go = "Marginpassenger_money_1";
		break;
		
		case "Marginpassenger_money_1":
			iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "どういたしまして、もっと持ってこい……じゃあな！";
			link.l1 = "…幸運を祈るぜ…";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, iTemp);
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			AddQuestRecord("Marginpassenger", "12");
			AddQuestUserData("Marginpassenger", "sSum", iTemp);
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
		break;
		
		case "Marginpassenger_offer":
			pchar.GenQuest.Marginpassenger.Goods = GetRandomGood(FLAG_GOODS_TYPE_EXPORT, FLAG_GOODS_VALUABLE_WOOD);
			pchar.GenQuest.Marginpassenger.GoodsQty = 200+rand(10)*10;
			switch (hrand(1))
			{
				case 0: //бухта на южном мейне
					SelectSouthshore();
					while (!isLocationFreeForQuests(pchar.GenQuest.Marginpassenger.Shore)) SelectSouthshore();
					dialog.text = "利口な男と取引するのは悪くねえな。さて、よく聞け。数日後に\n "+XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat")+" 本土からスペインの遠征隊がやって来るぜ、貴重な積荷を満載してな。やつらはその積荷を運ぶ船を待っている。 お前が一週間以内にそこへ行けば、その積荷を自分のものにできるチャンスがあるぞ。\n俺がお前の立場なら、とっくに自分の船へ向かってるぜ。それと、囚人をここに連れて来い。";
					link.l1 = "ありがとよ！この品は俺の苦労に見合う報酬だぜ。\nそれに、俺の乗客はもう町の門の近くにいるはずだ。お前のところに連れてこさせる。";
					link.l1.go = "Marginpassenger_offer_1";
				break;
				
				case 1: //просто кораблик
					SelectSouthcity();
					pchar.GenQuest.Marginpassenger.ShipName1 = GenerateRandomNameToShip(SPAIN);
					dialog.text = "頭の切れる男と取引するのは悪くねえな。さて、よく聞け。だいたい一週間後に、スペインのブリガンティン船『"+pchar.GenQuest.Marginpassenger.ShipName1+"「貴重な積荷を積んだ船が」から出航する "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen")+" へ "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Gen")+"。急げば簡単に追いつけるぜ。\nまだここにいるのか？俺ならもう自分の船に向かってるぜ。それと、囚人をここに連れてこい。";
					link.l1 = "ありがとよ！この品は俺の苦労に見合う報酬だぜ。乗客ももう町の門の近くにいるはずだ。 すぐにお前のところに連れてこさせる。";
					link.l1.go = "Marginpassenger_offer_2";
				break;
			}
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			pchar.GenQuest.Marginpassenger = "final";
		break;
		
		case "Marginpassenger_offer_1":
			DialogExit();
			AddQuestRecord("Marginpassenger", "13");
			AddQuestUserData("Marginpassenger", "sShore", XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat"));//лесник - окончание в СЖ // belamour gen
			AddQuestUserData("Marginpassenger", "sName", "Jacques the Kindman"));
			SetFunctionTimerCondition("Marginpassenger_SouthshoreOver", 0, 0, 7, false);
			pchar.quest.Marginpassenger.win_condition.l1 = "location";
			pchar.quest.Marginpassenger.win_condition.l1.location = pchar.GenQuest.Marginpassenger.Shore;
			pchar.quest.Marginpassenger.function = "Marginpassenger_Southshore";
		break;
		
		case "Marginpassenger_offer_2":
			DialogExit();
			AddQuestRecord("Marginpassenger", "16");
			AddQuestUserData("Marginpassenger", "sName", "Jacques the Kindman"));
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen"));
			AddQuestUserData("Marginpassenger", "sCity1", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Acc")); // лесник - окончание в СЖ
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName1);
			SetFunctionTimerCondition("Marginpassenger_SouthshipInWorld", 0, 0, 5+rand(2), false);
		break;
		
//---------------------------------------попытка залезть в сундуки --------------------------------------------
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("強盗だと！！！そんなの許せねえ！覚悟しやがれ、 "+GetSexPhrase("坊主","娘")+"...","おい、そこで何やってやがる！？俺を盗れると思ったのか？てめえはもう終わりだ…… ","待て、なんだと！？手を離せ！やっぱりお前は泥棒か！ここまでだ、この野郎…");
			link.l1 = LinkRandPhrase("くそっ！","カランバ！！","くそったれ！！");
			link.l1.go = "PL_Q3_fight";
		break;
					
// ----------------------------------------------блок нод angry--------------------------------------------------
		case "AngryRepeat_1":
            dialog.text = "出ていけ！";
			link.l1 = "「おっと……」";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "くだらねえ話で俺の邪魔をするな。\n次は痛い目を見ることになるぜ……";
        			link.l1 = "分かったぜ。";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = RandPhraseSimple("終わりだ、口を閉じろ。","もうお前と話したくねえから、これ以上俺にちょっかい出すんじゃねえぞ。");
			link.l1 = RandPhraseSimple("お望み通りに……","ふん、まあいいだろう…");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "もっと敬意を示して、無礼な態度をやめてくれるといいんだが？";
        			link.l1 = "安心しろ、Jacques、必ずやるぜ。";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("LeFransua_town","reload","reload6");
		break;
		
		case "pirate_town":
            dialog.text = "問題を解決しろだと？自分が何をやったかわかってんのか？まあいい、とにかく百万ペソ持ってこい。 そうすりゃ野郎どもにお前の“武勇伝”を忘れさせてやるぜ。気に入らねえなら地獄へ行きな。";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "よし、払う準備はできてるぜ。";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "了解だ。俺は行くぜ。";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//закрыть переход
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "よし！これでお前はまた潔白だと思え。ただし、もう二度とそんな汚ねえ真似はするんじゃねえぞ。";
			link.l1 = "俺はやめとくぜ。俺には高すぎるんだ。じゃあな…";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
		
		case "pirate_threat":
			if (GetNpcQuestPastDayWOInit(NPChar, "ThreatTalk") == 0)
			{
				dialog.text = NPCStringReactionRepeat("今日はすでにこの件について話しただろう。",
				                                      "はっきり言わなかったか？",
				                                      "お前のしつこさにはうんざりだ。",
				                                      "もう我慢の限界だ。さっさと失せろ！",
				                                      "repeat", 3, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("また今度にするよ...",
				                                   "もちろんだよ、"+npchar.name+"...",
				                                   "悪かったよ、"+npchar.name+"...",
				                                   "いてっ...", npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
				break;
			}
			if (iGPThreat != 0)
			{
				iBarbazonTotalTemp = 10 * iGPThreatRate;
				dialog.text = "ははっ！兄弟団の連中に目をつけられたんだな、" + GetSexPhrase("相棒", "お嬢さん") + "？まあ、しばらくの間なら大人しくさせておけるさ。ただし、それなりの金は必要だ。" + FindRussianDublonString(iBarbazonTotalTemp) + "払えば話はつけてやる。";
				if (PCharDublonsTotal() > iBarbazonTotalTemp)
				{
					if (iGPThreat < 5) link.l0 = "もちろん、これが君の金だ。";
					else link.l0 = "仕方ないな。これが君の金だ。";
					link.l0.go = "pirate_threat_pay";
				}
				link.l1 = "また後で来るよ...";
				link.l1.go = "exit";
			}
			else
			{
				SaveCurrentNpcQuestDateParam(NPChar, "ThreatTalk");
				if (NextDiag.TempNode != "I_know_you_good")
					dialog.text = "お前、正気か" + GetSexPhrase("", "い") + "？うちの連中はお前を疫病のように避けてるんだ。消え失せろ、時間の無駄だ。";
				else
					dialog.text = "何言ってんだ、" + GetSexPhrase("相棒", "お嬢さん") + "？お前は厄介者だって犬でもわかる。誰もお前とは関わりたくないんだよ。";
				link.l1 = "わかったよ...";
				link.l1.go = "exit";
			}
		break;

		case "pirate_threat_pay":
			iGPThreatRate = 0;
			iGPThreat = 0;
			SaveCurrentNpcQuestDateParam(NPChar, "ThreatTalk");
			RemoveDublonsFromPCharTotal(iBarbazonTotalTemp);
			DialogExit();
			PiratesDecreaseNotif("");
		break;
	}
}

void SelectSouthshore()
{
	switch (rand(6))
	{
		case 0: pchar.GenQuest.Marginpassenger.Shore = "shore37"; break;
		case 1: pchar.GenQuest.Marginpassenger.Shore = "shore47"; break;
		case 2: pchar.GenQuest.Marginpassenger.Shore = "shore48"; break;
		case 3: pchar.GenQuest.Marginpassenger.Shore = "shore25"; break;
		case 4: pchar.GenQuest.Marginpassenger.Shore = "shore21"; break;
		case 5: pchar.GenQuest.Marginpassenger.Shore = "shore20"; break;
		case 6: pchar.GenQuest.Marginpassenger.Shore = "shore19"; break;
	}
}

void SelectSouthcity()
{
	switch (hrand(2))
	{
		case 0: 
			pchar.GenQuest.Marginpassenger.Southcity = "Maracaibo";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Havana"; 
		break;
		
		case 1:
			pchar.GenQuest.Marginpassenger.Southcity = "Cartahena";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santiago"; 
		break;
		
		case 2:
			pchar.GenQuest.Marginpassenger.Southcity = "Portobello";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santodomingo"; 
		break;
	}
}
