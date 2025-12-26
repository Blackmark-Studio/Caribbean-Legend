// boal 25/04/04 общий диалог мэры
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref aData;
	aref Link, NextDiag, arName;

	DeleteAttribute(&Dialog,"Links");

	ref FortChref; // фортовый командер
	ref arItem;
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Mayor\" + NPChar.City + "_Mayor.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
    ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

    FortChref = GetFortCommander(NPChar.City); // будет или фортовик или сам губернатор

    ref offref;
    int i, cn, iRank, iDay;
    int qty;
    string attrLoc, QuestName, sTemp;
	bool bOk, bOk1, bOk2;
	
    if (CheckNPCQuestDate(npchar, "Card_date"))
	{
		SetNPCQuestDate(npchar, "Card_date");
		npchar.money = 5000 + (rand(10)+1) * makeint(100 * sti(PChar.rank) * (10.0 / MOD_SKILL_ENEMY_RATE));
	}
	// генератор ИДХ по кейсу -->
	attrLoc   = Dialog.CurrentNode;
  	if (findsubstr(attrLoc, "GetPrisonerIdx_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	pchar.GenQuest.GetPrisonerIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "sell_prisoner_2";
 	}
 	// генератор ИДХ по кейсу <--
 	
	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");
		break;
		
		case "fight":
            Pchar.quest.ArestInResidenceEnd.win_condition.l1          = "ExitFromLocation";
		    Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		    Pchar.quest.ArestInResidenceEnd.win_condition             = "ArestInResidenceEnd";
		    Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

			LAi_LockFightMode(Pchar, true); // ножками путь убегает
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		    LAi_group_Attack(NPChar, Pchar); // не работает на бессмертного мера :(
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;
		
		case "First time":
            NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Você ousa aparecer na minha casa?! Muito corajoso da sua parte, ou talvez tolo...","Como meus guardas idiotas deixaram um inimigo invadir meu palácio? Vou fazer alguém pagar caro por isso.","Aparentemente, meus guardas não valem nem um tostão, se qualquer canalha pode andar pela minha residência e mexer nas minhas coisas..."),LinkRandPhrase("O que você precisa, "+GetSexPhrase("canalha","diabo")+"?! Meus soldados já estão no seu encalço"+GetSexPhrase(", pirata imundo","")+"!",+"Assassino, saia da minha residência agora mesmo! Guardas!","Eu não tenho medo de você, "+GetSexPhrase("canalha","rato")+"! Em breve você será enforcado em nosso forte!"));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Seus soldados não valem nada.","Tenta me pegar."),RandPhraseSimple("Cale a boca, "+GetWorkTypeOfMan(npchar,"")+", ou eu fecho pra você!","Fique quieto, camarada, e você vai continuar vivo."));
				link.l1.go = "fight";
				break;
			} 
			if (sti(NPChar.nation) == PIRATE)
            {
				if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar, "GenQuest.CaptainComission.PiratesCity") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
				{
					dialog.text = "O que você precisa?";
					link.l1 = "Queria conversar com você sobre um assunto importante.";
					link.l1.go = "quests";
					break;
				}
				if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin" && NPChar.city == "LeFransua")
				{
					dialog.text = "O que você precisa?";
					link.l1 = "Queria conversar com você sobre um trabalho importante.";
					link.l1.go = "quests";
					break;
				}
					dialog.text = "Não há nada para discutir, senhor. Estou ocupado.";
					link.l1 = "Me desculpe.";
					link.l1.go = "Exit";
            }
			if (sti(NPChar.nation) != PIRATE && ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0) > 10)
            {
				iTotalTemp = ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0);
                dialog.text = "Oh, olha só quem está aí! É"+GetSexPhrase("","")+" "+GetFullName(pchar)+". Sabe, eu acabei de mandar caçadores de piratas atrás de você para trazê-lo de volta. Se eu soubesse que você ia entrar por aquela porta assim, teria economizado meu dinheiro.";
                if (sti(pchar.Money) >= iTotalTemp*6000)
                {
                    link.l1 = "Eu estava prestes a acertar nossas contas.";
				    link.l1.go = "arestFree_1";
                }
				link.l2 = "Está na hora de eu fazer uma saída rápida.";
				link.l2.go = "arest_1";
				break;
            }
			if (false)
			{
    			dialog.text = "Invasão! Guardas! Alarme! Assassinato!";
				link.l1 = "Merda!";
				link.l1.go = "fight"; 
				break;
			}
			//--> Jason, Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Citcount") && npchar.city == "FortFrance")
			{
    			dialog.text = "O que deseja, monsieur?";
				link.l1 = "Olá, Vossa Graça. Sou Charles de Maure, acabei de chegar de Paris. Estou procurando Michel de Montper.";
                link.l1.go = "Sharlie";
				npchar.quest.meeting = "1"; // patch-6
				DelLandQuestMark(characterFromId("FortFrance_Mayor"));
				break;
			}
			
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock") && npchar.city == "FortFrance")
			{
				if (CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
				{
					dialog.text = "Ah, é você, senhor... Preciso pedir desculpas pela minha grosseria. Me perdoe, estamos longe das gentilezas de Paris aqui nas colônias.";
					link.l1 = "Claro, Vossa Graça.";
					link.l1.go = "Sharlie_2";
				}
				else
				{
					dialog.text = "Você queria alguma coisa, Charles?";
					link.l1 = "Tenho uma pergunta...";
					link.l1.go = "quests";
					link.l2 = "Não, nada.";
					link.l2.go = "exit";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
				{
					link.l3 = "Monsieur, encontrei o corpo de um bandido na selva. Ele foi morto pelos índios. Havia brincos com ele, parecem ter vindo da Europa. Talvez pertençam a algum nobre da sua cidade?";
					link.l3.go = "Sharlie_junglejew";
				}
				npchar.quest.meeting = "1"; // patch-6
				break;
			}			
			//<-- Бремя гасконца
			//--> Sinistra, Травля крысы
			if (CheckAttribute(pchar, "questTemp.TK_TravlyaKrys") && npchar.city == "FortFrance")
			{
    			dialog.text = "Bem-vindo ao Caribe, Capitão de Maure. Desta vez, de verdade.";
				link.l1 = "Obrigado, Vossa Excelência.";
                link.l1.go = "TK_TravlyaKrys";
				DelLandQuestMark(npchar);
				break;
			}
			// Jason НСО
			// belamour legendary edition фикс проверки мундира с мушкетом
			if (CheckAttribute(pchar, "questTemp.Patria.Governor") && npchar.city == "Marigo" && IsUniformEquip())
			{
    			dialog.text = "É bom vê-lo, Governador! Como está? Tudo sob controle em Sint Maarten.";
				link.l1 = "Não tenho tempo para ficar. Continue com o bom trabalho.";
				link.l1.go = "exit";
				link.l2 = "Queria falar sobre trabalho.";
				link.l2.go = "quests";   //(перессылка в файл города)
				link.l8 = "Que tal um jogo de azar?";
				link.l8.go = "Play_Game";
				break;
			}
			// belamour legendary edition фикс проверки мундира с мушкетом
			if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE && IsUniformEquip())
			{
    			dialog.text = "Meu Deus, que prazer vê-lo, Governador-Geral! Está tudo maravilhoso aqui na nossa humilde colônia! Por favor, sente-se, vou pedir aos criados que preparem a mesa...";
				link.l1 = "Não precisa. Não vou ficar muito tempo. Continue com o bom trabalho.";
				link.l1.go = "exit"; 
				link.l2 = "Queria falar sobre trabalho.";
				link.l2.go = "quests";   //(перессылка в файл города)
				link.l8 = "Que tal um jogo de sorte?";
				link.l8.go = "Play_Game";
				break;
			}
			// belamour legendary edition фикс проверки мундира с мушкетом
			if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor") &&  IsUniformEquip())
			{
    			dialog.text = "Quem temos aqui! Monsieur Governador-Geral das Colônias Francesas! O que o traz aqui, Vossa Excelência? Sente-se, vou pedir aos meus criados que tragam vinho e frutas frescas.";
				link.l1 = "Não se preocupe, só vim aqui porque estava visitando a ilha, e não podia simplesmente passar sem dar um oi.";
				link.l1.go = "exit"; 
				link.l2 = "Queria falar sobre trabalho.";
				link.l2.go = "quests";   //(перессылка в файл города)
				link.l8 = "Que tal um jogo de azar?";
				link.l8.go = "Play_Game";
				break;
			}		
			//--> Jason, Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "MartiniqueGovernor" && npchar.city == "FortFrance")
			{
    			dialog.text = "Ah, aí está você, capitão! Tenho que dizer, você demorou mesmo.";
				link.l1 = "Cheguei assim que pude, Vossa Excelência. Disseram-me que há assuntos urgentes?";
				link.l1.go = "Portugal"; 
				break;
			}			
			//<-- Португалец
            
            if (npchar.quest.meeting == "0")
			{
				dialog.text = "Meus homens me disseram que você foi bastante insistente ao pedir uma audiência. Meu nome é "+GetFullName(npchar)+". Eu sou o governador da cidade de "+GetCityName(NPChar.city)+", súdito de "+NationKingsName(npchar)+". E agora, por favor, o que você deseja "+GetAddress_Form(NPChar)+"?";
				link.l1 = "Meu nome é "+GetFullName(pchar)+".";
				link.l1.go = "node_1";
				npchar.quest.meeting = "1";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_townhall")
				{
					dialog.text = TimeGreeting()+", Srta. MacArthur.";
					link.l1 = TimeGreeting()+", Vossa Excelência.";
					link.l1.go = "Helen_node_1"
				}
			}
			else
			{
               	//ОСАДЫ homo
				if (CheckAttribute(&Colonies[FindColony(npchar.City)],"Siege"))
                {

                    makearef(aData, NullCharacter.Siege);
                    
                    if (CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                    {
                        dialog.text = "É só isso?";
                        link.l1 = "Sim, senhor. Não vou tomar mais do seu tempo.";
                        link.l1.go = "exit";

                    }
                    else
                    {
                        dialog.text = "Me desculpe por incomodá-lo, mas não tenho tempo para conversar com você agora. Como deve saber, nossa colônia foi atacada por "+NationNamePeople(sti(aData.nation))+". Ainda estou cuidando das nossas defesas.";
                        link.l1 = "Quero oferecer minha ajuda na defesa do forte.";
                        link.l1.go = "siege_task";
                        link.l2 = "Então não vou mais tomar seu tempo.";
            			link.l2.go = "exit";
                    }
                }
                else
                {//->
                    makearef(aData, NullCharacter.Siege);
                    if (CheckAttribute(aData, "PlayerHelpMayor") && sti(aData.PlayerHelpMayor) == true
                    && CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                    {
                        AddMoneyToCharacter(Pchar,(sti(aData.iSquadronPower)*1500));
                        ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                        ChangeCharacterComplexReputation(pchar,"nobility", 10);
                        AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 180);
                        AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 200);
                        AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 200);
                        AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 200);
                        //--> слухи
                        SiegeRumour("They say that you had helped us to repel the "+NationNameSK(sti(aData.nation))+" squadron and to defend our colony! We are grateful to you, "+ GetAddress_Form(NPChar)+".", aData.Colony, sti(aData.conation), -1, 15, 3);
			            //<-- слухи
                        DeleteAttribute(aData, "PlayerHelpMayor");
                        DeleteAttribute(aData, "HelpColony");
                        dialog.text = "Ah, é você, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+", fico feliz em vê-lo. Boas notícias para nossa colônia – conseguimos repelir o "+NationNameSK(sti(aData.nation))+" invasores. Você também teve participação nisso, então aqui está sua recompensa - "+(sti(aData.iSquadronPower)*1500)+" peças de oito. Aqui está.";
                        link.l1 = "Obrigado, "+GetAddress_FormToNPC(NPChar)+", um prazer fazer negócios com você!";
                        link.l1.go = "exit";
                    }
                    else
                    {
   						//--> дача квеста найти кольцо в борделе
						if (rand(4) == 4 && pchar.questTemp.different == "free" && GetNpcQuestPastDayWOInit(npchar, "questTakeRing") > 365 && sti(pchar.questTemp.HorseQty) > 10)
						{// Addon-2016 Jason
							if (npchar.city == "Bridgetown" || npchar.city == "Charles" || npchar.city == "FortFrance" || npchar.city == "Marigo" || npchar.city == "Panama" || npchar.city == "PortRoyal" || npchar.city == "SantoDomingo" || npchar.city == "Tortuga")
							{
        						dialog.text = "Tenho uma tarefa para você, mas é um pouco fora do comum.";
								link.l1 = "Essas são as tarefas em que sou melhor.";
        						link.l1.go = "TakeRing_1";
								SaveCurrentNpcQuestDateParam(npchar, "questTakeRing");
								break;
							}
						}
						//<-- дача квеста найти кольцо в борделе    				
						dialog.text = RandPhraseSimple("Ah, é você de novo? O que você quer de mim desta vez?","Você está me distraindo dos assuntos da minha cidade. O que você quer, "+GetAddress_Form(NPChar)+"?");
						if (npchar.city != "Panama") // Addon-2016 Jason
						{
							link.l1 = "Quero conversar com você sobre trabalhar para "+NationNameGenitive(sti(NPChar.nation))+".";
							link.l1.go = "work";
						}
						// Warship Генер "Пираты на необитайке" - сдаём пиратов властям
						if(CheckAttribute(PChar, "Quest.PiratesOnUninhabited_OnShore") || CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
						{
							link.l11 = XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore+"Gen")+" Encontrei alguns piratas. Todos "+PChar.GenQuest.PiratesOnUninhabited.PiratesCount+" estão a bordo neste momento. Quero entregá-los às autoridades.";
							link.l11.go = "PiratesOnUninhabited_1";
						}
						
        				link.l2 = "Queria conversar com você sobre algo importante.";
						if(CheckAttribute(pchar,"questTemp.ReasonToFast") && !CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
						{
							link.l2.go = "ReasonToFast_Mayor1";
						}
						else
						{
							link.l2.go = "quests";   //(перессылка в файл города)
						}	
						if(CheckAttribute(pchar,"GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
						{
							if(pchar.GenQuest.CaptainComission == "Begin_1" && !CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor")) 
							{
								link.l12 = "Há um capitão no comando da patrulha "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" named "+pchar.GenQuest.CaptainComission.Name+", como posso vê-lo?";
								link.l12.go = "CapComission_Mayor1";
							}	
							if(CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
							{
								link.l12 = "Ex-capitão no comando da patrulha "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" concordou em revelar seu esconderijo às autoridades.";
								link.l12.go = "CapComission_Mayor9";
							}
							if(pchar.GenQuest.CaptainComission == "GetGoodsSuccess")
							{
								link.l12 = "Ex-capitão no comando da patrulha "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" revelou seu esconderijo para mim.";
								link.l12.go = "CapComission_Mayor13";
							}
						}
						if(CheckAttribute(pchar,"GenQuest.ShipWreck") && pchar.GenQuest.ShipWreck == "SailorsOnShore" && GetQuestPastDayParam("GenQuest.ShipWreck") < 25  && sti(npchar.nation) == sti(pchar.GenQuest.ShipWreck.Nation))
						{
							if(!CheckAttribute(pchar,"GenQuest.ShipWreck.SpeakMayor"))
							{
								iDay = GetQuestPastDayParam("GenQuest.ShipWreck");
								if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
								{
									link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Dat"))+" Encontrei o capitão "+pchar.GenQuest.ShipWreck.Name+" e seus marinheiros que foram deixados em terra pelos piratas "+pchar.GenQuest.ShipWreck.BadName+". "+"Infelizmente, eu já tinha homens demais no meu navio e não pude levá-los a bordo. Mas deixei provisões e armas com eles. Se um navio de resgate não os encontrar dentro de "+(30 - iDay)+" dias, então não sei se vou encontrá-los vivos ou não.";
									link.l13.go = "ShipWreck1";
								}
								else
								{
									link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Gen"))+" Encontrei marinheiros do navio naufragado '"+pchar.GenQuest.ShipWreck.ShipTypeName+"‘ com o capitão deles. "+"Infelizmente, eu já tinha homens demais no meu navio e não pude levá-los a bordo. Mas deixei provisões e armas com eles. Se um navio de resgate não os encontrar dentro de "+(30 - iDay)+" dias, então não sei se vou encontrá-los vivos ou não.";
									link.l13.go = "ShipWreck1";							
								}
							}	
						}
        				if (GetPrisonerQty() > 0)
        				{
                            link.l3 = "Quero entregar um prisioneiro.";
        				    link.l3.go = "sell_prisoner";
        				}
        				if (npchar.Default  == npchar.location) // если не в тюрьме
        				{
        					if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
        					{
        						link.l4 = "Preciso resolver alguns assuntos financeiros com você.";
        						link.l4.go = "LoanForAll";//(перессылка в кредитный генератор)
        					}
        				}
						//-->> сдача найденного в борделе кольца
						if (CheckCharacterItem(pchar, "MayorsRing"))
						{
							if (pchar.questTemp.different.TakeMayorsRing == "toBrothel")
							{
        						link.l5 = "Consegui encontrar seu anel. Aqui está.";
        						link.l5.go = "TakeRing_S1";
							}
							else
							{
        						link.l5 = "Eu tenho sua aliança de casamento. Uma das... garotas que trabalham no bordel estava com ela.";
        						link.l5.go = "TakeRing_S3";
							}
						}
						//<<-- сдача найденного в борделе кольца 
						
						//--> Jason, генер почтового курьера 2 уровня
						if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
						{
							if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
							{
							link.l14 = "Trago uma mensagem da cidade de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
							link.l14.go = "Postcureer_LevelUp_ForAll";
							}
						}
						//<-- генер почтового курьера 2 уровня
						
						// Warship, 16.05.11. Квест "Правосудие на продажу" -->
						if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
						{
							link.l15 = UpperFirst(GetAddress_FormToNPC(NPChar))+", encontrei uma quadrilha de contrabandistas cujo chefe foi recentemente capturado pelos guardas. Agora estão tramando a fuga dele. O navio deles '"+PChar.GenQuest.JusticeOnSale.ShipName+"' está atracado em "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Dat")+".";
							link.l15.go = "JusticeOnSale_1";
						}
						
						if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.ShipSink") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
						{
							link.l15 = UpperFirst(GetAddress_FormToNPC(NPChar))+", a quadrilha de contrabandistas não existe mais!";
							link.l15.go = "JusticeOnSale_7";
						}
						// <--Правосудие на продажу
						//Jason --> Регата
						if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
						{
							link.l16 = "Vim para a regata. Aqui está meu convite.";
							link.l16.go = "Regata";
						}
        				//link.l7 = "Gostaria de saber onde está o Governador-Geral de "+NationNameGenitive(sti(NPChar.nation))+"é.";
        				link.l8 = "Talvez queira fazer uma pausa com um jogo de azar?";
        			    link.l8.go = "Play_Game";
        				link.l10 = "Por favor, me desculpe, mas o dever me chama.";
        				link.l10.go = "exit";
                    }
                }//<-
			}
		break;
		
		// Warship Генер "Пираты на необитайке"
		case "PiratesOnUninhabited_1":
			offref = CharacterFromID("PirateOnUninhabited_0");
			qty = makeint(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) * (sti(offref.rank) * (800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L) * 100) + GetCharacterSkillToOld(offref, "Leadership") * 500 + GetCharacterSkillToOld(PChar, "commerce") * 500) / 20);
			
			PChar.GenQuest.PiratesOnUninhabited.MoneyForPirates = qty;
			
			dialog.text = "Muito bem. Precisamos combater essa praga juntos, com nossos esforços combinados. Vou mandar um navio imediatamente para buscá-los. Pode ter certeza de que eles estarão na forca em menos de uma semana. Ah, e claro, você receberá sua recompensa - "+FindRussianMoneyString(qty)+".";
			link.l1 = "Obrigado, Vossa Graça. Sempre um prazer. ";
			link.l1.go = "PiratesOnUninhabited_2";
			link.l2 = "Não. Pensando bem, isso não vai servir.";
			link.l2.go = "exit";
		break;
		
		case "PiratesOnUninhabited_2":
			offref = CharacterFromID("PirateOnUninhabited_0");
			
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.MoneyForPirates));
			
			RemovePassenger(PChar, offref);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
			
			sTemp = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTemp, "PiratesOnUninhabited", "12");
			AddQuestUserData(sTemp, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTemp, "mayorName", GetFullName(NPChar));
			CloseQuestHeader(sTemp);
			
			PChar.Quest.PiratesOnUninhabited_OnShore.over = "yes";
			PChar.Quest.PiratesOnUninhabited_OnMayak.over = "yes";
			
			if(CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
			{
				PChar.Quest.PiratesOnUninhabited_ShipSink.over = "yes";
				
				PChar.GenQuest.PiratesOnUninhabited.ClearShip = true;
				Map_ReleaseQuestEncounter("PiratesOnUninhabited_BadPirate"); // Убираем с глобалки
			}
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
		break;
		
		// ------------------------- Повод для спешки -----------------------------
		case "ReasonToFast_Mayor1":
			dialog.text = "Estou ouvindo, capitão.";
			link.l1 = "Queria lhe contar sobre uma colaboração criminosa entre um oficial da sua guarnição e piratas... (explica o caso).";
			if(sti(pchar.reputation.nobility) < 41)
			{
				link.l1.go = "ReasonToFast_BMayor";			
			}
			else
			{
				link.l1.go = "ReasonToFast_GMayor";	
			}
			pchar.questTemp.ReasonToFast.SpeakOther = true;			
		break;
		
		case "ReasonToFast_GMayor":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 
				// вилка_А
				dialog.text = "Obrigado, "+GetSexPhrase("senhor","senhorita")+"! Vou imediatamente ordenar a prisão desse traidor.\nVocê deve ter gastado muito dinheiro, mas infelizmente nosso tesouro está vazio...";
				link.l1 = "Eu não fiz isso pelo dinheiro, excelência.";
				link.l1.go = "ReasonToFast_GMayor_11";				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}			
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// получена карта
				dialog.text = "Eu lhe agradeço! Mandarei prender esse canalha.\nVeja só! Eu estava prestes a presenteá-lo com um sabre de cabo dourado pelos seus dez anos de serviço! Você me salvou de um vexame daqueles!";
				link.l2 = "A justiça é sua própria recompensa.";
				link.l2.go = "ReasonToFast_GMayor_21";			
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// патруль перебит
				dialog.text = "Mis"+GetSexPhrase("ter","s")+" de Maure, você não pode simplesmente matar um suspeito sem nenhuma testemunha! Agora nem conseguimos provas dos crimes dele! Estou me esforçando ao máximo para evitar que você seja preso por homicídio.";
				link.l3 = "Foi legítima defesa, Vossa Excelência.";
				link.l3.go = "ReasonToFast_GMayor_31";
				pchar.questTemp.ReasonToFast.speakAfterPatrolDied = true;	
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
			}			
		break;
		
		case "ReasonToFast_BMayor":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 				
				dialog.text = "Capitão, você tem ideia do que acabou de fazer?! Eu passei mais de um mês preparando essa armadilha! E agora, só para se divertir, você arruinou o encontro da nossa patrulha com "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_GEN)+" e agora você vem aqui se gabar disso?!! Talvez você possa me dizer agora, como devo justificar todas as despesas e custos dessa operação?!";
				link.l1 = "Excelência, acabei de resolver o seu problema. Se pensar bem, devia estar me pagando desde o começo!";
				link.l1.go = "ReasonToFast_BMayor_1";
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// получена карта
				dialog.text = "Deixe-me ver esse mapa\nVocê está falando sério? Esse pedaço de papel velho é a prova?";
				link.l2 = "Vamos lá, Vossa Graça, seja razoável.";
				link.l2.go = "ReasonToFast_BMayor_1";
				TakeItemFromCharacter(pchar, "mapQuest");				
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_B";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// патруль перебит
				dialog.text = "Bem, bem, agora sabemos o que aconteceu com a minha patrulha. Pelo menos, vindo até aqui, você nos poupou o trabalho de procurar o assassino.";
				link.l3 = "Vossa Graça! O senhor simplesmente se recusa a entender...";
				link.l3.go = "ReasonToFast_BMayor_1";			
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
			}		
		break;
		
		case "ReasonToFast_GMayor_11":
			dialog.text = "You may be an idiot but you are at least a useful idiot. Here - take this map; found it on a pirate who we hanged last week. God willing, perhaps you will find his treasure, although I find it quite unlikely...";
			link.l1 = "Muito obrigado, isso é realmente muito generoso da sua parte!";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "15");
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			GiveItem2Character(pchar, "mapQuest"); 
			arItem = ItemsFromID("mapQuest");
			ReasonToFast_GenerateTreasureMap(arItem);
			pchar.questTemp.ReasonToFast.state = "chain_A"; // вилка_А, наводки не генерим
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		
		case "ReasonToFast_GMayor_21":
			dialog.text = "Seu empenho é admirável. Por favor, aceite esta espada como recompensa – é o mínimo que posso fazer. Ah, e pode ficar com o mapa para você. Tenho certeza de que há muitos desses falsos espalhados pelo Caribe.";
			link.l1 = "Obrigado, isso é muito generoso da sua parte!";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "14");
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
			pchar.questTemp.ReasonToFast.state = "chain_B"; // была получена карта
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		case "ReasonToFast_GMayor_31":
			dialog.text = "Talvez, talvez... Bem, digamos apenas que este acordo foi decidido pela justiça divina e pela vontade do nosso Senhor.";
			link.l1 = "Muito obrigado, isso é muito generoso da sua parte!";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			AddQuestRecord("ReasonToFast", "16");
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar,"ReasonToFast");
		break;
		
		case "ReasonToFast_BMayor_1":
			dialog.text = "Controle-se, rapaz! Ou você enlouqueceu, ou está aliado aos nossos inimigos! Guardas, prendam esse idiota!";
			link.l1 = "Encoste um dedo em mim e vai perder a mão!";
			link.l1.go = "fight";
		
			pchar.quest.ReasonToFast_ExitFromTown.win_condition.l1			= "EnterToSea";           	
            pchar.quest.ReasonToFast_ExitFromTown.function    				= "ReasonToFast_ExitFromTownFight";						
			pchar.questTemp.ReasonToFast.canSpeakSailor = true;
			pchar.TownEscape = true;
			Flag_PIRATE();
		break;
		
		// ------------------------- Повод для спешки -----------------------------
		
		// --------------------------Операция 'Галеон'-----------------------------
		case "CapComission_Mayor1":
			dialog.text = "Neste momento, isso é impossível. Ele está preso, aguardando julgamento.";
			link.l1 = "É mesmo? E do que ele é suspeito?";			
			link.l1.go = "CapComission_Mayor2";
		break;
		
		case "CapComission_Mayor2":
			dialog.text = "Infelizmente, não é uma suspeita, mas um fato comprovado. Temos informações de que ele atacava navios sob o pretexto de patrulhar. Ele confiscava mercadorias de comerciantes e depois as vendia para contrabandistas e piratas. É uma pena... pensar que um dia ele foi considerado um dos melhores capitães que a Coroa já teve...";
			link.l1 = "E quem lhe deu as provas?";
			link.l1.go = "CapComission_Mayor3";				
		break;
		
		case "CapComission_Mayor3":
			dialog.text = "Uma das vítimas dele escreveu um relatório, no qual descreveu o incidente em detalhes, incluindo a data, o nome do navio atacado e a quantidade de mercadorias confiscadas. "+"Pode confiar, os números são realmente impressionantes. Na patrulha daquele dia "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")))+" capitão "+pchar.GenQuest.CaptainComission.Name+" estava realmente de serviço. O capitão descreveu esse incidente como um encontro com um navio pirata em seu relatório, mas não mencionou nenhuma carga.";
			link.l1 = "Mas havia alguma carga mesmo?";
			link.l1.go = "CapComission_Mayor4";
			pchar.GenQuest.CaptainComission.SpeakMayor = true;
		break;
		
		case "CapComission_Mayor4":
			dialog.text = "Não há dúvida quanto a isso. A parte lesada é um homem muito respeitado e não se rebaixaria a calúnias ou difamações. Neste momento, nossas patrulhas estão procurando o esconderijo do capitão. "+"Assim que for encontrado, o capitão poderá comparecer ao tribunal\nSe você nos ajudar com isso, seremos muito gratos a você.";
			link.l1 = "Provavelmente não. Não conheço bem a região para sair procurando um esconderijo. Com licença, preciso ir.";
			link.l1.go = "CapComission_Mayor5";
			link.l2 = "Talvez... Quanto tempo eu tenho?";
			link.l2.go = "CapComission_Mayor6";	
		break;
		
		case "CapComission_Mayor5":
			AddQuestRecord("CaptainComission2", "49");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			pchar.GenQuest.CaptainComission = "MayorTalkBad";
			CaptainComission_GenerateCaptainInPrison();
			DialogExit();
		break;
		
		case "CapComission_Mayor6":
			dialog.text = "Acredito que em dois dias as patrulhas conseguirão localizar o esconderijo sem a sua ajuda, então é melhor você se apressar."; 
			link.l1 = "Certo, vou cuidar disso. Mas vou precisar fazer uma visita ao capitão "+pchar.GenQuest.CaptainComission.Name+". Isso pode ser providenciado?";
			link.l1.go = "CapComission_Mayor7";
		break;
		
		case "CapComission_Mayor7":
			dialog.text = "Isso não será um problema. Vou informar o comandante do forte sobre a sua visita.";
			link.l1 = "Obrigado. Agora, por favor, me dê licença.";
			link.l1.go = "CapComission_Mayor8";
		break;
		
		case "CapComission_Mayor8":
			AddQuestRecord("CaptainComission2", "50");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);			
			AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			OfficersReaction("good");
			pchar.GenQuest.CaptainComission.MayorTalkGood = true;
			pchar.GenQuest.CaptainComission = "MayorTalkGood";
			pchar.quest.CaptainComission_TimeIsOver.over = "yes";
			SetFunctionTimerConditionParam("CaptainComission_GetSecretTimeIsOut", 0, 0, 2, MakeInt(24 - GetHour()), false);
			CaptainComission_GenerateCaptainInPrison();
			DialogExit();
		break;
		
		case "CapComission_Mayor9":
			dialog.text = "Excelente! Onde está o tesouro?";
			link.l1 = "Ainda não faço ideia. Ele não me disse o local exato.";
			link.l1.go = "CapComission_Mayor10";
		break;
		
		case "CapComission_Mayor10":
			dialog.text = "Hmm, que coincidência! Sabe, ele também 'não me indicou' o local exato...";
			link.l1 = "Estou trabalhando nisso.";
			link.l1.go = "CapComission_Mayor11";
		break;
		
		case "CapComission_Mayor11":
			dialog.text = "Não mais\nGuardas! Levem o prisioneiro de volta às celas\nVocê está livre para ir, "+GetFullName(pchar)+".";
			link.l1 = "Mas governador...";
			link.l1.go = "CapComission_Mayor12";
		break;
		
		case "CapComission_Mayor12":
			sld = CharacterFromID("CapComission_1");
			sld.lifeDay = 0;
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetActorType(sld);
            LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);			
			pchar.quest.CapComission_DeletePrisonGroup.win_condition.l1 = "ExitFromLocation";
            pchar.quest.CapComission_DeletePrisonGroup.win_condition.l1.location = pchar.location;
            pchar.quest.CapComission_DeletePrisonGroup.win_condition = "CaptainComission_DeletePrisonGroup";									
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", -4);			
			AddQuestRecord("CaptainComission2", "23");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("CaptainComission2");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CapComission_Mayor13":
			pchar.quest.CaptainComission_SpeakMayorGoods.over = "yes";
			dialog.text = "Excelente! E onde vamos procurar o tesouro dele?";
			link.l1 = "No  "+RandPhraseSimple(RandPhraseSimple("do norte","ocidental"),RandPhraseSimple("oriental","sul"))+" fim de "+XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore+"Gen")+" aos pés do penhasco há um grande nicho, cuja entrada está bloqueada por pedras. Esse é o esconderijo.";
			link.l1.go = "CapComission_Mayor14";
		break;
		
		case "CapComission_Mayor14":
			dialog.text = "Excelente trabalho! E onde está "+pchar.GenQuest.CaptainComission.Name+" ele mesmo? Disseram-me que você o tirou das masmorras do forte.";
			link.l1 = "Infelizmente, ele morreu em um confronto com os contrabandistas.";
			link.l1.go = "CapComission_Mayor15";
		break;
		
		case "CapComission_Mayor15":
			dialog.text = "Isso é ruim... Isso é muito ruim, "+GetSexPhrase("senhor","senhorita")+" "+GetFullName(pchar)+". Eu ia executá-lo em público, 'para servir de exemplo aos outros.'"+"De qualquer forma, ele não teria escapado da forca\nEntão, como você tecnicamente violou a lei ao libertar um prisioneiro ilegalmente, mas mesmo assim não conseguiu salvá-lo, não posso alterar isso no relatório. Portanto, você não receberá uma recompensa... Mas gostaria de lhe agradecer pessoalmente. Aceite meu presente – algo muito útil para um capitão de combate. ";
			link.l1 = "Obrigado. Sempre feliz em servir.";	
			link.l1.go = "CapComission_Mayor16";
		break;
		
		case "CapComission_Mayor16":
			AddQuestRecord("CaptainComission2", "30");
			AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			CloseQuestHeader("CaptainComission2");
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			ChangeCharacterComplexReputation(pchar,"nobility", 4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
			OfficersReaction("good");
			DeleteAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		// --------------------------Операция 'Галеон'-----------------------------
		
		// -------------------------- Генератор "Кораблекрушенцы" ------------
		case "ShipWreck1":
			if(iDay > 15)
			{
				dialog.text = RandPhraseSimple("Como você faz isso? Leva pelo menos quinze dias para chegar lá, mesmo navegando com o vento a favor!","Capitão "+GetFullName(pchar)+", sua irresponsabilidade me surpreende! Por que não me contou sobre isso antes?");
				link.l1 = "Bem, eu nem sei o que dizer...";
				link.l1.go = "ShipWreck2";
			}
			else
			{
				dialog.text = "Isto é uma ótima notícia! Já tínhamos perdido a esperança de ver "+pchar.GenQuest.ShipWreck.Name+"  vivo novamente. Vou enviar uma equipe de resgate imediatamente. Ah, e por favor, aceite esta recompensa pela sua eficiência e participação no resgate deles.";
				link.l1 = "Obrigado, Vossa Graça. Fico feliz por ter podido ajudar. Tenho certeza de que a expedição chegará a tempo.";
				link.l1.go = "ShipWreck3";	
			}
			pchar.GenQuest.ShipWreck.SpeakMayor = true;
			pchar.quest.ShipWreck_MeetInShore.over = "yes";
			pchar.quest.ShipWreck_SaveSailors.over = "yes"; // belamour gen таймер на 30 дней тоже нужно снять
		break;
		
		case "ShipWreck2":
			dialog.text = "Que surpresa... O que posso dizer? Vai estudar a Lei do Mar, garoto! Enfim, farei o possível para salvar essas pessoas.";
			link.l1 = "Vossa Graça, mas eu os deixei com provisões suficientes. O senhor tem tempo, garanto...";
			link.l1.go = "ShipWreck4";
		break;
		
		case "ShipWreck3":
			addMoneyToCharacter(pchar, sti(pchar.rank) * 300 + 3000 + rand(3000));
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			AddQuestRecord("ShipWrecked", "14");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString("Colony" + NPChar.city + "Gen")); // belamour gen просто NPChar.city ничего не даст
			AddQuestUserData("ShipWrecked", "ShoreName", XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Gen")); // belamour gen
			CloseQuestHeader("ShipWrecked");
			DeleteAttribute(pchar, "GenQuest.ShipWreck.SpeakMayor");		
			DialogExit();
			AddDialogExitQuest("ShipWreck_RemoveSailorsFromShore");
		break;		
		
		case "ShipWreck4":
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			AddQuestRecord("ShipWrecked", "13");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString("Colony" + NPChar.city + "Gen")); // belamour gen просто NPChar.city ничего не даст
			AddQuestUserData("ShipWrecked", "ShoreName", XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Gen")); // belamour gen
			CloseQuestHeader("ShipWrecked");
			DeleteAttribute(pchar, "GenQuest.ShipWreck.SpeakMayor");		
			DialogExit();
			AddDialogExitQuest("ShipWreck_RemoveSailorsFromShore");
		break;
		// -------------------------- Генератор "Кораблекрушенцы" ------------
		
		// ---------------------- найти кольцо в борделе ----------------------------
		case "TakeRing_1":
			dialog.text = "Estou ciente de que você, como posso dizer... "+GetSexPhrase("frequenta bordéis","gosto de visitar bordéis de vez em quando")+". E então decidi recorrer a você para pedir ajuda\n"+"Sabe, tenho vergonha de admitir, mas estive lá recentemente...";
			link.l1 = "E o que tem de errado nisso? Sexo é algo perfeitamente natural, sabia...";
			link.l1.go = "TakeRing_2";
		break;
		case "TakeRing_2":
			dialog.text = "Ah, não, não estou pregando, não. É que, certa vez, bebi demais e acabei perdendo minha aliança de casamento...";
			link.l1 = "Isso é um problema. Me desculpe.";
			link.l1.go = "TakeRing_3";
		break;
		case "TakeRing_3":
			dialog.text = "Eu não preciso que ninguém sinta pena de mim. Eu preciso do meu anel de volta. Se conseguir recuperá-lo antes da meia-noite, serei muito generoso. Se falhar, minha esposa vai me matar.";
			link.l1 = "Entendo... E onde exatamente você perdeu isso? Lembra de algum detalhe em especial?";
			link.l1.go = "TakeRing_4";
		break;
		case "TakeRing_4":
			dialog.text = "Infelizmente, não. Nada de novo.";
			link.l1 = "Entendi. Então, vamos procurar, certo?";
			link.l1.go = "TakeRing_5";
			link.l2 = "Sabe, "+GetAddress_FormToNPC(NPChar)+", acho que vou deixar passar essa. Por favor, me desculpe...";
			link.l2.go = "TakeRing_6";
		break;	
		case "TakeRing_5":
			dialog.text = "Excelente! Mas lembre-se – você precisa encontrá-lo antes da meia-noite.";
			link.l1 = "Eu me lembro. Voltarei em breve.";
			link.l1.go = "exit";
			pchar.questTemp.different = "TakeMayorsRing";
			pchar.questTemp.different.TakeMayorsRing = "toBrothel";
			pchar.questTemp.different.TakeMayorsRing.Id = GetFullName(npchar);
			pchar.questTemp.different.TakeMayorsRing.city = npchar.city;	
			pchar.questTemp.different.TakeMayorsRing.price = sti(pchar.rank)*100+1000;
			sld = ItemsFromID("MayorsRing");
			sld.CityName = XI_ConvertString("Colony" + npchar.city + "Gen");
			//ложим кольцо в итем
			if (rand(3) != 2)
			{				
				switch (rand(2))
				{
					case 0: sTemp = "_Brothel_room";  break;
					case 1: sTemp = "_Brothel";  break;
					case 2: sTemp = "_SecBrRoom";  break;
				}
				sld.shown = true;
				sld.startLocation = pchar.questTemp.different.TakeMayorsRing.city + sTemp;
				sld.startLocator = "item" + (rand(4)+1);
				pchar.questTemp.different.TakeMayorsRing.item = true; //флаг кольцо валяется в итемах
				Log_QuestInfo("The ring is at " + sld.startLocation + ", in locator " + sld.startLocator);
			}
			SetTimerFunction("TakeMayorsRing_null", 0, 0, 1); //освобождаем разрешалку на миниквесты 
			ReOpenQuestHeader("SeekMayorsRing");
			AddQuestRecord("SeekMayorsRing", "1");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("SeekMayorsRing", "sName", pchar.questTemp.different.TakeMayorsRing.Id);
		break;	
		case "TakeRing_6":
			dialog.text = "Oh? Bem, isso foi realmente inesperado... Então, boa sorte pra você, capitão.";
			link.l1 = "Adeus.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
		break;

		case "TakeRing_S1":
			dialog.text = "É o meu anel! Você salvou a minha vida!";
			link.l1 = "Não é nada, senhor.";
			link.l1.go = "TakeRing_S2";
			TakeItemFromCharacter(pchar, "MayorsRing");
		break;
		case "TakeRing_S2":
			dialog.text = "Aqui está o seu pagamento pelo excelente trabalho! Sou muito grato a você!";
			link.l1 = "Fico feliz em ajudar, senhor. Por favor, seja mais cuidadoso da próxima vez.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.different.TakeMayorsRing.price));
			pchar.questTemp.different = "free";
			pchar.quest.TakeMayorsRing_null.over = "yes"; //снимаем таймер
			AddQuestRecord("SeekMayorsRing", "7");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			CloseQuestHeader("SeekMayorsRing");
			DeleteAttribute(pchar, "questTemp.different.TakeMayorsRing");
		break;
		case "TakeRing_S3":
			dialog.text = "Senhor, tenha piedade! Eu realmente devia parar de beber tanto...";
			link.l1 = "Com certeza! Aqui está o seu anel.";
			link.l1.go = "TakeRing_S4";
		break;
		case "TakeRing_S4":
			dialog.text = "Sim, sim, muito obrigado. Estou em dívida com você! Aqui está o seu pagamento por um trabalho bem feito!";
			link.l1 = "Obrigado "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "exit";
			TakeItemFromCharacter(pchar, "MayorsRing");
			ChangeCharacterComplexReputation(pchar,"nobility", 3);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 3);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.different.TakeMayorsRing.price));
			pchar.questTemp.different = "free";
			pchar.quest.TakeMayorsRing_null.over = "yes"; //снимаем таймер
			AddQuestRecord("SeekMayorsRing", "7");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			CloseQuestHeader("SeekMayorsRing");
			DeleteAttribute(pchar, "questTemp.different.TakeMayorsRing");
		break;
		// ---------------------- найти кольцо в борделе ----------------------------

		case "node_1":
            //ОСАДЫ homo
			if (CheckAttribute(&Colonies[FindColony(npchar.City)],"Siege"))
            {

                makearef(aData, NullCharacter.Siege);
                

                if (CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                {
                    dialog.text = "Já discutimos tudo, não foi?";
                    link.l1 = "Certo. Não vou mais tomar o seu tempo.";
                    link.l1.go = "exit";

                }
                else
                {
                    dialog.text = "Me desculpe por incomodá-lo, mas não tenho tempo para conversar com você agora. Como você deve saber, nossa colônia foi atacada por "+NationNamePeople(sti(aData.nation))+". Preciso cuidar das nossas defesas.";
                    link.l1 = "Bem, só queria oferecer minha ajuda na defesa do forte.";
                    link.l1.go = "siege_task";
                    link.l2 = "Então não vou mais tomar seu tempo.";
        			link.l2.go = "exit";
                }
            }
            else
            {//->
                makearef(aData, NullCharacter.Siege);
                if (CheckAttribute(aData, "PlayerHelpMayor") && sti(aData.PlayerHelpMayor) == true
                && CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                {
                    AddMoneyToCharacter(Pchar,(sti(aData.iSquadronPower)*1500));
                    ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                    ChangeCharacterComplexReputation(pchar,"nobility", 10);
                    AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 180);
                    AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 200);
                    AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 200);
                    AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 200);
                    //--> слухи
                    SiegeRumour("They say that you had helped us to repel the "+NationNameSK(sti(aData.nation))+" squadron and defend our colony! We are grateful to you, "+ GetAddress_Form(NPChar)+".", aData.Colony, sti(aData.conation), -1, 15, 3);
		            //<-- слухи
                    DeleteAttribute(aData, "PlayerHelpMayor");
                    DeleteAttribute(aData, "HelpColony");
                    dialog.text = "Ah, é você, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+", fico feliz em vê-lo. Boas notícias – conseguimos repelir o "+NationNameSK(sti(aData.nation))+" invasores. Você também teve seu papel nisso, e aqui está sua recompensa - "+(sti(aData.iSquadronPower)*1500)+" peças de oito. Aqui está.";
                    link.l1 = "Obrigado, "+GetAddress_FormToNPC(NPChar)+", foi um prazer fazer negócios com você!";
                    link.l1.go = "exit";
                }
                else
                {
                    if (CheckAttribute(aData, "PlayerHelpMayor")) DeleteAttribute(aData, "PlayerHelpMayor");
                    dialog.text = "O que te traz aqui para me distrair de assuntos importantes do Estado?";
					if (npchar.city != "Panama") // Addon-2016 Jason
					{
						link.l1 = "Eu queria trabalhar para "+NationNameGenitive(sti(NPChar.nation))+".";
						link.l1.go = "work";
					}
					// Warship Генер "Пираты на необитайке" - сдаём пиратов властям
					if(CheckAttribute(PChar, "Quest.PiratesOnUninhabited_OnShore") || CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
					{
						link.l11 = XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore+"Dat")+" Encontrei alguns piratas. Todos "+PChar.GenQuest.PiratesOnUninhabited.PiratesCount+" estão a bordo neste momento. Quero entregá-los às autoridades.";
						link.l11.go = "PiratesOnUninhabited_1";
					}
					
        			link.l2 = "Queria falar com você sobre um assunto importante.";
					if(CheckAttribute(pchar,"questTemp.ReasonToFast") && !CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
					{
						link.l2.go = "ReasonToFast_Mayor1";
					}
					else
					{					
						link.l2.go = "quests";
					}	
					if(CheckAttribute(pchar,"GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
					{
						if(pchar.GenQuest.CaptainComission == "Begin_1" && !CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor")) 
						{
							link.l12 = "Há um capitão no comando da patrulha "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" named "+pchar.GenQuest.CaptainComission.Name+", como posso encontrá-lo?";
							link.l12.go = "CapComission_Mayor1";
						}	
						if(CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
						{
							link.l12 = "Ex-capitão no comando da patrulha "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" concordou em revelar seu esconderijo às autoridades.";
							link.l12.go = "CapComission_Mayor9";
						}
						if(pchar.GenQuest.CaptainComission == "GetGoodsSuccess")
						{
							link.l12 = "Ex-capitão no comando da patrulha  "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" revelou seu esconderijo para mim.";
							link.l12.go = "CapComission_Mayor13";
						}
					}
					if(CheckAttribute(pchar,"GenQuest.ShipWreck") && pchar.GenQuest.ShipWreck == "SailorsOnShore" && GetQuestPastDayParam("GenQuest.ShipWreck") < 25 && sti(npchar.nation) == sti(pchar.GenQuest.ShipWreck.Nation))
					{
						if(!CheckAttribute(pchar,"GenQuest.ShipWreck.SpeakMayor"))
						{
							iDay = GetQuestPastDayParam("GenQuest.ShipWreck");
							if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
							{
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Dat"))+" Conheci um capitão "+pchar.GenQuest.ShipWreck.Name+" e seus marinheiros que foram deixados em terra pelos piratas "+pchar.GenQuest.ShipWreck.BadName+". "+"Infelizmente, eu já tinha muitos homens no meu navio e por isso não pude levá-los a bordo. Mas deixei comida e armas para eles. Se o navio de resgate não os buscar dentro de "+(30 - iDay)+" dias, então não sei se ainda vou encontrá-los vivos ou não.";
								link.l13.go = "ShipWreck1";
							}
							else
							{
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Dat"))+" Encontrei marinheiros de um navio naufragado '"+pchar.GenQuest.ShipWreck.ShipTypeName+" ' com o capitão deles. "+"Infelizmente, eu já tinha homens demais no meu navio e, por isso, não pude levá-los a bordo. Mas deixei comida e armas para eles. Se o navio de resgate não os buscar dentro de "+(30 - iDay)+" dias, então não sei se ainda vou encontrá-los vivos ou não.";
								link.l13.go = "ShipWreck1";							
							}	
						}	
					}					
					//--> Jason, генер почтового курьера 2 уровня
						if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
						{
							if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
							{
							link.l14 = "Tenho uma mensagem da cidade de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
							link.l14.go = "Postcureer_LevelUp_ForAll";
							}
						}
					//<-- генер почтового курьера 2 уровня
					
					// --> Warship, 16.05.11. Квест "Правосудие на продажу".
					if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
					{
						link.l15 = "Milorde, descobri uma quadrilha de contrabandistas cujo chefe foi recentemente capturado pelos guardas. Agora eles estão planejando resgatá-lo. O navio deles '"+PChar.GenQuest.JusticeOnSale.ShipName+"' está atracado em "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Gen")+".";
						link.l15.go = "JusticeOnSale_1";
					}
					//<-- Правосудие на продажу
					
        			if (GetPrisonerQty() > 0)
        			{
                        link.l3 = "Preciso entregar o capitão capturado às autoridades.";
        			    link.l3.go = "sell_prisoner";
        			}
					//Jason --> Регата
					if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
					{
						link.l4 = "Estou aqui para a regata. Aqui está meu convite.";
						link.l4.go = "Regata";
					}
        			link.l5 = "Talvez você queira fazer uma pausa?";
        			link.l5.go = "Play_Game";
        			link.l10 = "Foi apenas uma visita de cortesia, "+GetAddress_FormToNPC(NPChar)+".";
        			link.l10.go = "node_2";
                }
    		}//<-
		break;
		
		case "Helen_node_1":
            //ОСАДЫ homo
			if (CheckAttribute(&Colonies[FindColony(npchar.City)],"Siege"))
            {

                makearef(aData, NullCharacter.Siege);
                

                if (CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                {
                    dialog.text = "Já discutimos tudo, não foi?";
                    link.l1 = "Certo. Não vou mais tomar o seu tempo.";
                    link.l1.go = "exit";

                }
                else
                {
                    dialog.text = "Me desculpe por te incomodar, mas não tenho tempo para conversar com você agora. Como deve saber, nossa colônia foi atacada por "+NationNamePeople(sti(aData.nation))+". Preciso cuidar das nossas defesas.";
                    link.l1 = "Bem, eu só queria oferecer minha ajuda na defesa do forte.";
                    link.l1.go = "siege_task";
                    link.l2 = "Então não vou mais tomar seu tempo.";
        			link.l2.go = "exit";
                }
            }
            else
            {//->
                makearef(aData, NullCharacter.Siege);
                if (CheckAttribute(aData, "PlayerHelpMayor") && sti(aData.PlayerHelpMayor) == true
                && CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                {
                    AddMoneyToCharacter(Pchar,(sti(aData.iSquadronPower)*1500));
                    ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                    ChangeCharacterComplexReputation(pchar,"nobility", 10);
                    AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 180);
                    AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 200);
                    AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 200);
                    AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 200);
                    //--> слухи
                    SiegeRumour("They say that you had helped us to repel the "+NationNameSK(sti(aData.nation))+" squadron and defend our colony! We are grateful to you, "+ GetAddress_Form(NPChar)+".", aData.Colony, sti(aData.conation), -1, 15, 3);
		            //<-- слухи
                    DeleteAttribute(aData, "PlayerHelpMayor");
                    DeleteAttribute(aData, "HelpColony");
                    dialog.text = "Ah, é você, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+", fico feliz em vê-lo. Boas notícias – conseguimos repelir o "+NationNameSK(sti(aData.nation))+" invasores. Você também teve sua participação nisso, e aqui está sua recompensa - "+(sti(aData.iSquadronPower)*1500)+" peças de oito. Aqui está.";
                    link.l1 = "Obrigado, "+GetAddress_FormToNPC(NPChar)+", foi um prazer fazer negócios com você!";
                    link.l1.go = "exit";
                }
                else
                {
                    if (CheckAttribute(aData, "PlayerHelpMayor")) DeleteAttribute(aData, "PlayerHelpMayor");
                    dialog.text = "O que te traz até mim? Achei que resolvia todos os seus assuntos com o seu... patrono. Mas fale, sempre fico contente em te ouvir.";
					if (npchar.city != "Panama") // Addon-2016 Jason
					{
						link.l1 = "Eu queria trabalhar para "+NationNameGenitive(sti(NPChar.nation))+".";
						link.l1.go = "work";
					}
					// Warship Генер "Пираты на необитайке" - сдаём пиратов властям
					if(CheckAttribute(PChar, "Quest.PiratesOnUninhabited_OnShore") || CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
					{
						link.l11 = XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore+"Dat")+" Encontrei alguns piratas. Todos "+PChar.GenQuest.PiratesOnUninhabited.PiratesCount+" estão a bordo neste momento. Quero entregá-los às autoridades.";
						link.l11.go = "PiratesOnUninhabited_1";
					}
					
        			link.l2 = "Queria falar com você sobre um assunto importante.";
					if(CheckAttribute(pchar,"questTemp.ReasonToFast") && !CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
					{
						link.l2.go = "ReasonToFast_Mayor1";
					}
					else
					{					
						link.l2.go = "quests";
					}	
					if(CheckAttribute(pchar,"GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
					{
						if(pchar.GenQuest.CaptainComission == "Begin_1" && !CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor")) 
						{
							link.l12 = "Há um capitão no comando da patrulha "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" named "+pchar.GenQuest.CaptainComission.Name+", como posso encontrá-lo?";
							link.l12.go = "CapComission_Mayor1";
						}	
						if(CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
						{
							link.l12 = "Ex-capitão no comando da patrulha "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" concordou em revelar seu esconderijo às autoridades.";
							link.l12.go = "CapComission_Mayor9";
						}
						if(pchar.GenQuest.CaptainComission == "GetGoodsSuccess")
						{
							link.l12 = "Ex-capitão no comando da patrulha  "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" revelou seu esconderijo para mim.";
							link.l12.go = "CapComission_Mayor13";
						}
					}
					if(CheckAttribute(pchar,"GenQuest.ShipWreck") && pchar.GenQuest.ShipWreck == "SailorsOnShore" && GetQuestPastDayParam("GenQuest.ShipWreck") < 25 && sti(npchar.nation) == sti(pchar.GenQuest.ShipWreck.Nation))
					{
						if(!CheckAttribute(pchar,"GenQuest.ShipWreck.SpeakMayor"))
						{
							iDay = GetQuestPastDayParam("GenQuest.ShipWreck");
							if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
							{
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Dat"))+" Encontrei um capitão "+pchar.GenQuest.ShipWreck.Name+" e seus marinheiros que foram deixados em terra por piratas "+pchar.GenQuest.ShipWreck.BadName+". "+"Infelizmente, eu já tinha homens demais no meu navio e por isso não pude levá-los a bordo. Mas deixei comida e armas para eles. Se o navio de resgate não os buscar dentro de "+(30 - iDay)+" dias, então não sei se ainda vou encontrá-los vivos ou não.";
								link.l13.go = "ShipWreck1";
							}
							else
							{
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Dat"))+" Encontrei marinheiros de um navio naufragado '"+pchar.GenQuest.ShipWreck.ShipTypeName+" ' com o capitão deles. "+"Infelizmente, eu já tinha muitos homens no meu navio e por isso não pude levá-los a bordo. Mas deixei comida e armas para eles. Se o navio de resgate não vier buscá-los dentro de "+(30 - iDay)+" dias, então não sei se ainda vou encontrá-los vivos ou não.";
								link.l13.go = "ShipWreck1";							
							}	
						}	
					}					
					//--> Jason, генер почтового курьера 2 уровня
						if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
						{
							if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
							{
							link.l14 = "Tenho uma mensagem da cidade de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
							link.l14.go = "Postcureer_LevelUp_ForAll";
							}
						}
					//<-- генер почтового курьера 2 уровня
					
					// --> Warship, 16.05.11. Квест "Правосудие на продажу".
					if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
					{
						link.l15 = "Milorde, localizei uma quadrilha de contrabandistas cujo chefe foi recentemente capturado pelos guardas. Agora eles estão tramando sua fuga. O navio deles '"+PChar.GenQuest.JusticeOnSale.ShipName+"' está atracado em "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Gen")+".";
						link.l15.go = "JusticeOnSale_1";
					}
					//<-- Правосудие на продажу
					
        			if (GetPrisonerQty() > 0)
        			{
                        link.l3 = "Preciso entregar o capitão capturado às autoridades.";
        			    link.l3.go = "sell_prisoner";
        			}
					//Jason --> Регата
					if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
					{
						link.l4 = "Estou aqui para a regata. Aqui está meu convite.";
						link.l4.go = "Regata";
					}
        			link.l5 = "Talvez você queira fazer uma pausa?";
        			link.l5.go = "Play_Game";
        			link.l10 = "Foi só uma visita de cortesia, "+GetAddress_FormToNPC(NPChar)+".";
        			link.l10.go = "node_2";
                }
    		}//<-
		break;
		
		case "Play_Game":
			//==> прибыла инспекция на Святом Милосердии
			if (CheckAttribute(npchar, "quest.SantaMisericordia"))
			{
    			dialog.text = "Agora não! Temos uma inspeção, don de Alamida está na cidade. Ah, todo ano é a mesma coisa, o que foi que eu fiz pra merecer isso...";
				link.l1 = "Como quiser. Não vou te atrapalhar.";
				link.l1.go = "exit"; 
				break;
			}
			//<== прибыла инспекция на Святом Милосердии
			dialog.text = "Hmm, e que tipo de jogos você prefere?";
			link.l1 = "Quer jogar uma partida de cartas valendo uma boa grana?";
			link.l1.go = "Card_Game";
   			link.l2 = "Que tal jogar uns dados no poker-joker?";
			link.l2.go = "Dice_Game";
			link.l10 = "Com licença, mas o dever me chama.";
			link.l10.go = "exit";
		break;
		
		//  карты -->
        case "Card_Game":
            if (!CheckNPCQuestDate(npchar, "Card_date_Yet") || sti(PChar.rank) < 4 || isBadReputation(pchar, 50) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(5))
            {
                SetNPCQuestDate(npchar, "Card_date_Yet");
				// belamour legendary edition фикс проверки мундира с мушкетом
				if(IsUniformEquip()) dialog.text = "Me perdoe, monsenhor, mas não tenho tempo para isso agora. Talvez numa próxima vez."; // Jason НСО
                else dialog.text = "Eu não aposto com piratas!";
    			link.l1 = "Como quiser.";
    			link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Card_date_begin"))
				{
					dialog.text = "Por que não! Relaxar faz bem para o coração, mas não para a bolsa...";
	    			link.l1 = "Excelente.";
	    			link.l1.go = "Cards_begin";
	    			link.l2 = "Quais são as regras do nosso jogo?";
	    			link.l2.go = "Cards_Rule";
    			}
    			else
    			{
					dialog.text = "Não, por hoje chega. Tenho coisas para fazer.";
	    			link.l1 = "Como quiser.";
	    			link.l1.go = "exit";
				}
			}
		break;

		case "Cards_Rule":
   			dialog.text = CARDS_RULE;
			link.l1 = "Bem, então vamos começar!";
			link.l1.go = "Cards_begin";
			link.l3 = "Não, não é para mim...";
			link.l3.go = "exit";
		break;

		case "Cards_begin":
			dialog.text = "Vamos acertar a aposta primeiro.";
			link.l1 = "Vamos jogar por 1.000 peças de oito.";
			link.l1.go = "Cards_Node_100";
			link.l2 = "Vamos jogar por 5.000 peças de oito.";
			link.l2.go = "Cards_Node_500";
			link.l3 = "Acho que não tenho escolha, preciso ir.";
			link.l3.go = "exit";
		break;

		case "Cards_Node_100":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckCardsGameSmallRate() && !bOk)
		    {
                dialog.text = "Você é um trapaceiro notório. Não vou jogar com você.";
                link.l1 = "É tudo mentira!";
			    link.l1.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 3000)
		    {
                dialog.text = "Você está brincando, "+GetAddress_Form(NPChar)+"? Você não tem dinheiro!";
                link.l1 = "Acontece.";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 3000)
		    {
                dialog.text = "É isso! Chega de cartas—antes que me chamem de perdulário e me obriguem a deixar meu posto.";
                link.l1 = "Pena.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Certo, vamos jogar por 1.000 peças de oito.";
			link.l1 = "Vamos começar!";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 1000;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_Node_500":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckCardsGameSmallRate() && !bOk)
		    {
                dialog.text = "Você é um trapaceiro notório. Não vou jogar com você.";
                link.l1 = "É tudo mentira! Bom, tanto faz.";
			    link.l1.go = "exit";
			    break;
		    }
			if (!CheckCardsGameBigRate())
		    {
                dialog.text = "Dizem que você é um jogador muito habilidoso. Não vou apostar alto com você.";
                link.l1 = "Talvez devêssemos baixar a aposta?";
			    link.l1.go = "Cards_Node_100";
				link.l2 = "Me desculpe, mas eu preciso ir.";
			    link.l2.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 15000)
		    {
                dialog.text = "Você está brincando, "+GetAddress_Form(npchar)+"? Você não tem 15.000 peças de oito!";
                link.l1 = "Eu vou levantá-los!";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 15000)
		    {
                dialog.text = "Não, essas apostas vão esvaziar o tesouro da cidade.";
                link.l1 = "Como desejar.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Certo, vamos jogar por 5.000 peças de oito.";
			link.l1 = "Vamos começar!";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 5000;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_begin_go":
            SetNPCQuestDate(npchar, "Card_date_begin");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
            LaunchCardsGame();
		break;
	    // карты <--

	    //  Dice -->
        case "Dice_Game":
            if (!CheckNPCQuestDate(npchar, "Dice_date_Yet") || sti(PChar.rank) < 4 || isBadReputation(pchar, 50) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(5))
            {
                SetNPCQuestDate(npchar, "Dice_date_Yet");
				// belamour legendary edition фикс проверки мундира с мушкетом
				if(IsUniformEquip()) dialog.text = "Me perdoe, monsenhor, mas não tenho tempo para isso agora. Talvez numa próxima vez."; // Jason НСО
                else dialog.text = "Eu não vou apostar com piratas!";
    			link.l1 = "Como quiser.";
    			link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
				{
					dialog.text = "Por que não! Relaxar faz bem para o coração... mas não para a bolsa...";
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
			link.l3 = "Não, não é para mim...";
			link.l3.go = "exit";
		break;

		case "Dice_begin":
			dialog.text = "Vamos acertar a aposta primeiro.";
			link.l1 = "Vamos jogar por 500 peças de oito por dado.";
			link.l1.go = "Dice_Node_100";
			link.l2 = "Vamos jogar por 2.000 peças de oito por dado.";
			link.l2.go = "Dice_Node_500";
			link.l3 = "Acho que não tenho escolha, preciso ir.";
			link.l3.go = "exit";
		break;

		case "Dice_Node_100":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckDiceGameSmallRate() && !bOk)
		    {
                dialog.text = "Você é um trapaceiro notório. Não vou apostar com você.";
                link.l1 = "É tudo mentira! Bem, tanto faz.";
			    link.l1.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 3000)
		    {
                dialog.text = "Você está brincando, "+GetAddress_Form(NPChar)+"? Você não tem dinheiro!";
                link.l1 = "Acontece.";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 3000)
		    {
                dialog.text = "Chega! Estou farto de jogos de azar – antes que me chamem de perdulário e me obriguem a deixar meu cargo...";
                link.l1 = "Pena.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Certo, vamos jogar por 500 peças de oito.";
			link.l1 = "Vamos começar!";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 500;
            pchar.GenQuest.Dice.SitType   = false;
		break;

		case "Dice_Node_500":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckDiceGameSmallRate() && !bOk)
		    {
                dialog.text = "Você é um trapaceiro notório. Não vou jogar com você.";
                link.l1 = "É tudo mentira! Bom, tanto faz.";
			    link.l1.go = "exit";
			    break;
		    }
			if (!CheckDiceGameBigRate())
		    {
                dialog.text = "Dizem que você é um jogador muito habilidoso. Não vou apostar alto com você.";
                link.l1 = "Talvez devêssemos baixar a aposta?";
			    link.l1.go = "Dice_Node_100";
				link.l2 = "Me desculpe, mas eu preciso ir.";
			    link.l2.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 15000)
		    {
                dialog.text = "Está brincando, "+GetAddress_Form(NPChar)+"? Você não tem 15.000 peças de oito!";
                link.l1 = "Eu vou aumentá-los!";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 15000)
		    {
                dialog.text = "Não, essas apostas certamente vão esvaziar o tesouro da cidade.";
                link.l1 = "Como desejar.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Certo, vamos jogar por 2.000 peças de oito por dado.";
			link.l1 = "Vamos começar!";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 2000;
            pchar.GenQuest.Dice.SitType   = false;
		break;

		case "Dice_begin_go":
            SetNPCQuestDate(npchar, "Dice_date_begin");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
            LaunchDiceGame();
		break;
	    // Dice <--
		case "node_2":
			dialog.text = "Nesse caso, peço que saia do meu escritório e pare de me distrair do meu trabalho";
			link.l1 = "Sim, sim, claro. Desculpe incomodar você.";
			link.l1.go = "exit";
		break;

		//---------------------------- генератор квестов мэра -------------------------------
		case "work": 
            dialog.text = "Isto é um erro. Avise os desenvolvedores sobre isso.";
        	link.l1 = "Obrigado, este é um jogo incrível!";
        	link.l1.go = "exit";
			
			//==> прибыла инспекция на Святом Милосердии
			if (CheckAttribute(npchar, "quest.SantaMisericordia"))
			{
    			dialog.text = "Agora não! Estamos tendo uma inspeção, don de Alamida está na cidade. Ah, todo ano é a mesma coisa, o que foi que eu fiz pra merecer isso...";
				link.l1 = "Como quiser. Não vou te atrapalhar.";
				link.l1.go = "exit"; 
				break;
			}
			//<== прибыла инспекция на Святом Милосердии
			//==> взят ли какой-либо квест
			if (CheckAttribute(pchar, "GenQuest.questName"))
			{		 				
				//--> Федот, да не тот
				QuestName = pchar.GenQuest.questName;
				if (pchar.GenQuest.(QuestName).MayorId != npchar.id) 
				{					
					dialog.text = RandPhraseSimple("Pelo que posso ver, você já tem uma missão dada pelo governador de "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.(QuestName).MayorId)].city+"Gen")+". Termine o trabalho que você já tem, e então conversaremos.","Hum, não era você em "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.(QuestName).MayorId)].city+"Voc")+" onde você recebeu ordens do governador local? Sim, está certo. Termine essa missão primeiro.");
					link.l1 = RandPhraseSimple("Entendi...","Entendido..."+GetSexPhrase("","")+", "+GetAddress_FormToNPC(NPChar)+".");
					link.l1.go = "exit";					
					break;
				}
				//<--Федот, да не тот
				//-------- взят квест уничтожения банды ---------->>
				if (QuestName == "DestroyGang")
				{
					switch (pchar.GenQuest.DestroyGang)
					{
						makearef(arName, pchar.GenQuest.DestroyGang);
						case "":
							dialog.text = LinkRandPhrase("Uma missão para localizar o bandido "+GetFullName(arName)+" já foi emitida para você. Agora cumpra-a!","Você já tem uma missão para localizar um bandido chamado "+GetFullName(arName)+". Estou esperando pelos resultados!","Enquanto você desperdiça seu tempo na minha residência, "+GetFullName(arName)+" está roubando nossos colonos! Mãos à obra!");
							link.l1 = RandPhraseSimple("Certo, "+GetAddress_FormToNPC(NPChar)+".","Estou ocupado com isso, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("O tempo que lhe foi dado para localizar e eliminar aquele bandido acabou. E que tipo de relatórios você acha que estou recebendo? Eu lhe digo - "+GetFullName(arName)+" ainda está vivo e firme! Agora se explique, "+GetAddress_Form(NPChar)+".","O tempo que lhe foi dado para eliminar aquele canalha chamado "+GetFullName(arName)+", acabou. Mesmo assim, estou sendo informado de que nenhum progresso foi feito. O que está acontecendo?");
							link.l1 = "Não consegui cumprir sua tarefa dentro do prazo estabelecido, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("E então, o que me diz? Conseguiu eliminar o bandido de que falei? "+GetFullName(arName)+" finalmente morreu?","Me diga só uma coisa - é "+GetFullName(arName)+" Vivo ou morto? ");
							link.l1 = "Infelizmente, ainda estou vivo, "+GetAddress_FormToNPC(NPChar)+". Consegui encontrá-lo, mas ele era mais forte do que eu e precisei recuar. Aquele bandido é um desgraçado difícil de lidar. Me desculpe.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("Então, o que me diz? Conseguiu eliminar o bandido de quem falei? "+GetFullName(arName)+" finalmente morreu?","Me diga só uma coisa - é "+GetFullName(arName)+" morto ou vivo?");
							link.l1 = "Ele está morto, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 180);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
				//-------- контркурьер ---------->>
				if (QuestName == "TakePostcureer")
				{
					switch (pchar.GenQuest.TakePostcureer)
					{
						case "":
							dialog.text = LinkRandPhrase("Uma missão para capturar um navio-correio já foi atribuída a você. Agora, cumpra-a!","Você já tem uma missão para capturar um navio-correio! Estou esperando pelos resultados!","Enquanto você perde seu tempo na minha residência, os documentos de que preciso estão caindo direto nas mãos do nosso inimigo! Vá trabalhar!");
							link.l1 = RandPhraseSimple("Certo, "+GetAddress_FormToNPC(NPChar)+".","Estou ocupado com isso, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("O tempo que lhe foi dado para localizar e capturar aquele navio-correio acabou. E que tipo de relatórios você acha que estou recebendo? Eu lhe digo – os documentos que eu esperava foram parar direto nas mãos do inimigo! Agora, tenha a bondade de se explicar, "+GetAddress_Form(NPChar)+".","Todo o tempo que você tinha para capturar os documentos do navio do mensageiro acabou. Mesmo assim, nenhum progresso foi feito. O que está acontecendo?");
							link.l1 = "Não consegui terminar o trabalho a tempo, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("E então, o que me diz? Conseguiu capturar os documentos?","Me diga só uma coisa - você conseguiu garantir a correspondência?");
							link.l1 = "Infelizmente, não, "+GetAddress_FormToNPC(NPChar)+". Consegui localizar o navio, mas os documentos me escaparam.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("E então, o que me diz? Conseguiu pegar os documentos?","Me diga só uma coisa - você conseguiu garantir a correspondência?");
							link.l1 = "Sim, "+GetAddress_FormToNPC(NPChar)+". Eu tenho eles. Aqui está.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 200);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 150);
							RemoveItems(pchar, "ContraPostLetters", 1);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
				//-------- контрфрахт - арсенал ---------->>
				if (QuestName == "TakeArsenalship")
				{
					switch (pchar.GenQuest.TakeArsenalship)
					{
						case "":
							dialog.text = LinkRandPhrase("Uma missão para destruir um transporte militar já foi atribuída a você. Agora, cumpra-a!","Você já tem uma missão para destruir um transporte militar! Estou aguardando os resultados!","Enquanto você perde seu tempo na minha residência, pólvora e munição estão sendo entregues direto para os canhões inimigos! Mãos à obra!");
							link.l1 = RandPhraseSimple("Certo, "+GetAddress_FormToNPC(NPChar)+".","Estou ocupado com isso, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("O tempo que lhe foi dado para localizar e destruir aquele transporte militar acabou. E que tipo de relatório você acha que estou recebendo? Eu lhe digo - o comboio inimigo chegou ao seu destino sem problemas! Agora, faça o favor de se explicar, "+GetAddress_Form(NPChar)+".","Todo o tempo que você tinha para destruir o transporte militar inimigo acabou. Mesmo assim, nenhum progresso foi feito. O que está acontecendo?");
							link.l1 = "Não consegui executar sua tarefa no tempo estipulado, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("E então, o que me diz? Conseguiu destruir o navio de transporte inimigo?","Me diga só uma coisa - aquela carga inimiga já está descansando no fundo do mar?");
							link.l1 = "Infelizmente, não, "+GetAddress_FormToNPC(NPChar)+". Consegui localizar o comboio, mas não consegui afundar o navio exigido.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("E então, o que me diz? Conseguiu destruir aquele transporte inimigo?","Me diga só uma coisa - o arsenal inimigo já está descansando no fundo do mar?");
							link.l1 = "Sim, "+GetAddress_FormToNPC(NPChar)+". Nosso inimigo não receberá aquela pólvora e munição.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 220);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 150);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
				//-------- ОЗГ - пират ---------->>
				if (QuestName == "TakePirateship")
				{
					switch (pchar.GenQuest.TakePirateship)
					{
						case "":
							dialog.text = LinkRandPhrase("Uma missão para eliminar um pirata já foi atribuída a você. Agora cumpra-a!","Você já tem uma missão para destruir um navio pirata! Estou aguardando os resultados!","Enquanto você perde seu tempo na minha residência, aquele pirata imundo está fazendo outra vítima! Vá trabalhar!");
							link.l1 = RandPhraseSimple("Certo, "+GetAddress_FormToNPC(NPChar)+".","Estou ocupado com isso, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("O tempo que lhe foi dado para localizar e eliminar o pirata acabou. E que tipo de relatórios você acha que estou recebendo? Eu lhe digo – aquele pirata imundo continua atacando nossos navios! Agora, faça o favor de se explicar, "+GetAddress_Form(NPChar)+".","Todo o tempo que lhe foi dado para destruir o navio pirata acabou. Ainda assim, nenhum progresso foi feito. O que está acontecendo?");
							link.l1 = "Não consegui terminar o seu serviço a tempo, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("E então, o que me diz? Conseguiu destruir o navio pirata?","Me diga só uma coisa - aquele pirata imundo finalmente está descansando no fundo do mar?");
							link.l1 = "Infelizmente, não, "+GetAddress_FormToNPC(NPChar)+". Consegui encontrar aquele canalha, mas não consegui afundar o navio dele.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("E então, o que me diz? Conseguiu destruir o navio pirata?","Me diga só uma coisa - aquele pirata imundo finalmente está descansando no fundo do mar?");
							link.l1 = "Sim, "+GetAddress_FormToNPC(NPChar)+". Esse canalha não vai mais incomodar nossos navios mercantes.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 250);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 150);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
					//-------- ОЗГ - пассажир ---------->>
				if (QuestName == "TakePassenger")
				{
					switch (pchar.GenQuest.TakePassenger)
					{
						case "":
							dialog.text = LinkRandPhrase("Uma missão para caçar um criminoso já foi atribuída a você. Agora, cumpra-a!","Você já tem uma missão para capturar um criminoso! Estou aguardando os resultados!","Enquanto você perde seu tempo na minha residência, aquele canalha imundo continua navegando por aí! Prossiga imediatamente com a missão que lhe foi confiada!");
							link.l1 = RandPhraseSimple("Certo, "+GetAddress_FormToNPC(NPChar)+".","Estou ocupado com isso, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("O tempo que lhe foi dado para encontrar esse canalha acabou. E que tipo de relatórios você acha que estou recebendo? Eu lhe digo - ele chegou ao destino em segurança e depois sumiu no ar! Agora, trate de se explicar, "+GetAddress_Form(NPChar)+".","Todo o tempo que lhe foi dado para encontrar o criminoso acabou. Ainda assim, nenhum progresso foi feito. O que está acontecendo?");
							link.l1 = "Não consegui cumprir sua tarefa no tempo estipulado, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("E então, o que me diz? Conseguiu pegar o bandido?","Me diga só uma coisa – aquele canalha imundo está mesmo no seu porão, amordaçado e algemado?");
							link.l1 = "Infelizmente, não, "+GetAddress_FormToNPC(NPChar)+". Eu falhei em capturar o vilão. Ele afundou junto com o navio em que estava.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("E então, o que me diz? Conseguiu pegar o bandido?","Me diga só uma coisa – aquele canalha imundo está no seu porão, amordaçado e algemado?");
							link.l1 = "Sim, "+GetAddress_FormToNPC(NPChar)+". Por favor, envie seus soldados até o cais, e eu o entregarei a você.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 250);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 200);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
							sld = &Characters[sti(Pchar.GenQuest.TakePassenger.PrisonerIDX)];
							ReleasePrisoner(sld); //освободили пленника
							sld.lifeday = 0;
						break;
					}
				}
				//-------- таможенный патруль ---------->>
				if (QuestName == "CustomPatrol")
				{
					switch (pchar.GenQuest.CustomPatrol)
					{
						case "":
							dialog.text = LinkRandPhrase("Uma missão para encontrar os contrabandistas já foi atribuída a você. Agora, cumpra-a!","Você já tem uma missão para encontrar os contrabandistas! Estou aguardando os resultados!","Enquanto você perde seu tempo na minha residência, aqueles contrabandistas estão se preparando para fechar outro acordo! Prossiga imediatamente com a missão que lhe foi confiada!");
							link.l1 = RandPhraseSimple("Certo, "+GetAddress_FormToNPC(NPChar)+".","Estou ocupado com isso, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("O tempo que lhe foi dado para encontrar os contrabandistas acabou. E que tipo de relatórios você acha que estou recebendo? Eu lhe digo – eles venderam todas as mercadorias sem problemas! Agora, faça o favor de se explicar, "+GetAddress_Form(NPChar)+".","Todo o tempo que você tinha para encontrar os contrabandistas acabou. Mesmo assim, nenhum progresso foi feito. O que está acontecendo?");
							link.l1 = "Não consegui concluir sua tarefa a tempo, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("E então, o que me diz? Já lidou com os contrabandistas?","Me diga só uma coisa – você acabou com o acordo dos contrabandistas?");
							link.l1 = "Infelizmente, não, "+GetAddress_FormToNPC(NPChar)+". Eu falhei em impedir os planos daqueles canalhas.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("E então, o que me diz? Já lidou com os contrabandistas?","Me diga só uma coisa - você estragou o acordo daqueles contrabandistas?");
							link.l1 = "Sim, "+GetAddress_FormToNPC(NPChar)+". Eu alcancei eles e destruí os navios de ambos os lados, tanto do comprador quanto do vendedor.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 200);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 300);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
				//-------- Дезертир ---------->>
				if (QuestName == "FindFugitive")
				{
					switch (pchar.GenQuest.FindFugitive)
					{
						case "":
							dialog.text = LinkRandPhrase("Uma missão para encontrar o desertor já foi atribuída a você. Agora, cumpra-a!","Você já tem uma missão para encontrar o desertor! Estou aguardando os resultados!","Enquanto você perde seu tempo na minha residência, aquele desertor pode estar traindo os segredos do nosso estado! Prossiga imediatamente com a missão que lhe foi confiada!");
							link.l1 = RandPhraseSimple("Certo, "+GetAddress_FormToNPC(NPChar)+".","Estou ocupado com isso, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("O tempo que lhe foi dado para encontrar o desertor acabou. E que tipo de relatório você acha que estou recebendo? Eu lhe digo – nenhum, absolutamente nada! Agora, trate de se explicar, "+GetAddress_Form(NPChar)+".","Todo o tempo que lhe foi dado para encontrar o desertor acabou. Ainda assim, nenhum progresso foi feito. O que está acontecendo?");
							link.l1 = "Não consegui terminar o seu serviço a tempo, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("E então, o que me diz? Conseguiu capturar o desertor?","Me diga só uma coisa – aquele desertor está no seu porão, amordaçado e algemado?");
							link.l1 = "Infelizmente, não, "+GetAddress_FormToNPC(NPChar)+". Eu falhei em capturar aquele canalha. Encontrei o rastro dele no povoado de "+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.City)+", mas justamente no dia anterior à minha chegada ele partiu para o sul em um navio pirata. Suponho que agora esteja com aqueles cavalheiros de fortuna.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("Ah, bem... Aqui está o nosso "+pchar.GenQuest.FindFugitive.Name+"... Ótimo trabalho, capitão! Teve dificuldades na busca?","Oh, que visita ilustre! Olá, "+pchar.GenQuest.FindFugitive.Name+"! Excelente trabalho, capitão! Você se esforçou muito na sua busca?");
							link.l1 = "Como dizer, "+GetAddress_FormToNPC(NPChar)+". Seja o que for, sua missão foi cumprida.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 300);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 200);
							ChangeCharacterComplexReputation(pchar, "authority", 1);
							sld = &Characters[sti(Pchar.GenQuest.FindFugitive.PrisonerIDX)];
							ReleasePrisoner(sld); //освободили пленника
							LAi_SetActorType(sld);
							sld.lifeday = 0;
							pchar.quest.FindFugitive_Over.over = "yes"; //снимаем таймер
							chrDisableReloadToLocation = false;//открыть локацию
						break;
					}
				}
				//------ проникновение во враждебный город ------------>>
				if (QuestName == "Intelligence")
				{
					switch (pchar.GenQuest.Intelligence)
					{
						case "":
							if (GetQuestPastDayParam("GenQuest.Intelligence") > sti(pchar.GenQuest.Intelligence.Terms))
							{
								dialog.text = RandPhraseSimple("O tempo que lhe foi dado para entregar a carta acabou. E pelo visto, você falhou.","O tempo acabou. Ainda assim, nenhum progresso foi feito. O que está acontecendo?");
								link.l1 = "Não consegui concluir o seu serviço, "+GetAddress_FormToNPC(NPChar)+".";
								link.l1.go = "All_Late";	
							}
							else
							{
								dialog.text = LinkRandPhrase("Uma missão para me entregar uma carta já foi atribuída a você. Agora cumpra-a!","Você já tem uma missão para entregar uma carta diretamente a mim! Estou aguardando o resultado, preciso dessa carta o quanto antes!","Enquanto você perde seu tempo na minha residência, a informação de que preciso urgentemente ainda está nas mãos de quem deveria me enviá-la! Vá imediatamente cumprir a missão que lhe foi confiada!");
								link.l1 = RandPhraseSimple("Certo, "+GetAddress_FormToNPC(NPChar)+".","Vou cuidar disso agora mesmo, "+GetAddress_FormToNPC(NPChar)+".");
								link.l1.go = "exit";	
							}
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("Você entregou a carta que eu estava esperando?","Me diga agora – você conseguiu?!");
							link.l1 = "Sim, tenho sim. Como combinamos – entregue a você, pessoalmente.";
							if (GetQuestPastDayParam("GenQuest.Intelligence") > sti(pchar.GenQuest.Intelligence.Terms))
							{
								link.l1.go = "Intelligence_ExecuteLate";
								AddCharacterExpToSkill(PChar, "Sneak", 300);
							}
							else
							{
								link.l1.go = "All_Execute";		
								AddCharacterExpToSkill(PChar, "Leadership", 100);
								AddCharacterExpToSkill(PChar, "Sneak", 300);
							}
							TakeItemFromCharacter(pchar, "sicretLetter");
							DeleteAttribute(ItemsFromID("sicretLetter"), "City");
							DeleteAttribute(ItemsFromID("sicretLetter"), "Mayor");
						break;
					}
				}
				break;
			}
			else
			{
				if(sti(pchar.reputation.nobility) > 41) {dialog.text = "Faço tudo ao meu alcance para combater a desordem nas terras que me foram confiadas, e sempre tenho tarefas para capitães honrados como você. Que tipo de missão você prefere realizar?";}
				else {dialog.text = "Faço todo o possível para manter a ordem nas terras sob minha autoridade, e até mesmo para alguém com sua reputação, Capitão, tenho uma tarefa. Em que tipo de missões gostaria de aplicar seus talentos?";}
				link.l1 = "Quero me concentrar nos assuntos internos da colônia e das áreas ao redor.";
				link.l1.go = "GovQuestGroup1";
				link.l2 = "Prefiro participar de operações realizadas além do seu domínio.";
				link.l2.go = "GovQuestGroup2";
				link.l3 = "Estou interessado em missões de alto risco que possam impactar as relações internacionais e fortalecer a posição de "+NationNameGenitive(sti(NPChar.nation))+".";
				link.l3.go = "GovQuestGroup3";
				link.l4 = "Me desculpe — prefiro não assumir nenhum compromisso no momento.";
				link.l4.go = "exit";
			}
			break;
			
			case "GovQuestGroup1":
			// Группа 1 - Местные
			if (CheckAttribute(npchar, "work_date") && GetNpcQuestPastDayParam(npchar, "work_date") <= 1)
			{
				dialog.text = RandPhraseSimple("Hoje não tenho nenhum trabalho desse tipo para você. Talvez volte amanhã...","Infelizmente, não tenho nenhuma tarefa desse tipo no momento. Tente voltar mais tarde, daqui a um ou dois dias.","Não posso te sobrecarregar com algo assim hoje. Ficarei feliz em te ver outra hora.");
				link.l1 = "Entendi. "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "exit";
				break;
			}
			pchar.GenQuest.Governor.Group1.index = hrand(2);
			i = pchar.GenQuest.Governor.Group1.index;
			switch (i)
			{
				case 0: // Отказ
					dialog.text = RandPhraseSimple("Hoje não tenho nenhum trabalho desse tipo para você. Talvez volte amanhã...","Infelizmente, não tenho nenhum serviço desse tipo no momento. Tente voltar mais tarde, daqui a um ou dois dias.","Não posso te sobrecarregar com algo assim hoje. Ficarei feliz em te ver outra hora.");
					link.l1 = RandPhraseSimple("Pena...","Ah, que pena, "+GetAddress_FormToNPC(NPChar)+". ");
					link.l1.go = "exit";
				break;
						
				case 1: // Таможенный патруль
					if (CheckAttribute(pchar, "GenQuest.Governor.Group1.day") && sti(pchar.GenQuest.Governor.Group1.day) == GetDataDay())
					{
						dialog.text = "Mudou de ideia, Capitão? Os contrabandistas ainda estão à solta e provavelmente não desistiram dos seus planos.";
						link.l1 = "Poderia me lembrar dos detalhes desta missão, Vossa Excelência.";
						link.l1.go = "CustomPatrol";
						link.l2 = RandPhraseSimple("Desculpe, mas não estou pronto para assumir essa tarefa no momento.","Receio que não posso cumprir esta tarefa agora.","Me desculpe — ainda não estou pronto para assumir essa tarefa.");
						link.l2.go = "exit";
						break;
					}
					dialog.text = "Chegou na hora certa, capitão. Preciso lidar com um problema urgente relacionado ao contrabando de mercadorias para nossa colônia. Suponho que seu navio esteja em condições e pronto para a batalha?";
					link.l1 = "Meu navio está sempre em condições e pronto para a batalha. Por favor, conte-me mais sobre a missão que está por vir, excelência.";
					link.l1.go = "CustomPatrol";
				break;
						
				case 2: // Уничтожение банды
					if (CheckAttribute(pchar, "GenQuest.Governor.Group1.day") && sti(pchar.GenQuest.Governor.Group1.day) == GetDataDay())
					{
						dialog.text = "Então você decidiu aceitar a tarefa de eliminar os bandidos, afinal, Capitão? Infelizmente, eles ainda representam uma ameaça ao bem-estar da nossa colônia.";
						link.l1 = "Poderia me lembrar dos detalhes desta tarefa, Vossa Excelência?";
						link.l1.go = "DestroyGang";
						link.l2 = RandPhraseSimple("Desculpe, mas não estou pronto para assumir essa tarefa no momento.","Receio que não posso cumprir esta tarefa agora.","Me desculpe — ainda não estou pronto para assumir essa tarefa.");
						link.l2.go = "exit";
						break;
					}
					pchar.GenQuest.DestroyGang.Terms = hrand(2) + 2;
					pchar.GenQuest.DestroyGang.Money = ((hrand(6)+4)*500)+5000+(sti(pchar.rank)*500);
					makearef(arName, pchar.GenQuest.DestroyGang);
					arName.nation = PIRATE;
					arName.sex = "man";
					SetRandomNameToCharacter(arName);
					dialog.text = "Neste momento, tenho uma missão para você. Na selva perto de "+XI_ConvertString("Colony"+npchar.city+"Gen")+" apareceu uma quadrilha de ladrões, e eu sei que o chefe deles se chama "+GetFullName(arName)+". Localize e elimine essa gangue de bandidos.";
					link.l1 = "Estou de alguma forma limitado nos termos?";
					link.l1.go = "DestroyGang";
				break;
			}
		break;

		case "GovQuestGroup2":
			// Группа 2 - За границами острова, но не государственные
			if (CheckAttribute(npchar, "work_date") && GetNpcQuestPastDayParam(npchar, "work_date") <= 1)
			{
				dialog.text = RandPhraseSimple("Hoje não tenho nenhum trabalho desse tipo para você. Talvez volte amanhã...","Infelizmente, não tenho nenhuma tarefa desse tipo no momento. Tente voltar mais tarde, daqui a um ou dois dias.","Não posso te sobrecarregar com algo assim hoje. Ficarei feliz em te ver outra hora.");
				link.l1 = RandPhraseSimple("Pena...","Ah, que pena, "+GetAddress_FormToNPC(NPChar)+". ");
				link.l1.go = "exit";
				break;
			}
			pchar.GenQuest.Governor.Group2.index = hrand(3);
			i = pchar.GenQuest.Governor.Group2.index;
			switch (i)
			{
				case 0: // Нет заданий
					dialog.text = RandPhraseSimple("Hoje não tenho nenhum trabalho desse tipo para você. Talvez volte amanhã...","Infelizmente, não tenho nenhuma tarefa desse tipo no momento. Tente voltar mais tarde, daqui a um ou dois dias.","Não posso te sobrecarregar com algo assim hoje. Ficarei feliz em te ver outra hora.");
					link.l1 = RandPhraseSimple("Pena...","Ah, que pena, "+GetAddress_FormToNPC(NPChar)+". ");
					link.l1.go = "exit";
				break;
						
				case 1:  // ОЗГ - захватить пассажира
					if (CheckAttribute(pchar, "GenQuest.Governor.Group2.day") && sti(pchar.GenQuest.Governor.Group2.day) == GetDataDay())
					{
						dialog.text = "Decidiu não perder a chance de mostrar do que é capaz? Preciso desse canalha vivo — e o quanto antes.";
						link.l1 = "Poderia me lembrar dos detalhes desta missão, Vossa Excelência?";
						link.l1.go = "TakePassenger";
						link.l2 = RandPhraseSimple("Desculpe, mas não estou pronto para assumir esta tarefa no momento.","Receio que não posso cumprir esta tarefa agora.","Me desculpe — ainda não estou pronto para assumir essa tarefa.");
						link.l2.go = "exit";
						break;
					}
					dialog.text = "Chegou na hora certa, senhor. Tenho uma missão urgente que é perfeita para você. Trata-se de encontrar e capturar uma certa pessoa...";
					link.l1 = "Uma caçada? Pode me explicar com mais detalhes o que esperam de mim?";
					link.l1.go = "TakePassenger";
				break;
						
				case 2: // Найти дезертира
					if (CheckAttribute(pchar, "GenQuest.Governor.Group2.day") && sti(pchar.GenQuest.Governor.Group2.day) == GetDataDay())
					{
						dialog.text = "Mudou de ideia, Capitão? Resolveu ir atrás do fugitivo afinal?";
						link.l1 = "Poderia me lembrar dos detalhes desta missão, Vossa Excelência?";
						link.l1.go = "FindFugitive";
						link.l2 = RandPhraseSimple("Desculpe, mas não estou pronto para assumir essa tarefa no momento.","Receio que não posso cumprir esta tarefa agora.","Me desculpe — ainda não estou pronto para assumir essa tarefa.");
						link.l2.go = "exit";
						break;
					}
					dialog.text = "Tenho uma missão para você que envolve visitar vários assentamentos no Caribe. Está pronto para uma longa jornada?";
					link.l1 = "Sim, meus homens e eu estamos prontos para partir imediatamente. O que exatamente terei que fazer?";
					link.l1.go = "FindFugitive";
				break;
						
				case 3: // Уничтожить корабль пиратов
					if (CheckAttribute(pchar, "GenQuest.Governor.Group2.day") && sti(pchar.GenQuest.Governor.Group2.day) == GetDataDay())
					{
						dialog.text = "O pirata ainda está atacando os mercadores, Capitão. Espero que desta vez esteja pronto para lidar com ele?";
						link.l1 = "Poderia me lembrar dos detalhes desta missão, Vossa Excelência?";
						link.l1.go = "TakePirateship";
						link.l2 = RandPhraseSimple("Desculpe, mas não estou pronto para assumir esta tarefa no momento.","Receio que não posso cumprir esta tarefa agora.","Me desculpe — ainda não estou pronto para assumir essa tarefa.");
						link.l2.go = "exit";
						break;
					}
					dialog.text = "Sim, tenho uma missão importante para você. Para cumpri-la, vai precisar usar todas as suas habilidades. Isso envolve piratas...";
					link.l1 = "Piratas? Então, pode me explicar com mais detalhes o que esperam de mim?";
					link.l1.go = "TakePirateship";
				break;
			}
		break;

		case "GovQuestGroup3":
			// Группа 3 - Государственные разборки, тяжелые бои
			if (CheckAttribute(npchar, "work_date") && GetNpcQuestPastDayParam(npchar, "work_date") <= 1)
			{
				dialog.text = RandPhraseSimple("Hoje não tenho nenhum trabalho desse tipo para você. Talvez volte amanhã...","Infelizmente, não tenho nenhuma tarefa desse tipo no momento. Tente voltar mais tarde, daqui a um ou dois dias.","Não posso te sobrecarregar com algo assim hoje. Ficarei feliz em te ver outra hora.");
				link.l1 = RandPhraseSimple("Pena...","Ah, que pena, "+GetAddress_FormToNPC(NPChar)+". ");
				link.l1.go = "exit";
				break;
			}
			pchar.GenQuest.Governor.Group3.index = hrand(3);
			i = pchar.GenQuest.Governor.Group3.index;
			switch (i)
			{
				case 0: // Отказ
					dialog.text = RandPhraseSimple("Hoje não tenho nenhum trabalho desse tipo para você. Talvez volte amanhã...","Infelizmente, não tenho nenhuma tarefa desse tipo no momento. Tente voltar mais tarde, daqui a um ou dois dias.","Não posso te sobrecarregar com algo assim hoje. Vou ficar feliz em te ver outra hora.");
					link.l1 = RandPhraseSimple("Pena...","Ah, que pena, "+GetAddress_FormToNPC(NPChar)+". ");
					link.l1.go = "exit";
				break;
						
				case 1: // Контркурьер
					if (CheckAttribute(pchar, "GenQuest.Governor.Group3.day") && pchar.GenQuest.Governor.Group3.day == GetDataDay())
					{
						dialog.text = "O tempo está acabando. Vai aceitar, ou veio só conversar de novo?";
						link.l1 = "Poderia me lembrar dos detalhes desta missão, Vossa Excelência.";
						link.l1.go = "TakePostcureer";
						link.l2 = RandPhraseSimple("Desculpe, mas não estou pronto para assumir essa tarefa no momento.","Receio que não posso cumprir esta missão agora.","Me desculpe — ainda não estou pronto para assumir essa tarefa.");
						link.l2.go = "exit";
						break;
					}
					dialog.text = "Sim, tenho uma missão para você. Para cumpri-la, você vai precisar mostrar rapidez e também certa habilidade em combate naval. Está pronto para provar seu valor?";
					link.l1 = "Sua Graça, poderia revelar mais detalhes sobre a missão?";
					link.l1.go = "TakePostcureer";
				break;
						
				case 2: // Контрфрахт - уничтожить корабль с арсеналом
					if (CheckAttribute(pchar, "GenQuest.Governor.Group3.day") && pchar.GenQuest.Governor.Group3.day == GetDataDay())
					{
						dialog.text = "Então, finalmente encontrou sua coragem, Capitão? Pronto para atacar os suprimentos do inimigo?";
						link.l1 = "Poderia me lembrar dos detalhes desta missão, Vossa Excelência?";
						link.l1.go = "TakeArsenalship";
						link.l2 = RandPhraseSimple("Desculpe, mas não estou pronto para assumir essa tarefa no momento.","Receio que não posso cumprir esta tarefa agora.","Me desculpe — ainda não estou pronto para assumir essa tarefa.");
						link.l2.go = "exit";
						break;
					}
					dialog.text = "Sim, tenho uma missão para você. Para cumpri-la, será preciso demonstrar coragem excepcional e também certa habilidade em combate naval. Está pronto para mostrar seu valor?";
					link.l1 = "Vossa Graça, poderia compartilhar mais detalhes sobre a missão que está por vir?";
					link.l1.go = "TakeArsenalship";;
				break;
						
				case 3: // Проникновение во враждебный город
					if (CheckAttribute(pchar, "GenQuest.Governor.Group3.day") && pchar.GenQuest.Governor.Group3.day == GetDataDay())
					{
						dialog.text = "Você já perguntou sobre essa tarefa, Capitão. Espero que desta vez não seja só mera curiosidade, hein?";
						link.l1 = "Por favor, relembre-me os detalhes desta missão, Vossa Excelência.";
						link.l1.go = "Intelligence";
						link.l2 = RandPhraseSimple("Desculpe, mas não estou pronto para assumir essa tarefa no momento.","Receio que não posso cumprir esta tarefa agora.","Me desculpe — ainda não estou pronto para assumir essa tarefa.");
						link.l2.go = "exit";
						break;
					}
					sTemp = GetSpyColony(npchar);
					if (sTemp == "none")
					{
						dialog.text = RandPhraseSimple("Hoje não tenho nenhum trabalho desse tipo para você. Talvez volte amanhã...","Infelizmente, não tenho nenhuma tarefa desse tipo no momento. Tente voltar mais tarde, daqui a um ou dois dias.","Hoje não posso lhe impor nada desse tipo. Ficarei feliz em vê-lo em outra ocasião.");
						link.l1 = "Entendi. "+GetAddress_FormToNPC(NPChar)+".";
						link.l1.go = "exit";
						break;
					}
					pchar.GenQuest.Intelligence.Terms = hrand(10) + (42 - MOD_SKILL_ENEMY_RATE);
					pchar.GenQuest.Intelligence.Money = ((hrand(5)+11)*2000)+(sti(pchar.rank)*1500);
					pchar.GenQuest.Intelligence.City = sTemp;
					sTemp = ", which is on " + XI_ConvertString(GetIslandByColony(&colonies[FindColony(pchar.GenQuest.Intelligence.City)])+"Dat");
					dialog.text = "Tenho uma missão para você, que envolve riscos consideráveis. Preciso que você se infiltre em "+XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Acc")+sTemp+", encontre uma certa pessoa lá e depois me entregue o que quer que ele lhe der.";
					link.l1 = "Hum, não acho que nisso "+XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Dat")+" Serei um convidado bem-vindo...";
					link.l1.go = "Intelligence";
				break;
			}
		break;
		//---------------------------- генератор квестов мэра -------------------------------

		case "sell_prisoner":
            dialog.text = "Quem você gostaria de resgatar?";

            qty = 1;
            for(i=0; i < GetPassengersQuantity(pchar); i++)
            {
                cn = GetPassenger(pchar,i);
                if(cn != -1)
                {
                    offref = GetCharacter(cn);
                    if(CheckAttribute(offref,"prisoned"))
                    {
        	            if(sti(offref.prisoned)==true && GetRemovable(offref)) // ставим только фантомов
        	            {
                            attrLoc = "l"+qty;
                            link.(attrLoc)    = GetFullName(offref) + " - " + NationNameMan(sti(offref.nation)) + ".";
                            link.(attrLoc).go = "GetPrisonerIdx_" + offref.index;
                            qty++;
                        }
                    }
                }
            }
			link.l99 = "Ninguém.";
			link.l99.go = "exit";
		break;
		
		case "sell_prisoner_2":
            offref = GetCharacter(sti(pchar.GenQuest.GetPrisonerIdx));
            attrLoc =  "So, this is captain " + GetFullName(offref) + ", " + NationNameMan(sti(offref.nation))+ ".";
            // цена зависит от губернатора
            qty = makeint(sti(offref.rank)*(800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L)*100) + GetCharacterSkillToOld(offref, "Leadership")*500 + GetCharacterSkillToOld(pchar, "commerce")*500);
			if(HasShipTrait(pchar, "trait14")) qty = makeint(qty * 1.35);
            if (sti(offref.nation) == sti(NPChar.nation))
            {
                attrLoc = attrLoc + " I am ready to pay the ransom for my compatriot in the amount of  " + FindRussianMoneyString(qty) + ".";
            }
            else
            {
                if (sti(offref.nation) == PIRATE)
                {
                    qty = qty / 5;
                    attrLoc = attrLoc + " I can give " + FindRussianMoneyString(qty) + "  for this gallowsbird. And then we'll execute the scoundrel at once.";

                }
                else
                {
                    qty = qty / 2;
                    attrLoc = attrLoc + " " + FindRussianMoneyString(qty) + "for that man, not a peso more.";
                }
            }
			dialog.text = attrLoc;
			pchar.PrisonerSellPrice =  qty;
			link.l1 = "Fechado. Ele é todo seu, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "sell_prisoner_3";
			link.l3 = "Não. Isso não serve.";
			link.l3.go = "exit";
		break;


		case "sell_prisoner_3":
			dialog.text = "Isso é bom.";
			link.l1 = "Tudo de bom.";
			link.l1.go = "exit";
			OfficersReaction("bad");

			offref = GetCharacter(sti(pchar.GenQuest.GetPrisonerIdx));
			AddMoneyToCharacter(pchar, sti(pchar.PrisonerSellPrice));
			if (sti(offref.nation) == sti(NPChar.nation))
            {
                AddCharacterExpToSkill(pchar, "Commerce", 25);
            }
            else
            {
                if (sti(offref.nation) == PIRATE)
                {
                    ChangeCharacterComplexReputation(pchar,"nobility", -2);
                }
                else
                {
                    AddCharacterExpToSkill(pchar, "Commerce", 5);
                }
            }

        	offref.location = "";
        	ReleasePrisoner(offref); // освободили пленника
		break;
		////   CAPTURE //////////
		case "CAPTURE_Main":
            NextDiag.TempNode = "CAPTURE_Main";
			AfterTownBattle();  // всё, все свободны
			
			// --> Левассер
			if (pchar.location == "Tortuga_townhall" && CheckAttribute(pchar, "questTemp.Sharlie.Hardcore_Tortuga"))
			{
                dialog.Text = "Mas que absurdo é esse, de Maure? Desde quando os franceses atacam seus próprios compatriotas?!";
                Link.l1 = "Por ordem do Governador-Geral François Longvilliers de Poincy, você, Monsieur Levasseur, está removido do cargo de governador de Tortuga e condenado à morte! E sou eu quem vai executar essa sentença!";
                Link.l1.go = "levasser";
				break;
			}
			// <-- Левассер
            // fix от грабежа 5 раз на дню -->
            if (!CheckNPCQuestDate(npchar, "GrabbingTownDate"))
			{
                dialog.Text = "Você já pegou tudo. O que mais você quer?";
                Link.l1 = "É, claro, cidade errada.";
                Link.l1.go = "Exit_City";

                NPChar.NoGiveMoney = true;

            	ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 20);
                // вернём диалог после разговора и спрячем
                SetReturn_Gover_Dialog_Exit(NPChar);
				break;
			}
			SetNPCQuestDate(npchar, "GrabbingTownDate");
			// fix от грабежа 5 раз на дню <--

            if (CheckAttribute(FortChref, "Fort.Mode") && sti(FortChref.Fort.Mode) != FORT_DEAD)
            { // а форт-то ЖИВ, значит с суши прошли
                dialog.Text = "Insolência sem precedentes! Os reforços do forte chegarão em breve, e você vai pagar por isso!";
                Link.l2 = "Eu não vou ficar aqui esperando eles chegarem. Só me pague, e vamos sair desta cidade.";
                Link.l2.go = "Summ";
                Pchar.HalfOfPaymentByCity = true; // токо половина денег
            }
            else
            {
				dialog.Text = "Desta vez você venceu, mas saiba que um esquadrão dos nossos caçadores de piratas vai te perseguir e arrancar cada peso da sua carne imunda de pirata!";
	            if (!bWorldAlivePause || bBettaTestMode)
	            {
	                int iColony = FindColony(npchar.city);
					if (!CheckAttribute(&colonies[iColony], "notCaptured")) //незахватываемые города
					{
						if (CheckAttribute(FortChref, "Default.Prison"))
	    				{
	    					Link.l1 = "Silence! This town belongs to me from now on; as for your piratehunters - I'll send them straight to Davy Jones' Locker. Hey lads, grab this pig and put it behind bars.";
	    				}
	    				else
	    				{
	    					Link.l1 = "Esta cidade agora me pertence. Rapazes, acompanhem o ex-governador até seus novos 'aposentos', heh heh.";
	    				}
	    				Link.l1.go = "City";
					}
				}
				if (!isCityHasFort(NPChar.City))
	            {
	                Link.l2 = "Reforços do forte? Basta me pagar um bom resgate e nós deixaremos sua cidade.";
				}
				else
				{
	            	Link.l2 = "Um esquadrão de caçadores de piratas? Hmm... Só me pague e nós deixaremos sua cidade.";
	            }
				Link.l2.go = "Summ";

                bOk = !bWorldAlivePause || bBettaTestMode;
	            if (isMainCharacterPatented() && bOk && !CheckAttribute(&colonies[iColony], "notCaptured")) //не даем захватить колонию
	            {
					// восстановим нацию патента
					PChar.nation = GetBaseHeroNation();
					
					dialog.Text = "Insolência sem precedentes! Como ousa atacar a colônia que pertence a "+NationNameGenitive(sti(NPChar.nation))+"?! Você vai pagar caro pelo sangue que derramou e pelo dano que causou ao nosso estado.";
	                Link.l1 = "A partir de agora, esta colônia me pertence. Quem ousar desafiar minha autoridade vai direto para o inferno.";
	                Link.l1.go = "City_patent";
	                Link.l2 = "Acalme-se. Estou agindo em nome de "+NationNameGenitive(sti(PChar.nation))+". A partir deste momento, esta colônia pertence a "+NationKingsCrown(PChar)+"!";
	                Link.l2.go = "City_nation";
	                Link.l3 = "Bela cidade você tem aqui. Seria uma verdadeira tragédia se ela fosse reduzida a cinzas e seu governador enforcado na praça principal. Acho que devemos conversar sobre o valor do resgate que está disposto a pagar para evitar que essa tragédia aconteça. ";
	                Link.l3.go = "Summ_patent";
	            }
            }
        break;
		
		// --> Левассер
		case "levasser":
            dialog.Text = "Poincy?! Maldito seja esse papista desgraçado! Eu mesmo vou acertar as contas com ele... e quanto a você, canalha, acabou pra você! Você não vai sair daqui vivo – eu mesmo vou garantir o seu fim!";
			Link.l1 = "Poupe-me do seu sermão, herege. Quando eu mandar sua alma huguenote para o Inferno, mande lembranças minhas a Lúcifer e Jean Calvin. Em guarda!";
			Link.l1.go = "levasser_1";
        break;
		
		case "levasser_1":
			chrDisableReloadToLocation = true;//закрыть локацию
            DialogExit();
			LAi_SetImmortal(npchar, false);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto6");
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LevasserDiedResidence");
			AddDialogExitQuest("MainHeroFightModeOn");	
        break;
		// <-- Левассер
        
        case "City":
            ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 40);
            AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 400);

            Pchar.GenQuestFort.fortCharacterIdx = FortChref.index;
            AddDialogExitQuest("Residence_Captured_Any");

            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
            // ремонт
            RepairAllShips();
            Log_Info("All ships have been repaired.");
            //  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
	        AddQuestRecordInfo("Gen_CityCapture", "t3");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
			//  СЖ <--
            NextDiag.CurrentNode = "Prison";
			DialogExit();
        break;

        case "City_patent":
            ChangeCharacterComplexReputation(GetMainCharacter(),"nobility", -20); // пираты мы, но у нас патент
            dialog.Text = "Desta vez você venceu, mas saiba que nosso esquadrão chegará em breve e não deixará nada de você!";
			Link.l1 = "Shut your mouth. This town belongs to me from now on; as for your squadron - I'll send it straight to Hell. Boys, escort the ex-governor to his new 'quarters', heh heh.";
			Link.l1.go = "City";
        break;

        case "Exit_for_pay":
			dialog.Text = "O que mais você precisa de mim?";
            Link.l1 = "Só estou conferindo se deixei passar alguma coisa...";
            Link.l1.go = "exit";

            NextDiag.TempNode = "Exit_for_pay";
		break;

        case "Exit_City":
		    NextDiag.CurrentNode = "Exit_for_pay";
		    Pchar.GenQuestFort.fortCharacterIdx = FortChref.index;
		    if (sti(NPChar.NoGiveMoney) == false) // себе берем
		    {
				// вернём диалог после разговора и спрячем
				SetReturn_Gover_Dialog_Exit(NPChar);
				AddDialogExitQuestFunction("TWN_ExitForPay");
            }
            DialogExit();
        break;

        case "Summ":
            dialog.Text = "Não tenho outra escolha a não ser aceitar seus termos. Pegue seu maldito dinheiro e saia da nossa colônia imediatamente.";
            Link.l1 = "Foi um prazer fazer negócios com você.";
            Link.l1.go = "Exit_City";
            NPChar.NoGiveMoney = false;

            ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 30);
            AddCharacterExpToSkill(GetMainCharacter(), SKILL_FORTUNE, 300);
            AddCharacterExpToSkill(GetMainCharacter(), "Commerce", 300);

            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1);
            //  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
	        AddQuestRecordInfo("Gen_CityCapture", "t2");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
			//  СЖ <--
        break;

        case "Summ_patent":
            dialog.Text = "Certo, diga quais são seus termos...";
            Link.l1 = "Aye, vae victis! Comece a contar seu dinheiro.";
            Link.l1.go = "Summ";
            ChangeCharacterComplexReputation(GetMainCharacter(),"nobility", -10); // не на службе
        break;

        case "City_nation":
			dialog.Text = "Certo, nós nos rendemos à sua misericórdia.";
			Link.l1 = "Eu aconselho você a deixar a cidade o quanto antes – as mudanças que estão por vir podem ser bem ruins para a sua saúde. Adeus.";
			Link.l1.go = "Exit_City";
			NPChar.NoGiveMoney = true;

            ChangeCharacterComplexReputation(GetMainCharacter(),"nobility", 5);
            AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 600);
            AddCharacterExpToSkill(GetMainCharacter(), "Sneak", 400);
            SetNationRelationBoth(sti(PChar.nation), sti(NPChar.nation), RELATION_ENEMY);

            PChar.questTemp.DontSetNewDialogToMayor = true; // иначе может сменить диалог и сбойнуть
            PChar.questTemp.DontNullDeposit = true;    // чтоб не нулили ростовщика
            SetCaptureTownByNation(NPChar.City, sti(PChar.nation));
            DeleteAttribute(PChar, "questTemp.DontSetNewDialogToMayor");
            AddDialogExitQuestFunction("LaunchColonyInfoScreen"); // табличка
            //  СЖ -->
	    	sTemp =  GetNationNameByType(sti(PChar.nation));
			ReOpenQuestHeader("Gen_CityCapture");
	        AddQuestRecordInfo("Gen_CityCapture", "t1");
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
			AddQuestUserData("Gen_CityCapture", "sNation", XI_ConvertString(sTemp + "Gen"));
			//  СЖ <--
			AddTitleNextRate(sti(PChar.nation), 1);  // счетчик звания
            SetCharacterRelationBoth(sti(FortChref.index), GetMainCharacterIndex(), RELATION_FRIEND);// нечего не даёт, тк работает OtherChar - а это губер, но он и так друг
            UpdateRelations();

            // 22.03.05  fix вернём диалог после разговора и спрячем
            //  внутри диалога не работало
            SetReturn_Gover_Dialog_Exit(NPChar);

            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
	    break;
	    
	    case "Prison":
			dialog.Text = "O que mais você quer de mim, canalha?";
            Link.l3 = "Como Vossa Excelência está gostando do novo quarto? Espaçoso o bastante? Bem, agora preciso ir!";
            Link.l3.go = "exit";
            NextDiag.TempNode = "Prison";
		break;
		
		case "arestFree_1":
			dialog.text = "Assentar? E como você imagina que isso seria?";
            link.l1 = "Acredito que uma quantia de "+iTotalTemp*6000+" pesos ainda podem me salvar, não podem?";
			link.l1.go = "arestFree_2";
			link.l2 = "Não. E está na hora de eu ir. Meus cumprimentos.";
			link.l2.go = "arest_1";
		break;

		case "arestFree_2":
            if (GetCharacterSkillToOld(PChar, SKILL_FORTUNE) >= hrand(7) && iTotalTemp < 21)
            {
    			dialog.text = "Suponho que poderíamos resolver nosso incidente dessa maneira. Você ainda não foi longe o bastante para tornar a situação irreparável.";
    		    link.l1 = "Excelente. Fico muito feliz. Por favor, aceite minha doação.";
    		    link.l1.go = "Exit";
    		    AddMoneyToCharacter(pchar, -iTotalTemp*6000);
    		    ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", -iTotalTemp);
    		    AddCharacterExpToSkill(pchar, "Fortune", 100);
            }
            else
            {
    			dialog.text = "Está me oferecendo um suborno? Ah, não! Seus atos malignos só podem ser redimidos de uma maneira... Guardas! Levem "+GetSexPhrase("ele","ela")+"   preso!";
    		    link.l1 = "Espere!";
    		    link.l1.go = "arest_2";
    		    AddCharacterExpToSkill(pchar, "Fortune", 10);
            }
		break;

		case "arest_1":
			dialog.text = "Claro, chegou a hora. Vamos nos despedir. Guardas! Peguem "+GetSexPhrase("ele","ela")+"!";
		    link.l1 = "De jeito nenhum!";
		    link.l1.go = "fight";
		break;

		case "arest_2":
			dialog.text = "Você já teve tempo de sobra para pensar! Guardas!";
			link.l1 = "Você não vai me pegar tão fácil!";
		    link.l1.go = "fight";
		break;    
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Уничтожение банды
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "DestroyGang":
			pchar.GenQuest.Governor.Group1.day = GetDataDay();
			dialog.text = "Claro. Para cumprir esta missão, estou lhe dando "+FindRussianDaysString(sti(pchar.GenQuest.DestroyGang.Terms))+", e sua recompensa, caso tenha sucesso, será "+FindRussianMoneyString(sti(pchar.GenQuest.DestroyGang.Money))+".";
			link.l1 = "Sim, eu aceito essa tarefa.";
		    link.l1.go = "DestroyGang_agree";
			link.l2 = "Hmm... Não, acho que vou deixar passar.";
		    link.l2.go = "All_disagree";
		break;
		case "DestroyGang_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.questName = "DestroyGang"; //тип квеста
			pchar.GenQuest.DestroyGang.Location = GetGangLocation(npchar); //определяем локацию,где банда
			pchar.GenQuest.DestroyGang.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			if (pchar.GenQuest.DestroyGang.Location == "none") //на всякий случай
			{
				dialog.text = "Espere, acabei de lembrar do relatório de ontem. A questão é que essa gangue já deixou nossa ilha. Então vou ter que cancelar a missão.";
				link.l1 = "Entendo. Que pena.";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "GenQuest." + pchar.GenQuest.questName);
				DeleteAttribute(pchar, "GenQuest.questName");
			}
			else
			{
				dialog.text = "Muito bem! Estarei esperando por você e seus relatórios na minha residência.";
				link.l1 = "Não vou te deixar esperando muito, "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "exit";
				pchar.quest.DestroyGang.win_condition.l1 = "location";
				pchar.quest.DestroyGang.win_condition.l1.location = pchar.GenQuest.DestroyGang.Location;
				pchar.quest.DestroyGang.win_condition = "DestroyGang_fight";
				pchar.quest.DestroyGang.again = true; //тупо дожидаться своего часа бандиты не будут
				SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.DestroyGang.Terms), false);
				//==> энкаунтеров в квестовой локации не будет 
				locations[FindLocation(pchar.GenQuest.DestroyGang.Location)].DisableEncounters = true;
				ReOpenQuestHeader("MayorsQuestsList");
				AddQuestRecord("MayorsQuestsList", "1");
				AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
				AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
				makearef(arName, pchar.GenQuest.DestroyGang);
				AddQuestUserData("MayorsQuestsList", "GangName", GetFullName(arName));
				AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.DestroyGang.Terms)));
				AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.DestroyGang.Money)));
			}
		break;
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Контркурьер
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "TakePostcureer":
			//установка параметров
			pchar.GenQuest.questName = "TakePostcureer"; //тип квеста
			// belamour legendary edition враждебную нацию квестодателя, а не героя -->
			pchar.GenQuest.TakePostcureer.Nation = FindEnemyNation2Character(sti(npchar.index)); //вражеская нация
			iTemp = 1;
			while (iTemp < 10 && sti(pchar.GenQuest.TakePostcureer.Nation) == PIRATE) {
				pchar.GenQuest.TakePostcureer.Nation = FindEnemyNation2Character(sti(npchar.index));
				iTemp += 1;
			}
			if (iTemp == 10 && sti(pchar.GenQuest.TakePostcureer.Nation) == PIRATE) {
				dialog.text = LinkRandPhrase("Hoje não tenho nenhum trabalho para lhe oferecer.","Hoje não há mais trabalhos para você.","Sem mais trabalho por hoje, desculpe. Volte amanhã e veremos...");
				link.l1 = RandPhraseSimple("Pena...","Ah, que pena, "+GetAddress_FormToNPC(NPChar)+". ");
        		link.l1.go = "exit";
				
				if (CheckAttribute(pchar, "GenQuest.questName")) {
					QuestName = pchar.GenQuest.questName;
					DeleteAttribute(pchar, "GenQuest." + QuestName);
					DeleteAttribute(pchar, "GenQuest.questName");
				}
				
				break;
			}
			pchar.GenQuest.TakePostcureer.City = FindQuestCity(npchar, "enemy",sti(pchar.GenQuest.TakePostcureer.Nation), false, false);
			// <-- legendary edition
			pchar.GenQuest.TakePostcureer.Island = GetArealByCityName(pchar.GenQuest.TakePostcureer.City);
			pchar.GenQuest.TakePostcureer.Terms = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, pchar.GenQuest.TakePostcureer.Island)+5;
			pchar.GenQuest.TakePostcureer.LoginDay = sti(pchar.GenQuest.TakePostcureer.Terms)-1;
			pchar.GenQuest.TakePostcureer.ShipType = SelectCureerShipType();
			pchar.GenQuest.TakePostcureer.ShipName = GenerateRandomNameToShip(sti(pchar.GenQuest.TakePostcureer.Nation));
			pchar.GenQuest.TakePostcureer.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakePostcureer.ShipType));
			pchar.GenQuest.TakePostcureer.Money = ((hrand(5)+hrand(6, "1")+42)*600)+(sti(pchar.rank)*1600);
			pchar.GenQuest.Governor.Group3.day = GetDataDay();
			dialog.text = "Claro. Você vai precisar localizar um navio mensageiro de "+NationNameGenitive(sti(pchar.GenQuest.TakePostcureer.Nation))+" chamado de '"+pchar.GenQuest.TakePostcureer.ShipName+"', aborde-a e traga-me os documentos, que você deve encontrar na cabine do capitão. Esta embarcação vai passar perto de "+XI_ConvertString("Colony"+pchar.GenQuest.TakePostcureer.City+"Gen")+" aproximadamente em "+FindRussianDaysString(pchar.GenQuest.TakePostcureer.Terms)+".";
			link.l1 = "Certo, eu aceito essa missão. E que tipo de documentos eu devo procurar?";
		    link.l1.go = "TakePostcureer_agree";
			link.l2 = "Hum... Não, acho que vou deixar passar.";
		    link.l2.go = "All_disagree";
		break;
		
		case "TakePostcureer_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakePostcureer.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "Correspondência. Há alguns papéis muito importantes para mim. Mas não precisa procurar entre os documentos, apenas traga o pacote inteiro para mim. Eu vou te pagar "+FindRussianMoneyString(sti(pchar.GenQuest.TakePostcureer.Money))+"\nEntão, estarei esperando por você e pelos resultados do seu trabalho na minha residência.";
			link.l1 = "Não vou te fazer esperar muito, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "exit";
			pchar.quest.TakePostcureer.win_condition.l1 = "location";
			pchar.quest.TakePostcureer.win_condition.l1.location = pchar.GenQuest.TakePostcureer.Island;
			pchar.quest.TakePostcureer.win_condition.l2 = "Timer";
			pchar.quest.TakePostcureer.win_condition.l2.date.hour  = sti(GetTime());
			pchar.quest.TakePostcureer.win_condition.l2.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.TakePostcureer.LoginDay));
			pchar.quest.TakePostcureer.win_condition.l2.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.TakePostcureer.LoginDay));
			pchar.quest.TakePostcureer.win_condition.l2.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.TakePostcureer.LoginDay));
			pchar.quest.TakePostcureer.function = "TakePostcureer_CreateShip";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakePostcureer.Terms), false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "3");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.TakePostcureer.City+"Gen"));
			AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.TakePostcureer.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakePostcureer.Money)));
			AddQuestUserData("MayorsQuestsList", "sNation", NationNameGenitive(sti(pchar.GenQuest.TakePostcureer.Nation)));
			AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakePostcureer.ShipName);
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Контрфрахт - уничтожить корабль с арсеналом
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "TakeArsenalship":
			//установка параметров
			pchar.GenQuest.questName = "TakeArsenalship"; //тип квеста
			// belamour legendary edition враждебную нацию квестодателя, а не героя -->
			pchar.GenQuest.TakeArsenalship.Nation = FindEnemyNation2Character(sti(npchar.index));
			iTemp = 1;
			while (iTemp < 10 && sti(pchar.GenQuest.TakeArsenalship.Nation) == PIRATE) {
				pchar.GenQuest.TakeArsenalship.Nation = FindEnemyNation2Character(sti(npchar.index));
				iTemp += 1;
			}
			if (iTemp == 10 && sti(pchar.GenQuest.TakeArsenalship.Nation) == PIRATE) {
				dialog.text = LinkRandPhrase("Hoje não tenho nenhum trabalho para lhe oferecer.","Hoje não há mais trabalhos para você.","Sem mais trabalho por hoje, desculpe. Volte amanhã, e veremos...");
				link.l1 = RandPhraseSimple("Pena...","Ah, que pena, "+GetAddress_FormToNPC(NPChar)+". ");
        		link.l1.go = "exit";
				
				if (CheckAttribute(pchar, "GenQuest.questName")) {
					QuestName = pchar.GenQuest.questName;
					DeleteAttribute(pchar, "GenQuest." + QuestName);
					DeleteAttribute(pchar, "GenQuest.questName");
				}
				
				break;
			}
			pchar.GenQuest.TakeArsenalship.City = FindQuestCity(npchar, "enemy",sti(pchar.GenQuest.TakeArsenalship.Nation), false, false);
			// <-- legendary edition
			pchar.GenQuest.TakeArsenalship.Island = GetArealByCityName(pchar.GenQuest.TakeArsenalship.City);
			pchar.GenQuest.TakeArsenalship.Terms = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, pchar.GenQuest.TakeArsenalship.Island)+5;
			pchar.GenQuest.TakeArsenalship.LoginDay = sti(pchar.GenQuest.TakeArsenalship.Terms)-1;
			pchar.GenQuest.TakeArsenalship.ShipType = SelectArsenalShipType(FLAG_SHIP_TYPE_RAIDER);
			pchar.GenQuest.TakeArsenalship.ShipTypeA = SelectArsenalShipType(FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_UNIVERSAL);
			pchar.GenQuest.TakeArsenalship.ShipName = GenerateRandomNameToShip(sti(pchar.GenQuest.TakeArsenalship.Nation));
			pchar.GenQuest.TakeArsenalship.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakeArsenalship.ShipType));
			pchar.GenQuest.TakeArsenalship.CannonA = SelectLevelCannonParameter(sti(pchar.GenQuest.TakeArsenalship.ShipTypeA)); // Addon 2016-1 Jason пиратская линейка
			pchar.GenQuest.TakeArsenalship.Money = ((hrand(5)+hrand(6, "1")+36)*700)+(sti(pchar.rank)*1600);
			pchar.GenQuest.Governor.Group3.day = GetDataDay();
			dialog.text = "Claro. Você vai precisar localizar um transporte militar "+NationNameGenitive(sti(pchar.GenQuest.TakeArsenalship.Nation))+", with gunpowder and ammunition on board; the name of the vessel is '"+pchar.GenQuest.TakeArsenalship.ShipName+"', find and destroy it. We'll weaken our enemy by doing that\nThe transport will sail with an escort to the colony "+XI_ConvertString("Colony"+pchar.GenQuest.TakeArsenalship.City)+", and will be approximately in "+FindRussianDaysString(pchar.GenQuest.TakeArsenalship.Terms)+", so you should hurry.";
			link.l1 = "Certo, eu aceito. Preciso afundar o navio do arsenal ou devo tentar capturá-lo?";
		    link.l1.go = "TakeArsenalship_agree";
			link.l2 = "Hmm... Não, acho que vou deixar passar.";
		    link.l2.go = "All_disagree";
		break;
		
		case "TakeArsenalship_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakeArsenalship.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "Não me importa, fica a seu critério. O importante é que esta carga não chegue ao destino. Se conseguir, eu vou te pagar "+FindRussianMoneyString(sti(pchar.GenQuest.TakeArsenalship.Money))+"... não vou mais atrasá-lo, capitão.";
			link.l1 = "Não vou te fazer esperar muito, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "exit";
			pchar.quest.TakeArsenalship.win_condition.l1 = "location";
			pchar.quest.TakeArsenalship.win_condition.l1.location = pchar.GenQuest.TakeArsenalship.Island;
			pchar.quest.TakeArsenalship.win_condition.l2 = "Timer";
			pchar.quest.TakeArsenalship.win_condition.l2.date.hour  = sti(GetTime());
			pchar.quest.TakeArsenalship.win_condition.l2.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.TakeArsenalship.LoginDay));
			pchar.quest.TakeArsenalship.win_condition.l2.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.TakeArsenalship.LoginDay));
			pchar.quest.TakeArsenalship.win_condition.l2.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.TakeArsenalship.LoginDay));
			pchar.quest.TakeArsenalship.function = "TakeArsenalship_CreateShip";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakeArsenalship.Terms), false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "8");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.TakeArsenalship.City));
			AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.TakeArsenalship.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakeArsenalship.Money)));
			AddQuestUserData("MayorsQuestsList", "sNation", NationNameGenitive(sti(pchar.GenQuest.TakeArsenalship.Nation)));
			AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakeArsenalship.ShipName);
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	ОЗГ - уничтожить корабль пиратов
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "TakePirateship":
			//установка параметров
			pchar.GenQuest.questName = "TakePirateship"; //тип квеста
			pchar.GenQuest.TakePirateship.City = FindQuestCity(npchar, "all", -1, true, true); // belamour legendary edition 
			pchar.GenQuest.TakePirateship.Island = GetArealByCityName(pchar.GenQuest.TakePirateship.City);
			pchar.GenQuest.TakePirateship.Terms = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, pchar.GenQuest.TakePirateship.Island)+5;
			pchar.GenQuest.TakePirateship.ShipType = SelectPirateShipType();
			pchar.GenQuest.TakePirateship.ShipName = GenerateRandomNameToShip(PIRATE);
			pchar.GenQuest.TakePirateship.Name = GenerateRandomName(PIRATE, "man");
			pchar.GenQuest.TakePirateship.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakePirateship.ShipType));
			pchar.GenQuest.TakePirateship.Money = ((hrand(5) + hrand(6, "1")+4)*800)+13000+(sti(pchar.rank)*1250);
			pchar.GenQuest.Governor.Group2.day = GetDataDay();
			dialog.text = "Claro. Estou realmente furioso com as ações de certo capitão pirata, cujo nome é "+pchar.GenQuest.TakePirateship.Name+"Esse canalha começou a atacar nossos mercantes, o que está prejudicando muito o comércio entre as colônias. Agora é o momento perfeito para nos livrarmos desse desgraçado, porque eu sei exatamente onde ele está se escondendo neste momento. Está pronto para mandar esse filho da mãe ao Julgamento de Deus?";
			link.l1 = "Seria uma honra! Onde posso encontrar esse pirata?";
		    link.l1.go = "TakePirateship_agree";
			link.l2 = "Hum... Não, acho que vou deixar passar.";
		    link.l2.go = "All_disagree";
		break;
		
		case "TakePirateship_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakePirateship.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "Na mais próxima "+FindRussianDaysString(pchar.GenQuest.TakePirateship.Terms)+" seu navio chamado '"+pchar.GenQuest.TakePirateship.ShipName+"' vai estar navegando ao longo das costas perto de "+XI_ConvertString("Colony"+pchar.GenQuest.TakePirateship.City+"Gen")+". Encontre-o e mate-o. Faça-o virar comida de peixe junto com seu navio, aborde o navio - não me importa. Só quero que esse maldito pirata pare de conspurcar nosso mar com sua presença\nPor essa tarefa estou disposto a lhe pagar "+FindRussianMoneyString(sti(pchar.GenQuest.TakePirateship.Money))+". Não perca tempo, capitão: esse canalha não vai esperar por você em "+XI_ConvertString("Colony"+pchar.GenQuest.TakePirateship.City+"Gen")+". Vá, e que Deus te ajude!";
			link.l1 = "Já içando âncora, "+GetAddress_FormToNPC(NPChar)+"! Não vai precisar esperar muito.";
			link.l1.go = "exit";
			pchar.quest.TakePirateship.win_condition.l1 = "location";
			pchar.quest.TakePirateship.win_condition.l1.location = pchar.GenQuest.TakePirateship.Island;
			pchar.quest.TakePirateship.function = "TakePirateship_CreateShip";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakePirateship.Terms), false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "9");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.TakePirateship.City+"Gen"));
			AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.TakePirateship.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakePirateship.Money)));
			AddQuestUserData("MayorsQuestsList", "sName", pchar.GenQuest.TakePirateship.Name);
			AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakePirateship.ShipName);
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	ОЗГ - захватить пассажира
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "TakePassenger":
			//установка параметров
			pchar.GenQuest.questName = "TakePassenger"; //тип квеста
			pchar.GenQuest.TakePassenger.Nation = FindEnemyNation2Character(sti(npchar.index));//вражеская нация
			iTemp = 1;
			while (iTemp < 10 && sti(pchar.GenQuest.TakePassenger.Nation) == PIRATE) {
				pchar.GenQuest.TakePassenger.Nation = FindEnemyNation2Character(sti(npchar.index));
				iTemp += 1;
			}
			if (iTemp == 10 && sti(pchar.GenQuest.TakePassenger.Nation) == PIRATE) {
				dialog.text = LinkRandPhrase("Hoje não tenho nenhum trabalho para lhe oferecer.","Hoje não há mais trabalhos para você.","Sem mais trabalho por hoje, desculpe. Volte amanhã e veremos...");
				link.l1 = RandPhraseSimple("Pena...","Ah, que pena, "+GetAddress_FormToNPC(NPChar)+". ");
        		link.l1.go = "exit";
				
				if (CheckAttribute(pchar, "GenQuest.questName")) {
					QuestName = pchar.GenQuest.questName;
					DeleteAttribute(pchar, "GenQuest." + QuestName);
					DeleteAttribute(pchar, "GenQuest.questName");
				}
				
				break;
			}
			pchar.GenQuest.TakePassenger.City = FindQuestCity(npchar, "enemy", sti(pchar.GenQuest.TakePassenger.Nation), false, false); // belamour legendary edition
			pchar.GenQuest.TakePassenger.CityA = SelectAnyColony(pchar.GenQuest.TakePassenger.City);
			pchar.GenQuest.TakePassenger.Terms1 = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, GetArealByCityName(pchar.GenQuest.TakePassenger.City));
			pchar.GenQuest.TakePassenger.Terms2 = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.TakePassenger.City), GetArealByCityName(pchar.GenQuest.TakePassenger.CityA))+1;
			pchar.GenQuest.TakePassenger.Terms = sti(pchar.GenQuest.TakePassenger.Terms1)+sti(pchar.GenQuest.TakePassenger.Terms2);
			pchar.GenQuest.TakePassenger.ShipType = SelectCureerShipType();
			pchar.GenQuest.TakePassenger.ShipName = GenerateRandomNameToShip(sti(pchar.GenQuest.TakePassenger.Nation));
			pchar.GenQuest.TakePassenger.Name = GenerateRandomName(sti(pchar.GenQuest.TakePassenger.Nation), "man");
			pchar.GenQuest.TakePassenger.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakePassenger.ShipType));
			pchar.GenQuest.TakePassenger.Money = ((hrand(5) + hrand(6, "1")+4)*500)+12500+(sti(pchar.rank)*1000);
			pchar.GenQuest.Governor.Group2.day = GetDataDay();
			string sText = SelectPassText();
			dialog.text = "Claro. Estou falando de um canalha chamado "+pchar.GenQuest.TakePassenger.Name+". "+sText+" Eu estive procurando por ele há bastante tempo, e agora finalmente consegui informações confiáveis sobre onde ele pode ser encontrado. Preciso que você traga esse homem para mim, vivo, custe o que custar. Quero enforcá-lo em público na praça da nossa cidade. Você está pronto para assumir essa missão?";
			link.l1 = "Estou pronto, "+GetAddress_FormToNPC(NPChar)+". Onde posso encontrar esse canalha?";
		    link.l1.go = "TakePassenger_agree";
			link.l2 = "Hum... Não, acho que vou deixar passar.";
		    link.l2.go = "All_disagree";
		break;
		
		case "TakePassenger_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakePassenger.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "Acabou de chegar "+FindRussianDaysString(pchar.GenQuest.TakePassenger.Terms1)+", ele, como passageiro em um navio chamado '"+pchar.GenQuest.TakePassenger.ShipName+"', vai zarpar de "+XI_ConvertString("Colony"+pchar.GenQuest.TakePassenger.City+"Gen")+" e vá para "+XI_ConvertString("Colony"+pchar.GenQuest.TakePassenger.CityA+"Acc")+". Você tem "+FindRussianDaysString(pchar.GenQuest.TakePassenger.Terms)+" para encontrar este navio na rota indicada, abordá-lo e capturar o desgraçado. Se seguir estas instruções, eu lhe pago "+FindRussianMoneyString(sti(pchar.GenQuest.TakePassenger.Money))+". Boa sorte para você, capitão!";
			link.l1 = "Não vou perder mais tempo, "+GetAddress_FormToNPC(NPChar)+"! Vou zarpar imediatamente.";
			link.l1.go = "exit";
			SetFunctionTimerCondition("TakePassenger_CreateShip", 0, 0, sti(pchar.GenQuest.TakePassenger.Terms1), false);
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakePassenger.Terms), false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "10");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.TakePassenger.City+"Gen"));
			AddQuestUserData("MayorsQuestsList", "sCityA", XI_ConvertString("Colony"+pchar.GenQuest.TakePassenger.CityA+"Acc"));
			AddQuestUserData("MayorsQuestsList", "sDay1", FindRussianDaysString(sti(pchar.GenQuest.TakePassenger.Terms1)));
			AddQuestUserData("MayorsQuestsList", "sDay2", FindRussianDaysString(sti(pchar.GenQuest.TakePassenger.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakePassenger.Money)));
			AddQuestUserData("MayorsQuestsList", "sName", pchar.GenQuest.TakePassenger.Name);
			AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakePassenger.ShipName);
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Таможенный патруль
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "CustomPatrol":
			//установка параметров
			pchar.GenQuest.questName = "CustomPatrol"; //тип квеста
			pchar.GenQuest.CustomPatrol.Nation = sti(npchar.nation);//нация
			pchar.GenQuest.CustomPatrol.Island = Islands[GetCharacterCurrentIsland(PChar)].id;
			pchar.GenQuest.CustomPatrol.LoginDay = rand(2)+1;
			pchar.GenQuest.CustomPatrol.Loginlocator = rand(3)+3;
			pchar.GenQuest.CustomPatrol.ShipType = SelectCustomPatrolShipType(FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_UNIVERSAL);
			pchar.GenQuest.CustomPatrol.ShipTypeA = SelectCustomPatrolShipType(FLAG_SHIP_TYPE_RAIDER);
			pchar.GenQuest.CustomPatrol.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.CustomPatrol.ShipType));
			pchar.GenQuest.CustomPatrol.Money = ((hrand(5)+hrand(6, "1")+4)*450)+8200 + (sti(pchar.rank) * 750);
			pchar.GenQuest.Governor.Group1.day = GetDataDay();
			dialog.text = "Tenho informações confiáveis de que um certo capitão marcou uma transação com contrabandistas para vender alguns escravos. Como deve saber, tais negócios feitos por particulares em nossas colônias são considerados contrabando.\nO problema é que não sei nem a hora exata, nem a data, nem o local onde os contrabandistas vão se encontrar. Tudo o que se sabe é que essa transação criminosa vai acontecer nos próximos três dias em nossa ilha. Para piorar, todos os meus navios de patrulha estão em reparo ou ocupados em outras missões e não podem caçar esses canalhas.\nSugiro que assuma essa tarefa – encontre os contrabandistas e lide com eles da forma mais decisiva possível, dê um exemplo a todos. Está pronto para essa missão?";
			link.l1 = "Estou pronto, "+GetAddress_FormToNPC(NPChar)+". Diga-me, você tem alguma informação adicional? Como o nome do capitão, o nome ou o tipo do navio dele?";
		    link.l1.go = "CustomPatrol_agree";
			link.l2 = "Hum... Não, acho que vou deixar passar.";
		    link.l2.go = "All_disagree";
		break;
		
		case "CustomPatrol_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.CustomPatrol.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "Minha fonte acabou de me informar que um acordo está sendo preparado e será concluído. É isso. Então, apenas fique de olho em todos os navios suspeitos nas nossas águas. Se tiver sucesso, vou lhe pagar uma quantia de "+FindRussianMoneyString(sti(pchar.GenQuest.CustomPatrol.Money))+"\nAlém disso, dadas as circunstâncias, autorizo você a recolher toda a carga de contrabando que conseguir encontrar. Extraoficialmente, é claro, desde que não a venda em nossa cidade.";
			link.l1 = "Bastante generoso. Certo, vou começar a patrulhar as águas da sua colônia, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "exit";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, 4, false);
			pchar.quest.CustomPatrol.win_condition.l1 = "location";
			pchar.quest.CustomPatrol.win_condition.l1.location = pchar.GenQuest.CustomPatrol.Island;
			pchar.quest.CustomPatrol.win_condition.l2 = "Timer";
			pchar.quest.CustomPatrol.win_condition.l2.date.hour  = sti(GetTime()+rand(8));
			pchar.quest.CustomPatrol.win_condition.l2.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.CustomPatrol.LoginDay));
			pchar.quest.CustomPatrol.win_condition.l2.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.CustomPatrol.LoginDay));
			pchar.quest.CustomPatrol.win_condition.l2.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.CustomPatrol.LoginDay));
			pchar.quest.CustomPatrol.function = "CustomPatrol_CreateShip";
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "11");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.CustomPatrol.Money)));
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Найти дезертира
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "FindFugitive":
			//установка параметров
			pchar.GenQuest.questName = "FindFugitive"; //тип квеста
			pchar.GenQuest.FindFugitive.Startcity = npchar.city;
			pchar.GenQuest.FindFugitive.City = SelectFugitiveCity();
			pchar.GenQuest.FindFugitive.Chance = rand(2);
			pchar.GenQuest.FindFugitive.Name = GenerateRandomName(sti(npchar.Nation), "man");
			pchar.GenQuest.FindFugitive.Money = ((hrand(5)+hrand(6, "1")+4)*600)+9600+(sti(pchar.rank)*900);
			sText = SelectFugitiveText();
			log_testinfo(pchar.GenQuest.FindFugitive.City);
			log_testinfo(FindRussianDaysString(sti(pchar.GenQuest.FindFugitive.Chance)));
			pchar.GenQuest.Governor.Group2.day = GetDataDay();
			dialog.text = "Vou te contar tudo em detalhes. Aconteceu uma história muito feia - "+sText+". Ao conversar com seus colegas e amigos, acreditamos, não sem razão, que o desertor se refugiou entre os piratas em um dos seus assentamentos\nSugiro que você visite o covil dos piratas, encontre o fugitivo, prenda-o e traga-o até aqui. A deserção é uma ofensa grave e não pode ficar impune. Você está pronto para assumir essa missão?";
			link.l1 = "Estou pronto, "+GetAddress_FormToNPC(NPChar)+". Você pode me dizer o nome do desertor?";
		    link.l1.go = "FindFugitive_agree";
			link.l2 = "Hum... Não, acho que vou deixar passar.";
		    link.l2.go = "All_disagree";
		break;
		
		case "FindFugitive_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.FindFugitive.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "Sim, claro. O nome dele é "+pchar.GenQuest.FindFugitive.Name+". Duvido muito que ele esteja usando o uniforme, então preste atenção em todo tipo de canalha. Dou-lhe um mês para a busca, pois temo que depois disso não fará mais sentido procurá-lo. Se tiver sucesso, lhe pagarei uma quantia de "+FindRussianMoneyString(sti(pchar.GenQuest.FindFugitive.Money))+".";
			link.l1 = "Não vou perder mais tempo, "+GetAddress_FormToNPC(NPChar)+"! Vou zarpar imediatamente.";
			link.l1.go = "exit";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, 30, false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "12");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.FindFugitive.Money)));
			AddQuestUserData("MayorsQuestsList", "sName", pchar.GenQuest.FindFugitive.Name);
			//создаем дезертира
			sld = GetCharacter(NPC_GenerateCharacter("Fugitive", "citiz_"+(21+rand(9)), "man", "man", sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, sti(npchar.nation), 30, true, "soldier"));
			SetFantomParamFromRank(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true);
			sld.name = pchar.GenQuest.FindFugitive.Name;
			sld.lastname = "";
			sld.dialog.FileName = "MayorQuests_dialog.c";
			sld.greeting = "marginal";
		break;
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Проникновение во враждебный город
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "Intelligence":
			pchar.GenQuest.Governor.Group3.day = GetDataDay();
			dialog.text = "Entendo. Talvez uma recompensa de "+FindRussianMoneyString(sti(pchar.GenQuest.Intelligence.Money))+" será um bom incentivo para você.";
			link.l1 = "É, paga bem... Vou aceitar essa missão.";
		    link.l1.go = "Intelligence_agree";
			link.l2 = "Hum... Não, acho que vou recusar. É perigoso demais.";
		    link.l2.go = "All_disagree";
		break;
		case "Intelligence_agree":
			if (pchar.GenQuest.Intelligence.City == "none" || isBadReputation(pchar, 30)) //на всякий случай
			{
				dialog.text = "Embora eu não possa dizer que confio totalmente em você... Acho que não vou lhe dar esta missão.";
				link.l1 = "Ah, que pena... Mas não há nada que eu possa fazer.";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "GenQuest." + pchar.GenQuest.questName);
			}
			else
			{
				npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
				pchar.GenQuest.questName = "Intelligence"; //тип квеста
				sTemp = pchar.GenQuest.Intelligence.City;
				switch (rand(4))
				{
					case 0:	sTemp += "_Priest";		break;
					case 1:	sTemp += "_trader";		break;
					case 2:	sTemp += "_shipyarder"; break;
					case 3:	sTemp += "_usurer";	    break;
					case 4:	sTemp += "_PortMan";	break;
				}
				pchar.GenQuest.Intelligence.SpyId = sTemp; //Id нашего шпиона в городе
				dialog.text = "Ótimo! Agora, vamos ao que interessa. Em "+XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Dat")+" você precisa encontrar um local "+GetWorkTypeOfMan(&characters[GetCharacterIndex(sTemp)],"Gen")+", o nome dele é "+GetFullName(&characters[GetCharacterIndex(sTemp)])+". Você dirá meu nome a ele, e ele lhe entregará um pacote de documentos. Por trazer esse pacote até minhas mãos, eu lhe darei "+FindRussianDaysString(sti(pchar.GenQuest.Intelligence.Terms))+". E lembre-se de que tudo deve ser feito em segredo. Se sua identidade for descoberta, o agente não vai arriscar tentar fazer contato. Está claro?";
				link.l1 = "Sim, entendi. "+GetAddress_FormToNPC(NPChar)+". Vou começar imediatamente.";
				link.l1.go = "exit";
				pchar.GenQuest.Intelligence.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
				SaveCurrentQuestDateParam("GenQuest.Intelligence"); //запись даты получения квеста
				ReOpenQuestHeader("MayorsQuestsList");
				AddQuestRecord("MayorsQuestsList", "6");
				AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
				AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
				AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Acc"));
				AddQuestUserData("MayorsQuestsList", "sIsland", XI_ConvertString(GetIslandByColony(&colonies[FindColony(pchar.GenQuest.Intelligence.City)])+"Dat"));
				AddQuestUserData("MayorsQuestsList", "sWho", GetWorkTypeOfMan(&characters[GetCharacterIndex(sTemp)], "Gen"));
				AddQuestUserData("MayorsQuestsList", "SpyName", GetFullName(&characters[GetCharacterIndex(sTemp)]));			
				AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.Intelligence.Terms)));
				AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Intelligence.Money)));
				AddQuestUserData("MayorsQuestsList", "sCity2", XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Dat"));
			}
		break;
		case "Intelligence_ExecuteLate":
			QuestName = pchar.GenQuest.questName;
			pchar.GenQuest.(QuestName).Money = sti(pchar.GenQuest.(QuestName).Money) / 2);
			dialog.text = RandPhraseSimple("Nada mal. Mas você não cumpriu o prazo, então vou ter que reduzir um pouco sua recompensa. Agora seu pagamento será "+FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money))+". Aqui está.","Isso é bom. Mas você não cumpriu o prazo, e eu estive esperando por essas cartas. Você atrapalhou meus planos, então sou obrigado a reduzir um pouco a sua recompensa. Ainda assim, fico satisfeito em lhe entregar o que lhe é devido - "+FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money))+". Aqui está.");
			link.l1 = "Eu não diria que isso me agrada, mas no fim das contas, os prazos realmente foram perdidos. Então não tenho do que reclamar, "+GetAddress_FormToNPC(NPChar)+".";
		    link.l1.go = "All_Execute_1";
			//--> слухи
			AddSimpleRumour(RandPhraseSimple("You know, governor " + GetFullName(npchar) + " are not very pleased with the quickness of a captain " + GetMainCharacterNameGen() + ".", 
				"Governor " + GetFullName(npchar) + " is not very pleased with captain " + GetMainCharacterNameDat() + ", "+ GetSexPhrase("who","who") +" complied with his orders, but did not in due time..."), sti(npchar.nation), 5, 1);
			//<-- слухи
		break;
		
		// -------------- общий набор для всех квестов мэра ------------------
		case "All_disagree":
			dialog.text = RandPhraseSimple("Hmm. Então, devo ter superestimado sua determinação, Capitão.","Você me decepciona, Capitão. Parece que realmente lhe faltam as qualidades necessárias para tais assuntos.","Da próxima vez, Capitão, pense duas vezes antes de desperdiçar meu tempo com conversa fiada.");
			link.l1 = "Me desculpe, "+GetAddress_FormToNPC(NPChar)+", mas não posso aceitar esse trabalho.";
		    link.l1.go = "exit";
			//ChangeCharacterComplexReputation(pchar,"nobility", -2);
			
			if (CheckAttribute(pchar, "GenQuest.questName"))
			{
				QuestName = pchar.GenQuest.questName;
				DeleteAttribute(pchar, "GenQuest." + QuestName);
				DeleteAttribute(pchar, "GenQuest.questName");
			}
		break;
		case "All_Late":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple("Bem, muito ruim - o que mais posso dizer. Eu confiei em você - e agora vejo que só perdi meu tempo. Estou decepcionado.","Bem, devo dizer que estou profundamente decepcionado com você... Sempre há pessoas em minha residência prontas para fazer esse tipo de serviço para mim – e eu perdi meu tempo com você. Fazer o quê...");
			link.l1 = "Me desculpe, "+GetAddress_FormToNPC(NPChar)+", eu fiz tudo o que pude.";
		    link.l1.go = "exit";
			//--> слухи
			AddSimpleRumour(LinkRandPhrase("You know, governor " + GetFullName(npchar) + " is very displeased with captain " + GetMainCharacterNameDat() + ". Just imagine - he failed to fulfill his assignment in time!", 
				"Governor " + GetFullName(npchar) + " is slightly annoyed that a captain " + GetFullName(pchar) + " put his shoulder to the wheel, but fail to fulfill his assignment in time. That's too bad...", 
				"I heard that governor " + GetFullName(npchar) + " is very displeased with you, captain " + GetFullName(pchar) + ", since you failed to meet the deadline while trying to fulfill his assignment."), sti(npchar.nation), 5, 1);
			//<-- слухи
			ChangeCharacterComplexReputation(pchar,"nobility", -4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			DeleteAttribute(pchar, "GenQuest." + QuestName);
			DeleteAttribute(pchar, "GenQuest.questName");
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; //реплику вертаем
			SaveCurrentNpcQuestDateParam(npchar, "work_date"); //сразу ещё один не даем
			CloseQuestHeader("MayorsQuestsList");
		break;
		case "All_Found":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple("Estou simplesmente chocado! Você conseguiu localizar seu alvo, mas não se preocupou em garantir sua vantagem – isso é uma imprudência extrema. Estou decepcionado!","Bem, devo dizer que estou decepcionado com você... Encontrar seu alvo não basta – é preciso ter os meios para destruí-lo. Há muitos mercenários em minha residência sempre prontos para realizar esse tipo de serviço para mim. O que eu estava pensando quando recorri a você?");
			link.l1 = "Me desculpe, "+GetAddress_FormToNPC(NPChar)+", mas simplesmente não estou disposto a arriscar minha própria vida de forma imprudente.";
		    link.l1.go = "exit";
			//--> слухи
			AddSimpleRumour(LinkRandPhrase("You know, governor " + GetFullName(npchar) + " is very displeased with captain " + GetMainCharacterNameDat() + ". Imagine, "+ GetSexPhrase("he turned out to be a downright coward","she turned out to be a downright coward") +"!", 
				"Governor " + GetFullName(npchar) + " is slightly annoyed that a captain " + GetFullName(pchar) + " took the job, but failed to carry it out because of their own indecision. Hee-hee, what wilt captains!", 
				"I heard that Governor " + GetFullName(npchar) + " very displeased with you, Captain " + GetFullName(pchar) + ". They say you're nothing but a coward"+ GetSexPhrase("","") +"..."), sti(npchar.nation), 5, 1);
			//<-- слухи
			ChangeCharacterComplexReputation(pchar,"nobility", -6);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			DeleteAttribute(pchar, "GenQuest." + QuestName);
			DeleteAttribute(pchar, "GenQuest.questName");
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; //реплику вертаем
			SaveCurrentNpcQuestDateParam(npchar, "work_date"); //сразу ещё один не даем
			CloseQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "21");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
		break;
		case "All_Execute":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple("Ótima notícia! Bem, está na hora de acertarmos as contas. Sua recompensa será "+FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money))+". Aqui está.","Excelente! Isso é o melhor para todos... Bem, fico feliz em lhe entregar sua merecida recompensa - "+FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money))+". Aqui está.");
			link.l1 = "Obrigado, "+GetAddress_FormToNPC(NPChar)+", "+RandPhraseSimple("Foi um prazer fazer negócios com você!","Fico agradavelmente surpreso com a clareza dos assentamentos.");
		    link.l1.go = "All_Execute_1";
			//--> слухи
			AddSimpleRumour(LinkRandPhrase("You know, governor " + GetFullName(npchar) + "  was praising for diligence"+ GetSexPhrase("a captain","a young lady") +" " + GetMainCharacterNameGen() + ".", 
				"Governor " + GetFullName(npchar) + " is praising captain " + GetMainCharacterNameGen() + ", "+ GetSexPhrase("he","she") +" is always a flawless performer when it comes to governor's assignments. An irreplaceable person for the governor, I say...", 
				"I heard that governor " + GetFullName(npchar) + " is very much pleased with you, captain " + GetFullName(pchar) + ". He defines you as a very careful and thorough officer. That's very nice to hear, captain..."), sti(npchar.nation), 5, 1);
			//<-- слухи
		break;
		case "All_Execute_1":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple("Muito bem. Pode voltar para me ver – talvez eu tenha outro trabalho para você.","Ótimo, então! Acho que vou te oferecer esses trabalhos de novo.");
			link.l1 = RandPhraseSimple("Ótimo.","Certo.");
		    link.l1.go = "exit";
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.(QuestName).Money));
			CloseQuestHeader("MayorsQuestsList");
			ChangeCharacterComplexReputation(pchar,"nobility", 4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(PChar, "Leadership", 180);
			OfficersReaction("good"); // dlc
			
			DeleteAttribute(pchar, "GenQuest." + QuestName);
			DeleteAttribute(pchar, "GenQuest.questName");
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; //реплику вертаем
			SaveCurrentNpcQuestDateParam(npchar, "work_date"); //сразу ещё один не даем
			// инкремент в базу заданий мэров
			sTemp = npchar.City;
			if (!CheckAttribute(pchar, "GenQuest.MayorQuestsList." + sTemp)) pchar.GenQuest.MayorQuestsList.(sTemp) = 0;
			pchar.GenQuest.MayorQuestsList.(sTemp) = sti(pchar.GenQuest.MayorQuestsList.(sTemp)) + 1;
		break;
//<-- осады homo
		case "siege_task":
            makearef(aData, NullCharacter.Siege);
            aData.HelpColony = true;
			dialog.text = "Nesses tempos difíceis, qualquer ajuda será muito bem-vinda. Aceitamos seu apoio – ajude-nos a defender nossa colônia e você será recompensado.";
			link.l1 = "Então não vamos perder tempo.";
		    link.l1.go = "exit";
		break;
		
		//Jason --> Бремя гасконца
		case "Sharlie":
			dialog.text = "Você está procurando por Michel de Monper? Interessante... E para que você precisa dele?";
			link.l1 = "Eu sou irmão dele. Meu pai me disse que Michel está com problemas e precisa de ajuda, então eu...";
			link.l1.go = "Sharlie_1";			
		break;
		
		case "Sharlie_1":
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "First time";
			DelLandQuestMark(sld);
			dialog.text = "É mesmo? Não me lembro de Monsieur de Monper ter irmãos... Sabe, monsieur, você me parece muito suspeito... então vou prendê-lo para uma investigação mais detalhada. Tenente! Detenha este homem!";
			link.l1 = "Mas Vossa Senhoria!";
			link.l1.go = "exit";
			if (GetCharacterIndex("SharlieKnown") != -1)
			{
				sld = characterFromId("SharlieKnown");
				sld.lifeday = 0;
			}	
			AddDialogExitQuestFunction("Sharlie_enterSoldiers");
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Sharlie_2":
			QuestPointerDelLoc("Fortfrance_town", "reload", "reload3_back");
			dialog.text = "E ainda assim, gostaria de me redimir. Aqui - por favor, aceite esta espada, esta pistola e esta armadura leve - é um presente meu para você. Acredito que vai achar tudo isso bem útil.";
			link.l1 = "Obrigado, monsieur. Considerando que seus guardas levaram tudo o que eu tinha, isso vai ser muito útil.";
			// belamour legendary edition -->
			link.l1.go = "Sharlie_5";		
			link.l2 = "Obrigado, monsieur. Existe alguma outra maneira de me ajudar? De cavalheiro para cavalheiro? Você mesmo pode ver em que situação terrível eu estou!";
			link.l2.go = "Sharlie_3";	
		break;
		
		case "Sharlie_3":
			dialog.text = "Bem, Charles... (revirando a escrivaninha) Aqui, fique com este amuleto sagrado para lhe trazer sorte. Não posso ajudar mais, desculpe. Aqui nas colônias, você vai ter que contar apenas consigo mesmo.";
			link.l1 = "Bem, pelo menos é alguma coisa. Obrigado pelo presente, senhor.";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Commerce", 10);
			Log_Info("You'have received equipment");
			Log_Info("You have received the 'Holy Water' amulet");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "amulet_7");
			TakeNItems(pchar, "blade_08", 1);
			if(GetCharacterEquipByGroup(pchar, BLADE_ITEM_TYPE) == "")
			{
				EquipCharacterbyItem(pchar, "blade_08");
			}
			TakeNItems(pchar, "pistol1", 1);
			TakeNItems(pchar, "cirass5", 1);
			pchar.quest.Sharlie_PardonOver.over = "yes";
			DeleteAttribute(pchar, "questTemp.Sharlie.Pardon");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
			{
				DelLandQuestMark(npchar);
			}
			if(CheckAttribute(pchar,"systeminfo.tutorial.Amulet"))
			{
				DoQuestFunctionDelay("Tutorial_Amulet", 0.1);
			}
		break;
		
		case "Sharlie_5":
			// <-- legendary edition
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 10);
			Log_Info("You'have received equipment");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "blade_08", 1);
			if(GetCharacterEquipByGroup(pchar, BLADE_ITEM_TYPE) == "")
			{
				EquipCharacterbyItem(pchar, "blade_08");
			}
			TakeNItems(pchar, "pistol1", 1);
			TakeNItems(pchar, "cirass5", 1);
			pchar.quest.Sharlie_PardonOver.over = "yes";
			DeleteAttribute(pchar, "questTemp.Sharlie.Pardon");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
			{
				DelLandQuestMark(npchar);
			}
		break;
		//<-- Бремя гасконца
		
		//Sinistra --> Травля крысы		
		case "TK_TravlyaKrys":
			dialog.text = "Que reviravolta do destino, Charles... Não é todo dia que vemos alguém subir tão rápido no nosso mundo. Tenho a impressão de que você e eu vamos nos dar muito bem.";
			link.l1 = "Seria uma honra. Talvez tenha alguma tarefa para mim?";
			link.l1.go = "TK_TravlyaKrys_2";
			DeleteAttribute(pchar, "questTemp.TK_TravlyaKrys");
			PChar.quest.TK_Timer.over = "yes";
		break;
		
		case "TK_TravlyaKrys_2":
			dialog.text = "Com certeza! Ainda mais depois do seu sucesso enfrentando um dos piratas de Barbazon perto de Le François...";
			link.l1 = "Não posso dizer que tenho boas lembranças daquele encontro. Quem exatamente é Barbazon?";
			link.l1.go = "TK_TravlyaKrys_3";
		break;
		
		case "TK_TravlyaKrys_3":
			dialog.text = "Jacques Barbazon, também conhecido como Jacques o Justo, lidera o covil de bandidos em Le François. Ele é um dos chamados barões piratas, causando problemas com pirataria e contrabando nas Pequenas Antilhas. É um criminoso notório, e pode apostar, um dia ele vai acabar na forca em St. Pierre!";
			link.l1 = "Com licença, mas você não é a verdadeira autoridade na Martinica? Não pode simplesmente acabar com aquele ninho? Eu estive lá, e acredite, não tem nada de impressionante.";
			link.l1.go = "TK_TravlyaKrys_4";
		break;
		
		case "TK_TravlyaKrys_4":
			dialog.text = "Eu aconselharia você a não se gabar do seu conhecimento sobre os cantos menos respeitáveis da minha ilha, Charles. Isso não combina com um nobre. Quanto à sua pergunta\nNem tudo no nosso mundo se resolve com força bruta. Existem interesses políticos e comerciais em jogo. Mas não vamos entrar em detalhes desnecessários: tenho uma tarefa específica que exige um pouco de força bruta.";
			link.l1 = "Por favor, continue.";
			link.l1.go = "TK_TravlyaKrys_5";
		break;
		
		case "TK_TravlyaKrys_5":
			dialog.text = "Barbazon atrai bandos de piratas de pouca expressão, famintos por ouro fácil. Às vezes, ele joga uma isca para um deles só para ver todos brigarem por ela. De vez em quando, ele põe o sobrevivente para trabalhar, mas na maioria das vezes, ele os expulsa — e pode acreditar, não há nada mais perigoso do que um pirata desesperado à solta.";
			link.l1 = "Acho que entendi, mas não tenho certeza se estou à altura. Assumi o comando do meu navio há pouco tempo e ainda estou aprendendo como tudo funciona, por assim dizer...";
			link.l1.go = "TK_TravlyaKrys_6";
		break;
		
		case "TK_TravlyaKrys_6":
			dialog.text = "Besteira! Você já provou o sabor da vitória – mais do que muitos dos preguiçosos entre meus oficiais! A cidade vai te recompensar com cinco mil pesos por afundar mais um dos ratos do Barbazon, livre de impostos. Oito mil se trouxer o pirata vivo – para uma execução adequada, é claro.";
			link.l1 = "Eu com certeza preciso desse dinheiro. Onde posso encontrar esse pirata?";
			link.l1.go = "TK_TravlyaKrys_7";
			link.l2 = "Desculpe, mas acho que ainda não estou pronto para esse tipo de tarefa.";
			link.l2.go = "TK_TravlyaKrys_Otkaz";
		break;
		
		case "TK_TravlyaKrys_Otkaz":
			dialog.text = "Que pena, Charles. Nesse caso, não vou tomar mais o seu tempo.";
			link.l1 = "Adeus, Vossa Excelência.";
			link.l1.go = "exit";
		break;
		
		case "TK_TravlyaKrys_7":
			dialog.text = "Fico feliz que você esteja conosco, Charles. Nossos relatórios de inteligência indicam que o Hater, uma escuna, está se preparando para partir de Le François. Não podemos perder tempo, então zarpe e vá atrás dele. Não se preocupe, meu amigo, você vai conseguir.";
			link.l1 = "Com a graça de Deus, Vossa Excelência.";
			link.l1.go = "TK_TravlyaKrys_8";			
		break;
		
		case "TK_TravlyaKrys_8":
			DialogExit();
			SetQuestHeader("TravlyaKrys");
			AddQuestRecord("TravlyaKrys", "1");
			
			sld = GetCharacter(NPC_GenerateCharacter("TK_Heiter", "mercen_8", "man", "man", sti(PChar.rank), PIRATE, -1, true, "pirate"));
			sld.name = "Daniel";
			sld.lastname = "Montbars";
			FantomMakeSmallSailor(sld, SHIP_LUGGER, "Hater", CANNON_TYPE_CANNON_LBS3, 20, 40, 20, 25, 35);
			SetCharacterGoods(sld, GOOD_GOLD, 1);
			sld.AlwaysEnemy = true;
			sld.AlwaysSandbankManeuver = true;
			sld.DontRansackCaptain = true;
			
			Group_FindOrCreateGroup("HeiterAttack");
			Group_SetType("HeiterAttack", "pirate");
			Group_AddCharacter("HeiterAttack", "TK_Heiter");

			Group_SetGroupCommander("HeiterAttack", "TK_Heiter");
			Group_SetTaskAttack("HeiterAttack", PLAYER_GROUP);
			Group_SetAddress("HeiterAttack", "Martinique", "Quest_Ships", "Quest_Ship_6");
			Group_LockTask("HeiterAttack");
			
			PChar.quest.TK_Potopil.win_condition.l1 = "Character_sink";
			PChar.quest.TK_Potopil.win_condition.l1.character = "TK_Heiter";
			PChar.quest.TK_Potopil.win_condition = "TK_Potopil";
		break;
		//<-- Травля крысы
		
		//Jason --> Португалец
		case "Portugal":
			dialog.text = "Claro que pode, capitão! É por isso que lhe incomodei.";
			link.l1 = "Então estou todo ouvidos.";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "Pescadores locais viram uma embarcação estranha perto da ilha na noite passada. Dizem que era um enorme navio de guerra, como um navio de linha, sem bandeiras ou lanternas de sinalização. Não acredito que esse navio seja realmente maior do que uma fragata, mas mesmo assim já seria demais!";
			link.l1 = "O medo transforma pequenos problemas em grandes montanhas, isso é certo... mas qual é o sentido disso?";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			dialog.text = "Recorro a você, capitão. Meus parceiros comerciais estão assustados com esses boatos – acham que se trata de piratas ou corsários espanhóis, e isso prejudica os negócios. O pior de tudo é que não há navios de guerra na colônia no momento, apenas alguns saveiros para proteção e uma escuna velha, boa só para caçar contrabandistas.\nNão posso deixar isso sem atenção... De qualquer forma, agora metade da cidade já ouviu falar do navio misterioso! Por favor, una-se a nós com seu navio para ajudar a encontrá-lo – conheço você como um capitão honrado, e mesmo que seja só uma fragata, seus canhões podem convencê-la a procurar presas em outro lugar!";
			link.l1 = "Monsieur... Na verdade, eu tinha outros planos...";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			dialog.text = "Por favor, capitão! Só por alguns dias, até que esses boatos inquietantes se acalmem! E, claro, você será recompensado pelo seu tempo. Dez mil peças de oito lhe servem?";
			link.l1 = "Hmm... mas, Vossa Excelência, eu...";
			link.l1.go = "Portugal_4";
		break;
		
		case "Portugal_4":
			dialog.text = "E nós vamos dobrar esse valor, caso você realmente enfrente esse navio em combate, e triplicar se conseguir afundá-lo! Então, o que me diz?";
			link.l1 = "Certo, eu já estava planejando ficar aqui por alguns dias mesmo.";
			link.l1.go = "Portugal_5";
		break;
		
		case "Portugal_5":
			dialog.text = "Excelente, eu nunca duvidei de você, monsieur capitão! Lembre-se – apenas dois dias em nossas águas, e o dinheiro será seu. E se for forçado a entrar em batalha, será pago conforme o resultado.";
			link.l1 = "Entendi, excelência. Temos um acordo, e estou voltando para o meu navio agora.";
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_6":
			dialog.text = "Estarei esperando pelo seu retorno, capitão!";
			link.l1 = "Permita-me retirar-me.";
			link.l1.go = "Portugal_7";
		break;
		
		case "Portugal_7":
			DialogExit();
			AddQuestRecord("Portugal", "10");
			NextDiag.CurrentNode = "Portugal_8";
			LocatorReloadEnterDisable("Fortfrance_town", "reload1_back", false);
			LocatorReloadEnterDisable("Fortfrance_town", "reload2_back", false);
			LocatorReloadEnterDisable("Fortfrance_town", "gate_back", false);//открыть выходы из города
			bDisableFastReload = true;//закрыть быстрый переход
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			pchar.quest.Portugal_Seapatrol.win_condition.l1 = "location";
			pchar.quest.Portugal_Seapatrol.win_condition.l1.location = "Martinique";
			pchar.quest.Portugal_Seapatrol.function = "PortugalSeapatrolGo";
			pchar.quest.Portugal_SeapatrolAvendel.win_condition.l1 = "location";
			pchar.quest.Portugal_SeapatrolAvendel.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Portugal_SeapatrolAvendel.function = "AvendelSpeach";
		break;
		
		case "Portugal_8":
			dialog.text = "Capitão, acredito que tínhamos um acordo de que você patrulharia nossas águas costeiras por dois dias!";
			link.l1 = "Sim, claro. Eu me lembro disso.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Portugal_8";
		break;
		
		case "Portugal_9":
			dialog.text = "Muito bem, você cumpriu sua parte do acordo. Aqui está sua recompensa - 10.000 pesos, como combinamos.";
			link.l1 = "Muito obrigado! Como pode ver, suas preocupações eram infundadas. Boa sorte para você!";
			link.l1.go = "Portugal_10";
		break;
		
		case "Portugal_10":
			DialogExit();
			AddMoneyToCharacter(pchar, 10000);
			NextDiag.CurrentNode = "First time";
			pchar.quest.MartiniqueGovernorOver.over = "yes"; //снять таймер
		break;
		//<-- Португалец
		
		// Warship, 16.05.11. Генер "Правосудие на продажу".
		case "JusticeOnSale_1":
			dialog.text = "Oh "+GetAddress_Form(NPChar)+", você me surpreendeu! Aqueles canalhas ficaram mesmo tão ousados? Preciso avisar o comandante imediatamente e enviar uma patrulha costeira para lá!";
			link.l1 = "Fico feliz por ter ajudado. Posso me retirar agora?";
			link.l1.go = "JusticeOnSale_2";
			
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait");
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.PrisonWait");
			
			DeleteQuestCondition("JusticeOnSale_MapEnter");
		break;
		
		case "JusticeOnSale_2":
			dialog.text = "Claro, capitão. Aqui – por favor, aceite esta modesta recompensa de minha parte pessoalmente.";
			link.l1 = "Obrigado.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("JusticeOnSale_DlgExitAfterMayor_1");
		break;
		
		case "JusticeOnSale_4":
			dialog.text = "Você tem razão, capitão! Não podemos simplesmente deixar assim! Eu gostaria de pedir que você vá até "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Dat")+", encontre o navio deles e prenda toda a quadrilha! Se resistirem, use a força e não hesite!";
			link.l1 = "Permita-me retirar-me.";
			link.l1.go = "JusticeOnSale_5";
		break;
		
		case "JusticeOnSale_5":
			dialog.text = "Agora vá. Navegue até lá e garanta que ninguém escape da justiça. Acho que você vai precisar desembarcar na praia primeiro, e depois pode cuidar do navio.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("JusticeOnSale_DlgExitAfterMayor_2");
		break;
		
		case "JusticeOnSale_7":
			dialog.text = "Muito obrigado pela sua ajuda. Aqueles canalhas tiveram o que mereciam. Por favor, aceite esta modesta recompensa, pessoalmente de mim. Aprecio muito a ordem e a paz na minha cidade.";
			link.l1 = "...";
			link.l1.go = "JusticeOnSale_8";
		break;
		
		case "JusticeOnSale_8":
			AddMoneyToCharacter(PChar, sti(PChar.rank) * 300 + hrand(1000));
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale");
			DialogExit();
		break;
		//<-- Правосудие на продажу
		
			//--> Jason регата
		case "Regata":
			// belamour legendary edition -->
			if(sti(pchar.rank) < 15)
			{
				Notification_Level(false, 15);
				dialog.text = "Ah, maravilhoso, bom te ver, capitão! Ouvi falar dos seus talentos, mas volte quando estiver realmente pronto.";
				link.l1 = "Sim, claro. Como quiser.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Ah, excelente, que bom ver você, capitão! Chegou na hora certa – a regata vai começar em poucos dias. Já leu as regras da regata? Um oficial deve tê-las entregue a você.";
				link.l1 = "Sim, senhor, eu fiz.";
				link.l1.go = "Regata_1";
				RemoveItems(PChar, "letter_open", 1);//уберем письмо
				DeleteAttribute(pchar, "questTemp.Regata.ToPortRoyal"); // patch-5
			}
		break;
		
		case "Regata_1":
			dialog.text = "E você já preparou 50.000 pesos – sua taxa de entrada, que vai contribuir para o prêmio?";
			if (makeint(Pchar.money) >= 50000)
			{
				link.l1 = "Sim, claro. Por favor, aceite minha recompensa.";
				link.l1.go = "Regata_2";
			}
			link.l2 = "Estou um pouco sem dinheiro no momento. Mas com certeza vou conseguir juntar o valor necessário.";
			link.l2.go = "Regata_nomoney";
		break;
		
		case "Regata_2":
			dialog.text = "Very good. If you win, you'll get your money back fivefold. Now you need to become better acquainted with the rules of the regatta.\nYou can learn all the details from Sir Henry Stivenson; he should be in one of the rooms in the residence. Go to him—he'll explain everything.";
			link.l1 = "Certo. Vou fazer exatamente isso.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -50000);
			pchar.quest.Regata_Guber.win_condition.l1 = "location";
			pchar.quest.Regata_Guber.win_condition.l1.location = "Portroyal_Roomtownhall";
			pchar.quest.Regata_Guber.function = "PrepareToRegataInPortroyal";
			pchar.questTemp.Regata.Begin = "true";
			NextDiag.TempNode = "First time";
		break;
		
		case "Regata_nomoney":
			dialog.text = "Tudo bem, mas por favor, não demore muito, Capitão. A regata começa em breve.";
			link.l1 = "Entendi. Vou tentar trazer o dinheiro para você assim que eu puder.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_1";
			pchar.questTemp.Regata.nomoney = "true";
		break;
		
		//регата-финал
		case "Regata_Final":
			dialog.text = "Aha! E aqui está o vencedor da regata! Bom dia, Capitão "+GetFullName(pchar)+"! Permita-me parabenizá-lo por esse sucesso tão merecido! Os vencedores da regata sempre foram populares nas colônias inglesas – e com razão.";
			link.l1 = "Obrigado, senhor!";
			link.l1.go = "Regata_complete";
		break;
		
		case "Regata_complete":
			dialog.text = "Agora vamos para a parte mais agradável - a cerimônia de premiação. O primeiro prêmio é de 250.000 pesos. Parabéns!";
			link.l1 = "Obrigado!";
			link.l1.go = "Regata_complete_1";
		break;
		
		case "Regata_complete_1":
			AddMoneyToCharacter(pchar, 250000);
			// belamour legendary edition в регате только один приз -->
			GiveItem2Character(pchar, "blade_26");
			GiveItem2Character(pchar, "cirass4");
			GiveItem2Character(pchar, "bussol");
			
			dialog.text = "Além disso, você receberá um conjunto de prêmios valiosos: a lendária espada de aço de Toledo 'Asoleda', uma armadura milanesa e uma bússola de qualidade. Tudo seu.";
			// <-- legendary edition
			link.l1 = "Fico muito feliz, senhor. Sinceramente, não esperava tamanha generosidade.";
			link.l1.go = "Regata_complete_2";
		break;
		
		case "Regata_complete_2":
			dialog.text = "Em nome de todos os súditos das colônias inglesas, agradeço por participar da regata e mais uma vez o parabenizo pela vitória! Se você fez uma aposta, procure Sir Henry Stevenson para receber seus ganhos, caso ainda não tenha feito isso. Boa sorte para você, capitão!";
			link.l1 = "Muito obrigado por suas gentis palavras, senhor! Permita-me também agradecer pela oportunidade de participar de um evento tão grandioso. Agora, por favor, permita-me retirar-me.";
			link.l1.go = "Regata_complete_3";
		break;
		
		case "Regata_complete_3":
			DialogExit();
			NextDiag.CurrentNode = "First time";
		break;
		//<-- регата
	}
}

string GetGangLocation(ref npchar)
{
    int n;
	string island = GetArealByCityName(npchar.city);
	string LocationId, sAreal;
	int storeArray[2];
	SetArraySize(&storeArray, MAX_LOCATIONS);  
    int howStore = 0;

	for(n=0; n<MAX_LOCATIONS; n++)
	{				
		if (GiveArealByLocation(&locations[n]) == island)
		{			
			//==> на всякий случай
			if (CheckAttribute(&locations[n], "DisableEncounters") && locations[n].DisableEncounters == true) continue;
			LocationId = locations[n].id;
			if (findsubstr(LocationId, "jungle" , 0) != -1 || findsubstr(LocationId, "Shore" , 0) != -1 || findsubstr(LocationId, "CaveEntrance" , 0) != -1)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	n = storeArray[hrand(howStore-1)];
	return locations[n].id;
}

string GetSpyLocation(ref npchar)
{
    aref	arCommon, arRld, arRld2;
    int	i, n, Qty, Qty2;
	string LocId; 
	string	storeArray [50];
	int howStore = 0;
    makearef(arRld, Locations[FindLocation(npchar.city + "_town")].reload);
	Qty = GetAttributesNum(arRld);
    if (CheckAttribute(pchar, "questTemp.jailCanMove.Deliver.locationId")) //если взят квест по доставке малявы
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2")
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	else
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2")
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	if (howStore == 0) return "none";
	LocId = storeArray[hrand(howStore-1)];
	SetOpenDoorCommonLoc(npchar.city, LocId); //открываем дверь
	for(n=0; n<MAX_CHARACTERS; n++)
	{
		if (CheckAttribute(&characters[n], "locations") && characters[n].locations == LocId) 
		{			
			characters[n].lifeDay = 0;
		}
	}
	return LocId;
}

string GetSpyColony(ref NPChar)
{
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;
	string sChrId;

	for(int n=0; n<MAX_COLONIES; n++)
	{
		// Rebbebion, чуть изменил функцию, чтобы условно испанцы не просили пробраться к испанцам, французы к французам и т.д
		if (colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && GetRelation2BaseNation(sti(colonies[n].nation)) == RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].id != npchar.City && colonies[n].nation != npchar.nation)
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	return colonies[storeArray[Rand(howStore-1)]].id;
}

int SelectCureerShipType()
{
	int iClass = 6;
	int iRank = sti(pchar.rank);
	
	if(iRank < 6) iClass = 6;
	if(iRank >= 6 && iRank < 12) iClass = 6 - rand(1);
	if(iRank >= 12 && iRank < 21) iClass = 5 - rand(1);
	if(iRank >= 21) iClass = 4 - rand(1);
	
	return GetRandomShipType(GetClassFlag(iClass), FLAG_SHIP_TYPE_RAIDER + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY);
}

int SelectPirateShipType()
{
	int iClass = 6;
	int iRank = sti(pchar.rank);
	
	if(iRank < 6) iClass = 6;
	if(iRank >= 6 && iRank < 12) iClass = 5;
	if(iRank >= 12 && iRank < 21) iClass = 4;
	if(iRank >= 21 && iRank < 30) iClass = 4 - rand(1);
	if(iRank >= 30) iClass = 2;
	
	return GetRandomShipType(GetClassFlag(iClass), FLAG_SHIP_TYPE_RAIDER + FLAG_SHIP_TYPE_UNIVERSAL + FLAG_SHIP_TYPE_WAR, FLAG_SHIP_NATION_ANY);
}

int SelectCustomPatrolShipType(int iFlagType)
{
	if(CheckAttribute(pchar, "questTemp.StatusCity"))
	{
		return SHIP_CAREERLUGGER;
	}
	
	int iClass = 6;
	int iRank = sti(pchar.rank);
	
	if(iRank < 6) iClass = 6;
	if(iRank >= 6 && iRank < 12) iClass = 6 - rand(1);
	if(iRank >= 12 && iRank < 21) iClass = 5 - rand(1);
	if(iRank >= 21) iClass = 4 - rand(1);
	
	return GetRandomShipType(GetClassFlag(iClass), iFlagType, FLAG_SHIP_NATION_ANY);
}

int SelectArsenalShipType(int iFlagType)
{
	int iClass = 6;
	int iRank = sti(pchar.rank);
	
	if(iRank < 6) iClass = 6;
	if(iRank >= 6 && iRank < 12) iClass = 6 - rand(1);
	if(iRank >= 12 && iRank < 21) iClass = 5 - rand(1);
	if(iRank >= 21 && iRank < 30) iClass = 4 - rand(1);
	if(iRank >= 30) iClass = 2;
	
	return GetRandomShipType(GetClassFlag(iClass), iFlagType, FLAG_SHIP_NATION_ANY);
}

string SelectPassText()
{
	string sText;
	switch (hrand(5))
	{
		case 0: sText = "That Judas, using his position, sold an important state secret to an enemy power."; break;
		case 1: sText = "That foul scoundrel killed his relative, a well-known and noble man, in order to inherit his fortune."; break;
		case 2: sText = "That foul scoundrel insulted my family and me personally."; break;
		case 3: sText = "This thieving rogue stole a decent sum of money from our city's treasury."; break;
		case 4: sText = "That villain is guilty of deaths of nearly a dozen of our citizens."; break;
		case 5: sText = "That rogue used his connection to take possession of a merchant vessel, and then he stole it and sold at the neighboring shipyard."; break;
	}
	return sText;
}

string SelectFugitiveCity()
{
	string sCity;
	switch (rand(3))
	{
		case 0: sCity = "LaVega"; break;
		case 1: sCity = "PuertoPrincipe"; break;
		case 2: sCity = "LeFransua"; break;
		case 3: sCity = "FortOrange"; break;
	}
	return sCity;
}

string SelectFugitiveText()
{
	string sText;
	switch (hrand(5))
	{
		case 0: sText = "one of the junior officers in our garrison has deserted and left the colony on board of a merchant ship."; break;
		case 1: sText = "one of our officers deserted right on duty and escaped on board of a smuggler ship."; break;
		case 2: sText = "one of our naval officers serving on a patrol brig deserted for unknown reason, hijacked a long boat and disappeared on it."; break;
		case 3: sText = "one of our prison guards threw up his service for  unknown reason and left our colony aboard a private vessel."; break;
		case 4: sText = "one of the soldiers in our garrison abandoned his post while keeping guard, went to the cove and left this place aboard an unknown vessel."; break;
		case 5: sText = "one of our military officers, captain of a patrol lugger, abandoned his ship in the open sea and went south on a fishing long boat."; break;
	}
	return sText;
}
