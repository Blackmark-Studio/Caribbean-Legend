void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, Diag;
	string NPC_Meeting;	
	int Shit, i;
	ref refStore;
	ref sld;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
        case "exit":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
		break;

        case "First time":
			Diag.TempNode = "first time";
			if(CheckAttribute(PChar, "quest.Contraband.active"))
			{
				int iTmp = false;
				int iChIdx;
				
				float fMaxClass = ((MOD_SKILL_ENEMY_RATE/5.0) + 1.5);
				if (IsEquipCharacterByArtefact(pchar, "talisman21")) fMaxClass = 2.0;
				
				if (GetCompanionQuantity(pchar) > 1) iTmp = true;
				if (GetCharacterShipClass(pchar) < fMaxClass) iTmp = true;

				// поиск мин.  те старшего класса
				/* for (i=0; i<COMPANION_MAX; i++)
				{
					iChIdx = GetCompanionIndex(GetMainCharacter(), i);
					if (iChIdx>=0)
					{
						sld = GetCharacter(iChIdx);
            			if (GetCharacterShipClass(sld) < ((MOD_SKILL_ENEMY_RATE/5.0) + 1.5)) iTmp = true;
					}
				} */
				
				if (iTmp)
				{
					dialog.text = NPCStringReactionRepeat("こんな目立つ船で来るなって言われなかったのか！戦列艦でも連れてくればよかったんじゃねえのか？さっさと失せろ、 小さい船で出直して来い。","出て行け！さもないと俺たちが自分で巡回隊に突き出してやるぞ。","自分のボートに行って逃げろ。","…お前にはもううんざりだ…","ブロック",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("わかった、わかった、俺の船を変えるとするぜ。","落ち着け、今向かっている。","くそっ、うまくいくと思ったのによ…","ああ、俺は本当に頑固なんだぜ！",npchar,Dialog.CurrentNode);
						link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
					break;
				}
			
				Dialog.snd = "voice\SMSH\SMSH001";
				dialog.Text = RandPhraseSimple("おい、ここで何してるんだ、 "+GetSexPhrase("相棒","少女")+"?",RandSwear()+"ここで何の用だ！？");
				Link.l1 = "気楽にいこうぜ、相棒、取引しようじゃねえか！";
				Pchar.quest.Contraband.Counter = 0; // не торговали
				if(Pchar.Location == Pchar.location.from_sea)
				{
					Link.l1.go = "Exchange";
				}
				else
				{
					Link.l1.go = "No_Ship";
				}
				//по заданию губернатора, истребление контры, только эта ветка.
				if (CheckAttribute(pchar, "GenQuest.KillSmugglers") && pchar.GenQuest.KillSmugglers == "" && pchar.GenQuest.KillSmugglers.Areal == GiveArealByLocation(&locations[FindLocation(pchar.location)]))				
				{
					Link.l2 = "私はここの総督の命令で来た "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.KillSmugglers.MayorId)].city+"Gen")+"「武器を捨てて俺について来い、お前は逮捕されるんだ！」";
					Link.l2.go = "GenQuestKillContraband_1";
				}
			}
			else
			{
//================ METRO ====================
				//если заплатил, то разговаривают, иначе посылают
				if (CheckAttribute(PChar, "GenQuest.contraTravel.payed") && sti(PChar.GenQuest.contraTravel.payed) == true)
				{
                    dialog.Text = RandPhraseSimple("ああ、やっと来たな！待ってたぜ。さあ行こう、出航の時間だ。","さっさとやろうぜ。あちこちに巡回がいるんだ。ここから早く離れないと！");
					//по заданию губернатора, истребление контры, только эта ветка.
					if (CheckAttribute(pchar, "GenQuest.KillSmugglers") && pchar.GenQuest.KillSmugglers == "" && pchar.GenQuest.KillSmugglers.Areal == GiveArealByLocation(&locations[FindLocation(pchar.location)]))
					{
						Link.l1 = "私はここの総督の命令で来た "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.KillSmugglers.MayorId)].city+"Gen")+"「武器を捨てて俺について来い、お前は逮捕されるんだ！」";
						Link.l1.go = "GenQuestKillContraband_1";
						break;
					}
					//если набрал пассажиров, в сад..
					if (GetPassengersQuantity(PChar) > 0)
					{
						dialog.Text = "「お前は誰だ？俺たちはたった一人の乗客について話してたんだぞ！」";
						Link.l1 = "おっと……";
						Link.l1.go = "Exit";
						break;
					}
					//если набрал компаньонов или купил корабль себе уже :), в сад..
					if (GetCompanionQuantity(PChar) > 1 || sti(PChar.ship.type) != SHIP_NOTUSED)
					{
						dialog.Text = RandPhraseSimple("お前は誰だ？俺たちは乗客を待っていたんだ、船長じゃねえぞ。","消え失せろ！自分の船を処分するまで戻ってくるんじゃねえぞ。");
						Link.l1 = "くそっ！";
						Link.l1.go = "Exit";
						break;
					}
					//типа помог отбиться, свой парень... 
					if (CheckAttribute(PChar, "GenQuest.contraTravel.PatrolFight") && sti(PChar.GenQuest.contraTravel.PatrolFight) == true)
					{
						if (chrDisableReloadToLocation) // ещё бой идёт
						{
						    dialog.Text = "くそっ、巡回隊だ！俺たちはお前を知らねえし、お前も俺たちを知らねえだろう。";
							Link.l1 = "……わかった……";
							Link.l1.go = "Exit";
							break;
						}
						dialog.Text = RandPhraseSimple("助けてくれてありがとう。俺たちはこの恩を忘れねえぜ。さあ、今すぐ出航しよう。","よくやった！いい戦いぶりだったな。行くぞ。");
						ChangeContrabandRelation(PChar, 5);
						PChar.GenQuest.contraTravel.PatrolFight = false;
						AddCharacterExpToSkill(Pchar, "Sneak", 50);
					}
					//тут все ок, отправляемся.
					Link.l2 = "俺はこれから向かうところだ。";
					Link.l2.go = "Exit";
					//а это патруль... 
					if (GetSummonSkillFromNameToOld(Pchar, SKILL_SNEAK) < frandSmall(13.0*(1.0 - pow(0.9, sti(PChar.rank)))) && !CheckAttribute(PChar, "GenQuest.contraTravel.PatrolFight"))
					{
						AddDialogExitQuest("Rand_ContrabandInterruption");
						PChar.GenQuest.contraTravel.PatrolFight = true;
					}
					else 
					{
						//поместим Грея в локацию.
						refStore = CharacterFromID("Abracham_Gray");
						ChangeCharacterAddressGroup(refStore, "Ship_deck", "goto", "goto2");
						refStore.dialog.Filename = "Smuggler_Ship_dialog.c";
                        refStore.dialog.CurrentNode = "Travel_talkStart";
						//поплыл, иначе RemoveTravelSmugglers грохнет всю ветку
						PChar.GenQuest.contraTravel.ship = true;
						PChar.quest.Munity = "";  // признак выхода с палубы
						
						SetLaunchFrameFormParam(".. " + sti(Pchar.GenQuest.contraTravel.destination.days) + " days passed." + NewStr() + "Smuggler's ship deck.",
						                        "Reload_To_Location", 0.1, 5.0);
                        bQuestCheckProcessFreeze = true;
						WaitDate("", 0, 0, sti(Pchar.GenQuest.contraTravel.destination.days), rand(20), 0);
						bQuestCheckProcessFreeze = false;
						MakeCloneShipDeck(refStore, true); // подмена палубы
						SetLaunchFrameReloadLocationParam("Ship_deck", "reload", "reload1", "Travel_talkOnDeck");
						AddDialogExitQuest("LaunchFrameForm");
						AddCharacterExpToSkill(Pchar, "Sneak", 50);
					}
//================ METRO ====================
				}
				else
				{
                    // если таможня уже бежит
					if (CheckAttribute(NPChar, "ContrabandInterruption"))
					{
					    dialog.Text = RandSwear()+"巡回隊だ！俺たちはお前を知らねえし、お前も俺たちを知らねえだろう。";
						Link.l1 = "「いいだろう！」";
						Link.l1.go = "Exit";
					}
					else
					{
						dialog.Text = "消え失せろ！俺たちの取引を邪魔したら、内臓を引きずり出してやるぞ。";
						Link.l1 = RandPhraseSimple("俺に脅しをかけるつもりか、この野郎！？","てめえの言葉で喉を詰まらせることになるぜ！");
						Link.l1.go = "Exit_fight";
						Link.l2 = "心配するな、商売のやり方はわかってる。じゃあな。";
						Link.l2.go = "Exit";
					}
				}
			}
		break;

		case "No_Ship":
			Dialog.snd = "voice\SMSH\SMSH003";
			dialog.Text = "背中に背負ってるのか？お前の船はどこだ？";
			Link.l1 = RandPhraseSimple("まずは、何か裏がないか確かめてみたいんだ。","船を危険にさらしたくなかったんだ。何事も自分の目で確かめたいからな。");
			Link.l1.go = "No_ship_1";
			Link.l2 = "取引は終わりだ！";
			Link.l2.go = "Cancellation";
		break;

		case "No_ship_1":
			Dialog.snd = "voice\SMSH\SMSH004";
			dialog.Text = "俺たちは正直者だ、騙したりしねえよ。船をここに持ってきな、ただし巡回の連中に後をつけられないようにな。";
			Link.l1 = "わかった。ここで待っていろ。";
			Link.l1.go = "Exit";
		break;

		case "Cancellation":
            if (sti(Pchar.quest.Contraband.Counter) == 0)
            {
    			dialog.Text = "終わりだと？冗談じゃねえよ！";
    			Link.l1 = "俺は本気だ。";
    			Link.l1.go = "Cancellation_1";
			}
			else
            {
    			dialog.Text = "そうかい。まあ、今日は取引がうまくいったからな。";
    			Link.l1 = "「正解だ！」";
    			Link.l1.go = "Finish_exit";
			}
		break;

		case "Cancellation_1":
			if( makeint(Pchar.rank) <= 3 || GetSummonSkillFromNameToOld(Pchar, SKILL_FENCING) <= 5 || GetSummonSkillFromNameToOld(Pchar, SKILL_LEADERSHIP) <= 5 )
			{
				if(Rand(1) == 1)
				{
					ChangeContrabandRelation(pchar, -30);
					Dialog.snd = "voice\SMSH\SMSH006";
					dialog.Text = "この野郎！俺たちをそんな簡単に騙せると思うなよ！そのツケはてめえの首で払ってもらうぜ！";
					Link.l1 = "疑わしいぜ！";
					Link.l1.go = "Exit_fight";			
				}
				else
				{
					ChangeContrabandRelation(pchar, -10);
					Dialog.snd = "voice\SMSH\SMSH007";
					dialog.Text = "逃がさねえぞ！";
					Link.l1 = "他で吠えてろ、この野郎ども！";
					Link.l1.go = "Exit_cancel";
				}
			}	
			else
			{
				ChangeContrabandRelation(pchar, -10);
				Dialog.snd = "voice\SMSH\SMSH008";
				dialog.Text = "後悔するぜ！";
				Link.l1 = "お前はしゃべりすぎだ。";
				Link.l1.go = "Exit_cancel";			
			}	
		break;

		case "GenQuestKillContraband_1":
			//счетчик подстав по "метро"...
			if(CheckAttribute(PChar, "GenQuest.contraTravel.active") && sti(PChar.GenQuest.contraTravel.active) == true)
			{
				Statistic_AddValue(PChar, "contr_TravelKill", 1);
				ChangeContrabandRelation(pchar, -20); //репу контры вниз
			}
			dialog.Text = "そのことの報いは受けてもらうぜ！";
			Link.l1 = "ならば、お前たちは全員死ぬことになる。俺にははっきりとした命令があるんだ――抵抗すれば全員始末しろとな。";
			Link.l1.go = "Exit_fight";
		break;
		
		case "Exit_Cancel":
            DeleteAttribute(Pchar, "quest.Contraband");
            CloseQuestHeader("Gen_Contraband");
			Pchar.quest.Rand_Smuggling.over = "yes";
			RemoveSmugglersFromShore();
			RemoveAllContraGoods(CharacterFromId(pchar.GenQuest.Contraband.SmugglerId));
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
		break;
		
		case "Exit_fight":
            DeleteAttribute(Pchar, "quest.Contraband.active");
			DeleteAttribute(Pchar, "quest.Contraband.counter");			

			AddSimpleRumourCity("Heard the latest news? The local smugglers were rounded up by a patrol not long ago. And you know what? Captain who had a deal with them escaped!" +
				"He had dashing lads in his crew and the whole patrol was killed. And our local smugglers just vanished. There was nothing found on the shore. No goods, no stash and smugglers. See, how they do their business here!", Pchar.quest.contraband.City, 3, 5, "");	

			CloseQuestHeader("Gen_Contraband");
			Pchar.quest.Rand_Smuggling.over = "yes";
			LAi_group_FightGroups(LAI_GROUP_PLAYER, pchar.GenQuest.Smugglers_Group, true);
			RemoveSmugglersFromShore();
			RemoveAllContraGoods(CharacterFromId(pchar.GenQuest.Contraband.SmugglerId));
			LAi_SetFightMode(Pchar, true);

			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
		break;

		case "Finish_exit":
            // таможня на суше
            if(GetSummonSkillFromName(pchar, "Sneak") < Rand(120))
			{
				AddDialogExitQuest("Rand_ContrabandInterruption");
				for (i=1; i<=3; i++)
				{
					characters[GetCharacterIndex("Rand_Smug0"+i)].ContrabandInterruption = true;
				}
			}
			AddCharacterExpToSkill(Pchar, "Sneak", 100);
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
			ChangeContrabandRelation(pchar, 15);
            OfficersReaction("bad");
            ChangeCharacterComplexReputation(pchar,"nobility", -1);
            
            CloseQuestHeader("Gen_Contraband");
            
			DeleteAttribute(Pchar, "quest.Contraband.active");
			DeleteAttribute(Pchar, "quest.Contraband.counter");
	
			Pchar.quest.Rand_Smuggling.over = "yes";
			RemoveSmugglersFromShore();
			RemoveAllContraGoods(CharacterFromId(pchar.GenQuest.Contraband.SmugglerId));
		break;

		case "Exchange":
			// сама торговля -->
            if(FindContrabandGoods(Pchar) == -1 && sti(Pchar.quest.Contraband.Counter) == 0)
            {
				dialog.Text = "「で、ここで何してるんだ？売るものが何もないじゃねえか！お前の積み荷の品は全部、町で売れるんだぜ！」";
				Link.l1 = "今回は運がなかったな。";
				Link.l1.go = "NoGoods";
			}
			else
			{
                // установим окружение -->
                if (sti(Pchar.quest.Contraband.Counter) == 0) // не торговали ещё
                {
                    if(hrand(11) == 3)
                    {
        				dialog.Text = "なるほどな……お前の積み荷はタダでもらっていくぜ。どうせ文句なんか言えねえだろうしな。";
        				Link.l1 = "やってみろ、このクズ野郎！";
        				Link.l1.go = "Exit_fight";
                        break;
        			}
        			// море и солдаты на суше НЕЗАВИСИМЫ!!!
        			if(GetSummonSkillFromNameToOld(Pchar, SKILL_SNEAK) < Rand(12))
        			{
                        SetCoastalGuardPursuit();
        			}
        			// при убегании от патруля на карту - корабли трем
        			SetTimerCondition("Rand_ContrabandInterruptionAtSeaEnded", 0, 0, 2, false);// если в порту сидим, спим, то 2 день
        			
                    Pchar.quest.Rand_ContrabandAtSeaEnded.win_condition.l1 = "MapEnter";
        			Pchar.quest.Rand_ContrabandAtSeaEnded.win_condition = "Rand_ContrabandAtSeaEnded";
    			}
    			// установим окружение <--
				dialog.text = "よし、見せてもらおうか。";										  
				Link.l1 = "見せてみろ、何があるんだ。";
				Link.l1.go = "Exchange1"; 
				if (sti(Pchar.quest.Contraband.Counter) == 0)
    			{
        			Link.l99 = "考えが変わった。";
    				Link.l99.go = "Cancellation";
				}				
            }
		break;
		
		case "Exchange1":
			NPChar.quest.meeting = NPC_Meeting;
			Diag.CurrentNode = Diag.TempNode;		 
			DialogExit();
			// belamour legendary edition опасный груз
			pchar.GenQuest.Smugglerzpq = npchar.id;
			
			LaunchContrabandTrade(CharacterFromId(pchar.GenQuest.Contraband.SmugglerId),  sti(pchar.FindContrabandGoods.StoreIdx));	
		break;				
		// belamour legendary edition опасный груз -->
		case "SmugglerZPQ":
			dialog.text = "いい取引だな、船長！他にも面白い品があったら教えてくれよ！";										  
			Link.l1 = "同感だ、俺も今回の取引には満足しているぜ。ああ、もし全ての商品をこんなに良い値で買えたらなあ……";
			Link.l1.go = "SmugglerZPQ_1"; 
		break;

		case "SmugglerZPQ_1":
			dialog.text = "なぜ普通の商品をそんな値段で買わなきゃならないんだ？店で合法的に買えるのにさ。\nでも落ち込むなよ。実はどんな商品でも売れるんだ、たとえ普通の火薬でもな！とんでもない高値で売れることもある――大事なのは、売る場所を知ってるかどうかだぜ。";										  
			Link.l1 = "さあ、誰がこんな法外な値段で火薬を買うってんだ？";
			Link.l1.go = "SmugglerZPQ_2"; 
		break;
		
		case "SmugglerZPQ_2":
			dialog.text = "まあ、それは俺が言った通りだぜ、へへ…でもな…実は火薬を売って大儲けするチャンスは本当にあるんだが、この取引はやっぱり俺たち向きじゃねえ。そういうのには、 かなり評判が良くないといけねえし、俺たちは分かるだろ、貴族なんかじゃねえからな。";										  
			Link.l1 = "そうだな、調べてみてもいいぜ。必要な時は俺だって親切にもなれるさ。取引について教えてくれるか？";
			Link.l1.go = "SmugglerZPQ_3"; 
		break;
		
		case "SmugglerZPQ_3":
			dialog.text = "この世の中、船長、何をするにも金がかかるんだ。情報だって例外じゃねえ、いや、 むしろ情報こそが一番高くつくもんさ。こうしよう――この話を教えてやる代わりに、象徴的な額……そうだな、五千ペソってところでどうだ？";										  
			Link.l1 = "怪しい情報に五千ペソも払って、火薬を高値で売れる場所を教えてもらうだと？いや、 この助言がなくても何とかなると思うぜ。";
			Link.l1.go = "SmugglerZPQ_NM"; 
			if(sti(pchar.money) > 4999)
			{
				Link.l2 = "この取引で五千以上は稼げると思うぜ。よし、乗った。";
				Link.l2.go = "SmugglerZPQ_4";
			}
		break;	
		
		case "SmugglerZPQ_NM":
			npchar.Dialog.CurrentNode = "first time";
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.Smugglerzpq");
			dialog.text = "決めるのはあんた次第だぜ、船長。どっちにしても、いい取引だったな。幸運を祈るぜ……パトロールには気をつけろよ！";										  
			Link.l1 = "君もな。じゃあな。";
			Link.l1.go = "exit"; 
		break;
		
		case "SmugglerZPQ_4":
			AddMoneyToCharacter(pchar, -5000);
			dialog.text = "素晴らしいですな、船長！あなたは本当に特別なお得意様ですよ。さて、聞いてください。 メインのいくつかのスペイン都市で火薬の問題があるという噂を耳にしました。熱帯の豪雨のせいか、 他の理由かは分かりませんが――要するに、植民地を守る砦の備蓄がほとんど残っていないそうです。そして、この砦の司令官が、 この困難な状況を助けてくれる者を探しているとか。\nただし、問題が二つあります。第一に、これはとても繊細な話なので、 司令官はどんなならず者にも話すわけではありません。第二に、非常に大量の火薬を運ぶ話なので、 どんな船でも積めるわけではなく、艦隊が必要になるかもしれません。それに、どの船長も自分の船を、 流れ弾ひとつで島ごと吹き飛ばしかねない浮かぶ火薬庫にしたがるとは限りませんからな。";
			if(CheckAttribute(pchar,"questTemp.zpq"))
			{
				Link.l1 = "すまないが、この取引についてはすでに知っているんだ。それでも、この取引は金以上の価値があるから、 お前には五千払うに値する。";
				Link.l1.go = "SmugglerZPQ_5"; 
			}
			else
			{
				Link.l1 = "貴重な情報をありがとう。もしメインに行くことがあれば、現地の要塞の司令官たちに彼らの不幸について聞いてみるさ。 そんで、どうにかしてその問題を解決するか、あるいは利用させてもらうぜ、へへ。";
				Link.l1.go = "SmugglerZPQ_6"; 
			}
		break;
		
		case "SmugglerZPQ_5":
			npchar.Dialog.CurrentNode = "first time";
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.Smugglerzpq");
			dialog.text = "そういうもんさ。とにかく、いい取引だったな。幸運を祈るぜ…巡回隊には気をつけろよ！";										  
			Link.l1 = "君もな。じゃあな。";
			Link.l1.go = "exit"; 
		break;
		
		case "SmugglerZPQ_6":
			npchar.Dialog.CurrentNode = "first time";
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.Smugglerzpq");
			AddQuestRecord("zpq", "0");
			dialog.text = "そういうもんさ。とにかく、いい取引だったな。幸運を祈るぜ…巡回隊には気をつけろよ！";										  
			Link.l1 = "あなたもね。さようなら。";
			Link.l1.go = "exit"; 
		break;
		// <-- legendary edition опасный груз
	}
}
