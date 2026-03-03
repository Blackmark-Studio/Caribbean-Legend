// boal 25/04/04 общий диалог горожан
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
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
    ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06
    int iTest, iTemp;
    iTest = FindColony(NPChar.City); // город
    ref rColony;
    string sTemp, sCity;
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
            /*if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				dialog.text = RandPhraseSimple("Um espião? Guardas!","Alarme! Tem um intruso!");
				link.l1 = "Cale a boca. Eu estou indo embora.";
				link.l1.go = "fight";
				break;
			}*/
			
			if (sti(NPChar.nation) == PIRATE)
			{
				if (sti(rColony.HeroOwn) == true) // наш горожанин
				{
				    dialog.text = RandPhraseSimple("Dizem que é você quem manda nesta cidade, "+GetSexPhrase("senhor","senhorita")+".","Que encontro agradável, o chefe da cidade veio até mim com uma pergunta.");
					link.l1 = RandPhraseSimple("Mudei de ideia.","Estou apenas explorando esta cidade. Adeus.");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("Tenho uma pergunta pra você.","Preciso de informações.");
					link.l2.go = "quests";//(перессылка в файл города)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("Quero falar de negócios.","Sobre as finanças...");
							link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
						}
					}
					break;
				}
				else
				{ // пираты, не наши
				    dialog.text = RandPhraseSimple("O que você quer? Vai andando.","Não fique no caminho, suma daqui!");
					link.l1 = RandPhraseSimple("Ei, para de latir, tá bom?","Fique calmo, ou pode se arrepender!");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("Tenho uma pergunta para você.","Um momento da sua atenção, por favor. Tenho uma pergunta.");
					link.l2.go = "quests";//(перессылка в файл города)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("Quero conversar sobre negócios.","Sobre as finanças...");
							link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
						}
					}
					break;
				}
			}
            if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";

                // homo 05/08/06
				dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("Meu nome é ","Meu nome é ","Pode me chamar de ")+GetFullName(npchar)+LinkRandPhrase(". O que você precisa?",". Eu não "+NPCharSexPhrase(NPChar,"já te vi aqui antes","já te vi lá antes")+", quem é você?",". Quem é você, e o que quer de mim?"),LinkRandPhrase("Saudações, "+GetAddress_Form(NPChar)+". Meu nome é "+GetFullName(npchar)+". Qual é o seu?","Olá, "+GetAddress_Form(NPChar)+"! Eu sou "+GetFullName(npchar)+". Posso saber seu nome?","Sim, "+GetAddress_Form(NPChar)+". O que você quer? Ah, meu nome é "+GetFullName(npchar)+". E quem é você?"));

				Link.l1 = pcharrepphrase(LinkRandPhrase("Pelos trovões! ","Maldição! ","Maldição pra você! ")+"Sim, eu sou o Capitão "+GetFullName(Pchar)+LinkRandPhrase(", você realmente nunca ouviu falar de mim"+NPCharSexPhrase(NPChar,", patife?","?")," e "+GetSexPhrase("o pirata mais temido","a pirata mais famosa de todas")+" nessas águas! "," e que eu queime no Inferno se isso não for verdade!"),LinkRandPhrase("Eu sou o Capitão"+GetFullName(Pchar)+".","Meu nome é "+GetFullName(Pchar)+".","Pode me chamar de Capitão "+GetFullName(Pchar)));

                //LinkRandPhrase("I am Captain" + GetFullName(Pchar) + ".", "My name is " + GetFullName(Pchar) + ".", "You may call me Captain " + GetFullName(Pchar));
				Link.l1.go = "Meeting";
			}
			else
			{
				if(rand(5) == 1 && NPChar.sex == "woman" && !CheckAttribute(NPChar, "CitizenFindItem.NoQuest") && !CheckAttribute(PChar, "GenQuest.CitizenFindItem.StartQuest") && CheckAttribute(NPChar, "City"))
				{
					dialog.Text = "Capitão, você poderia me ajudar, por favor?";
					link.l1 = LinkRandPhrase("Desculpe, não. Tenho pouco tempo disponível.","Desculpe, não posso. Estou muito ocupado.","Não, não posso. Tenho assuntos urgentes que exigem minha atenção.");
					link.l1.go = "CitizenFindItem_NoQuest";
					link.l2 = LinkRandPhrase("Claro, posso sim. Qual é o problema?","Sim, eu vou te ajudar. Me conte mais sobre esse seu negócio.","Me conte mais sobre o seu negócio...");
					link.l2.go = "CitizenFindItem_1";
					NextDiag.TempNode = "First time";
					break;
				}
				
				if(CheckAttribute(PChar, "GenQuest.CitizenFindItem.CitizenID") && PChar.GenQuest.CitizenFindItem.CitizenID == NPChar.ID && CheckCharacterItem(PChar, "DOjeronRing"))
				{
					dialog.Text = "Sim, Capitão, estou ouvindo.";
					link.l1 = NPChar.name+", eu encontrei sua aliança de casamento.";
					link.l1.go = "CitizenFindItem_Complete_1";
					break;
				}
			
				link.l1 = PCharRepPhrase("Quero saber mais sobre esta cidade.","Me fale sobre esta cidade.");
				link.l1.go = "new question";
 				link.l2 = RandPhraseSimple("Tenho uma pergunta para você.","Preciso de informações.");
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
						link.l3 = RandPhraseSimple("Quero discutir negócios.","Sobre as finanças...");
						link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
					}
				}
				// --> квестовый генератор мэра, поиск шпиёна на улице. eddy
				if (CheckAttribute(pchar, "GenQuest.SeekSpy.City") && pchar.location == (npchar.city + "_town"))
	            {
					link.l4 = NPCharSexPhrase(npchar,LinkRandPhrase("Espere! Diga quem é você—agora mesmo! Estou procurando um espião inimigo a pedido do governador de "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+"!","Pare! Estou agindo no interesse da cidade "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+" por ordem do governador. Estou procurando na cidade por um agente hostil.","Pare, amigo! O governador local "+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname+" quer encontrar um espião na cidade."),LinkRandPhrase("Espere aí, senhora! Diga quem é você – agora mesmo! Estou procurando um espião inimigo a pedido do governador de "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+"!","Mulher, preciso detê-la! Estou agindo pelo bem da cidade "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+" por ordem do governador. Estou procurando na cidade por um agente hostil","Fique parada, beleza! O governador local "+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname+" quer encontrar um espião na cidade..."));
					link.l4.go = "SitySpy";
				}
				// <-- квестовый генератор мэра, поиск шпиёна на улице
				
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
				{
					link.l16 = "Talvez você possa me dar um conselho. Quero comprar "+pchar.GenQuest.Device.Shipyarder.Type+", e me disseram que estava sendo vendido na sua cidade. Bem, alguém estava vendendo isso nas ruas. Você sabe de alguma coisa sobre isso?";
					link.l16.go = "Device_Citizen";
				}
				// <-- генератор Неудачливый вор
				
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	            {
					link.l5 = LinkRandPhrase("Você está ciente","Você sabia","Você ouviu")+" que uma igreja local foi saqueada recentemente?");
					link.l5.go = "Citiz_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				
                dialog.Text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("Oh, é você, "+GetFullName(Pchar)+" "+GetSexPhrase(", velho canalha","- mulher de destaque")+"","Bom te ver de novo, "+GetSexPhrase("meu velho","beleza")+" "+Pchar.name,"Ah, é o bom e velho "+GetSexPhrase("Capitão","senhora")+" "+GetFullName(Pchar))+LinkRandPhrase(". Eu pensei que você estivesse morto!",". E com certeza, "+GetSexPhrase("Bêbado como sempre.","já não estou me sentindo muito bem.")+"",". E, pelo que vejo, ainda em liberdade!")+LinkRandPhrase(" Então, diga o que pensa – o que você precisa?"," O que você precisa desta vez?"," Você está me importunando por nada de novo?"),LinkRandPhrase(TimeGreeting()+", Capitão ","Olá, "+GetAddress_Form(NPChar)+" ","Saúdo você, Capitão ")+GetFullName(Pchar)+LinkRandPhrase(". O que poderia "+GetSexPhrase("um cavalheiro tão distinto","uma dama tão encantadora")+", tipo? Tem algo que você precise de mim?",". O que te traz aqui?",". O que você quer saber desta vez?")),PCharRepPhrase(LinkRandPhrase("Olá, Capitão ","Olá. Ah, é você "+GetAddress_Form(NPChar)+" ","Oh, Capitão ")+GetFullName(Pchar)+LinkRandPhrase(", eu pensei"+NPCharSexPhrase(NPChar," "," ")+"nós nunca mais nos veríamos,",", não posso dizer que estou feliz"+NPCharSexPhrase(NPChar," "," ")+"ver você, mas",", entendi, você ainda está vivo. Que pena. Então,")+LinkRandPhrase(" o que você precisa?"," o que você veio fazer aqui?"," o que eu posso "+NPCharSexPhrase(NPChar,"posso te ajudar com o quê?","posso te ajudar?")),LinkRandPhrase(TimeGreeting()+", Capitão "+GetFullName(Pchar)+". Em que posso te ajudar?","Oh, se não é"+GetSexPhrase("","")+" Capitão "+GetFullName(Pchar)+"! O que você gostaria de saber desta vez?","Olá, "+GetAddress_Form(NPChar)+" "+Pchar.lastname+". Você queria alguma coisa?")));                         
	   			link.l6 = PCharRepPhrase(RandPhraseSimple("Não, você está ouvindo coisas. Vou indo agora.","Não, nada – eu só estava indo"+GetSexPhrase("","")+" para a taverna."),RandPhraseSimple("Não, nada. Boa sorte pra você!","Só estou dando uma olhada. Até logo."));
				link.l6.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "ShipLetters_7":
			dialog.text = "Que perguntas?";
			link.l1 = "O nome nesses papéis te diz alguma coisa?";
			link.l1.go = "ShipLetters_8";
		break;
		
		case "ShipLetters_8":
			dialog.text = LinkRandPhrase("Não me interesso por papéis estranhos. Além disso, não sei ler. Vá falar com o agiota, aquele diabo com certeza sabe ler e escrever.","Não faço ideia do que você está falando. Pergunte ao pessoal da cidade, Capitão "+GetFullName(Pchar)+".","Eu realmente não faço ideia de como te ajudar, Capitão "+GetFullName(Pchar)+". Tente perguntar ao agiota – talvez ele saiba.");
			link.l1 = "Vou seguir seu conselho com prazer!";
			link.l1.go = "exit";
		break;
		
		case "Meeting":
		    dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("Mas você não está mentindo, Capitão "+GetFullName(Pchar)+"?","E daí, "+PChar.name+"?","Vou me lembrar de você, "+GetFullName(Pchar)+".")+"E agora, o que você precisa?",LinkRandPhrase("É um prazer conhecê-lo, Capitão "+PChar.name,"Feliz"+NPCharSexPhrase(NPChar," "," ")+" prazer em conhecê-lo, "+GetAddress_Form(NPChar)+" "+PChar.lastname,"Prazer em conhecê-lo, Capitão "+PChar.name)+". Mas imagino que você veio aqui por algo mais do que só saber meu nome?");

            link.l1 = PCharRepPhrase("Eu queria "+GetSexPhrase("","")+" saber alguma coisa sobre esse buraco que você chama de cidade!","Eu queria"+GetSexPhrase("","")+" saber algo sobre esta cidade.");
			link.l1.go = "new question";
            Link.l2 = RandPhraseSimple("Tenho uma pergunta para você.","Preciso de informações.");
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
					link.l3 = RandPhraseSimple("Quero discutir negócios.","Sobre as finanças...");
					link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
			}
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "Talvez você possa me dar um conselho. Quero comprar "+pchar.GenQuest.Device.Shipyarder.Type+", e me disseram que estava sendo vendido na sua cidade. Bem, alguém estava vendendo isso nas ruas. Você sabe de algo sobre isso?";
				link.l16.go = "Device_Citizen";
			}
			// <-- генератор Неудачливый вор
			
			// --> квестовый генератор мэра, поиск шпиёна на улице. eddy
			if (CheckAttribute(pchar, "GenQuest.SeekSpy.City") && pchar.location == (npchar.city + "_town"))
	        {
				link.l4 = NPCharSexPhrase(npchar,LinkRandPhrase("Espere! Diga quem é você - agora mesmo! Estou procurando um espião inimigo a pedido do governador de "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+"!","Pare! Eu ajo no interesse de"+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+" por ordem do governador. Estou vasculhando a cidade em busca de um agente hostil.","Pare, amigo! O governador local "+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname+" quer encontrar um espião na cidade."),LinkRandPhrase("Espere, senhora! Diga quem é você – agora mesmo! Estou procurando um espião inimigo a pedido do governador de "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+"!","Mulher, preciso detê-la! Estou agindo no interesse da cidade "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+" por ordem do governador. Estou procurando na cidade por um agente hostil.","Pare, bela mulher! O governador local "+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname+" quer procurar um espião na cidade..."));
				link.l4.go = "SitySpy";
			}
			// <-- квестовый генератор мэра, поиск шпиёна на улице
			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	        {
				link.l5 = LinkRandPhrase("Você está ciente","Você ouviu","Você ouviu")+" que uma igreja local foi saqueada recentemente?");
				link.l5.go = "Citiz_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.
			
			Link.l6 = PCharRepPhrase(RandPhraseSimple("Não, você está imaginando coisas. Vou indo agora.","Não, nada – eu só estava indo para a taverna."),RandPhraseSimple("Não, nada. Boa sorte pra você!","Só estou dando uma olhada. Até logo."));
			Link.l6.go = "exit";
		break;
		
		case "new question":
            dialog.text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("Oh sim, estou quase tão feliz"+NPCharSexPhrase(NPChar," "," ")+" te ver como um copo de bebida. Pergunte o que quiser.","Você gosta de conversar, Capitão? Eu também... Principalmente com uma caneca de rum.","Sim, "+PChar.name+"?"),LinkRandPhrase("O que você precisa?","Entendi, Capitão "+PChar.name+". Você é"+GetSexPhrase("","")+" bem falante. ","Você me deixou exausto"+GetSexPhrase("","")+" com suas perguntas, Capitão. É melhor você me ajudar com o rum.")),PCharRepPhrase(LinkRandPhrase("O que você quer saber "+GetAddress_Form(NPChar)+"?","Estou ouvindo você, Capitão.","Eu preciso ir, então por favor seja rápido, Capitão."),LinkRandPhrase("Sempre feliz"+NPCharSexPhrase(NPChar," "," ")+"  ter boa companhia, "+GetAddress_Form(NPChar)+" "+PChar.lastname+". Fale o que pensa.","Sim, "+GetAddress_Form(NPChar)+"?","Você gosta de conversar, Capitão? Pois eu também...")));

            // homo 25/06/06
			link.l1 = LinkRandPhrase("Quais são as fofocas populares na taverna local?","O que está acontecendo por estas terras?","O que há de novo por aqui?");
			link.l1.go = "rumours_citizen";
			link.l2 = LinkRandPhrase("Pode me mostrar o caminho até lá?","Não consigo encontrar o caminho para um certo lugar...","Poderia me mostrar o caminho...?");
			link.l2.go = "town";  //(перессылка в файл города)
			if(Rand(1)==0)
			{
				link.l3 = LinkRandPhrase("Quero saber o que andam dizendo sobre uma certa pessoa.","Você não sabe o que andam dizendo sobre uma certa pessoa?","Gostaria de saber algo sobre os moradores daqui.");
				if(rand(1) == 0 || PChar.location == "LaVega_Town" || PChar.location == "PuertoPrincipe_town"
				|| PChar.location == "Pirates_town" || PChar.location == "Panama_town" || !CheckAttribute(NPChar, "City"))
				{
					link.l3.go = "info"; //(перессылка в файл города)
				}
				else
				{
					link.l3.go = "RumourAboutOwners"; // Warship. Сделал по-другому - у жителя каждого города будет свой диалог.
				}
			}
			else
			{
				link.l3 = "Por favor, me conte mais sobre a sua colônia.";
				link.l3.go = "colony";
			}
            link.l4 = RandPhraseSimple("Tenho negócios importantes!","Tenho negócios com você.");
			link.l4.go = "quests";  //(перессылка в файл города)
			link.l5 = PCharRepPhrase(RandPhraseSimple("Não, você está imaginando coisas. Vou indo agora.","Não, nada – eu só estava indo para a taverna."),RandPhraseSimple("Não, nada. Boa sorte pra você!","Só estou dando uma olhada. Até logo."));
			link.l5.go = "exit";
		break;
		
		case "RumourAboutOwners":
			Dialog.Text = "Sobre quem você gostaria de saber?";
			if(GetCharacterIndex(NPChar.city + "_Mayor") != -1)
			{
				link.l1 = "Sobre o governador.";
				link.l1.go = "RumourAboutOwners_Mayor";
			}
			if(GetCharacterIndex(NPChar.city + "_TavernKeeper") != -1)
			{
				link.l2 = "Sobre o dono da taverna local.";
				link.l2.go = "RumourAboutOwners_TavernKeeper";
			}
			if(GetCharacterIndex(NPChar.city + "_ShipYarder") != -1)
			{
				link.l3 = "Sobre o mestre do porto.";
				link.l3.go = "RumourAboutOwners_ShipYarder";
			}
			if(GetCharacterIndex(NPChar.city + "_Trader") != -1)
			{
				link.l4 = "Sobre o dono da loja local.";
				link.l4.go = "RumourAboutOwners_Trader";
			}
			link.l9 = "Deixa pra lá, esquece.";
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
		
		case "colony":
			dialog.text = LinkRandPhrase("Pra ser sincero, não sei muito sobre isso, mas ainda posso te contar uma coisa ou outra.","E o que te interessa na nossa colônia?","Claro. O que você gostaria de saber?");
            switch(Rand(1))
			{
				case 0:
					link.l1 = "Que tipo de cidade é esta?";
					link.l1.go = "colony_town";
				break;

				case 1:
					link.l1 = "O que você sabe sobre o forte que defende a cidade?";
					link.l1.go = "fort";
				break;
            }
			link.l2 = "Vamos mudar de assunto.";
			link.l2.go = "new question";
		break;
	  // to_do
		case "colony_town":
            dialog.text = "Está brincando? Ou fazendo piada? Olhe no canto superior direito da sua tela.";
			link.l1 = "É, foi mal.";
		    link.l1.go = "exit";
		break;
		
		case "fort":
            dialog.text = "Eu não sei nada sobre isso.";
			link.l1 = "Pena.";
		    link.l1.go = "exit";
		break;
		
		//Jason --> генератор Неудачливый вор
		case "Device_Citizen":
           dialog.text = "Hmm, "+pchar.GenQuest.Device.Shipyarder.Type+"? Nunca ouvi falar disso antes... O que é, afinal? Nunca ouvi falar de algo assim em todo o meu tempo"+NPCharSexPhrase(npchar,"","")+".";
			link.l1 = "Bem, é uma ferramenta de carpinteiro naval, "+pchar.GenQuest.Device.Shipyarder.Describe+". Alguém tem vendido algo assim na cidade? Talvez. Você viu alguém carregando algo desse tipo?";
			link.l1.go = "Device_Citizen_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Citizen_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) > 3 && sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 6 && npchar.sex != "woman")
			{
				dialog.text = "Hum... Sim, acho que vi alguém com algo assim. Ele estava andando por ali com isso algumas horas atrás. Um aparelho interessante, sem dúvida.";
				link.l1 = "E como ele era, e para onde foi? Eu preciso muito desse instrumento.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "Não, não vi nada parecido com isso.";
				link.l1 = "Entendi. Bem, hora de perguntar por aí!";
				link.l1.go = "exit";
			}
		break;
		
		//============================ Генератор мэра. Квест по розыску шпиона на улице ============================
		case "SitySpy":
			dialog.text = NPCStringReactionRepeat(NPCharSexPhrase(npchar,"E o que isso tem a ver comigo? Eu sou daqui!","Bem, por que você vem me incomodar com isso? Eu moro nesta cidade e não sei nada sobre essas coisas!"),NPCharSexPhrase(npchar,"O que você quer de mim de novo? Já não te disse que eu não sou o espião?!","Já não te falei que sou daqui?!"),NPCharSexPhrase(npchar,"Meu querido, é você de novo! Me deixe em paz – eu sou daqui!","Por que você está me enchendo com essas perguntas idiotas de novo?"),NPCharSexPhrase(npchar,"De novo! Agora isso é um absurdo!","Olha, só me deixa em paz, tá bom? Por favor!"),"block",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Quem pode confirmar sua afirmação?","Ah, me desculpe - já te perguntei isso antes...","Desculpe, tem tanta gente...","Tudo bem, tudo bem...",npchar,Dialog.CurrentNode);
		    link.l1.go = DialogGoNodeRepeat("SitySpy_1", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
			// ==> выбираем подтверждателя
			int num = FindNearCharacters(npchar, 20.0, -1.0, -1.0, 1.0, false, true);
			if(num > 0)
			{
				for(i = 0; i < num; i++)
				{
					iTemp = chrFindNearCharacters[i].index;
					if (CheckAttribute(&characters[iTemp], "CityType"))
					{
						if(characters[iTemp].CityType == "soldier" || characters[iTemp].CityType == "citizen")
						{
							break;
						}
					}
				}
				pchar.GenQuest.SeekSpy.Idx = chrFindNearCharacters[i].index; //индекс выбранного
				pchar.GenQuest.SeekSpy.Type = characters[sti(pchar.GenQuest.SeekSpy.Idx)].chr_ai.type; //тип кто помог
				pchar.GenQuest.SeekSpy.BaseIdx = npchar.index; //индекс
			}
		break;
		case "SitySpy_1":
			if (sti(pchar.GenQuest.SeekSpy.Idx) == -1 || sti(pchar.GenQuest.SeekSpy.Idx) == 1) //на всякий случай
			{
				dialog.text = "Qualquer um pode! Escuta, por que você continua me importunando?! Se tem algum problema, vá falar com o governador e resolva isso de uma vez!",link.l1 ="Hum... É melhor não incomodá-lo por uma coisa tão trivial. Eu acredito em você.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Alguém nesta cidade! "+NPCharSexPhrase(npchar,GetFullName(&characters[sti(pchar.GenQuest.SeekSpy.Idx)])+" posso fazer isso, por exemplo, agora que "+NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.Idx)],"ele","ela")+" está bem ali.","Oh, Senhor, bem, por exemplo, "+NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.Idx)],GetAddress_FormToNPC(NPChar)+" "+characters[sti(pchar.GenQuest.SeekSpy.Idx)].lastname,GetFullName(&characters[sti(pchar.GenQuest.SeekSpy.Idx)]))+" Eu posso fazer isso.");				
			link.l1 = "Certo, vamos ver então.";
		    link.l1.go = "SitySpy_2";
			sld = &characters[sti(pchar.GenQuest.SeekSpy.Idx)];
			sld.dialog.currentnode = "SeekSpy_Checking";
			pchar.GenQuest.SeekSpy.time = 4.0; //время на подбежать
			if (sld.chr_ai.type == "merchant") pchar.GenQuest.SeekSpy.time = 0.0; //мерчант базарит сразу
            LAi_SetActorTypeNoGroup(sld);
		break;
		case "SitySpy_2":
			sld = &characters[sti(pchar.GenQuest.SeekSpy.Idx)];
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorTurnToCharacter(npchar, sld);
			LAi_ActorDialog(sld, pchar, "", stf(pchar.GenQuest.SeekSpy.time), 0); 
			DialogExit();
		break;
		//=================== ноды квеста мэра. поиск шпиона на улице, опрос свидетеля ==================
		case "SeekSpy_Checking":
			dialog.text = "Sim, "+NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.BaseIdx)]," é mesmo um local.","ela é mesmo daqui.");
			link.l1 = RandPhraseSimple("Entendi"+GetSexPhrase("","")+". Obrigado pela sua ajuda.","Tudo certo. Obrigado pela ajuda.");
			link.l1.go = "SeekSpy_Checking_1";
		break;
		case "SeekSpy_Checking_1":
			switch (pchar.GenQuest.SeekSpy.Type)
			{
				case "guardian": LAi_SetGuardianTypeNoGroup(npchar); break;
				case "patrol":   LAi_SetPatrolTypeNoGroup(npchar);   break;
				case "citizen":  LAi_SetCitizenTypeNoGroup(npchar);  break;
				case "merchant": LAi_SetMerchantTypeNoGroup(npchar); break;
			}
			LAi_SetCitizenTypeNoGroup(&characters[sti(pchar.GenQuest.SeekSpy.BaseIdx)]);
			NextDiag.CurrentNode = "First Time";
			DialogExit();
		break;
		
		// Мини квест на поиск обручального кольца -->
		case "CitizenFindItem_1":
			dialog.text = "Veja, ontem eu estava fora da cidade, dando uma volta, e perdi minha aliança de casamento... "+GetSexPhrase("Capitão, você poderia procurar por isso, por favor?","Senhora, por favor, me ajude a encontrar isso!")+"";
			link.l1 = "Claro "+GetSexPhrase("Eu posso! Por uma moça tão bonita como você, eu faço qualquer coisa!","Eu vou te ajudar. A Igreja nos ensina a ajudar quem precisa.")+"";
			link.l1.go = "CitizenFindItem_2";
			link.l2 = LinkRandPhrase("Não, não posso. Me desculpe. Tenho muita coisa para fazer.","Desculpe, não posso. Acabei de lembrar."+GetSexPhrase("","")+", que ainda tenho assuntos pendentes...","Estou com muito pouco tempo, então não posso te ajudar com nada...");
			link.l2.go = "CitizenFindItem_NoQuest";
			break;
			
		case "CitizenFindItem_2":
			dialog.text = ""+GetSexPhrase("Capitão","Senhora")+", isso é maravilhoso! Por favor, encontre este anel para mim, meu marido chega em apenas "+sti(NPChar.LifeDay)+" dias, e eu não gostaria que ele me visse sem minha aliança de casamento.";
			link.l1 = RandPhraseSimple("Onde foi que você perdeu, você disse?","Então, onde exatamente você perdeu isso?");
			link.l1.go = "CitizenFindItem_3";
		break;
			
		case "CitizenFindItem_3":
			dialog.text = "Logo depois dos portões da cidade...";
			link.l1 = "Bem, então vou sair para procurar por isso...";
			link.l1.go = "CitizenFindItem_4";
		break;
			
		case "CitizenFindItem_4":
			dialog.text = "Sim, por favor. E seja rápido – lembre-se de que você só tem "+sti(NPChar.LifeDay)+" dias.";
			link.l1 = "Eu me lembro.";
			link.l1.go = "exit";
			PChar.GenQuest.CitizenFindItem.StartQuest = true;
			PChar.GenQuest.CitizenFindItem.City = NPChar.City;
			PChar.GenQuest.CitizenFindItem.CitizenID = NPChar.ID;
				
			sCity = NPChar.City + "_ExitTown";
				
			//sTemp = "randitem" + (rand(1)+1); // Т.е. может получиться, что его вовсе найти не удастся. И это гуд.
			sTemp = "randitem1";
			Log_TestInfo("The ring shall be in the locator - " + sTemp);
			PChar.GenQuest.CitizenFindItem.ItemLocator = sTemp;
			ChangeItemDescribe("DOjeronRing", "itmdescr_WeddingRing");			
			items[FindItem("DOjeronRing")].Name = "itmname_WeddingRing";
			items[FindItem("DOjeronRing")].City = XI_ConvertString("Colony" + NPChar.City + "Gen");
			SetFunctionTimerCondition("CitizenFindItemMiniQuest_Timer", 0, 0, sti(NPChar.LifeDay), false);
			PChar.GenQuestRandItem.(sCity).(sTemp) = "DOjeronRing";
			SetGameModeCondition("CitizenFindItemMiniQuest_CheckItem");			
		break;
			
		case "CitizenFindItem_NoQuest":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			NPChar.CitizenFindItem.NoQuest = true; // Эта девушка квест больше не даст
		break;
			
		case "CitizenFindItem_Complete_1":
			dialog.text = ""+GetSexPhrase("Capitão","moça")+"! Estou tão feliz! Como posso te agradecer?";
			link.l1 = "Ah, não precisa agradecer – fiz isso de coração.";
			link.l1.go = "CitizenFindItem_Complete_2";
			link.l2 = "Algumas centenas de pesos certamente não fariam mal...";
			link.l2.go = "CitizenFindItem_Complete_3";
			RemoveItems(PChar, "DOjeronRing", 1);
			DeleteAttribute(PChar, "GenQuest.CitizenFindItem");
			NPChar.CitizenFindItem.NoQuest = true;
			PChar.Quest.CitizenFindItemMiniQuest_Timer.over = "yes";
			BackItemDescribe("DOjeronRing");
			items[FindItem("DOjeronRing")].Name = "itmname_DOjeronRing";
			DeleteAttribute(&items[FindItem("DOjeronRing")], "City");
		break;
			
		case "CitizenFindItem_Complete_2":
			dialog.text = "Oh, "+GetSexPhrase("Capitão, você é uma pessoa tão nobre","senhora, você é tão nobre")+"! Vou certamente rezar por você na igreja! Adeus...";
			link.l1 = "Adeus, "+NPChar.name+".";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(PChar,"nobility" ,1);
			AddCharacterExpToSkill(PChar, "Leadership", 10);
			AddCharacterExpToSkill(PChar, "Fortune", 10);
		break;
			
		case "CitizenFindItem_Complete_3":
			iTemp = (rand(3)+1)*50;
			dialog.text = "Ah, claro. Aqui -"+FindRussianMoneyString(iTemp)+". Isso é tudo que eu tenho. Por favor, aceite este dinheiro... E adeus.";
			link.l1 = "Adeus, "+GetFullName(NPChar)+".";
			link.l1.go = "exit";
			AddMoneyToCharacter(PChar, iTemp);
		break;
		// <-- Мини квест на поиск обручального кольца
		
		//=================== ноды квеста священника. поиск грабителей (квест №2)==================
		case "Citiz_GenQuest_Church_2_1":
			if(rand(3) != 1)
			{
				dialog.text = LinkRandPhrase("Não, não sei nada sobre isso.","Eu não sei nada sobre isso.","Eu não sei de nada.");
					link.l1 = LinkRandPhrase("Tá certo, obrigado.","Entendi, obrigado.","Tudo bem, por favor, me desculpe.");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Eu não sei nada sobre isso, mas você pode perguntar aos frequentadores da taverna – com certeza vão te contar uma coisa ou outra.","Não posso te contar nada. Pergunte na taverna.","Não sei de nada em especial, mas ouvi dizer que rolou alguma fofoca na taverna.");
				link.l1 = "Bem, pelo menos é alguma coisa.";
				link.l1.go = "exit";
			}
			
			NPChar.GenQuest.ChurchQuest_2.AskedPeople = true;
		break;		
		
		//замечение по обнажённому оружию
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ouça – como cidadão desta cidade, preciso pedir que você não ande por aí com a lâmina desembainhada.","Ouça – como cidadão desta cidade, preciso pedir que você não ande por aí com a lâmina desembainhada.");
				link.l1 = LinkRandPhrase("Certo.","Certo.","Como você disser...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Calma aí "+GetSexPhrase("companheiro","moça")+" quando você anda por aí com uma arma na mão. Isso me deixa nervoso...","Eu não gosto quando "+GetSexPhrase("homens","qualquer um")+" andam por aí com armas em punho. Isso me assusta...");
				link.l1 = RandPhraseSimple("Entendi.","Vou guardar isso.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

	}
}
