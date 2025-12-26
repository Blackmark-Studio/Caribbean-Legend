//Jason общий диалог мещан
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
    ProcessCommonDialogRumors(NPChar, Link, NextDiag);
    int iTest, iTemp;
    iTest = FindColony(NPChar.City);
    ref rColony;
    string sTemp, sCity, sTitle;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	String attrLoc = Dialog.CurrentNode;
	
	if(HasSubStr(attrLoc, "RumourAboutOwners_"))
	{
		NPChar.RumourOwnerType = FindStringAfterChar(attrLoc, "_");
		Dialog.CurrentNode = "RumourAboutOwners_TakeRumour";
	}
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
            LAi_group_Attack(NPChar, Pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			if (sti(NPChar.nation) == PIRATE)
			{
				if (sti(rColony.HeroOwn) == true) // наш горожанин
				{
				    dialog.text = RandPhraseSimple("Dizem que você manda nesta cidade, "+GetSexPhrase("senhor","senhorita")+".","Que encontro agradável, "+GetSexPhrase("senhor","senhorita")+"!");
					link.l1 = RandPhraseSimple("Mudei de ideia. Boa sorte!","Só estou passeando pela cidade. Até logo.");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("Tenho uma pergunta pra você.","Preciso de algumas informações.");
					link.l2.go = "quests";//(перессылка в файл города)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("Quero discutir questões financeiras.","Sobre as finanças...");
							link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
						}
					}
					break;
				}
				else
				{ // пираты, не наши
					if (sti(pchar.GenQuest.Piratekill) > 20)
					{
						dialog.text = RandPhraseSimple("Alarme! Um lunático armado está aqui! Às armas!","Às armas! Tem um louco armado aqui!");
						link.l1 = RandPhraseSimple("O quê?!","O que você está fazendo?!");
						link.l1.go = "pirate_fight";
					}
					else
					{
						dialog.text = RandPhraseSimple("O que você quer? Siga seu caminho.","Pare de bloquear meu caminho, suma daqui.");
						link.l1 = RandPhraseSimple("Sabe de uma coisa? Não late!","Se acalme. Ou eu mesmo vou fazer isso!");
						link.l1.go = "exit";
						link.l2 = RandPhraseSimple("Quero te perguntar uma coisa.","Só um momento da sua atenção, por favor. Uma pergunta.");
						link.l2.go = "quests";//(перессылка в файл города)
						if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
						{
							if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
							{
								link.l3 = RandPhraseSimple("Quero discutir questões financeiras.","Sobre finanças...");
								link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
							}
						}
					}
				}
				break;
			}
            if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";
				// проверка наличия корабля в порту
				bool ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && 4-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0 && or(IsWarShipType(pchar), IsRaiderShipType(pchar))) ok = false;
				if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Townpassenger") && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)//горожанин-пассажир
				{
					dialog.text = "Bom dia, "+GetAddress_Form(NPChar)+". Vejo que você é o capitão do seu próprio navio. Quero lhe pedir um favor...";
					link.l1 = "Estou ouvindo, "+GetAddress_FormToNPC(NPChar)+". O que você quer?";
					link.l1.go = "passenger";
					link.l2 = "Me desculpe, "+GetAddress_FormToNPC(NPChar)+", mas estou com pressa.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}

                // homo 05/08/06
				dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("Eu sou ","Meu nome é ","Pode me chamar de ")+GetFullName(npchar)+LinkRandPhrase(". O que você quer?",". Eu não te vi antes. Quem é você?",". Quem é você, e o que quer de mim?"),LinkRandPhrase("Saudações, "+GetAddress_Form(NPChar)+". Meu nome é "+GetFullName(npchar)+". E qual é o seu nome?","Olá, "+GetAddress_Form(NPChar)+"! Eu sou "+GetFullName(npchar)+". Posso saber o seu nome?","Sim, "+GetAddress_Form(NPChar)+". O que você quer? E, aliás, meu nome é "+GetFullName(npchar)+". E qual é o seu nome?"));

				Link.l1 = pcharrepphrase(LinkRandPhrase("Maldição! ","Droga! ","Maldito seja! ")+"Sim, eu sou o capitão "+GetFullName(Pchar)+LinkRandPhrase(", você nunca ouviu falar "+NPCharSexPhrase(NPChar,", desgraçado?","?")," e "+GetSexPhrase("o pirata mais famoso","a pirata mais famosa de todas")+" no mar!"," e que eu seja amaldiçoado se eu estiver errado!"),LinkRandPhrase("Eu sou "+GetFullName(Pchar)+", capitão.","Meu nome é "+GetFullName(Pchar)+".","Pode me chamar de capitão "+GetFullName(Pchar)+"."));
				Link.l1.go = "Meeting";
				
				//==> прибыла инспекция на Святом Милосердии
				if (CheckAttribute(pchar, "questTemp.SantaMisericordia.ColonyZapret") && pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_town")
				{
					dialog.Text = LinkRandPhrase(LinkRandPhrase("A cidade inteira está em alerta – dom Fernando de Alamida, o inspetor real, chegou. Olha, já vi muita coisa por aqui, mas isso... Não é o luto que muda as pessoas, e sim como elas lidam com ele. Dizem que ele virou outro homem depois da morte do pai. Agora, não existe servo mais incorruptível e... implacável da Coroa em todo o Arquipélago.","Olha só para o 'Santa Misericórdia'! Dizem que o próprio rei mandou construir seguindo projetos especiais. E repara – não tem um arranhão sequer. Como se a própria Virgem Maria protegesse o navio. Mas ouvi uns boatos... talvez nem seja a Virgem, afinal.","Você sabe quantas vezes já tentaram matar Dom Fernando? Doze ataques em mar aberto – e isso só no ano passado! Mas com uma tripulação tão leal e bem treinada, e sob a proteção do Senhor – ele vai sobreviver ao décimo terceiro também!"),LinkRandPhrase("Você ficou sabendo? Don Fernando de Alamida chegou à nossa cidade, e dizem que ele está pelas ruas agora mesmo. Queria tanto vê-lo com meus próprios olhos...","Um homem complicado, esse dom Fernando. Uns dizem que ele é um salvador, limpando a Pátria da sujeira. Outros sussurram que algo se quebrou nele depois da morte do pai, e logo todos estaremos chorando. Mas vou te dizer uma coisa: não tema ele. Tema quem fez dele o que ele é.","Que homem bonito, esse dom Fernando! Mas sabe o que é estranho? Parece que ele não repara em ninguém. Só pensa em dever e serviço. Ouvi dizer que havia uma moça... mas depois de conversar com um padre, ele largou completamente os prazeres do mundo. Como se tivesse feito um voto."),RandPhraseSimple(RandPhraseSimple("Maldito inspetor! Enquanto ele está aqui, a cidade parece morta. Não tem comércio, não tem diversão. Até respirar, parece, tem que ser mais devagar. E sabe o que é mais assustador? É igualzinho em todo porto. Sempre do mesmo jeito. Sua Majestade Real não poderia ter inventado uma tortura melhor pra todos nós!","Dom Fernando visitou o orfanato de novo. Faz doações generosas, reza por horas. Um homem tão digno deveria servir de exemplo para esses malditos ladrões de dinheiro!"),RandPhraseSimple("Ha! O 'santo' Fernando fechou todos os bordéis de novo. Mas deixa pra lá, logo ele vai embora e vão abrir tudo de novo.","O insp... inspetor chegou, isso sim! Dom Fernando de Almeyda, ou, como é mesmo o nome, Alamida! Tão importante que até o governador anda nas pontas dos pés perto dele. Dizem que ele olha nos seus olhos e enxerga todos os seus pecados de uma vez. De arrepiar!")));
					link.l1 = "...";
					link.l1.go = "exit";
				}
				//<== прибыла инспекция на Святом Милосердии
				//==> Леди Бет в порту города
				if (CheckAttribute(pchar, "questTemp.LadyBeth.CaptainInColony") && pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_town")
				{
					dialog.Text = findLedyBethRumour(npchar);
					link.l1 = "...";
					link.l1.go = "exit";
				}
				//<== Леди Бет в порту города
			}
			else
			{
				link.l1 = PCharRepPhrase("Eu só quero perguntar uma coisa sobre esse buraco que você chama de 'cidade'.","Quero te perguntar algo sobre esta cidade.");
				link.l1.go = "new question";
 				link.l2 = RandPhraseSimple("Tenho uma pergunta pra você.","Preciso de algumas informações.");
				if (CheckCharacterItem(pchar, "CaptainBook"))				
				{
					if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
					{
						link.l2.go = "ShipLetters_7";// генератор  "Найденные документы"
					}
					else
					{
						link.l2.go = "quests";
					}	
				}
				else
				{
					link.l2.go = "quests";//(перессылка в файл города)
				}	
				if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
	            {
	                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
	                {
						link.l3 = RandPhraseSimple("Quero discutir questões financeiras.","Sobre finanças...");
						link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
					}
				}
				
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
				{
					link.l16 = "Escute, espero que você possa me ajudar. Quero comprar um "+pchar.GenQuest.Device.Shipyarder.Type+", e me disseram que essa coisa foi vendida na sua cidade. Bem, alguém estava vendendo isso nas ruas. Você sabe de alguma coisa?";
					link.l16.go = "Device_Citizen";
				}
				// <-- генератор Неудачливый вор
				
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	            {
					link.l5 = LinkRandPhrase("Você sabe ","Você está ciente ","Você ouviu ")+" que a igreja local foi roubada recentemente?";
					link.l5.go = "Citiz_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				
				dialog.Text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("Ah, é você "+GetFullName(Pchar)+" "+GetSexPhrase("- velho amigo!","- bonitona!")+"","Fico feliz em te ver, "+GetSexPhrase("velho amigo!","bonitona!")+" "+Pchar.name,"Ah, esse é o "+GetSexPhrase("o próprio capitão","a própria capitã")+" "+GetFullName(Pchar))+RandPhraseSimple(". Achei que você estivesse morto!",". E talvez "+GetSexPhrase("Bêbado como sempre.","um pouco bêbado."))+LinkRandPhrase(" Continue, o que você precisa?"," O que é agora?","   Vai me incomodar de novo?"),LinkRandPhrase(TimeGreeting()+", capitão ","Bom dia para você, "+GetAddress_Form(NPChar)+" ","Saudações, Capitão ")+GetFullName(Pchar)+LinkRandPhrase(". Como posso ajudar você "+GetSexPhrase("um homem tão digno","uma moça tão valiosa")+", como você?",". Por que você está aqui?",". O que você quer saber desta vez?")),PCharRepPhrase(LinkRandPhrase("Olá, Capitão ","Saudações, ah, é você "+GetAddress_Form(NPChar)+" ","Ah, capitão ")+GetFullName(Pchar)+LinkRandPhrase(", achei que nunca mais fôssemos nos encontrar, e",", não vou dizer que estou feliz em te ver, mas",", vejo que você ainda está vivo, que pena, e")+LinkRandPhrase(" o que você quer?"," por que você está aqui?"," Como posso ajudar você?"),LinkRandPhrase(TimeGreeting()+", capitão "+GetFullName(Pchar)+". Como posso ajudar você?","Ah, é o capitão "+GetFullName(Pchar)+"! Como posso ajudar você?","Saudações, "+GetAddress_Form(NPChar)+" "+Pchar.lastname+". Você quer alguma coisa?")));  
	   			link.l6 = PCharRepPhrase(RandPhraseSimple("Seus ouvidos te enganam. Eu preciso ir.","Não, não é nada, eu só estava indo para a taverna."),RandPhraseSimple("Tudo bem, tanto faz. Boa sorte!","Só estou passeando pela cidade. Até logo."));
				link.l6.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "ShipLetters_7":
			dialog.text = "Perguntas?";
			link.l1 = "O nome nesses papéis te diz alguma coisa?";
			link.l1.go = "ShipLetters_8";
		break;
		
		case "ShipLetters_8":
			dialog.text = LinkRandPhrase("Não dou a mínima pra esse papel qualquer, e além disso, nem sei ler. Vai falar com o agiota, dizem que ele entende dessas letras, ha!","Eu não sei do que você está falando, pergunte para outra pessoa, capitão"+GetFullName(Pchar)+".","Não sei como ajudar você, Capitão "+GetFullName(Pchar)+" Tente falar com o agiota, talvez ele saiba.");
			link.l1 = "Obrigado.";
			link.l1.go = "exit";
		break;
		
		case "Meeting":
		    dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("Você não está mentindo, capitão "+GetFullName(Pchar)+"?","E daí "+PChar.name+"?","Vou me lembrar de você, "+GetFullName(Pchar)+".")+" Agora me diga, o que você quer?",LinkRandPhrase("Prazer em conhecê-lo, Capitão "+PChar.name,"Fico feliz que nos conhecemos, "+GetAddress_Form(NPChar)+" "+PChar.lastname,"É um prazer, Capitão "+PChar.name)+". Mas duvido que você só quisesse saber meu nome, certo?");
            link.l1 = PCharRepPhrase("Eu só quero perguntar uma coisa sobre esse buraco que você chama de 'cidade'.","Quero te perguntar algo sobre esta cidade.");
			link.l1.go = "new question";
            Link.l2 = RandPhraseSimple("Tenho uma pergunta pra você.","Preciso de algumas informações.");
			if (CheckCharacterItem(pchar, "CaptainBook"))				
			{
				if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
				{
					link.l2.go = "ShipLetters_7";// генератор  "Найденные документы"
				}
				else
				{
					Link.l2.go = "quests";
				}	
			}
			else
			{
					link.l2.go = "quests";//(перессылка в файл города)
			}			
			if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
            {
                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
                {
					link.l3 = RandPhraseSimple("Quero discutir questões financeiras.","Sobre as finanças...");
					link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
			}
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "Olha, espero que você possa me ajudar. Quero comprar um "+pchar.GenQuest.Device.Shipyarder.Type+", e me disseram que essa coisa foi vendida na sua cidade. Bem, alguém estava vendendo isso nas ruas. Você sabe de algo sobre isso?";
				link.l16.go = "Device_Citizen";
			}
			// <-- генератор Неудачливый вор
			
			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	        {
				link.l5 = LinkRandPhrase("Você sabe ","Você está ciente ","Você ouviu ")+" que a igreja local foi roubada recentemente?";
				link.l5.go = "Citiz_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.
			
			Link.l6 = PCharRepPhrase(RandPhraseSimple("Seus ouvidos te enganam. Eu preciso ir.","Não, não é nada, eu estava indo para a taverna."),RandPhraseSimple("Bem, não é nada. Boa sorte!","Só estou passeando pela cidade. Até logo."));
			Link.l6.go = "exit";
		break;
		
		case "new question":
            dialog.text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("Ah, e estou tão feliz em te ver quanto por um gole, pode perguntar o que quiser.","Gosta de conversar, capitão? Eu também... Ainda mais com uma caneca de rum.","Sim, "+PChar.name+"?"),LinkRandPhrase("O que mais você quer?","Eu aceito, capitão "+PChar.name+", que você gosta de conversar?")),PCharRepPhrase(LinkRandPhrase("O que mais você quer, "+GetAddress_Form(NPChar)+"?","Estou ouvindo, capitão.","Preciso ir, então pergunte logo, Capitão."),LinkRandPhrase("Sempre fico feliz com uma companhia agradável, "+GetAddress_Form(NPChar)+" "+PChar.lastname+". Fale.","Sim, "+GetAddress_Form(NPChar)+"?","Gosta de conversar, capitão? Eu também... ")));
			link.l1 = LinkRandPhrase("Que rumores estão circulando nesta cidade?","Alguma novidade por aqui?","Como está a vida em terra?");
			link.l1.go = "rumours_townman";
			link.l2 = LinkRandPhrase("Pode me mostrar o caminho?","Não consigo encontrar o caminho para um lugar...","Me ajude a chegar a um lugar...");
			link.l2.go = "town";  //(перессылка в файл города)
			link.l3 = RandPhraseSimple("Quero saber o que dizem sobre uma pessoa.","Você sabe o que dizem sobre alguém?");
			link.l3.go = "info"; //(перессылка в файл города)
			link.l4 = RandPhraseSimple("Quero saber mais sobre os moradores daqui.","Você pode me contar algo sobre os moradores daqui?");
			link.l4.go = "RumourAboutOwners";
			link.l5 = PCharRepPhrase(RandPhraseSimple("Seus ouvidos te enganam. Eu preciso ir.","Não, não é nada, estou a caminho da taverna."),RandPhraseSimple("Bem, não é nada. Boa sorte!","Só estou passeando pela cidade. Até logo."));
			link.l5.go = "exit";
		break;
		
		case "RumourAboutOwners":
			Dialog.Text = "Em quem você está interessado?";
			if(GetCharacterIndex(NPChar.city + "_Mayor") != -1)
			{
				link.l1 = "Quero saber mais sobre o governador.";
				link.l1.go = "RumourAboutOwners_Mayor";
			}
			if(GetCharacterIndex(NPChar.city + "_TavernKeeper") != -1)
			{
				link.l2 = "Quer saber mais sobre o dono da taverna local.";
				link.l2.go = "RumourAboutOwners_TavernKeeper";
			}
			if(GetCharacterIndex(NPChar.city + "_ShipYarder") != -1)
			{
				link.l3 = "Quero saber mais sobre o mestre do estaleiro local.";
				link.l3.go = "RumourAboutOwners_ShipYarder";
			}
			if(GetCharacterIndex(NPChar.city + "_Trader") != -1)
			{
				link.l4 = "Quer saber mais sobre o dono da loja local.";
				link.l4.go = "RumourAboutOwners_Trader";
			}
			link.l9 = "Não é nada. Esqueça isso.";
			link.l9.go = "exit";
			break;
			
		case "RumourAboutOwners_TakeRumour":
			sTemp = sRumourAboutOwners_CityRumour(NPChar.City, NPChar.RumourOwnerType);
			Dialog.Text = sTemp;
			link.l1 = "Obrigado.";
			link.l1.go = "exit";
			// Здесь можно делать проверка по квестам, какой слух выпал
			DeleteAttribute(PChar, "QuestTemp.RumoursAboutOwners");
		break;
		
		//Jason --> генератор Неудачливый вор
		case "Device_Citizen":
           dialog.text = "Hm, "+pchar.GenQuest.Device.Shipyarder.Type+"? Nunca ouvi falar disso... Moro aqui há muito tempo e nunca vi nada parecido.";
			link.l1 = "Bem, isso é uma ferramenta de construção naval, "+pchar.GenQuest.Device.Shipyarder.Describe+". Alguém tem vendido algo assim na cidade? Ou talvez andando por aí com isso e você percebeu?";
			link.l1.go = "Device_Citizen_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Citizen_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) > 3 && sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 6 && npchar.sex != "woman")
			{
				dialog.text = "Hm... Sim, eu vi um homem com esse objeto algumas horas atrás. Ele estava andando pelas ruas. Era uma ferramenta interessante.";
				link.l1 = "Como ele era, e para onde estava indo? Eu realmente preciso de algo assim.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "Não, não vi nada parecido com isso.";
				link.l1 = "Entendi. Então vou continuar perguntando.";
				link.l1.go = "exit";
			}
		break;
		
		//=================== ноды квеста священника. поиск грабителей (квест №2)==================
		case "Citiz_GenQuest_Church_2_1":
			if(rand(3) != 1)
			{
				dialog.text = LinkRandPhrase("Não, não sei nada sobre isso.","Não, eu devo ir.","Eu não sei de nada.");
					link.l1 = LinkRandPhrase("Bem, obrigado.","Entendi, obrigado.","Certo, com licença.");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Não sei nada sobre isso, mas talvez você possa perguntar aos frequentadores da taverna, eles com certeza vão te contar mais.","Não posso te contar nada, pergunte a alguém na taverna.");
				link.l1 = "Obrigado por isso.";
				link.l1.go = "exit";
			}
			
			NPChar.GenQuest.ChurchQuest_2.AskedPeople = true;
		break;		
		
		//-------------------------------горожанин-пассажир----------------------------------------------
		case "passenger":
			if (hrand(19) > 9) SetPassengerParameter("Townpassenger", false);
			else SetPassengerParameter("Townpassenger", true);
			if (!CheckAttribute(pchar, "GenQuest.Townpassenger.Enemycity"))
			{
				dialog.text = "Capitão, preciso chegar à colônia chamada "+XI_ConvertString("Colony"+pchar.GenQuest.Townpassenger.City)+", assim que possível, está em "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Townpassenger.City)+"Dat")+", em "+FindRussianDaysString(sti(pchar.GenQuest.Townpassenger.DaysQty))+". Seu navio parece bem mais robusto do que a maioria desses barquinhos que navegam por aqui. Posso lhe pagar "+FindRussianMoneyString(sti(pchar.GenQuest.Townpassenger.Money))+". O que me diz?";
			}
			else
			{
				dialog.text = "Capitão, preciso chegar à colônia "+XI_ConvertString("Colony"+pchar.GenQuest.Townpassenger.City)+", está em um "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Townpassenger.City)+"Voc")+", em um "+FindRussianDaysString(sti(pchar.GenQuest.Townpassenger.DaysQty))+". Eu sei que isso parece extremamente arriscado, mas talvez "+FindRussianDublonString(sti(pchar.GenQuest.Townpassenger.Money))+" seria uma boa ajuda para você?";
			}
			link.l1 = "Hm. Também estou indo nessa direção, então estou pronto para te levar a bordo nessas condições.";
			link.l1.go = "passenger_1";
			link.l2 = "Me desculpe,  "+GetAddress_FormToNPC(NPChar)+", mas estou navegando em outra direção. Não posso te ajudar.";
			link.l2.go = "passenger_exit";
		break;
		
		case "passenger_exit":
			dialog.text = "Que pena. Bem, vou esperar por outro navio. Adeus.";
			link.l1 = "Até mais.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Townpassenger");
		break;
		
		case "passenger_1":
			dialog.text = "Ótimo, porque estou cansado de esperar. Você vai receber seu pagamento quando chegarmos lá.";
			link.l1 = "Vá para o meu navio, "+GetAddress_FormToNPC(NPChar)+". Vamos partir em breve.";
			link.l1.go = "passenger_2";
		break;
		
		case "passenger_2":
			DialogExit();
			pchar.GenQuest.Townpassenger.id = npchar.id;
			LAi_SetImmortal(npchar, true);
			DeleteAttribute(npchar, "LifeDay");
			LAi_RemoveLoginTime(npchar);
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sTitle = npchar.index+"Citizpassenger";

// LDH 13Sep17 - do not add to an existing Citizpassenger record -->
// "Rename" the quest record by copying it to a new name and deleting the old record
			if (CheckAttribute(pchar, "questinfo."+sTitle))
			{
				string sTempLDH = frand(1);
				sTempLDH = strcut(sTempLDH, 2, 5);    // 4 random digits
				string sTitle1 = sTitle+sTempLDH;

				aref arTo, arFrom;
				makearef(arFrom, pchar.questinfo.(sTitle));
				makearef(arTo,   pchar.questinfo.(sTitle1));
				CopyAttributes(arTo, arFrom);
				pchar.questinfo.(sTitle1) = "";

				DeleteAttribute(pchar, "questinfo."+sTitle);

				Trace("Duplicate Citizpassenger record "+sTitle+" copied to "+sTitle1+" **");
			}
// <--

			AddQuestRecordEx(sTitle, "Citizpassenger", "1");
			AddQuestUserDataForTitle(sTitle, "sType", "citizen");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			sTemp = XI_ConvertString("Colony" +pchar.GenQuest.Townpassenger.City) + ", which is on " + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Townpassenger.City)+"Voc")+"."; // belamour gen
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sDays", FindRussianDaysString(sti(pchar.GenQuest.Townpassenger.DaysQty)));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
            if (!CheckAttribute(pchar, "GenQuest.Townpassenger.Enemycity")) AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Townpassenger.Money)));
			else AddQuestUserData(sTitle, "sMoney", FindRussianDublonString(sti(pchar.GenQuest.Townpassenger.Money)));
			pchar.quest.Townpassenger.win_condition.l1 = "location";
			pchar.quest.Townpassenger.win_condition.l1.location = pchar.GenQuest.Townpassenger.City+"_town";
			pchar.quest.Townpassenger.function = "Townpassenger_complete";
			SetFunctionTimerCondition("Townpassenger_Over", 0, 0, sti(pchar.GenQuest.Townpassenger.DaysQty), false);
		break;
		
		case "passenger_3":
			pchar.quest.Townpassenger_Over.over = "yes"; //снять таймер
			dialog.text = "Aqui estamos, excelente! Esta viagem no seu navio foi bastante agradável. Meus agradecimentos. Aqui está o seu pagamento, senhor.";
			link.l1 = "Boa sorte, "+GetAddress_FormToNPC(NPChar)+"! Adeus.";
			link.l1.go = "passenger_4";
		break;
		
		case "passenger_4":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			npchar.lifeday = 0;
			RemovePassenger(Pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
			OfficersReaction("good");				
			AddCharacterExpToSkill(pchar, "Sailing", 80);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			if (CheckAttribute(pchar, "GenQuest.Townpassenger.Enemycity"))
			{
				AddCharacterExpToSkill(pchar, "Sneak", 50);
				TakeNItems(pchar, "gold_dublon", sti(pchar.GenQuest.Townpassenger.Money));
			}
			else AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Townpassenger.Money));
			sTitle = npchar.index+"Citizpassenger";
			AddQuestRecordEx(sTitle, "Citizpassenger", "3");
			CloseQuestHeader(sTitle);
			DeleteAttribute(Pchar, "GenQuest.Townpassenger");
		break;
//<-- горожанин-пассажир
		
		//замечение по обнажённому оружию
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ouça, como cidadão desta cidade, peço que guarde sua espada.","Escute, como cidadão desta cidade, estou pedindo que você embainhe sua espada.");
				link.l1 = LinkRandPhrase("Certo.","Como quiser.","Como quiser...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Cuidado ao correr com uma arma. Isso me deixa nervoso...","Não gosto quando um estranho passa na minha frente com uma espada desembainhada...");
				link.l1 = RandPhraseSimple("Entendi.","Não se preocupe.");
			}
			link.l1.go = "exit";
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
