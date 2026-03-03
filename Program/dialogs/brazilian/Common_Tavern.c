#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
#include "interface\ship.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Tavern\" + NPChar.City + "_Tavern.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06
	
	int iTest, iTemp;
	string sTemp;
	string NPCCity = NPChar.City;
    iTest = FindColony(NPChar.City); // город 
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	bool ok;
	
	if(!CheckAttribute(pchar, "questTemp.TavernVisit."+(NPCCity) )) 
	{
		pchar.questTemp.TavernVisit.(NPCCity) = true;
		pchar.questTemp.TavernVisit.counter = sti(pchar.questTemp.TavernVisit.counter) + 1;
		notification("First Tavern Visit " + XI_ConvertString(NPCCity + "TavernName"), "Drunk");
		AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 10.0);
	}	
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("O alarme soou na cidade, e todos estão à sua procura. Se eu fosse você, não ficaria aqui.","Todos os guardas da cidade estão vasculhando a cidade atrás de você. Eu não sou tolo e não vou falar com você!","Corra, "+GetSexPhrase("companheiro","moça")+", antes que os soldados te transformem em carne moída..."),LinkRandPhrase("O que você precisa, "+GetSexPhrase("canalha","fedelho")+"?! Os guardas da cidade já estão no seu encalço, você não vai longe"+GetSexPhrase(", pirata imundo!","")+"","Assassino, saia do meu estabelecimento agora! Guardas!","Eu não tenho medo de você, "+GetSexPhrase("canalha","rato")+"Em breve você será enforcado em nosso forte, não vai chegar muito longe..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, um alarme nunca é problema pra mim..."," Eles nunca vão me pegar. "),RandPhraseSimple("Cale a boca, "+GetWorkTypeOfMan(npchar,"")+", ou eu arranco sua língua!","Heh, "+GetWorkTypeOfMan(npchar,"")+", e todos eles lá - para pegar piratas! É o que eu te digo, amigo: fica quieto e não vai morrer..."));
				link.l1.go = "exit";
				break;
			}
			if (sti(pchar.GenQuest.Piratekill) > 20 && sti(npchar.nation) == PIRATE)
			{
				dialog.text = RandPhraseSimple("E é você, seu bastardo! Acha que estamos te servindo rum aqui? De jeito nenhum! Rapazes! Às armas! Matem esse canalha!","Quer uma bebida, pirata? Ha! Não! Agora vamos te mostrar como as coisas funcionam! Rapazes, desembainhem as espadas!");
				link.l1 = RandPhraseSimple("Hã? O quê?","Pare!");
				link.l1.go = "fight";
				bDisableFastReload = true;//закрыть переход
				pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
				pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
				pchar.quest.pirate_in_town.function = "TownPirate_battle";
				break;
			}
			//Jason, Бремя гасконца
			if(NPChar.City == "FortFrance")
			{
				if (!CheckAttribute(npchar, "quest.Rum") && CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.questTemp.Sharlie == "ship" && makeint(environment.time) > 5.0 && makeint(environment.time) < 19.0)
				{
					link.l1 = "Monsieur, estou procurando trabalho. Você tem algum serviço?";
					link.l1.go = "Sharlie_rum";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") && pchar.questTemp.Sharlie.Rum == "regard")
				{
					link.l1 = "Terminei sua tarefa. O barco com o rum foi entregue na Baía de Le François e passado para o seu pessoal.";
					link.l1.go = "Sharlie_rum_5";
					break;
				}
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "crew" && npchar.city == "FortFrance")
			{
				DelLandQuestMark(npchar);
				FreeSitLocator("FortFrance_tavern", "sit7");
				dialog.text = "Queria alguma coisa, monsieur?";
				Link.l1 = "Olá, estalajadeiro, preciso contratar uma tripulação para o meu navio. Você pode me ajudar com isso?";
				Link.l1.go = "Sharlie_crew";
				break;
			}
			
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "skiper" && npchar.city == "FortFrance")
			{
				DelLandQuestMark(npchar);
				dialog.text = "Olá de novo. O que deseja desta vez, monsieur?";
				Link.l1 = ""+npchar.name+", eu sei que estou incomodando, mas só mais uma pergunta. Preciso de um navegador — sabe onde posso encontrar um?";
				Link.l1.go = "Sharlie_skiper";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
    			dialog.text = "O que deseja, monsieur?";
				Link.l1 = "Eu esperava que você pudesse responder a algumas perguntas.";
				Link.l1.go = "quests";
				if(!CheckAttribute(pchar,"questTemp.TimeLock"))
				{
					link.l2 = "Gostaria de alugar um quarto.";
					link.l2.go = "room";
				}
				break;
			}			
			//Бремя гасконца
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "tavern" && npchar.city == "Tortuga")
			{
				dialog.text = "Que prazer vê-lo, senhor! Em que posso ajudar? Rum, conhaque, uísque escocês?";
				Link.l1 = "Quero uma garrafa do seu melhor vinho francês e a chave de um quarto.";
				Link.l1.go = "mtraxx_tortuga";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "room" && npchar.city == "Tortuga")
			{
				dialog.text = "Você já pagou, monsieur, seu quarto fica no andar de cima.";
				Link.l1 = "Merci.";
				Link.l1.go = "exit";
				break;
			}
			
			// Sinistra - Квест "Длинные тени старых грехов" ==>	
			if (CheckAttribute(pchar, "questTemp.DTSG_BasTerTavern") && npchar.city == "BasTer")
			{
				dialog.text = "Como posso servi-lo, Capitão? Depois do que aconteceu, deve estar querendo uma bebida.";
				Link.l1 = "Isso pode esperar. Na verdade, quero conversar sobre o que aconteceu.";
				Link.l1.go = "DTSG_BasTerTavern_1";
				DelLandQuestMark(npchar);
				break;
			}
			// <== Квест "Длинные тени старых грехов" - Sinistra
			
			//--> Торговля по закону
			if (CheckAttribute(pchar, "questTemp.TPZ_Start") && !CheckAttribute(pchar, "questTemp.TPZ_Tavern_1") && npchar.city == "BasTer")
			{
				dialog.text = "Me desculpe, "+GetAddress_Form(NPChar)+", mas hoje não posso lhe oferecer uma gota sequer de bebida.";
				Link.l1 = "O quê? Que tipo de taverna não pode oferecer nem uma gota de rum? Perdi alguma grande celebração que esvaziou seus barris?";
				Link.l1.go = "TPZ_Tavern_1";
				pchar.questTemp.TPZ_Tavern_1 = true;
				DelLandQuestMark(npchar);
				break;
			}
			//<-- Торговля по закону

			if(NPChar.quest.meeting == "0")
			{
				dialog.Text = GetNatPhrase(npchar,LinkRandPhrase("Bem-vindo à minha humilde taverna '"+XI_ConvertString(NPChar.City+"TavernName")+"', senhor. Fico feliz em vê-lo.","À sua disposição, senhor! Em nossa taverna '"+XI_ConvertString(NPChar.City+"TavernName")+" sempre ficamos felizes em receber novos visitantes.","Primeira vez aqui, senhor? Não hesite, aqui no '"+XI_ConvertString(NPChar.City+"TavernName")+"' você sempre se sente em casa!"),LinkRandPhrase("Entre, monsieur capitão. Não o reconheço, então deve ser sua primeira vez no '"+XI_ConvertString(NPChar.City+"TavernName")+"'."," Nunca te vi antes, monsieur. Vamos nos apresentar: eu sou "+GetFullName(npchar)+", o estalajadeiro de '"+XI_ConvertString(NPChar.City+"TavernName")+"'.","É um prazer receber nosso novo hóspede, Monsieur Capitão! Na minha taverna '"+XI_ConvertString(NPChar.City+"TavernName")+" Primeira rodada é sempre por conta da casa! Eu sou o dono deste lugar, "+GetFullName(npchar)+", lhe dá as boas-vindas."),LinkRandPhrase("Señor Capitão! Bem-vindo à taverna '"+XI_ConvertString(NPChar.City+"TavernName")+"'!","Oh, que hidalgo radiante veio visitar nossa taverna '"+XI_ConvertString(NPChar.City+"TavernName")+"'! É a sua primeira vez aqui, senhor?","Buenos días, senhor! Eu sou "+GetFullName(npchar)+", humilde proprietário do '"+XI_ConvertString(NPChar.City+"TavernName")+"', estamos felizes em recebê-lo aqui!"),LinkRandPhrase("Olá, mynheer kapitein. Eu sou o dono da taverna '"+XI_ConvertString(NPChar.City+"TavernName")+"'. Primeira vez se hospedando conosco?","Boa tarde, senhor. Bem-vindo à taverna '"+XI_ConvertString(NPChar.City+"TavernName")+"'.","Muito bom ver você, mynheer kapitein! Nossa própria taverna '"+XI_ConvertString(NPChar.City+"TavernName")+"' cumprimenta você! Rum, vinho, ou se me permite sugerir, temos um novo e travesso destilado holandês chamado gim?"));
				Link.l1 = LinkRandPhrase("Que lugar aconchegante você tem aqui... Permita-me apresentar - "+GetFullName(pchar)+", é um prazer conhecê-lo.",""+GetFullName(pchar)+", é um prazer conhecê-lo. Então, o que você pode me oferecer?","Meu nome é "+GetFullName(pchar)+" e eu sou novo neste porto. Me diga, pelo que esta taverna é mais conhecida?");
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_tavern")
				{
					dialog.text = "Ahoy, Rumba! Voltou de uma viagem ou está partindo para outra?";
					link.l1 = "Olá, "+npchar.name+". Só decidi passar por aqui.";
					Link.l1.go = "Helen_meeting";
					NPChar.quest.meeting = "1";
					break;
				}
				NPChar.quest.meeting = "1";
			}
			else
			{
				// Квестовый генератор священника. Квест №1. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_1.CurPortManColony + "_tavern")
		        {
		            if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NoMoneyToBarmen"))
		            {
		            	iTemp = sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen);
		            	dialog.Text = "Então, capitão, você trouxe para mim "+FindRussianMoneyString(iTemp)+".";
		            	if(sti(PChar.Money) >= iTemp)
		            	{
							link.l1 = "Sim, eu tenho. Aqui estão...";
							link.l1.go = "Tavern_ChurchGenQuest1_Node_4_1";
						}
						else
						{
							link.l1 = "Não, ainda não...";
							link.l1.go = "exit";
						}
		            }
		            else
		            {
		            	dialog.Text = "O que deseja, meu bom "+GetSexPhrase("senhor","senhora")+"?";
						link.l1 = "Uma garrafa de rum para meu amigo naquela mesa ali.";
						link.l1.go = "Tavern_ChurchGenQuest1_Node_1";
					}
					break;
				}
				// <-- Квестовый генератор священника. Квест №1.
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("Oh, ilustres convidados! Ei, você aí – dá licença e abre espaço para um capitão valente! E anda logo, antes que eu te jogue pra fora, haha!","Deus misericordioso do céu! Se não é "+GetFullName(pchar)+"! Acabei de receber uma nova remessa dos melhores vinhos, por favor, entre!","Oh, "+GetAddress_Form(NPChar)+", está tendo problemas? Deixe-me cuidar de você. Esta garrafa é por conta da casa. Pode confiar, é o melhor vinho da região..."),LinkRandPhrase("Oh, é o Capitão "+GetFullName(pchar)+"! Ei, você aí! Mostre um pouco de respeito ao bom capitão! Aqui não é curral! Me desculpe, capitão, claramente as mães deles nunca ensinaram boas maneiras.","Ora, ora, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Vamos ter uma longa noite, haha! Meninas, é melhor colocarem seus melhores vestidos!","Boa tarde, "+GetFullName(pchar)+", fico feliz em vê-lo! Por favor, senhor, tenho um pedido. Acabei de comprar mesas novas, então, por favor, nada de brigas esta noite."),LinkRandPhrase("Olá, capitão. Fique à vontade, mas lembre-se de que até o próprio Capitão Sharp respeita as regras no meu estabelecimento.","O-ho-ho! Olha só quem apareceu! É "+GetFullName(pchar)+" ele mesmo! E a gente já estava começando a ficar entediado com a sua ausência! Que tal contar uma aventura para o pessoal enquanto eu abro um novo barril de rum, capitão?","O-ho-ho! É "+GetFullName(pchar)+" você mesmo! Espero que não vá de novo atrair meus clientes para o alto-mar com histórias das suas grandes aventuras?")),LinkRandPhrase(LinkRandPhrase(""+GetFullName(pchar)+"! Este velho lobo do mar fica sempre feliz em ver você no seu estabelecimento! Por favor, senhor, sente-se e as moças vão cuidar de você!","Por favor, capitão, fique à vontade! Sempre um prazer receber meu hóspede favorito. O que vai beber?","Fico feliz em te ver de novo, "+GetFullName(pchar)+"! Gostaria de uma mesa só para você? Ou prefere sentar-se no balcão?"),LinkRandPhrase("Boa tarde, capitão. O ar está frio, permita-me lhe oferecer um excelente vinho quente que acabei de preparar, por conta da casa!","Olá, Capitão "+GetFullName(pchar)+"! Fico feliz que tenha vindo me visitar de novo. O que deseja?","Fico feliz em ter você, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Fico feliz que você frequente meu humilde estabelecimento! Fazemos de tudo para agradar."),LinkRandPhrase("Capitão! Seja muito bem-vindo, seja bem-vindo! Tenho aqui um magnífico d'Anjou digno do próprio rei Luís, e guardei especialmente para você!",""+GetFullName(pchar)+"! Que bom que você veio. Quer que eu mande esses ratos do mar embora, ou prefere que fiquem? Pode confiar, eu esvaziaria a taverna inteira só pra você!","Meu Deus, olha o Capitão "+GetFullName(pchar)+"! Ei, galanteadores - tragam a melhor toalha de mesa para a mesa do capitão!")));
				Link.l1 = pcharrepphrase(RandPhraseSimple(RandPhraseSimple("Ah, vejo que ainda sou lembrado por aqui... Sirva-me um copo, camarada, enquanto dou uma olhada em volta...","Calma, amigo, hoje estou de bom humor. Vamos começar com um rum, que tal?..."),RandPhraseSimple("Oh... você não está muito feliz por eu estar aqui? Espero ter ouvido errado, ha!","Ahoy. Espero que seu vinho seja melhor do que sua saudação. Caso contrário, posso ficar irritado, sabia...")),RandPhraseSimple(RandPhraseSimple("Sempre bom te ver, camarada. O que você tem aí pra esquentar um velho lobo do mar?","Ah, seu estabelecimento fica melhor a cada dia! Visitar aqui é sempre um prazer..."),RandPhraseSimple("Não esqueceu de um velho andarilho? Fico lisonjeado, meu amigo.","Bom ver um velho amigo de novo... Ainda tem um pouco de rum aí?")));
				Link.l1.go = "step_node";
			}
			break;
				
			case "step_node":
				dialog.Text = LinkRandPhrase("Estou ouvindo, capitão.","Minha taverna '"+XI_ConvertString(NPChar.City+"TavernName")+"' às suas ordens, Capitão!","Pode falar, capitão! O que vai querer hoje?");
				Link.l1 = "Tem algum rapaz na ilha pronto para tentar a sorte no mar?";
				Link.l1.go = "crew hire";
				Link.l2 = "Eu esperava que você pudesse responder a algumas perguntas.";
				Link.l2.go = "int_quests";
				if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l21 = "Gostaria de discutir questões financeiras.";
					link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
				
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
		            	{
					link.l10 = LinkRandPhrase("Você pode me contar algo sobre o roubo recente na igreja?","O que você sabe sobre o roubo recente na igreja?","Você ouviu algo sobre o recente roubo na igreja?");
					link.l10.go = "Tavern_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_tavern" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
				{
					link.l16 = "Dizem que você sabe quase tudo sobre esta colônia. Quero comprar "+pchar.GenQuest.Device.Shipyarder.Type+", e me disseram que tinha sido vendida na sua cidade. Bem, alguém estava vendendo isso na feira. Você pode me contar algo sobre isso?";
					link.l16.go = "Device_Tavern";
				}
				// <-- генератор Неудачливый вор
			
				//Jason --> генератор Место под солнцем
				if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "continue" && NPChar.location == pchar.GenQuest.Sunplace.Trader.CityT + "_tavern")
				{
					link.l17 = "Estou procurando um agiota chamado "+pchar.GenQuest.Sunplace.Trader.Enemyname+". Onde posso encontrá-lo?";
					link.l17.go = "Sunplace_Tavern";
				}
				// <-- генератор Место под солнцем
			
				// --> Голландский гамбит
				if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "JacobOnMain" && NPChar.location == pchar.questTemp.HWIC.Holl.JacobCity + "_tavern")
				{
					link.l18 = "Olá, "+npchar.name+". Preciso encontrar Jacob van Berg - onde ele está? Não o vejo na sua taverna...";
					link.l18.go = "HWICHollJacob_Tavern";
				}
				if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "start" && NPChar.nation == SPAIN && !CheckAttribute(npchar, "quest.HWICTalked"))
				{
					link.l18 = "Olá, "+npchar.name+". Estou procurando por um caballero chamado Fernando Rodriguez. Ele apareceu na sua cidade?";
					link.l18.go = "HWICSelfFernando_Tavern";
				}
				// <-- Голландский гамбит
			
				//Jason --> гонки на гидропланах
				if (CheckAttribute(pchar, "GenQuest.Racing.Go.Advantage") && NPChar.location == pchar.GenQuest.Racing.Go.StartCity + "_tavern")
				{
					link.l19 = "Vim buscar meus ganhos, que você guardou para mim. "+npchar.name+".";
					link.l19.go = "Race_Advantage";
				}
				// <-- гонки на гидропланах
			
				//Jason --> захват пассажиров
				if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "take" && NPChar.location == pchar.GenQuest.Marginpassenger.Targetcity+"_tavern")
				{
					link.l20 = "Eu queria saber onde posso encontrar um homem chamado "+pchar.GenQuest.Marginpassenger.q2Name+"? Ele mora na sua cidade.";
					link.l20.go = "Marginpassenger";
				}
				// <-- захват пассажиров
				if(!CheckAttribute(pchar,"questTemp.TimeLock"))
				{
					link.l3 = pcharrepphrase("Tem um quarto livre, amigo?","Você tem um quarto disponível? Gostaria de ficar aqui por um tempo.");
					link.l3.go = "room";
				}
				Link.l4 = "Infelizmente, já estou de partida, "+NPChar.name+". Até mais.";
				Link.l4.go = "exit";
		break;
		
		case "Helen_meeting":
			dialog.Text = "Ah, bem, entre, entre. Você é sempre bem-vindo aqui.";
			link.l1 = "Sim, obrigado. Foi bom te ver. Adeus.";
			link.l1.go = "exit";
			Link.l2 = "Estou precisando de gente nova. Só garanta que sejam capazes, certo?";
			Link.l2.go = "crew hire";
			link.l3 = "Eu gostaria de descansar em terra firme e colocar meus pensamentos em ordem, mas não enquanto minha mãe está agitada pela casa.";
			link.l3.go = "Helen_room";
			Link.l4 = "Posso te perguntar uma coisa? ";
			Link.l4.go = "quests";
			link.l5 = " Tenho um assunto para discutir com você, "+NPChar.name+".";
			link.l5.go = "Helen_rumours_tavern";
		break;
		
		case "Meeting":
			// Квестовый генератор священника. Квест №1. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_1.CurPortManColony + "_tavern")
	        {
	            dialog.Text = "O que deseja, graciosa "+GetSexPhrase("senhor","senhora")+"?";
				link.l1 = "Uma garrafa de rum para o meu companheiro naquela mesa ali.";
				link.l1.go = "Tavern_ChurchGenQuest1_Node_1";
				break;
			}
			// <-- Квестовый генератор священника. Квест №1.
			dialog.Text = LinkRandPhrase("Estou ouvindo, capitão.","O que posso lhe oferecer, capitão?","Então, capitão, o que vai ser?");
			Link.l1 = "Preciso de uma tripulação, "+NPChar.name+".";
			Link.l1.go = "crew hire";
			Link.l2 = NPChar.name+", vamos conversar...";
			Link.l2.go = "int_quests";
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l21 = "Gostaria de discutir questões financeiras.";
				link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
			}
			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
	        {
				link.l10 = LinkRandPhrase("Você pode me contar algo sobre o roubo recente na igreja?","O que você sabe sobre o recente roubo na igreja?","Você ouviu algo sobre o recente roubo na igreja?");
				link.l10.go = "Tavern_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_tavern" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "Dizem que você sabe praticamente tudo sobre esta colônia. Quero comprar "+pchar.GenQuest.Device.Shipyarder.Type+", e me disseram que tinha sido vendida na sua cidade. Bem, alguém estava vendendo isso nas ruas. Você pode me contar algo sobre isso?";
				link.l16.go = "Device_Tavern";
			}
			// <-- генератор Неудачливый вор
			
			//Jason --> генератор Место под солнцем
			if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "continue" && NPChar.location == pchar.GenQuest.Sunplace.Trader.CityT + "_tavern")
			{
   				link.l17 = "Me fale sobre um agiota chamado "+pchar.GenQuest.Sunplace.Trader.Enemyname+". Onde posso encontrá-lo?";
				link.l17.go = "Sunplace_Tavern";
			}
			// <-- генератор Место под солнцем
			
			//--> Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "JacobOnMain" && NPChar.location == pchar.questTemp.HWIC.Holl.JacobCity + "_tavern")
				{
					link.l18 = "Olá, "+npchar.name+". Preciso encontrar Jacob van Berg - onde ele está? Não o vejo na sua taverna...";
					link.l18.go = "HWICHollJacob_Tavern";
				}
				if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "start" && NPChar.nation == SPAIN && !CheckAttribute(npchar, "quest.HWICTalked"))
				{
					link.l18 = "Olá, "+npchar.name+". Estou procurando por um caballero chamado Fernando Rodriguez. Ele já chegou à sua cidade?";
					link.l18.go = "HWICSelfFernando_Tavern";
				}
				//<-- Голландский гамбит
				
				//Jason --> гонки на гидропланах
				if (CheckAttribute(pchar, "GenQuest.Racing.Go.Advantage") && NPChar.location == pchar.GenQuest.Racing.Go.StartCity + "_tavern")
				{
					link.l19 = "Vim buscar meus ganhos, que você está guardando para mim. "+npchar.name+".";
					link.l19.go = "Race_Advantage";
				}
				// <-- гонки на гидропланах
				//Jason --> захват пассажиров
				if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "take" && NPChar.location == pchar.GenQuest.Marginpassenger.Targetcity+"_tavern")
				{
					link.l20 = "Eu estava me perguntando onde posso encontrar um homem chamado "+pchar.GenQuest.Marginpassenger.q2Name+"? Ele mora na sua cidade.";
					link.l20.go = "Marginpassenger";
				}
				// <-- захват пассажиров
			if(!CheckAttribute(pchar,"questTemp.TimeLock"))
			{
				link.l3 = pcharrepphrase("Tem um quarto de graça, camarada?","Você tem um quarto disponível? Gostaria de ficar aqui por um tempo.");
				link.l3.go = "room";
			}
			Link.l4 = "Acho que vou voltar mais tarde.";
			Link.l4.go = "exit";
		break;
		
		case "crew hire":
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			ok = sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok;
			
			if (!ok)
			{
				Dialog.text = "E pra que você precisa de marinheiros, capitão? Não vejo seu navio no porto.";
				link.l1 = RandPhraseSimple("Exatamente... Eu tinha atracado no lugar errado.","Esqueci de entrar no porto...");
				link.l1.go = "exit";
				break;
			}
			
            if (makeint(environment.time) > 22.0 || makeint(environment.time) < 7.0)
			{
				Dialog.text = "Geralmente há muitos homens querendo virar marinheiros, mas agora já é tarde – eles só vão começar a aparecer de manhã. Talvez você queira alugar um quarto e esperar por eles?";
				link.l1 = "Certo. Você tem algum quarto disponível?";
				link.l1.go = "room";
				link.l2 = "Não estou interessado em um quarto no momento. Até mais.";
				link.l2.go = "exit";
			}
			else
			{
                if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
                {
                    Dialog.text = "Você acha que servimos criminosos procurados aqui? Agradeça por eu não chamar os guardas.";
					link.l1 = "Obrigado.";
					link.l1.go = "exit";
                }
                else
                {
					if (pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_tavern") // Блеквуд в городе
					{
						Dialog.text = "Capitão, hoje não tem viva alma na taverna. Todos que queriam já foram com o Capitão Blackwood.";
						link.l1 = "Que pena!";
						link.l1.go = "exit";
						break;
					}
					if (CheckAttribute(NPChar, "CrewHired.PGGId") && GetNpcQuestPastDayParam(NPChar, "CrewHired") < 3 && GetCrewQuantity(rColony) == 0)
					{
						Dialog.text = "Ah, desculpe capitão, você chegou só um pouco tarde. Todos os rapazes que queriam embarcar já zarparam com um capitão valente "+GetFullName(CharacterFromID(NPChar.CrewHired.PGGId))+".";
						link.l1 = "Que pena!";
						link.l1.go = "exit_crew";
					}
					else
					{						
						if(bPartitionSet)
						{		
							if(GetPartitionAmount("CrewPayment") > 0)
							{
								if(IsEquipCharacterByArtefact(pchar, "totem_07"))
								{
									DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
									NextDiag.CurrentNode =  NextDiag.TempNode;
									DialogExit();
									LaunchHireCrew();							
								}
								else
								{
									dialog.text = "Capitão, dizem que você é bem mão de vaca. Ninguém aqui quer entrar para a sua tripulação.";
									link.l1 = "Entendi...";
									link.l1.go = "exit";
								}
							}
							else
							{
								DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
								NextDiag.CurrentNode =  NextDiag.TempNode;
								DialogExit();
								LaunchHireCrew();	
							}
						}	
						else
						{
							DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
							NextDiag.CurrentNode =  NextDiag.TempNode;
							DialogExit();
							LaunchHireCrew();							
						}						
					}
				}
			}
		break;
		
		case "exit_crew" :
			DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
			NextDiag.CurrentNode =  NextDiag.TempNode;
			DialogExit();
			LaunchHireCrew();
		break;
	////////////////////////////////////////////////////////=============================================///////////////////////////////////////////////////////	
        case "int_quests":
			dialog.text = "Estou ouvindo.";
			//link.l1 = "Estou procurando trabalho. Você pode me ajudar?";
			//link.l1.go = "work";
			//homo 15/06/06 слухи
			link.l2 = LinkRandPhrase("Pode me contar as novidades?","O que está acontecendo por estas terras?","O que há de novo em terra?");
			link.l2.go = "rumours_tavern";
			//homo
			link.l3 = "Vim por outro motivo.";
			link.l3.go = "quests";
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "EncGirlFack_fighted")
				{
					link.l5 = "Você sabe onde posso encontrar "+pchar.GenQuest.EncGirl.name+"?";
					link.l5.go = "EncGirl_1";
				}	
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					link.l6 = "Você pode me dizer onde eu poderia procurar por "+pchar.GenQuest.EncGirl.sLoverId+"?";
					link.l6.go = "EncGirl_3";
				}
				if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "tavern_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l7 = "Oi, vim a convite do seu filho."; 
					link.l7.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}
			}
			if(CheckAttribute(pchar,"GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.City && CheckAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern"))
			{
				if(pchar.GenQuest.CaptainComission.variant == "A0")
				{												
					if(pchar.GenQuest.CaptainComission.Speak_Tavern == true)
					{
						link.l9 = "Então, você viu  "+pchar.GenQuest.CaptainComission.Name+"?";
						link.l9.go = "CaptainComission_3";
					}
					else
					{
						link.l9 = "Você pode me dizer onde devo procurar  "+pchar.GenQuest.CaptainComission.Name+"?";
						link.l9.go = "CaptainComission_1";
					}
				}	

				if(pchar.GenQuest.CaptainComission.variant == "A2" && pchar.GenQuest.CaptainComission == "Begin_1")
				{
					link.l9 = "Você sabe onde posso encontrar o capitão de uma patrulha "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+"?";
					link.l9.go = "CaptainComission_Tavern7";					
				}				
				if(pchar.GenQuest.CaptainComission.variant == "A3" && pchar.GenQuest.CaptainComission == "Begin_1")
				{
					if(pchar.GenQuest.CaptainComission.Speak_Tavern == true)
					{
						link.l9 = "Então, você viu "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.CanoneerName,NAME_NOM)+"?";
						link.l9.go = "CaptainComission_3";
					}
					else
					{					
						link.l9 = "Você sabe algo sobre o capitão da patrulha "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+"?";
						link.l9.go = "CaptainComission_Tavern1";
						if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
						{
							pchar.GenQuest.CaptainComission.GetRumour = true;
							SaveCurrentQuestDateParam("GenQuest.CaptainComission.GetRumour");
						}	
					}	
				}					
			}
			if(CheckAttribute(pchar,"GenQuest.Hold_GenQuest") && NPChar.city == pchar.GenQuest.Hold_GenQuest.City && pchar.GenQuest.Hold_GenQuest.Speak_Tavern == false )
			{
				link.l10 = "Você poderia me dizer onde posso encontrar um homem chamado "+pchar.GenQuest.Hold_GenQuest.Name+"?";
				link.l10.go = "hold_genquest1";
			}
			if (CheckCharacterItem(pchar, "CaptainBook") && CheckAttribute(pchar, "questTemp.different.GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakTavern") && (pchar.questTemp.different.GiveShipLetters.city == npchar.city))
			{
				link.l11 = "Por acaso encontrei alguns documentos de navio não muito longe daqui....";
				link.l11.go = "ShipLetters_4";			
			}

			// Jason --> квест губера на поиск дезертира
			if(CheckAttribute(pchar, "GenQuest.FindFugitive") && pchar.GenQuest.FindFugitive != "Late" && sti(NPChar.nation) == PIRATE)
			{
				link.l12 = "Escute, estou procurando um velho amigo meu, "+pchar.GenQuest.FindFugitive.Name+" é o nome dele. Um capitão conhecido me disse que ele estava indo para o seu assentamento. Por acaso você chegou a encontrá-lo?";
				link.l12.go = "FindFugitiveTav";
			}
			//<-- поиск дезертира

			link.l15 = "Nada, obrigado.";
			link.l15.go = "exit";
		break;
		
		case "hold_genquest1":
			switch(sti(pchar.GenQuest.Hold_GenQuest.TavernVariant))
			{
				case 0:
					dialog.text = LinkRandPhrase("O que você disse? "+pchar.GenQuest.Hold_GenQuest.Name+"? Hmm... Nunca ouvi falar dele.","Você tem certeza de que ele é daqui da nossa cidade? Nunca ouvi falar de alguém assim.","Não havia ninguém assim na nossa pequena colônia. Nunca ouvi falar dele em todo o tempo que estou aqui.");
					link.l1 = "Tem certeza?";
					link.l1.go = "hold_genquest2";					
				break;
				
				case 1: 
					switch (hrand(3))
					{
						case 0:
							pchar.GenQuest.Hold_GenQuest.foundStr = "the church";						
							pchar.GenQuest.Hold_GenQuest.found = "church";
						break;
						case 1:
							if (npchar.city != "Panama")
							{
							pchar.GenQuest.Hold_GenQuest.foundStr = "the shipyard";						
							pchar.GenQuest.Hold_GenQuest.found = "shipyard";
							}
							else
							{
								pchar.GenQuest.Hold_GenQuest.foundStr = "the church";						
								pchar.GenQuest.Hold_GenQuest.found = "church";
							}
						break;
						case 2:
							pchar.GenQuest.Hold_GenQuest.foundStr = "the usurer";												
							pchar.GenQuest.Hold_GenQuest.found = "bank";
						break;
						case 3:
							pchar.GenQuest.Hold_GenQuest.foundStr = "the shop";						
							pchar.GenQuest.Hold_GenQuest.found = "store";
						break;
					} 
					dialog.text = "Dá uma olhada "+pchar.GenQuest.Hold_GenQuest.foundStr+", ele costuma ser encontrado lá com frequência.";
					link.l1 = "Obrigado, farei exatamente isso.";
					link.l1.go = "hold_genquest3";				
				break;
				
				case 2:
					dialog.text = LinkRandPhrase(RandPhraseSimple("O que você disse? "+pchar.GenQuest.Hold_GenQuest.Name+"? Hmm... Nunca ouvi falar dele. Tem certeza de que ele é da nossa vila? Nunca ouvi falar de alguém assim.","Heh-heh... Bem, agora só o próprio Senhor sabe onde procurar por ele - no inferno ou no céu. Ele morreu faz mais de um ano, mas ainda tem gente perguntando por ele... Coitado, nem depois de morto tem descanso..."),RandPhraseSimple("Você não vai encontrá-lo lá — pelo menos não entre os vivos. Ele morreu há pouco tempo — febre amarela... Que Deus o tenha... Que homem forte ele era! Quando jovem, foi um grande aventureiro! Mas quando a morte vem te buscar, não há muito o que se possa fazer...","Ah, sentiu falta dele? Ele deixou essas bandas faz tempo. Ninguém sabe pra onde foi — talvez pras colônias da América do Norte, talvez de volta pra Europa. Só juntou suas coisas e sumiu."),"Ah, você está procurando por isso "+pchar.GenQuest.Hold_GenQuest.Name+" quem ficou rico e comprou uma casa na Nova Inglaterra? Olha, teve época em que eu vendia rum pra ele fiado – até hoje me deve. As pessoas são tão ingratas, sabia.");
					link.l1 = "Entendi. Bem, obrigado mesmo assim.";	
					link.l1.go = "hold_genquest4";
				break;
				
				case 3:
					dialog.text = "Ué, onde mais você procuraria por ele, se não na taverna? Ele é figurinha carimbada lá – afoga os pecados no vinho, heh-heh. Volte daqui a pouco – se ele aparecer, aviso pra ele te esperar.";	
					link.l1 = "Obrigado, vou fazer isso.";
					link.l1.go = "hold_genquest5";
				break;
			}
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = true;
		break;
		
		case "hold_genquest2":
			dialog.text = "Como eu não teria certeza se conheço todo mundo aqui pessoalmente. Não é o primeiro ano que estou comandando a taverna aqui. "+"Já vi todos eles em todas as situações possíveis. Às vezes, a esposa vinha buscar o marido, outras vezes eles saíam sozinhos, e em algumas ocasiões eu mesmo tive que jogá-los pra fora. 'Tenho certeza?!' Claro que tenho!";
			link.l1 = "Bem, obrigado mesmo assim...";	
			link.l1.go = "exit";
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			AddQuestRecord("HoldQuest", "7");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;
		
		case "hold_genquest3":
			Hold_GenQuest_GenerateChar();		
			AddQuestRecord("HoldQuest", "8");
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Gen")); 			
			AddQuestUserData("HoldQuest", "sFoundChar", pchar.GenQuest.Hold_GenQuest.foundStr);
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.Name);
			SetFunctionTimerConditionParam("Hold_GenQuest_FindCharTimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			DialogExit();
		break;
		
		case "hold_genquest4":
			AddQuestRecord("HoldQuest", "13");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			AddQuestUserData("HoldQuest", "sNameChar", pchar.GenQuest.Hold_GenQuest.Name);
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("HoldQuest");
			DeleteAttribute(pchar,"GenQuest.Hold_GenQuest");			
			DialogExit();
		break;
		
		case "hold_genquest5":
			SetFunctionTimerConditionParam("Hold_GenQuest_GetMapTimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_GenerateMapChar");			
		break;
		
		case "CaptainComission_1":
			dialog.text = LinkRandPhrase("Ele costuma vir aqui com frequência, mas no momento ele não está. Volte de vez em quando – vou pedir para ele esperar por você aqui se aparecer.","Ele vem aqui com frequência. Se voltar mais tarde, com certeza vai encontrá-lo por aqui.","Volte de vez em quando – ele aparece aqui com frequência. Vou avisar que você esteve procurando por ele.");
			link.l1 = "Obrigado, eu volto mais tarde...";
			link.l1.go = "CaptainComission_2";
			pchar.GenQuest.CaptainComission.Speak_Tavern = true;
		break;
		
		case "CaptainComission_2":
			pchar.quest.CapComission_ExitFromTavern.win_condition.l1 = "ExitFromLocation";
			pchar.quest.CapComission_ExitFromTavern.win_condition.l1.location = pchar.location;
			pchar.quest.CapComission_ExitFromTavern.function = "CaptainComission_GenerateChar";

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "CaptainComission_3":
			dialog.text = "Ele já passou por aqui, então deve estar por perto...";
			link.l1 = "Obrigado.";
			link.l1.go = "exit";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern");
		break;
		
		case "CaptainComission_Tavern1":
			pchar.GenQuest.CaptainComission.Speak_Tavern = true;
			dialog.text = "Existe alguém que não conheça ele? A vila inteira já fala dele há dias.";
			link.l1 = "Pode me contar mais?";
			link.l1.go = "CaptainComission_Tavern2";
		break;
		
		case "CaptainComission_Tavern2":
			dialog.text = "Um pouco. O capitão foi executado, e o mesmo aconteceu com parte da tripulação dele. O resto foi espalhado pelo Caribe, sem patente nem posição... E pra quê? Segundo o juiz, ele afundou um pirata durante uma patrulha e ficou com o saque pra si\n"+"O negócio é o seguinte: nem o dono deste navio, nem as mercadorias foram encontrados... eles têm vasculhado as baías e enseadas da região procurando por eles, mas até agora, nada.";
			link.l1 = "O quê, nenhum dos tripulantes revelou onde está o esconderijo?";	
			link.l1.go = "CaptainComission_Tavern3";	
		break;
		
		case "CaptainComission_Tavern3":
			dialog.text = "Nem um sequer! Nem sob tortura! Ainda não entendo por que o governador acreditaria tão facilmente nessa calúnia. Capitão "+pchar.GenQuest.CaptainComission.Name+" tinha uma boa reputação, e sua tripulação era bem treinada e disciplinada, algo que qualquer almirante invejaria.";
			link.l1 = "E onde devo procurar pelos membros sobreviventes da tripulação?";
			link.l1.go = "CaptainComission_Tavern4";
		break;
		
		case "CaptainComission_Tavern4":
			dialog.text = "Isso eu não sei – eles se espalharam pelos quatro cantos... Mas... ainda tem um deles por aqui, só que duvido que você consiga tirar muita coisa dele. Ele levou uma pancada forte na cabeça. Sabe, ele era artilheiro sob comando de "+pchar.GenQuest.CaptainComission.Name+". Ele foi encontrado inconsciente em uma enseada dois dias depois daquele acidente. Primeiro, o levaram ao hospital e o trataram como um herói, mas quando a situação se complicou, jogaram-no na masmorra e tentaram interrogá-lo, mas depois decidiram que ele precisava de cuidados médicos antes de qualquer coisa.";
			link.l1 = "Ele ainda está aqui agora?";
			link.l1.go = "CaptainComission_Tavern5";
		break;
		
		case "CaptainComission_Tavern5":
			pchar.GenQuest.CaptainComission.CanoneerName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "Sim, "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.CanoneerName,NAME_NOM)+" é o nome dele. Ele aparece de vez em quando, gasta as moedinhas que ganha pedindo esmola em rum. Pobre coitado. Se eu o vir, vou dizer para ele esperar aqui por você.";
			link.l1 = "Obrigado, volto mais tarde.";
			link.l1.go = "CaptainComission_Tavern6";
		break;
		
		case "CaptainComission_Tavern6":
			AddQuestRecord("CaptainComission2", "39");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); 
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sCharName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_ABL));
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			SetFunctionExitFromLocationCondition("CaptainComission_GenerateCanoneer", pchar.location, false);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "CaptainComission_Tavern7":
			DeleteAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern");
			dialog.text = "Conheço ele? Claro que conheço. E pra que você precisa dele?";
			link.l1 = "Tenho negócios com ele...";
			link.l1.go = "CaptainComission_Tavern8";
		break;
		
		case "CaptainComission_Tavern8":
			dialog.text = ""+GetAddress_Form(pchar)+", você deveria tomar cuidado com esse 'negócio'. "+pchar.GenQuest.CaptainComission.Name+" está detido sob suspeita de pirataria, e os homens do governador estão vasculhando a ilha em busca de seus cúmplices.";
			link.l1 = "Não me diga! E o que ele fez?";
			link.l1.go = "CaptainComission_Tavern9";
		break;
		
		case "CaptainComission_Tavern9":
			dialog.text = "Eu não sei se é verdade ou não, mas dizem que ele escondeu a carga confiscada de um navio pirata que passava e não entregou nada. E até agora, ninguém encontrou nem o pirata, nem a carga. Ainda não entendo por que o governador acreditou tão facilmente nessa calúnia. Capitão "+pchar.GenQuest.CaptainComission.CapName+"  tinha uma boa reputação, e era um excelente soldado. Pode confiar na minha palavra, "+GetAddress_Form(pchar)+".";
			link.l1 = "Bem, obrigado pelo aviso. Até mais.";
			link.l1.go = "CaptainComission_Tavern10";
		break;
		
		case "CaptainComission_Tavern10":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
			{
				pchar.GenQuest.CaptainComission.GetRumour = true;
				SaveCurrentQuestDateParam("GenQuest.CaptainComission.GetRumour");
				SetFunctionTimerConditionParam("CaptainComission_TimeIsOver", 0, 0, 2, MakeInt(24 - GetHour()), false);
				AddQuestRecord("CaptainComission2", "19");
				AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); // лесник окончание
				AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			}			
			DialogExit();
		break;
				
		case "EncGirl_1":
			dialog.text = "E para que você precisa dela?";
			link.l1 = "Tenho negócios com ela...";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "Metade dos homens do nosso povoado parece ter negócios com ela. Se as nossas mulheres a pegassem, iam jogá-la nua para fora dos portões da cidade.";
			link.l1 = "Ah, tudo bem... "+GetSexPhrase("Parece que entrei numa longa fila, então. Bem, se mais alguém aparecer procurando por ela, diga pra esperar atrás de mim.","Entendi")+"...";
			link.l1.go = "exit";
			pchar.quest.EncGirl_SpeakTavernKeeper.over = "yes";
			DeleteAttribute(pchar, "GenQuest.EncGirl");
		break;
		
		case "EncGirl_3":
			dialog.text = "Ele costuma aparecer por aqui – geralmente vem procurando trabalho, mas agora não está. Volte de vez em quando – vou avisar para ele te esperar aqui se aparecer.";
			link.l1 = "Obrigado, eu volto mais tarde...";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "FindingLover";
			pchar.quest.EncGirl_ExitTavern.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_ExitTavern.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_ExitTavern.function = "EncGirl_GenerateLover";
		break;
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "Ah, então você é "+GetSexPhrase("aquele capitão que trouxe","aquela moça que trouxe")+" meu filho pródigo com uma jovem esposa?";
				link.l1 = "Sim, fui eu quem ajudou.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "Oh, aí "+GetSexPhrase("ele é, nosso benfeitor","ela é, nossa benfeitora")+". Esperando uma recompensa, é isso?";
				link.l1 = "Bem, não preciso de recompensa, só o seu agradecimento já basta.";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "Sou muito grato a você por não ter abandonado meu filho na hora em que ele mais precisava e por ajudá-lo a sair de uma situação delicada. Permita-me agradecer e, por favor, aceite esta quantia modesta e um presente meu, pessoalmente.";
			link.l1 = "Obrigado. Ajudar esse jovem casal foi um prazer.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "Obrigado? Que obrigado o quê?! Já faz meio ano que aquele cabeça-oca está por aí sem trabalho – e olha só, ainda arranja tempo pra um caso! Quando eu tinha a idade dele, já tocava meu próprio negócio! Pfff! O governador tem uma filha em idade de casar – e esse idiota me aparece com uma qualquer, sem família nem raízes, e ainda tem a ousadia de pedir minha bênção!";
			link.l1 = "Suponho que você não acredita em amor à primeira vista?";
			link.l1.go = "EncGirl_6_1";		
		break;
		
		case "EncGirl_5_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.EncGirl.sum));
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item);
			AddQuestRecord("JungleGirl", "18");
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "EncGirl_6_1":
			dialog.text = "Amor? Amor!? Você está zombando de mim ou é burro? Que vergonha, incentivar os jovens em seus caprichos e agir como um alcoviteiro! Não só tirou uma moça de casa, como também arruinou a vida do meu filho. Não espere agradecimentos. Adeus.";
			link.l1 = "O mesmo pra você então.";
			link.l1.go = "EncGirl_6_2";
		break;
		
		case "EncGirl_6_2":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
				
		case "ShipLetters_4":
			pchar.questTemp.different.GiveShipLetters.speakTavern = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Deixe-me dar uma olhada! Hmm... Mas você mesmo é capitão. Acho que deveria falar com o mestre do porto sobre isso.";
				link.l1 = "Obrigado pelo seu conselho.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Deixe-me dar uma olhada! Ah! Pelo nome, isso pertence a um dos meus clientes, um cavalheiro bastante respeitado. Posso entregar esses documentos pessoalmente ao dono. Você me dá eles?";
				link.l1 = "Pensando bem...";
				link.l1.go = "exit";
				link.l2 = "Pode levar. Fico feliz em poder ajudar.";
				link.l2.go = "ShipLetters_end";				
			}	
		break;
		
		case "ShipLetters_end":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "3");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters"); 
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//zagolski. переделка
		case "work":
			if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
				dialog.text = RandPhraseSimple("Não me importa a quem eu sirvo, já que dinheiro não tem nacionalidade. Mas não vou te ajudar, já que você veio sob a bandeira de "+NationNameGenitive(sti(pchar.nation))+".","Sou apenas uma simples dona de taverna, mas colaborar com "+NationNameAblative(sti(pchar.nation))+" não me parece atraente.");
				link.l1 = RandPhraseSimple("Bem, como quiser...","Bem, como quiser...");
				link.l1.go = "exit";
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				dialog.text = RandPhraseSimple("We usually have a lot of passengers here. Still, I don't think there would be even one duffer among them who might agree to travel on your ship. Your ill repute precedes you; only a fool would sail with such a scoundrel.","I am quite frequently approached by merchants who need escorting. But your ill repute precedes you, and I will not recommend you to anyone. I care for my own reputation, you know. No one wants to hire a wolf to guard their sheep.");
				link.l1 = RandPhraseSimple("Ah, sério, você não devia acreditar em todas essas fofocas...","Entendo. É difícil fazer todo mundo ficar em silêncio.","As pessoas estão muito sensíveis hoje em dia...");
				link.l1.go = "exit";
				break;
			}
			if (sti(Pchar.Ship.Type) == SHIP_NOTUSED)
        	{
				dialog.text = "E onde está o seu navio? Ou pretende carregar os passageiros nas costas e nadar?";
				link.l1 = "Ei, você tem razão...";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Talvez eu tenha um trabalho, se você não tiver medo de visitar assentamentos piratas ou portos de nações inimigas. Está procurando algo em especial?";
			link.l1 = "Isso não deve ser um problema. Acho que posso providenciar uma escolta.";
			link.l1.go = "work_1";
			link.l2 = "Você tem passageiros? Posso levá-los aonde quiserem, se pagarem por isso.";
			link.l2.go = "work_2";
			link.l3 = "Não, esse tipo de trabalho não é para mim. Obrigado.";
			link.l3.go = "exit";
		break;

		case "work_1":
				dialog.text = "Normalmente não me pedem para fazer escolta. Pergunte aos mercadores na taverna – talvez eles precisem dos seus serviços.";
				link.l1 = "Está bem, como quiser.";
                link.l1.go = "exit";
		break;

		case "work_2":
			if (!CheckAttribute(npchar, "work_date") || GetNpcQuestPastDayParam(npchar, "work_date") >= 2 || bBettaTestMode)
    		{					
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 5)//при низком авторитете не даем
				{
					dialog.text = "Sinto muito, mas não tenho ninguém disposto a viajar com você.";
					link.l1 = "Entendi.";
					link.l1.go = "exit";
					break;
				}
		         // пассажир
				if (hrand(6) > 1)
				{
					dialog.Text = "Tem um homem que acabou de entrar – ele estava perguntando sobre um navio que passou por aqui. Você pode falar com ele, se quiser.";
					link.l1 = RandPhraseSimple("Quem é ele? Será que é um canalha? Ou, pior ainda, um pirata procurado?","E quem é ele? Vai ter algum problema com ele?");
					Link.l1.go = "PassangerAreYouSure";
				}
				else
				{
					dialog.text = "Não, hoje ninguém perguntou sobre isso. Talvez, em outro dia.";
					link.l1 = RandPhraseSimple("Bem, se não está lá, não está...","É sempre assim comigo... Fazer o quê, até mais.");
					link.l1.go = "exit";
				}
            }
    		else
    		{
				dialog.text = "Não tem ninguém hoje. Volte daqui a alguns dias.";
				link.l1 = "Está bem, como quiser.";
                link.l1.go = "exit";
    		}
        break;

        case "ConvoyAreYouSure":
		    dialog.text = LinkRandPhrase("Quem poderia saber? Você perguntou - eu respondi.","Bem, isso é com você. Eu não colocaria minha mão no fogo por ninguém lá.","Todo tipo de gente vem aqui. Isto é uma taverna, capitão, não a mansão do governador.");
			Link.l1 = "Obrigado, então vamos negociar.";
			Link.l1.go = "exit";
			pchar.quest.destination = findTraderCity(npchar);
			pchar.ConvoyQuest.City = npchar.city;
			AddDialogExitQuest("prepare_for_convoy_quest");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
        break;

        case "PassangerAreYouSure":
		    dialog.text = LinkRandPhrase("Quem poderia saber? Você perguntou - eu respondi.","Bem, isso é com você. Eu não colocaria minha mão no fogo por ninguém lá.","Todo tipo de gente aparece por aqui. Isto é uma taverna, capitão, não a mansão do governador.");
			Link.l1 = "Entendi. Vamos descobrir quem é esse homem...";
			Link.l1.go = "exit";
			sGlobalTemp = findPassangerCity(npchar);
			pchar.GenQuest.GetPassenger_City = npchar.city;
			AddDialogExitQuest("prepare_for_passenger_quest");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
        break;

		 case "fight":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Helen_room":
			dialog.text = "Claro, Helen. Quanto tempo você vai ficar? E então, brigou com a velha Gladys?";
			if(!isDay())
			{
				link.l1 = "Só quero dormir até de manhã. Se eu voltar pra casa agora, com certeza vou acordá-la.";
				link.l1.go = "Helen_room_day";
			}
			else
			{
				link.l1 = "Não, não, só preciso zarpar à noite, e não quero acordá-la.";
				link.l1.go = "Helen_room_night";
				link.l2 = "Quero dormir bem, sem pressa pra levantar. Vou ficar com um quarto pelo dia.";
				link.l2.go = "Helen_room_day_next";
			}
		break;

		case "room":
   			if (chrDisableReloadToLocation || CheckAttribute(pchar, "GenQuest.TavernClose")) //кто-то должен подойти к ГГ.
			{
				dialog.text = "O quarto está ocupado, "+GetAddress_Form(NPChar)+", não posso fazer nada por você.";
				link.l1 = "Bem, que pena...";
				link.l1.go = "exit";
				break;
			}
			// суп из черепахи
			if (CheckAttribute(pchar, "questTemp.Terrapin.Room_close") && npchar.location == "Tortuga_tavern")
			{
				dialog.text = "Monsieur Henri Thibaut está ocupando o quarto no momento, e já pagou um mês adiantado, então não posso fazer nada por você, capitão.";
				link.l1 = "Bem, que pena...";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "cave" && npchar.location == "Tortuga_tavern")
			{
				dialog.text = "O quarto está ocupado, "+GetAddress_Form(NPChar)+", não posso fazer nada por você.";
				link.l1 = "Bem, que pena...";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "shore" && npchar.location == "Baster_tavern") // 070712
			{
				dialog.text = "O quarto está ocupado, "+GetAddress_Form(NPChar)+", não há nada que eu possa fazer por você.";
				link.l1 = "Bem, que pena...";
				link.l1.go = "exit";
				break;
			}
			if (pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_tavern") // Блеквуд в городе
			{
				Dialog.text = "Infelizmente, não, Capitão. Todos os quartos estão ocupados por Blackwood e seus homens.";
				if (CheckAttribute(pchar, "questTemp.LadyBeth_TavernRoomDialog"))
				{
					link.l1 = "Ah, que pena!";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "Todos os quartos? Tem mais de um quarto aqui?";
					link.l1.go = "LadyBeth_Room";
				}
				break;
			}
			//-->> квест официантки
			if (pchar.questTemp.different == "FackWaitress_toRoom")
			{
				dialog.text = "Quer alugar um quarto? Sem problema. 100 peças de oito e ele é seu.";
				if (sti(pchar.money) >= 100)
				{
					link.l1 = "Aqui está o seu dinheiro.";
					link.l1.go = "exit";
					AddMoneyToCharacter(pchar, -100);
					LocatorReloadEnterDisable(npchar.city + "_tavern", "reload2_back", false);
					pchar.questTemp.different = "FackWaitress_toRoomUp";
				}
				else
				{
					link.l1 = "Hum... Acho que vou voltar mais tarde...";
					link.l1.go = "exit";
				}
				break;
			}
			if (pchar.questTemp.different == "FackWaitress_toRoomUp")//квест официантки
			{
				dialog.text = "O quarto é todo seu. Entre e fique à vontade.";
				link.l1 = "Valeu, camarada.";
				link.l1.go = "exit";
				break;
			}
			//<<-- квест официантки
			// --> квест "A damsel in the jungle"
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && npchar.city == pchar.GenQuest.EncGirl.city)
			{
				if(pchar.GenQuest.EncGirl == "EncGirl_ToTavern")
				{
					dialog.text = "Quer alugar um quarto? Sem problema. 100 peças de oito e é seu.";
					if (sti(pchar.money) >= 100)
					{
						link.l1 = "Aqui está o seu dinheiro.";
						link.l1.go = "exit";
						AddMoneyToCharacter(pchar, -100);
						LocatorReloadEnterDisable(npchar.city + "_tavern", "reload2_back", false);
						pchar.GenQuest.EncGirl = "EncGirl_toRoomUp";
					}
					else
					{
						link.l1 = "Hum... Acho que vou voltar mais tarde...";
						link.l1.go = "exit";
					}
					break;
				}
				if (pchar.GenQuest.EncGirl == "EncGirl_toRoomUp")//квест  по спасению тетки в пампасах
				{
					dialog.text = "O quarto é todo seu. Entre e fique à vontade.";
					link.l1 = "Valeu, camarada.";
					link.l1.go = "exit";
					break;
				}
			}
			// <-- квест "A damsel in the jungle"

			// belamour постоялец -->
			if (CheckAttribute(pchar, "GenQuest.Unwantedpostor") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && abs(50-sti(pchar.reputation.nobility)) > 20)
			{
				if(pchar.GenQuest.Unwantedpostor == "start")
				{
					SetFunctionTimerCondition("Unwantedpostor_OneDay", 0, 0, 1, false);
					pchar.GenQuest.Unwantedpostor = "timer";
				}
				dialog.text = "Com licença, capitão, infelizmente não há quartos disponíveis. O hóspede não quer sair. E ainda nem me pagou...";
				link.l1 = "Parece que vamos ter que passar a noite no salão comum...";
				link.l1.go = "Unwantedpostor_hall_day_wait";
				link.l2 = "Desculpe. Vamos falar de outra coisa.";
				link.l2.go = "int_quests";
				if(pchar.GenQuest.Unwantedpostor != "Lose")
				{
					link.l3 = "Então chame os guardas. Que tipo de hóspede é esse? Não paga, não quer sair...";
					link.l3.go = "Unwantedpostor";
				}
				break;
			}
			//<-- постоялец

			dialog.text = "Por quanto tempo você pretende ficar aqui?";
			if(!isDay())
			{
				link.l1 = "Até de manhã.";
				link.l1.go = "room_day";
			}
			else
			{
				link.l1 = "Até a noite.";
				link.l1.go = "room_night";
				link.l2 = "Até a manhã seguinte.";
				link.l2.go = "room_day_next";
			}
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.MarySexBlock"))
			{
				pchar.questTemp.MarySexBlock = true;
				SetTimerFunction("Mary_DeleteSexBlock", 0, 0, 1);
			}
		break;

		case "room_day":
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_FreeBuhlo") && npchar.id == "PuertoPrincipe_tavernkeeper")
			{
				dialog.text = "O quarto está à sua disposição, capitão. Totalmente de graça.";
				link.l1 = "Valeu, camarada.";
				link.l1.go = "room_day_wait";
				link.l3 = "Agora não. Vamos falar de outra coisa.";
				link.l3.go = "int_quests";
				break;
			}
			dialog.text = "Isso vai te custar 5 peças de oito.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "Fechado. Aqui está.";
				link.l1.go = "room_day_wait";
			}
			link.l2 = pcharrepphrase("Por esse preço? Está alugando aposentos reais? Prefiro ficar na sala comum de graça.","Infelizmente, dormir numa cama está além das minhas posses no momento, pelo visto. Acho que vou ter que passar a noite no salão comum, num banco.");
			link.l2.go = "hall_day_wait";
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				link.l3 = "Agora não. Vamos mudar de assunto.";
				link.l3.go = "int_quests";
			}
		break;

		case "room_day_next":
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_FreeBuhlo") && npchar.id == "PuertoPrincipe_tavernkeeper")
			{
				dialog.text = "O quarto está à sua disposição, capitão. Totalmente de graça.";
				link.l1 = "Valeu, camarada.";
				link.l1.go = "room_day_wait_next";
				link.l3 = "Agora não. Vamos falar de outra coisa.";
				link.l3.go = "int_quests";
				break;
			}
			dialog.text = "Isso vai te custar 10 peças de oito.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "Fechado. Aqui está.";
				link.l1.go = "room_day_wait_next";
			}
			link.l2 = pcharrepphrase("Por esse preço? Está alugando aposentos reais? Prefiro ficar na sala comum de graça.","Infelizmente, o luxo de dormir numa cama está além das minhas posses no momento, ao que parece. Acho que vou ter que dormir no salão comum, em um banco.");
			link.l2.go = "hall_day_wait";
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				link.l3 = "Agora não. Vamos mudar de assunto.";
				link.l3.go = "int_quests";
			}
		break;

		case "room_night":
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_FreeBuhlo") && npchar.id == "PuertoPrincipe_tavernkeeper")
			{
				dialog.text = "O quarto está à sua disposição, capitão. Absolutamente de graça.";
				link.l1 = "Valeu, amigo.";
				link.l1.go = "room_night_wait";
				link.l3 = "Agora não. Vamos falar de outra coisa.";
				link.l3.go = "int_quests";
				break;
			}
			dialog.text = "Isso vai te custar 5 peças de oito.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "Fechado. Aqui está.";
				link.l1.go = "room_night_wait";
			}
			link.l2 = pcharrepphrase("Por esse preço? Está alugando aposentos reais? Prefiro ficar na sala comum de graça.","Ao que parece, o luxo de dormir numa cama está além das minhas posses no momento. Acho que vou ter que passar a noite no salão comum, num banco mesmo.");
			link.l2.go = "hall_night_wait";
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				link.l3 = "Agora não. Vamos mudar de assunto.";
				link.l3.go = "int_quests";
			}
		break;

		case "room_night_wait":
			// belamour прерывание ночной приключенец -->
			if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
			{
				if(GetCharacterIndex(pchar.GenQuest.NightAdventureId) != -1)
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
				SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
			}
			// <-- прерывание ночного приключенца 
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_night");
		break;

		case "hall_night_wait":
			if (hRand(3) == 1)
            {
                Dialog.text = "Cai fora daqui, seu canalha! O salão pode ser livre, mas esperamos um mínimo de decência!";
				link.l1 = "Certo, certo, já estou indo.";
				link.l1.go = "exit";
            }
            else
            {
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_night");
			}
		break;

		case "room_day_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_tavern");
			// belamour прерывание ночной приключенец -->
			if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
			{
				if(GetCharacterIndex(pchar.GenQuest.NightAdventureId) != -1)
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
				SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
			}
			// <-- прерывание ночного приключенца 
			if (CheckAttribute(pchar, "GenQuest.LigaAttack") && hrand(1) == 1)
			{
				TavernWaitDate("wait_night");
				pchar.GenQuest.LigaAttack.Go = "true"; //атака киллеров
			}
			else TavernWaitDate("wait_day");
		break;

		case "room_day_wait_next":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -10);
			AddDialogExitQuest("sleep_in_tavern");
			// belamour прерывание ночной приключенец -->
			if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
			{
				if(GetCharacterIndex(pchar.GenQuest.NightAdventureId) != -1)
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
				SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
			}
			// <-- прерывание ночного приключенца 
			if (CheckAttribute(pchar, "GenQuest.LigaAttack") && hrand(1) == 1)
			{
				TavernWaitDate("wait_night");
				pchar.GenQuest.LigaAttack.Go = "true"; //атака киллеров
			}
			else TavernWaitDate("wait_day");
		break;

		case "hall_day_wait":
			if (hrand(1) == 1)
            {
                Dialog.text = "Cai fora daqui, seu canalha! O salão pode ser de graça, mas esperamos um mínimo de decência!";
				link.l1 = "Certo, certo, já estou indo.";
				link.l1.go = "exit";
            }
            else
            {
				// belamour прерывание ночной приключенец -->
				if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
					SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
				}
				// <-- прерывание ночного приключенца
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_day");
			}
		break;
		
		case "tavern_keeper":
			NextDiag.TempNode = "First time";

			dialog.text = "Pare com esse comportamento absurdo na minha taverna agora mesmo ou vou chamar os guardas!";
			link.l1 = "Tá bom, tá bom, já estou indo.";
			link.l1.go = "exit_sit";
		break;

		case "exit_sit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;
		
		//******************* ноды квеста священника. поиск грабителей (квест № 2)**********************
		case "Tavern_GenQuest_Church_2_1":
			dialog.text = "Eu não sei muito sobre isso... É melhor você perguntar aos clientes.";
			link.l1 = "Entendi, obrigado.";
			link.l1.go = "exit";
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen");
		break;
			
		//******************* ноды квеста священника. вернуть рукописи (квест № 1)**********************
		case "Tavern_ChurchGenQuest1_Node_1":
			dialog.text = "Não oferecemos serviços a crédito, "+GetSexPhrase("senhor","perder")+".";
			link.l1 = "Eu pago em boa moeda. Você não aceita mais ouro ou prata?";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_2";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_2":
			dialog.text = "Me desculpe, "+GetSexPhrase("senhor","senhorita")+" Capitão, mas seu amigo tinha uma dívida, e eu pensei...";
			link.l1 = "Pense menos e trabalhe mais rápido. Agora, quanto meu valente amigo te deve?";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_3";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_3":
			iTemp = (rand(3)+1)*100;
			PChar.GenQuest.ChurchQuest_1.MoneyToBarmen = iTemp;
			if(rand(1) == 0) // "If he's a simple one and pays right away"
			{
				dialog.text = FindRussianMoneyString(iTemp)+", senhorita"+GetSexPhrase("ter","s")+" capitão, e ele também penhorou alguns livros da igreja – era tudo o que ele tinha com ele, que tinham algum valor.";
				if(sti(PChar.money) >= iTemp)
				{
					link.l1 = "Aqui estão suas moedas. Entregue os manuscritos. E tome cuidado com eles – isto não é um livro de gravuras indecentes, mas sim as Sagradas Escrituras!";
					link.l1.go = "Tavern_ChurchGenQuest1_Node_4_1";
				}
				else
				{
					link.l1 = "Espere um pouco... Eu volto com o dinheiro";
					link.l1.go = "exit";
					PChar.GenQuest.ChurchQuest_1.NoMoneyToBarmen = true;
				}
			}
			else // "If he's not a simple one"
			{
				dialog.text = FindRussianMoneyString(iTemp)+", senhorita"+GetSexPhrase("ter","s")+" capitão.";
				link.l1 = "Vou pagar a dívida dele e ficar com o que ele deixou como garantia.";
				link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2";
			}
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_1":
			DialogExit();
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen));
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen");
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "8");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"));
			AddQuestUserData(sQuestTitle, "sName", GetFullName(CharacterFromID("ChurchGenQuest1_Cap")));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 2, false);
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2":
			dialog.text = "Não, senhorita"+GetSexPhrase("ter","s")+", isso não vai funcionar desse jeito.";
			link.l1 = "O que você quer dizer com 'isso não vai funcionar assim'? A dívida do capitão está paga – ele está limpo. Você recebeu seu dinheiro de volta – está satisfeito. Eu aceito o compromisso dele – estou tranquilo. Todo mundo está bem – então por que 'isso não vai funcionar assim'?";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_1";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_1":
			dialog.text = "Porque, senhorita"+GetSexPhrase("ter","s")+" Capitão, eu não preciso do dinheiro. Eu conheço muito bem esse capitão, então nunca esperei de verdade que ele me pagasse ou pegasse esses manuscritos de volta.";
			link.l1 = "Como assim - você não precisa de dinheiro? Então você planejou ficar com esses livros desde o começo? Mas por quê, pelo amor de Deus?!";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_2";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_2":
			dialog.text = "Em nome de Deus - exatamente, é por isso, senhorita"+GetSexPhrase("ter","s")+". Meu menino estava muito doente, e minha esposa e eu fizemos uma promessa de doar para a Igreja se nosso Senhor abençoado curasse nosso filho da febre. A misericórdia do Senhor não tem fim, meu filho está vivo e saudável, e agora devemos cumprir nossa promessa. E já estava na hora, capitão "+PChar.GenQuest.ChurchQuest_1.CapFullName+" aparece e penhora esses livros da igreja. Eu não podia permitir tamanha obscenidade – pagar bebidas com a Palavra – e por isso resolvi entregar esses livros ao pastor da nossa paróquia.";
			link.l1 = "Bem, certamente isso é uma boa ação, mas você também deve saber que esses livros na verdade pertencem a outro padre – na verdade, não só um padre, mas um bispo e meu guia espiritual. E ele pode ficar furioso e até amaldiçoar quem ousar doar bens roubados da Igreja. Eu gostaria de comprá-los de você e levá-los em segurança para casa. Você pode doar o dinheiro para sua paróquia, tenho certeza de que Deus vai apreciar do mesmo jeito.";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_3";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_3":
			dialog.text = "Mis"+GetSexPhrase("ter","s")+"... Senhorita"+GetSexPhrase("ter","s")+" Capitão... Claro, eu não fazia ideia! Vou devolvê-los, e não vou pedir nenhum dinheiro em troca. Só peço que fale com o bispo por nós – talvez ele possa nos abençoar e nos liberar do nosso voto...";
			link.l1 = "É claro que seu voto será considerado cumprido! Afinal, você abriu mão do seu lucro para devolver os livros ao verdadeiro dono. A igreja específica não importa, pois há apenas um Deus e uma única Santa Igreja Católica Apostólica, certo? Muito bem, entregue-os para mim, e boa sorte para você...";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_4";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_4":
			DialogExit();
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen));
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen");
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "9");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown)); // belamour gen
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 2, false);
		break;
		
		//Jason --> генератор Неудачливый вор
		case "Device_Tavern":
			dialog.text = "Hmm, "+pchar.GenQuest.Device.Shipyarder.Type+"? Nunca ouvi falar disso antes... O que é, afinal? Nunca ouvi falar de algo assim em todo o meu tempo.";
			link.l1 = "Bem, é uma ferramenta de carpinteiro naval, "+pchar.GenQuest.Device.Shipyarder.Describe+". Alguém te ofereceu algo assim?";
			link.l1.go = "Device_Trader_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Trader_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) == 6)
			{
				dialog.text = "Hum... Sim, um sujeito estranho realmente trouxe essa coisa pra mim. Mas não me disse o que era – só tentou trocar por bebida. Claro que recusei – não tinha utilidade pra aquele bibelô.";
				link.l1 = "E como ele era, e para onde foi? Eu preciso muito desse instrumento.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "Não, nada disso. Desculpe, não posso te ajudar. Pergunte por aí.";
				link.l1 = "Entendi. Bem, hora de perguntar por aí!";
				link.l1.go = "exit";
			}
		break;
		// <-- генератор Неудачливый вор
		
		//Jason --> генератор Место под солнцем
		case "Sunplace_Tavern":
			if (makeint(environment.time) > 12.0 && makeint(environment.time) < 17.0)//в магазине
			{
				dialog.text = ""+pchar.GenQuest.Sunplace.Trader.Enemyname+"? Ele esteve lá recentemente, e agora já deve ter ido encontrar o companheiro dele – o lojista. Tente procurá-lo na loja – com certeza ele deve estar lá.";
				link.l1 = "Obrigado! Você me ajudou muito!";
				link.l1.go = "Sunplace_Tavern_1";
			}
			else//ушел на рыбалку
			{
				dialog.text = ""+pchar.GenQuest.Sunplace.Trader.Enemyname+"? Hoje, bem cedo, ele saiu para o mar em seu lugre para uma viagem. Aposto que agora mesmo está encostado no balaústre, admirando a paisagem. Se precisar dele, pode tentar encontrá-lo no mar ou esperar até que ele volte em alguns dias...";
				link.l1 = "Obrigado! Acho que não vou esperar – vai ser mais fácil encontrá-lo no mar. Boa sorte!";
				link.l1.go = "Sunplace_Tavern_2";
			}
		break;
		
		case "Sunplace_Tavern_1"://магазин
			pchar.quest.Sunplace_Store.win_condition.l1 = "location";
			pchar.quest.Sunplace_Store.win_condition.l1.location = pchar.GenQuest.Sunplace.Trader.CityT + "_store";
			pchar.quest.Sunplace_Store.function = "Sunplace_CreateTrader";
			AddQuestRecord("Sunplace", "6");
			AddQuestUserData("Sunplace", "sName", pchar.GenQuest.Sunplace.Trader.Enemyname);
			AddQuestUserData("Sunplace", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.CityT+"Gen"));
			DialogExit();
			pchar.GenQuest.Sunplace.Trader = "hunt";
		break;
		
		case "Sunplace_Tavern_2"://рыбалка
			pchar.GenQuest.Sunplace.Trader.IslandID = GetCharacterCurrentIslandId(npchar);
			pchar.GenQuest.Sunplace.Trader.EnemyNation = npchar.nation;
			pchar.quest.Sunplace_Sea.win_condition.l1 = "location";
			pchar.quest.Sunplace_Sea.win_condition.l1.location = pchar.GenQuest.Sunplace.Trader.IslandID;
			pchar.quest.Sunplace_Sea.function = "Sunplace_CreateTraderLugger";
			AddQuestRecord("Sunplace", "7");
			AddQuestUserData("Sunplace", "sName", pchar.GenQuest.Sunplace.Trader.Enemyname);
			AddQuestUserData("Sunplace", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.CityT+"Gen"));
			DialogExit();
			pchar.GenQuest.Sunplace.Trader = "hunt";
		break;
		// <-- генератор Место под солнцем	
		
		// Jason --> Голландский гамбит
		case "HWICHollJacob_Tavern":
			dialog.text = "Psssst... Por que você está gritando? Ele já está te esperando faz um bom tempo. Já tomou quase um litro de rum. Sobe para o quarto, você vai encontrá-lo lá.";
			link.l1 = "Ah, entendi. Tomara que ele ainda esteja acordado.";
			link.l1.go = "exit";
			LocatorReloadEnterDisable(pchar.questTemp.HWIC.Holl.JacobCity+"_tavern", "reload2_back", false);
			pchar.questTemp.HWIC.Holl = "JacobInRoom";
			AddDialogExitQuestFunction("Create_JacobVanBerg");
			DelLandQuestMark(npchar);
		break;
		
		case "HWICSelfFernando_Tavern":
			if (NPChar.location == pchar.questTemp.HWIC.Self.SpainCity +"_tavern")
			{
				//DelMapTonzagAllQM();
				dialog.text = "Sim, eu conheço esse cavalheiro. Ele deve estar em algum lugar da cidade – vi ele passando pela minha janela há pouco tempo.";
				link.l1 = "Obrigado! Vou procurá-lo!";
				link.l1.go = "Fernando_Land";
				/* if (makeint(environment.time) > 10.0 && makeint(environment.time) < 18.0)//на улице
				{
					dialog.text = "Sim, eu conheço esse cavalheiro. Ele deve estar em algum lugar da cidade – vi ele passando pela minha janela há pouco tempo.";
					link.l1 = "Obrigado! Vou procurá-lo!";
					link.l1.go = "Fernando_Land";
				}
				else //в море
				{
					dialog.text = "Sim, ele está visitando nossa cidade agora. No momento ele não está aqui – saiu navegando em sua brigantina. Provavelmente não está longe, deve estar em algum lugar nas águas ao redor da nossa ilha.";
					link.l1 = "Valeu, amigo! Você me ajudou muito!";
					link.l1.go = "Fernando_Sea";
				} */
				pchar.questTemp.HWIC.Self = "KillFernando";
			}
			else
			{
				dialog.text = "Fernando Rodriguez? Nunca ouvi falar desse nome. Não, não sei nada sobre esse homem.";
				link.l1 = "Entendi... Bem, a busca continua...";
				link.l1.go = "exit";
			}
			npchar.quest.HWICTalked = "true";
		break;
		
		case "Fernando_Land":
			pchar.quest.HWIC_Fernando.win_condition.l1 = "location";
			pchar.quest.HWIC_Fernando.win_condition.l1.location = pchar.questTemp.HWIC.Self.SpainCity +"_town";
			pchar.quest.HWIC_Fernando.function = "CreateFernandoOnLand";
			AddQuestRecord("Holl_Gambit", "3-2");
			DialogExit();
		break;
		
		case "Fernando_Sea":
			pchar.questTemp.HWIC.Self.FernandoIslandID = GetCharacterCurrentIslandId(npchar);
			pchar.quest.HWIC_Fernando.win_condition.l1 = "location";
			pchar.quest.HWIC_Fernando.win_condition.l1.location = pchar.questTemp.HWIC.Self.FernandoIslandID;
			pchar.quest.HWIC_Fernando.function = "CreateFernandoOnSea";
			AddQuestRecord("Holl_Gambit", "3-3");
			DialogExit();
		break;
		//<-- Голландский гамбит
		
		//Jason --> гонки на гидропланах
		case "Race_Advantage":
			dialog.text = "Sim, claro. Parabéns, capitão. Já estou sabendo da sua vitória. Aqui está o seu dinheiro.";
			link.l1 = "Obrigado, "+npchar.name+".";
			link.l1.go = "Race_Advantage_1";
		break;
		
		case "Race_Advantage_1":
			DialogExit();
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Racing.Go.Money)*2);
			AddQuestRecord("Racing", "4");
			AddQuestUserData("Racing", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.StartCity+"Gen"));
			CloseQuestHeader("Racing");
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
		break;
		//<-- гонки на гидропланах
		
		//Jason --> захват пассажиров
		case "Marginpassenger":
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger.lose"))
			{
				dialog.text = "Errr, senhor, "+pchar.GenQuest.Marginpassenger.q2Name+" morreu por volta de "+LinkRandPhrase("um mês","três semanas","dois meses")+" ago. "+LinkRandPhrase("De repente sucumbiu à febre","Ele foi esfaqueado nos portões da cidade - bandidos ou aqueles selvagens de pele vermelha","Ele levou um tiro em um duelo")+". Que Deus o tenha em paz...";
				link.l1 = "Droga!.. E o que eu faço com o... Ah, deixa pra lá. Valeu pela informação. Até mais, "+npchar.name+".";
				link.l1.go = "Marginpassenger_1";
			}
			else
			{
				dialog.text = ""+pchar.GenQuest.Marginpassenger.q2Name+"? Sim, ele deve estar em algum lugar da cidade. Procure por ele nas ruas. Mas lembre-se que todos os dias até o meio-dia ele fica no gabinete do governador, e depois das nove da noite ele se tranca em casa.";
				link.l1 = "Obrigado! Vou procurá-lo...";
				link.l1.go = "Marginpassenger_2";
			}
		break;
		
		case "Marginpassenger_1":
			DialogExit();
			AddQuestRecord("Marginpassenger", "7");
			AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City));
			// belamour gen: Добряку недолго осталось -->
			if(CheckAttribute(pchar, "questTemp.LongHappy"))
			{
				AddQuestUserData("Marginpassenger", "sBaron", "to Puerto Principe, to the Black Pastor");
			}
			else
			{
				AddQuestUserData("Marginpassenger", "sBaron", "to Le Francois, to Kindly Jacques");
			}
			// <-- belamour gen
			pchar.GenQuest.Marginpassenger = "cabin";
		break;
		
		case "Marginpassenger_2":
			DialogExit();
			AddQuestRecord("Marginpassenger", "8");
			AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
			pchar.GenQuest.Marginpassenger = "street";
		break;
		//<-- захват пассажиров
		
		//Jason --> поиск дезертира
		case "FindFugitiveTav":
			if (NPChar.city == pchar.GenQuest.FindFugitive.City && sti(pchar.GenQuest.FindFugitive.Chance) == 0)
			{
				dialog.text = NPCStringReactionRepeat("Parece que seu capitão estava dizendo a verdade. "+pchar.GenQuest.FindFugitive.Name+" de fato chegou recentemente ao nosso povoado. Procure por ele nas ruas durante o dia – normalmente ele está por aí, matando o tempo.","Você já me perguntou sobre esse homem, e eu já te contei tudo o que sabia!","Você está de brincadeira comigo, ou é realmente um idiota?! Você já está perguntando a mesma coisa pela terceira vez!","Só de pensar, como é que um idiota desses virou capitão...","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Muito obrigado, amigo, você me ajudou demais!","Tá, tá bom.","Caramba, calma aí, não precisa se empolgar tanto. Eu só esqueci.","Bem, ele fez, como você pode ver...",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("FindFugitiveTav_1", "exit", "", "", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = NPCStringReactionRepeat("Não, camarada, nunca ouvi esse nome antes. Pergunte por aí – talvez alguém o conheça...","Você já me perguntou sobre esse homem, e eu já disse: não sei!","Você está de brincadeira comigo, ou é realmente um idiota?! Você já está perguntando a mesma coisa pela terceira vez!","Só de pensar, como é que um idiota desses virou capitão...","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Entendi. Bem, obrigado mesmo assim.","Tá, tá, tudo bem.","Caramba, calma aí, não precisa se empolgar tanto. Eu só esqueci.","Bem, ele fez, como você pode ver...",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
			}
		break;
		
		case "FindFugitiveTav_1":
			DialogExit();
			AddQuestRecord("MayorsQuestsList", "12-1");
			sld = characterFromId("Fugitive");
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, true);
			sld.dialog.currentnode = "Fugitive_city";
			LAi_SetLoginTime(sld, 11.0, 18.0);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.FindFugitive.City+"_town", "goto", "goto"+(rand(9)+1));
		break;
		//<-- поиск дезертира
		
		//--> Бремя гасконца
		case "Sharlie_crew":
			dialog.text = "Infelizmente, não posso te ajudar agora – ninguém que eu conheço aceitaria servir sob seu comando. Mas posso te dar um conselho – converse com aquele marinheiro que acabou de sentar na mesa logo atrás de você. Ele e os companheiros dele acabaram de sair de um navio mercante. Talvez eles topem ir com você.";
			link.l1 = "Certo, vou fazer exatamente isso! Muito obrigado!";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "sailor";
			//усадим матроса Алонсо
			sld = GetCharacter(NPC_GenerateCharacter("SharlieSailor" , "Alonso", "man", "man", 10, FRANCE, -1, true, "quest"));
			sld.name = GetCharacterName("Alonso");
			sld.lastname = "";
			FantomMakeCoolFighter(sld, 10, 20, 20, "blade_05", "", "", 10);
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "Sharlie_sailor";
			sld.greeting = "town_sailor";
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetSitType(sld);
			LAi_SetImmortal(sld, true);
			FreeSitLocator("FortFrance_tavern", "sit7");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern", "sit", "sit7");
			AddQuestRecord("Sharlie", "6-1"); // mitrokosta
		break;
		
		case "Sharlie_skiper":
			dialog.text = "Não posso te dizer nada específico, amigo. No momento, nenhum navegador está frequentando meu estabelecimento. Tente perguntar pelo porto – talvez as pessoas saibam de algo.";
			link.l1 = "Entendi. Certo, vou conversar com o pessoal.";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "findskiper";
			//сгенерим наводчика
			sld = GetCharacter(NPC_GenerateCharacter("SharlieSkiperTalker", "citiz_"+(rand(19)+21), "man", "man", 10, FRANCE, -1, true, "marginal"));
			FantomMakeCoolFighter(sld, 10, 20, 20, RandPhraseSimple("blade_04","blade_06"), "", "", 10);
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "skipertalker";
			sld.greeting = "marginal";
			LAi_SetWarriorType(sld);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "FortFrance_town", "patrol", "patrol"+(rand(13)+1));
			LAi_SetLoginTime(sld, 6.0, 21.99);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		//<-- Бремя гасконца
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx_tortuga":
			sld = characterFromId("Tortuga_waitress");
            dialog.text = "Já vou, monsieur!.. O melhor vinho francês! "+sld.name+"! Vá preparar o melhor quarto de hóspedes! Isso vai custar 1000 pesos, monsieur.";
			link.l1 = "Aqui.";
			link.l1.go = "mtraxx_tortuga_1";
		break;
		
		case "mtraxx_tortuga_1":
			AddMoneyToCharacter(pchar, -1000);
            DialogExit();
			pchar.questTemp.Mtraxx.Retribution = "room";
			pchar.quest.mtraxx_retribution_room.win_condition.l1 = "locator";
			pchar.quest.mtraxx_retribution_room.win_condition.l1.location = "Tortuga_tavern";
			pchar.quest.mtraxx_retribution_room.win_condition.l1.locator_group = "reload";
			pchar.quest.mtraxx_retribution_room.win_condition.l1.locator = "reload2_back";
			pchar.quest.mtraxx_retribution_room.function = "Mtraxx_RetributionToRoom";
		break;
		// belamour постоялец -->
		case "Unwantedpostor_hall_day_wait":
			if (hrand(1) == 1)
            {
                Dialog.text = "Fora daqui, canalha! Você está ocupando espaço valioso de clientes que pagam!";
				link.l1 = "Tudo bem, tá bom... Eu tô indo.";
				link.l1.go = "exit";
            }
            else
            {
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_day");
			}
		break;
		
		case "Unwantedpostor":
				dialog.text = "É, e assustar todos os meus clientes com o fato de que meus guardas arrastam pessoas pra fora da taverna? E alguns dos meus fregueses não gostam de ficar perto de soldados. Isso deixa eles nervosos, entende? Não quero acabar com a minha reputação...";
				link.l1 = "Hum, e se eu resolver o seu problema?";
				link.l1.go = "Unwantedpostor_1";
		break;
		
		case "Unwantedpostor_1":
				dialog.text = "Já decidiu? Ele está armado, parece ser algum tipo de mercenário profissional...";
				link.l1 = "Hmm, você tem razão, não estou com vontade de discutir com um mercenário armado...";
				link.l1.go = "Exit";
				link.l2 = "Bem, eu também não sou nenhuma freira enclausurada... E ainda quero alugar um quarto.";
				link.l2.go = "Unwantedpostor_2";
		break;
		
		case "Unwantedpostor_2":
				dialog.text = "Bem, se você conseguir, aham... convencê-lo a sair, então o quarto é seu até de manhã. Sem custo algum, é claro.";
				link.l1 = "Sabe, mudei de ideia. Não estou a fim de convencer ninguém.";
				link.l1.go = "Exit";
				link.l2 = "Você vai querer ver isso. Seu hóspede indesejado está prestes a voar da sua taverna feito uma gaivota gigante.";
				link.l2.go = "Unwantedpostor_kikcoff";
		break;
		
		case "Unwantedpostor_kikcoff":
				DialogExit();
				chrDisableReloadToLocation = true; //закрыть локацию
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location+"_upstairs")], true); //запретить драться
				iTemp = sti(pchar.rank) + rand(5);
				sld = GetCharacter(NPC_GenerateCharacter("Berglar_Unwantedpostor", "citiz_5"+(rand(3)+1), "man", "man", iTemp, PIRATE, -1, true, "quest")); // "mercen_"+(rand(14)+14)
				FantomMakeCoolFighter(sld, iTemp, 50 + rand(30), 50 + rand(30), "topor_04", "", "bullet", 50);
				sld.dialog.filename = "GenQuests_Dialog.c";
				sld.dialog.currentnode = "Unwantedpostor_room";	
				sld.greeting = "Enc_Raiders"; 
				if (findsubstr(locations[FindLocation(pchar.location)].id, "tavern_upstairs" , 0) == -1)
				{
					DoQuestReloadToLocation(pchar.location+"_upstairs", "quest", "quest4", "");
					ChangeCharacterAddressGroup(sld, pchar.location+"_upstairs", "quest", "quest3");
				} 
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 1.5);
		break;
		// <-- belamour постоялец
		
		case "Helen_room_night":
			dialog.text = "Entendi. São cinco pratas.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "Claro, aqui está.";
				link.l1.go = "room_night_wait";
			}
			link.l2 = "Quer saber... Melhor deixar pra outra hora. Vou passar o resto do dia de pé.";
			link.l2.go = "Helen_night_exit";
		break;
		
		case "Helen_room_day":
			dialog.text = "Decisão sábia. São cinco pratas, e uma boa noite pra você.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "Aqui está, e obrigado - boa noite.";
				link.l1.go = "room_day_wait";
			}
			link.l2 = "Pensando bem, não estou com vontade de dormir. Vou andar pela cidade, respirar um pouco do ar da noite.";
			link.l2.go = "Helen_day_exit";
		break;
		
		case "Helen_room_day_next":
			dialog.text = "Claro, Helen. Serão dez pesos.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "Claro, aqui está.";
				link.l1.go = "room_day_wait_next";
			}
			link.l2 = "Na verdade... Eu poderia fazer algo útil com um dia inteiro. Talvez numa outra ocasião.";
			link.l2.go = "Helen_Next_day_exit";
		break;
		
		case "Helen_night_exit":
			dialog.text = "Como quiser, Helen.";
			link.l1 = "Mhm.";
			link.l1.go = "exit";
		break;
		
		case "Helen_day_exit":
			dialog.text = "Você pode até acabar sentindo sono depois de uma boa caminhada.";
			link.l1 = "Ha-ha, talvez.";
			link.l1.go = "exit";
		break;
		
		case "Helen_next_day_exit":
			dialog.text = "Como preferir.";
			link.l1 = "Bem, até a próxima.";
			link.l1.go = "exit";
		break;
		
		case "Helen_rumours_tavern":
			dialog.text = "Claro, Helen, estou todo ouvidos.";
			link.l1 = "Quais são as novidades ou rumores interessantes na cidade?";
			link.l1.go = "rumours_tavern";
		break;
		
		// Леди Бет -->
		case "LadyBeth_Room":
			dialog.text = "Ele paga o triplo do preço normal, então... você entende. E eu não recomendaria recusar – ele tem um temperamento difícil. Principalmente ultimamente.";
			link.l1 = "O que há de errado com ele?";
			link.l1.go = "LadyBeth_Room_2";
		break;
		
		case "LadyBeth_Room_2":
			dialog.text = "Obsessão, é isso que é. No começo, ele era um sujeito generoso, bondoso. Os marinheiros dele gastavam dinheiro nas tavernas, compravam presentes para as moças. Era uma verdadeira festa quando o 'Lady Beth' chegava ao porto. E agora? Agora eles só compram mantimentos e recrutam gente sem critério. Como se não precisassem de marinheiros, mas apenas de braços para trabalhar. Bem, você pode falar com ele pessoalmente.";
			link.l1 = "Talvez eu faça isso. Obrigado.";
			link.l1.go = "exit";
			pchar.questTemp.LadyBeth_TavernRoomDialog = true;
		break;
		// Леди Бет <--
	}
}

string findTraderCity(ref NPChar)
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES); 
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (colonies[n].id != "Panama" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != GetIslandByColony(&colonies[n])) //не на свой остров
		{
			if (nation == RELATION_ENEMY || sti(npchar.nation) == PIRATE)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hRand(howStore-1)];
	return colonies[nation].id;
}

string findPassangerCity(ref NPChar)
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (colonies[n].nation != "none" && colonies[n].id != "Panama" && GetIslandByCityName(npchar.city) != GetIslandByColony(&colonies[n])) //не на свой остров
		{
			if (nation == RELATION_ENEMY || sti(npchar.nation) == PIRATE)
			{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hRand(howStore-1)];
	return colonies[nation].id;
}
