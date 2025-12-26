// общий диалог ростовщиков
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, chr, sld;
	aref Link, NextDiag;
	string NPC_Area, sTemp, sTitle, sDepositType1, sDepositType2;
	int LoanSum, LoanInterest, LoanPeriod, LoanResult, iPastMonths, DepositSum, DepositInterest, DepositResult, iNum, iTemp, iTotalDublonQty;
	int iRes, iPer, iDep;
	float fPer;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	string iDay, iMonth, s1;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;

	NPC_Area = Npchar.City;
	sDepositType1 = NPC_Area + "_Type1";
	sDepositType2 = NPC_Area + "_Type2";
 
	if(!CheckAttribute(npchar, "quest.item_date"))
	{
		npchar.quest.item_date = "";
	} 
 
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Usurer\" + NPChar.City + "_Usurer.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06

	if (!CheckAttribute(npchar, "quest.trade_date"))
    {
        npchar.quest.trade_date = "";
    }
    if (!CheckAttribute(npchar, "quest.FindCitizenNoShip"))
    {
        npchar.quest.FindCitizenNoShip = 0;
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
			if (LAi_group_GetPlayerAlarm() > 0)
			{
				//--> работорговец
				if(pchar.questTemp.Slavetrader == "After_enterSoldiers" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
				{
					dialog.text = " Acabou. Agora saia daqui, "+pchar.name+". Eu vou limpar toda essa bagunça.";
					link.l1 = "Certo, vou zarpar!";
					link.l1.go = "exit";
					break;
				}
				//<-- работорговец
			
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("A cidade está em alerta e estão procurando por você em todos os cantos! Se eu fosse você, não ficaria aqui por muito tempo.","Todos os guardas estão procurando por você. Não sou idiota e não vou arriscar falar com você!","Corra, "+GetSexPhrase("amigo","garota")+", antes que os soldados te transformem num queijo suíço..."),LinkRandPhrase("O que você quer, criatura vil?! Os guardas da cidade já sabem onde você está e você não vai escapar, "+GetSexPhrase("pirata imundo","sua prostituta pirata")+"!","Assassino imundo, saia do meu estabelecimento! Guardas!","Eu não tenho medo de você, criatura vil! Logo você será enforcado em nosso forte, não vai escapar..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, isso não é problema pra mim...","Eles nunca vão me pegar."),RandPhraseSimple("Cale a boca, "+GetWorkTypeOfMan(npchar,"")+", ou eu arranco sua língua maldita!","Heh, "+GetWorkTypeOfMan(npchar,"")+", quer pegar um pirata também? Escute, rapaz, sente-se aqui quieto e vai sair vivo..."));
				link.l1.go = "fight";
				break;
			}
		//Jason ---------------------------------------Бремя гасконца------------------------------------
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.location == "Fortfrance_bank")
			{
				dialog.text = "Precisa de algo, monsieur?";
				Link.l1 = "Preciso de algumas informações... Quero lhe perguntar sobre algo.";
				Link.l1.go = "quests";
				Link.l2 = "Que tal um pequeno empréstimo?";
				Link.l2.go = "sharlie_credit";
				Link.l3 = "Não, mudei de ideia.";
				Link.l3.go = "exit";
				if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
				{
					link.l4 = "Dê uma olhada nestes brincos, monsieur. Encontrei-os no bolso de um bandido na selva. É claramente obra de um joalheiro refinado, que, tenho certeza, não é daqui deste mato. O que me diz?";
					link.l4.go = "Sharlie_junglejew";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskiper")
				{
					link.l1 = "Eu sei que você tem um devedor chamado Folke Deluc. Diga-me, quão grave é a... inadimplência dele?";
					link.l1.go = "Sharlie";
				}	
				if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipermoney")
				{
					link.l1 = "Estou aqui por causa da dívida de Folke Deluc.";
					link.l1.go = "Sharlie_repeat";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipercaptive")
				{
					link.l1 = "Terminei sua tarefa, monsieur. Aqui está o seu... amigo espanhol.";
					link.l1.go = "Sharlie_14";
				}
				break;
			}			
		//<-- Бремя гасконца
			
			//--> работорговец
			if (pchar.questTemp.Slavetrader == "canTakeQuest" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Finalmente, um capitão digno veio ao meu estabelecimento. Estou tão cansado desses tolos que acham que simplesmente planto seus dobrões e guinéus e os colho todo mês para pagar seus juros.\nEles contam cada moeda, sem imaginar que o pobre agiota precisa recorrer a todo tipo de artimanha para não morrer de fome, enquanto ainda lhes oferece meios de comprar um ganso para o Natal.";
				Link.l1 = "Imagino que seus clientes não ficarão felizes ao ouvir tais palavras do homem que guarda as economias deles.";
				Link.l1.go = "GiveTaskSlave";
				npchar.quest.slave = "current";//чтобы камнем не долбил
				break;
			}	
			
			if (pchar.questTemp.Slavetrader == "TakeShoreCap_end" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "...";
				Link.l1 = "Escuta aqui, velho rato, agora você vai ter que se esforçar pra me explicar tudo direitinho! Não havia escravos na carga daquele navio, só um grupo de soldados! Foi uma missão difícil demais lidar com eles! Estou muito irritado, então é bom você se explicar!";
				Link.l1.go = "Slaveshore_5";
				break;
			}	
			if (pchar.questTemp.Slavetrader == "Win_HavanaFort" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Ah, finalmente você apareceu! O arquipélago inteiro comenta sobre o seu ataque ousado. Que bom te ver!";
				Link.l1 = "Eu prefiro o anonimato a esse tipo de fama... É perigoso demais.";
				Link.l1.go = "Win_Havana_Fort";
				break;
			}	
			if (pchar.questTemp.Slavetrader == "Havana_seekslaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Você trouxe meus cinco mil escravos?";
				if (GetSquadronGoods(Pchar, GOOD_SLAVES) >= 5000)
				{
					Link.l1 = "Sim. Eles estão no meu porão de carga.";
					Link.l1.go = "Havana_Fort_yesA";
				}
				else
				{
					Link.l1 = "Não, ainda estou trabalhando nisso.";
					Link.l1.go = "exit";
				}
				break;
			}	
			
			if (pchar.questTemp.Slavetrader == "End_quest_bad" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Hm... Você ainda está vivo? Que estranho. Mas não vai durar muito. Soldados! Socorro! Tem um bandido aqui!";
				link.l1 = "Que canalha!";
				link.l1.go = "exit";
				LAi_group_Attack(NPChar, Pchar);
				break;
			}
			
			if(pchar.questTemp.Slavetrader == "wait_6" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_6") > 6 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Bom dia. Meu nome é "+GetFullName(npchar)+". Como posso ser útil?";
				link.l1 = "Oh! O que o senhor está fazendo aqui?";
				link.l1.go = "Usurer_Escape";
				break;
			}
			//<-- работорговец
			// ФМК-Гваделупа
			if(CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "killers" && npchar.location == "BasTer_bank")
			{
				dialog.Text = "...";
				link.l1 = "Ei, seu desgraçado. Teve uma ideia brilhante? Contratou capangas pra me matar? Queria me calar? Fala, agora!";
				link.l1.go = "FMQG_x";
				break;
			}
			// Леди Бет -->
			if (pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_Bank" && !CheckAttribute(pchar, "questTemp.LadyBeth_Usurer")) // Блеквуд в городе
			{
				dialog.Text = "Oh, Capitão! Por favor, veja o que eu tenho hoje. Alguns itens que adquiri dos homens do Blackwood. Eles precisam de dinheiro para uma nova expedição e, para nós – lucro, não é?";
				link.l1 = "O Blackwood sabe que os homens dele estão vendendo o que encontram?";
				link.l1.go = "LadyBeth_Usurer_1";
				break;
			}
			// Леди Бет <--
			if(NPChar.quest.meeting == "0")
			{
				dialog.Text = LinkRandPhrase(LinkRandPhrase("Bom dia para você, "+GetAddress_Form(NPChar)+". Como posso ajudá-lo? Eu te conheço?","Entre, capitão. Meu nome é "+GetFullName(npchar)+" e eu sou o banqueiro local.","Prazer em conhecê-lo, "+GetAddress_Form(NPChar)+"! Eu sou um banqueiro local, e se você está com algum problema de dinheiro, então posso ajudá-lo."),LinkRandPhrase("Já nos conhecemos antes, capitão? Eu sou "+GetFullName(npchar)+", e eu sou um banqueiro local.","Entre, Capitão. Meu nome é "+GetFullName(npchar)+" e eu sou o banqueiro local.","Saudações, "+GetAddress_Form(NPChar)+". Eu sou "+GetFullName(npchar)+", o banqueiro local."),LinkRandPhrase("Prazer em conhecê-lo, "+GetAddress_Form(NPChar)+", eu sou "+GetFullName(npchar)+" apenas um banqueiro modesto nesta cidade maravilhosa.","A escolha é sua, capitão! Quer pegar umas moedas emprestadas comigo ou prefere emprestar dinheiro com juros?","Senhor Capitão! Fico muito feliz que tenha vindo ao meu modesto escritório!"));
				link.l1 = RandPhraseSimple(LinkRandPhrase("É um prazer! Eu estava passeando pela cidade e resolvi passar aqui para te ver.","Com prazer, eu sou "+GetFullName(pchar)+", prazer em conhecê-lo.",""+GetFullName(pchar)+" , capitão do navio chamado "+pchar.ship.name+" , prazer em conhecê-lo. Isto aqui é um banco, certo?"),RandPhraseSimple("Prazer em conhecê-lo. Eu sou "+GetFullName(pchar)+". Capitão de um navio chamado "+pchar.ship.name+". Eu só queria te conhecer.","Aha, então vocês têm um banco aqui, certo? Prazer em conhecê-lo, eu sou "+GetFullName(pchar)+", um capitão do meu próprio navio."));
				link.l1.go = "next";
				NPChar.quest.meeting = "1";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_bank")
				{
					dialog.text = "Lady MacArthur, seja bem-vinda, por favor, entre.";
					link.l1 = "E para você, "+npchar.lastname;
					link.l1.go = "Helen_next";
				}
			}
			else
			{
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("É você! O que deseja, "+GetAddress_Form(NPChar)+"?","O que o traz aqui, capitão? Me desculpe, mas sua reputação não faz de você um cliente exatamente desejável.","Aha, outro cliente! No começo achei que você fosse um ladrão... ha-ha, estou só brincando."),LinkRandPhrase("Oh! O que você quer? Isto é um banco, não uma taverna.","Bom dia para você, capitão. Devo informar que sou bastante seletivo ao escolher meus clientes.","O que você quer, "+GetFullName(pchar)+"? Espero que você se lembre de que sua reputação não permite que você faça um grande empréstimo?"),LinkRandPhrase("Espero que queira investir dinheiro, "+GetAddress_Form(NPChar)+"? Não será fácil conseguir um empréstimo para você.","Capitão "+GetFullName(pchar)+" O que você deseja de um humilde banqueiro? Sinto muito, mas não poderei lhe conceder um empréstimo. Só eu posso lhe emprestar dinheiro com juros.","Entre, "+GetAddress_Form(NPChar)+". Sinto muito em informar que você não é o cliente mais bem-vindo, mas normalmente não costumo recusar ninguém de imediato.")),LinkRandPhrase(LinkRandPhrase("Olá, senhor "+GetFullName(pchar)+"! Estou sempre pronto para ajudá-lo com assuntos de negócios.","Olá, senhor "+GetAddress_Form(NPChar)+". Estou sempre pronto para fazer um empréstimo ou aceitar qualquer investimento.","Caro "+GetFullName(pchar)+"! Que bom te ver! O que deseja?"),LinkRandPhrase("Capitão "+GetFullName(pchar)+"! Estou sempre ao seu dispor. Gostaria de fazer um empréstimo ou investir dinheiro a juros?","Saudações, capitão! Você é sempre um cliente bem-vindo aqui. Sua reputação nos negócios é excelente!","Bom dia, "+GetFullName(pchar)+". Fico feliz que tenha me visitado novamente. Espero que tenha vindo em busca de um acordo comercial lucrativo?"),LinkRandPhrase("Bom dia para você, capitão! O que deseja? Veio buscar um empréstimo ou fazer um investimento?","Capitão "+GetFullName(pchar)+"! Deseja emprestar dinheiro em condições vantajosas? Sempre fico feliz em receber um cliente tão respeitável.","Fico feliz em vê-lo novamente, capitão! Estou sempre à disposição para ajudá-lo, seja com um empréstimo ou um investimento.")));
				link.l1 = pcharrepphrase(RandPhraseSimple(LinkRandPhrase("Sem brincadeira, banqueiro, eu tenho um negócio pra tocar aqui.","Você fala demais, camarada. Vamos direto ao assunto.","Já ouviu dizer que dinheiro não tem cheiro? Então tape o nariz e vamos aos negócios."),LinkRandPhrase("E é assim que você recebe seus clientes? Por sorte, estou de bom humor hoje.","Ha! Não está feliz em me ver, hein? E eu não sou uma moeda de ouro para causar uma boa impressão em você. Enfim, vamos aos negócios, agiota.","Ah, eu gostaria de te ensinar um pouco de respeito, mas não tenho tempo pra isso. Vamos falar de dinheiro, então.")),RandPhraseSimple(LinkRandPhrase("Fico feliz em ver meu velho amigo!","Sempre é um prazer vir aqui, meu amigo. Vamos direto ao assunto.","Também estou muito satisfeito. Vamos falar de negócios, amigo."),LinkRandPhrase("Fico muito feliz em conhecê-lo. Quais são as novidades nos mares financeiros?","Fico feliz que ainda se lembre de mim. Estou com pressa, então vamos direto ao assunto.","Olá, velho amigo! Fico feliz em vê-lo novamente!")));
				link.l1.go = "next";
			}
			break;
			
			case "next":
			dialog.text = NPCStringReactionRepeat("Como posso ajudá-lo?","O que deseja desta vez?","Hm... quais são as suas preocupações?","Eh, "+GetAddress_Form(npchar)+", você nem imagina como alguns clientes podem ser irritantes...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Não, obrigado, só estou andando por aí e conversando.","Sou eu de novo. Só queria conversar com você.","Sim, sou eu de novo. Nada sério, só queria conversar com você.","Sim, ser banqueiro nem sempre é tão fácil assim. Só queria conversar...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			link.l2 = "Quero discutir nossos assuntos financeiros.";
			link.l2.go = "LoanUsurer";//(на кредитный генератор)
			link.l3 = "Tenho interesse em joias, ídolos exóticos ou pedras preciosas.";
			if (!isMultiObjectKnown("gold_dublon"))
			{
				link.l3.go = "items_0";
			}
			else
			{
				link.l3.go = "items_1";
			}	
			link.l4 = "Preciso de algumas informações. Bem, tenho algo para te perguntar.";
			link.l4.go = "quests";//(перессылка в файл города)
//Jason, генер почтового курьера 2 уровня
			if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
			{
				if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					link.l12 = "Trouxe os documentos de negócios de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
					link.l12.go = "Postcureer_LevelUp_ForAll";
				}
			}
			//квесты мэра, проникновение во враждебный город
  			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
			{
				link.l7 = RandPhraseSimple("Estou aqui sob as ordens de um homem. Ele é um governador "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" me enviou aqui. Preciso pegar algo com você.");
				link.l7.go = "IntelligenceForAll";
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "usurer_keeper")
			{
				link.l9 = "Bom dia, fui convidado pelo seu filho."; 
				link.l9.go = "EncGirl_4";
				pchar.quest.EncGirl_GetLoverFather.over = "yes";
			}	
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer"))
			{
				link.l10 = "Estou interessado em saber quem é o proprietário do documento.";
				link.l10.go = "ShipLetters_Usurer1";			
			}
			
			//--> семейная реликвия // лесник переписал с нпчара на чара 
			if (CheckAttribute(pchar, "GenQuest.Noblelombard") && npchar.city == pchar.GenQuest.Noblelombard.City && !CheckAttribute(pchar, "quest.noblelombard"))// вот тут 
			{
				link.l11 = "Quero falar sobre a dívida do seu cliente. O nome dele é "+pchar.GenQuest.Noblelombard.Name+". Ele penhorou a relíquia da família. Eu represento os interesses dele aqui, e tenho o direito de discutir a devolução com você.";
				link.l11.go = "Noblelombard";			
			}
			if (CheckAttribute(pchar, "GenQuest.Noblelombard.Giveregard") && npchar.city == pchar.GenQuest.Noblelombard.City)
			{
				link.l11 = "Tivemos uma reunião há três meses e falamos sobre a relíquia de um homem. O nome dele era "+pchar.GenQuest.Noblelombard.Name+". Lembra disso? Ele teve que abrir um depósito em meu nome. A quantia é  "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Regard))+"...";
				link.l11.go = "Noblelombard_5";			
			}
			//<-- семейная реликвия
			
			//-->работорговец
			if (pchar.questTemp.Slavetrader == "Seek_slaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id) 
			{
				link.l8 = "É sobre a sua ... tarefa com os escravos.";
				link.l8.go = "Checkslaves";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Bom dia, "+NPChar.name+", vamos conversar sobre sua tarefa.";
				link.l8.go = "Takeslaves_4_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway_pinas" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Bom dia, "+NPChar.name+", vamos falar sobre a sua tarefa.";
				link.l8.go = "Pinas_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "died" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Bom dia, "+NPChar.name+", vamos falar sobre sua tarefa.";
				link.l8.go = "Takeslaves_4_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait") > 20 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Vim como combinamos. Tem algum trabalho pra mim?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "waitship" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Vim como prometi. Que tal um trabalho?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_1" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_1") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Bom dia, "+npchar.name+". Como vai? Tem uma nova tarefa para mim?";
				link.l8.go = "EscapeSlave";
				break;
			}
			if(pchar.questTemp.Slavetrader == "escapeslave_win" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Sua missão está cumprida. Consegui encontrar aqueles fugitivos. Mas não foi tão fácil assim.";
				link.l8.go = "Escape_slaves_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_2" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_2") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Bom dia, "+npchar.name+". Vim atrás de uma nova tarefa lucrativa.";
				link.l8.go = "Slaveshore";
				break;
			}			
			
			if(pchar.questTemp.Slavetrader == "goodbye" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Más notícias,"+npchar.name+".   Não consegui tomar a brigantina.";
				link.l8.go = "Brig_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goodbye_1" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Olhe,  "+npchar.name+". Eu persegui a brigantina, mas não encontrei nenhum documento. Tem certeza de que estavam lá?";
				link.l8.go = "Letter_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "winbrig" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Boas notícias,"+npchar.name+". Consegui encontrar aquele brigantino e recuperar os documentos. Aqui estão.";
				link.l8.go = "Brig_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_3" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_3") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Bom dia, "+npchar.name+". Você preparou uma nova tarefa para mim?";
				link.l8.go = "SlaveGalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wingalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", consegui interceptar aquele tal 'galeão'.";
				link.l8.go = "Wingalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostgalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", me desculpe, mas não consegui embarcar neste galeão.";
				link.l8.go = "Lostgalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_4" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_4") > 4 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Bom dia, "+npchar.name+". Vim buscar meu dinheiro.";
				link.l8.go = "FindRat";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wincorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", sua missão está completa. Aquele desgraçado do Gontier está morto, assim como a tripulação dele.";
				link.l8.go = "Wincorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostcorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", sinto muito, mas não consegui capturar Francois Gontier, mesmo tendo o seguido até Tortuga. Ele conseguiu escapar de mim em sua corveta.";
				link.l8.go = "lostcorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_5" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_5") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Bom dia,"+npchar.name+". Conte-me sobre essa nova missão que você preparou para mim.";
				link.l8.go = "Havana_fort";
				break;
			}
			//<--работорговец
			NextDiag.TempNode = "First time";
		break;
		
		case "Helen_next":
			dialog.text = NPCStringReactionRepeat("Eu não diria que você está precisando de dinheiro ou tentando aumentar sua fortuna. O que o traz ao meu escritório?","O que você quer desta vez?","Hm... quais são as suas preocupações?","Eh, "+GetAddress_Form(npchar)+", você nem imagina como alguns clientes podem ser irritantes...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Não, obrigado, só estou andando por aí e conversando.","Sou eu de novo. Só queria conversar com você.","Sim, sou eu de novo. Nada sério, só queria conversar com você.","Sim, ser banqueiro nem sempre é tão fácil assim. Só queria conversar...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			link.l2 = "Quero discutir nossos assuntos financeiros.";
			link.l2.go = "LoanUsurer";//(на кредитный генератор)
			link.l3 = "Tenho interesse em joias, ídolos exóticos ou pedras preciosas.";
			if (!isMultiObjectKnown("gold_dublon"))
			{
				link.l3.go = "items_0";
			}
			else
			{
				link.l3.go = "items_1";
			}	
			link.l4 = "Preciso de algumas informações. Bem, tenho algo para te perguntar.";
			link.l4.go = "quests";//(перессылка в файл города)
//Jason, генер почтового курьера 2 уровня
			if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
			{
				if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					link.l12 = "Trouxe os documentos de negócios de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
					link.l12.go = "Postcureer_LevelUp_ForAll";
				}
			}
			//квесты мэра, проникновение во враждебный город
  			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
			{
				link.l7 = RandPhraseSimple("Estou aqui sob as ordens de um homem. Ele é um governador "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" me mandou aqui. Preciso pegar algo com você.");
				link.l7.go = "IntelligenceForAll";
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "usurer_keeper")
			{
				link.l9 = "Bom dia, fui convidado pelo seu filho."; 
				link.l9.go = "EncGirl_4";
				pchar.quest.EncGirl_GetLoverFather.over = "yes";
			}	
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer"))
			{
				link.l10 = "Estou interessado em saber quem é o dono do documento.";
				link.l10.go = "ShipLetters_Usurer1";			
			}
			
			//--> семейная реликвия // лесник переписал с нпчара на чара 
			if (CheckAttribute(pchar, "GenQuest.Noblelombard") && npchar.city == pchar.GenQuest.Noblelombard.City && !CheckAttribute(pchar, "quest.noblelombard"))// вот тут 
			{
				link.l11 = "Quero falar sobre a dívida do seu cliente. O nome dele é "+pchar.GenQuest.Noblelombard.Name+". Ele penhorou a relíquia da família. Eu represento os interesses dele aqui e tenho o direito de discutir a devolução com você.";
				link.l11.go = "Noblelombard";			
			}
			if (CheckAttribute(pchar, "GenQuest.Noblelombard.Giveregard") && npchar.city == pchar.GenQuest.Noblelombard.City)
			{
				link.l11 = "Tivemos uma reunião há três meses e falamos sobre a relíquia de um homem. O nome dele era "+pchar.GenQuest.Noblelombard.Name+". Lembra disso? Ele teve que abrir um depósito em meu nome. A quantia é  "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Regard))+"...";
				link.l11.go = "Noblelombard_5";			
			}
			//<-- семейная реликвия
			
			//-->работорговец
			if (pchar.questTemp.Slavetrader == "Seek_slaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id) 
			{
				link.l8 = "É sobre a sua ... tarefa com os escravos.";
				link.l8.go = "Checkslaves";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Bom dia, "+NPChar.name+", vamos falar sobre a sua tarefa.";
				link.l8.go = "Takeslaves_4_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway_pinas" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Bom dia, "+NPChar.name+", vamos conversar sobre sua tarefa.";
				link.l8.go = "Pinas_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "died" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Bom dia, "+NPChar.name+", vamos falar sobre a sua tarefa.";
				link.l8.go = "Takeslaves_4_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait") > 20 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Vim como combinamos. Tem algum trabalho pra mim?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "waitship" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Vim como prometi. Que tal um trabalho?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_1" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_1") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Bom dia, "+npchar.name+". Como está indo? Tem uma nova tarefa para mim?";
				link.l8.go = "EscapeSlave";
				break;
			}
			if(pchar.questTemp.Slavetrader == "escapeslave_win" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Sua missão está cumprida. Consegui encontrar aqueles fugitivos. Mas não foi tão fácil assim.";
				link.l8.go = "Escape_slaves_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_2" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_2") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Bom dia, "+npchar.name+". Vim atrás de uma nova tarefa lucrativa.";
				link.l8.go = "Slaveshore";
				break;
			}			
			
			if(pchar.questTemp.Slavetrader == "goodbye" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Más notícias,"+npchar.name+".   Não consegui pegar a brigantina.";
				link.l8.go = "Brig_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goodbye_1" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Olha,  "+npchar.name+". Eu persegui a brigantina, mas não encontrei nenhum documento. Tem certeza de que eles estavam lá?";
				link.l8.go = "Letter_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "winbrig" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Boas notícias,"+npchar.name+". Consegui encontrar aquele brigantino e recuperar os documentos. Aqui estão.";
				link.l8.go = "Brig_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_3" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_3") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Bom dia, "+npchar.name+". Você preparou uma nova tarefa para mim?";
				link.l8.go = "SlaveGalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wingalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", consegui interceptar aquele tal 'galeão'.";
				link.l8.go = "Wingalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostgalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", me desculpe, mas eu não consegui abordar esse galeão.";
				link.l8.go = "Lostgalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_4" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_4") > 4 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Bom dia, "+npchar.name+". Vim buscar meu dinheiro.";
				link.l8.go = "FindRat";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wincorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", sua missão está concluída. Aquele desgraçado do Gontier está morto, assim como toda a sua tripulação.";
				link.l8.go = "Wincorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostcorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", sinto muito, mas não consegui capturar Francois Gontier, embora eu o tenha seguido até Tortuga. Ele conseguiu escapar de mim em sua corveta.";
				link.l8.go = "lostcorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_5" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_5") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Bom dia,"+npchar.name+". Conte-me sobre essa nova missão que você preparou para mim.";
				link.l8.go = "Havana_fort";
				break;
			}
			//<--работорговец
			NextDiag.TempNode = "First time";
		break;

		case "items_0":
			dialog.text = "Quer comprar alguns dobrões de ouro ou baús para eles? Acredite, é um investimento muito valioso.";
			link.l1 = "Sim, isso é muito interessante.";
			link.l1.go = "items";
			AddQuestRecordInfo("Recipe", "Gold_dublon");
			SetAlchemyRecipeKnown("gold_dublon");
			SetAlchemyRecipeKnown("Chest");
			npchar.quest.meeting = "1"; 			
		break;
		
		case "items_1":
			dialog.text = "Você quer negociar em pesos ou dobrões?";
			link.l1 = "Por pesos.";
			link.l1.go = "items";
			link.l2 = "Por dobrões.";
			link.l2.go = "items_dub";
		break;
		
		case "items":
			if (npchar.quest.item_date != lastspeak_date)
			{
				GiveItemToTrader(npchar);
				npchar.quest.item_date = lastspeak_date;
			}
			if(CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu")) AddItems(npchar, "gold_dublon", 100);
			if(CheckAttribute(pchar, "questTemp.Del_Rostovshik_repeat")) AddItems(npchar, "gold_dublon", 100);
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
		break;
		
		case "items_dub":
			if (npchar.quest.item_date != lastspeak_date)
			{
				GiveItemToTrader(npchar);
				npchar.quest.item_date = lastspeak_date;
			}
			if(CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu")) AddItems(npchar, "gold_dublon", 100);
			if(CheckAttribute(pchar, "questTemp.Del_Rostovshik_repeat")) AddItems(npchar, "gold_dublon", 100);
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 1);
		break;
		
		//<<<<----------генератор -"Shipping documents". ------		
		case "ShipLetters_Usurer1":
			pchar.questTemp.different.GiveShipLetters.speakUsurer = true;
			dialog.text = "Vai me tomar muito tempo para ler esses papéis e o meu tempo custa caro.";
			link.l1 = "Talvez, "+sti(pchar.questTemp.different.GiveShipLetters.price1)+" pesos vão compensar pelo seu tempo?";
			link.l1.go = "ShipLetters_Usurer2";
			link.l2 = "Como desejar. Adeus!";
			link.l2.go = "exit";
		break;
		
		case "ShipLetters_Usurer2":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.GiveShipLetters.price1));
			pchar.questTemp.different.GiveShipLetters.speakUsurer_1 = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Deixe-me ver! Não, nunca vi esse nome antes. Mostre isso ao nosso mestre do porto.";
				link.l1 = "Sinto muito, mas nós tínhamos um acordo! Você prometeu me contar sobre esse capitão!";
				link.l1.go = "ShipLetters_Usurer2_1";
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
			{
				s1 = "Well... I know the owner of this ship. He is not a very rich man, but he has some wealth.";
				dialog.text = s1+" Dizem que ele é um contrabandista de sucesso. Era isso que você queria ouvir?";
				link.l1 = "Parece que sim...";
				link.l1.go = "ShipLetters_Usurer2_2";
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
			{
				s1 = "Well... I am not sure that I can congratulate you for your found.";
				dialog.text = s1+"Estes documentos estão assinados para o nosso navio de patrulha colonial, e seu capitão é conhecido por seus princípios firmes.";
				link.l1 = "Uma patrulha? Sob as ordens do comandante?";
				link.l1.go = "ShipLetters_Usurer2_3";
			}
		break;
		
		case "ShipLetters_Usurer2_1":
			dialog.text = "Eu prometi que daria uma olhada nesses papéis e nada mais. Pode ir.";
			link.l1 = "Obrigado... eu acho.";
			link.l1.go = "exit";
		break;
		
		case "ShipLetters_Usurer2_2":
			dialog.text = "A decisão é sua. Nosso comandante tem demonstrado um certo 'interesse' nessa pessoa há bastante tempo. Já tem alguma ideia? E aqui temos conhecimentos de embarque sem nenhuma marca...";
			link.l1 = "Entendo. Muito obrigado!";
			link.l1.go = "exit";		
		break;
		
		case "ShipLetters_Usurer2_3":
			s1 = "Exactly. Our smugglers are bearing a grudge against this captain by the way.";
			dialog.text = s1+"E como mencionei antes, o dono do documento é um homem de princípios e não gosta muito de crimes locais.";
			link.l1 = "Entendo. Minha gratidão!";
			link.l1.go = "exit";		
		break;

		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "Ah, presumo que você seja o capitão que trouxe meu filho pródigo e sua jovem esposa?";
				link.l1 = "Sim, fui eu quem os ajudou a escapar.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "Ah, aqui está você, meu benfeitor. Esperando uma recompensa, imagino?";
				link.l1 = "Sua gratidão já seria suficiente, pelo menos...";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "Sou realmente grato por ter ajudado meu filho e não deixado ele naquela situação difícil. Por favor, permita-me agradecer da melhor forma que posso. Aceite esta quantia modesta e um pequeno presente meu.";
			link.l1 = "Meus agradecimentos. Foi um prazer ajudar esse jovem casal.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "Obrigado? Pelo quê? Esse cabeça-oca ficou desempregado metade do ano e já arranjou tempo pra conseguir uma garota! Eu já tocava meu próprio negócio na idade dele. Tem a filha de um governador pronta pra casar, e ele me aparece com essa vadia aqui—Deus me perdoe por dizer isso! E agora ainda quer minha bênção!";
			link.l1 = "Imagino que você não acredita em sentimentos?";
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
			dialog.text = "Sentimentos? Que tipo de sentimentos? Você é um homem feito e ainda fala de sentimentos? Que vergonha, se rebaixando assim para agradar os mais jovens. Você tirou a moça dos pais dela e destruiu a vida do meu filho. Não espere nenhum agradecimento da minha parte. Adeus.";
			link.l1 = "Então, adeus...";
			link.l1.go = "EncGirl_6_2";
		break;
		
		case "EncGirl_6_2":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("saw","saw"));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		Кредитный генератор Loan
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "LoanUsurer":
			if (npchar.id == "Panama_Usurer")
			{
				if (sti(pchar.reputation.nobility) > 70 && ChangeCharacterNationReputation(pchar, SPAIN, 0) >= 80 && !CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold"))
				{
					dialog.text = "Vamos conversar sobre isso. Estou ouvindo.";
				}
				else
				{
					dialog.text = "Ah, ah. Receio que terei de recusar sua proposta. "+GetAddress_Form(NPChar)+". Sinto muito, mas meu banco não oferece serviços aos inimigos da Espanha.";
					link.l1 = "O dinheiro não tem nacionalidade, senhor banqueiro.";
					if (CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold"))
					{
						if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)) && makeint(Pchar.Quest.Deposits.(sDepositType1)) == true)
						{
							dialog.text = "Uhum, "+GetAddress_Form(NPChar)+". Devo informar que seu depósito não é mais válido.";
							Link.l1 = "Com que direito?!";
							Link.l1.go = "Panama_Deposit_SgorelVklad";
							DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
							break;						
						}
						else
						{
							link.l1.go = "Panama_Deposit_Cartahena";
							break;
						}
					}
					if (sti(pchar.reputation.nobility) < 71 || ChangeCharacterNationReputation(pchar, SPAIN, 0) < 80)
					{
						link.l1.go = "Panama_Deposit_NoReputation";
						break;
					}
				}
			}
			dialog.text = "Vamos conversar sobre isso. Estou ouvindo.";
			//кредиты
            if(CheckAttribute(Pchar, "Quest.Loans." + (NPC_Area)) && makeint(Pchar.Quest.Loans.(NPC_Area)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Loans.(NPC_Area).StartYear),makeint(Pchar.Quest.Loans.(NPC_Area).StartMonth),makeint(Pchar.Quest.Loans.(NPC_Area).StartDay), makefloat(Pchar.Quest.Loans.(NPC_Area).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				Pchar.Quest.Loans.(NPC_Area).Result = makeint(Pchar.Quest.Loans.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Loans.(NPC_Area).Sum)/100)*makefloat(Pchar.Quest.Loans.(NPC_Area).Interest))*(iPastMonths+1);// boal 23.01.2004
				if(makeint(PChar.money) >= makeint(Pchar.Quest.Loans.(NPC_Area).Result))
				{
					Link.l5 = "Estou te devendo "+FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).Result))+LinkRandPhrase(", estou pronto para devolver seu dinheiro",". Quero quitar a dívida.",".  Finalmente, chegou a hora de acertar as contas.");
					Link.l5.go = "loan_return";	
					sTemp = "credit";
				}					
			}
			else
			{
				Link.l6 = LinkRandPhrase("Gostaria de pegar algumas moedas emprestadas.","Eu realmente preciso conseguir alguns pesos.","Que tal um pequeno empréstimo?");
				Link.l6.go = "loan";					
				if(makeint(Pchar.money) >= 100)
				{
					Link.l7 = LinkRandPhrase("Gostaria de depositar meu dinheiro para receber juros.","Você aceitaria guardar alguns sacos da minha prata?","Posso deixar algumas moedas de prata com você para tempos difíceis?"); // patch
					Link.l7.go = "deposit";				
				}			
				if(CheckUseDublons(NPChar))
				{
					Link.l8 = "Quero depositar alguns dobrões para render juros.";
					Link.l8.go = "deposit_dub";				
				}
			}
			
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)) && makeint(Pchar.Quest.Deposits.(sDepositType1)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Deposits.(sDepositType1).StartYear),makeint(Pchar.Quest.Deposits.(sDepositType1).StartMonth),makeint(Pchar.Quest.Deposits.(sDepositType1).StartDay), makefloat(Pchar.Quest.Deposits.(sDepositType1).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)+ ".Rem"))
				{
					Pchar.Quest.Deposits.(sDepositType1).Result = makeint(Pchar.Quest.Deposits.(sDepositType1).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType1).Sum)/100)*makefloat(Pchar.Quest.Deposits.(sDepositType1).Interest))*iPastMonths+sti(Pchar.Quest.Deposits.(sDepositType1).Rem);
				}
				else
				{
					Pchar.Quest.Deposits.(sDepositType1).Result = makeint(Pchar.Quest.Deposits.(sDepositType1).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType1).Sum)/100)*makefloat(Pchar.Quest.Deposits.(sDepositType1).Interest))*iPastMonths;
				}
				Link.l9 = LinkRandPhrase("Vim buscar meu investimento de volta, em pesos.","Está na hora de receber a prata que você me deve.","Preciso do meu investimento de volta em pesos, com todos os juros.");
				Link.l9.go = "Deposit_return";									
			}
			
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)) && makeint(Pchar.Quest.Deposits.(sDepositType2)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Deposits.(sDepositType2).StartYear),makeint(Pchar.Quest.Deposits.(sDepositType2).StartMonth),makeint(Pchar.Quest.Deposits.(sDepositType2).StartDay), makefloat(Pchar.Quest.Deposits.(sDepositType2).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)+ ".Rem"))
				{
					Pchar.Quest.Deposits.(sDepositType2).Result = makeint(Pchar.Quest.Deposits.(sDepositType2).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType2).Sum)/100)*makeint(Pchar.Quest.Deposits.(sDepositType2).Interest))*iPastMonths+sti(Pchar.Quest.Deposits.(sDepositType2).Rem);
				}
				else
				{
					Pchar.Quest.Deposits.(sDepositType2).Result = makeint(Pchar.Quest.Deposits.(sDepositType2).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType2).Sum)/100)*makeint(Pchar.Quest.Deposits.(sDepositType2).Interest))*iPastMonths;
				}
				Link.l10 = LinkRandPhrase("Quero recuperar meu investimento em dobrões.","Está na hora de recuperar o ouro que você me deve.","Preciso que meu investimento em dobrões seja devolvido, com todos os juros.");
				Link.l10.go = "Deposit_return_dub";									
			}
/*			
			
*/			
			//выход
			if (sTemp == "credit")
			{
				link.l11 = "Eu me lembro da minha dívida, mas ainda não estou pronto para pagá-la...";
				link.l11.go = "Loan_Remind";
			}
			else
			{
				link.l11 = "Me enganei, não tenho negócios financeiros com você. Adeus.";
				link.l11.go = "exit";
			}
		break;
		
		//============== кредиты ===============
		case "loan":
            if (sti(NPChar.nation) == PIRATE)
            {
                dialog.text = "Não, não posso ajudá-lo. Só posso aceitar investimentos neste lugar problemático. Você pode investir pesos de prata ou dobrões de ouro.";				
                if(makeint(Pchar.money) >= 100)
				{
	                Link.l1 = "Quero investir pesos, então vamos conversar sobre o valor.";
	                Link.l1.go = "deposit";
				}				
				if(CheckUseDublons(NPChar))
				{
					Link.l2 = "Quero investir dobrões. Vamos definir o valor.";
					Link.l2.go = "deposit_dub";
				}
                Link.l3 = "Não estou interessado.";
				link.l3.go = "exit";
                break;
            }
			// проверка на проф пригодность -->
            if (isBadReputation(pchar, 42))
            {
                dialog.text = RandSwear()+"Seu nome é "+GetFullName(pchar)+", certo? Você tem "+RandPhraseSimple("uma má reputação ","uma má reputação ")+" e eu não quero fazer negócios com você.";
				link.l1 = RandPhraseSimple("Um homem não pode cometer um erro?",RandSwear()+"Tanto faz!");
				link.l1.go = "exit";
                break;
            }
            // проверка на проф пригодность <--
			Dialog.snd = "voice\USDI\USDI016";
			dialog.text = "Oh, você é sempre bem-vindo. De quanto precisa?";
			Link.l1 = "Um pequeno.";
			Link.l1.go = "Small";
			Link.l2 = "Moderado.";
			Link.l2.go = "Medium";
			Link.l3 = "O maior possível.";
			Link.l3.go = "Large";
		break;

		case "small":
			Pchar.Quest.Loans.(NPC_Area).Sum = 500*makeint(Pchar.rank)+125*GetSummonSkillFromName(pchar,SKILL_COMMERCE);
			Dialog.snd = "voice\USDI\USDI017";
			dialog.text = "Excelente! Sempre é muito mais fácil lidar com quantias pequenas – menos risco para ambos os lados. Posso lhe oferecer "+FindRussianMoneyString(sti(Pchar.Quest.loans.(NPC_Area).sum))+"...";
			Link.l1 = "Fechado. E quanto à sua parte?";
			Link.l1.go = "Interest";
			Link.l2 = "Isso não vai funcionar pra mim. Vamos mudar isso.";
			Link.l2.go = "Loan";
			Link.l3 = "Acho que é melhor não se endividar por minha causa. Adeus.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Medium":
			Pchar.Quest.Loans.(NPC_Area).Sum = 1500*makeint(Pchar.rank)+325*GetSummonSkillFromName(pchar,SKILL_COMMERCE);
			Dialog.snd = "voice\USDI\USDI018";
			dialog.text = "Sem problema. Espero que "+FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).sum))+" vou ajudar você a resolver seus problemas. Esta é uma quantia considerável.";
			Link.l1 = "Combinado. E quanto à sua parte?";
			Link.l1.go = "Interest";
			Link.l2 = "Isso não vai funcionar para mim. Vamos mudar isso.";
			Link.l2.go = "Loan";
			Link.l3 = "Acho melhor eu me manter longe de dívidas. Adeus.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Large":
			Pchar.Quest.Loans.(NPC_Area).Sum = 4000*makeint(Pchar.rank)+600*GetSummonSkillFromName(pchar,SKILL_COMMERCE);
			Dialog.snd = "voice\USDI\USDI019";
			dialog.text = "Bem... é arriscado. Tudo bem, estou pronto para lhe conceder um empréstimo de "+FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).sum))+". Espero que compreenda, capitão, esta é realmente uma quantia considerável. Peço que leve isso a sério.";
			Link.l1 = "Fechado. E quanto à sua parte?";
			Link.l1.go = "Interest";
			Link.l2 = "Isso não vai funcionar para mim. Vamos mudar isso.";
			Link.l2.go = "Loan";
			Link.l3 = "Acho melhor eu ficar longe de dívidas. Adeus.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Interest":
			Pchar.Quest.Loans.(NPC_Area).Interest = 4.0 + (makeint((((6.0 - 4.0) * (GetSummonSkillFromName(pchar, "Commerce") + GetSummonSkillFromName(pchar, "Leadership")) / 200) ) / 0.5 + 0.5)) * 0.5;
			//Pchar.Quest.Loans.(NPC_Area).Interest = 16 - makeint(Pchar.skill.commerce);
			// Rebbebion, добавил фикс отображения знака процента
			Dialog.snd = "voice\USDI\USDI020";
			dialog.text = fts(stf(Pchar.Quest.Loans.(NPC_Area).Interest),1)+"%% ao mês. Não posso lhe oferecer condições melhores com base no que sei sobre você."; 
			Link.l1 = "Por mim tudo bem. Vamos falar sobre o tempo.";
			Link.l1.go = "Period";
			Link.l3 = "Acho que é melhor eu me manter longe das dívidas. Adeus.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Period":
			Pchar.Quest.Loans.(NPC_Area).Period = makeint(makeint(Pchar.reputation.nobility)/20) + 1;			
			Dialog.snd = "voice\USDI\USDI021";
			dialog.text = "Levando em conta o que eu sei sobre você, "+Pchar.name+", aguardarei o retorno deste empréstimo por "+FindRussianMonthString(sti(Pchar.Quest.Loans.(NPC_Area).Period))+". Depois disso, tomarei certas providências. Espero que compreenda isso."; 
			Link.l1 = "Eu aceito de bom grado seus termos... e suas moedas.";
			Link.l1.go = "LoanGranted";
			Link.l3 = "Com licença, mas isso não serve para mim. Adeus.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "LoanGranted":
			Dialog.snd = "voice\USDI\USDI022";
			dialog.text = "Fico sinceramente feliz. Mas permita-me avisar. Faço isso há muito tempo e sei como recuperar meus investimentos. Então, se algum dia tiver ideias tolas, sugiro que as deixe de lado\nSem ofensa, apenas um aviso.";
			Link.l1 = "Hm... Bem. Adeus.";
			Link.l1.go = "LoanGranted_exit";
		break;

		case "Loan_Remind":
			Dialog.snd = "voice\USDI\USDI023";
			dialog.text = "A decisão é sua, capitão. Meus juros continuam aumentando e você não tem tanto tempo assim.";
			Link.l1 = "Não se preocupe com isso. Até logo.";
			Link.l1.go = "exit";
		break;

		case "loan_return":
			addMoneyToCharacter(Pchar, -(makeint(Pchar.Quest.Loans.(NPC_Area).Result)));
			// boal 27.01.2004 -->
            if (npchar.quest.trade_date != lastspeak_date) // дыра с прокачкой была
            {
    			AddCharacterExpToSkill(Pchar, "Commerce", makeint(Pchar.Quest.Loans.(NPC_Area).Result) / 350);
    			AddCharacterExpToSkill(Pchar, "Leadership", makeint(Pchar.Quest.Loans.(NPC_Area).Result) / 700);
			}
			// boal 27.01.2004 <--
			DeleteAttribute(PChar, "quest.Loans_" + NPC_Area); // bug fix
			DeleteAttribute(PChar, "quest.Loans." + NPC_Area);
			Dialog.snd1 = "voice\USDI\USDI024";
			Dialog.snd2 = "voice\USDI\USDI025";
			Dialog.snd3 = "voice\USDI\USDI026";
			dialog.text = LinkRandPhrase("Maravilhoso! Venha até mim quando precisar de moedas. Estarei ao seu dispor a qualquer momento.","Minha gratidão. É sempre um prazer lidar com um homem que consegue pagar suas dívidas em dia. Às vezes, imprevistos acontecem, eu entendo... mas prefiro que os problemas sejam resolvidos.","Ah, eu estava certo em confiar em você, "+GetAddress_Form(NPChar)+"! Espero que esta não seja a última vez que você use meus serviços. Talvez possamos fechar negócios ainda melhores para você, agora que sei que é um homem honesto.");
			Link.l1 = LinkRandPhrase("Quero pegar um empréstimo.","Eu realmente preciso conseguir alguns pesos.","Que tal um pequeno empréstimo?");
			Link.l1.go = "loan";			
			if(makeint(PChar.money) >= 100)
			{
				Link.l2 = LinkRandPhrase("Gostaria de investir meu dinheiro.","Você vai guardar algum tesouro pirata?","Posso deixar algumas moedas de prata com você para um dia chuvoso?");
				Link.l2.go = "deposit";				
			}		
			if(CheckUseDublons(NPChar))	
			{
				Link.l3 = "Quero investir alguns dobrões para receber juros";
				Link.l3.go = "deposit_dub";				
			}
			Link.l4 = "Adeus, "+NPchar.name+".";
			Link.l4.go = "ExitDelLoan1";
		break;

		case "deposit":
			dialog.text = LinkRandPhrase("Vejo um homem sábio! Qual valor gostaria de investir?","Certo. Confie em mim, essa quantia ficará aqui em segurança, rendendo todos os seus juros.","Vejo que você sabe o que realmente importa nesta vida. Quanto gostaria de investir?");
			link.l1.edit = 3;
			link.l1 = "";	
			Link.l1.go = "result";
		break;
		
		case "result":
			Pchar.QuestTemp.Deposits.(sDepositType1).Interest = GetDepositRate();
			Pchar.QuestTemp.Deposits.(sDepositType1).Sum = dialogEditStrings[3];
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp <= 0)
			{
				dialog.text = "Brincando, é?";
				link.l1 = "Foi meu erro.";
				link.l1.go = "exit";
				break;
			}
			if (iTemp > sti(pchar.money))
			{
				dialog.text = "Hum, infelizmente você não tem tanto dinheiro assim. Vamos falar sério...";
				link.l1 = "Certo.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Certo. Posso te oferecer... digamos..."+fts(stf(Pchar.QuestTemp.Deposits.(sDepositType1).Interest),1)+" %. Por mês, é claro.";
			Link.l1 = "Funciona para mim.";
			Link.l1.go = "Deposit_placed";
			Link.l2 = "É melhor eu mudar o valor.";
			Link.l2.go = "Deposit";
			Link.l3 = "Parece que isso foi uma má ideia... Adeus.";
			Link.l3.go = "Exit";
		break;

		case "Deposit_placed":
			Dialog.snd = "voice\USDI\USDI033";
			if ( !CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)+".Result"))
			{
			    Pchar.Quest.Deposits.(sDepositType1).Result = 0;//fix
			}
			// boal limit
			if ( (sti(Pchar.Quest.Deposits.(sDepositType1).Result) + sti(Pchar.QuestTemp.Deposits.(sDepositType1).Sum)) > sti(NPChar.UsurerDeposit)*1000)
			{
			    dialog.text = "Perdoe-me, capitão, mas essa quantia é grande demais para o meu banco colonial. Não vou conseguir lhe pagar os juros. E a falta de uma escolta confiável... Espero que compreenda. De qualquer forma, o valor máximo que posso aceitar de você é "+FindRussianMoneyString(MakeMoneyShow(sti(NPChar.UsurerDeposit)*1000,MONEY_SIGN,MONEY_DELIVER))+".";
				Link.l1 = "Que pena, então terei que procurar outro banqueiro.";
				Link.l1.go = "Exit";
			}
			else
			{
				dialog.text = "Agora você pode ter certeza de que nem a tempestade mais feroz vai te deixar sem uma moeda.";
				Link.l1 = "Certo. Até mais.";
				Link.l1.go = "Deposit_Exit";
			}
		break;
		
		case "Deposit_return":
			Dialog.snd = "voice\USDI\USDI034";
			dialog.text = "Considerando os juros prometidos e o tempo que passou, devo a você "+FindRussianMoneyString(sti(Pchar.Quest.Deposits.(sDepositType1).Result))+"... Tem certeza de que quer pegar o dinheiro?";
			Link.l1 = "Com certeza. Me entregue.";			
			Link.l1.go = "Deposit_return_1";		
			Link.l2 = "Quero retirar parte do meu dinheiro.";			
			Link.l2.go = "Deposit_return_part";
			Link.l3 = "Você tem razão. Vou deixar com você por um tempo. Tenha um bom dia.";			
			Link.l3.go = "Exit";		
		break;		
		
		case "Deposit_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)+ ".Rem"))
			{
				DeleteAttribute(Pchar,"Quest.Deposits." + (sDepositType1)+ ".Rem");
			}
			Pchar.Quest.Deposits.(sDepositType1).Interest = stf(Pchar.QuestTemp.Deposits.(sDepositType1).Interest);
			Pchar.Quest.Deposits.(sDepositType1).Sum      = sti(Pchar.QuestTemp.Deposits.(sDepositType1).Sum);
			Pchar.Quest.Deposits.(sDepositType1).city 	  = NPC_Area;	

			AddMoneyToCharacter(Pchar, -(makeint(Pchar.Quest.Deposits.(sDepositType1).Sum)));
			// общий долг
			Pchar.Quest.Deposits.(sDepositType1).Sum = sti(Pchar.Quest.Deposits.(sDepositType1).Result) + sti(Pchar.Quest.Deposits.(sDepositType1).Sum);
			Pchar.Quest.Deposits.(sDepositType1) = true;
			Pchar.Quest.Deposits.(sDepositType1).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType1).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType1).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType1).StartTime 	= getTime();
			DialogExit();
		break;
		
		//--> Jason забор денег по частям
		case "Deposit_return_part":
			dialog.text = "E quanto?";
			link.l1.edit = 4;
			link.l1 = "";	
			Link.l1.go = "result_part";
		break;

		case "result_part":
			iTemp = sti(dialogEditStrings[4]);
			if (iTemp <= 0)
			{
				dialog.text = "Que piada mais idiota, senhor!";			
				link.l1 = "Droga! Me desculpe... Vamos mudar o valor.";	
				Link.l1.go = "Deposit_return_part";
				break;
			}
			if (iTemp > sti(Pchar.Quest.Deposits.(sDepositType1).Result))
			{
				dialog.text = "Você não tem tanto dinheiro assim na sua conta.";			
				link.l1 = "Droga! Foi meu erro. Vamos mudar o valor.";	
				Link.l1.go = "Deposit_return_part";
				break;
			}
			if (iTemp == sti(Pchar.Quest.Deposits.(sDepositType1).Result))
			{
				dialog.text = "Tudo isso? Muito bem, como quiser. Aqui está o seu dinheiro.";			
				link.l1 = "Obrigado!";	
				Link.l1.go = "Deposit_return_all";
				break;
			}
			dialog.text = "Certo. Pegue. Aqui está o seu dinheiro.";			
			link.l1 = "Obrigado!";	
			Link.l1.go = "result_part_1";
		break;
		
		case "result_part_1":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			addMoneyToCharacter(Pchar, iTemp);
			iRes = sti(Pchar.Quest.Deposits.(sDepositType1).Result)-iTemp; //остаток на счете
			fPer = stf(Pchar.Quest.Deposits.(sDepositType1).Interest);
			iDep = sti(Pchar.Quest.Deposits.(sDepositType1).Sum); //стартовая сумма
			if (iRes <= sti(Pchar.Quest.Deposits.(sDepositType1).Sum)) // стало меньше начальной суммы
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
				Pchar.Quest.Deposits.(sDepositType1).Interest = fPer;
				Pchar.Quest.Deposits.(sDepositType1).Sum = iRes;
				Pchar.Quest.Deposits.(sDepositType1).Result = 0;
			}
			else // если остаток больше начальной суммы - проценты продолжаем считать с неё, а не с остатка, ибо нефиг, дельту приплюсуем к набежавшим процентам - банкир Jason :) 
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
				Pchar.Quest.Deposits.(sDepositType1).Interest = fPer;
				Pchar.Quest.Deposits.(sDepositType1).Sum = iDep;
				Pchar.Quest.Deposits.(sDepositType1).Rem = iRes-iDep;
			}
			Pchar.Quest.Deposits.(sDepositType1).city 	  	= NPC_Area;	
			Pchar.Quest.Deposits.(sDepositType1) 			= true;
			Pchar.Quest.Deposits.(sDepositType1).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType1).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType1).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType1).StartTime 	= getTime();
		break;
		
		case "Deposit_return_all":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			addMoneyToCharacter(Pchar, iTemp);
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
		break;
		//<-- забор денег по частям		
		
		case "Deposit_return_1":
			addMoneyToCharacter(Pchar, makeint(Pchar.Quest.Deposits.(sDepositType1).Result));
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "Oh... É tão difícil perder isso. Eu realmente me apeguei a esse dinheiro. Volte sempre, de qualquer forma.";			
			Link.l1 = "Farei isso se for necessário. Adeus.";			
			Link.l1.go = "Exit";
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
		break;
		
		//  ugeen -> вклады в дублонах	
		case "deposit_dub":
			dialog.text = LinkRandPhrase("Vejo um homem sábio! Que quantia gostaria de investir?","Certo. Confie em mim, essa quantia ficará aqui em segurança, rendendo todos os seus juros.","Vejo que você sabe o que realmente importa nesta vida. Quanto gostaria de investir?");
			link.l1.edit = 3;
			link.l1 = "";	
			Link.l1.go = "result_dub";
		break;
		
		case "result_dub":		
			iTotalDublonQty = GetCharacterItem(pchar,"gold_dublon") + CheckItemMyCabin("gold_dublon");		
			Pchar.QuestTemp.Deposits.(sDepositType2).Interest = 1;
			Pchar.QuestTemp.Deposits.(sDepositType2).Sum = dialogEditStrings[3];
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp <= 0)
			{
				dialog.text = "Está brincando, hein?";
				link.l1 = "Hm, meu engano...";
				link.l1.go = "exit";
				break;
			}						
			if (iTemp > iTotalDublonQty)
			{
				dialog.text = "Hm, infelizmente você não tem tanto dinheiro assim. Vamos ser sinceros...";
				link.l1 = "Hm... bom.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Certo. Posso te oferecer... digamos..."+Pchar.QuestTemp.Deposits.(sDepositType2).Interest+" %. Por mês, é claro.";
			Link.l1 = "Por mim, tudo certo.";
			Link.l1.go = "Deposit_placed_dub";
			Link.l2 = "É melhor eu mudar o valor.";
			Link.l2.go = "Deposit_dub";
			Link.l3 = "Acho que é melhor ficar com meu ouro. Adeus.";
			Link.l3.go = "Exit";
		break;
		
		case "Deposit_placed_dub":
			Dialog.snd = "voice\USDI\USDI033";
			if ( !CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)+".Result"))
			{
			    Pchar.Quest.Deposits.(sDepositType2).Result = 0;//fix
			}
			// boal limit
			if ( (sti(Pchar.Quest.Deposits.(sDepositType2).Result) + sti(Pchar.QuestTemp.Deposits.(sDepositType2).Sum)) > sti(NPChar.UsurerDeposit)*10)
			{
			    dialog.text = "Perdoe-me, capitão, mas essa quantia é grande demais para o meu banco colonial. Não poderei lhe pagar os juros. E a falta de uma guarda confiável... Espero que compreenda. De qualquer forma, o valor máximo que posso aceitar de você é "+FindRussianDublonString(MakeMoneyShow(sti(NPChar.UsurerDeposit)*10,MONEY_SIGN,MONEY_DELIVER))+".";
				Link.l1 = "Que pena, vou ter que procurar outro banqueiro então.";
				Link.l1.go = "Exit";
			}
			else
			{
				dialog.text = "Agora você pode ter certeza de que nem a mais forte tempestade vai te deixar sem uma moeda.";
				Link.l1 = "Ótimo. Adeus.";
				Link.l1.go = "Deposit_Exit_dub";
			}
		break;
		
		case "Deposit_return_dub":
			Dialog.snd = "voice\USDI\USDI034";
			dialog.text = "Considerando os juros prometidos e o tempo que se passou, devo a você "+FindRussianDublonString(sti(Pchar.Quest.Deposits.(sDepositType2).Result))+"... Tem certeza de que quer pegar o dinheiro?";
			Link.l1 = "Com certeza. Me entregue.";			
			Link.l1.go = "Deposit_return_dub_1";		
			Link.l2 = "Quero sacar uma parte do meu dinheiro.";			
			Link.l2.go = "Deposit_return_dub_part";
			Link.l3 = "Você tem razão. Vou deixar com você por um tempo. Tenha um bom dia.";			
			Link.l3.go = "Exit";		
		break;	

		case "Deposit_exit_dub":
			NextDiag.CurrentNode = NextDiag.TempNode;		
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)+ ".Rem"))
			{
				DeleteAttribute(Pchar,"Quest.Deposits." + (sDepositType2)+ ".Rem");
			}	
			Pchar.Quest.Deposits.(sDepositType2).Interest = sti(Pchar.QuestTemp.Deposits.(sDepositType2).Interest);
			Pchar.Quest.Deposits.(sDepositType2).Sum      = sti(Pchar.QuestTemp.Deposits.(sDepositType2).Sum);
			Pchar.Quest.Deposits.(sDepositType2).city 	  = NPC_Area;	
			
			iTemp = GetCharacterItem(pchar,"gold_dublon");
			if(iTemp > sti(Pchar.Quest.Deposits.(sDepositType2).Sum))
			{
				TakeNItems(pchar,"gold_dublon", -sti(Pchar.Quest.Deposits.(sDepositType2).Sum));
			}
			else
			{
				TakeNItems(pchar,"gold_dublon", -iTemp));
				iTemp = sti(Pchar.Quest.Deposits.(sDepositType2).Sum) - iTemp;
				GetItemMyCabin("gold_dublon", iTemp);
			}
						
			// общий долг
			Pchar.Quest.Deposits.(sDepositType2).Sum = sti(Pchar.Quest.Deposits.(sDepositType2).Result) + sti(Pchar.Quest.Deposits.(sDepositType2).Sum);
			Pchar.Quest.Deposits.(sDepositType2) = true;
			Pchar.Quest.Deposits.(sDepositType2).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType2).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType2).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType2).StartTime 	= getTime();
			DialogExit();
		break;	
		
		//-->забор дублонов по частям
		case "Deposit_return_dub_part":
			dialog.text = "E quanto?";
			link.l1.edit = 4;
			link.l1 = "";	
			Link.l1.go = "result_dub_part";
		break;
		
		case "result_dub_part":
			iTemp = sti(dialogEditStrings[4]);
			if (iTemp <= 0)
			{
				dialog.text = "Que piada tola, senhor!";			
				link.l1 = "Droga! Me desculpe... Vamos mudar o valor...";	
				Link.l1.go = "Deposit_return_dub_part";
				break;
			}			
			if (iTemp > sti(Pchar.Quest.Deposits.(sDepositType2).Result))
			{
				dialog.text = "Você não tem tanto ouro assim na sua conta, senhor.";			
				link.l1 = "Droga! Foi erro meu. Vamos mudar o valor...";	
				Link.l1.go = "Deposit_return_dub_part";
				break;
			}			
			if (iTemp == sti(Pchar.Quest.Deposits.(sDepositType2).Result))
			{
				dialog.text = "Tudo isso? Muito bem, como quiser. Aqui está o seu dinheiro.";			
				link.l1 = "Obrigado!";	
				Link.l1.go = "Deposit_return_dub_all";
				break;
			}
			dialog.text = "Certo. Pegue. Aqui está o seu dinheiro.";			
			link.l1 = "Obrigado!";	
			Link.l1.go = "result_dub_part_1";
		break;
		
		case "result_dub_part_1":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			TakeNItems(pchar,"gold_dublon", iTemp);
			iRes = sti(Pchar.Quest.Deposits.(sDepositType2).Result)-iTemp; //остаток на счете
			iPer = sti(Pchar.Quest.Deposits.(sDepositType2).Interest);
			iDep = sti(Pchar.Quest.Deposits.(sDepositType2).Sum); //стартовая сумма
			if (iRes <= sti(Pchar.Quest.Deposits.(sDepositType2).Sum)) // стало меньше начальной суммы
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
				Pchar.Quest.Deposits.(sDepositType2).Interest = iPer;
				Pchar.Quest.Deposits.(sDepositType2).Sum = iRes;
				Pchar.Quest.Deposits.(sDepositType2).Result = 0;
			}
			else // если остаток больше начальной суммы - проценты продолжаем считать с неё, а не с остатка, ибо нефиг, дельту приплюсуем к набежавшим процентам - банкир Jason :) 
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
				Pchar.Quest.Deposits.(sDepositType2).Interest = iPer;
				Pchar.Quest.Deposits.(sDepositType2).Sum = iDep;
				Pchar.Quest.Deposits.(sDepositType2).Rem = iRes-iDep;
			}
			Pchar.Quest.Deposits.(sDepositType2).city 	  	= NPC_Area;	
			Pchar.Quest.Deposits.(sDepositType2) 			= true;
			Pchar.Quest.Deposits.(sDepositType2).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType2).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType2).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType2).StartTime 	= getTime();
		break;
		
		case "Deposit_return_dub_all":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			TakeNItems(pchar,"gold_dublon", iTemp);
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
		break;
		//<-- забор денег по частям		
		
		case "Deposit_return_dub_1":
			TakeNItems(pchar,"gold_dublon", sti(Pchar.Quest.Deposits.(sDepositType2).Result));
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "Oh... É tão difícil perder isso. Eu realmente me apeguei a esse dinheiro. Volte sempre, de qualquer forma.";			
			Link.l1 = "Se for preciso, eu farei. Adeus.";			
			Link.l1.go = "Exit";
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
		break;
		//  ugeen <- вклады в дублонах	
		
		case "DeadMotherfucker":
			Dialog.TempNode = "DeadMotherFucker_1";
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "Você ainda está vivo? Veio devolver meu dinheiro, por acaso? Maldito seja! Perdi tanto dinheiro que você jamais conseguiria me pagar! E não vou ter paz enquanto não vir seu corpo sem vida!";
            Link.l1 = "Eu só quero resolver as coisas de forma pacífica.";
			Link.l1.go = "LoanRestore_1";
			Link.l2 = LinkRandPhrase("Muito bem, vamos ver então! Saiba que você também não está a salvo da morte!","Ameaça?! Então vamos ver o que você vai fazer...","Dinheiro não é a coisa mais importante em nossas vidas. Não se lamente tanto por isso, e não mate ninguém. Vamos lá, eu te desafio.");
			Link.l2.go = "ExitDelLoan2";
		break;

		case "DeadMotherFucker_1":			
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "Saia daqui! Eu queria nunca mais ver você.";			
			Link.l1 = "...";			
			Link.l1.go = "ExitDelLoan2";
            Dialog.TempNode = "DeadMotherFucker_1";
		break;
		// boal обратимость факапства -->
		case "LoanRestore_1":
            iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Loans.(NPC_Area).StartYear),makeint(Pchar.Quest.Loans.(NPC_Area).StartMonth),makeint(Pchar.Quest.Loans.(NPC_Area).StartDay), makefloat(Pchar.Quest.Loans.(NPC_Area).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
			Pchar.Quest.Loans.(NPC_Area).Result = makeint(Pchar.Quest.Loans.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Loans.(NPC_Area).Sum)/100)*makefloat(Pchar.Quest.Loans.(NPC_Area).Interest))*(iPastMonths+1);
			dialog.text = "Ah, é mesmo? E quais são as suas preocupações?";
			Link.l1 = "Por hoje, estou te devendo "+FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).Result))+". E eu ofereço este dinheiro a você.";
			Link.l1.go = "DeadMotherFucker_1";
            if (sti(Pchar.Money) >= 2*sti(Pchar.Quest.Loans.(NPC_Area).Result))
            {
    			Link.l2 = "Ofereço minha dívida para restabelecer boas relações com você. É "+FindRussianMoneyString(2*sti(Pchar.Quest.Loans.(NPC_Area).Result))+".";
    			Link.l2.go = "LoanRestore_2";
			}
		break;
		
		case "LoanRestore_2":
			dialog.text = "Agora sim! Posso fazer negócios com você, afinal.";
			Link.l1 = "Obrigado. Não vou decepcioná-lo de novo.";
			Link.l1.go = "ExitDelLoan2";
			NextDiag.TempNode = "First time";			
			addMoneyToCharacter(Pchar, -2*sti(Pchar.Quest.Loans.(NPC_Area).Result));
			DeleteAttribute(PChar, "quest.Loans_" + NPC_Area);
			DeleteAttribute(PChar, "quest.Loans." + NPC_Area);
			ChangeCharacterHunterScore(PChar, NationShortName(sti(NPChar.nation)) + "hunter", -30);
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
		break;

		case "ExitDelLoan1":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteAttribute(Pchar, "quest.Loans." + (NPC_Area));
		break;

		case "ExitDelLoan2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteAttribute(Pchar, "quest.Loans." + (NPC_Area));
			DeleteAttribute(Pchar, "quest.Deposits." + (NPC_Area));
		break;
		
        case "LoanGranted_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;

			AddMoneyToCharacter(Pchar, makeint(Pchar.Quest.Loans.(NPC_Area).Sum));
			Pchar.Quest.Loans.(NPC_Area) = true;
			Pchar.Quest.Loans.(NPC_Area).StartDay = getDataDay();
			Pchar.Quest.Loans.(NPC_Area).StartMonth = getDataMonth();
			Pchar.Quest.Loans.(NPC_Area).StartYear = getDataYear();
			Pchar.Quest.Loans.(NPC_Area).StartTime = getTime();

			sTemp = "Loans_" + NPC_Area;			
			SetTimerCondition(sTemp, 0, makeint(Pchar.Quest.Loans.(NPC_Area).Period), 0, false);
			pchar.quest.(sTemp).CityId = NPC_Area;
			pchar.quest.(sTemp).win_condition = "LoansForAll";
			
			DialogExit();
			npchar.quest.trade_date = lastspeak_date; // дыра с прокачкой была
		break;
        
		//работорговец
		int iSlaveMoney;
		int amount;
		case "GiveTaskSlave":
			pchar.questTemp.Slavetrader.iSlaveQuantity = 100;
			pchar.questTemp.Slavetrader.iSlaveMoney = sti(pchar.questTemp.Slavetrader.iSlaveQuantity) * 250;
			dialog.Text = "Ah, vamos lá! Somos pessoas sérias, você e eu, somos melhores do que esses idiotas que estão prontos para morrer por um único doblão, mas nunca sequer tentam transformar um em dois\nEstou procurando um homem a quem possa oferecer um negócio de verdade. Um homem corajoso e ativo, honesto e pontual, mas que não seja... eh... excessivamente preocupado com dilemas morais. E espero que você seja o homem que estou procurando.";
			Link.l1 = "Vai depender do tipo de 'acordo' que você pretende me oferecer.";
			Link.l1.go = "GiveTaskSlave_1";
		break;
			
		case "GiveTaskSlave_1":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity(npchar.city);
			dialog.Text = "Muito bem, então ouça. A escravidão é o negócio mais lucrativo do Caribe atualmente. Não sou um fazendeiro, mas tenho clientes de confiança\nPortanto, preciso do seguinte número de escravos - "+pchar.questTemp.Slavetrader.iSlaveQuantity+" cabeças. Estou pronto para lhe pagar 250 pesos por cada uma. Acredite, é um preço justo. No total, você vai ganhar "+FindRussianMoneyString(sti(pchar.questTemp.Slavetrader.iSlaveMoney))+".";
			Link.l1 = "Não, eu não sou um negociante de escravos. Procure outro assistente que não ignore a própria consciência.";
			Link.l1.go = "exit_slaves";
			Link.l2 = "Uma oferta tentadora. Eu gostaria de aceitar. Para quando você precisa dos escravos?";
			Link.l2.go = "GiveTaskSlave_2";
		break;
			
		case "exit_slaves":
			dialog.Text = "Ah, parece que ninguém está disposto a mexer um dedo para pegar o ouro que está bem debaixo do nariz. Estou realmente decepcionado. Adeus, e nem pense em sair por aí fofocando sobre nossa conversa. Meu braço alcança longe...";
			Link.l1 = "Seu alcance é 'sujo'... assim como sua língua. Adeus.";
			Link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "End_quest";
			DeleteAttribute(npchar, "quest.slave");
		break;
			
		case "GiveTaskSlave_2":
			dialog.Text = "Não vou limitar o seu tempo, mas tente cumprir sua missão o quanto antes. A demanda por 'marfim negro' é enorme. Se fizer um bom trabalho, vou lhe passar esse tipo de serviço de vez em quando no futuro.";
			Link.l1 = "Parece ótimo. Bem, aguarde boas notícias.";
			Link.l1.go = "exit";						
			pchar.questTemp.Slavetrader = "Seek_slaves"; // это ввод имени квеста и состояния квеста
			AddQuestRecord("Slavetrader", "1");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("Slavetrader", "sQty", makeint(pchar.questTemp.Slavetrader.iSlaveQuantity));
			AddQuestUserData("Slavetrader", "sSum", makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			LAi_LocationDisableOfficersGen(&Locations[FindLocation(pchar.location)], true); // блокируем вход офицеров 2015
		break;
			
		case "Checkslaves":
			amount = GetSquadronGoods(Pchar, GOOD_SLAVES) - sti(pchar.questTemp.Slavetrader.iSlaveQuantity);
			dialog.Text = "Você conseguiu obter aquela remessa de 'marfim negro'?";
            if (amount < 0)
			{
				Link.l1 = "Ainda não. Só estou verificando se nosso acordo ainda está valendo.";
            	Link.l1.go = "exit";
			}
			else
			{
				Link.l1 = "Sim. Estão todos no meu porão.";
            	Link.l1.go = "Takeslaves";
			}
		break;
		
		case "Takeslaves":
			amount = sti(pchar.questTemp.Slavetrader.iSlaveQuantity);
			dialog.Text = "Excelente. Meus homens vão cuidar disso... Não se preocupe com a alfândega ou com o comandante do forte. Estou conduzindo uma grande operação aqui, então não espere problemas e ninguém vai te acusar de contrabando.";
			Link.l1 = "Parece que você está em uma posição forte aqui... Então, e quanto ao meu pagamento?";
            Link.l1.go = "Takeslaves_1";
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, amount);
		break;
		
		case "Takeslaves_1":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			dialog.Text = "Aqui está. Não falo por falar. Fique comigo, capitão, e logo você terá tanto ouro que vai precisar de um galeão para carregar tudo!";
			Link.l1 = "Seria ótimo, ha-ha... E agora?";
            Link.l1.go = "Takeslaves_2";
		break;
		
		case "Takeslaves_2":
			dialog.Text = "Próximo? Volte aqui em três semanas. Estou negociando um acordo agora, e ele deve estar pronto até lá.";
			Link.l1 = "Muito bem, combinado. Adeus.";
            Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "2");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.questTemp.Slavetrader = "wait";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait");//запомнить дату
		break;
		
		case "Takeslaves_3":
			if (4-sti(RealShips[sti(pchar.ship.type)].Class) < 0)//проверка класса корабля
			{
				dialog.Text = "Tenho um trabalho, mas seu navio é fraco demais. Não quero que fracasse na missão, nem desejo mandar você para a morte. Ainda há tempo, então consiga um navio maior, como uma barca, uma brigantina, um brigue ou pelo menos uma flauta. Não perca tempo!";
				Link.l1 = "Entendi, vou cuidar disso. Até mais.";
            	Link.l1.go = "Takeslaves_3_smallship";
			}
			else
			{
				dialog.Text = "Finalmente! Eu estava esperando por você. Agora vamos direto ao assunto. Como você sabe, sempre há concorrentes em qualquer negócio... e eu também tenho os meus. Esses canalhas gananciosos e sem escrúpulos estão sempre prontos para roubar um cliente meu! Na verdade, quero eliminar um deles e ainda lucrar com isso.";
				Link.l1 = "Estou ouvindo.";
            	Link.l1.go = "Takeslaves_4";
			}
		break;
		
		case "Takeslaves_3_smallship":
			pchar.questTemp.Slavetrader = "waitship";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Takeslaves_4":
			Slavetrader_GetRandomShore();//выбор бухты
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.questTemp.Slavetrader.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "Muito bem. Agora escute. Esse patife chamado "+GetName(NAMETYPE_ORIG,pchar.questTemp.Slavetrader.UnknownPirateName,NAME_NOM)+", trouxe escravos da África e lançou âncora em "+XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore+"Gen")+", fica numa ilha chamada "+XI_ConvertString(pchar.questTemp.Slavetrader.Island)+". Ele está esperando contrabandistas lá. O galeão dele se chama '"+pchar.questTemp.Slavetrader.ShipName+". O acordo deles precisa ser quebrado a qualquer custo!";
			link.l1 = "E quanto aos escravos? Seria um desperdício afundá-los!";
			link.l1.go = "Takeslaves_5";
		break;
		
		case "Takeslaves_5":
			dialog.Text = "Por que você faria isso? Não há necessidade disso. "+GetName(NAMETYPE_ORIG,pchar.questTemp.Slavetrader.UnknownPirateName,NAME_NOM)+" tem uma péssima reputação e ninguém vai se importar com o seu desaparecimento. Suba a bordo do galeão dele, mate o homem e certifique-se de que ele não volte, traga a carga para mim e eu a venderei. Segundo minhas fontes, há cerca de mil e quinhentos escravizados.";
			Link.l1 = "Vejam só. Esse é um valor considerável. E quanto ao meu pagamento?";
            Link.l1.go = "Takeslaves_6";
			Link.l2 = "Não, senhor, essas intrigas não são para mim. Por que eu iria estragar minha relação com os contrabandistas?";
            Link.l2.go = "exit_slaves_1";
		break;
		
		case "exit_slaves_1":
			dialog.Text = "Bem... Parece que me enganei sobre você... Adeus, e esqueça nossa conversa. E não vá espalhar fofocas sobre o que ouviu aqui. Eu sou o dono desta cidade. E se estiver pensando em abordar o '"+pchar.questTemp.Slavetrader.ShipName+" por você mesmo... Vou garantir que você acabe na forca. Pense nisso.";
			Link.l1 = "Não se preocupe, não vou denunciá-lo às autoridades e não preciso do seu galeão. Adeus.";
            Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase(" agreed"," agreed"));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";//конец квеста
		break;
		
		case "Takeslaves_6":
			dialog.Text = "Considerando que já lhe forneci a localização da carga e você não precisa navegar em busca de 'um prêmio', o pagamento é um pouco menor – 200 pesos por cabeça. Ainda assim, é uma ótima quantia – trezentos mil pesos em caso de sucesso e do navio.";
			Link.l1 = "Fechado. Quanto tempo eu tenho?";
            Link.l1.go = "Takeslaves_7";
			Link.l2 = "Ho-ho! Você fala como se esses escravos fossem nadar até o meu navio por vontade própria, ansiosos para entrar na minha carga o quanto antes! Você realmente espera que minha tripulação arrisque o pescoço por uma quantia tão miserável? Aumente minha recompensa ou estou fora desse negócio.";
            Link.l2.go = "exit_slaves_1";
		break;
		
		case "Takeslaves_7":
			dialog.text = "Você tem duas semanas. Não se atrase, ou ele vai transferir a carga e tudo estará perdido.";
			link.l1 = "Então terei que me apressar. Espere por boas notícias minhas.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "3");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
			AddQuestUserData("Slavetrader", "sShoreName", XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore + "Dat")); // belamour gen
			AddQuestUserData("Slavetrader", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.questTemp.Slavetrader.Island) + "Voc")); // belamour gen
			pchar.quest.Slavetrader_ShipsAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_ShipsAttack.win_condition.l1.location = pchar.questTemp.Slavetrader.Island;
            pchar.quest.Slavetrader_ShipsAttack.function = "Slavetrader_CreateSlaveShips";//создание кораблей
			SetFunctionTimerCondition("Slavetrader_SlaveShipsOver", 0, 0, 15, false);	//таймер
			pchar.questTemp.Slavetrader = "wait1";	//это заглушка
		break;
		
		case "Takeslaves_4_lose":
			dialog.text = "Bem, "+GetFullName(pchar)+", e a nossa missão? Seu rosto sombrio me diz que você não conseguiu cumpri-la.";
			link.l1 = "Droga, você está certo... Eu... bem, você sabe... Cheguei atrasado. Parecia que ele já tinha ido embora, porque não encontrei ninguém lá. Tive que velejar contra o vento o caminho todo, droga...";
			link.l1.go = "Takeslaves_5_lose";
		break;
		
		case "Takeslaves_4_win":
			dialog.text = "Bem, "+GetFullName(pchar)+", qual foi o seu lucro hoje? Disseram-me que "+GetName(NAMETYPE_ORIG,pchar.questTemp.Slavetrader.UnknownPirateName,NAME_NOM)+" alimenta os peixes! Ha-ha-ha!";
			link.l1 = "Sim, cheguei bem na hora! "+GetName(NAMETYPE_ORIG,pchar.questTemp.Slavetrader.UnknownPirateName,NAME_NOM)+" estava transferindo escravos para o navio do contrabandista. Tive que abordar os dois e mandá-los direto para o fundo do mar, então agora você tem menos concorrentes.";
			link.l1.go = "Takeslaves_5_win";
		break;
		
		case "Takeslaves_5_lose":
			dialog.text = "Sim, acho que me enganei sobre você. Chegou atrasado? Ou ficou com medo de lutar? Tanto faz. Agora isso não importa mais. Cai fora. Acabou entre nós. Esqueça tudo o que viu ou ouviu aqui.";
			link.l1 = "Então, até logo.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "5_5");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
		
		case "Takeslaves_5_win":
			pchar.questTemp.Slavetrader.Nation = npchar.nation;
			amount = 1600 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			if (amount < 0)
			{
				dialog.text = "Eu estava certo sobre você - "+GetSexPhrase(" você é um bandido charmoso"," você é uma donzela destemida")+"! Preciso de homens como você. Você cumpriu sua missão de forma excelente – trouxe mais de mil e quinhentos escravos! Infelizmente, só posso pagar por mil e seiscentos escravos. Não tenho moedas suficientes para pagar pelo restante, então você terá que vendê-los por conta própria. Sua recompensa é de 320.000 pesos.";
				link.l1 = "Obrigado. Foi um prazer fazer negócios com você, "+npchar.name+"!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, 320000);
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, 1600);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", 1600);
				AddQuestUserData("Slavetrader", "sMoney", 320000);
				break;
			}
			if (amount >= 0 && amount < 200)
			{
				dialog.text = "Eu estava certo sobre você - "+GetSexPhrase(" você é um bandido charmoso"," você é uma donzela destemida")+"! Preciso de homens como você. Cumpriu sua missão de forma exemplar – trouxe para mim "+sTemp+" escravos. Sua recompensa é "+FindRussianMoneyString(iSlaveMoney)+".";
				link.l1 = "Obrigado. Foi um prazer fazer negócios com você, "+npchar.name+"!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 200 && amount < 600)
			{
				dialog.text = "Pelo menos você sobreviveu à situação mais difícil com a honra intacta. Embora o prêmio seja menor do que eu esperava, ainda assim estou satisfeito. Você trouxe "+sTemp+" escravos. Sua recompensa é "+FindRussianMoneyString(iSlaveMoney)+"";
				link.l1 = "Obrigado. Foi um prazer fazer negócios com você, "+npchar.name+"!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 600 && amount < 1100)
			{
				dialog.text = "Entendo... Consigo compreender, mas esperava bem mais. Você trouxe apenas "+sTemp+" escravos. Pelo menos você destruiu meus concorrentes e isso já vale alguma coisa. Sua recompensa é  "+FindRussianMoneyString(iSlaveMoney)+".";
				link.l1 = "Meu agradecimento. Agradeço sua compreensão. "+npchar.name+"!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 1100 && amount < 1600)
			{
				dialog.text = "Parece ótimo, mas... hmm. Acho que me enganei sobre você. O que você trouxe? "+sTemp+" escravos? E o resto? E nem venha me dizer que você os afundou. Tenho certeza de que você os vendeu para contrabandistas, ou pior ainda – para aquele canalha do Lavoisier. Cai fora, não quero mais fazer negócio com você!";
				link.l1 = "Como desejar, adeus.";
				link.l1.go = "node_hanter_1";
				break;
			}
			dialog.text = "Parece ótimo, mas... onde estão nossos escravos? Onde está nossa carga? E não venha me dizer que você afundou tudo. Deve ter vendido para os contrabandistas ou, pior ainda, para aquele canalha do Lavoisier. Cai fora, não quero mais saber de você.";
			link.l1 = "Como quiser, adeus.";
			link.l1.go = "node_hanter_1";
		break;
		
		case "node_hanter_1":
			dialog.text = "Isso ainda não acabou. Ninguém ousa me enganar! E você vai pagar pela sua tentativa – vou garantir que você tenha problemas. Agora, saia daqui!";
			link.l1 = "Vá para o inferno você e esse seu tráfico de escravos! Eu devia te cortar aqui mesmo, mas sou muito melhor do que você jamais será.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 30);
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Takeslaves_6_win":
			dialog.text = "Parece que estamos trabalhando bem juntos, "+pchar.name+". Fico muito satisfeito. Volte a me procurar daqui a um mês e talvez eu tenha um trabalho feito sob medida para você. Já tenho algumas ideias em mente.";
			link.l1 = "Claro, nos vemos em um mês. Trabalhar com você é muito lucrativo.";
			link.l1.go = "Takeslaves_7_win";
		break;
			
		case "Takeslaves_7_win":
			dialog.text = "Isso vai te render uma fortuna... Só mais uma pergunta, "+pchar.name+", você encontrou algo incomum na cabine da galé?";
			link.l1 = "Nada de especial, na verdade... Perdi alguma coisa?";
			link.l1.go = "Nostatue";
			if (CheckCharacterItem(pchar, "talisman8"))
			{
				link.l2 = "Você está falando desse velho fivela, algum amuleto de 'escorpião'?";
				link.l2.go = "Yestatue";
			}
		break;
			
		case "Nostatue":
			dialog.text = "Talvez você tenha feito, talvez não ... Agora não importa mais. Nos vemos em um mês. Adeus!";
			link.l1 = "Até logo, "+npchar.name+".";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Yestatue":
			dialog.text = "Exatamente! Isto é uma fíbula Medici... já ouviu falar delas? Isso significa que estava mesmo na cabine do desgraçado... Posso dar uma olhada?";
			link.l1 = "Claro, pode pegar.";
			link.l1.go = "Yestatue_1";
			RemoveItems(PChar, "talisman8", 1);
		break;
			
		case "Yestatue_1":
			Log_Info("You gave a talisman");
			PlaySound("interface\important_item.wav");
			dialog.text = "Pois é, pois é... Realmente é. Escute, "+pchar.name+", venda para mim. Estou pronto para pagar cem mil pesos.";
			link.l1 = "Cem mil? Hm... Concordo. Aqui está!";
			link.l1.go = "Buystatue";
			link.l2 = "Não, não vou vender. O verdadeiro valor desta fíbula não pode ser medido em prata ou ouro. Eu sei como essas coisas funcionam.";
			link.l2.go = "Nobuystatue";
		break;
			
		case "Buystatue":
			dialog.text = "Perfeito! Fico feliz que tenhamos um acordo. Pegue seu dinheiro. Espero vê-lo daqui a um mês.";
			link.l1 = "Adeus, "+npchar.name+".";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 100000);
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Nobuystatue":
			dialog.text = "You see, I desperately need this fibula! I completely agree with you, it can't be valued in money; any foolish merchant wouldn't even pay you five thousand for it. But it seems you truly understand its worth, since you refuse to sell it for such a sum.\n May I offer you a trade, if you don't want money? I have something you might find interesting. Here, take a look. Remarkable light armour! See for yourself! I offer it to you in exchange for the fibula.\nIt is not unique, by the way. You sailors can always find more for yourselves, but I cannot. Do you agree now?";
			link.l1 = "Heh... Suponho que sim. Me dê a armadura e pegue esta fíbula.";
			link.l1.go = "Nobuystatue_yes";
			link.l2 = "Não, esta fíbula vale muito mais para mim do que esta armadura. Vou ficar com ela para mim.";
			link.l2.go = "Nobuystatue_no";
		break;
			
		case "Nobuystatue_yes":
			dialog.text = "Excelente! Fico feliz que tenhamos um acordo. Esta armadura agora é sua. Pegue. Nos vemos em um mês. Até logo.";
			link.l1 = "Até logo, "+npchar.name+".";
			link.l1.go = "exit";
			TakeNItems(pchar, "cirass7", 1);
			Log_Info("You have received a Brigandine");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Nobuystatue_no":
			dialog.text = "Que pena... Muito ruim. Bem, fique com isso. Não vou te julgar. Nos vemos em um mês. Adeus.";
			link.l1 = "Adeus.";
			link.l1.go = "exit";
			TakeNItems(pchar, "talisman8", 1);
			Log_Info("You have received a talisman");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "EscapeSlave":
			dialog.text = "Você chegou na hora certa, "+pchar.name+". Tenho uma missão para você, se estiver pronto para começar.";
			link.l1 = "Claro, estou pronto.";
			link.l1.go = "EscapeSlave_1";
		break;
			
		case "EscapeSlave_1":
			dialog.text = "Excelente! Agora, direto ao ponto. Já ouviu as últimas notícias?";
			link.l1 = "Hm, como assim? Chegam muitas novidades todos os dias.";
			link.l1.go = "EscapeSlave_2";
		break;
			
		case "EscapeSlave_2":
			dialog.text = "Essa história diz respeito diretamente aos nossos negócios. Houve a maior fuga de escravos da história do Novo Mundo! Mais de mil pessoas escaparam e, nesse meio tempo, destruíram e incendiaram alguns postos avançados da Holanda.";
			link.l1 = "Intrigante. Continue.";
			link.l1.go = "EscapeSlave_3";
		break;
			
		case "EscapeSlave_3":
			dialog.text = "Mas eles não apenas fugiram, de alguma forma conseguiram deixar a ilha! Não deixaram nenhum rastro. Mathias Beck está indignado. Mas isso não é o mais importante... O que importa é que peço que você navegue até Curaçao, descubra o que aconteceu lá, rastreie os fugitivos e os capture E, claro, salve-os das mãos da justiça holandesa, que não teria nenhuma piedade. Pagarei 300 pesos por cabeça – ouvi dizer que são excelentes escravos.";
			link.l1 = "Entendido. Estou indo para Curaçao. Aguarde por boas notícias.";
			link.l1.go = "EscapeSlave_yes";
			link.l2 = "Sabe, eu não vou aceitar a missão. Não vou tirar a liberdade do povo. Eles arriscaram a vida para conquistá-la. Eles a mereceram.";
			link.l2.go = "EscapeSlave_no";
		break;
			
		case "EscapeSlave_no":
			dialog.text = "Que pena... Não esperava isso de você... e logo no momento mais inoportuno. Suponho que esteja claro para você que nossa parceria chegou ao fim. Adeus.";
			link.l1 = "Tenha um bom dia.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "EscapeSlave_yes":
			Slavetrader_GetEscapeShore();
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(HOLLAND);
			pchar.questTemp.Slavetrader = "EscapeSlave_Villemstad";
			AddQuestRecord("Slavetrader", "22_1");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			DialogExit();
		break;
			
		case "Escape_slaves_win":
			int iSlaveMoneyH;
			string sNum;
			amount = 1100 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*300;
			sNum = GetSquadronGoods(Pchar, GOOD_SLAVES) - 1100;
			iSlaveMoneyH = makeint(sNum)*100;
			if (amount < 0)
			{
				dialog.text = "Ha! Você não só cumpriu sua difícil missão, como ainda trouxe mais escravos do que eu pedi - "+sTemp+" escravos. Mas "+sNum+" os escravos não fugiram de Curaçao. Vou te pagar 100 pesos por cabeça. Imagino que isso seja suficiente para você. Sua recompensa é de 330.000 pesos e "+FindRussianMoneyString(iSlaveMoneyH)+" por um excesso, ha-ha.";
				link.l1 = "Ha! Você realmente não pode ser enganado. Concordo, do jeito que você quiser. "+npchar.name+"!";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, 330000);
				AddMoneyToCharacter(pchar, makeint(iSlaveMoneyH));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_5");
				AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoneyH));
				break;
			}
			if (amount < 101 && amount >= 0)
			{
				dialog.text = "Você completou aquela missão difícil da melhor forma possível e me trouxe "+sTemp+" escravos. Sua recompensa é "+FindRussianMoneyString(iSlaveMoney)+".";
				link.l1 = "Meus agradecimentos. Foi um prazer fazer negócios com você, "+npchar.name+"!";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 100 && amount < 600)
			{
				dialog.text = "Você conseguiu cumprir essa missão difícil. O prêmio não é tão valioso quanto eu esperava, mas estou satisfeito mesmo assim. Então você trouxe aqui "+sTemp+" escravos. Sua recompensa é "+FindRussianMoneyString(iSlaveMoney)+".";
				link.l1 = "Obrigado. Foi um prazer fazer negócios com você, "+npchar.name+"!";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 600 && amount < 1100)
			{
				dialog.text = "Você os encontrou? Hm... o que você trouxe para mim?"+sTemp+" Escravos? Onde está o resto da carga? E nem tente me dizer que você a afundou. Deve ter vendido para contrabandistas, ou pior ainda – para aquele canalha do Lavoisier, de Isla-Tesoro. Saia daqui, não quero mais fazer negócios com você.";
				link.l1 = "Adeus.";
				link.l1.go = "node_hanter_1";
				break;
			}
			dialog.text = "Encontrou-os? E quanto aos escravos? Onde está nossa carga? E nem tente me dizer que você a afundou. Deve ter vendido para contrabandistas ou, pior ainda, para aquele canalha do Lavoisier de Isla-Tesoro. Saia daqui, não quero mais fazer negócios com você.";
			link.l1 = "Adeus.";
			link.l1.go = "node_hanter_1";
		break;
		
		case "Escape_slaves_win_1":
			dialog.text = "Eu realmente aprecio você, "+pchar.name+". Sério. Volte aqui em um mês e eu vou preparar um novo negócio, lucrativo para nós dois.";
			link.l1 = "Também estou satisfeito com nossa parceria, "+npchar.name+". Até daqui a um mês.";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_2");
			pchar.questTemp.Slavetrader = "wait_2";
		break;
			
		case "Slaveshore":
			dialog.text = "Você chegou na hora certa, "+pchar.name+". Estou procurando um marinheiro corajoso e sem escrúpulos, ha-ha. Está pronto para assumir o meu serviço?";
			link.l1 = "Estou ouvindo.";
			link.l1.go = "Slaveshore_1";
		break;
			
		case "Slaveshore_1":
			pchar.questTemp.Slavetrader.Island = Islands[GetCharacterCurrentIsland(pchar)].id;
			pchar.questTemp.Slavetrader.Island.Shore = GetIslandRandomShoreId(pchar.questTemp.Slavetrader.Island);
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.questTemp.Slavetrader.Nation = NPChar.nation;
			dialog.text = "Desta vez é bem simples. Hoje, uma pinassa "+pchar.questTemp.Slavetrader.ShipName+"' sob a bandeira de "+NationNameGenitive(sti(npchar.nation))+" lançou âncora em "+XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore+"Gen")+" baía. Foi carregado com um grande lote de 'ébano' com a ajuda dos contrabandistas locais. Duas mil cabeças, nada menos\nNenhum soldado na tripulação e o capitão é um comerciante. No geral, nenhuma ameaça. Aborde o navio e traga a carga para mim. 200 pesos por cabeça, como de costume.";
			link.l1 = "Hm... Isso não é igual ao último trabalho. Você está sugerindo que eu ataque um navio do seu próprio país!";
			link.l1.go = "Slaveshore_2";
		break;
			
		case "Slaveshore_2":
			dialog.text = "Eu não entendo, "+pchar.name+"A bandeira do navio importa? Você realmente se importa com isso?";
			link.l1 = "Eu? Não, não dou a mínima, ouro não tem nacionalidade. Só foi um pouco inesperado...";
			link.l1.go = "Slaveshore_3_yes";
			link.l2 = "Eu me importo. Eu não quero ter "+NationNameAblative(sti(npchar.nation))+" entre meus inimigos.";
			link.l2.go = "Slaveshore_3_no";
		break;
			
		case "Slaveshore_3_no":
			dialog.text = "Está falando sério? Só pode estar brincando, hoje em dia não se pode confiar em ninguém... Nesse caso, vá embora. E esqueça tudo o que viu ou ouviu aqui!";
			link.l1 = "Até mais,"+npchar.name+".";
			link.l1.go = "node_hanter_1";
		break;
			
		case "Slaveshore_3_yes":
			dialog.text = "Por que está surpreso? Porque não me importo com a nacionalidade das moedas? Garanto-lhe, de fato, não me importo. Para ser sincero, patriotismo não combina com um banqueiro profissional, a menos que ele queira ir à falência um dia\nMas chega de filosofia. Vamos ao que interessa – o navio ficará aqui até a meia-noite, então não lhe resta muito tempo. Está pronto para prosseguir?";
			link.l1 = "Sim, "+npchar.name+", estou a caminho.";
			link.l1.go = "Slaveshore_4";
		break;
			
		case "Slaveshore_4":
			dialog.text = "Excelente. Não tenho dúvidas de que você será bem-sucedido em nossa missão. Boa sorte."+pchar.name+".";
			link.l1 = "Obrigado! Adeus.";
			link.l1.go = "exit";
            AddQuestRecord("Slavetrader", "10");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShip", pchar.questTemp.Slavetrader.ShipName);
			pchar.quest.Slavetrader_ShoreAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_ShoreAttack.win_condition.l1.location = pchar.questTemp.Slavetrader.Island;//отправляем в локацию
            pchar.quest.Slavetrader_ShoreAttack.function = "Slavetrader_CreateShoreShips";//создание кораблей
			SetFunctionTimerCondition("Slavetrader_ShoreShipsOver", 0, 0, 1, false);	//таймер
			pchar.questTemp.Slavetrader = "wait1";	//заглушка
		break;
			
		case "Pinas_lose":
		dialog.text = "Bem, "+GetFullName(pchar)+", e a sua missão? Seu rosto sombrio me diz que você falhou.";
			link.l1 = "Você está absolutamente certo... Eu... Bem... Cheguei tarde demais. Eu estava na taverna, e quando zarpei, não havia ninguém no mar.";
			link.l1.go = "Takeslaves_5_lose";
		break;
			
		case "Slaveshore_5":
			dialog.text = ""+pchar.name+", por favor, acalme-se. Não é culpa minha! Droga, recebi o relatório tarde demais... Houve traição! Um dos meus homens de confiança me entregou!";
			link.l1 = "Certo, vejo que está falando a verdade. Você teve sorte que o capitão da chalupa me contou que nosso 'negócio' foi descoberto. Eu já teria te matado se ele não tivesse aberto o bico. Mas você, seu maldito saco de dinheiro, ficou me dizendo esse tempo todo que 'manda nessa cidade'!";
			link.l1.go = "Slaveshore_6";
		break;
			
		case "Slaveshore_6":
			dialog.text = "A emboscada não foi organizada pelas autoridades locais, caso contrário eu saberia... "+pchar.name+", this is not the right time for quarrels. Both of us are in danger; one of my former contractors has set us up\nI managed to find out that all the gathered evidence—a package of papers—is being transported to our governor-general. If he gets them, we are finished! You, by the way, will suffer the most.";
			link.l1 = "Agora entendi o que aquele capitão desgraçado quis dizer!";
			link.l1.go = "Slaveshore_7";
		break;
			
		case "Slaveshore_7": //выбор острова, куда бригантина пойдёт
			switch (sti(NPChar.nation))
            {
                case HOLLAND :
					pchar.questTemp.Slavetraderbrig.Island = "Curacao";
                break;
                case FRANCE :
					pchar.questTemp.Slavetraderbrig.Island = "Nevis";
                break;
                case SPAIN :
					pchar.questTemp.Slavetraderbrig.Island = "Cuba2";  
                break;
                case ENGLAND :
					pchar.questTemp.Slavetraderbrig.Island = "Jamaica";     
                break;
			}
			pchar.questTemp.Slavetraderbrig.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));//имя бригантины
			pchar.questTemp.Slavetrader.Nation = NPChar.nation;
			dialog.text = "Escute com atenção. Ainda temos uma chance. O pacote foi enviado no bergantim '"+pchar.questTemp.Slavetraderbrig.ShipName+". Isso é a única coisa da qual tenho certeza. Documentos estão sendo entregues ao governador-geral em sua residência em "+XI_ConvertString(pchar.questTemp.Slavetraderbrig.Island)+". Você precisa interceptá-lo, abordá-lo e encontrar essas provas incriminadoras.";
			link.l1 = "Não tenho muita escolha aqui. Reze por mim, por você, e torça para que eu consiga pegar isso. Vamos conversar sobre tudo isso de novo quando eu voltar. Não pense que vou simplesmente deixar pra lá.";
			link.l1.go = "Slaveshore_8";
			AddQuestRecord("Slavetrader", "14");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetraderbrig.ShipName);
			AddQuestUserData("Slavetrader", "sIsland", XI_ConvertString(GetIslandByArealName(pchar.questTemp.Slavetraderbrig.Island)));
			pchar.quest.Slavetrader_BrigAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_BrigAttack.win_condition.l1.location = pchar.questTemp.Slavetraderbrig.Island;//отправляем в локацию
            pchar.quest.Slavetrader_BrigAttack.function = "Slavetrader_CreateBrig";//создание бригантины
			SetFunctionTimerCondition("Slavetrader_BrigOver", 0, 0, 15, false);	//таймер
			pchar.questTemp.Slavetrader = "wait1";	//это нода ожидания, пустая
		break;
		
		case "Slaveshore_8":
			dialog.text = "Conseguir esse pacote é sua prioridade principal! Não vou me sentir seguro até você me entregar... Droga..."+pchar.name+", parece que temos um problema aqui...";
			link.l1 = "O que foi?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Slavetrader_enterSoldiers");
			break;
			
		case "Brig_lose":
			dialog.text = "Droga... Eu estava contando com você. "+pchar.name+". Muito bem então. Mas não faremos mais negócios. Se eu não conseguir subornar o investigador, vou ter que fugir. E não recomendo que você fique aqui – os soldados podem aparecer a qualquer momento. Adeus.";
			link.l1 = "Adeus, "+npchar.name+".";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Letter_lose":
			dialog.text = "Eles estavam lá. Bem, não podemos mais fazer negócios juntos, não é mais seguro. Adeus.";
			link.l1 = "Adeus, "+npchar.name+".";
			link.l1.go = "exit";
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Brig_win":
			dialog.text = "Excelente! Eu nunca duvidei de você, "+pchar.name+". Por favor, me dê esses papéis, estou muito nervoso.";
			link.l1 = "Leve-os.";
			link.l1.go = "Brig_win_1";
		break;
			
		case "Brig_win_1":
			RemoveItems(PChar, "letter_1", 1);
			dialog.text = "Ótimo... Agora estou seguro. O governador-geral não vai saber de nada, e já resolvi todos os problemas com as autoridades locais, mas foi caro, pode acreditar.";
			link.l1 = "Parece ótimo, mas você não acha que deveria me compensar pelos meus problemas por causa das suas atitudes impensadas?";
			link.l1.go = "Brig_win_2";
		break;
			
		case "Brig_win_2":
			dialog.text = "Claro, "+pchar.name+". Ainda mais, eu lhe devo muito. E realmente espero continuar nossos negócios. Mas peço que me compreenda – gastei uma fortuna – a lealdade do governador e do comandante não sai barata. E ainda tive que lidar com aquele assassinato de toda a patrulha no meu banco...";
			link.l1 = "Quer dizer que não vai me ressarcir os custos?!";
			link.l1.go = "Brig_win_3";
		break;
			
		case "Brig_win_3":
			dialog.text = "Não seja tão duro, "+pchar.name+". Estou realmente passando por dificuldades financeiras no momento, então lhe ofereço um tipo diferente de pagamento.";
			link.l1 = "Estou ouvindo você então.";
			link.l1.go = "Brig_win_4";
		break;
			
		case "Brig_win_4":
			dialog.text = "My companion and I were caught in a storm near the southern shores of the Main a year ago. Our ships were thrown onto the rocks of the Boca de la Serpienta coast; although they soon sank, we managed to drag our cargo ashore. Chests filled with precious stones and jewellery. The bay seemed quite cosy, so we hid the treasures without any trouble\nBut we were attacked by the Indians the next morning as soon as the storm had ended. That's how most of the survivors died, including my companion. A few sailors and I managed to escape on a longboat\nWe reached Cumana safely, yet I didn't dare return for the treasures. I am sure the local savages are still guarding their shore, along with my chests. But you can deal with that band of redskins\nThe jewellery you'll find there is more than enough to cover all your expenses, including an expedition to the southern Main.";
			link.l1 = "Hm... tudo bem. Então estou indo para Cumana";
			link.l1.go = "Brig_win_5";
		break;
			
		case "Brig_win_5":
			dialog.text = "Pode ficar tranquilo, "+pchar.name+", tudo o que disse é verdade. Espero vê-lo daqui a um mês. Já tenho outro negócio em mente, e penso em como posso ajudar minha empresa em dificuldades. Adeus.";
			link.l1 = "Até mais, "+npchar.name+".";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_3");
			pchar.questTemp.Slavetrader = "wait_3";
			Pchar.quest.Slavetrader_Bonanza.win_condition.l1 = "location";
            Pchar.quest.Slavetrader_Bonanza.win_condition.l1.location = "Shore18";
            Pchar.quest.Slavetrader_Bonanza.function = "Slavetrader_Bonanza";
		break;
			
		case "SlaveGalleon":
			dialog.text = "E aqui está você, "+pchar.name+". Que bom, você chegou na hora certa, como sempre. Gostaria de lhe dar mais informações sobre o mercado de escravos do Caribe antes de passar sua próxima missão. Você sabe o que significa a palavra 'repartimiento'?";
			link.l1 = "Hm, não, "+npchar.name+", eu não sei. Mas suponho que seja sobre tirar algo de alguém. Estou certo?";
			link.l1.go = "SlaveGalleon_1";
		break;
			
		case "SlaveGalleon_end":
			dialog.text = "Você me surpreende. O que esperava de mim? Vá embora!";
			link.l1 = "Um negócio ilegal pesa demais na minha consciência. Principalmente o tráfico de escravos.";
			link.l1.go = "node_hanter_1";
		break;
			
		case "SlaveGalleon_1":
			dialog.text = "Você quase conseguiu,"+pchar.name+". Tirar a liberdade de alguém. O repartimiento é uma maneira astuta e legal de escravizar os índios locais. Por assim dizer. As autoridades espanholas usam isso contra os povos nativos do continente. Você gostaria de saber mais?";
			link.l1 = "Por que não?";
			link.l1.go = "SlaveGalleon_2";
		break;
			
		case "SlaveGalleon_2":
			dialog.text = "Representantes da coroa espanhola visitam aldeias indígenas. Usando enganação cínica e ameaças diretas, eles obrigam os índios a comprar todo tipo de porcaria, como carne podre e navalhas velhas, por preços absurdos. Tudo fiado\nAlgum tempo depois, digamos um ano, os representantes voltam e exigem o pagamento. Se os índios não conseguem pagar, o que quase sempre acontece, os espanhóis levam alguns dos homens mais fortes, supostamente por um tempo e para 'ensinar como cultivar a terra'\nComo você deve imaginar, eles nunca voltam para suas aldeias. É assim que nossos índios confiantes acabam em plantações de açúcar e fábricas de mogno.";
			link.l1 = "Maldição... sério mesmo... O que os índios fazem quanto a isso? Eles resistem quando os espanhóis os escravizam? Ou simplesmente não entendem o que está acontecendo?";
			link.l1.go = "SlaveGalleon_3";
		break;
			
		case "SlaveGalleon_3":
			dialog.text = "Suponho que eles sempre percebem o que está para acontecer, mas só alguns ousam se opor abertamente, especialmente quando os espanhóis apresentam um papel com a digital do cacique. Claro, essas táticas geralmente são usadas contra tribos pacíficas como os Arawaks ou Miskitos. Esse truque não funciona com os guerreiros Itza ou Akawoys\nBem, vamos falar sobre sua missão.";
			link.l1 = "Já consigo sentir o cheiro de muitas moedas! Estou ouvindo, "+npchar.name+".";
			link.l1.go = "SlaveGalleon_4";
		break;
			
		case "SlaveGalleon_4":
			Slavetrader_GetHispanShore();
			sTemp = pchar.questTemp.SlavetraderAreal.add; 
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(SPAIN);
			dialog.text = "Em breve, um pesado galeão partirá de Caracas. Ele se chama "+pchar.questTemp.Slavetrader.ShipName+". It contains a huge number of slaves - about 3,000 men - Indians from the Orinoco, captured according to the repartimientos policy. The galleon is sailing to Santiago; the sugar plantations of Cuba need many workers. You must capture the galleon with her cargo. I would take at least two ships with me if I were you; they say the galleon is the finest of its kind. Pay rates remain the same - 200 pesos per head. ";
			link.l1 = "Heh! Parece bom. Concordo.";
			link.l1.go = "SlaveGalleon_5";
			link.l2 = "Você sabe que eu não gosto desse seu repartimiento. É cínico demais. Eu não vou fazer isso.";
			link.l2.go = "SlaveGalleon_end";
		break;
			
		case "SlaveGalleon_5":
			sTemp = pchar.questTemp.SlavetraderAreal.add; 
			dialog.text = "Então lhe desejo sorte. Saiba que o capitão deste galeão é um marinheiro de guerra muito habilidoso e experiente. Não será uma luta fácil, então prepare-se. Não perca tempo, ele vai levar uns quinze ou vinte dias para chegar "+sTemp+" Santiago. Tente não perder, embora este galeão seja realmente difícil de não notar\nSim! Quase me esqueci! Há muitos artefatos indígenas no navio, os nativos costumam pagar suas dívidas com itens de culto e artesanato. Traga-me qualquer coisa especial que encontrar, e eu pagarei generosamente por cada objeto valioso que trouxer.";
			link.l1 = "Entendi.";
			link.l1.go = "exit";
			SlavetraderGalleonInWorld();
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Slavetrader_SlaveGalleonOver", 0, 0, 20, false);
			pchar.questTemp.Slavetrader = "wait1";
			AddQuestRecord("Slavetrader", "18");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
			AddQuestUserData("Slavetrader", "sAreal", sTemp);
		break;
			
		case "Lostgalleon":
			dialog.text = "Bem, "+pchar.name+", era minha última esperança... Por isso confiei esse trabalho a você. Ninguém além de você poderia fazê-lo... e agora vejo que nem você foi capaz. Vamos nos despedir, então. Depois do último fracasso e de todos esses boatos, perdi todos os meus clientes. Estou quase falido, talvez eu tenha que deixar esta cidade. Não te culpo – esse trabalho era mesmo difícil demais. Eh... Adeus,"+pchar.name+".";
			link.l1 = "Me desculpe, "+npchar.name+", isso passou dos limites. Sinto muito de verdade. Talvez tudo se acalme. Adeus.";
			link.l1.go = "exit";
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Wingalleon":
			pchar.questTemp.Slavetrader.Nation = npchar.nation;
			amount = 3000 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			if(amount < 1) 
			{
				dialog.text = "Ufa, agora me sinto melhor... Fiz bem em confiar em você... De onde veio essa ironia? O que aconteceu?";
				link.l1 = "Caro senhor, não era um galeão... ou um galeão muito grande... Droga! Era um Navio de Linha! E você nem me avisou! Mas consegui abordá-lo. Eu tenho "+sTemp+" escravos e estou pronto para transferi-los para você. Conforme nosso acordo, você me deve - "+FindRussianMoneyString(iSlaveMoney)+". Seria ótimo receber alguma compensação pela sua informação equivocada.";
				link.l1.go = "Wingalleon_1";
			}
			else
			{
			dialog.text = "Você encontrou o galeão? E os escravos? Deveriam ser três mil, não menos! Maldição, todos são ratos e traidores! Não esperava isso de você... você era minha última esperança\nMuito bem... Juro, vou gastar cada moeda que me resta para te destruir, para te matar! A frota inteira de "+NationNameGenitive(sti(npchar.nation))+" vou caçar você! Saia daqui!";
				link.l1 = "Bem...";
				link.l1.go = "Wingalleon_goaway";
			}
		break;
			
		case "Wingalleon_goaway":
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 70);
			pchar.questTemp.Slavetrader = "End_quest";
			DialogExit();
		break;
			
		case "Wingalleon_1":
			dialog.text = "Não me diga! Juro que eu não fazia ideia. Era para zarpar um galeão pesado, não um maldito navio de linha! Parece que mudaram os planos no último instante... Mas, ainda assim, você conseguiu!\nConcordo plenamente com você sobre o dinheiro e o ressarcimento das suas despesas, mas acontece que eu não disponho dessa quantia no momento. Você sabe dos meus problemas recentes... Mas não fique bravo, "+pchar.name+", pelo amor de Deus. Você me entrega a carga e eu vendo, meu cliente já está esperando\nEm cinco dias terei todo o valor, então você receberá o que merece. Pode confiar em mim. Aqui, pegue todo o dinheiro que tenho agora.";
			link.l1 = "Hm... Eu esperava receber o dinheiro agora. Queria que você soubesse o tipo de encrenca que tive que enfrentar! Ah, tanto faz... Vou ser compreensivo com você. Mas lembre-se: se tentar me enganar, eu te encontro até na Europa!";
			link.l1.go = "Wingalleon_yes";
			link.l2 = "Sabe, "+npchar.name+", vai se danar! Isso não foi um acordo. Você nem imagina o tipo de confusão que eu tive que enfrentar. Vou ficar com todos os escravos para mim e vendê-los sem a sua agência.";
			link.l2.go = "Wingalleon_no";
		break;
			
		case "Wingalleon_no":
			dialog.text = "Então, agora sim estamos conversando! Parece que os desavisados "+npchar.name+" eu era apenas uma vaca para ser ordenhada, um simples atraso já basta para você me trair e começar uma operação por conta própria. Parece que você esqueceu que fui eu quem te deu o trabalho e te contou sobre o saque\nMuito bem... Juro que vou gastar até a última moeda que me resta para te destruir, para te matar! A frota inteira de "+NationNameGenitive(sti(npchar.nation))+" Eu vou caçar você! Saia da minha frente!";
			link.l1 = "Não ouse tentar me assustar com um cofre vazio. Vou afundar todas as suas frotas e jogá-las para os caranguejos.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 70);
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Wingalleon_yes":
			dialog.text = "Obrigado pela sua compreensão, "+pchar.name+". Eu prometo que tudo vai ficar bem, não precisa das suas ameaças\nConsidere isto um adiantamento. Quinze baús. Cinco deles servirão como compensação por danos morais. Venha me ver em cinco dias para receber o restante.\nNão se esqueça de trazer qualquer item indígena que tenha encontrado no navio... se é que encontrou algum, é claro. De qualquer forma, não tenho como te pagar por eles.";
			link.l1 = "Em cinco dias,"+npchar.name+". Em cinco dias...";
			link.l1.go = "Wingalleon_yes_1";
		break;
			
		case "Wingalleon_yes_1":
			TakeNItems(pchar, "chest", 15);
			Log_Info("You've received credit chests");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_4");
			pchar.questTemp.Slavetrader = "wait_4";
			AddQuestRecord("Slavetrader", "20");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			pchar.questTemp.Slavetrader.iSlaveMoney = makeint(sTemp)*200-120000;
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
			DialogExit();
		break;
	
		case "FindRat":
			dialog.text = "Como prometi, "+pchar.name+", estou pronto para lhe pagar. Os escravos foram vendidos, o cliente está satisfeito, e nós também. Após descontar o adiantamento, sua recompensa é"+FindRussianMoneyString(sti(pchar.questTemp.Slavetrader.iSlaveMoney))+". Por favor, pegue seu dinheiro.";
			link.l1 = "Excelente, "+npchar.name+". É bom lidar com um homem que honra sua palavra...";
			link.l1.go = "FindRat_1";
		break;
			
		case "FindRat_1":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			dialog.text = "Você sempre pode confiar na minha palavra, "+pchar.name+". Nunca lhe dei motivo algum para duvidar de mim. Parceiros precisam ser honestos um com o outro, esse é o segredo dos negócios\nVamos falar sobre artefatos indígenas agora. Mostre-me o que você tem, não faça um colecionador como eu esperar.";
			link.l1 = "Hm... Dê uma olhada.";
			link.l1.go = "FindRat_2";
		break;
			
		case "FindRat_2":
			if (CheckCharacterItem(pchar, "talisman16"))
			{
				dialog.text = "Sim! Excelente! Uma adaga ritual dourada! É uma raridade. Sempre quis algo assim na minha coleção. Posso te oferecer 30.000 por ela, ou um amuleto de 'Ehecatl' em troca. De qualquer forma, tenho dois deles.";
				link.l1 = "Eu aceitaria dinheiro.";
				link.l1.go = "BG_money";
				link.l2 = "Eu aceitaria um amuleto de 'Ehecatl' em troca.";
				link.l2.go = "BG_change";
				link.l3 = "É melhor eu ficar com esta faca.";
				link.l3.go = "BG_no";
			}
			else
			{
				dialog.text = "Vejamos... Infelizmente, você não tem nada interessante para me oferecer.";
				link.l1 = "O que você disser.";
				link.l1.go = "BG_PF";
			}
		break;
			
		case "BG_money":
			dialog.text = "Excelente. Pegue seus 30.000 e esta faca indígena agora é minha.";
			link.l1 = "Ótimo. E é só isso que lhe interessa...";
			link.l1.go = "BG_PF";
			AddMoneyToCharacter(pchar, 30000);
			Log_Info("You've given a golden knife");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "talisman16", 1);
		break;
			
		case "BG_change":
			dialog.text = "Excelente! Aqui está o seu amuleto, e esta faca indígena agora é minha.";
			link.l1 = "Ótimo. E é só isso que lhe interessa...";
			link.l1.go = "BG_PF";
			Log_Info("You've given a golden knife");
			Log_Info("You've received an amulet of 'Ehecatl'");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "talisman16", 1);
			TakeNItems(pchar, "obereg_9", 1);
		break;
			
		case "BG_no":
			dialog.text = "Tanto faz. Mas é uma pena, de qualquer jeito...";
			link.l1 = "Ótimo. E é só isso que lhe interessa...";
			link.l1.go = "BG_PF";
		break;
			
		case "BG_PF":
			dialog.text = "Espere! Deixe-me dar outra olhada...";
			link.l1 = "Claro. Venha dar uma olhada e escolha o que quiser.";
			link.l1.go = "PF_check";
		break;
			
		case "PF_check":
			if (CheckCharacterItem(pchar, "mineral31"))
			{
				dialog.text = "Isto! E eu nem percebi de início. Estou interessado nesse osso com um anel de cobre. Que coisa intrigante, devo dizer... Posso te pagar 20.000 pesos ou te dar um amuleto 'Cimaruta' em troca.";
				link.l1 = "Eu aceitaria dinheiro.";
				link.l1.go = "PF_money";
				link.l2 = "Eu aceitaria um amuleto 'Cimaruta' em troca.";
				link.l2.go = "PF_change";
				link.l3 = "Eu ficaria com este artefato comigo.";
			link.l3.go = "PF_no";
			}
			else
			{
				dialog.text = "Não... você não tem mais nada de interessante aqui.";
				link.l1 = "Tanto faz!";
				link.l1.go = "FindRat_3";
			}
		break;
			
		case "PF_money":
			dialog.text = "Excelente! Aqui estão seus 20.000 pesos e este osso agora é meu.";
			link.l1 = "Ótimo. Estou satisfeito com o nosso acordo.";
			link.l1.go = "FindRat_3";
			AddMoneyToCharacter(pchar, 20000);
			Log_Info("You've given a magic bone");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "mineral31", 1);
		break;
			
		case "PF_change":
			dialog.text = "Excelente! Aqui está o seu amuleto, e este osso agora é meu.";
			link.l1 = "Ótimo. Estou satisfeito com o nosso acordo.";
			link.l1.go = "FindRat_3";
			Log_Info("You've given a magic bone");
			Log_Info("I've received an amulet of 'Cimaruta'");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "mineral31", 1);
			TakeNItems(pchar, "amulet_11", 1);
		break;
			
		case "PF_no":
			dialog.text = "Tanto faz. Mas é uma pena, de qualquer jeito...";
			link.l1 = "Eu preciso desse osso para mim, me desculpe.";
			link.l1.go = "FindRat_3";
		break;
			
		case "FindRat_3":
			dialog.text = "Bem... ao abordar o galeão—oh, desculpe, o Navio de Linha—você me salvou. Eu realmente aprecio nossa parceria, "+pchar.name+". Você é meu melhor agente.";
			link.l1 = "Fico lisonjeado. Você está superestimando um pouco as minhas conquistas...";
			link.l1.go = "FindRat_4";
		break;
			
		case "FindRat_4":
			dialog.text = "Estou falando muito sério. E vou lhe pedir para assumir outra missão por causa das suas habilidades extraordinárias e porque confio em você.";
			link.l1 = "Heh! Surpreendente! Estou ouvindo. Onde está o outro galeão com os escravos?";
			link.l1.go = "FindRat_5";
		break;
			
		case "FindRat_5":
			dialog.text = "Desta vez, não se trata de escravos. Surpreso? Vou te pagar bem pela missão... Muito bem.";
			link.l1 = "Vamos direto ao assunto.";
			link.l1.go = "FindRat_6";
		break;
			
		case "FindRat_6":
			dialog.text = "Este negócio está ligado aos acontecimentos recentes dos quais você também fez parte... Então, como talvez saiba, estou envolvido em um ramo bastante ilegal – o tráfico de escravos. Você também deve saber que contrato corsários como você para todo tipo de serviço\nUm dos meus homens me traiu há pouco tempo, por motivos desconhecidos. Ele reuniu provas e fez um relatório para as autoridades. Você teve o desprazer de ver as consequências com seus próprios olhos. Um navio com soldados chegou aqui... você sabe o resto\nFoi preciso muito esforço para eu resolver a situação. Como deve entender, não posso deixar essa traição sem resposta. Além disso, não posso viver e trabalhar em paz sabendo que o rato ainda está vivo. Já enviei caçadores de recompensas, mas até agora sem resultado\nPeço que você mesmo resolva essa questão. Até porque as ações dele também te afetaram.";
			link.l1 = "Hm... aquele canalha merecia ser enforcado no mastro! Conte-me mais sobre ele e, é claro, sobre o meu pagamento pelo serviço.";
			link.l1.go = "FindRat_7";
		break;
			
		case "FindRat_7":
			dialog.text = "Não se preocupe com isso. Vou pagar generosamente pela eliminação dele, e não estou falando só de dinheiro. Não vou poupar as melhores peças das minhas coleções. Vamos falar sobre o homem. O nome dele é Francois Gontier\nEle sabe que estou atrás dele, então vendeu sua fragata para despistar. Meus colegas disseram que ele foi visto no Panamá. Acho que você deveria começar sua busca por lá.";
			link.l1 = "Bem, então estou de saída.";
			link.l1.go = "FindRat_8";
		break;
			
		case "FindRat_8":
			dialog.text = "Então lhe desejo sorte. Saiba que esse Gontier é um marinheiro muito experiente e tem uma tripulação de bandidos destemidos. Ele não tem nada a perder, então vai lutar de forma bastante desesperada.";
			link.l1 = "Não tenho medo de gente como ele, mas vou considerar o que você disse. Adeus, e pode ter certeza, vou pegá-lo até no inferno.";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(SPAIN);
			AddQuestRecord("Slavetrader", "21");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.questTemp.Slavetrader = "FindRatPanama";
		break;
			
		case "Wincorvette":
			dialog.text = "Excelente! Agora ele pode escrever seus relatórios para as águas-vivas. Ninguém ousa me desafiar. Meus agradecimentos a você, "+pchar.name+", você é um homem indispensável.";
			link.l1 = "Obrigado, "+npchar.name+", por uma avaliação tão positiva das minhas ações. E quanto ao meu pagamento?";
			link.l1.go = "Wincorvette_1";
		break;
			
		case "Wincorvette_1":
			dialog.text = "Claro. Eu pagaria um preço justo por um trabalho tão difícil. Primeiro, apresento a você este excelente telescópio.";
			link.l1 = "Que surpresa incrível, que presente!";
			link.l1.go = "Wincorvette_2";
		break;
			
		case "Wincorvette_2":
			dialog.text = "Além disso, aqui estão 100.000 pesos como seu pagamento principal e 50.000 como compensação pelas suas próprias despesas.";
			link.l1 = "Obrigado, "+npchar.name+". Repito, é um verdadeiro prazer fazer negócios com você.";
			link.l1.go = "Wincorvette_3";
			Log_Info("You've received an excellent spyglass");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "spyglass4", 1);
		break;
			
		case "Wincorvette_3":
			dialog.text = "Estarei esperando por você em um mês, como sempre. É um grande negócio em jogo, e você vai precisar de um esquadrão bem equipado. Peço que compreenda isso e se prepare direito. Se meu plano der certo, vamos ficar ricos.";
			link.l1 = "Ótimo,"+npchar.name+". Vou voltar quando estiver pronto.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 150000);
			AddQuestRecord("Slavetrader", "21_13");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_5");
			pchar.questTemp.Slavetrader = "wait_5";
		break;
			
		case "Lostcorvette":
			dialog.text = "Que pena, que vergonha... Bem, não fique chateado, você não é o primeiro homem que aquele canalha enganou. Um dia ainda vou pegar ele de qualquer jeito\nQuanto a você, venha me ver daqui a um mês. Vai ser grande, então reúna um esquadrão bem equipado e armado. Por favor, leve isso a sério e faça o melhor para se preparar. Se meu plano der certo, vamos ficar ricos.";
			link.l1 = "Ótimo, "+npchar.name+". Voltarei quando estiver pronto.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_14");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_5");
			pchar.questTemp.Slavetrader = "wait_5";
		break;
		
		case "Havana_fort":
			dialog.text = "Chegou bem na hora, "+pchar.name+"! Eu já estava começando a me preocupar, ia mandar um homem atrás de você\nVamos começar! Sua missão agora é realmente grande e arriscada, mas a recompensa está à altura. Você vai receber mais de um milhão de pesos quando o trabalho estiver concluído.";
			link.l1 = "Agora sim! Estou ouvindo, "+npchar.name+".";
			link.l1.go = "Havana_fort_1";
		break;
		
		case "Havana_fort_1":
			dialog.text = "Os índios escravizados estavam sendo levados em pequenos grupos para Havana de todas as partes do continente, e alguns galeões também chegaram da África e foram descarregados. Agora, já há quase cinco mil escravos atrás dos altos muros do forte de Havana.";
			link.l1 = "Tenho a impressão de que o acordo envolve atacar Havana.";
			link.l1.go = "Havana_fort_2";
		break;
		
		case "Havana_fort_2":
			dialog.text = "Você está no caminho certo, "+pchar.name+".   É exatamente isso que quero pedir que faça. Você, e só você. Duvido que algum dos meus outros agentes seja capaz de realizar essa tarefa\nAcredito que você está dentro?";
			link.l1 = "Para ser sincero, "+npchar.name+", estou um pouco perplexo agora. Eu não fazia ideia de que sua operação era tão... grandiosa. Claro, estou dentro. "+RandSwear()+"";
			link.l1.go = "Havana_fort_3";
			link.l2 = "Sabe de uma coisa, "+npchar.name+", isso já passou dos limites. Já cansei das suas surpresas. Da próxima vez, sua ganância vai me fazer declarar guerra à Espanha e terei que enfrentá-los sozinho. Se você realmente precisa desses escravos, então ataque Havana por conta própria.";
			link.l2.go = "Havana_fort_not";
		break;
		
		case "Havana_fort_not":
			dialog.text = "Não esperava isso de você... Droga, o que vou dizer ao meu cliente? Tudo bem. A decisão é sua e agora preciso encontrar outro parceiro. Adeus, "+pchar.name+". E não vou mais usar seus serviços no futuro. Lembre-se de que você deixou escapar um acordo que poderia ter enriquecido seus descendentes por sete gerações.";
			link.l1 = "Você não pode pegar todo o dinheiro do mundo, e quis abraçar mais do que pode. Adeus, "+npchar.name+".";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
		
		case "Havana_fort_3":
			dialog.text = "Eu sabia que você aceitaria. Agora, ouça os detalhes. O forte de Havana sempre foi um alvo difícil, mas agora está ainda mais protegido.\nDois navios de linha estão guardando as costas de Cuba, e você terá que lidar com eles antes de atacar o forte...";
			link.l1 = "Entendo. Não vai ser a primeira vez que enfrento Navios de Linha, ha-ha. Quanto tempo eu tenho?";
			link.l1.go = "Havana_fort_4";
		break;
		
		case "Havana_fort_4":
			dialog.text = "Não muito. Três semanas, no máximo, e depois disso os escravos serão levados para os postos espanhóis em Cuba. Você precisa se apressar. ";
			link.l1 = "Então não vamos perder tempo. Estou a caminho!";
			link.l1.go = "Havana_fort_5";
		break;
		
		case "Havana_fort_5":
			dialog.text = "Um momento!"+pchar.name+", você e eu nunca tivemos nenhum mal-entendido ou desentendimento. Ainda assim, quero que saiba o que está acontecendo aqui. Eu confio em você, e o cliente confia em mim\nInvestimos muito esforço e dinheiro nesta operação. Cada escravo, todos os cinco mil, deve ser entregue a mim\nCaso contrário, seremos obrigados a tomar medidas muito drásticas contra você. Sem ofensa, isto é apenas um aviso. ";
			link.l1 = "Não se preocupe, "+npchar.name+", eu entendo como funciona o negócio, por isso você também deve lembrar de me pagar assim que eu entregá-los. Até logo.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "24");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.quest.Slavetrader_HavanaAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_HavanaAttack.win_condition.l1.location = "Cuba2";//отправляем в локацию
            pchar.quest.Slavetrader_HavanaAttack.function = "Slavetrader_CreateLineShips";//создание линейных кораблей
			SetFunctionTimerCondition("Slavetrader_HavanaOver", 0, 0, 20, false);	//таймер
			characters[GetCharacterIndex("Havana_Mayor")].dialog.captureNode = "Slavetrader_HavanaAttack"; //капитулянтская нода мэра
			pchar.questTemp.Slavetrader = "wait1";
		break;
		
		case "Win_Havana_Fort":
			pchar.quest.Slavetrader_FiveTSlavesOver.over = "yes";
			amount = 5000 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			if (amount < 1)
			{
				dialog.text = "Bem... E quanto ao prêmio pela sua vitória?";
				link.l1 = "Eu tenho "+sTemp+" escravos.";
				link.l1.go = "Havana_Fort_yes";
				break;
			}
			if (amount < 4500 && amount >= 1)
			{
				dialog.text = "Ora, ora. Esqueceu o que eu disse? Era para você me trazer nada menos que cinco mil escravos, e você trouxe "+sTemp+". Por que isso?";
				link.l1 = "Hmm... Alguns deles não sobreviveram à viagem de Havana... a comida e os remédios estavam acabando.";
				link.l1.go = "Havana_Fort_no";
				break;
			}
			dialog.text = "Ora, ora... Está tentando me enganar? Esqueceu o que eu disse? Onde estão meus escravos, eu lhe pergunto! Onde eles estão?!";
			link.l1 = "Hm... Bem, veja...";
			link.l1.go = "Havana_Fort_no";
		break;
		
		case "Havana_Fort_no":
			dialog.text = "Certo. Não preciso das suas explicações. Nós tínhamos um acordo, e vou lhe dar uma semana para conseguir pelo menos cinco mil escravos. Caso contrário, você terá muitos problemas.";
			link.l1 = "Tá bom, tá bom, calma, eu vou pegar pra você.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "29");
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Slavetrader_HavanaSeekOver", 0, 0, 14, false);
			} 
			else SetFunctionTimerCondition("Slavetrader_HavanaSeekOver", 0, 0, 7, false);
			pchar.questTemp.Slavetrader = "Havana_seekslaves";
		break;
		
		case "Havana_Fort_yes":
			dialog.text = "Excelente! Você cumpriu minha tarefa como sempre faz. Estou muito satisfeito com você.";
			link.l1 = "Eu também... Mas ficarei ainda mais satisfeito quando receber meu pagamento pela carga.";
			link.l1.go = "Havana_Fort_yes_1";
		break;
		
		case "Havana_Fort_yesA":
		dialog.text = "Fico muito satisfeito com isso. Você se atrasou, mas cumpriu minha tarefa da melhor maneira possível.";
			link.l1 = "E agora quero receber pelo carregamento.";
			link.l1.go = "Havana_Fort_yes_1";
			pchar.quest.Slavetrader_HavanaSeekOver.over = "yes";
		break;
		
		case "Havana_Fort_yes_1":
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			dialog.text = "Claro. Vou vender os escravos para o meu cliente, ele vai pagar e você receberá suas moedas. Igual da última vez. Vamos ver, você trouxe aqui "+sTemp+" escravos. A soma é "+FindRussianMoneyString(iSlaveMoney)+". Volte aqui para receber o pagamento em uma semana.";
			link.l1 = "Certo, "+npchar.name+", temos um acordo. Estarei aqui em uma semana. Mas tome muito cuidado...";
			link.l1.go = "Havana_Fort_yes_2";
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
		break;
		
		case "Havana_Fort_yes_2":
			dialog.text = ""+pchar.name+", por favor, não faça isso. Somos parceiros e não há espaço para trapaças ou desconfiança entre nós. Prometi-lhe muitas moedas e você as recebeu. Prometi tarefas interessantes e você também as teve. Sempre reembolsei suas despesas, mesmo nos dias mais difíceis para meus negócios. Já deixei de cumprir minha palavra alguma vez?";
			link.l1 = "Hmm... Não... Eu só quero receber meu pagamento, só isso.";
			link.l1.go = "Havana_Fort_yes_3";
		break;
		
		case "Havana_Fort_yes_3":
			dialog.text = "Veja só..."+pchar.name+", você é meu melhor agente e conto em fazer negócios com você novamente no futuro. ";
			link.l1 = "Certo, "+npchar.name+". Mas você também precisa me entender - um milhão de pesos é uma quantia enorme.";
			link.l1.go = "Havana_Fort_yes_4";
		break;
		
		case "Havana_Fort_yes_4":
			dialog.text = "Eu entendo perfeitamente, mas preciso vender os escravos primeiro, só então receberei o dinheiro.";
			link.l1 = "Certo. Acho que nos entendemos.";
			link.l1.go = "Havana_Fort_yes_5";
		break;
		
		case "Havana_Fort_yes_5":
			dialog.text = "Excelente. Vejo você em uma semana. Agora preciso me preparar e partir para negociar com meu cliente.";
			link.l1 = "Não vou incomodá-lo então. Nos vemos em uma semana, "+npchar.name+".";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader.Name = npchar.name;
			AddQuestRecord("Slavetrader", "32");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_6");
			SetFunctionTimerCondition("Slavetrader_UsurerEscape", 0, 0, 8, false);
			pchar.questTemp.Slavetrader = "wait_6";
			pchar.questTemp.Slavetrader.Cityname = npchar.city +"_town";
			LocatorReloadEnterDisable(npchar.city +"_town", "reload8_back", true);//чтобы не ходил неделю сюда вообще
		break;

		case "Usurer_Escape":
			dialog.text = "O que estou fazendo aqui? Bem... este é o meu banco. Comprei ele há dois dias. Você é meu primeiro cliente e posso lhe oferecer condições de crédito muito tentadoras...";
			link.l1 = "Que se danem os créditos! Onde está "+pchar.questTemp.Slavetrader.Name+"?";
			link.l1.go = "Usurer_Escape_1";
		break;

		case "Usurer_Escape_1":
			dialog.text = "Calma, por favor! Ele fugiu faz tempo.";
			link.l1 = "Como?";
			link.l1.go = "Usurer_Escape_2";
		break;
		
		case "Usurer_Escape_2":
			dialog.text = "Não sabia? Ele sumiu faz uma semana. Descobriu-se que levou todos os investimentos dos clientes. Dizem que até o governador foi prejudicado. Esta casa ficou abandonada e eu a comprei da colônia.";
			link.l1 = "Desapareceu? Como assim?";
			link.l1.go = "Usurer_Escape_3";
		break;
		
		case "Usurer_Escape_3":
			dialog.text = "Ouvi dizer que ele fugiu da nossa colônia... Imagino que ele também te deve. Muito?";
			link.l1 = "Mais de um milhão! Mas eu vou pegar esse rato de qualquer jeito! Onde ele foi? O nome do navio dele?";
			link.l1.go = "Usurer_Escape_4";
		break;
		
		case "Usurer_Escape_4":
			dialog.text = "Nobody knows. Seriously. He just disappeared. The ship named 'Mauritius' or 'Maurdius' sailed away that day; perhaps he used it to escape.";
			link.l1 = "Porra! E eu confiava naquele desgraçado! Ele já cheirava a traidor desde o primeiro dia! E eu fui idiota o bastante pra acreditar que éramos parceiros de verdade! Mas um dia ele vai se arrepender... Tá bom,"+npchar.name+", peço desculpas pelo meu comportamento... Se você for um homem de bem, lidarei com você no futuro, pode ter certeza disso, mas por agora, adeus.";
			link.l1.go = "Usurer_Escape_5";
		break;
		
		case "Usurer_Escape_5":
			string sColony;
			sColony = npchar.city;
			SetNull2Deposit(sColony);
			dialog.text = "Está tudo bem. Eu entendo. Se precisar de dinheiro ou quiser investir, estou sempre à sua disposição.";
			link.l1 = "Obrigado. Mas é melhor eu guardar meu dinheiro comigo. Até logo.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "33");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "wait1";
			pchar.questTemp.SanBoxTarget.Slavetrader = true;
			ChangeCharacterComplexReputation(pchar, "fame", 25);
			LAi_LocationDisableOfficersGen(&Locations[FindLocation(pchar.location)], false); // разблокируем вход офицеров 2015
		break;
	//<--работорговец	

	//--> семейная реликвия
		case "Noblelombard":
			dialog.text = "Ah, é mesmo? Parece que ele não quer falar comigo pessoalmente.... Muito bem, vamos tratar do assunto com você. "+pchar.GenQuest.Noblelombard.Name+" me deve "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Summ))+": "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Money))+" e também meu interesse - "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Percent))+" por três meses. Se eu não vir o dinheiro até amanhã, vou vender a relíquia dele, e pouco me importa o valor que ela tem para ele. Negócios são negócios.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Summ))
			{
				link.l1 = "Excelente! Nesse caso, vou lhe pagar toda a quantia com todos os juros imediatamente - "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Summ))+". Ele mesmo vai pegar a relíquia dele. Aqui está o seu dinheiro.";
				link.l1.go = "Noblelombard_1";
			}
			if(sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Percent)*2)
			{
				link.l2 = "Meu cliente terá o dinheiro em três meses. Vamos fazer um acordo: eu pago os juros dos últimos três meses e dos próximos três meses."+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Percent)*2)+". E a própria dívida será paga a você depois.";
				link.l2.go = "Noblelombard_2";
			}
			if(sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Percent))
			{
				link.l3 = "Meu cliente terá o dinheiro em três meses. Que tal eu pagar os juros dos últimos três meses e você esperar até que meu cliente tenha dinheiro suficiente?";
				link.l3.go = "Noblelombard_3";
			}
			link.l4 = "Essa raridade custa uma fortuna! Parece que meu cliente vai ter que pagar por ela ele mesmo.";
			link.l4.go = "Noblelombard_4";
			pchar.quest.noblelombard = "true";//лесник с нпчара на пчара
		break;
		
		case "Noblelombard_1":
			dialog.text = "Excelente! No fim, tudo deu certo, peguei meu dinheiro e "+pchar.GenQuest.Noblelombard.Name+" vai recuperar sua relíquia.";
			link.l1 = "Foi um prazer fazer negócios com você, "+npchar.name+"! Até logo, por enquanto.";
			link.l1.go = "exit";
			pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Summ)*2;
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Summ));
			pchar.GenQuest.Noblelombard = "full";
			AddCharacterExpToSkill(pchar, "Leadership", 150);
	
		break;
		
		case "Noblelombard_2":
			if(sti(pchar.GenQuest.Noblelombard.Chance) < 7)
			{
				dialog.text = "Hm... Tudo bem. Isso serve para mim. Mas se "+pchar.GenQuest.Noblelombard.Name+" não encontrar o dinheiro em três meses, então não vou conceder outra prorrogação. Certifique-se de que ele saiba disso.";
				link.l1 = "Eu vou! Fico feliz que tenhamos fechado um acordo. Até logo.";
				link.l1.go = "exit";
				pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Percent)*4;
				AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Percent)*2);
				pchar.GenQuest.Noblelombard = "maxpercent";
				AddCharacterExpToSkill(pchar, "Leadership", 50);
				AddCharacterExpToSkill(pchar, "Fortune", 70);
			
			}
			else
			{
				dialog.text = "Não. Isso não vai funcionar. Preciso da quantia inteira antes do pôr do sol. Certifique-se de que seu 'cliente' saiba disso. Não tenho mais nada a lhe dizer.";
				link.l1 = "Hm... tudo bem. Uma pena que você não queira ceder.";
				link.l1.go = "Noblelombard_4";
				AddCharacterExpToSkill(pchar, "Fortune", 30);
			
			}
		break;
		
		case "Noblelombard_3":
			if(sti(pchar.GenQuest.Noblelombard.Chance) < 3)
			{
				dialog.text = "Hm... Está bem. Aceito só por respeito ao seu cliente. Mas se "+pchar.GenQuest.Noblelombard.Name+" não encontrar o dinheiro em três meses, então não vou conceder outra prorrogação. Certifique-se de que ele saiba disso.";
				link.l1 = "Eu vou! Fico feliz que fechamos um acordo. Até logo.";
				link.l1.go = "exit";
				pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Percent)*2;
				AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Percent));
				pchar.GenQuest.Noblelombard = "minpercent";
				AddCharacterExpToSkill(pchar, "Leadership", 50);
				AddCharacterExpToSkill(pchar, "Fortune", 150);
			}
			else
			{
				dialog.text = "Não. Isso não vai funcionar. Preciso da quantia inteira antes do pôr do sol. Certifique-se de que seu 'cliente' saiba disso. Não tenho mais nada a lhe dizer.";
				link.l1 = "Hm... tudo bem. Uma pena que você não queira ceder.";
				link.l1.go = "Noblelombard_4";
				AddCharacterExpToSkill(pchar, "Fortune", 60);
	
			}
		break;
		
		case "Noblelombard_4":
			DialogExit();
			pchar.GenQuest.Noblelombard = "fail";
		break;
		
		case "Noblelombard_5":
			if(sti(pchar.GenQuest.Noblelombard.Chance) == 9)
			{
				dialog.text = "Não me diga! "+pchar.GenQuest.Noblelombard.Name+" não abriu um depósito em seu nome. Ele nem está mais em nossa colônia - partiu para a Europa. Vou lhe dizer, nunca vi homem tão desonesto. Tentou me enganar, mas não conseguiu - também tenho meus truques...";
				link.l1 = "Desgraçado! Ele me deu a palavra dele....";
				link.l1.go = "Noblelombard_6";
			}
			else
			{	// Addon-2016 Jason уменьшаем раздачу дублонов
				dialog.text = "Certo. "+pchar.GenQuest.Noblelombard.Name+" fez um depósito em seu nome. Por favor, aceite...";
				link.l1 = "Excelente! Até logo, "+npchar.name+".";
				link.l1.go = "Noblelombard_9";
			}
		break;
		
		case "Noblelombard_6":
			dialog.text = "Não existe tal coisa para pessoas como "+pchar.GenQuest.Noblelombard.Name+" porque eles não têm honra nem consciência. Imagino que ele te enganou?";
			link.l1 = "Ele tem, suponho. Tanto faz, "+npchar.name+", também não vou ficar aqui por muito tempo, e a Europa é pequena... Talvez a gente se encontre um dia. Adeus!";
			link.l1.go = "Noblelombard_7";
		break;
		
		case "Noblelombard_7":
			DialogExit();
			AddDialogExitQuestFunction("Noblelombard_Usurer_bad");
		break;
		
		case "Noblelombard_9":
			DialogExit();
			AddDialogExitQuestFunction("Noblelombard_Usurer_good");
		break;
//<-- семейная реликвия

		// Бремя гасконца
		case "sharlie_credit":
			dialog.text = "Monsieur, eu não o conheço. Só empresto dinheiro a cidadãos locais ou a capitães. Me perdoe...";
			link.l1 = "Entendo. Que pena, no entanto.";
			link.l1.go = "exit";
		break;
		// Бремя гасконца
		
		// Addon-2016 Jason, французские миниквесты (ФМК)
		// ФМК-Гваделупа
		case "FMQG_x":
			DelLandQuestMark(npchar);
			dialog.text = "O-o quê...   O que você quer dizer?";
			link.l1 = "Você é um maldito rato! Agora preste muita atenção: eu não sou tão idiota assim. Pinette escreveu duas cópias da carta. Eu te entreguei uma, a outra está com meu agente de confiança. Se algo me acontecer – meu homem vai entregar direto nas mãos do governador...";
			link.l1.go = "FMQG_x1";
		break;
		
		case "FMQG_x1":
			dialog.text = "";
			link.l1 = "Então sugiro que você reze pela minha saúde na igreja em cada sermão matinal, em vez de mandar assassinos atrás de mim. Último aviso! Tente qualquer coisa contra mim e você está ferrado. Entendeu? Ótimo. Respire fundo e continue contando seus dobrões.";
			link.l1.go = "FMQG_x2";
		break;
		
		case "FMQG_x2":
			DialogExit();
			pchar.questTemp.FMQG = "end";
			FMQ_Count();
			AddQuestRecord("FMQ_Guadeloupe", "27");
			CloseQuestHeader("FMQ_Guadeloupe");
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			AddCharacterExpToSkill(pchar, "Sneak", 400);
			AddCharacterExpToSkill(pchar, "Sailing", 200);
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		// Другое
		case "NeHochuRazgovarivat":
			dialog.text = "Não quero falar com você.";
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		// Леди Бет -->
		case "LadyBeth_Usurer_1":
			dialog.text = "Claro! Muitos só querem receber seu dinheiro e ir embora. Principalmente com os rumores recentes...";
			link.l1 = "Que rumores?";
			link.l1.go = "LadyBeth_Usurer_2";
		break;
		
		case "LadyBeth_Usurer_2":
			dialog.text = "Dizem que as condições entre a tripulação estão piorando. Monsieur Blackwood até começou a tolerar perdas frequentes – algo que nunca aconteceu antes. Mas isso não é da minha conta. Eu só vendo mercadorias. Então, o que lhe interessa?";
			link.l1 = "Vamos direto ao assunto.";
			link.l1.go = "next";
			npchar.quest.item_date = "LadyBeth";
			pchar.questTemp.LadyBeth_Usurer = true;
		break;
		// Леди Бет <--
	}	
}

// ugeen проверка, можем ли мы использовать дублоны в качестве вклада
bool CheckUseDublons(ref NPChar)
{
	int iTest 	= FindColony(NPChar.City); // город банка
	if(iTest == -1) return false;
	
	ref rColony = GetColonyByIndex(iTest);
	 	 
	bool bOk1 = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea); 
	bool bOk2 = (GetCharacterItem(pchar,"gold_dublon") > 10) || (CheckItemMyCabin("gold_dublon") > 10);
	
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && bOk1 && bOk2) return true;

	return false;
}

void SlavetraderGalleonInWorld()
{
	//создаем галеон с рабами
	ref sld;
	string sName;
	sName = pchar.questTemp.Slavetrader.ShipName;
	sld = GetCharacter(NPC_GenerateCharacter("GaleonCap", "", "man", "man", 45, SPAIN, 20, true, "quest"));
	FantomMakeCoolSailor(sld, SHIP_LINESHIP, sName, CANNON_TYPE_CANNON_LBS42, 100, 100, 100);
	FantomMakeCoolFighter(sld, 45, 100, 100, "blade_21", "pistol5", "bullet", 100);
	sld.Ship.Mode = "war";	
	SetCaptanModelByEncType(sld, "war");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;
	sld.DontRansackCaptain = true;
	sld.WatchFort = true;
	sld.AlwaysEnemy = true;


	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterGoods(sld, GOOD_SLAVES, 3000 + rand(200));//положить в трюм рабов
	sld.ship.Crew.Morale = 100;
	ChangeCrewExp(sld, "Sailors", 100);
	ChangeCrewExp(sld, "Cannoners", 100);
	ChangeCrewExp(sld, "Soldiers", 100);
	//в морскую группу кэпа
	string sGroup = "SlaveGalleon";
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	pchar.quest.SlaveHalleon_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.SlaveHalleon_AfterBattle.win_condition.l1.group = "SlaveGalleon";
	pchar.quest.SlaveHalleon_AfterBattle.function = "Slavetrader_SlaveHalleon_AfterBattle";
	sld.city = pchar.questTemp.Slavetrader.Island; //определим колонию, из бухты которой выйдет
	sld.cityShore = pchar.questTemp.Slavetrader.Island.Shore;
	sld.quest.targetCity = "Santiago"; //определим колонию, в бухту которой он придёт
	sld.quest.targetShore = GetIslandRandomShoreId(GetArealByCityName(sld.quest.targetCity));
	//Log_TestInfo("Captain of the galleon sailed away from " + sld.city + "and heading to " + sld.quest.targetShore);
	//==> на карту
	sld.mapEnc.type = "trade";
	//выбор типа кораблика на карте
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = "Galleon '" + sName + " '";
	int daysQty = 20; //дней доехать даем с запасом
	Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, daysQty);//вот он, сам запуск энкаунтера
}
