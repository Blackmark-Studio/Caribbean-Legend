// BOAL диалог пленников - в трюме
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ref offref;
    int i, cn;
    int qty;
    string attrLoc, sTmp;
    
	switch(Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча
		case "First time":
		//--> Jason, Ложный след
		if (CheckAttribute(pchar, "questTemp.FalseTrace.Prisoner") && GetFullName(npchar) == pchar.questTemp.FalseTrace.CapName)
		{
			dialog.text = "何の用だ、船長？俺の身代金の話か？あの娘の運命を気にしていることは知っておいてほしい……";
			link.l1 = "「カトリーヌ・レイナーのことを話しているのか？その件についてはもう聞いているぞ。」 "+pchar.questTemp.FalseTrace.CapName+"。彼女があなたと話すように私に頼んだんだ。";
			link.l1.go = "FalseTrace_Prisoner";
			break;	
		}
		//<-- Ложный след
		
		// Addon-2016 Jason ФМК-Гваделупа
		if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG != "fail" && CheckAttribute(pchar, "questTemp.FMQG.Prisoner") && GetFullName(npchar) == pchar.questTemp.FMQG.Prisoner)
		{
			dialog.text = "";
			link.l1 = "見てくれよ、ドン・フアン、裏切りってのは汚えもんだぜ……";
			link.l1.go = "FMQG";
			break;	
		}
			if (sti(NPChar.nation) == PIRATE)
			{
				dialog.text = RandSwear()+"「俺はお前の捕虜だ」 "+GetAddress_Form(NPChar)+"。しかし、あなたに知っておいてほしいのは "+NationNameNominative(sti(NPChar.nation))+" 「自分の仲間のために金なんて払わねえ。俺たちはみんな自分で何とかするしかねえんだ。」";
				link.l1 = "ふん……お前からはもう儲けは出そうにねえな。せめてどこかの植民地で犯罪者として身代金を取ることはできそうだぜ。";
				link.l1.go = "offender";
				if (FindFreeRandomOfficer() > 0)
				{
					link.l2 = "見ろよ、お前は腕の立つ戦士だ。俺にはそういう奴が必要なんだ。俺の指揮下で働いてみないか？";
					link.l2.go = "free_to_officer";
				}	
			}
			else
			{
				dialog.text = RandSwear()+"俺はお前の捕虜だ。 "+GetAddress_Form(NPChar)+". "+NationNameNominative(sti(NPChar.nation))+" 俺の自由のためなら、いい値で買ってくれるはずだぜ。";
				if(NPChar.EncType == "trade" && FindFreeRandomOfficer() > 0 && CheckAttribute(NPChar, "Back.Ship.Mode") && NPChar.Back.Ship.Mode == "trade")
				{
					link.l1 = "見ろよ、お前は腕の立つ船乗りだ。俺にはお前みたいな奴が必要なんだぜ。俺の指揮下で働く気はねえか？";
					link.l1.go = "free_to_officer_trader";
				}
			}
			attrLoc = Sea_FindNearColony();
			if (attrLoc != "none") 
			{
                link.l3 = "俺たちは「から」遠くねえ "+GetCityName(attrLoc)+"。ここでお前を解放してやることもできるんだ。";
			    link.l3.go = "free_withoutFee";
			}
			else
			{
                link.l3 = "水夫長のところへ行って、ロッカーをもらうように伝えろ。次の港で下船できるぞ。";
			    link.l3.go = "free_withoutFee_2";
			}			
			link.l4 = "お前はきっと立派な奴隷になるだろうな――力もあるし、従順そうだ。";
			link.l4.go = "Slave_1";
			link.l5 = "お前は帆を下ろせという命令を無視し、力で抵抗したな。だから首を吊ることになるぜ。 水夫長にはすでに俺の命令を伝えてある。";
			link.l5.go = "PunishmentAction";
			link.l99 = "知っている。";
			link.l99.go = "exit";
			NextDiag.TempNode = "second time"; 
		break;
		
		case "second time":
			if(CheckAttribute(NPChar,"Hold_GenQuest") && !CheckAttribute(pchar,"GenQuest.Hold_GenQuest"))
			{
				switch(sti(NPChar.Hold_GenQuest.variant))
				{				
					case 0: // "tip-off"
						dialog.text = RandPhraseSimple("船長、俺の身代金よりもっと儲かる提案を聞いてみないか？","ここで取引の余地がないのは承知していますが、私の提案を聞いてみませんか？");
						link.l1 = "聞いているぞ。";	
						link.l1.go = "free_tip_off";
					break;
					
					case 1:
						dialog.text = "船長、どうして俺をただ解放してくれないんだ？俺なんかに価値はねえよ。 奴隷商人に売ったって小銭しか手に入らねえし、評判も悪くなるだけだぜ。";
						link.l1 = "「もしお前をただ解放したら、俺には何の得もねえじゃねえか……」";
						link.l1.go = "free_by_hoard";
						attrLoc = Sea_FindNearColony();
						if (attrLoc != "none") 
						{
							link.l2 = "お前は帆を下ろせという命令を無視し、さらに武力で抵抗した。その罪で絞首刑になるぞ。 水夫長にはすでに俺の命令を伝えてある。";
							link.l2.go = "PunishmentAction";							
						}
						else
						{
							link.l2 = "お前は本当にしつこいな。だから望み通りにしてやろう。もう自由の身だ。俺の船から出て行け。";
							link.l2.go = "free_in_sea";
						}
						link.l3 = LinkRandPhrase("俺の我慢を試すな。生きてるだけでもう運がいいんだぜ。","お前には俺なりの計画があるんだぜ。","将来、まだお前に役立ってもらうことがあるかもしれねえな。");
						link.l3.go = "exit";	
					break;
					
					case 2: // "ransom"
						dialog.text = "船長、この不安で俺は参っちまうぜ。俺をどうするつもりか、教えてもらえねえか？";
						link.l1 = "俺に差し出せるものがあるのか？";
						link.l1.go = "free_buyout";
						link.l2 = RandPhraseSimple("まだお前については何も思いつかねえな。",RandPhraseSimple("計画だと？首に砲弾でもぶら下げるか？冗談だ、はは！","お前は俺の捕虜だ。俺にはお前に何をしようとする権利がある。\nお前自身の考えなんざ、ここじゃ何の価値もねえ。"));
						link.l2.go = "exit";
					break;										
				}
				NextDiag.TempNode = "second time"; 
			}
			else
			{
				if (sti(NPChar.nation) == PIRATE)
				{
					dialog.text = "船長、どうして俺を解放してくれないんだ？俺なんか必要ないだろう。海賊になるしか道がなかったんだ、 価値のある技能も学もないからさ。俺が望んだのは、少し金を稼いで引退することだけだったんだ。";
					if (FindFreeRandomOfficer() > 0)
					{
						link.l2 = "見ろよ、お前は腕の立つ戦士だし、俺にはお前みたいな荒くれ者が必要なんだ。俺の部下になってみないか？";
						link.l2.go = "free_to_officer";
					}				
					link.l3 = LinkRandPhrase("お前に情けはかけねえ。海にはごろつきが山ほどいるが、これで一人減るってわけだな。"," 何か問題でもあるのか、“海の狼”よ？ここにいて大人しくしてろ。","お前らみたいな奴らには絞首台が待ってるんだ。俺はお前を役人に売り渡すぜ、 それがどんな海賊にもいい教訓になるだろうよ。");	
					link.l3.go = "exit";
				}
				else
				{
					if(NPChar.EncType == "trade")
					{
						dialog.text = "船長、お願いです…私を解放してください。家族も子供もいるんです、私がいなければ生きていけません。";
						if (FindFreeRandomOfficer() > 0 && CheckAttribute(NPChar, "Back.Ship.Mode") && NPChar.Back.Ship.Mode == "trade")
						{
							link.l2 = "見ろよ、お前は腕の立つ水夫だ。俺にはお前みたいな奴が必要なんだ。俺の指揮下で働いてみないか？";
							link.l2.go = "free_to_officer_trader";
						}
						link.l3 = LinkRandPhrase("お前には俺なりの計画があるんだぜ。","お前は将来まだ俺の役に立つかもしれねえな。","お前は俺の捕虜だ。だから俺はお前に何をしようと全くの自由だぜ。");
						link.l3.go = "exit";
					}
					if(NPChar.EncType == "war")
					{
						dialog.text = RandPhraseSimple("船長、私は戦いに敗れました。どうかお慈悲をお与えください。 ","船長、どうかご慈悲をお願いします。私が戦争捕虜として扱われる理由がないことは承知しておりますので、 どうか命だけはお助けください。海であなたと再び会うことは決してありませんと誓います。");
						link.l2 = LinkRandPhrase("俺の我慢を試すんじゃねえ。生きてるだけでもう運がいいんだぜ。",RandPhraseSimple("お前には俺なりの計画があるんだぜ。","将来、お前がまだ俺の役に立つかもしれねえな。"),RandPhraseSimple("お前は俺の囚人だ。俺にはお前に好きなことをする権利がある。\nお前自身の意見なんざ、ここじゃ何の価値もねえ。","お前は……いや、かつては軍艦の船長だったんだろうし、危険も承知していただろう。ここで聖人ぶるんじゃねえぞ。"));
						link.l2.go = "exit";	
						if (isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 1)
						{
							if(sti(Items[sti(pchar.EquipedPatentId)].Nation) == sti(NPChar.nation) && FindFreeRandomOfficer() > 0)
							{
								link.l3 = "見ろよ、お前は腕の立つ戦士だし、俺にはお前みたいな荒くれ者が必要なんだ。俺の部下にならねえか？";
								link.l3.go = "free_to_officer";
							}
						}
					}
				}
				attrLoc = Sea_FindNearColony();
				if (attrLoc != "none") 
				{
					link.l4 = "俺たちはもうすぐだ "+GetCityName(attrLoc)+"。ここでお前を解放してやることもできるんだ。";
					link.l4.go = "free_withoutFee";
				}
				else
				{
					if(NPChar.EncType == "trade" || NPChar.EncType == "pirate")
					{
						link.l4 = "水夫長のところへ行って、ロッカーをもらうように伝えろ。次の港で上陸できるぞ。";
						link.l4.go = "free_withoutFee_4";			
					}	
					else
					{
						link.l4 = "畜生め！甲板長のところへ行って、ロッカーをもらえと言ってこい。次の港で降ろしてやる。覚えておけ、 次に会う時が最後だぞ。";
						link.l4.go = "free_withoutFee_4";
					}
				}				
				link.l5 = "お前は帆を下ろせという命令を無視し、武力で抵抗した。その罪で絞首刑に処す。 すでに甲板長には俺の命令を伝えてある。";
				link.l5.go = "PunishmentAction";
				NextDiag.TempNode = "second time"; 
			}	
		break;
		
		case "offender":
			dialog.text = "犯罪者だと？冗談じゃねえか、"+GetAddress_Form(NPChar)+"!";
			link.l1 = "冗談じゃねえ。本当にお前は海賊だな。";
			link.l1.go = "exit";
		break;
		
		case "free_to_officer":
			if ((GetSummonSkillFromName(pchar, "Leadership") + 20) <= GetSummonSkillFromName(npchar, "Leadership"))
			{
				dialog.text = "お前の指揮下で働くくらいなら、サメの餌になったほうがマシだぜ！";
				link.l1 = "舌の使い方に気をつけろ、さもないと奴らの餌になるぜ。";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "「あなたの部下になるために」 "+GetAddress_Form(NPChar)+"？俺も同感だ。自分の仕事はわかってるし、失うものなんて何もねえ。";
				link.l1 = "取引成立だ！さっさと仕事に取りかかれ。";
				link.l1.go = "free_to_officer_Hire";
				link.l2 = "ちょっと待て、やっぱり気が変わった。";
				link.l2.go = "exit";
			}
		break;

		case "free_to_officer_trader":
			if (GetSummonSkillFromName(pchar, "Leadership") <= GetSummonSkillFromName(npchar, "Leadership"))
			{
				dialog.text = LinkRandPhrase("魅力的な申し出だが……俺は断らなきゃならねえ。信念のためにな。","悪いが、お前が俺の仲間にしたことを考えたら……無理だ。","いいえ、船長。こんな恐ろしい目に遭った後では、もうこの仕事はできません。 もし聖母マリア様が私の祈りを聞き入れてくださり、自由を与えてくださったなら、 もう二度と航海には出ないと誓いました。");
				link.l1 = "あなたの選択だ。俺は無理強いしねえよ。";	
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "なぜだ？俺は貧乏な船長で、船も失っちまったし、陸にはもう何も残っちゃいねえんだ。 残ってるのは請求書と借金だけさ……";
				link.l1 = "取引成立だ！水夫長のところへ行って手当を受け取れ。お前を俺の船の乗組員にするのは、もう少し後だぜ。";	
				link.l1.go = "free_to_officer_Hire";
				link.l2 = "ちょっと待て、やっぱり気が変わった。";
				link.l2.go = "exit";
			}
		break;
		
		case "free_to_officer_Hire":
            NPChar.Dialog.Filename = "Enc_Officer_dialog.c";
            NPChar.greeting = "Gr_Officer";
            NPChar.loyality = 5 + rand(10);
		    if (sti(NPChar.reputation) > 41)
		    {
		        NPChar.alignment = "good";
		    }
		    else
		    {
		        NPChar.alignment = "bad";
		    }
            ReleasePrisoner(NPChar); // освободили пленника
            DeleteAttribute(NPChar, "LifeDay") // постоянный
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			// тут трем накопивщиеся сабли и корабли 290704 BOAL -->
			DeleteAttribute(Npchar, "Ship");
			Npchar.Ship.Type = SHIP_NOTUSED;
            DeleteAttribute(Npchar, "Fellows"); // его офицеры
            Npchar.Fellows.Passengers.id0 = Npchar.index; // свой пассажир

			Npchar.Fellows.Passengers.boatswain = "-1";
			Npchar.Fellows.Passengers.navigator = "-1";
			Npchar.Fellows.Passengers.doctor = "-1";
			Npchar.Fellows.Passengers.cannoner = "-1";
			Npchar.Fellows.Passengers.treasurer = "-1";
			Npchar.Fellows.Passengers.carpenter = "-1";
            
			if(CheckAttribute(NPChar,"Hold_GenQuest")) DeleteAttribute(NPChar, "Hold_GenQuest");
			
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			DialogExit();
        break;
				
		case "Slave_1":
			dialog.text = "But "+GetAddress_Form(NPChar)+"「、そんなことはできない！私は降伏したんだ。」";
            link.l1 = "黙れ！…縛り上げろ。";
			link.l1.go = "Slave_2";
			link.l99 = "よし。俺が決めるまでここにいろ……";
			link.l99.go = "exit";
		break;
		
		case "Slave_2":
			OfficersReaction("bad");		
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
            if (rand(5) == 1)
            {
    			dialog.text = "ありえねえ！奴隷になるくらいなら死んだほうがマシだ！";
                link.l1 = "やめろ！これは命令だ！…甲板長！積荷を片付けろ…";
    			link.l1.go = "free_in_sea_4";
			}			
			else
			{
                if (rand(1) == 1)
                {
                    if (GetPrisonerQty() > 1)
                    {
                        dialog.text = "屠殺屋だ！野郎ども、俺に続け、失うものなんてねえぞ！";
                        link.l1 = "間違った選択だな、お嬢さんたち。反乱の始末は俺が自分でやるし、しかもすぐに終わらせるぜ……";
            			link.l1.go = "free_in_sea_battle_all";
                    }
					else
					{
						dialog.text = "冗談じゃねえ！戦って死んだほうがマシだぜ！";
						link.l1 = "お望みのままに……";
						link.l1.go = "free_in_sea_battle_1";
					}	
    			}
    			else
    			{
					dialog.text = "ああ、同感だ。俺には選択肢がねえんだよ。";
                    link.l1 = "素晴らしい。死んだ英雄になるより、生きている奴隷の方がましだぜ。";
        			link.l1.go = "Slave_3";				
    			}			
			}
		break;

		case "Slave_3":
            ReleasePrisoner(NPChar); //  пленника в рабы
        	LAi_SetActorType(NPChar);
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	ChangeCharacterComplexReputation(pchar,"nobility", -6);
        	DialogExit();
        	AddCharacterGoodsSimple(pchar, GOOD_SLAVES, 1);
        break;

		case "free_withoutFee":
			dialog.text = "「ああ」 "+GetAddress_Form(NPChar)+"「本当にそんなに親切なのか、身代金も要求せずに俺を解放してくれるのか？」";
            link.l1 = "ああ、俺だ。もうお前は自由だぞ。"+GetFullName(NPChar);
			link.l1.go = "free_withoutFee_2";
			link.l99 = "ふむ……一理あるな！もう少し考える時間が必要だ。";
			link.l99.go = "exit";
		break;

		case "free_withoutFee_2":
			dialog.text = "ありがとうございます。 "+GetFullName(PChar)+"！あなたのために祈ります。";
            link.l1 = "さあ行け、生き延びるんだ。さもないと俺の情けが無駄になるぜ。";
			link.l1.go = "free_withoutFee_3";
			OfficersReaction("good");
		break;
		
		case "free_withoutFee_3":
            ReleasePrisoner(NPChar); // освободили пленника
        	LAi_SetActorType(NPChar);
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	ChangeCharacterComplexReputation(pchar,"nobility", 2);
        	DialogExit();
        break;	

		case "free_withoutFee_4":	
			switch(NPChar.EncType)
			{
				case "pirate":
					dialog.text = RandPhraseSimple("ありがとうございます、船長。あなたのご親切は決して忘れません。私はこの仕事を辞めて、 静かな港で小舟の修理をして暮らします。それなら私にもできます。","ありがとうございます、船長！誓います、この恩知らずな稼業はやめて漁師になります。");
					link.l1 = "もし本当のことを言っているなら幸運を祈る。だが、そうでないなら、二度と俺に会わないように祈るんだな……";	
				break;
				case "trade":
					dialog.text = "どう感謝していいかわからないよ、船長。もう希望なんて失ってたんだ。あなたの親切はみんなに話すよ。約束する、 あなたのためにろうそくを灯す！教会にたどり着いたら、必ずね。";
					link.l1 = "さらばだ。次は、抵抗しようなんて考えるなよ。俺に発砲したら、お前も乗組員も死刑だぜ。";
				break;
				case "war":
					dialog.text = "感謝します、船長。あなたのために祈ります。";
					link.l1 = "幸運を祈るぜ。ただし、もし俺を狩ろうと決めたなら、それがお前の最期になるぞ。";
				break;
			}
			link.l1.go = "free_withoutFee_3";
		break;
		
		case "free_in_sea_battle_1":
            ReleasePrisoner(NPChar); // освободили пленника        	
        	LAi_LocationFightDisable(&Locations[FindLocation("My_Deck")], false);
            LAi_SetFightMode(Pchar, true);
            LAi_SetWarriorType(NPChar);
            LAi_group_MoveCharacter(NPChar, LAI_GROUP_TmpEnemy);
            LAi_group_SetHearRadius(LAI_GROUP_TmpEnemy, 100.0);
            LAi_group_FightGroupsEx(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "My_Deck_Battle_End");
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, "Prisoner", LAI_GROUP_NEITRAL);
        	DialogExit();
        break;		

		case "free_in_sea_battle_all":
			//ugeen --> привет Сиварду !!! после релиза пленников кол-во пассажиров уменьшается и цикл нихрена дальше не срабатывал
			for(int j = GetPassengersQuantity(pchar) - 1; j > -1; j--)
            {
                cn = GetPassenger(pchar, j);
                if(cn != -1)
                {
                    offref = GetCharacter(cn);
                    if (CheckAttribute(offref,"prisoned"))
                    {
        	            if(sti(offref.prisoned)==true && GetRemovable(offref)) // ставим только фантомов
        	            {
                        	ReleasePrisoner(offref); // освободили пленника
							LAi_SetWarriorType(offref);
							LAi_warrior_DialogEnable(offref, false);
                            LAi_group_MoveCharacter(offref, LAI_GROUP_TmpEnemy);
                        }
                    }
                }
            }
            LAi_LocationFightDisable(&Locations[FindLocation("My_Deck")], false);
            LAi_SetFightMode(Pchar, true);
			LAi_group_SetHearRadius(LAI_GROUP_TmpEnemy, 100.0);
            LAi_group_FightGroupsEx(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "My_Deck_Battle_End");
        	DialogExit();
        break;
		
		case "free_in_sea_4":
        	ReleasePrisoner(NPChar); // освободили пленника
            NPChar.location = "";
	        LAi_KillCharacter(NPChar);
        	DialogExit();
        break;

		case "PunishmentAction":
			dialog.text = "But "+GetAddress_Form(NPChar)+"、そんなことしちゃだめだ！俺は降参したんだぞ。";
			link.l1 = "お前の部下たちがいなくなってからだ。お前は奴らを裏切った……ボースン！こいつを連れて行け。";
			link.l1.go = "PunishmentAction1";
			link.l2 = "うーん……考える時間が必要だ。ここにいろ。";
			link.l2.go = "exit";
        break;

		case "PunishmentAction1":
			OfficersReaction("bad");		
			ChangeCharacterComplexReputation(pchar,"nobility", -2);			
			AddCharacterExpToSkill(Pchar, "Leadership", -150);
			if (rand(1) == 1)
            {
                if (GetPrisonerQty() > 1)
                {
                    dialog.text = "「屠殺屋だ！野郎ども、もう失うものなんてねえぞ！」";
                    link.l1 = "間違った選択だな、嬢ちゃんたち。反乱の始末は俺が自分でやるし、しかもすぐに片付けるぜ……";
					link.l1.go = "free_in_sea_battle_all";
                }
				else
				{
					dialog.text = "冗談じゃねえ！戦って死んだほうがマシだぜ！";
					link.l1 = "ご希望のままに……";
					link.l1.go = "free_in_sea_battle_1";
				}	
    		}
			else
    		{
				dialog.text = "せめて祈る時間くらいはくれ……";
                link.l1 = "祈りたければ、どうぞ。";
        		link.l1.go = "PunishmentAction2";				
    		}						
		break;
		
		case "PunishmentAction2":
        	ReleasePrisoner(NPChar); // освободили пленника
            NPChar.location = "";		
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);
			DialogExit();
		break;
		
		case "free_tip_off":
			dialog.text = "あんたみたいな男に役立つ面白い情報があるぜ。だが、その代わりに俺が自由になれるって約束が欲しいんだ。";
			link.l1 = "提案内容すら知らないのに、どうやって保証なんてできるんだ？お前の情報が俺に役立つとは思えねえな。";
			link.l1.go = "free_tip_off_0";
			link.l2 = "俺が約束できるのは言葉だけだ。";
			link.l2.go = "free_tip_off_1";
		break;
		
		case "free_tip_off_0":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);			
			DeleteAttribute(NPChar, "Hold_GenQuest");
			DialogExit();
		break;
		
		case "free_tip_off_1":
			switch(NPChar.EncType)
			{
				case "trade":
					sTmp = "He proposed me a freight but this guy was too greedy and I rejected the offer.";  
				break;
				case "war":
					sTmp = "I have escorted him a few times as a commander of a convoy.";
				break;
				case "pirate":
					sTmp = "I had an idea to rob him once but I have never had a single chance to do that.";
				break;
			}
			dialog.text = "よし。俺にはそれで十分だ。さて、本題に入ろう、\n "+XI_ConvertString("Colony"+NPChar.Hold_GenQuest.City+"Voc")+" 裕福な商人が住んでいる "+NPChar.Hold_GenQuest.Name+". "+"奴は自分の船『"+NPChar.Hold_GenQuest.ShipName+" 販売 "+GetStrSmallRegister(XI_ConvertString(Goods[sti(NPChar.Hold_GenQuest.Goods)].Name+"Acc"))+" 航路： "+XI_ConvertString("Colony"+NPChar.Hold_GenQuest.FromCity)+" - "+XI_ConvertString("Colony"+NPChar.Hold_GenQuest.ToCity)+". "+"荷物が多すぎるときは護衛に金を払うんだ。"+sTmp+" この情報は、たった一人の命よりもあなたにとって価値があるはずだ。";
			link.l1 = "この情報が俺に役立つとは思えねえ。俺は平和な商人を狩ったりしねえからな。";	
			link.l1.go = "free_tip_off_0";
			link.l2 = "この情報が俺に役立つかどうかは分からねえが、約束はしたからな。甲板長がお前を俺の船員たちのところに連れて行き、 一番近い港で解放してやる。";
			link.l2.go = "free_tip_off_2";			
		break;
		
		case "free_tip_off_2":
			dialog.text = "感謝するぜ、船長！お前の誠実さには最初から疑いなんてなかったぜ！";
			link.l1 = RandPhraseSimple(RandPhraseSimple("君についても同じことが言えたらよかったんだが","悪いが、お前については同じことは言えねえな。"),RandPhraseSimple("行け、そして次はこんなに寛大にはしないと覚えておけ。","さっさと行け、そして俺の邪魔をするな。次はそう簡単には信じねえぞ。"));
			link.l1.go = "free_tip_off_3";
		break;
		
		case "free_tip_off_3":
			pchar.GenQuest.Hold_GenQuest.Goods 			= NPChar.Hold_GenQuest.Goods;			
			pchar.GenQuest.Hold_GenQuest.Nation 		= NPChar.Hold_GenQuest.Nation; 
			pchar.GenQuest.Hold_GenQuest.Name 			= NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.ToCity 		= NPChar.Hold_GenQuest.ToCity;
			pchar.GenQuest.Hold_GenQuest.FromCity 		= NPChar.Hold_GenQuest.FromCity; 
			pchar.GenQuest.Hold_GenQuest.ShipName 		= NPChar.Hold_GenQuest.ShipName;				
			pchar.GenQuest.Hold_GenQuest.City 			= NPChar.Hold_GenQuest.City;
			pchar.GenQuest.Hold_GenQuest.CapName		= GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.Island			= GetArealByCityName(pchar.GenQuest.Hold_GenQuest.City); 
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern 	= true;
			
			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "1");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.Hold_GenQuest.Goods)].Name + "Acc"))); 
			AddQuestUserData("HoldQuest", "sCityFrom", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.FromCity));
			AddQuestUserData("HoldQuest", "sCityTo", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.ToCity));
			AddQuestUserData("HoldQuest", "sShipName", pchar.GenQuest.Hold_GenQuest.ShipName);
			
			SetFunctionTimerCondition("Hold_GenQuest_SetMerchant_pre", 0, 0, 1+rand(2), false);
			SetFunctionTimerCondition("Hold_GenQuest_MerchantOver", 0, 0, 30, false);
			
            ReleasePrisoner(NPChar); // освободили пленника
        	LAi_SetActorType(NPChar);
			NPChar.LifeDay = 0;
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	DialogExit();			
		break;
	
		case "free_buyout":
			dialog.text = "それと、お前に提案があるんだ。\n "+XI_ConvertString("Colony"+NPChar.Hold_GenQuest.City+"Voc")+" 命だ、友よ "+NPChar.Hold_GenQuest.Name+" 彼の名前だ。かつて一緒に商売をしていたんだ。"+"そこで奴を探せ。きっと大金を払ってくれるはずだ。奴は俺に借りがあるからな、俺が自分でケリをつけるぜ。";
			link.l1 = "お前の友達か？そいつを見せてみろ。";	
			link.l1.go = "free_buyout1";
			link.l2 = "「最初の港で身代金が手に入るなら、どうしてお前の友達を探さなきゃならねえんだ？」";
			link.l2.go = "free_tip_off_0";
		break;
	
		case "free_buyout1":
			LAi_CharacterDisableDialog(NPChar);
			
			pchar.GenQuest.Hold_GenQuest.City 		= NPChar.Hold_GenQuest.City;			
			pchar.GenQuest.Hold_GenQuest.Nation 	= NPChar.Hold_GenQuest.Nation;
			pchar.GenQuest.Hold_GenQuest.Name 		= NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.CapName	= GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.CapId		= NPChar.Id;
			pchar.GenQuest.Hold_GenQuest.TavernVariant = rand(1);
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = false;
			
			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "6");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Voc")); 
			AddQuestUserData("HoldQuest", "sNameChar", NPChar.Hold_GenQuest.Name);
			DialogExit();
		break;

		case "free_by_hoard":
			dialog.text = "実はな、俺はいい宝を持ってる男を知ってるんだが、そいつにはそれを使う度胸がねえんだよ。";
			link.l1 = "どういう意味だ？";
			link.l1.go = "free_by_hoard1";
			link.l2 = "くだらねえ話はやめろ。自分の魂の心配でもしてな。";
			link.l2.go = "free_tip_off_0";
		break;
		
		case "free_by_hoard1":
			dialog.text = "俺はお前に大きな財宝へと繋がる話をしてやる。その代わり、次の港で俺を解放するって約束してくれ。";
			link.l1 = "俺がいつ、どうお前を扱うかは自分で決める。お前の「話」なんざ関係ねえ。";
			link.l1.go = "free_tip_off_0";
			link.l2 = "聞いている。俺の言葉は約束だ。";
			link.l2.go = "free_by_hoard2";
		break;
		
		case "free_by_hoard2":
			dialog.text = "私はそのような名誉ある "+GetSexPhrase("男","女")+"。あんたみたいな人は、いつだって約束を守るんだな！たとえ世界が燃えていようが、あんたは約束を守る！そうだろう、 船長？";
			link.l1 = "話をしろ。さもないと、今すぐにでも……首なしで海に放り込んでやるぞ。";
			link.l1.go = "free_by_hoard4";
		break;
		
		case "free_by_hoard4":
			dialog.text = "ははっ、いい冗談だな……さて、聞けよ。そこにいる奴が "+XI_ConvertString("Colony"+NPChar.Hold_GenQuest.City+"Voc")+" 「名付けられた」 "+NPChar.Hold_GenQuest.Name+"、若い頃はかなり向こう見ずな奴だったんだ。あの頃はいろんな「取引」をやってたもんさ…"+"だから一度酒場で、彼は自分が～の一員だと俺に話したんだ\n "+GetName(NAMETYPE_VIP,NPChar.Hold_GenQuest.PirateName,NAME_ACC)+" あいつの仲間で、そいつはあの海賊どもが宝を埋めているのを見たんだ。"+" あの財宝のために仲間五人を殺したんだ……やつが捕まって絞首刑になったって噂もあったが、実際は足を洗って家庭を持ったんだよ。財宝の場所は覚えていて、 地図まで描いた。俺にも一緒に探しに行かないかと誘ってきた。迷信深いやつでな、 財宝は血にまみれていると信じていて、一人で行くのを怖がっていた。正直、俺も同じ理由で行かなかったんだ。 "+"あいつは地図を売る気満々だったが、どうせ俺がそこへ行くことはないし、必要もなかったんだよ…\nそれが俺の話さ…あんたみたいな勇敢な奴にはきっと役立つと思うぜ。それに地図はかなり安いもんだ。";
			link.l1 = "それを本気で信じろってのか？お前の話は嘘だ、だから取引は破棄するぜ。";
			link.l1.go = "free_tip_off_0";
			link.l2 = "面白い話だが、正直あまり信じちゃいねえ。\nだが俺の言葉は守るぜ、行って水夫長にロッカーを用意してもらえ。\nお前は自由だ。";
			link.l2.go = "free_by_hoard5";
		break;
		
		case "free_by_hoard5":
			dialog.text = "感謝するぜ、船長！これで男の言葉の重みがわかったよ "+GetSexPhrase("旦那！","お嬢さん！");
			link.l1 = "さっさと行け、俺の邪魔をするな。次はこんなに甘くはしねえぞ。");
			link.l1.go = "free_by_hoard6";
		break;
		
		case "free_by_hoard6":
			pchar.GenQuest.Hold_GenQuest.City 		= NPChar.Hold_GenQuest.City;			
			pchar.GenQuest.Hold_GenQuest.Nation 	= NPChar.Hold_GenQuest.Nation;
			pchar.GenQuest.Hold_GenQuest.Name 		= NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.PirateName	= NPChar.Hold_GenQuest.PirateName;
			pchar.GenQuest.Hold_GenQuest.CapName	= GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.TavernVariant = rand(1) + 2;
			pchar.GenQuest.Hold_GenQuest.Sum		= 10000 + rand(10000);
			pchar.GenQuest.Hold_GenQuest.Treasure	= rand(1);
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = false;
			
			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "12");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Voc")); 
			AddQuestUserData("HoldQuest", "sNameChar", pchar.GenQuest.Hold_GenQuest.Name);
			AddQuestUserData("HoldQuest", "sPirateName", GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_ACC));
			
            ReleasePrisoner(NPChar); // освободили пленника
        	LAi_SetActorType(NPChar);
			NPChar.LifeDay = 0;
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	DialogExit();					
		break;
		
		case "free_in_sea":
			dialog.text = "しかし、 "+GetAddress_Form(NPChar)+"「俺たちは大海原にいるんだぜ！それじゃまるで俺を処刑するのと同じじゃねえか！」";
			link.l1 = "それがあんたの望みだったんだろう。さらばだ。甲板長が俺の命令を実行する。";
			link.l1.go = "PunishmentAction1";
			link.l2 = "よし、まだ決めてねえ。";
			link.l2.go = "exit";
		break;		
		
		//--> Jason, Ложный след
		case "FalseTrace_Prisoner":
			dialog.text = "カトリーヌ！本当に君にここへ来るよう頼んだのか？あんな素晴らしい娘が…";
			link.l1 = "詩の話はやめにして、船長、もっと重大な話をしよう。今の状況について説明するから、返事をしてもらうぞ。 お前の返事次第で、お前自身とカテリーヌの運命が決まるんだ。";
			link.l1.go = "FalseTrace_Prisoner_1";
		break;
		
		case "FalseTrace_Prisoner_1":
			dialog.text = "聞いているぞ、船長。";
			link.l1 = "俺があんたのフリュート船に乗り込んだのは、カテリンの夫アダム・レイナーが「お前の船には大量の銀がある」 と言ったからだ。この企みで、彼はかつて自分のものだった女――あんたのもとへ逃げてきた女――を取り戻すことができたってわけさ。";
			link.l1.go = "FalseTrace_Prisoner_2";
		break;
		
		case "FalseTrace_Prisoner_2":
			dialog.text = "アダム？あの野郎か？全部あいつの計画だったんだ！今やっと分かった……そうだ、俺は三か月前にカトリーヌの逃亡を手伝ったんだ。かわいそうな娘さ、あいつがどんな扱いをしてたか、 あんたには分からねえだろう……";
			link.l1 = "あいつは彼の妻だったが、俺には何があろうと関係ねえ、俺の知ったこっちゃない。 お前のフリュート船に乗り込んだのは間違いだったが、今さら話しても遅いぜ。 アダムは手伝いの報酬を払うと約束してくれたんだ。";
			link.l1.go = "FalseTrace_Prisoner_3";
		break;
		
		case "FalseTrace_Prisoner_3":
			dialog.text = "アダムが約束したって？ははっ！それを信じたのか？船長、あいつがどんな奴か知ってるのか？あいつは……";
			link.l1 = "カトリーヌはすでに彼についていろいろ話してくれたし、そのためにずいぶん骨を折ってくれた。だが、 あいつの提案にも一理あるし、あの野郎を信じる理由はねえが、 もしかしたら今回は本当のことを言ってるのかもしれねえ。\nだから、単刀直入にいこう……";
			link.l1.go = "FalseTrace_Prisoner_4";
		break;
		
		case "FalseTrace_Prisoner_4":
			dialog.text = "";
			link.l1 = "お前を当局に身代金付きで引き渡して、アダムとカテリーヌを届けるつもりだったんだ "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Acc")+"それからアダムから斜視のソリーの金貨についての情報を手に入れて、それを目指して航海するつもりだった。\nだがカトリーヌが、まずあなたと話すようにと俺を説得したんだ。彼女は、アダムよりももっと良くて信頼できるものを、 あなたが俺に提示してくれるかもしれないと言っていた――あなたたちの命と自由と引き換えにね。";
			link.l1.go = "FalseTrace_Prisoner_5";
		break;
		
		case "FalseTrace_Prisoner_5":
			dialog.text = "";
			link.l1 = "だからこそ、俺はここに立ってお前と話しているんだ。俺の話はこれで終わりだ。今度はお前の番だぜ。 俺の言葉とカテリーヌの言葉をよく考えて、意見を聞かせてくれ。あまり時間はないぞ。";
			link.l1.go = "FalseTrace_Prisoner_6";
		break;
		
		case "FalseTrace_Prisoner_6":
			dialog.text = "船長！あんたが善人だとは思わないけど、貧しい娘の願いを聞いてここまで来てくれた。 あんたにも義理や哀れみの心があるってことだな。時間はいらない、今すぐ私の提案を伝えるよ。";
			link.l1 = "本当か？素晴らしい！それじゃあ、話を聞こう。";
			link.l1.go = "FalseTrace_Prisoner_7";
		break;
		
		case "FalseTrace_Prisoner_7":
			dialog.text = "アダム・レイナーを逮捕して鎖につなげ。\nそれから俺とキャサリンを連れて "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+"。街には上陸するなよ、結局お前が俺のフリュート船を沈めたんだからな、俺たち三人を降ろすなら "+XI_ConvertString(pchar.questTemp.FalseTrace.TargetShore+"Gen")+"\n武器も頼みたい。俺たちはジャングルを抜けて街へ向かう、そのクズには自分の罪だけじゃなく、 お前の分まできっちり償わせてやるぜ。奴にはそれだけの報いが必要だ\nお前の名前が表に出ることは絶対にないと約束する。その代わり、 敵国の金貨を積んだ船についての確かな情報を教えてやる\nお前にとっては大した相手じゃねえが、油断は禁物だぜ。だが手に入る戦利品は上等だ。俺の身代金や、 いわゆる片目のソリーの宝なんかよりずっとな。どうだ、取引成立か？";
			link.l1 = "俺はあんたの計画が気に入らねえ。俺がこの岸を離れた途端、地元の役人どもが俺を狩りに来ると思うぜ\n "+XI_ConvertString(pchar.questTemp.FalseTrace.TargetShore+"Gen")+"「……いやだ、船長。俺は命を張るつもりはねえ。話はこれで終わりだ。」";
			link.l1.go = "FalseTrace_Prisoner_8";
			link.l2 = "ふむ、カテリーヌの言った通りだったようだな。お前の提案、気に入ったぜ。アダム・レイナーは逮捕される。 今すぐ手配しよう。アダムを捕まえたらお前は釈放される。じゃあな、船長！";
			link.l2.go = "FalseTrace_Prisoner_9";
		break;
		
		case "FalseTrace_Prisoner_8":
			DialogExit();
			AddQuestRecord("FalseTrace", "9");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
			AddDialogExitQuestFunction("SetCheckForSolly");
			bQuestDisableMapEnter = false;
			LAi_CharacterDisableDialog(npchar);
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		break;
		
		case "FalseTrace_Prisoner_9":
			DialogExit();
			AddQuestRecord("FalseTrace", "10");
			pchar.quest.FalseTraceSollyOver.over = "yes"; //снять таймер
			AddDialogExitQuestFunction("SetCheckForGoldShip");
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.FalseTrace.PrisonerID = npchar.id;
			Pchar.questTemp.FalseTrace.PrisonerIDX = GetCharacterIndex(npchar.id);
		break;
		//<-- Ложный след
		
		// Addon-2016 Jason ФМК-Гваделупа
		case "FMQG":
			dialog.text = "説教しに来たのか、それとも商売しに来たのか？";
			link.l1 = "商売の話だ。俺にはお前の相棒、ベルトラン・ピネットが必要なんだ。あいつのせいで俺は大変な目に遭ってるんだよ。 どこにいるか教えろ、なあ？";
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			dialog.text = "「なぜ俺がそんなことをお前に話すと思うんだ？」";
			link.l1 = "命がけなのはお前だぜ。俺はお前をバステールまで連れて行き、総督に引き渡して、 カルロス・デ・ミリヤールの脱走を手助けした脱走兵として賞金をもらうつもりだ。\n選ぶのはお前だ。ピネットの居場所を教えるか、それとも二人でグアドループに向かうかだ。";
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			dialog.text = "そうか、全部知っているんだな……いいだろう、ベルナール・ピネットについて知っていることは全部話す。ただし、その代わりに俺を自由にしてくれ。";
			link.l1 = "さあ、話してみろ。前回と同じように、モスキート湾に上陸させてやる。ただし、もし俺に嘘をついたら、 ドン・カルロスからもらったあのプランテーションに火をつけてやるぜ。 さらにバステールにもお前の居場所を知らせるから、追うのは俺だけじゃなくなるぞ。";
			link.l1.go = "FMQG_3";
		break;
		
		case "FMQG_3":
			dialog.text = "まずは、そこに上陸させてくれ。それで少しは安心できるし、全部話すって誓うよ。";
			link.l1 = "いいだろう。どうせお前はどこにも行けやしねえからな。";
			link.l1.go = "FMQG_4";
		break;
		
		case "FMQG_4":
			DialogExit();
			AddQuestRecord("FMQ_Guadeloupe", "16");
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.FMQG.PrisonerID = npchar.id;
			Pchar.questTemp.FMQG.PrisonerIDX = GetCharacterIndex(npchar.id);
			pchar.quest.FMQG_SailMoskitos.win_condition.l1 = "location";
			pchar.quest.FMQG_SailMoskitos.win_condition.l1.location = "Shore47";
			pchar.quest.FMQG_SailMoskitos.function = "FMQG_ArriveMoskitos";
			pchar.questTemp.FMQG = "to_moskitos";
			AddMapQuestMarkShore("Shore47", true);
			bDisableMapEnter = false; // Rebbebion, теперь можно
		break;
		
		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
	}
}
