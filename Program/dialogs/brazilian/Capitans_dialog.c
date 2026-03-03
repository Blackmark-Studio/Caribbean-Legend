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
					dialog.text = "Olá, capitão. Caramba, você não faz ideia de como estou feliz em te ver!";
					link.l1 = "Oi. Permita-me apresentar - "+GetFullName(PChar)+". Fico feliz em ver que você também está vivo e bem, vim aqui justamente para procurar por você – e pelo seu navio.";
					link.l1.go = "WM_Captain";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1WM") && pchar.questTemp.WPU.Escort == "wait" && NPChar.id == "WMCaptain")
				{
					dialog.text = "Você trouxe os materiais que pedi?";
					if (sti(pchar.questTemp.WPU.Escort.Planks) - GetSquadronGoods(pchar, GOOD_PLANKS) <= 0 && sti(pchar.questTemp.WPU.Escort.Sailcloth) - GetSquadronGoods(pchar, GOOD_SAILCLOTH) <= 0 && sti(pchar.questTemp.WPU.Escort.Linen) - GetSquadronGoods(pchar, GOOD_COTTON) <= 0)
					{
						link.l1 = "Sim. Tudo o que você precisa para consertar seu navio está no meu porão.";
						link.l1.go = "WM_Captain_5";
					}
					else
					{
						link.l1 = "Não, ainda estou trabalhando nisso.";
						link.l1.go = "exit";
					}
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1VSP") && pchar.questTemp.WPU.Escort == "toCap" && NPChar.id == "WMCaptain")
				{
					dialog.text = "Ahoy, "+GetAddress_Form(NPChar)+". Meu nome é "+GetFullName(NPChar)+", eu sou o capitão deste navio. Permita-me expressar minha mais sincera gratidão pela sua ajuda na luta contra aqueles malditos piratas — se você não tivesse intervindo, as coisas poderiam ter terminado muito mal para nós. Você realmente nos salvou, caramba!";
					link.l1 = "Não foi nada,  "+GetAddress_FormToNPC(NPChar)+". Permita-me apresentar - "+GetFullName(PChar)+", vim até você a pedido do mestre do porto "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+". Ele me contou sobre os infortúnios da sua caravana e me mandou procurar o seu navio.";
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
					dialog.text = "Espere, desse jeito você pode me matar. O que você quer de mim?";
					//выкуп
					link.l1 = "Vamos resolver isso de forma pacífica. Um resgate, creio eu, será a melhor decisão. Uma quantia de "+Pchar.GenQuest.MoneyForCaptureShip+" pesos vão me servir muito bem, "+GetAddress_FormToNPC(NPChar)+". E depois disso, pode sumir!";
					link.l1.go = "surrender1";
					// обираем до нитки
					link.l2 = "Quero ver o que você tem no porão. E depois disso, você e sua tripulação podem ir para onde quiserem.";
					link.l2.go = "surrender2";
					break;
				}
				
				//Голландский Гамбит, против всех
				if (CheckAttribute(PChar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "MeetingStivesant" && NPChar.id == "Stivesant")
				{
					dialog.text = "Olá, senhor. Que bom te ver. O capitão Longway provavelmente vai embarcar mais tarde, não é?";
					link.l1 = "Boa tarde, senhor Stuyvesant. Permita-me apresentar-me - "+GetFullName(pchar)+". Longway não vai vir, ele não está no 'Meifeng'.";
					link.l1.go = "Stivesant_1";
					pchar.quest.QuestShipsTerms_Over.over = "yes"; //снять таймер
					break;
				}
				if (CheckAttribute(PChar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "FleutOnTrinidad" && NPChar.id == "Keller")
				{
					DelLandQuestMark(npchar);
					dialog.text = "Ah, capitão. O que te traz à minha flauta?";
					link.l1 = "Boa tarde, senhor Keller. Permita-me apresentar-me - "+GetFullName(pchar)+". Vim buscar sua ajuda em um assunto incomum.";
					link.l1.go = "Keller_1";
					break;
					//Голландский гамбит
				}
				// belamour рыбацкое судно -->
				if(npchar.id == "FishingBoatCap")
				{
					if(!CheckAttribute(pchar, "GenQuest.FishingBoatSecondTime"))
					{
						Dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! Eu sou o capitão do "+GetFullName(NPChar)+". O que te traz a bordo do meu navio?";
						link.l1 = "E um bom dia pra você. O que te traz a esta baía?";
						link.l1.go = "FishingBoat";
						break;
					}
					else
					{
						Diag.CurrentNode = "first time";
						dialog.text = "Gostaria de conversar sobre mais alguma coisa?";
						link.l1 = "Eu queria"+GetSexPhrase("","")+" para saber as últimas novidades do arquipélago.";
						link.l1.go = "rumours_capitan";
						if(CheckAttribute(pchar,"GenQuest.FishingBoatDialogEnb"))
						{
							link.l2 = "Mostre-me de novo, por favor, que tipo de bugigangas você tem à venda. ";
							link.l2.go = "Торговля";
							if(pchar.GenQuest.FishingBoatDialogEnb != "no special goods")
							{
								link.l3 = "Hum, talvez dê uma olhada melhor no porão – quem sabe encontre algo para vender?";
								link.l3.go = "Особые товары";
							}
						}
						link.l4 = "Nada de especial, só vim te cumprimentar!";
						link.l4.go = "exit";	
						break;
					}
				}
				// <-- рыбацкое судно
				
				//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
				// генерал губернатор
				if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
				{
					Dialog.text = "Governador Geral, Vossa Graça, saudações! Em que posso servi-lo?";
					link.l1 = "Tenho um trabalho para você!";
					link.l1.go = "quests";
					link.l2 = "Nada de especial, só vim dar um oi!";
					link.l2.go = "exit";
					break;
				}
				// вице адмирал
				if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && sti(Items[sti(pchar.EquipedPatentId)].Nation) == npchar.nation)
				{
					Dialog.text = "Bem-vindo a bordo do meu navio, Vice-Almirante! Em que posso ajudá-lo?";
					link.l1 = "Tenho um trabalho para você!";
					link.l1.go = "quests";
					link.l2 = "Nada de especial, só vim te cumprimentar!";
					link.l2.go = "exit";
					break;
				}
				// Офицер с патентом
				if(IsOfficerFullEquip() && sti(Items[sti(pchar.EquipedPatentId)].Nation) == npchar.nation)
				{
					Dialog.text = "Fico feliz em ver um colega de trabalho, Capitão! Como posso ajudar?";
					link.l1 = "Tenho um serviço pra você!";
					link.l1.go = "quests";
					link.l2 = "Nada de especial, só vim dar um oi!";
					link.l2.go = "exit";
					break;
				}			
				// <-- legendary edition
                if (CheckAttribute(NPChar, "EncType")  && NPChar.EncType == "war")
                {
    			    Dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! Eu sou "+GetFullName(NPChar)+" - capitão de um navio pertencente ao "+NationKingsName(NPChar)+". esquadra. O que te trouxe a bordo do meu navio?";
    			}
    			else
                {
    			    Dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! Eu sou o capitão "+GetFullName(NPChar)+". O que te trouxe a bordo do meu navio?";
    			}
    			link.l1 = "Meu nome é "+GetFullName(Pchar)+". Eu tenho um assunto para tratar com você!";
    			link.l1.go = "quests";
                link.l2 = "Ah, nada, só "+GetSexPhrase("veio","veio")+" para cumprimentar você!";
    			link.l2.go = "exit";
            }
            else
            {
                Dialog.text = "Você não percebeu, , "+GetAddress_Form(NPChar)+", que estamos em uma batalha? Agora não é hora de conversar!";
    			link.l1 = "Concordo plenamente! Vou voltar para o meu navio.";
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
					Dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! Eu sou o capitão do "+GetFullName(NPChar)+". O que te traz a bordo do meu navio?";
					link.l1 = "E um bom dia para você. O que está fazendo nesta baía?";
					link.l1.go = "FishingBoat";
					break;
				}
				else
				{
					dialog.text = "Há mais alguma coisa que você gostaria de discutir?";
					link.l1 = "Eu queria"+GetSexPhrase("","")+" para descobrir as últimas notícias do arquipélago.";
					link.l1.go = "rumours_capitan";
					if(CheckAttribute(pchar,"GenQuest.FishingBoatDialogEnb"))
					{
						link.l2 = "Mostre-me de novo, por favor, que tipo de bugigangas você tem à venda. ";
						link.l2.go = "Торговля";
						if(pchar.GenQuest.FishingBoatDialogEnb != "no special goods")
						{
							link.l3 = "Hum, talvez dê uma olhada melhor no porão – quem sabe aparece algo pra vender?";
							link.l3.go = "Особые товары";
						}
					}
					link.l4 = "Nada de especial, só vim dar um oi!";
					link.l4.go = "exit";	
					break;
				}
			}
			// <-- рыбацкое судно
            if (!CheckAttribute(NPChar, "MainCaptanId")  || NPChar.MainCaptanId == pchar.GenQuest.CaptainId)
            {
                Dialog.text = "Estou ouvindo você com muita atenção,  "+GetAddress_Form(NPChar)+".";
                link.l1 = "Quero ouvir as últimas novidades do arquipélago.";
                //homo 25/06/06
                link.l1.go = "rumours_capitan";
                //belamour legendary edition 
				bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
				bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
				bOk = bOk1 || bOk2;
                if (CheckAttribute(NPChar, "EncGroupName") && !bOk) // только для фантомов грабеж
                {
                    iCapBattleDifficulty = CalcBattleDifficulty();
                    link.l2 = "(Chance de intimidação: "+iCapBattleDifficulty+"%%) "+RandPhraseSimple("Você ao menos sabe quem eu sou? Acho que está claro que meus canhões podem transformar seu barco em uma peneira. Vamos resolver isso em paz. Um resgate me serve muito bem.","Viu? Está bem aqui, em mar aberto... Que tal fazer uma pequena oferta para manter meus rapazes de bom humor? Só pela segurança dos seus também.");
                    link.l2.go = "Talk_board";
                }
                if (CheckAttribute(NPChar, "Ship.Mode") && NPChar.Ship.Mode == "Trade")
                {
	           		link.l3 = "De onde você está vindo?";
	    			link.l3.go = "price_1";
	    			link.l4 = "Quer negociar?";
	    			link.l4.go = "Trade_1";
    			}
				//--> квест мэра, поиски пирата
				if (CheckAttribute(pchar, "GenQuest.DestroyPirate"))
				{
	    			link.l6 = "Estou procurando por um navio pirata que esteja operando nessas águas. Você viu algo suspeito?";
	    			link.l6.go = "MQ_step_1";
				}
				//<-- квест мэра, поиски пирата
    			link.l5 = "Quer relaxar?";
			    link.l5.go = "Play_Game";
                link.l9 = "Acho que é melhor eu ir.";
    			link.l9.go = "exit";
			}
			else
			{
                Dialog.text = "Não estou autorizado a tratar com você. Fale com o comandante do nosso esquadrão. O nome dele é  "+GetFullName(characterFromID(NPChar.MainCaptanId))+", você pode encontrá-lo no "+XI_ConvertString(RealShips[sti(characters[GetCharacterIndex(NPChar.MainCaptanId)].Ship.Type)].BaseName)+" '"+characters[GetCharacterIndex(NPChar.MainCaptanId)].Ship.Name+"'.";
                link.l1 = "Obrigado. Vou fazer como você disse.";
                link.l1.go = "exit";
                Diag.TempNode = "Go_away_Good";
			}
        break;
        case "Trade_1":
			dialog.text = "Por que não?";
			link.l1 = "Vamos dar uma olhada nas mercadorias.";
			link.l1.go = "Trade_2";
			link.l2 = "Mudei de ideia.";
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
			dialog.text = "O que você está sugerindo?";
			link.l1 = "Que tal uma partida de cartas valendo dinheiro de verdade?";
			link.l1.go = "Card_Game";
   			link.l2 = "Que tal jogar uns dados no pôquer joker?";
			link.l2.go = "Dice_Game";
			link.l10 = "Me desculpe, mas tenho alguns assuntos para resolver.";
			link.l10.go = "exit";
		break;
        // карты -->
        case "Card_Game":
            if (!CheckNPCQuestDate(npchar, "Card_date_Yet") || isBadReputation(pchar, 30) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(3))
            {
                SetNPCQuestDate(npchar, "Card_date_Yet");
                dialog.text = "Eu não vou apostar com bandidos!";
    			link.l1 = "Como quiser.";
    			link.l1.go = "exit";
			}
			else
			{
                dialog.text = "Por que não? Eu certamente não me importaria de fazer uma pausa...";
    			link.l1 = "Excelente.";
    			link.l1.go = "Cards_begin";
    			link.l2 = "Quais são as regras?";
    			link.l2.go = "Cards_Rule";
			}
		break;

		case "Cards_Rule":
   			dialog.text = CARDS_RULE;
			link.l1 = "Então, vamos começar, né!";
			link.l1.go = "Cards_begin";
			link.l3 = "Não, não é pra mim...";
			link.l3.go = "exit";
		break;

		case "Cards_begin":
			Dialog.text = "Vamos acertar a aposta primeiro.";
			link.l1 = "Vamos jogar por 100 pesos.";
			link.l1.go = "Cards_Node_100";
			link.l2 = "Vamos jogar por 500 pesos.";
			link.l2.go = "Cards_Node_500";
			link.l3 = "Acho que é melhor eu ir.";
			link.l3.go = "exit";
		break;

		case "Cards_Node_100":
		    if (sti(pchar.Money) < 300)
		    {
                dialog.text = "Está brincando ou o quê? Você não tem dinheiro!";
                link.l1 = "Acontece.";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 300)
		    {
                dialog.text = "Bem, já chega, senão não vou ter dinheiro suficiente para manter o navio...";
                link.l1 = "Pena.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Certo, vamos jogar por 100 moedas.";
			link.l1 = "Vamos começar!";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 100;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_Node_500":
		    if (sti(pchar.Money) < 1500)
		    {
                dialog.text = "Você está brincando ou o quê? Você não tem 1.500 pesos!";
                link.l1 = "Eu vou encontrá-los!";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 1500)
		    {
                dialog.text = "Não, essas apostas certamente vão acabar comigo.";
                link.l1 = "Como quiser.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Certo, vamos jogar por 500 moedas.";
			link.l1 = "Vamos começar!";
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
                dialog.text = "Eu não vou apostar com bandidos!";
    			link.l1 = "Como quiser.";
    			link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
				{
					dialog.text = "Por que não! Relaxar sempre faz bem à saúde... mas nem sempre ao bolso...";
	    			link.l1 = "Excelente.";
	    			link.l1.go = "Dice_begin";
	    			link.l2 = "Quais são as regras do nosso jogo?";
	    			link.l2.go = "Dice_Rule";
    			}
    			else
    			{
					dialog.text = "Não, por hoje chega. Tenho coisas para fazer.";
	    			link.l1 = "Como quiser.";
	    			link.l1.go = "exit";
				}
			}
		break;

		case "Dice_Rule":
   			dialog.text = DICE_RULE;
			link.l1 = "Então, vamos começar!";
			link.l1.go = "Dice_begin";
			link.l3 = "Não, não é pra mim...";
			link.l3.go = "exit";
		break;

		case "Dice_begin":
			Dialog.text = "Vamos acertar a aposta primeiro.";
			link.l1 = "Vamos jogar por 50 pesos.";
			link.l1.go = "Dice_Node_100";
			link.l2 = "Vamos jogar por 200 pesos.";
			link.l2.go = "Dice_Node_500";
			link.l3 = "Acho que é melhor eu ir.";
			link.l3.go = "exit";
		break;

		case "Dice_Node_100":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckDiceGameSmallRate() && !bOk)
		    {
                dialog.text = "Você é bem conhecido como um"+GetSexPhrase("trapaceiro","trapaceiro")+".. Eu nunca vou jogar dados com você.";
                link.l1 = "É tudo mentira! Pois bem, que seja.";
			    link.l1.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 300)
		    {
                dialog.text = "Você está brincando ou o quê? Você não tem dinheiro!";
                link.l1 = "Acontece.";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 300)
		    {
                dialog.text = "Chega! Cansei de apostar – antes que me chamem de trapaceiro e me obriguem a sair do navio.";
                link.l1 = "Pena.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Certo, vamos jogar por 50 moedas.";
			link.l1 = "Vamos começar!";
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
                dialog.text = "Você é bem conhecido como um"+GetSexPhrase("trapaceiro","trapaceiro")+". Eu nunca vou jogar dados com você.";
                link.l1 = "É tudo mentira! Pois bem, que seja.";
			    link.l1.go = "exit";
			    break;
		    }
			if (!CheckDiceGameBigRate())
		    {
                dialog.text = "Ouvi dizer que você é bem habilidoso no jogo. Não vou apostar alto com você.";
                link.l1 = "Que tal abaixarmos a aposta, talvez?";
			    link.l1.go = "Dice_Node_100";
				link.l2 = "Me desculpe, mas eu preciso ir.";
			    link.l2.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 1500)
		    {
                dialog.text = "Você está brincando ou o quê? Você não tem 1.500 pesos!";
                link.l1 = "Eu vou encontrá-los!";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 1500)
		    {
                dialog.text = "Não, essas apostas vão acabar comigo, com certeza.";
                link.l1 = "Como quiser.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Certo, vamos jogar por 200 moedas.";
			link.l1 = "Vamos começar!";
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
	                Dialog.Text = "Por que você quer saber? Isso é assunto meu.";
					Link.l1 = "Como quiser.";
					Link.l1.go = "exit";
	            }
	            else
	            {
                    sld = &Characters[iMoney];
                    pchar.PriceList.ShipStoreIdx = iMoney;
                    
					Dialog.Text = "Eu venho da cidade de"+GetCityName(sld.City)+".";
					Link.l1 = "Quais são os preços das mercadorias na loja local?";
					Link.l1.go = "price_2";
					Link.l9 = "Eu devo ir.";
					Link.l9.go = "exit";
				}
			}
			else
			{
                Dialog.Text = "Já te contei tudo. Não me incomode à toa.";
				Link.l1 = "É, você tem razão. Adeus.";
				Link.l1.go = "exit";
            }
		break;
		
		case "price_2":
            sld = &Characters[sti(pchar.PriceList.ShipStoreIdx)];
			SetPriceListByStoreMan(&Colonies[FindColony(sld.City)]);
			Dialog.Text = "Aqui está... (você recebeu a lista de preços)..";
			Link.l1 = "Muito obrigado!";
			Link.l1.go = "exit";
			PlaySound("interface\important_item.wav");
		break;
		
        case "Talk_board":
            bOk = iCapBattleDifficulty > hrand(98);
            //if ((Group_GetCharactersNum(NPChar.EncGroupName) - Group_GetDeadCharactersNum(NPChar.EncGroupName)) > GetCompanionQuantity(PChar) && rand(11) > GetCharacterSkillToOld(PChar, SKILL_FORTUNE))
            if(!bOk && iCapBattleDifficulty <= 33)
            {
                Dialog.text = "Ha-ha! Boa piada. Principalmente porque está claro que eu tenho a vantagem aqui. Volte para o seu navio e afunde com ele.";
                link.l1 = "...";
                link.l1.go = "Boarding";
            }
            else
            {
                if(!bOk)
                {
                    Dialog.text = "Capitão, você não devia ter feito suas sujeiras a bordo do meu navio. Mas vou mostrar misericórdia e deixar você voltar para o seu navio para afundar junto com ele.";
                    link.l1 = "Vamos ver quem vai virar comida de tubarão hoje!";
                    link.l1.go = "Boarding";
                }
                else
                {
                    if(iEncPow == -1) iEncPow = 0;
                    Pchar.GenQuest.MoneyForCaptureShip = (70 + hrand(60, "&CapSur"+NPChar.id)) * iEncPow;
					if(HasShipTrait(pchar, "trait14")) Pchar.GenQuest.MoneyForCaptureShip = makeint(sti(Pchar.GenQuest.MoneyForCaptureShip) * 1.35);
                    Dialog.text = RandSwear()+"Sim, já ouvi muito sobre suas atrocidades. Que seja, mas lembre-se "+XI_ConvertString(NationShortName(sti(NPChar.nation))+"hunter")+" não vou deixar isso impune!";
                    link.l1 = "Excelente. Uma quantia de "+Pchar.GenQuest.MoneyForCaptureShip+" pesos vão me servir muito bem, "+GetAddress_FormToNPC(NPChar)+".";
                    link.l1.go = "Capture";
                    link.l2 = "Ah, deixa pra lá. Eu só estava brincando"+GetSexPhrase("","")+"!";
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
            Dialog.Text = "Aqui está - agora suma daqui!";
			Link.l1 = "Que bom! E você também se cuide, amigo!";
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
			Dialog.Text = "O que mais você quer de mim?";
			Link.l1 = "Nada.";
			Link.l1.go = "exit";
			Diag.TempNode = "surrender_goaway";
		break;
		
		case "surrender2":			
			dialog.text = "Parece que não tenho outra escolha a não ser me submeter a você.";
			link.l1 = "Segue em frente, vai!";
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
			Link.l1 = RandPhraseSimple(RandSwear()+"Isto é muito interessante. Outra pergunta?","Só mais um caso.");
			Link.l1.go = "quests";
			Link.l2 = RandPhraseSimple("Obrigado, eu já devo ir.","Tudo de bom.");
			Link.l2.go = "exit";
			Diag.TempNode = "quests";
		break;
		
		case "Go_away":
			Dialog.Text = "Saia do meu navio!";
			Link.l1 = "Já estou de saída.";
			Link.l1.go = "exit";
			Diag.TempNode = "Go_away";
		break;
		
		case "Go_away_Good":
			Dialog.Text = " Nossa conversa acabou. Não vou te contar nada novo "+GetAddress_Form(NPChar)+".";
			Link.l1 = "Está bem. Nos vemos no mar!";
			Link.l1.go = "exit";
			Diag.TempNode = "Go_away_Good";
		break;

        case "Capture":
            Diag.TempNode = "Go_away";
            Dialog.Text = "Aqui está - agora suma daqui!";
			Link.l1 = "Legal!";
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
            Dialog.Text = "Espere, desse jeito você pode me matar. O que você quer de mim?";
			Link.l1 = "Para te matar!";
			Link.l1.go = "QuestAboardCabinDialog_1";
			Link.l2 = "Renda-se!";
			Link.l2.go = "QuestAboardCabinDialog_2";
			Link.l3 = "Nos dê o mapa, Billy (c)";  // предмет, далее не ясно или  QuestAboardCabinDialog_1 или QuestAboardCabinDialog_2
			Link.l3.go = "QuestAboardCabinDialog_3";  // можно закодить покидание корабля, но экипаж уже вырезан и тп...
        break;
        
        case "QuestAboardCabinDialog_1":
			Dialog.Text = "Vamos ver então, seu bastardo!";
			Link.l1 = "E o que eu deveria ver?";
			Link.l1.go = "exit";
			// тут можно восстановить НР противника (NPChar) или добавить парочку гардов против ГГ
			LAi_SetCurHPMax(NPChar);
			AddDialogExitQuestFunction("QuestAboardCabinDialogExitWithBattle"); // тут ругань обратно
		break;
		
		case "QuestAboardCabinDialog_2":
			Dialog.Text = "Tá bom, você venceu!";
			Link.l1 = "Decisão inteligente!";
			Link.l1.go = "exit";
			AddDialogExitQuestFunction("QuestAboardCabinDialogSurrender");
		break;
		
		case "QuestAboardCabinDialog_3":
			Dialog.Text = "Espero que se engasgue com isso!";
			Link.l1 = "Muito bem, coloque as algemas e fique de boca fechada, prisioneiro.";
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
			Dialog.Text = ""+GetSexPhrase("Vim aqui","Vim aqui")+", fez uma bagunça"+GetSexPhrase("","")+", e levou tudo"+GetSexPhrase("","")+", agora você quer me tornar um escravo? Nunca!";
			Link.l1 = "Então prepare-se para morrer.";
			Link.l1.go = "QuestAboardCabinDialog_1";
		break;
		//eddy. квест мэра, поиски пирата
		case "MQ_step_1":
			Dialog.Text = "Não, não vi nenhum navio suspeito que parecesse de piratas.";
			Link.l1 = "Entendi.";
			Link.l1.go = "exit";
		break;
		
		//homo Наводка на купца
		case "MerchantTrap_Abordage":

			Dialog.Text = "Em nome de "+NationKingsName(NPChar)+" se renda, "+GetSexPhrase("pirata imundo","vadia imunda!")+"! Então sua vida será poupada até um tribunal justo, onde você será julgado por tudo "+NationNameSK(sti(NPChar.nation))+"navios que você saqueou"+GetSexPhrase("","")+".";
			Link.l1 = "Vai se ferrar! Você devia se render!";
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
					dialog.text = "Excelência, Governador-Geral! Estou ouvindo com atenção, mas peço que seja breve: estamos em guerra com "+fort+", e eu preciso direcionar o rumo da batalha.";
				}
				else
				{
					if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && sti(Items[sti(pchar.EquipedPatentId)].Nation) == npchar.nation)
					{
						dialog.text = "Vice-Almirante! Estou ouvindo com atenção, mas tenho pouco tempo: estamos em combate com "+fort+", e eu preciso direcionar o rumo da batalha.";
					}
					else
					{
						dialog.text = "Estou te ouvindo, mas vamos logo ao motivo da sua visita, estamos em guerra com "+fort+", e eu preciso assumir o comando da batalha.";
					}
				}
                link.l1 = "É por isso que estou aqui,  "+GetAddress_FormToNPC(NPChar)+".";
                link.l1.go = "attack_fort";

                link.l2 = "Nesse caso, não vou tomar mais do seu tempo. Até logo, "+GetAddress_FormToNPC(NPChar)+".";
                link.l2.go = "exit";
    			
            }
            else
            {
                Dialog.text = "Não tenho autorização para tratar com você. Fale com o comandante do nosso esquadrão. O nome dele é  "+GetFullName(rchar)+", você pode encontrá-lo em "+XI_ConvertString(RealShips[sti(rchar.Ship.Type)].BaseName)+" ''"+rchar.Ship.Name+"''.";
                link.l1 = "Obrigado. Vou fazer como você disse.";
                link.l1.go = "exit";
            
            }
            Diag.TempNode = "Siegehelp";
            
		break;
		
		case "attack_fort":
                dialog.text = "E o que você quer dizer?";
                link.l1 = "Posso ajudar você a destruir o forte da colônia de "+GetCityName(aData.Colony)+" e conquistar a cidade, e os despojos, que, se tivermos sucesso, vamos dividir entre nós.";
                link.l1.go = "Siegehelp_1";
                link.l2 = "Na verdade, meu assunto mal vale o seu tempo. Adeus, "+GetAddress_FormToNPC(NPChar)+".";
                link.l2.go = "exit";
                Diag.TempNode = "Siegehelp_0";
		break;
		
		case "Siegehelp_0":
            Dialog.text = "Você de novo? Achei que já tínhamos conversado sobre tudo.";
            link.l1 = "Você tem razão. Acho que acabei esquecendo"+GetSexPhrase("","")+".";
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
                dialog.text = "E quanto da pilhagem você espera receber?";
                link.l1 = "Metade.";
                link.l1.go = "Big_part";
                link.l2 = "Um terço.";
                link.l2.go = "Middle_part";
                link.l3 = "Um quarto.";
                link.l3.go = "Small_part";
            }
            else
            {
                dialog.text = "Não preciso dos seus serviços, capitão! Vou tomar essa colônia sozinho e não preciso de ajuda para isso.";
                link.l1 = "Por que você tem tanta certeza, "+GetAddress_FormToNPC(NPChar)+", qualquer um pode ter um golpe de má sorte.";
                link.l1.go = "attack_fort_03";
                link.l2 = "Nesse caso, não vou tomar mais do seu tempo, "+GetAddress_FormToNPC(NPChar)+". Adeus!";
                link.l2.go = "exit";
            }
			Diag.TempNode = "Siegehelp_0";

		break;
		
		case "attack_fort_03":
            if((sti(aData.iSquadronPower)*SquadronDamage - (ifortPower)*fortDamage) < 4000)
            {
                dialog.text = "Por outro lado, meus navios ficaram bem danificados nessa batalha, e reforços certamente não fariam mal. Se você concordar em "+GetPart(4)+", então, suponho, poderíamos chegar a um acordo.";
                link.l1 = "Isso me serve, "+GetAddress_FormToNPC(NPChar)+". Vou tentar atacar o forte, e vocês vão nos apoiar com o fogo dos canhões do seu navio.";
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 4;
                link.l2 = "Eu não sou tão barato assim, "+GetAddress_FormToNPC(NPChar)+". Me desculpe pela distração"+GetSexPhrase("","")+" não quero te afastar dos seus compromissos. Adeus!";
                link.l2.go = "exit";
            }else{
                dialog.text = "Tenho navios suficientes no meu esquadrão para reduzir este forte a pó – é só uma questão de tempo. E agora, poderia sair do meu navio, por favor? A vitória me espera!";
                link.l1 = "Bem, nesse caso, "+GetAddress_FormToNPC(NPChar)+", permita-me me retirar. Adeus!";
                link.l1.go = "exit";
            }
		    Diag.TempNode = "Siegehelp_0";
		break;
		case "Big_part":
            if( (sti(aData.iSquadronPower)*SquadronDamage - (ifortPower)*fortDamage) <= -1500)
            {
                dialog.text = "Os canhões do forte danificaram gravemente meus navios, e talvez estejamos em desvantagem na próxima batalha. Aceito sua ajuda e concordo com seus termos.";
                link.l1 = "Excelente, "+GetAddress_FormToNPC(NPChar)+", nesse caso vamos tentar assaltar o forte, e você vai nos apoiar com o fogo dos canhões do seu navio.";
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
					dialog.text = "Excelência, ainda preciso relatar o andamento da operação... Pelo menos me deixe "+GetPart(4)+".";
				}
				else
				{
                dialog.text = "Não é demais, capitão? Você tem "+GetNumShips(GetCompanionQuantity(PChar))+", e meu esquadrão já "+GetNumShips(Group_GetCharactersNum(sGroup))+". Posso te oferecer "+GetPart(4)+". E considere isso justo.";
				}
                aData.PartAttaksFort = 4;
                link.l1 = "Concordo"+GetSexPhrase("","")+", "+GetAddress_FormToNPC(NPChar)+", nesse caso eu vou atacar o forte, e você vai nos apoiar com o fogo dos canhões do seu navio.";
                link.l1.go = "attack_fort_04";
                link.l2 = "Infelizmente, acho que não, "+GetAddress_FormToNPC(NPChar)+". Não há mais nada a discutir. Adeus.";
                link.l2.go = "exit";
            }
            Diag.TempNode = "Siegehelp_0";
        break;
        
        case "attack_fort_04":
            dialog.text = "Assim que o forte for tomado, começaremos a desembarcar grupos na praia, e então continuaremos lutando dentro da cidade, onde espero encontrar você.";
            link.l1 = "Então está bem. Até logo, "+GetAddress_FormToNPC(NPChar)+"!";
            link.l1.go = "exit";
            Diag.TempNode = "Siegehelp_0";
            PChar.quest.Union_with_Escadra = "Yes";
        break;

        case "Middle_part":
            if((sti(aData.iSquadronPower)*SquadronDamage - (ifortPower)*fortDamage) <= -600)
            {
                dialog.text = "Acho que vou aceitar seus termos. Uma operação conjunta vai aumentar minhas chances de vencer essa luta. Se tudo correr como planejado, você receberá sua parte do saque.";
                link.l1 = "Que bom que chegamos a um acordo, "+GetAddress_FormToNPC(NPChar)+". Vou ordenar que meus homens ataquem o forte imediatamente.";
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 3;
            }else{
				// belamour legendary edition
				bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation);
				bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE;
				bOk = bOk1 || bOk2;
				if(bOk)
				{
					dialog.text = "Excelência, ainda preciso relatar o andamento da operação... Pelo menos deixe-me "+GetPart(4)+".";
				}
				else
				{
                dialog.text = "Não é demais, capitão? Você tem "+GetNumShips(GetCompanionQuantity(PChar))+", e meu esquadrão já "+GetNumShips(Group_GetCharactersNum(sGroup))+". Posso te oferecer "+GetPart(4)+". E considere isso justo.";
				}
                link.l1 = "Eu "+GetSexPhrase("concordar","concordar")+", "+GetAddress_FormToNPC(NPChar)+", nesse caso eu vou atacar o forte, e vocês vão nos apoiar com o fogo dos canhões do seu navio.";
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 4;
                link.l2 = "Infelizmente, acho que não. "+GetAddress_FormToNPC(NPChar)+". Não há mais nada para discutir. Adeus.";
                link.l2.go = "exit";
            }
            Diag.TempNode = "Siegehelp_0";
        break;

        case "Small_part":
            dialog.text = "Meus navios estão exaustos, e qualquer reforço é bem-vindo nesta situação. Aceito sua ajuda e concordo com seus termos.";
            link.l1 = "Estou feliz"+GetSexPhrase("","")+", "+GetAddress_FormToNPC(NPChar)+".. Vou imediatamente ordenar aos meus homens que comecem o ataque ao forte.";
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
            dialog.text = "Olá, capitão! Foi realmente uma batalha difícil, mas conseguimos quebrar a feroz resistência dos defensores da cidade. Saqueamos "+sti(aData.loot)+" pesos. Conforme nosso acordo, sua parte é "+ilt+". Please accept this money; you certainly deserve every last coin of it. And now please excuse me, but I must return to my business.";
            link.l1 = "Nesse caso, vou te deixar, "+GetAddress_FormToNPC(NPChar)+". Adeus!";
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
            dialog.text = "Olá, capitão! Tem algum assunto comigo?";
            link.l1 = "Não, "+GetAddress_FormToNPC(NPChar)+". Adeus!";
            link.l1.go = "exit";
            Diag.TempNode = "no_return_02";
		break;
		
		case "GoldSquadron":
            ref rch = Group_GetGroupCommander("Sea_Head_of_Gold_Squadron");
            if (NPChar.id == rch.id)
            {
    			dialog.text = "Estou ouvindo você, mas seja breve sobre o motivo da sua visita, não tenho muito tempo. Estou em uma missão importante e secreta, e tenho ordens para afundar qualquer navio suspeito em mar aberto que possa ameaçar nosso comboio.";                          
                link.l1 = "Neste caso, não vou tomar mais do seu tempo. Boa sorte, "+GetAddress_FormToNPC(NPChar)+".";
                link.l1.go = "exit";

            }
            else
            {
                Dialog.text = "Não estou autorizado a negociar com você. Fale com o comandante do nosso esquadrão. O nome dele é "+GetFullName(rch)+", você pode encontrá-lo em "+XI_ConvertString(RealShips[sti(rch.Ship.Type)].BaseName)+" ''"+rch.Ship.Name+"''.";
                link.l1 = "Obrigado. Vou fazer como você disse.";
                link.l1.go = "exit";

            }
            Diag.TempNode = "GoldSquadron";
		break;
		
		case "WM_Captain":
			dialog.text = "Prazer em te conhecer, meu nome é "+GetFullName(npchar)+". Então você veio nos ajudar? Nesse caso, fico especialmente aliviado, pois nossa situação é realmente crítica – estamos sozinhos nas margens de uma ilha desabitada, o navio mal consegue navegar, e a tripulação sofreu grandes perdas...";
			link.l1 = "Pelo que ouvi, você enfrentou piratas, e depois veio aquela tempestade...";
			link.l1.go = "WM_Captain_1";
			pchar.quest.DesIsland_Over.over = "yes";//снять прерывание
		break;
		
		case "WM_Captain_1":
			dialog.text = "Certo. Meu navio ficou muito danificado na batalha – até tivemos que resistir a um ataque de abordagem liderado por aqueles malditos piratas. Depois, fomos pegos por uma tempestade... ah, nem gosto de lembrar. Fomos arrastados até esta costa inóspita. Passamos o dia inteiro rezando à Virgem Santíssima para nos salvar da tempestade e manter as correntes das âncoras intactas\nE aqui estamos. Já faz uma semana que estamos consertando o navio, mas veja você mesmo: só restaram cinquenta homens e ainda estamos sem tábuas de madeira – e de onde vamos tirar isso? Da selva? É claro. Trabalhamos duro todos os dias e mesmo assim só conseguimos um quinto do material necessário\nNavegar com tantos danos seria o mesmo que suicídio. Agora você vê como estamos por aqui, capitão...";
			link.l1 = "É... Sua situação não é nada fácil. Vamos pensar no que podemos fazer e como posso te ajudar.";
			link.l1.go = "WM_Captain_2";
		break;
		
		case "WM_Captain_2":
			dialog.text = "Ah, queria que tivéssemos tábuas e lonas suficientes – assim poderíamos consertar nosso navio em uma semana\nCapitão, já que veio até aqui de propósito, talvez possa visitar o porto mais próximo e comprar os materiais de que precisamos? Isso resolveria nosso problema. Não se preocupe com o dinheiro, eu reembolso todas as despesas.";
			link.l1 = "Claro. O que exatamente você precisa entregar, e quanto?";
			link.l1.go = "WM_Captain_3";
		break;
		
		case "WM_Captain_3":
			pchar.questTemp.WPU.Escort.Planks = 300 + hrand(5)*10;
			pchar.questTemp.WPU.Escort.Sailcloth = 150 + hrand(10)*10;
			pchar.questTemp.WPU.Escort.Linen = 70 + hrand(7)*10;
			dialog.text = "Eu já entendi tudo isso. Considerando o que já temos, eu preciso "+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Planks))+" tábuas, "+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Sailcloth))+" tecido de vela e "+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Linen))+" algodão. Com esses materiais, conseguiríamos consertar o navio em uma semana, e então poderíamos zarpar.";
			link.l1 = "Certo. Vou trazer todos os materiais que você precisa. Espere por mim - volto em no máximo dez dias.";
			link.l1.go = "WM_Captain_4";
		break;
		
		case "WM_Captain_4":
			dialog.text = "Muito obrigado, capitão! Isso tira um peso da minha cabeça. Vamos esperar e rezar pelo seu retorno em segurança!";
			link.l1 = "Não se preocupe. Em breve você terá tudo o que precisa para os reparos.";
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
			dialog.text = "Estaremos ansiosos esperando o seu retorno, capitão!";
			link.l1 = "Levem âncora!";
			link.l1.go = "exit";
			Diag.TempNode = "WM_Captain_again";
		break;
		
		case "WM_Captain_5":
			dialog.text = "Excelente! Agora podemos começar a consertar o navio!";
			link.l1 = "Meus homens vão te ajudar – assim será mais rápido. Além disso, preciso te acompanhar até a colônia de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity)+", então quanto antes terminarmos os reparos, melhor para mim.";
			link.l1.go = "WM_Captain_6";
		break;
		
		case "WM_Captain_6":
			pchar.questTemp.WPU.Current.TargetIslandID.Shore = SelectQuestShoreLocationFromSea(pchar.questTemp.WPU.Current.TargetIslandID);
			dialog.text = "De verdade, não faço ideia de como agradecer você direito, capitão... Por favor, mande descarregar os materiais numa enseada chamada "+XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID.Shore)+" - lá temos tudo pronto para os reparos.";
			link.l1 = "Certo. Vamos nos encontrar na praia.";
			link.l1.go = "exit";
			AddQuestRecord("Escort", "29");
			AddQuestUserData("Escort", "sShore", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID.Shore+"Gen"));
			pchar.quest.DisasterShip_WMC.win_condition.l1 = "location";
			pchar.quest.DisasterShip_WMC.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID.Shore;
			pchar.quest.DisasterShip_WMC.function = "RepairShip_Prepare";
			Diag.TempNode = "WM_Captain_repeat";
		break;
		
		case "WM_Captain_repeat":
			dialog.text = "Quando vamos começar os reparos, capitão? Vou te esperar na praia.";
			link.l1 = "Sim, claro. Estou indo agora.";
			link.l1.go = "exit";
			Diag.TempNode = "WM_Captain_repeat";
		break;
		
		case "Repair_start":
			dialog.text = "Bem, tudo parece pronto para os reparos. Acho que terminamos em cerca de cinco dias.";
			link.l1 = "Muito bom! Eu ia explorar esta ilha de qualquer jeito, então vou aproveitar bem o tempo.";
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
			dialog.text = "Pronto, terminamos os reparos e o navio está pronto para zarpar. Quando partimos, capitão?";
			link.l1 = "Se você está pronto, não vejo motivo para ficar parado. Levante âncora!";
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
			dialog.text = "Quero agradecer mais uma vez, capitão – você ajudou muito a mim e à minha tripulação a sair daquela enrascada. Como prometi, vou compensá-lo pelos materiais necessários para consertar meu navio. Aqui estão "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money))+", por favor, leve-os. E este é o meu presente pessoal para você.";
			link.l1 = "Fiquei feliz em poder ajudar você.";
			link.l1.go = "WMShip_final_1";
		break;
		
		case "WMShip_final_1":
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.LevelUp_1Money));
			TakeNItems(pchar, "obereg_"+(hrand(10)+1), 1);
			dialog.text = "E agora, é hora de se despedir, capitão. Não se esqueça de passar na autoridade portuária – estão esperando por você lá. Até mais!";
			link.l1 = "Tenha um bom dia, "+npchar.name+"!";
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
			dialog.text = "É mesmo? E eu já estava achando que tinham nos esquecido. Sim, meu navio foi o que mais sofreu. Ficamos à mercê do tempo depois que a tempestade obrigou os piratas a desistirem do ataque à nossa caravana. Fomos levados até esta costa inóspita\nPassamos alguns dias consertando o navio e descansando. Esses pagãos nos atacaram de novo, bem quando estávamos prestes a zarpar\nE então a tempestade voltou — achamos que o Senhor finalmente tinha decidido acabar conosco, mas aí você apareceu. Santa Maria, obrigada! Mais uma vez, obrigado, capitão!";
			link.l1 = "Acabou tudo, "+GetAddress_FormToNPC(NPChar)+". Agora preciso escoltar você até "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+", para protegê-lo de mais problemas. Você está pronto para ir agora? A tempestade já começou a diminuir.";
			link.l1.go = "VSP_Captain_1";
		break;
		
		case "VSP_Captain_1":
			dialog.text = "Mas é claro! Quanto antes deixarmos este lugar, mais tranquilos ficarão meus homens – eles já sofreram demais. Vamos zarpar!";
			link.l1 = "Siga meu navio – e acalme sua tripulação, não há mais nada a temer agora.";
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
			dialog.text = "Vamos zarpar, capitão?";
			link.l1 = "Claro. Vou voltar para o meu navio agora.";
			link.l1.go = "exit";
			Diag.TempNode = "VSP_Captain_again";
		break;
		
		case "VSPShip_final":
			pchar.quest.Escort_fail.over = "yes";
			pchar.quest.DisasterShipWM_Over.over = "yes";//снимаем оба прерывания
			RemoveCharacterCompanion(Pchar, characterFromID("WMCaptain"));//удаляем компаньона
			pchar.questTemp.WPU.Escort.LevelUp_1Money = 10000+sti(pchar.rank)*200;
			dialog.text = "Quero te agradecer mais uma vez, capitão – você ajudou muito a mim e à minha tripulação a sair dessa enrascada. Aqui estão"+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money))+". Toda a tripulação contribuiu, então nem pense em recusar. E este é meu presente pessoal para você.";
			link.l1 = "Fiquei feliz em ajudar você!";
			link.l1.go = "WMShip_final_1";
		break;
		
		case "SShip_final":
			pchar.questTemp.WPU.Escort.LevelUp_1Money = 5000+sti(pchar.rank)*100;
			RemovePassenger(Pchar, npchar);//удаляем пассажира
			dialog.text = "Quero te agradecer de novo, capitão, por ter nos tirado dessa enrascada. Aqui, aceite essas moedas - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money))+"  e aqui, aceite este presente. Não é muito, mas é tudo o que posso fazer para agradecer pelo que você fez. Por favor, não recuse minha oferta\nMinha antiga tripulação está impressionada com você e suas batalhas contra índios e piratas. Todos eles querem se juntar a você. Espero que não recuse a oferta de serviço leal de marinheiros que acabam de perder seu navio?";
			link.l1 = "Claro que não. Vou guardar com prazer. Fiquei feliz em ajudar você!";
			link.l1.go = "WMShip_final_1";
		break;
		
		//Голландский Гамбит
		case "Stivesant_1":
			DelLandQuestMark(npchar);
			dialog.text = "Certo. Mas, senhor, poderia me explicar o que está acontecendo aqui? Como é que você está no comando do 'Meifeng'? Aconteceu alguma coisa com Longway?";
			link.l1 = "Tenho todas as explicações que você precisa – e também algumas outras informações importantes.";
			link.l1.go = "Stivesant_2";			
		break;
		
		case "Stivesant_2":
			dialog.text = "Então estou todo ouvidos.";
			link.l1 = "Houve um golpe em Willemstad. Lucas Rodenburg tomou o lugar do governador e mandou prender Matthias Beck por uma suspeita absurda de que ele teria ligações com a inteligência britânica.";
			link.l1.go = "Stivesant_3";			
		break;
		
		case "Stivesant_3":
			dialog.text = "Hum... Senhor, o que você está me contando é realmente surpreendente. Recebi notícias de Willemstad não faz muito tempo, e não havia nada disso nelas.";
			link.l1 = "Por favor, escute-me, senhor Stuyvesant. O senhor deve ter recebido as notícias por meio de Rodenburg, e ele deve estar certo de que você não chegará a Curaçao.";
			link.l1.go = "Stivesant_4";			
		break;
		
		case "Stivesant_4":
			dialog.text = "Mister, estou gostando cada vez menos do que você está dizendo. Quem é você, afinal?";
			link.l1 = "Sou apenas um capitão, um homem que não é indiferente ao destino dos colonos holandeses. Lucas Rodenburg ordenou que Longway destruísse seu navio e matasse você também. E como 'Meifeng' não levantaria suas suspeitas, ele teria feito isso sem dificuldade.";
			link.l1.go = "Stivesant_5";			
		break;
		
		case "Stivesant_5":
			dialog.text = "Então, você quer dizer que o Lucas...";
			link.l1 = "Decidiram tirar você do poder da forma mais simples possível – simplesmente eliminando você. Fora você, não há mais ninguém na região capaz de oferecer qualquer resistência significativa à influência de Rodenburg no Arquipélago.";
			link.l1.go = "Stivesant_6";			
		break;
		
		case "Stivesant_6":
			dialog.text = "Não acredito nisso!";
			link.l1 = "Eu não caí nessa conversa de que o Beck tinha ligação com a inteligência inglesa e fiz minha própria investigação. Descobri que o 'Meifeng', cheio de bandidos escolhidos a dedo, partiu para Philipsburg. Fui atrás deles e os enfrentei. Longway foi capturado e me contou tudo isso, inclusive onde você estava.";
			link.l1.go = "Stivesant_7";			
		break;
		
		case "Stivesant_7":
			dialog.text = "Hm... Isso parece provável. Ninguém, além do Rodenburg, sabia ou poderia saber sobre minha agenda e rota! Maldição! Isso é traição! Onde está o Longway?!";
			link.l1 = "Eu o libertei em troca de sua confissão voluntária. Tenho que dizer, ele não estava muito disposto a cumprir a ordem de Rodenburg, mas também não podia ignorá-la. Ele também disse que não voltaria a servir a Rodenburg – essa última sujeira foi a gota d'água.";
			link.l1.go = "Stivesant_8";			
		break;
		
		case "Stivesant_8":
			dialog.text = "Tudo bem... Capitão "+GetFullName(pchar)+", você vai vir comigo para Willemstad. Vai navegar no 'Meifeng' à frente do meu navio. Se o que disse for verdade, Lucas deve ser preso, e você vai ajudar nisso. Mas se mentiu para mim... Só poderá culpar a si mesmo.";
			link.l1 = "Para mim, não faz sentido mentir para você, senhor. Vamos nos apressar!";
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
			dialog.text = "Capitão, vá até 'Meifeng'. Está na hora de zarparmos.";
			link.l1 = "Sim, senhor, claro.";
			link.l1.go = "exit";
			Diag.TempNode = "Stivesant_10";
		break;
		
		case "Keller_1":
			dialog.text = "Muito interessante! Por favor, me conte sua história. Vou fazer o possível para ajudar.";
			link.l1 = "Mynheer Keller, você se lembra de quando encontrou uma flauta a caminho de Willemstad alguns meses atrás? Havia uma família de refugiados judeus a bordo. Você jantou naquele navio e depois seguiu viagem.";
			link.l1.go = "Keller_2";
		break;
		
		case "Keller_2":
			dialog.text = "Sim, acho que sim... Sim, agora me lembro perfeitamente. Então, qual é o lance?";
			link.l1 = "A chalupa foi afundada por piratas naquele mesmo dia. Só dois sobreviventes conseguiram escapar – Solomon e Abigail, sua filha. Eles encontraram abrigo numa ilha a poucos quilômetros de onde o ataque aconteceu. Preciso encontrar essa ilha. Você consegue se lembrar onde viu essa chalupa? Isso é muito importante.";
			link.l1.go = "Keller_3";
		break;
		
		case "Keller_3":
			dialog.text = "E é só isso que você precisa? Eu conheço essa ilha. Ela fica bem perto, entre Trinidad e Curaçao. Uma ilha pequena, deserta, sem habitantes. Nem índios tem lá.";
			link.l1 = "E você sabe as coordenadas aproximadas?";
			link.l1.go = "Keller_4";
		break;
		
		case "Keller_4":
			dialog.text = "Posso te dizer as coordenadas exatas. Fica em 12  48'  Norte e 64  41'  Oeste. Procure por lá. A ilha é bem pequena, mas você deve conseguir encontrá-la facilmente.";
			link.l1 = "Muito obrigado, senhor Keller! Você me ajudou muito. Adeus.";
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
			dialog.text = "Queria mais alguma coisa, capitão?";
			link.l1 = "Não, obrigado. Eu só estava voltando para o meu navio.";
			link.l1.go = "exit";
			Diag.TempNode = "Keller_6";
		break;
		
		// belamour рыбацкое судно -->
		case "FishingBoat":
			pchar.GenQuest.FishingBoatSecondTime = true;
			dialog.text = "Nada de especial, isto aqui é um barco de pesca, pegamos peixe por aqui. Alguém precisa ganhar a vida de algum jeito.";
			link.l1 = "Sim, eu concordo, esses são os tempos...";
			link.l1.go = "FishingBoat_1";			
		break;
		
		case "FishingBoat_1":
			Diag.TempNode = "FishingBoat_1";
			dialog.text = "O que você quer?";
			link.l1 = "Eu queria"+GetSexPhrase("","")+" para descobrir as últimas novidades do arquipélago.";
            link.l1.go = "rumours_capitan";
			link.l2 = "Como estão suas pescarias hoje? Pode vender? Algumas provisões não me fariam mal...";
			link.l2.go = "FishingBoat_2";
			link.l3 = "Nada de especial, só vim dar um oi!";
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
				
				dialog.text = "A pesca está boa hoje, só precisamos de tempo para puxar as redes. Podemos vender pra você, até mais barato que na loja – afinal, já vendemos peixe para um comerciante local mesmo. Se transformarmos tudo isso em mantimentos... Agora temos "+iTemp+" disso, podemos vender por um preço de "+iMoney+" pesos cada um. Quanto você aceita?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта";
				link.l2 = "Sabe, mudei de ideia sobre comprar seus mantimentos.";	
				link.l2.go = "exit";
				
			}
			if(GetDataDay() > 10 && GetDataDay() < 21) 
			{
				Diag.TempNode = "FishingBoat_1";
				dialog.text = "Sim, algo assim, para ser sincero, não tem peixe nenhum ... Hoje quase não pegamos nada. Mas sobraram arpões – achamos que talvez desse pra pegar um peixe grande ou até uma baleia, se tivéssemos sorte ... Talvez você precise de arpões?";
				link.l1 = "Não, não estou interessado em arpões.";
				link.l1.go = "exit";
				link.l2 = "Hum, um arpão também é uma coisa útil nas mãos certas. Provavelmente vou comprar.";
				link.l2.go = "Гарпуны";
			}
			if(GetDataDay() > 20)
			{
				dialog.text = "Sim, algo, para ser sincero, não tem peixe nenhum... Quase nada foi pescado hoje. Então não tem muito o que vender. A não ser que... Eu tenho umas bugigangas, talvez alguma coisa te interesse. Quer dar uma olhada?";
				link.l1 = "Não, não me interesso por bugigangas.";
				link.l1.go = "exit";
				link.l2 = "É uma pena que não tenha nada de interessante. Bem, pelo menos vamos dar uma olhada nos seus badulaques – quem sabe algo chame minha atenção ...";
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
				dialog.text = "Isso é demais... Eu não tenho tudo isso! Dá pra comprar menos?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта повтор";	
				link.l2 = "Sabe, mudei de ideia sobre comprar seus mantimentos.";	
				link.l2.go = "exit";
			}	
			if(iQty < 1)
			{
				dialog.text = "Você está brincando comigo? Você precisa de mantimentos ou não? Se sim, quanto?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта повтор";	
				link.l2 = "Sabe, mudei de ideia sobre comprar seus mantimentos.";	
				link.l2.go = "exit";
			}
			if(iQty > 0 && iQty <= iTemp)
			{
				dialog.text = "Fechado! "+sti(iQty*iMoney)+" pesos.";
				if(sti(pchar.money) < iQty*iMoney)
				{
					link.l1 = "Hum, eu não tenho tanto dinheiro assim. Talvez numa outra hora.";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "Fechado! Traga as mercadorias para o meu navio.";
					link.l1.go = "Удачная покупка";
					link.l2 = "Sabe, mudei de ideia sobre comprar seus mantimentos.";
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
				dialog.text = "Isso é demais... Eu não tenho tudo isso! Você poderia comprar menos?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта";	
				link.l2 = "Sabe, mudei de ideia sobre comprar seus mantimentos.";	
				link.l2.go = "exit";
			}	
			if(iQty < 1)
			{
				dialog.text = "Você está brincando comigo? Precisa de mantimentos ou não? Se sim, quanto?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта";	
				link.l2 = "Sabe, mudei de ideia sobre comprar seus mantimentos.";	
				link.l2.go = "exit";
			}
			if(iQty > 0 && iQty <= iTemp)
			{
				dialog.text = "Fechado! "+sti(iQty*iMoney)+" pesos.";
				if(sti(pchar.money) < iQty*iMoney)
				{
					link.l1 = "Hum, eu não tenho tanto dinheiro assim. Talvez outra hora.";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "Fechado! Carregue as mercadorias no meu navio.";
					link.l1.go = "Удачная покупка";
					link.l2 = "Sabe, mudei de ideia sobre comprar seus mantimentos.";
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
				dialog.text = "Temos "+iTemp+" peças. Podemos vendê-las por cem pesos cada arpão. Quantos você precisa?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов";
				link.l2 = "Sabe, mudei de ideia, não preciso dos arpões.";	
				link.l2.go = "exit";
		break;
		
		case "Количество вбитых гарпунов":
   
			iQty = sti(dialogEditStrings[3]);
			iTemp = makeint(pchar.GenQuest.FishingBoatITemp);
			pchar.GenQuest.FishingBoatIQty = iQty;
			Diag.TempNode = "FishingBoat_1";
			if(iQty > iTemp)
			{
				dialog.text = "Isso é demais... Eu não tenho tudo isso! Você poderia comprar menos?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов заново";	
				link.l2 = "Sabe, mudei de ideia, não preciso dos arpões.";	
				link.l2.go = "exit";
			}	
			if(iQty < 1)
			{
				dialog.text = "Você está brincando comigo? Você precisa de arpões ou não? Se sim, quantos?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов заново";	
				link.l2 = "Sabe, mudei de ideia, não preciso mais dos arpões.";	
				link.l2.go = "exit";
			}
			if(iQty > 0 && iQty <= iTemp)
			{
				dialog.text = "Fechado! "+sti(iQty*100)+" pesos.";
				if(sti(pchar.money) < iQty*100)
				{
					link.l1 = "Hum, eu não tenho tanto dinheiro assim. Talvez em outra ocasião.";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "Fechado! Vou dar um jeito de usá-los.";
					link.l1.go = "Удачная покупка гарпунов";
					link.l2 = "Sabe, mudei de ideia, não preciso dos arpões.";
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
				dialog.text = "Isso é demais... Eu não tenho tudo isso! Você poderia comprar menos?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов";	
				link.l2 = "Sabe, mudei de ideia, não preciso dos arpões.";	
				link.l2.go = "exit";
			}	
			if(iQty < 1)
			{
				dialog.text = "Você está brincando comigo? Você precisa de arpões ou não? Se sim, quantos?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов";	
				link.l2 = "Sabe, mudei de ideia, não preciso dos arpões.";	
				link.l2.go = "exit";
			}
			if(iQty > 0 && iQty <= iTemp)
			{
				dialog.text = "Fechado! "+sti(iQty*100)+" pesos.";
				if(sti(pchar.money) < iQty*100)
				{
					link.l1 = "Hum, eu não tenho tanto dinheiro assim. Talvez outra hora.";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "Fechado! Vou dar um jeito de usá-los.";
					link.l1.go = "Удачная покупка гарпунов";
					link.l2 = "Sabe, mudei de ideia, não preciso mais dos arpões.";
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
				dialog.text = "Não, não tem mais nada. É só um barco de pesca! O que mais poderia ter aqui?";
				link.l1 = "Tá bom, entendi.";
				link.l1.go = "exit";
			}
			else if(hrand(2, "&SpeGoo") == 1)
			{
				if(ChangeContrabandRelation(pchar, 0) > 5)
				{
					
					dialog.text = "Bem ... eu tenho uma coisinha aqui ... Guardei, pensei em vender pra alguém. Mas vou cobrar caro por ela! E não vou oferecer de novo. Vai querer ver?";
					link.l1 = "Mostre, vamos ver que tipo de coisinha é essa.";
					link.l1.go = "Особые товары предметы";
				}
				else
				{
					Diag.TempNode = "First time";
					Diag.CurrentNode = "First time";
					pchar.GenQuest.FishingBoatDialogEnb = "no special goods";
					dialog.text = "Não, não tem mais nada. É um barco de pesca! O que mais poderia ter aqui?";
					link.l1 = "Tá bom, eu entendi. ";
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
					
					dialog.text = "Bem ... Eu tenho uma boa aqui ... Por pura sorte, encontrei isso na beira da baía. É "+iQty+" "+sTemp+". O preço por peça é "+iMoney+". Mas eu só vou vender tudo de uma vez e não vou oferecer de novo. E para que nenhum estranho fique sabendo disso ... entendeu?";
					link.l1 = "Não, eu não quero essas mercadorias duvidosas, obrigado. Não vou contar pra ninguém, pode ficar tranquilo.";
					link.l1.go = "exit";
					if(sti(pchar.money) >= iMoney*iQty)
					{
						link.l2 = "Eu entendo você. Mas a mercadoria vale a pena. Eu fico com ela. Mande entregar no meu navio.";
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
				dialog.text = "É "+GetItemName(sTemp)+". Consegui arranjar isso... bem, não importa onde. Pensei em vender para algum conhecedor. Te faço por apenas 10.000 pesos! Vai querer?";
				if(sti(pchar.money) > 9999)
				{
					link.l1 = "Eu aceito, claro! O negócio está de pé. ";
					link.l1.go = "Купили особый товар";
				}
				link.l2 = "Não, eu não preciso disso. Eu não vou aceitar. ";
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
