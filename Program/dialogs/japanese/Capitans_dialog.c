// разговор с капитаном на палубе  Boal
//homo 25/06/06
#include "DIALOGS\%language%\Rumours\Common_rumours.c"

int iEncPow = -1;
int iCapBattleDifficulty = -1; // Действует, пока не выгружен этот диалог

void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, Diag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	//belamour рыбацкое судно
	int i, iTemp, iQty;
	string sTemp;
    //homo Осады
    aref aData;
    makearef(aData, NullCharacter.Siege);
    string sCap, sGroup;
    string fort;
	bool bOk, bOk1, bOk2;

    if (CheckAttribute(aData, "nation"))
    {
	    sCap = NationShortName(sti(aData.nation))+"SiegeCap_";
	    sGroup = "Sea_"+sCap+"1";
	    
	   // string myships  = GetCompanionQuantity(PChar);
       // string escships = Group_GetCharactersNum(sGroup);
        
        switch(sti(aData.conation))
        {
            case 0:  fort = "English fort"; break;
            case 1:  fort = "French fort"; break;
            case 2:  fort = "Spanish fort"; break;
            case 3:  fort = "Dutch fort"; break;
            case 4:  fort = "Pirate fort"; break;
        }
        int ifortPower = sti(colonies[FindColony(aData.colony)].FortValue);
        int fortDamage = CheckFortInjuri();
        int SquadronDamage = CheckSquadronInjuri();
        
    }

    int iMoney;
	ref sld;
    
    if (CheckNPCQuestDate(npchar, "Card_date"))
	{
		SetNPCQuestDate(npchar, "Card_date");
		npchar.money = 3000 + rand(10) * makeint(100 * sti(PChar.rank) * (10.0 / MOD_SKILL_ENEMY_RATE));
	}
	else
	{
		if(sti(npchar.money) > CAP_MAX_MONEY || sti(npchar.money) < CAP_MIN_MONEY) 	
		{
			npchar.money = CAP_MIN_MONEY + rand(CAP_NORM);
		}
	}
    //homo 26/06/06
	ProcessCommonDialogRumors(NPChar, Link, Diag);
	switch(Dialog.CurrentNode)
	{
        case "Exit":
			DialogExit();
			Diag.CurrentNode = Diag.TempNode;
		break;
		
		case "First time":
			if (!bDisableMapEnter)
			{
				//--> Jason эскорт 2 уровень
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1WM") && pchar.questTemp.WPU.Escort == "begin" && NPChar.id == "WMCaptain")
				{
					dialog.text = "やあ、船長。くそっ、あんたに会えてどれだけ嬉しいか分かってねえだろう！";
					link.l1 = "やあ。自己紹介させてくれ― "+GetFullName(PChar)+"。君が無事で元気そうで本当に嬉しいよ、俺は君と君の船を探しにここへ来たんだ。";
					link.l1.go = "WM_Captain";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1WM") && pchar.questTemp.WPU.Escort == "wait" && NPChar.id == "WMCaptain")
				{
					dialog.text = "私が頼んだ材料を持ってきたか？";
					if (sti(pchar.questTemp.WPU.Escort.Planks) - GetSquadronGoods(pchar, GOOD_PLANKS) <= 0 && sti(pchar.questTemp.WPU.Escort.Sailcloth) - GetSquadronGoods(pchar, GOOD_SAILCLOTH) <= 0 && sti(pchar.questTemp.WPU.Escort.Linen) - GetSquadronGoods(pchar, GOOD_COTTON) <= 0)
					{
						link.l1 = "はい。あなたの船を修理するのに必要なものはすべて俺の船倉にあるぜ。";
						link.l1.go = "WM_Captain_5";
					}
					else
					{
						link.l1 = "いいや、まだ作業中だ。";
						link.l1.go = "exit";
					}
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1VSP") && pchar.questTemp.WPU.Escort == "toCap" && NPChar.id == "WMCaptain")
				{
					dialog.text = "「おい、」 "+GetAddress_Form(NPChar)+"。私の名前は "+GetFullName(NPChar)+"、俺はこの船の船長だ。あの忌々しい海賊野郎どもとの戦いで助けてくれたこと、心から感謝するぜ。 あんたが介入してくれなかったら、俺たちは本当に危なかった。まったく、命の恩人だよ！";
					link.l1 = "「たいしたことじゃねえ」  "+GetAddress_FormToNPC(NPChar)+"。自己紹介させていただきますが― "+GetFullName(PChar)+"、港長の依頼であなたのもとに来た "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+"。彼はあなたの隊商の不運について話してくれて、あなたの船を探すよう私に言った。";
					link.l1.go = "VSP_Captain";
					break;
				}
				//<-- эскорт 2 уровень
				
				if(CheckAttribute(NPChar, "surrendered"))
				{
                    CalcBattleDifficulty();
                    if(iEncPow == -1) iEncPow = 0;
					Pchar.GenQuest.MoneyForCaptureShip = (70 + hrand(60, "&CapSur"+NPChar.id)) * iEncPow;
					if(HasShipTrait(pchar, "trait14")) Pchar.GenQuest.MoneyForCaptureShip = makeint(sti(Pchar.GenQuest.MoneyForCaptureShip) * 1.35);
					dialog.text = "待てよ、こんなやり方じゃ俺を殺す気か。何が望みだ？";
					//выкуп
					link.l1 = "この件は平和的に解決しよう。身代金が最善の選択だろう。金額は "+Pchar.GenQuest.MoneyForCaptureShip+" ペソで十分だぜ "+GetAddress_FormToNPC(NPChar)+"。そしたら、とっとと失せろ！";
					link.l1.go = "surrender1";
					// обираем до нитки
					link.l2 = "お前の船倉に何があるか見せてもらおうじゃねえか。\nそれが済んだら、お前も乗組員も好きなところへ行っていいぜ。";
					link.l2.go = "surrender2";
					break;
				}
				
				//Голландский Гамбит, против всех
				if (CheckAttribute(PChar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "MeetingStivesant" && NPChar.id == "Stivesant")
				{
					dialog.text = "やあ、旦那。お会いできて嬉しいです。ロングウェイ船長は後でおそらく乗船されるのでしょう？";
					link.l1 = "ごきげんよう、スタイフェサント旦那。自己紹介させていただきます—— "+GetFullName(pchar)+"。ロンウェイは来ない、「メイフェン」には乗っていないんだ。";
					link.l1.go = "Stivesant_1";
					pchar.quest.QuestShipsTerms_Over.over = "yes"; //снять таймер
					break;
				}
				if (CheckAttribute(PChar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "FleutOnTrinidad" && NPChar.id == "Keller")
				{
					DelLandQuestMark(npchar);
					dialog.text = "おう、船長。俺のフルートに何の用だ？";
					link.l1 = "ごきげんよう、ケラー旦那。自己紹介させていただきます—— "+GetFullName(pchar)+"。少し変わった件であなたの助けを求めに来ました。";
					link.l1.go = "Keller_1";
					break;
					//Голландский гамбит
				}
				// belamour рыбацкое судно -->
				if(npchar.id == "FishingBoatCap")
				{
					if(!CheckAttribute(pchar, "GenQuest.FishingBoatSecondTime"))
					{
						Dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"！俺がこの船の船長だ "+GetFullName(NPChar)+"。俺の船に何の用だ？";
						link.l1 = "「ごきげんよう。何の用でこの湾に来られたのですか？」";
						link.l1.go = "FishingBoat";
						break;
					}
					else
					{
						Diag.CurrentNode = "first time";
						dialog.text = "他に話したいことはあるか？";
						link.l1 = "欲しかった"+GetSexPhrase("","")+" 諸島の最新情報を知るために。";
						link.l1.go = "rumours_capitan";
						if(CheckAttribute(pchar,"GenQuest.FishingBoatDialogEnb"))
						{
							link.l2 = "もう一度見せてくれ、どんなガラクタを売ってるんだい。 ";
							link.l2.go = "Торговля";
							if(pchar.GenQuest.FishingBoatDialogEnb != "no special goods")
							{
								link.l3 = "ふむ、船倉でもう少し探してみたらどうだ？何か売れるものが見つかるかもしれねえぞ？";
								link.l3.go = "Особые товары";
							}
						}
						link.l4 = "特に用はないけど、挨拶しに来ただけだぜ！";
						link.l4.go = "exit";	
						break;
					}
				}
				// <-- рыбацкое судно
				
				//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
				// генерал губернатор
				if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
				{
					Dialog.text = "総督閣下、閣下、ごきげんよう！何かご用でしょうか？";
					link.l1 = "お前に頼みたい仕事があるんだ！";
					link.l1.go = "quests";
					link.l2 = "特に用はないけど、ちょっと挨拶しに来ただけだぜ！";
					link.l2.go = "exit";
					break;
				}
				// вице адмирал
				if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && sti(Items[sti(pchar.EquipedPatentId)].Nation) == npchar.nation)
				{
					Dialog.text = "俺の船へようこそ、副提督！何かご用ですか？";
					link.l1 = "お前に頼みたい仕事があるんだ！";
					link.l1.go = "quests";
					link.l2 = "特に用はないが、挨拶しに来ただけだぜ！";
					link.l2.go = "exit";
					break;
				}
				// Офицер с патентом
				if(IsOfficerFullEquip() && sti(Items[sti(pchar.EquipedPatentId)].Nation) == npchar.nation)
				{
					Dialog.text = "お仲間に会えて嬉しいぜ、船長！どう手伝えばいい？";
					link.l1 = "お前に頼みたい仕事があるぜ！";
					link.l1.go = "quests";
					link.l2 = "特に用はないけど、ちょっと挨拶しに来ただけだぜ！";
					link.l2.go = "exit";
					break;
				}			
				// <-- legendary edition
                if (CheckAttribute(NPChar, "EncType")  && NPChar.EncType == "war")
                {
    			    Dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"！俺は "+GetFullName(NPChar)+" - "+NationNameGenitive(npchar.nation)+"の所属船の船長 "+NationKingsName(NPChar)+"。艦隊。何の用で俺の船に乗り込んできたんだ？";
    			}
    			else
                {
    			    Dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"！俺が船長だ "+GetFullName(NPChar)+"。何の用で俺の船に乗り込んできたんだ？";
    			}
    			link.l1 = "私の名前は "+GetFullName(Pchar)+"。お前に用があるんだ！";
    			link.l1.go = "quests";
                link.l2 = "ああ、何でもない、ただ "+GetSexPhrase("来た","来た")+" あなたを歓迎するために！";
    			link.l2.go = "exit";
            }
            else
            {
                Dialog.text = "気づいていないのか、 "+GetAddress_Form(NPChar)+"「戦闘中だぜ？今は話してる場合じゃねえ！」";
    			link.l1 = "まったく同感だ！俺は自分の船に戻るぜ。";
    			link.l1.go = "exit";
            }
			Diag.TempNode = "first time";
 		break;

        case "quests":
			// belamour рыбацкое судно -->
			if(npchar.id == "FishingBoatCap")
			{
				if(!CheckAttribute(pchar, "GenQuest.FishingBoatSecondTime"))
				{
					Dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"！俺がこの船の船長だ "+GetFullName(NPChar)+"。俺の船に何の用だ？";
					link.l1 = "「やあ、こんにちは。この湾で何をしているんだ？」";
					link.l1.go = "FishingBoat";
					break;
				}
				else
				{
					dialog.text = "他に話したいことはありますか？";
					link.l1 = "欲しかった"+GetSexPhrase("","")+" 諸島の最新情報を知るために。";
					link.l1.go = "rumours_capitan";
					if(CheckAttribute(pchar,"GenQuest.FishingBoatDialogEnb"))
					{
						link.l2 = "もう一度見せてくれ、どんなガラクタを売っているんだ？ ";
						link.l2.go = "Торговля";
						if(pchar.GenQuest.FishingBoatDialogEnb != "no special goods")
						{
							link.l3 = "うーん、船倉でもっと探してみたらどうだ？何か売り物が見つかるかもしれねえぞ？";
							link.l3.go = "Особые товары";
						}
					}
					link.l4 = "特に用はないけど、ちょっと挨拶しに来ただけだぜ！";
					link.l4.go = "exit";	
					break;
				}
			}
			// <-- рыбацкое судно
            if (!CheckAttribute(NPChar, "MainCaptanId")  || NPChar.MainCaptanId == pchar.GenQuest.CaptainId)
            {
                Dialog.text = "私はあなたの話をとても注意深く聞いています。  "+GetAddress_Form(NPChar)+".";
                link.l1 = "諸島の最新情報を聞きたいんだ。";
                //homo 25/06/06
                link.l1.go = "rumours_capitan";
                //belamour legendary edition 
				bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
				bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
				bOk = bOk1 || bOk2;
                if (CheckAttribute(NPChar, "EncGroupName") && !bOk) // только для фантомов грабеж
                {
                    iCapBattleDifficulty = CalcBattleDifficulty();
                    link.l2 = "（威圧の成功率： " + iCapBattleDifficulty + "%%) " + RandPhraseSimple("俺が誰だか分かってるのか？俺の大砲がてめえのボロ船を穴だらけにできるってことは分かるだろう。 平和的に済ませようじゃねえか。身代金で十分だぜ。", "見たか？ここだよ、公海のど真ん中さ……どうだい、うちの連中の機嫌取りにちょっとばかしお布施でもしてくれねえか？あんたの連中の無事のためにもさ。");
                    link.l2.go = "Talk_board";
                }
                if (CheckAttribute(NPChar, "Ship.Mode") && NPChar.Ship.Mode == "Trade")
                {
	           		link.l3 = "どこから来たんだ？";
	    			link.l3.go = "price_1";
	    			link.l4 = "取引したいか？";
	    			link.l4.go = "Trade_1";
    			}
				//--> квест мэра, поиски пирата
				if (CheckAttribute(pchar, "GenQuest.DestroyPirate"))
				{
	    			link.l6 = "この海域で活動している海賊船を探しているんだ。何か怪しいものを見かけなかったか？";
	    			link.l6.go = "MQ_step_1";
				}
				//<-- квест мэра, поиски пирата
    			link.l5 = "「くつろぎたいか？」";
			    link.l5.go = "Play_Game";
                link.l9 = "俺はそろそろ行くべきだな。";
    			link.l9.go = "exit";
			}
			else
			{
                Dialog.text = "俺にはお前と交渉する権限はねえ。うちの戦隊の司令官に話せ。名前は\n  "+GetFullName(characterFromID(NPChar.MainCaptanId))+"、彼はその上で見つけることができる "+XI_ConvertString(RealShips[sti(characters[GetCharacterIndex(NPChar.MainCaptanId)].Ship.Type)].BaseName)+" 「」"+characters[GetCharacterIndex(NPChar.MainCaptanId)].Ship.Name+"「。」";
                link.l1 = "ありがとうございます。おっしゃる通りにいたします。";
                link.l1.go = "exit";
                Diag.TempNode = "Go_away_Good";
			}
        break;
        case "Trade_1":
			dialog.text = "なぜだ？";
			link.l1 = "品物を見に行こうぜ。";
			link.l1.go = "Trade_2";
			link.l2 = "考えが変わった。";
			link.l2.go = "exit";
		break;
		
		case "Trade_2":
            Partition_GetCargoCostCoeff("after");
			FillShipStore(NPChar);
	    	pchar.shiptrade.character = NPChar.id;
   			Diag.CurrentNode = Diag.TempNode;
		    DialogExit();
		    DeleteAttribute(pchar, "PriceList.StoreManIdx"); // не вести лог по кораблям
		    LaunchStore(SHIP_STORE);
		break;
		
        case "Play_Game":
			dialog.text = "何を提案しているんだ？";
			link.l1 = "本気の金を賭けてカード勝負でもどうだ？";
			link.l1.go = "Card_Game";
   			link.l2 = "ポーカージョーカーでサイコロを振ってみないか？";
			link.l2.go = "Dice_Game";
			link.l10 = "申し訳ないが、ちょっと用事があるんだ。";
			link.l10.go = "exit";
		break;
        // карты -->
        case "Card_Game":
            if (!CheckNPCQuestDate(npchar, "Card_date_Yet") || isBadReputation(pchar, 30) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(3))
            {
                SetNPCQuestDate(npchar, "Card_date_Yet");
                dialog.text = "「悪党どもとは賭けなんかしねえぞ！」";
    			link.l1 = "ご希望の通りに。";
    			link.l1.go = "exit";
			}
			else
			{
                dialog.text = "なぜだ？俺はちょっと休憩してもかまわねえんだが…";
    			link.l1 = "素晴らしい。";
    			link.l1.go = "Cards_begin";
    			link.l2 = "「規則は何だ？」";
    			link.l2.go = "Cards_Rule";
			}
		break;

		case "Cards_Rule":
   			dialog.text = CARDS_RULE;
			link.l1 = "さあ、始めようぜ！";
			link.l1.go = "Cards_begin";
			link.l3 = "いや、俺のためじゃねえ……";
			link.l3.go = "exit";
		break;

		case "Cards_begin":
			Dialog.text = "まずは賭けの内容を決めよう。";
			link.l1 = "100ペソで勝負しようぜ。";
			link.l1.go = "Cards_Node_100";
			link.l2 = "５００ペソで勝負しようぜ。";
			link.l2.go = "Cards_Node_500";
			link.l3 = "俺はそろそろ行くべきだな。";
			link.l3.go = "exit";
		break;

		case "Cards_Node_100":
		    if (sti(pchar.Money) < 300)
		    {
                dialog.text = "冗談か？金がねえじゃねえか！";
                link.l1 = "そういうこともあるさ。";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 300)
		    {
                dialog.text = "さて、もう十分だ。これ以上やったら船の維持費が足りなくなっちまう……";
                link.l1 = "残念だな。";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "よし、100枚のコインで勝負しよう。";
			link.l1 = "始めよう！";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 100;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_Node_500":
		    if (sti(pchar.Money) < 1500)
		    {
                dialog.text = "冗談か？それとも何だ？1,500ペソなんて持ってねえじゃねえか！";
                link.l1 = "俺が見つけてやるぜ！";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 1500)
		    {
                dialog.text = "いや、この賭け事がきっと俺の破滅になるぜ。";
                link.l1 = "ご希望の通りに。";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "よし、500枚のコインで勝負しよう。";
			link.l1 = "始めよう！";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 500;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_begin_go":
            Diag.CurrentNode = Diag.TempNode;
			DialogExit();
            LaunchCardsGame();
		break;
	    // карты <--
	    //  Dice -->
        case "Dice_Game":
            if (!CheckNPCQuestDate(npchar, "Dice_date_Yet") || isBadReputation(pchar, 30) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(3))
            {
                SetNPCQuestDate(npchar, "Dice_date_Yet");
                dialog.text = "「悪党どもとは賭けはしねえぞ！」";
    			link.l1 = "ご希望のままに。";
    			link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
				{
					dialog.text = "いいじゃねえか！くつろぐのは体にはいいが……財布にはそうでもねえからな……";
	    			link.l1 = "素晴らしい。";
	    			link.l1.go = "Dice_begin";
	    			link.l2 = "俺たちのゲームのルールは何だ？";
	    			link.l2.go = "Dice_Rule";
    			}
    			else
    			{
					dialog.text = "いや、今日はもう終わりだ。やることがあるんでな。";
	    			link.l1 = "ご希望通りに。";
	    			link.l1.go = "exit";
				}
			}
		break;

		case "Dice_Rule":
   			dialog.text = DICE_RULE;
			link.l1 = "さあ、始めようぜ！";
			link.l1.go = "Dice_begin";
			link.l3 = "いいえ、俺のためじゃねえんだ……";
			link.l3.go = "exit";
		break;

		case "Dice_begin":
			Dialog.text = "まずは賭けの内容を決めよう。";
			link.l1 = "「50ペソで勝負しようぜ。」";
			link.l1.go = "Dice_Node_100";
			link.l2 = "200ペソで勝負しようぜ。";
			link.l2.go = "Dice_Node_500";
			link.l3 = "俺はそろそろ行くべきだな。";
			link.l3.go = "exit";
		break;

		case "Dice_Node_100":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckDiceGameSmallRate() && !bOk)
		    {
                dialog.text = "「あなたは」\n「としてよく知られている」"+GetSexPhrase("いかさま師","いかさま師")+"……お前とは絶対にサイコロ勝負なんかしないぜ。";
                link.l1 = "全部嘘だ！まあ、そういうことなら仕方ねえな。";
			    link.l1.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 300)
		    {
                dialog.text = "ふざけてるのか？金がねえじゃねえか！";
                link.l1 = "そういうこともあるさ。";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 300)
		    {
                dialog.text = "もうたくさんだ！俺は賭博はやめるぜ――これ以上やってたら、横領者呼ばわりされて船を追い出されちまうからな。";
                link.l1 = "残念だな。";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "よし、50枚のコインで勝負しよう。";
			link.l1 = "始めよう！";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 50;
            pchar.GenQuest.Dice.SitType   = false;
		break;

		case "Dice_Node_500":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckDiceGameSmallRate() && !bOk)
		    {
                dialog.text = "あなたは「～として」よく知られている"+GetSexPhrase("イカサマ師","いかさま師")+"。お前とは絶対にサイコロ勝負なんかしないぜ。";
                link.l1 = "全部嘘だ！まあ、そういうことなら仕方ねえな。";
			    link.l1.go = "exit";
			    break;
		    }
			if (!CheckDiceGameBigRate())
		    {
                dialog.text = "お前が相当な遊び人だって聞いたぜ。お前とは高額の賭けはしねえよ。";
                link.l1 = "「賭け金を下げてみるか？」";
			    link.l1.go = "Dice_Node_100";
				link.l2 = "申し訳ないが、俺は行かなきゃならねえ。";
			    link.l2.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 1500)
		    {
                dialog.text = "冗談言ってんのか？お前、1,500ペソなんて持ってねえじゃねえか！";
                link.l1 = "俺が見つけてやるぜ！";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 1500)
		    {
                dialog.text = "いや、この賭けがきっと俺の破滅になるぜ。";
                link.l1 = "ご希望どおりに。";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "よし、200枚のコインで勝負しよう。";
			link.l1 = "始めよう！";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 200;
            pchar.GenQuest.Dice.SitType   = false;
		break;

		case "Dice_begin_go":
            SetNPCQuestDate(npchar, "Dice_date_begin");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
            LaunchDiceGame();
		break;
	    // Dice <--
        case "price_1":
			if (CheckNPCQuestDate(npchar, "trade_date"))
			{
                SetNPCQuestDate(npchar, "trade_date");
				iMoney = findPriceStoreMan(NPChar);
	            if (iMoney == -1)
	            {
	                Dialog.Text = "なんで知りたいんだ？それは俺の個人的な事情だ。";
					Link.l1 = "ご希望の通りに。";
					Link.l1.go = "exit";
	            }
	            else
	            {
                    sld = &Characters[iMoney];
                    pchar.PriceList.ShipStoreIdx = iMoney;
                    
					Dialog.Text = "私はその都市から来た"+GetCityName(sld.City)+".";
					Link.l1 = "地元の店での商品の値段はいくらだ？";
					Link.l1.go = "price_2";
					Link.l9 = "俺は行くぜ。";
					Link.l9.go = "exit";
				}
			}
			else
			{
                Dialog.Text = "もう全部話しただろう。くだらねえことで俺を煩わせるな。";
				Link.l1 = "ああ、その通りだ。じゃあな。";
				Link.l1.go = "exit";
            }
		break;
		
		case "price_2":
            sld = &Characters[sti(pchar.PriceList.ShipStoreIdx)];
			SetPriceListByStoreMan(&Colonies[FindColony(sld.City)]);
			Dialog.Text = "はい、どうぞ……（価格表を受け取りました）…";
			Link.l1 = "本当にありがとうございます！";
			Link.l1.go = "exit";
			PlaySound("interface\important_item.wav");
		break;
		
        case "Talk_board":
            bOk = iCapBattleDifficulty > hrand(98);
            //if ((Group_GetCharactersNum(NPChar.EncGroupName) - Group_GetDeadCharactersNum(NPChar.EncGroupName)) > GetCompanionQuantity(PChar) && rand(11) > GetCharacterSkillToOld(PChar, SKILL_FORTUNE))
            if(!bOk && iCapBattleDifficulty <= 33)
            {
                Dialog.text = "ハハハ！いい冗談だな。特に俺が明らかに優位に立ってるからな。自分の船に戻って、そのまま沈めよ。";
                link.l1 = "...";
                link.l1.go = "Boarding";
            }
            else
            {
                if(!bOk)
                {
                    Dialog.text = "船長、俺の船で汚い仕事をするべきじゃなかったな。だが、情けをかけてお前を自分の船に戻してやるよ、 そのまま沈むがいい。";
                    link.l1 = "今日は誰がサメの餌になるか見ものだぜ！";
                    link.l1.go = "Boarding";
                }
                else
                {
                    if(iEncPow == -1) iEncPow = 0;
                    Pchar.GenQuest.MoneyForCaptureShip = (70 + hrand(60, "&CapSur"+NPChar.id)) * iEncPow;
					if(HasShipTrait(pchar, "trait14")) Pchar.GenQuest.MoneyForCaptureShip = makeint(sti(Pchar.GenQuest.MoneyForCaptureShip) * 1.35);
                    Dialog.text = RandSwear()+"ああ、お前の悪行についてはたっぷり聞いてるぜ。まあいいだろうが、覚えておけ "+XI_ConvertString(NationShortName(sti(NPChar.nation))+"狩人")+" 許さねえからな！";
                    link.l1 = "素晴らしい。合計は "+Pchar.GenQuest.MoneyForCaptureShip+" ペソで十分だぜ、 "+GetAddress_FormToNPC(NPChar)+".";
                    link.l1.go = "Capture";
                    link.l2 = "ああ、気にするな。ただの冗談だよ"+GetSexPhrase("","")+"!";
                    link.l2.go = "exit";
                }
            }
            // тут нужен учёт запрета повторного наезда
            Diag.TempNode = "Go_away";
			sld = characterFromId(pchar.GenQuest.CaptainId);
            sld.talk_date_Go_away =  lastspeakdate(); // boal злопамятность :)
        break;
		
		case "surrender1" :
			Diag.TempNode = "surrender_goaway";
            Dialog.Text = "ほらよ、さっさと失せろ！";
			Link.l1 = "いいね！お前も元気でな、友よ！";
			Link.l1.go = "exit";
			sld = characterFromId(pchar.GenQuest.CaptainId);
            sld.talk_date_Go_away = lastspeakdate();
			AddMoneyToCharacter(pchar, sti(Pchar.GenQuest.MoneyForCaptureShip));
			ChangeCharacterComplexReputation(pchar,"nobility", -2); 		
			ChangeCharacterComplexReputation(pchar,"authority", 1.0); 							
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			ChangeCharacterHunterScore(pchar, NationShortName(sti(NPChar.nation)) + "hunter", GetIntByCondition(HasShipTrait(pchar, "trait23"), 7 + rand(10), 3 + rand(5)));
		break;
		
		case "surrender_goaway":
			Dialog.Text = "俺に他に何を望んでるんだ？";
			Link.l1 = "「何もない。」";
			Link.l1.go = "exit";
			Diag.TempNode = "surrender_goaway";
		break;
		
		case "surrender2":			
			dialog.text = "どうやらお前に従うしかなさそうだな。";
			link.l1 = "さあ、どいたどいた！";
			link.l1.go = "surrender3";				
		break;
						
		case "surrender3":
			Diag.TempNode = "surrender_goaway";
			sld = characterFromId(pchar.GenQuest.CaptainId);
            sld.talk_date_Go_away = lastspeakdate();
			DialogExit(); 
			LaunchTransferMain(pchar, sld, "Transfer");
		break;
				
        case "rumours":
			Dialog.Text = SelectRumour(); // to_do
			Link.l1 = RandPhraseSimple(RandSwear()+"これはとても興味深いですね。ほかに質問はありますか？","ただの出来事さ。");
			Link.l1.go = "quests";
			Link.l2 = RandPhraseSimple("ありがとうございます、そろそろ失礼します。","ごきげんよう。");
			Link.l2.go = "exit";
			Diag.TempNode = "quests";
		break;
		
		case "Go_away":
			Dialog.Text = "俺の船から降りろ！";
			Link.l1 = "俺はもう行くぜ。";
			Link.l1.go = "exit";
			Diag.TempNode = "Go_away";
		break;
		
		case "Go_away_Good":
			Dialog.Text = "我々の話はこれで終わりだ。新しいことは何も教えねえぞ "+GetAddress_Form(NPChar)+".";
			Link.l1 = "よし、また海で会おうぜ！";
			Link.l1.go = "exit";
			Diag.TempNode = "Go_away_Good";
		break;

        case "Capture":
            Diag.TempNode = "Go_away";
            Dialog.Text = "ほらよ――さっさと出ていけ！";
			Link.l1 = "いいね！";
			Link.l1.go = "exit";
			AddMoneyToCharacter(pchar, sti(Pchar.GenQuest.MoneyForCaptureShip));
			ChangeCharacterComplexReputation(pchar,"nobility", -5);			
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			ChangeCharacterHunterScore(pchar, NationShortName(sti(NPChar.nation)) + "hunter", GetIntByCondition(HasShipTrait(pchar, "trait23"), 7 + rand(10), 3 + rand(5)));
        break;

        case "Boarding":
            if (CheckAttribute(NPChar, "MainCaptanId"))
            {
                PChar.StartBattleAfterDeck = true;
                PChar.StartBattleMainCaptanId = NPChar.MainCaptanId;
                PChar.StartBattleEncGroupName = NPChar.EncGroupName;
            }
            DialogExit();
            Diag.CurrentNode = Diag.TempNode;
        break;
        
        case "QuestAboardCabinDialog":  // тестовый диалог, в игре не работает, для метода SetQuestAboardCabinDialog
			Diag.TempNode = "QuestAboardCabinDialog";
            Dialog.Text = "待てよ、こんなやり方じゃ俺を殺す気か。何が望みだ？";
			Link.l1 = "お前を殺すためだ！";
			Link.l1.go = "QuestAboardCabinDialog_1";
			Link.l2 = "降伏しろ！";
			Link.l2.go = "QuestAboardCabinDialog_2";
			Link.l3 = "地図を渡せ、ビリー（c）";  // предмет, далее не ясно или  QuestAboardCabinDialog_1 или QuestAboardCabinDialog_2
			Link.l3.go = "QuestAboardCabinDialog_3";  // можно закодить покидание корабля, но экипаж уже вырезан и тп...
        break;
        
        case "QuestAboardCabinDialog_1":
			Dialog.Text = "さて、どうなるか見てやるぜ、この野郎！";
			Link.l1 = "「それで、俺は何を見ればいいんだ？」";
			Link.l1.go = "exit";
			// тут можно восстановить НР противника (NPChar) или добавить парочку гардов против ГГ
			LAi_SetCurHPMax(NPChar);
			AddDialogExitQuestFunction("QuestAboardCabinDialogExitWithBattle"); // тут ругань обратно
		break;
		
		case "QuestAboardCabinDialog_2":
			Dialog.Text = "「わかった、お前の勝ちだ！」";
			Link.l1 = "賢い判断だな！";
			Link.l1.go = "exit";
			AddDialogExitQuestFunction("QuestAboardCabinDialogSurrender");
		break;
		
		case "QuestAboardCabinDialog_3":
			Dialog.Text = "それを喉に詰まらせて苦しめよ！";
			Link.l1 = "よし、足枷につけ、黙っていろ、囚人。";
			if (rand(1) == 1)  // пример!!!
			{
				Link.l1.go = "QuestAboardCabinDialog_2";
			}
			else
			{
			    Link.l1.go = "QuestAboardCabinDialog_3_1";
			}
			TakeNItems(NPChar, "Chest", -1);
			TakeNItems(pchar, "Chest", 1);
		break;
		
		case "QuestAboardCabinDialog_3_1":
			Dialog.Text = ""+GetSexPhrase("ここに来た","ここに来た")+"、めちゃくちゃにした"+GetSexPhrase("","")+"、そして全てを奪った"+GetSexPhrase("","")+"「今度は俺を奴隷にしようってのか？絶対に嫌だ！」";
			Link.l1 = "なら、死ぬ覚悟をしろ。";
			Link.l1.go = "QuestAboardCabinDialog_1";
		break;
		//eddy. квест мэра, поиски пирата
		case "MQ_step_1":
			Dialog.Text = "いいや、海賊らしい怪しい船は見てねえな。";
			Link.l1 = "なるほど。";
			Link.l1.go = "exit";
		break;
		
		//homo Наводка на купца
		case "MerchantTrap_Abordage":

			Dialog.Text = "「〜の名の下に」 "+NationKingsName(NPChar)+" 降伏しろ "+GetSexPhrase("汚ねえ海賊","このあばずれ女め！")+"！ならば、お前の命は公平な裁判まで助けてやる。その場で全ての罪を裁かれることになるぞ "+NationNameSK(sti(NPChar.nation))+"お前が略奪した船"+GetSexPhrase("","")+".";
			Link.l1 = "くたばれ！降参しやがれ！";
			Link.l1.go = "exit";
			LAi_SetCurHPMax(NPChar);
			AddDialogExitQuestFunction("QuestAboardCabinDialogExitWithBattleNoParam"); // тут ругань обратно
		break;
		
		case "Siegehelp":		
            ref rchar = Group_GetGroupCommander(sGroup);
            if (NPChar.id == rchar.id)
            {
    			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
				{
					dialog.text = "閣下、総督閣下！私は注意深くお聞きしておりますが、どうか手短にお願いします。我々は今、戦っておりますので。 "+fort+"、それに俺が戦いの指揮を執らなきゃならねえんだ。";
				}
				else
				{
					if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && sti(Items[sti(pchar.EquipedPatentId)].Nation) == npchar.nation)
					{
						dialog.text = "副提督！私は注意深く聞いているが、時間がない。我々は戦っているのだ。 "+fort+"、それに俺が戦いの指揮を執らなきゃならねえんだ。";
					}
					else
					{
						dialog.text = "話は聞いているが、用件に早く入ろうぜ、俺たちは今、戦争中なんだ "+fort+"、それに俺が戦いの指揮を執る必要があるんだ。";
					}
				}
                link.l1 = "だからこそ、私はここにいるのだ。  "+GetAddress_FormToNPC(NPChar)+".";
                link.l1.go = "attack_fort";

                link.l2 = "それなら、これ以上あなたの時間を取らないよ。じゃあな、 "+GetAddress_FormToNPC(NPChar)+".";
                link.l2.go = "exit";
    			
            }
            else
            {
                Dialog.text = "俺にはお前と交渉する権限はねえ。うちの戦隊の司令官に話せ。名前は\n  "+GetFullName(rchar)+"、彼ならで会えるぞ "+XI_ConvertString(RealShips[sti(rchar.Ship.Type)].BaseName)+" 「」"+rchar.Ship.Name+"「」。";
                link.l1 = "ありがとうございます。おっしゃる通りにします。";
                link.l1.go = "exit";
            
            }
            Diag.TempNode = "Siegehelp";
            
		break;
		
		case "attack_fort":
                dialog.text = "「それはどういう意味だ？」";
                link.l1 = "「私はその植民地の砦を打ち砕く手助けができる」 "+GetCityName(aData.Colony)+" そして町を占領し、戦利品も手に入れる。もしうまくいけば、それらは俺たちで山分けするんだ。";
                link.l1.go = "Siegehelp_1";
                link.l2 = "実のところ、私の用件はあなたの貴重なお時間を取るほどのものではありません。では、失礼します。 "+GetAddress_FormToNPC(NPChar)+".";
                link.l2.go = "exit";
                Diag.TempNode = "Siegehelp_0";
		break;
		
		case "Siegehelp_0":
            Dialog.text = "またお前か？もう全部話し合ったと思ってたぜ。";
            link.l1 = "その通りだ。忘れてしまったようだ"+GetSexPhrase("","")+".";
			link.l1.go = "exit";
			NPChar.DeckDialogNode = "Siegehelp_0";
            Diag.TempNode = "Siegehelp_0";

		break;
		
		case "Siegehelp_1":
            SiegeResult("");
			// belamour legendary edition
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation);
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE;
			bOk = bOk1 || bOk2;
            if (sti(aData.win)==0 || bOk)
            {
                dialog.text = "「それで、お前は戦利品の分け前をどれくらいもらうつもりなんだ？」";
                link.l1 = "半分だ。";
                link.l1.go = "Big_part";
                link.l2 = "三分の一。";
                link.l2.go = "Middle_part";
                link.l3 = "四分の一だ。";
                link.l3.go = "Small_part";
            }
            else
            {
                dialog.text = "俺はお前の助けなんぞいらねえ、船長！この植民地は俺が自分の手で奪い取るつもりだ、誰の力も必要ねえんだよ。";
                link.l1 = "「なぜそんなに確信しているんだ、 "+GetAddress_FormToNPC(NPChar)+"、誰だって運が悪い時はあるもんだ。";
                link.l1.go = "attack_fort_03";
                link.l2 = "その場合は、これ以上お時間を取らせません。 "+GetAddress_FormToNPC(NPChar)+"。さらばだ！";
                link.l2.go = "exit";
            }
			Diag.TempNode = "Siegehelp_0";

		break;
		
		case "attack_fort_03":
            if((sti(aData.iSquadronPower)*SquadronDamage - (ifortPower)*fortDamage) < 4000)
            {
                dialog.text = "一方で、この戦いで俺の船はかなり損傷してしまったし、援軍が来てくれれば助かるのは間違いない。 もし同意してくれるなら\n "+GetPart(4)+"「それなら、まあ、合意に達することもできるだろうな。」";
                link.l1 = "「それで構わねえぜ」 "+GetAddress_FormToNPC(NPChar)+"。俺が砦を攻撃してみるから、お前は自分の船の大砲で援護してくれ。";
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 4;
                link.l2 = "「俺はそんな安い男じゃねえ」 "+GetAddress_FormToNPC(NPChar)+"。お騒がせして申し訳ありません"+GetSexPhrase("","")+" お忙しいところ失礼しました。さようなら！";
                link.l2.go = "exit";
            }else{
                dialog.text = "俺の艦隊にはこの要塞を粉々にするだけの船が十分にある――時間の問題だ。\nさあ、俺の船から降りてくれないか？勝利が俺を待ってるんだ！";
                link.l1 = "「そういうことなら、」 "+GetAddress_FormToNPC(NPChar)+"、それではこれにて失礼いたします。ごきげんよう！";
                link.l1.go = "exit";
            }
		    Diag.TempNode = "Siegehelp_0";
		break;
		case "Big_part":
            if( (sti(aData.iSquadronPower)*SquadronDamage - (ifortPower)*fortDamage) <= -1500)
            {
                dialog.text = "砦の大砲で俺の船はひどく損傷した。これからの戦いで俺たちが負ける側になるかもしれねえ。助けを受け入れ、 お前の条件にも同意するぜ。";
                link.l1 = "「素晴らしい」 "+GetAddress_FormToNPC(NPChar)+"その場合は我々が砦を攻撃するから、君は自分の船の砲撃で援護してくれ。";
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 2;
            }
            else
            {
				// belamour legendary edition
				bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation);
				bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE;
				bOk = bOk1 || bOk2;
				if(bOk)
				{
					dialog.text = "閣下、作戦の進捗についてまだご報告しなければなりません……せめてお聞きください "+GetPart(4)+".";
				}
				else
				{
                dialog.text = "多すぎじゃねえか、船長？お前は "+GetNumShips(GetCompanionQuantity(PChar))+"、そして俺の戦隊は "+GetNumShips(Group_GetCharactersNum(sGroup))+"。お前に提供できる "+GetPart(4)+"。公平だと考えてくれ。";
				}
                aData.PartAttaksFort = 4;
                link.l1 = "同意する"+GetSexPhrase("","")+", "+GetAddress_FormToNPC(NPChar)+"その場合は俺が要塞を攻撃するから、お前は自分の船の大砲で援護してくれ。";
                link.l1.go = "attack_fort_04";
                link.l2 = "「残念だが、そうは思わねえな」 "+GetAddress_FormToNPC(NPChar)+"。これ以上話すことはない。さらばだ。";
                link.l2.go = "exit";
            }
            Diag.TempNode = "Siegehelp_0";
        break;
        
        case "attack_fort_04":
            dialog.text = "砦を奪取し次第、上陸部隊を岸に展開し始める。その後は町の中で戦闘を続けるつもりだ、 そこで君と会えることを願っている。";
            link.l1 = "そうか。では、また会おう。 "+GetAddress_FormToNPC(NPChar)+"!";
            link.l1.go = "exit";
            Diag.TempNode = "Siegehelp_0";
            PChar.quest.Union_with_Escadra = "Yes";
        break;

        case "Middle_part":
            if((sti(aData.iSquadronPower)*SquadronDamage - (ifortPower)*fortDamage) <= -600)
            {
                dialog.text = "お前の条件に同意しようと思うぜ。共同作戦なら、この戦いで勝てる見込みも上がるからな。すべて計画通りに進めば、 お前にも分け前をやる。";
                link.l1 = "「合意に達してよかったな」 "+GetAddress_FormToNPC(NPChar)+"。すぐに部下たちに砦への攻撃を命じる。";
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 3;
            }else{
				// belamour legendary edition
				bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation);
				bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE;
				bOk = bOk1 || bOk2;
				if(bOk)
				{
					dialog.text = "閣下、作戦の進捗についてまだご報告しなければなりません……せめてお聞きください "+GetPart(4)+".";
				}
				else
				{
                dialog.text = "多すぎじゃねえか、船長？お前は "+GetNumShips(GetCompanionQuantity(PChar))+"、そして俺の戦隊は "+GetNumShips(Group_GetCharactersNum(sGroup))+"。お前に提供できる "+GetPart(4)+"。これで公平だと考えてくれ。";
				}
                link.l1 = "I "+GetSexPhrase("同意する","同意する")+", "+GetAddress_FormToNPC(NPChar)+"その場合は俺が砦を攻撃する、そしてお前は自分の船の砲撃で俺たちを援護してくれ。";
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 4;
                link.l2 = "残念だが、そうは思わねえな。 "+GetAddress_FormToNPC(NPChar)+"。これ以上話すことはない。さらばだ。";
                link.l2.go = "exit";
            }
            Diag.TempNode = "Siegehelp_0";
        break;

        case "Small_part":
            dialog.text = "俺の船は疲れ切っているし、この状況では新たな戦力はどれも歓迎だ。手を貸してくれるなら、その条件を受け入れるぜ。 ";
            link.l1 = "嬉しい"+GetSexPhrase("","")+", "+GetAddress_FormToNPC(NPChar)+"……すぐに部下たちに砦への攻撃を開始するよう命じる。";
            link.l1.go = "attack_fort_04";
            aData.PartAttaksFort = 4;
            Diag.TempNode = "Siegehelp_0";
        break;
		
		case "Talk_Capture_City":
            AfterTownBattle();  // все, все свободны
            LAi_LoginInCaptureTown(NPChar, false);
            aData.win = 1;
            EndOfTheSiege("End");
            NPChar.location = "";
            int ilt = makeint(sti(aData.loot)/sti(aData.PartAttaksFort));
            dialog.text = "やあ、船長！確かに激しい戦いだったが、町の守備隊の激しい抵抗をなんとか打ち破ったぜ。俺たちは略奪した "+sti(aData.loot)+" ペソだ。我々の取り決め通り、お前の取り分は "+ilt+"。どうぞこの金をお受け取りください。あなたは一枚残らず受け取るにふさわしい方です。さて、失礼しますが、 私は自分の仕事に戻らねばなりません。";
            link.l1 = "その場合は、あなたを残していくよ。 "+GetAddress_FormToNPC(NPChar)+"。さらばだ！";
            link.l1.go = "exit";
            //AddDialogExitQuest("End_Siege_and_Attaks_City");

            Diag.TempNode = "no_return_02";
            AddMoneyToCharacter(PChar, ilt);
            ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
            ChangeCharacterComplexReputation(PChar,"nobility", 10);
            AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 80);
            AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 100);
            AddCharacterExpToSkill(GetMainCharacter(), "Defence", 100);
            AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 100);
            AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 100);
            AddCharacterExpToSkill(GetMainCharacter(), "Fortune", 80);
            aData.loot = sti(aData.loot) - ilt;
            if (CheckAttribute(PChar, "quest.LeaveTown")) Pchar.quest.LeaveTown.over = "yes";
            //--> слухи
            SiegeRumour("I've been told that you had helped our squadron in the assault of the "+NationNameSK(sti(aData.conation))+" colony - "+GetCityName(aData.Colony)+"! We're so thankfull to you, "+ GetAddress_Form(NPChar)+".", "", sti(aData.nation), -1, 30, 3);
            //<-- слухи
		break;

        case "no_return_02":
            dialog.text = "おう、船長！俺に用かい？";
            link.l1 = "いいや "+GetAddress_FormToNPC(NPChar)+"。さようなら！";
            link.l1.go = "exit";
            Diag.TempNode = "no_return_02";
		break;
		
		case "GoldSquadron":
            ref rch = Group_GetGroupCommander("Sea_Head_of_Gold_Squadron");
            if (NPChar.id == rch.id)
            {
    			dialog.text = "話を聞こう。ただし、用件は手短にしてくれ、時間がないんだ。私は重要かつ極秘の任務中で、我々 の護送船団に脅威となりうる怪しい船は、公海上で沈めるよう命じられている。";                          
                link.l1 = "それなら、これ以上あなたの時間は取らないよ。幸運を祈るぜ。 "+GetAddress_FormToNPC(NPChar)+".";
                link.l1.go = "exit";

            }
            else
            {
                Dialog.text = "俺にはお前と交渉する権限はねえ。うちの戦隊の司令官に話せ。名前は\n "+GetFullName(rch)+"、彼はで見つけられる "+XI_ConvertString(RealShips[sti(rch.Ship.Type)].BaseName)+" ''"+rch.Ship.Name+"「」。";
                link.l1 = "ありがとう。言われた通りにするよ。";
                link.l1.go = "exit";

            }
            Diag.TempNode = "GoldSquadron";
		break;
		
		case "WM_Captain":
			dialog.text = "はじめまして、私の名前は "+GetFullName(npchar)+"「それで、助けに来てくれたのか？それなら特に嬉しいよ、今の状況は本当に危機的なんだ――俺たちは無人島の岸に取り残されて、船はやっとのことで浮かんでいるし、乗組員も大勢失ってしまった……」";
			link.l1 = "聞いた話によると、お前は海賊と戦ったそうだな、それからあの嵐もあったんだろう…";
			link.l1.go = "WM_Captain_1";
			pchar.quest.DesIsland_Over.over = "yes";//снять прерывание
		break;
		
		case "WM_Captain_1":
			dialog.text = "その通りだ。俺の船は戦闘でひどく損傷した――あの海賊野郎どもの乗り込みまで受けちまったんだ。その後、嵐に巻き込まれてな……ああ、思い出したくもねえ。俺たちはこの不毛な岸まで流されちまった。嵐から救ってくれ、 錨鎖が切れませんようにって、一日中聖母マリアに祈ってたんだ\nそして今ここにいる。もう一週間も船を修理してるが、見ての通りだ：残ってるのは五十人だけ、木材も足りねえ――どこから調達しろってんだ？ジャングルか？まあ、そうだろうな。毎日必死に働いてるが、 必要な資材の五分の一しか集まってねえ\nこんな損傷のまま航海するなんざ自殺行為だ。これで俺たちの現状がわかっただろう、船長……";
			link.l1 = "ああ……お前の状況は気の毒だな。どうすればいいか、俺にできることが何か考えてみようぜ。";
			link.l1.go = "WM_Captain_2";
		break;
		
		case "WM_Captain_2":
			dialog.text = "ええ、もし板と帆布が十分にあれば、一週間以内に船を修理できるんだがな\n船長、わざわざここまで来てくれたんだ、ついでに一番近い港に行って必要な資材を買ってきてくれないか？ それでこの問題は解決するぜ。金の心配はいらねえ、かかった費用は全部俺が払うからよ。";
			link.l1 = "もちろんだ。何を、どれくらい届ければいいんだ？";
			link.l1.go = "WM_Captain_3";
		break;
		
		case "WM_Captain_3":
			pchar.questTemp.WPU.Escort.Planks = 300 + hrand(5)*10;
			pchar.questTemp.WPU.Escort.Sailcloth = 150 + hrand(10)*10;
			pchar.questTemp.WPU.Escort.Linen = 70 + hrand(7)*10;
			dialog.text = "俺はもう全部把握してる。今あるものを考慮すると、俺に必要なのは "+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Planks))+" 「板材」 "+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Sailcloth))+" 帆布と "+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Linen))+" 綿だ。これらの材料があれば、一週間で船を修理できるし、それから出航できるぞ。";
			link.l1 = "わかった。必要な材料をすべて持ってくる。待っていてくれ――十日以内には戻るからな。";
			link.l1.go = "WM_Captain_4";
		break;
		
		case "WM_Captain_4":
			dialog.text = "本当にありがとうございます、船長！これで心の荷が下りました。あなたの無事なご帰還を待ちながら祈っています！";
			link.l1 = "心配するな。すぐに修理に必要なものは全部そろうぜ。";
			link.l1.go = "exit";
			AddQuestRecord("Escort", "27");
			AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
			AddQuestUserData("Escort", "sIsland", XI_ConvertString("Colony"+pchar.questTemp.WPU.Current.TargetIslandID));
			AddQuestUserData("Escort", "sQty1", FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Planks)));
			AddQuestUserData("Escort", "sQty2", FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Sailcloth)));
			AddQuestUserData("Escort", "sQty3", FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Linen)));
			Diag.TempNode = "WM_Captain_again";
			SetFunctionTimerCondition("WM_Captain_Over", 0, 0, 11, false);
			pchar.questTemp.WPU.Escort = "wait";
		break;
		
		case "WM_Captain_again":
			dialog.text = "お帰りを心よりお待ちしております、船長！";
			link.l1 = "錨を上げろ！";
			link.l1.go = "exit";
			Diag.TempNode = "WM_Captain_again";
		break;
		
		case "WM_Captain_5":
			dialog.text = "素晴らしい！これで船の修理を始められるぞ！";
			link.l1 = "俺の部下たちが手伝うぜ――そのほうが早いからな。それに、俺もお前を植民地まで案内しなきゃならねえ。 "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity)+"、だから修理が早く終われば終わるほど俺には都合がいいんだ。";
			link.l1.go = "WM_Captain_6";
		break;
		
		case "WM_Captain_6":
			pchar.questTemp.WPU.Current.TargetIslandID.Shore = SelectQuestShoreLocationFromSea(pchar.questTemp.WPU.Current.TargetIslandID);
			dialog.text = "本当に、どう感謝を伝えればいいのかわかりません、船長…。どうか「」という入り江に資材を降ろすよう命じてください\n "+XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID.Shore)+" －そこでは修理の準備がすべて整っている。";
			link.l1 = "いいだろう。岸で会おう。";
			link.l1.go = "exit";
			AddQuestRecord("Escort", "29");
			AddQuestUserData("Escort", "sShore", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID.Shore+"Gen"));
			pchar.quest.DisasterShip_WMC.win_condition.l1 = "location";
			pchar.quest.DisasterShip_WMC.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID.Shore;
			pchar.quest.DisasterShip_WMC.function = "RepairShip_Prepare";
			Diag.TempNode = "WM_Captain_repeat";
		break;
		
		case "WM_Captain_repeat":
			dialog.text = "修理はいつ始めますか、船長？\n岸でお待ちしています。";
			link.l1 = "はい、もちろん。今すぐ出発します。";
			link.l1.go = "exit";
			Diag.TempNode = "WM_Captain_repeat";
		break;
		
		case "Repair_start":
			dialog.text = "さて、修理の準備はすべて整ったようだな。だいたい五日ほどで終わると思うぜ。";
			link.l1 = "よし！どうせこの島を探索するつもりだったから、時間を有効に使わせてもらうぜ。";
			link.l1.go = "Repair_start_1";
		break;
		
		case "Repair_start_1":
			DialogExit();
			pchar.quest.WM_Captain_Over.over = "yes";//снять прерывание
			sld = characterFromId("WMCaptain");
			LAi_SetImmortal(sld, false);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			RemoveCharacterGoods(pchar, GOOD_PLANKS, sti(pchar.questTemp.WPU.Escort.Planks));
			RemoveCharacterGoods(pchar, GOOD_SAILCLOTH, sti(pchar.questTemp.WPU.Escort.Sailcloth));
			RemoveCharacterGoods(pchar, GOOD_COTTON, sti(pchar.questTemp.WPU.Escort.Linen));
			DoQuestFunctionDelay("RepairShip_WithoutMasts", 5.0);
		break;
		
		case "Repair_end":
			dialog.text = "さて、これで終わりだ。修理は全部終わったし、船も出航の準備ができてるぜ。いつ出発するんだ、船長？";
			link.l1 = "準備ができているなら、ここでぐずぐずする意味はねえ。錨を上げろ！";
			link.l1.go = "Repair_end_1";
		break;
		
		case "Repair_end_1":
			DialogExit();
			sld = characterFromId("WMCaptain");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 5.0);
			AddQuestRecord("Escort", "30");
			AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
			AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity));
			SetFunctionTimerCondition("DisasterShipWM_Over", 0, 0, 25, false);
			log_info("You have 25 days to escort "+pchar.questTemp.WPU.Escort.ShipBaseName+" '"+pchar.questTemp.WPU.Escort.ShipName+"' to the port of "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+"");
			pchar.quest.DisasterShip_final.win_condition.l1 = "location";
			pchar.quest.DisasterShip_final.win_condition.l1.location = pchar.questTemp.WPU.Escort.StartCity +"_town";
			pchar.quest.DisasterShip_final.function = "WMShip_final";
		break;
		
		case "WMShip_final":
			pchar.quest.Escort_fail.over = "yes";
			pchar.quest.DisasterShipWM_Over.over = "yes";//снимаем оба прерывания
			RemoveCharacterCompanion(Pchar, characterFromID("WMCaptain"));//удаляем компаньона
			pchar.questTemp.WPU.Escort.LevelUp_1Money = sti(pchar.questTemp.WPU.Escort.Planks)*15+sti(pchar.questTemp.WPU.Escort.Sailcloth)*9+sti(pchar.questTemp.WPU.Escort.Linen)*45;//деньги за материалы
			dialog.text = "もう一度お礼を言いたい、船長。あなたのおかげで、俺と乗組員はあの窮地から抜け出せたんだ。約束通り、 船の修理に必要な資材の代金はお支払いする。こちらが\n "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money))+"、どうぞ、お受け取りください。それと、これは私からあなたへの個人的な贈り物です。";
			link.l1 = "お役に立てて嬉しかったです。";
			link.l1.go = "WMShip_final_1";
		break;
		
		case "WMShip_final_1":
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.LevelUp_1Money));
			TakeNItems(pchar, "obereg_"+(hrand(10)+1), 1);
			dialog.text = "さて、そろそろお別れの時間だ、船長。\n港湾局に寄るのを忘れるなよ――あんたを待ってるぜ。\nまた会おう！";
			link.l1 = "良い一日を。 "+npchar.name+"!";
			link.l1.go = "WMShip_final_2";
		break;
		
		case "WMShip_final_2":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			DialogExit();
			sld = characterFromId("WMCaptain");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1WM")) AddQuestRecord("Escort", "31");
			if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1VSP")) AddQuestRecord("Escort", "37");
			if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1S")) AddQuestRecord("Escort", "40");
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money)));
			AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
			AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
		break;
		
		case "VSP_Captain":
			dialog.text = "そうか？てっきり俺たちは忘れられたのかと思い始めていたところだ。ああ、俺の船が一番ひどい目に遭ったんだ。 嵐で海賊どもが隊商への攻撃を諦めた後、俺たちは荒れ狂う自然と戦う羽目になった。流れ着いたのがこの不毛な岸だ\n数日かけて修理と休息をしていた。出航しようとしたまさにその時、またしても異教徒どもが襲ってきたんだ\nそして再び嵐が襲いかかってきた――今度こそ主が俺たちを終わらせるおつもりかと思ったが、そこへあんたが現れた。聖母マリアに感謝を！ 改めて礼を言うぜ、船長！";
			link.l1 = "すべて終わった、 "+GetAddress_FormToNPC(NPChar)+"。さて、これからあなたを護衛して "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+"、これ以上のトラブルから守るためだ。もう出発する準備はできているか？嵐はすでに収まり始めているぞ。";
			link.l1.go = "VSP_Captain_1";
		break;
		
		case "VSP_Captain_1":
			dialog.text = "もちろんだ！早くここを離れれば離れるほど、俺の部下たちも落ち着くってもんだ――もう十分に苦しんだからな。さあ、出航しようぜ！";
			link.l1 = "俺の船について来い――それと、船員たちを落ち着かせろ。もう怖がることは何もねえぞ。";
			link.l1.go = "VSP_Captain_2";
		break;
		
		case "VSP_Captain_2":
			pchar.quest.DisasterShip_GetOut.over = "yes";
			DialogExit();
			Group_DelCharacter("WMShip", "WMCaptain");//иначе будет клон
			sld = characterFromId("WMCaptain");
			LAi_SetImmortal(sld, false);
			SetCharacterRemovable(sld, false);
			sld.CompanionEnemyEnable = false; //всегда друзья
			SetCompanionIndex(pchar, -1, sti(sld.index));
			sld.loyality = MAX_LOYALITY;
			AddQuestRecord("Escort", "36");
			AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
			SetFunctionTimerCondition("DisasterShipWM_Over", 0, 0, 25, false);
			log_info("You have 25 days to escort "+pchar.questTemp.WPU.Escort.ShipBaseName+" '"+pchar.questTemp.WPU.Escort.ShipName+"' to the port of"+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+"");
			pchar.questTemp.WPU.Escort = "win";
			pchar.quest.Escort_fail.win_condition.l1 = "NPC_Death";//прерывание на потопление сопровождаемого
			pchar.quest.Escort_fail.win_condition.l1.character = "WMCaptain";
			pchar.quest.Escort_fail.function = "DisasterShipWM_failed";
			pchar.quest.DisasterShip_final.win_condition.l1 = "location";
			pchar.quest.DisasterShip_final.win_condition.l1.location = pchar.questTemp.WPU.Escort.StartCity +"_town";
			pchar.quest.DisasterShip_final.function = "WMShip_final";
			Diag.currentnode = "VSP_Captain_again";
			Delete_EscortStorm();//уберем шторм
		break;
		
		case "VSP_Captain_again":
			dialog.text = "出航しますか、船長？";
			link.l1 = "ああ。今から自分の船に戻るぜ。";
			link.l1.go = "exit";
			Diag.TempNode = "VSP_Captain_again";
		break;
		
		case "VSPShip_final":
			pchar.quest.Escort_fail.over = "yes";
			pchar.quest.DisasterShipWM_Over.over = "yes";//снимаем оба прерывания
			RemoveCharacterCompanion(Pchar, characterFromID("WMCaptain"));//удаляем компаньона
			pchar.questTemp.WPU.Escort.LevelUp_1Money = 10000+sti(pchar.rank)*200;
			dialog.text = "もう一度お礼を言いたい、船長――あなたは俺と俺の船員たちがこの窮地を脱するのを大いに助けてくれた。ここにあるのは"+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money))+"。乗組員全員が出し合ったんだ、だから断るなんて考えるなよ。それと、これは俺からの個人的な贈り物だ。";
			link.l1 = "お役に立てて嬉しかったぜ！";
			link.l1.go = "WMShip_final_1";
		break;
		
		case "SShip_final":
			pchar.questTemp.WPU.Escort.LevelUp_1Money = 5000+sti(pchar.rank)*100;
			RemovePassenger(Pchar, npchar);//удаляем пассажира
			dialog.text = "もう一度お礼を言わせてくれ、船長。この厄介事から俺たちを救ってくれてありがとう。さあ、 このコインを受け取ってくれ― "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money))+"  それから、これを受け取ってくれ。大した物じゃないが、君がしてくれたことへの感謝のしるしだ。どうか、 この申し出を断らないでくれ\n俺の元部下たちは、お前とインディアンや海賊との戦いぶりに驚いている。みんなお前の仲間になりたがってるんだ。 船を失ったばかりの忠実な水夫たちの申し出を、どうか断らないでくれよ？";
			link.l1 = "もちろん違うぜ。喜んで預かっておくよ。助けになれて嬉しかったぜ！";
			link.l1.go = "WMShip_final_1";
		break;
		
		//Голландский Гамбит
		case "Stivesant_1":
			DelLandQuestMark(npchar);
			dialog.text = "よろしい。しかし、旦那、ここで何が起きているのか説明してくれないか？どうしてあんたが『Meifeng』の指揮を執っているんだ！？Longwayに何かあったのか？";
			link.l1 = "お前に必要な説明は全部あるぜ――それに他にも大事な情報があるんだ。";
			link.l1.go = "Stivesant_2";			
		break;
		
		case "Stivesant_2":
			dialog.text = "それなら、耳を傾けよう。";
			link.l1 = "ウィレムスタッドでクーデターが起きた。ルーカス・ローデンブルフが総督の座を奪い、 マティアス・ベックをイギリス諜報部との関係があるという馬鹿げた疑いで投獄したんだ。";
			link.l1.go = "Stivesant_3";			
		break;
		
		case "Stivesant_3":
			dialog.text = "ふむ……旦那、あなたがおっしゃっていることは本当に驚きです。私はつい最近ウィレムスタッドから知らせを受け取りましたが、 そんな話はまったくありませんでした。";
			link.l1 = "どうかお聞きください、スタイフェサント旦那。ローデンブルクを通じて知らせを受け取ったはずですし、 彼はあなたがキュラソーに到着できないと確信しているに違いありません。";
			link.l1.go = "Stivesant_4";			
		break;
		
		case "Stivesant_4":
			dialog.text = "旦那、あんたの話はだんだん気に入らなくなってきたぜ。いったい何者なんだ？";
			link.l1 = "俺はただの船長であり、オランダ植民者たちの運命に無関心でいられない一人の男だ。\nルーカス・ローデンブルクがロングウェイにお前の船を沈め、お前も殺すよう命じたんだ。\nそして「メイフェン」ならお前の疑いを引くこともなかったから、やすやすとそれを実行できただろう。";
			link.l1.go = "Stivesant_5";			
		break;
		
		case "Stivesant_5":
			dialog.text = "つまり、ルーカスが……";
			link.l1 = "一番簡単な方法でお前を権力の座から引きずり下ろすことにした――つまり、お前を消すってことだ。他には、この地域でローデンブルクの諸島への影響力にまともに抵抗できる者はいない。 お前以外にはな。";
			link.l1.go = "Stivesant_6";			
		break;
		
		case "Stivesant_6":
			dialog.text = "信じられねえ！";
			link.l1 = "ベックがイギリスの諜報と繋がっているなんて馬鹿げた話には乗らず、自分で調査をしたんだ。\n手練れの殺し屋どもを乗せた『メイフェン』がフィリップスバーグへ向かったことを突き止め、 奴らを追跡して戦いを挑んだ。\nロンウェイを捕らえ、そいつがこの情報を全部吐いたんだ。お前の居場所もな。";
			link.l1.go = "Stivesant_7";			
		break;
		
		case "Stivesant_7":
			dialog.text = "ふむ……それはあり得るな。俺の予定や航路を知っていたのはローデンブルク以外に誰もいなかったし、知り得るはずもなかった！ くそっ！裏切りだ！ロングウェイはどこだ！？";
			link.l1 = "私は彼を自白と引き換えに解放した。正直に言うと、 彼はローデンブルクの命令を実行することにあまり乗り気ではなかったが、無視することもできなかったそうだ。\nそれに、もうローデンブルクの下には戻らないとも言っていた――この最後の汚い仕事で、ついに我慢の限界に達したらしい。";
			link.l1.go = "Stivesant_8";			
		break;
		
		case "Stivesant_8":
			dialog.text = "わかった……船長 "+GetFullName(pchar)+"、お前は俺と一緒にウィレムスタッドへ来てもらう。お前は俺の船より先に『メイフェン』で航海するんだ。 もしお前の言ったことが本当なら、ルーカスは逮捕されるべきだし、お前にも手伝ってもらう。だが、 もし俺に嘘をついていたら……自業自得だぞ。";
			link.l1 = "俺がお前に嘘をつく理由なんてないぜ、旦那。急ごう！";
			link.l1.go = "Stivesant_9";			
		break;
		
		case "Stivesant_9":
			DialogExit();
			Diag.CurrentNode = "Stivesant_10";
			AddQuestRecord("Holl_Gambit", "3-52");
			pchar.questTemp.HWIC.Self = "WayWithStivesant";
			Group_DelCharacter("Stivesant_Halleon", "Stivesant");
			SetCharacterRemovable(npchar, false);
			npchar.CompanionEnemyEnable = false; //всегда друзья
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = 40;
			DeleteAttribute(npchar, "LifeDay");
			pchar.quest.Seek_Piter.win_condition.l1 = "location";
			pchar.quest.Seek_Piter.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Seek_Piter.win_condition.l2 = "Day";
			pchar.quest.Seek_Piter.function = "StivesantOnStreet";
			pchar.quest.Terms_Over.win_condition.l1 = "Timer";
			pchar.quest.Terms_Over.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Terms_Over.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 15);
			pchar.quest.Terms_Over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 15);
			pchar.quest.Terms_Over.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 15);
			pchar.quest.Terms_Over.function = "QuestShipsTerms_Over";
			AddMapQuestMarkCity("Villemstad", false);
		break;
		
		case "Stivesant_10":
			dialog.text = "船長、「Meifeng」へ行ってくれ。出航の時間だ。";
			link.l1 = "はい、旦那、もちろんです。";
			link.l1.go = "exit";
			Diag.TempNode = "Stivesant_10";
		break;
		
		case "Keller_1":
			dialog.text = "とても興味深いな！さあ、君の話を聞かせてくれ。俺もできる限り力になるぜ。";
			link.l1 = "ケラー旦那、数か月前ウィレムスタッドへ向かう途中でフリュート船に出会ったことを覚えているか？ その船にはユダヤ人難民の家族が乗っていた。あんたはその船で食事をしてから旅を続けたんだ。";
			link.l1.go = "Keller_2";
		break;
		
		case "Keller_2":
			dialog.text = "ああ、そうだと思う……うん、今はっきり思い出したよ。で、どういう話なんだ？";
			link.l1 = "そのフルート船はまさにその日に海賊に沈められたんだ。難民として助かったのは二人だけ――ソロモンと、その娘アビゲイルだ。彼らは襲撃があった場所から数マイル離れた島に避難した。 俺はその島を探さなきゃならねえ。あんたがそのフルート船を見かけた場所を思い出してくれないか？ これはとても重要なんだ。";
			link.l1.go = "Keller_3";
		break;
		
		case "Keller_3":
			dialog.text = "それだけでいいのか？この島なら知ってるぜ。すぐ近くだ、トリニダードとキュラソーの間にな。小さくて、無人で、 誰も住んでねえ島だ。インディオさえいねえぞ。";
			link.l1 = "「そのおおよその座標は分かるか？」";
			link.l1.go = "Keller_4";
		break;
		
		case "Keller_4":
			dialog.text = "正確な座標を教えてやろう。北緯12度48分、西経64度41分の場所だ。そこで探してみな。島はかなり小さいが、簡単に見つけられるはずだ。";
			link.l1 = "ありがとうございます、ケラー旦那！大いに助かりました。では、ごきげんよう。";
			link.l1.go = "Keller_5";
		break;
		
		case "Keller_5":
			DialogExit();
			Diag.CurrentNode = "Keller_6";
			pchar.quest.Keller_fail.over = "yes";
			pchar.questTemp.HWIC_Coordinates = "true"; //атрибут координат на поиск острова через каюту
			DeleteAttribute(pchar, "questTemp.HWICMC");
			AddQuestRecord("Holl_Gambit", "3-66");
		break;
		
		case "Keller_6":
			dialog.text = "他にご用はありますか、船長？";
			link.l1 = "いいえ、結構です。ちょうど自分の船に戻るところでした。";
			link.l1.go = "exit";
			Diag.TempNode = "Keller_6";
		break;
		
		// belamour рыбацкое судно -->
		case "FishingBoat":
			pchar.GenQuest.FishingBoatSecondTime = true;
			dialog.text = "特に変わったことはないさ、ここは漁船だ、魚を獲って生計を立ててるんだ。何かしら稼がなきゃならねえからな。";
			link.l1 = "ああ、同感だ、まさにそんな時代だな……";
			link.l1.go = "FishingBoat_1";			
		break;
		
		case "FishingBoat_1":
			Diag.TempNode = "FishingBoat_1";
			dialog.text = "それで、何の用だ？";
			link.l1 = "欲しかった"+GetSexPhrase("","")+" 諸島の最新情報を知るために。";
            link.l1.go = "rumours_capitan";
			link.l2 = "今日の漁獲はどうだ？売れるものはあるか？食料を少し分けてくれると助かるんだが…";
			link.l2.go = "FishingBoat_2";
			link.l3 = "特に用はないけど、ちょっと挨拶しに来ただけだぜ！";
    		link.l3.go = "exit";	
	
		break;
		
		case "FishingBoat_2":
			if(GetDataDay() < 11) 
			{
				if(sti(RealShips[sti(npchar.ship.type)].basetype) == SHIP_TARTANE) iTemp = 100 + hrand(100);
				else iTemp = 200 + hrand(100);
				iMoney = sti(GetCurrentIslandGoodsPrice(GOOD_FOOD)*0.66);
				pchar.GenQuest.FishingBoatITemp = iTemp;
				pchar.GenQuest.FishingBoatIMoney = iMoney;
				
				dialog.text = "今日は大漁だ、あとは網を引き上げる時間さえあればいい。あんたにも売れるぜ、店より安くな。 どうせ地元の商人にも魚を卸してるんだ。これを全部食糧に換算すると……今あるのは\n "+iTemp+" それなら、売ればこの値段になる "+iMoney+" 1枚あたりペソだ。いくつ欲しいんだ？";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта";
				link.l2 = "あのな、お前の食料を買う気が変わったんだ。";	
				link.l2.go = "exit";
				
			}
			if(GetDataDay() > 10 && GetDataDay() < 21) 
			{
				Diag.TempNode = "FishingBoat_1";
				dialog.text = "ああ、そうだな、正直に言うと魚が全然いないんだ……今日はほとんど何も獲れなかったよ。だが、銛は余ってる――運が良ければ大物かクジラでも仕留められるかと思ってな……銛が欲しいのかい？";
				link.l1 = "いや、俺は銛には興味ねえんだ。";
				link.l1.go = "exit";
				link.l2 = "ふむ、銛も使いようによっては役に立つもんだな。たぶん買うとするか。";
				link.l2.go = "Гарпуны";
			}
			if(GetDataDay() > 20)
			{
				dialog.text = "ああ、実はな、魚は全然いねえんだ……今日はほとんど何も獲れなかった。だから売るものもあまりねえんだよ。だが……ちょっとしたガラクタならあるぜ、もしかしたら興味があるかもな。見ていくかい？";
				link.l1 = "いや、ガラクタには興味ねえんだ。";
				link.l1.go = "exit";
				link.l2 = "獲物がないのは残念だな。まあ、せめてお前のガラクタを見せてもらおうか――何か気になるものがあるかもしれねえ・・・";
				link.l2.go = "Торговля";
			}	
		break;
		
		case "Количество вбитого провианта":
			Diag.TempNode = "FishingBoat_1";
			iQty = sti(dialogEditStrings[3]);
			iTemp = makeint(pchar.GenQuest.FishingBoatITemp);
			pchar.GenQuest.FishingBoatIQty = iQty;
			iMoney = makeint(pchar.GenQuest.FishingBoatIMoney);
			if(iQty > iTemp)
			{
				dialog.text = "そんなに多すぎる……そんなに持ってないよ！もっと少なく買えないか？";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта повтор";	
				link.l2 = "あのな、やっぱりお前の食糧を買うのはやめることにしたぜ。";	
				link.l2.go = "exit";
			}	
			if(iQty < 1)
			{
				dialog.text = "冗談じゃねえだろ？食料が必要なのか？必要なら、どれくらい欲しいんだ？";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта повтор";	
				link.l2 = "あのな、やっぱりお前の食料を買うのはやめたぜ。";	
				link.l2.go = "exit";
			}
			if(iQty > 0 && iQty <= iTemp)
			{
				dialog.text = "「取引成立だ！」 "+sti(iQty*iMoney)+" ペソ。";
				if(sti(pchar.money) < iQty*iMoney)
				{
					link.l1 = "うーん、そんなに金は持ってねえな。別の機会にしてくれ。";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "取引成立だ！品物を俺の船に持ってこい。";
					link.l1.go = "Удачная покупка";
					link.l2 = "あのな、お前の食料を買うのはやめることにしたぜ。";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "Количество вбитого провианта повтор":
			Diag.TempNode = "FishingBoat_1";
			iQty = sti(dialogEditStrings[3]);
			iTemp = makeint(pchar.GenQuest.FishingBoatITemp);
			pchar.GenQuest.FishingBoatIQty = iQty;
			iMoney = makeint(pchar.GenQuest.FishingBoatIMoney);
			if(iQty > iTemp)
			{
				dialog.text = "そんなに多すぎる……そんなに持ってないよ！もっと少なく買ってくれないか？";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта";	
				link.l2 = "あのな、お前の食料を買う気が変わったんだ。";	
				link.l2.go = "exit";
			}	
			if(iQty < 1)
			{
				dialog.text = "冗談じゃねえよな？食料が必要なのか？必要なら、どれくらい欲しいんだ？";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта";	
				link.l2 = "あのな、お前の食料を買う気が変わったんだ。";	
				link.l2.go = "exit";
			}
			if(iQty > 0 && iQty <= iTemp)
			{
				dialog.text = "「取引成立だ！」 "+sti(iQty*iMoney)+" ペソ。";
				if(sti(pchar.money) < iQty*iMoney)
				{
					link.l1 = "うーん、そんなに金は持ってねえな。別の機会にしてくれ。";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "取引成立だ！俺の船に貨物を積み込め。";
					link.l1.go = "Удачная покупка";
					link.l2 = "あのな、お前の食料を買うのはやめることにしたぜ。";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "Удачная покупка":
			Diag.TempNode = "First time";
			Diag.CurrentNode = "First time";
			iQty = makeint(pchar.GenQuest.FishingBoatIQty);
			iMoney = makeint(pchar.GenQuest.FishingBoatIMoney);
			iTemp = iQty*iMoney;
			DialogExit();
			SetCharacterGoods(pchar, GOOD_FOOD, GetCargoGoods(pchar, GOOD_FOOD)+iQty);
			AddMoneyToCharacter(pchar, -iTemp);
		break;
		
		case "Гарпуны":
				Diag.TempNode = "FishingBoat_1";
				iTemp = 5+hrand(5);
				pchar.GenQuest.FishingBoatITemp = iTemp;
				dialog.text = "我々には "+iTemp+" 部品だ。一本の銛につき百ペソで売れるぜ。何本必要なんだ？";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов";
				link.l2 = "あのな、やっぱり気が変わったんだ、銛はいらねえよ。";	
				link.l2.go = "exit";
		break;
		
		case "Количество вбитых гарпунов":
   
			iQty = sti(dialogEditStrings[3]);
			iTemp = makeint(pchar.GenQuest.FishingBoatITemp);
			pchar.GenQuest.FishingBoatIQty = iQty;
			Diag.TempNode = "FishingBoat_1";
			if(iQty > iTemp)
			{
				dialog.text = "そんなに高すぎるよ……そんなに持ってないんだ！もっと少なく買ってくれないか？";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов заново";	
				link.l2 = "あのな、やっぱり気が変わった。銛はいらねえよ。";	
				link.l2.go = "exit";
			}	
			if(iQty < 1)
			{
				dialog.text = "冗談じゃねえだろうな？銛が必要なのか？そうなら、何本いるんだ？";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов заново";	
				link.l2 = "あのな、やっぱり気が変わったんだ、銛はいらねえよ。";	
				link.l2.go = "exit";
			}
			if(iQty > 0 && iQty <= iTemp)
			{
				dialog.text = "「取引成立だ！」 "+sti(iQty*100)+" ペソ。";
				if(sti(pchar.money) < iQty*100)
				{
					link.l1 = "うーん、そんなに金は持ってねえな。別の機会にしてくれ。";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "取引成立だ！俺がうまく使ってやるぜ。";
					link.l1.go = "Удачная покупка гарпунов";
					link.l2 = "なあ、やっぱり気が変わったんだ、銛はいらねえよ。";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "Количество вбитых гарпунов заново":
			iQty = sti(dialogEditStrings[3]);
			iTemp = makeint(pchar.GenQuest.FishingBoatITemp);
			pchar.GenQuest.FishingBoatIQty = iQty;
			Diag.TempNode = "FishingBoat_1";
			if(iQty > iTemp)
			{
				dialog.text = "そんなに多すぎるよ……そんなに持ってないんだ！もっと少なく買ってくれないか？";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов";	
				link.l2 = "あのな、気が変わったんだ、銛はいらねえよ。";	
				link.l2.go = "exit";
			}	
			if(iQty < 1)
			{
				dialog.text = "ふざけてるのか？銛が必要なんだろ？そうなら、何本いるんだ？";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов";	
				link.l2 = "あのな、気が変わったんだ、銛はいらねえよ。";	
				link.l2.go = "exit";
			}
			if(iQty > 0 && iQty <= iTemp)
			{
				dialog.text = "取引成立だ！ "+sti(iQty*100)+" ペソ。";
				if(sti(pchar.money) < iQty*100)
				{
					link.l1 = "うーん、そんなに金は持ってねえな。別の機会にしてくれ。";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "取引成立だ！俺がうまく使ってやるぜ。";
					link.l1.go = "Удачная покупка гарпунов";
					link.l2 = "あのな、やっぱり気が変わったんだ、銛はいらねえよ。";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "Удачная покупка гарпунов":
			DialogExit();
			Diag.TempNode = "First time";
			Diag.CurrentNode = "First time";
			iQty = makeint(pchar.GenQuest.FishingBoatIQty);
			TakeNItems(pchar, "slave_01", iQty);
			AddMoneyToCharacter(pchar, -iQty*100);
			
		break;
		
		case "Торговля":
			DialogExit();
			Diag.TempNode = "First time";
			Diag.CurrentNode = "First time";
			if(!CheckAttribute(pchar,"GenQuest.FishingBoatDialogEnb")) pchar.GenQuest.FishingBoatDialogEnb = true;
			LaunchItemsTrade(NPChar, 0);
		break;
		
		case "Особые товары":
			if(hrand(2, "&SpeGoo") == 0)
			{
				Diag.TempNode = "First time";
				Diag.CurrentNode = "First time";
				pchar.GenQuest.FishingBoatDialogEnb = "no special goods";
				dialog.text = "いや、他には何もない。漁船だぜ！他に何があるってんだ？";
				link.l1 = "わかったよ。";
				link.l1.go = "exit";
			}
			else if(hrand(2, "&SpeGoo") == 1)
			{
				if(ChangeContrabandRelation(pchar, 0) > 5)
				{
					
					dialog.text = "ええと…ここにちょっとした物があるんだ…取っておいたんだが、誰かに売ろうと思ってな。だが高くつくぜ！二度とこの話はしない。見るかい？";
					link.l1 = "見せてみろ、どんな小物か見てやろう。";
					link.l1.go = "Особые товары предметы";
				}
				else
				{
					Diag.TempNode = "First time";
					Diag.CurrentNode = "First time";
					pchar.GenQuest.FishingBoatDialogEnb = "no special goods";
					dialog.text = "いや、他には何もねえ。漁船だぜ！他に何があるってんだ？";
					link.l1 = "わかったよ。 ";
					link.l1.go = "exit";
				}
			}
			else
			{
				pchar.GenQuest.FishingBoatDialogEnb = "no special goods";
				Diag.TempNode = "First time";
				Diag.CurrentNode = "First time";
				if(ChangeContrabandRelation(pchar, 0) > 5)
				{
					if(GetDataDay() < 8)
					{	
						iMoney = GetStoreGoodsPrice(&Stores[SantaCatalina_STORE], GOOD_SANDAL, PRICE_TYPE_BUY, pchar, 1);
						iTemp = GOOD_SANDAL;
						sTemp = "units of backout";
					}
					if(GetDataDay() > 7 && GetDataDay() < 15)
					{
						iMoney = GetStoreGoodsPrice(&Stores[PortSpein_STORE], GOOD_OIL, PRICE_TYPE_BUY, pchar, 1);
						iTemp = GOOD_OIL;
						sTemp = "barrels of ship tar"; 
					}
					if(GetDataDay() > 14 && GetDataDay() < 22) 
					{
						iMoney = GetStoreGoodsPrice(&Stores[BasTer_STORE], GOOD_ROPES, PRICE_TYPE_BUY, pchar, 1);
						iTemp = GOOD_ROPES;
						sTemp = "bays of ship ropes"; 
					}
					if(GetDataDay() > 21) 
					{
						iMoney = GetStoreGoodsPrice(&Stores[Villemstad_STORE], GOOD_SHIPSILK, PRICE_TYPE_BUY, pchar, 1);
						iTemp = GOOD_SHIPSILK;
						sTemp = "rolls of ship silk";
					}
					iQty = 20 + sti(rand(6)*5);
					pchar.GenQuest.FishingBoatITemp = iTemp;
					pchar.GenQuest.FishingBoatIMoney = iMoney;
					pchar.GenQuest.FishingBoatIQty = iQty;
					
					dialog.text = "さて……いいものがここにあるんだ……まったくの偶然で、湾の岸辺で見つけたんだ。それは\n "+iQty+" "+sTemp+"。1個あたりの値段は "+iMoney+"。だが、全部まとめて一度きりしか売らねえし、二度目はねえぞ。それに、よそ者には絶対に知られたくねえ……わかったか？";
					link.l1 = "いや、怪しい品物はいらないよ、ありがとう。誰にも言わないから、安心しな。";
					link.l1.go = "exit";
					if(sti(pchar.money) >= iMoney*iQty)
					{
						link.l2 = "分かった。だが、その品はそれだけの価値がある。俺が買う。あいつを俺の船に運ばせろ。";
						link.l2.go = "Купили стратегический товар";
					}
				}
			}
		break;
		
		case "Особые товары предметы":
			pchar.GenQuest.FishingBoatDialogEnb = "no special goods";
			Diag.TempNode = "First time";
			Diag.CurrentNode = "First time";
			if(ChangeContrabandRelation(pchar, 0) > 5)
			{
				switch(GetDataDay())
				{
					case 21: sTemp = "mushket1";  break;
					case 22: sTemp = "cirass5";   break;
					case 23: sTemp = "blade_16";  break;
					case 24: sTemp = "blade_04";  break;
					case 25: sTemp = "blade_06";  break;
					case 26: sTemp = "compass1";  break;
					case 27: sTemp = "clock2";    break;
					case 28: sTemp = "pistol4";   break;
					case 29: sTemp = "pistol2";   break;
					case 30: sTemp = "obereg_9";  break;
					case 31: sTemp = "obereg_10"; break;	
				}
				pchar.GenQuest.FishingBoatSTemp = sTemp;
				dialog.text = "それは "+GetItemName(sTemp)+"…手に入れたんだが…まあ、どこでかは気にするな。目利きに売ろうと思ってたんだが、あんたになら一万ペソで譲ってやるぜ！どうだ、 買うか？";
				if(sti(pchar.money) > 9999)
				{
					link.l1 = "もちろん、俺がもらうぜ！物はちゃんと立ってるからな。 ";
					link.l1.go = "Купили особый товар";
				}
				link.l2 = "いや、いらねえ。受け取らねえよ。 ";
				link.l2.go = "exit";
			}
		
		break;
		
		case "Купили особый товар":
			Diag.TempNode = "First time";
			Diag.CurrentNode = "First time";
			DialogExit();
			sTemp = pchar.GenQuest.FishingBoatSTemp;
			if(GetDataDay() != 23 || GetDataDay() != 24 || GetDataDay() != 25) 
			{
				TakeNItems(pchar, sTemp, 1);
			}
			else
			{
				sTemp = GetGeneratedItem(sTemp);
				GiveItem2Character(pchar, sTemp);
			}
			AddMoneyToCharacter(pchar, -10000);
		break;
		
		case "Купили стратегический товар":
			Diag.TempNode = "First time";
			Diag.CurrentNode = "First time";
			iQty = makeint(pchar.GenQuest.FishingBoatIQty);
			iMoney = makeint(pchar.GenQuest.FishingBoatIMoney);
			iTemp = makeint(pchar.GenQuest.FishingBoatITemp);
			DialogExit();
			SetCharacterGoods(pchar, iTemp, GetCargoGoods(pchar,iTemp)+iQty);
			AddMoneyToCharacter(pchar, -iMoney*iQty);
		break;
		// <-- рыбацкое судно
	}
}

string GetNumShips(int ship)
{
    string numships;
    switch(ship)
    {
       case 0: numships = "no ships"; break;
       case 1: numships = "one ship";      break;
       case 2: numships = "two ships";       break;
       case 3: numships = "three ships";       break;
       case 4: numships = "four ships";    break;
       case 5: numships = "five ships";     break;
       case 6: numships = "six ships";    break;
    }
    return numships;
}

string GetPart(int part)
{
    string numpart;
    switch(part)
    {
       case 0: numpart = ""; break;
       case 1: numpart = "all loot"; break;
       case 2: numpart = "half of the loot"; break;
       case 3: numpart = "third of the loot"; break;
       case 4: numpart = "quarter of the loot";      break;
    }
    return numpart;
}

int findPriceStoreMan(ref NPChar)
{
    ref ch;
	int n;
    int storeArray[40];
    int howStore = 0;

	for(n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(ch,Characters[n]);
		if (CheckAttribute(ch, "Dialog.Filename") && ch.Dialog.Filename == "Common_Store.c") // магазин
		{
            //if (sti(ch.nation) !=  sti(NPChar.nation)) continue;
            if (ch.location == "none") continue; // фикс для новых, невидимых до поры островов
            storeArray[howStore] = n;
            howStore++;
            
            // homo 05/09/06
            if ( CheckAttribute(NPChar, "FromColony") && NPChar.FromColony == ch.City ) return n;
            //
		}
    }
    if (howStore == 0)
    {
        return -1;
    }
    else
    {
        return storeArray[rand(howStore-1)];
    }
}

int CalcBattleDifficulty()
{
    UpdatePlayerSquadronPower();

    float encPow = 0.0;
    float pchPow = stf(PChar.Squadron.RawPower);

    string sTemp;
    if(CheckAttribute(CharacterRef, "SeaAI.Group.Name"))
        sTemp = CharacterRef.SeaAI.Group.Name;
    else return 0;

    int	iGroupIndex = Group_FindGroup(sTemp);
    if (iGroupIndex < 0)
    {
        Log_TestInfo("НЕТ ГРУППЫ В CalcBattleDifficulty");
        trace("НЕТ ГРУППЫ В CalcBattleDifficulty");
        return 0;
    }

    ref rGroup = Group_GetGroupByIndex(iGroupIndex);
    if (!CheckAttribute(rGroup, "Quest")) return 0;

    aref aCompanions, aCharInfo;
    makearef(aCompanions, rGroup.Quest);
    int qty = GetAttributesNum(aCompanions);

    ref rChar, rShip;
    int iShipType, idx;
    for(int i = 0; i < qty; i++)
    {
        aCharInfo = GetAttributeN(aCompanions, i);
        idx = sti(aCharInfo.index);
        if(idx == -1) continue;
        rChar = GetCharacter(idx);
        if(!CheckAttribute(rChar, "index") || rChar.index == "none" || LAi_IsDead(rChar)) continue;
        iShipType = sti(rChar.Ship.Type);
        if(iShipType == SHIP_NOTUSED) continue;
        rShip = GetRealShip(iShipType);
        encPow += GetRealShipPower(rChar);
    }

    iEncPow = encPow;

    if(pchPow == 0.0)
    {
        if(encPow == 0.0) return 50;
        return 0;
    }

    float fRatio = (encPow * 0.9) / pchPow;

    if(fRatio >= 1.7) return 0; // Кирдык
    // От 50 шанс быстро падает к 0
    if(fRatio >= 1.0)
    {
        return MakeInt(100 * 0.5 * pow((1.7 - fRatio) / 0.7, 2.5));
    }
    // От 50 шанс медленно растёт к 100
    return MakeInt(100 * (0.5 + 0.5 * pow((1 - fRatio), 0.5)));
}
