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
				dialog.text = RandPhraseSimple("¿Un espía? ¡Guardias!","¡Alarma! ¡Hay un intruso!");
				link.l1 = "Cállate. Me voy.";
				link.l1.go = "fight";
				break;
			}*/
			
			if (sti(NPChar.nation) == PIRATE)
			{
				if (sti(rColony.HeroOwn) == true) // наш горожанин
				{
				    dialog.text = RandPhraseSimple("Dicen que eres el que gobierna este pueblo, "+GetSexPhrase("señor","señorita")+".","Qué encuentro tan agradable, el jefe de la ciudad se ha dirigido a mí con una pregunta.");
					link.l1 = RandPhraseSimple("He cambiado de opinión.","Solo estoy explorando este pueblo. Adiós.");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("Tengo una pregunta para ti.","Necesito información.");
					link.l2.go = "quests";//(перессылка в файл города)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("Quiero discutir negocios.","Respecto a las finanzas...");
							link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
						}
					}
					break;
				}
				else
				{ // пираты, не наши
				    dialog.text = RandPhraseSimple("¿Qué quieres? Sigue tu camino.","¡No te quedes en el camino, vete!");
					link.l1 = RandPhraseSimple("Oye, deja de ladrar, ¿no lo harás?","¡Cálmate, o podrías arrepentirte!");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("Tengo una pregunta para ti.","Un momento de tu atención, por favor. Tengo una pregunta.");
					link.l2.go = "quests";//(перессылка в файл города)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("Quiero hablar de negocios.","Respecto a las finanzas...");
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
				dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("Mi nombre es ","Mi nombre es ","Puedes llamarme ")+GetFullName(npchar)+LinkRandPhrase(". ¿Qué necesitas?",". No he "+NPCharSexPhrase(NPChar,"te he visto aquí antes","te he visto allí antes")+", ¿quién eres tú?","¿Quién eres y qué necesitas de mí?"),LinkRandPhrase("Saludos, "+GetAddress_Form(NPChar)+". Mi nombre es "+GetFullName(npchar)+". ¿Y el tuyo?","Hola, "+GetAddress_Form(NPChar)+"¡Yo soy "+GetFullName(npchar)+". ¿Puedo saber su nombre?","Sí, "+GetAddress_Form(NPChar)+". ¿Qué quieres? Por cierto, mi nombre es "+GetFullName(npchar)+". ¿Y tú eres?"));

				Link.l1 = pcharrepphrase(LinkRandPhrase("¡Por el trueno!","¡Campanas del infierno!","¡Mala suerte para ti!")+"Sí, soy el Capitán "+GetFullName(Pchar)+LinkRandPhrase(", ¿realmente no has oído hablar de mí"+NPCharSexPhrase(NPChar,", ¿pícaro?","?")," y "+GetSexPhrase("el pirata más notorio","la dama pirata más notoria")+" ¡en estas aguas! "," ¡y que arda en el Infierno si eso no es cierto!"),LinkRandPhrase("Soy Capitán"+GetFullName(Pchar)+".","Mi nombre es "+GetFullName(Pchar)+".","Puedes llamarme Capitán "+GetFullName(Pchar)));

                //LinkRandPhrase("Soy el Capitán" + GetFullName(Pchar) + ".", "Me llamo " + GetFullName(Pchar) + ".", "Puedes llamarme Capitán " + GetFullName(Pchar));
				Link.l1.go = "Meeting";
			}
			else
			{
				if(rand(5) == 1 && NPChar.sex == "woman" && !CheckAttribute(NPChar, "CitizenFindItem.NoQuest") && !CheckAttribute(PChar, "GenQuest.CitizenFindItem.StartQuest") && CheckAttribute(NPChar, "City"))
				{
					dialog.Text = "Capitán, ¿podrías ayudarme, por favor?";
					link.l1 = LinkRandPhrase("Lo siento, no. Tengo poco tiempo para perder.","Lo siento, no puedo. Demasiado ocupado.","No, no puedo. Tengo asuntos urgentes que requieren mi atención.");
					link.l1.go = "CitizenFindItem_NoQuest";
					link.l2 = LinkRandPhrase("Claro que puedo. ¿Cuál es el problema?","Sí, te ayudaré. Cuéntame más sobre ese negocio tuyo.","Dime más sobre ese negocio tuyo...");
					link.l2.go = "CitizenFindItem_1";
					NextDiag.TempNode = "First time";
					break;
				}
				
				if(CheckAttribute(PChar, "GenQuest.CitizenFindItem.CitizenID") && PChar.GenQuest.CitizenFindItem.CitizenID == NPChar.ID && CheckCharacterItem(PChar, "DOjeronRing"))
				{
					dialog.Text = "Sí, Capitán, estoy escuchando.";
					link.l1 = NPChar.name+", encontré tu anillo de bodas.";
					link.l1.go = "CitizenFindItem_Complete_1";
					break;
				}
			
				link.l1 = PCharRepPhrase("Quiero aprender más sobre este pueblo.","Háblame de este pueblo.");
				link.l1.go = "new question";
 				link.l2 = RandPhraseSimple("Tengo una pregunta para ti.","Necesito información.");
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
						link.l3 = RandPhraseSimple("Quiero discutir negocios.","Respecto a las finanzas...");
						link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
					}
				}
				// --> квестовый генератор мэра, поиск шпиёна на улице. eddy
				if (CheckAttribute(pchar, "GenQuest.SeekSpy.City") && pchar.location == (npchar.city + "_town"))
	            {
					link.l4 = NPCharSexPhrase(npchar,LinkRandPhrase("¡Espera! Dime quién eres, ¡ahora mismo! Estoy buscando a un espía enemigo por petición del gobernador de "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+"¡!","¡Alto! Actúo en interés de la ciudad "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+"por orden del gobernador. Estoy buscando por la ciudad a un agente hostil.","¡Alto, amigo! El gobernador "+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname+" quiere encontrar a un espía en la ciudad."),LinkRandPhrase("¡Espera, señora! Dime quién eres, ¡ahora mismo! Estoy buscando a un espía enemigo a petición del gobernador de "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+"¡!","Mujer, ¡debo detenerte! Actúo en interés del pueblo "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+" por orden del gobernador. Estoy buscando en la ciudad a un agente hostil","¡Quédate quieta, belleza! El gobernador "+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname+" quiere encontrar un espía en la ciudad..."));
					link.l4.go = "SitySpy";
				}
				// <-- квестовый генератор мэра, поиск шпиёна на улице
				
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
				{
					link.l16 = "Quizás puedas darme un consejo. Quiero comprar "+pchar.GenQuest.Device.Shipyarder.Type+", y me han dicho que se estaba vendiendo en tu ciudad. Bueno, alguien lo estaba vendiendo en las calles. ¿Sabes algo al respecto?";
					link.l16.go = "Device_Citizen";
				}
				// <-- генератор Неудачливый вор
				
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	            {
					link.l5 = LinkRandPhrase("¿Estás consciente?","¿Sabías tú?","¿Has oído?")+"¿que la iglesia ha sido saqueada recientemente?");
					link.l5.go = "Citiz_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				
                dialog.Text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("Oh, eres tú, "+GetFullName(Pchar)+" "+GetSexPhrase(", viejo sinvergüenza","- damisela audaz")+"","Me alegra verte de nuevo, "+GetSexPhrase("viejo amigo","belleza")+" "+Pchar.name,"Oh, es el buen viejo "+GetSexPhrase("Capitán","señora")+" "+GetFullName(Pchar))+LinkRandPhrase("¡.Pensé que estabas muerto!",". Y, ciertamente, "+GetSexPhrase("borracho como siempre.","ya bajo mal tiempo.")+"",". Y, como veo, ¡aún en libertad!")+LinkRandPhrase("Entonces, habla lo que piensas: ¿qué necesitas?","¿Qué necesitas esta vez?","¿Me estás molestando de nuevo por nada?"),LinkRandPhrase(TimeGreeting()+", Capitán ","Hola, "+GetAddress_Form(NPChar)+" ","Te saludo, Capitán ")+GetFullName(Pchar)+LinkRandPhrase(". ¿Qué podría "+GetSexPhrase("un caballero tan gallardo","una dama tan audaz")+", ¿como? ¿Podrías necesitar algo de mí?","¿Para qué has venido?",". ¿Qué quieres saber esta vez?")),PCharRepPhrase(LinkRandPhrase("Hola, Capitán ","Hola. Oh, eres tú "+GetAddress_Form(NPChar)+" ","Oh, Capitán ")+GetFullName(Pchar)+LinkRandPhrase(", pensé"+NPCharSexPhrase(NPChar," "," ")+"nunca nos volveríamos a encontrar,",", no puedo decir que estoy contento"+NPCharSexPhrase(NPChar," "," ")+"verte, pero",", Veo, todavía estás vivo. Lamentable. Entonces,")+LinkRandPhrase("¿qué necesitas?","¿a qué has venido?"," ¿qué puedo yo "+NPCharSexPhrase(NPChar,"¿en qué puedo ayudarte?","¿en qué puedo ayudarte?")),LinkRandPhrase(TimeGreeting()+", Capitán "+GetFullName(Pchar)+". ¿Con qué puedo ayudarte?","Oh, si no es"+GetSexPhrase("","")+" Capitán "+GetFullName(Pchar)+"¡ ¿Qué te gustaría saber esta vez?","Hola, "+GetAddress_Form(NPChar)+" "+Pchar.lastname+". ¿Querías algo?")));                         
	   			link.l6 = PCharRepPhrase(RandPhraseSimple("No, estás oyendo cosas. Me voy ahora.","No, nada. Solo me iba a "+GetSexPhrase("","")+" a la taberna."),RandPhraseSimple("No, nada. ¡Buena suerte para ti!","Solo estoy mirando alrededor. Adiós."));
				link.l6.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "ShipLetters_7":
			dialog.text = "¿Qué preguntas?";
			link.l1 = "¿El nombre en estos papeles te suena familiar?";
			link.l1.go = "ShipLetters_8";
		break;
		
		case "ShipLetters_8":
			dialog.text = LinkRandPhrase("No me importan los papeles desconocidos. Además, no sé leer. Ve a ver al usurero, ese diablo seguramente sabe leer y escribir.","No tengo idea de lo que estás hablando. Pregunta a los lugareños, Capitán "+GetFullName(Pchar)+".","Realmente no tengo idea de cómo ayudarte, Capitán "+GetFullName(Pchar)+". Intenta preguntar al usurero, quizás él pueda saber.");
			link.l1 = "¡Con gusto seguiré tu consejo!";
			link.l1.go = "exit";
		break;
		
		case "Meeting":
		    dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("¿Pero no estás mintiendo, Capitán "+GetFullName(Pchar)+"?","¿Y qué, "+PChar.name+"?","Te recordaré, "+GetFullName(Pchar)+".")+" ¿Y ahora, qué es lo que necesitas?",LinkRandPhrase("Un placer conocerte, Capitán "+PChar.name,"Contento"+NPCharSexPhrase(NPChar," "," ")+", conocerle, "+GetAddress_Form(NPChar)+" "+PChar.lastname,"Encantado de conocerte, Capitán "+PChar.name)+". Pero, supongo, viniste aquí por algo más que solo aprender mi nombre?");

            link.l1 = PCharRepPhrase("Quería"+GetSexPhrase("","")+"¡para saber algo sobre este agujero que llamas ciudad!","Quería"+GetSexPhrase("","")+"para saber algo sobre esta ciudad.");
			link.l1.go = "new question";
            Link.l2 = RandPhraseSimple("Tengo una pregunta para ti.","Necesito información.");
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
					link.l3 = RandPhraseSimple("Quiero discutir negocios.","Respecto a las finanzas...");
					link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
			}
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "Quizás puedas darme un consejo. Quiero comprar "+pchar.GenQuest.Device.Shipyarder.Type+", y me han dicho que se vendía en tu ciudad. Bueno, alguien lo estaba vendiendo en las calles. ¿Sabes algo sobre eso?";
				link.l16.go = "Device_Citizen";
			}
			// <-- генератор Неудачливый вор
			
			// --> квестовый генератор мэра, поиск шпиёна на улице. eddy
			if (CheckAttribute(pchar, "GenQuest.SeekSpy.City") && pchar.location == (npchar.city + "_town"))
	        {
				link.l4 = NPCharSexPhrase(npchar,LinkRandPhrase("¡Alto ahí! Dime quién eres, ¡ahora mismo! Estoy buscando a un espía enemigo a petición del gobernador de "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+".","¡Alto! Actúo en el interés de"+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+" por orden del gobernador. Estoy buscando en la ciudad a un agente hostil.","¡Alto, amigo! El gobernador "+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname+" quiere encontrar a un espía en el pueblo."),LinkRandPhrase("¡Espera, dama! Dime quién eres, ¡ahora mismo! Estoy buscando a un espía enemigo por petición del gobernador de "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+".","Mujer, ¡debo detenerte! Actúo en interés de la ciudad "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen")+" por orden del gobernador. Estoy buscando por la ciudad a un agente hostil.","¡Alto, hermosa mujer! El gobernador "+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname+" quiere buscar a un espía en el pueblo..."));
				link.l4.go = "SitySpy";
			}
			// <-- квестовый генератор мэра, поиск шпиёна на улице
			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	        {
				link.l5 = LinkRandPhrase("¿Estás consciente?","¿Has oído","¿Has oído")+" ¿que la iglesia fue saqueada recientemente?");
				link.l5.go = "Citiz_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.
			
			Link.l6 = PCharRepPhrase(RandPhraseSimple("No, estás oyendo cosas. Me voy ahora.","No, nada. Solo iba a la taberna."),RandPhraseSimple("¡No, nada. ¡Buena suerte para ti!","Solo estoy mirando alrededor. Adiós."));
			Link.l6.go = "exit";
		break;
		
		case "new question":
            dialog.text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("Oh sí, estoy casi tan contento"+NPCharSexPhrase(NPChar," "," ")+" verte como una copa de licor. Pregunta lo que quieras.","¿Te gusta hablar, Capitán? Bueno, a mí también... Especialmente con una copa de ron.","¿Sí, "+PChar.name+"?"),LinkRandPhrase("¿Qué necesitas?","Ya veo, Capitán "+PChar.name+". Eres"+GetSexPhrase("","")+" bastante hablador. ","Me has cansado"+GetSexPhrase("","")+" con tus preguntas, Capitán. Mejor ayúdame con el ron.")),PCharRepPhrase(LinkRandPhrase("¿Qué quieres saber "+GetAddress_Form(NPChar)+"?","Te estoy escuchando, Capitán.","Tengo que irme, así que por favor sea rápido, Capitán."),LinkRandPhrase("Siempre contento"+NPCharSexPhrase(NPChar," "," ")+" de tener buena compañía, "+GetAddress_Form(NPChar)+" "+PChar.lastname+". Habla tu mente.","¿Sí, "+GetAddress_Form(NPChar)+"?","¿Te gusta charlar, Capitán? Bueno, a mí también...")));

            // homo 25/06/06
			link.l1 = LinkRandPhrase("¿Qué chismes son populares en la taberna?","¿Qué está pasando en estas tierras?","¿Qué hay de nuevo en tierra aquí?");
			link.l1.go = "rumours_citizen";
			link.l2 = LinkRandPhrase("¿Puede dirigirme allí?","No puedo encontrar el camino a un lugar en particular...","¿Podrías mostrar el camino...?");
			link.l2.go = "town";  //(перессылка в файл города)
			if(Rand(1)==0)
			{
				link.l3 = LinkRandPhrase("Quiero saber qué dice la gente sobre una cierta persona.","¿No sabes lo que la gente está diciendo sobre una cierta persona?","Me gustaría aprender algo sobre los locales.");
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
				link.l3 = "Por favor, cuéntame más sobre tu colonia.";
				link.l3.go = "colony";
			}
            link.l4 = RandPhraseSimple("¡Tengo asuntos importantes!","Tengo asuntos contigo.");
			link.l4.go = "quests";  //(перессылка в файл города)
			link.l5 = PCharRepPhrase(RandPhraseSimple("No, estás oyendo cosas. Me voy ahora.","No, nada. Solo iba camino a la taberna."),RandPhraseSimple("No, nada. ¡Buena suerte para ti!","Solo estoy echando un vistazo. Adiós."));
			link.l5.go = "exit";
		break;
		
		case "RumourAboutOwners":
			Dialog.Text = "¿De quién te gustaría saber?";
			if(GetCharacterIndex(NPChar.city + "_Mayor") != -1)
			{
				link.l1 = "Sobre el gobernador.";
				link.l1.go = "RumourAboutOwners_Mayor";
			}
			if(GetCharacterIndex(NPChar.city + "_TavernKeeper") != -1)
			{
				link.l2 = "Sobre el dueño de la taberna.";
				link.l2.go = "RumourAboutOwners_TavernKeeper";
			}
			if(GetCharacterIndex(NPChar.city + "_ShipYarder") != -1)
			{
				link.l3 = "Sobre el capitán del puerto.";
				link.l3.go = "RumourAboutOwners_ShipYarder";
			}
			if(GetCharacterIndex(NPChar.city + "_Trader") != -1)
			{
				link.l4 = "Sobre el dueño de la tienda.";
				link.l4.go = "RumourAboutOwners_Trader";
			}
			link.l9 = "No importa, olvídalo.";
			link.l9.go = "exit";
			break;
			
		case "RumourAboutOwners_TakeRumour":
			sTemp = sRumourAboutOwners_CityRumour(NPChar.City, NPChar.RumourOwnerType);
			Dialog.Text = sTemp;
			link.l1 = "Gracias.";
			link.l1.go = "exit";
			// Здесь можно делать проверка по квестам, какой слух выпал
			DeleteAttribute(PChar, "QuestTemp.RumoursAboutOwners");
			break;
		
		case "colony":
			dialog.text = LinkRandPhrase("Honestamente, no sé mucho al respecto, pero aún así puedo contarte una cosa o dos.","¿Y qué le interesa de nuestra colonia?","Claro. ¿Qué te gustaría saber?");
            switch(Rand(1))
			{
				case 0:
					link.l1 = "¿Qué tipo de pueblo es este?";
					link.l1.go = "colony_town";
				break;

				case 1:
					link.l1 = "¿Qué sabes sobre el fuerte que defiende la ciudad?";
					link.l1.go = "fort";
				break;
            }
			link.l2 = "Cambiemos de tema.";
			link.l2.go = "new question";
		break;
	  // to_do
		case "colony_town":
            dialog.text = "¿Estás bromeando? ¿O es una broma? Mira la esquina derecha de tu pantalla.";
			link.l1 = "Sí, mi culpa.";
		    link.l1.go = "exit";
		break;
		
		case "fort":
            dialog.text = "No sé nada al respecto.";
			link.l1 = "Lástima.";
		    link.l1.go = "exit";
		break;
		
		//Jason --> генератор Неудачливый вор
		case "Device_Citizen":
           dialog.text = "Mmm, "+pchar.GenQuest.Device.Shipyarder.Type+"¿Nunca antes había oído hablar de eso... Qué es en realidad? Nunca había oído hablar de tal cosa en todo mi tiempo"+NPCharSexPhrase(npchar,"","")+".";
			link.l1 = "Bueno, es una herramienta de constructor de barcos, "+pchar.GenQuest.Device.Shipyarder.Describe+". ¿Alguien ha estado vendiendo tal cosa en la ciudad? Quizás. ¿Notaste a alguien tener tal cosa en sí mismo?";
			link.l1.go = "Device_Citizen_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Citizen_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) > 3 && sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 6 && npchar.sex != "woman")
			{
				dialog.text = "Hmm... Sí, supongo que he visto a una persona con algo de aspecto similar. Estaba caminando por ahí con eso hace varias horas. Un dispositivo interesante, ciertamente.";
				link.l1 = "¿Y cómo era él y hacia dónde se fue? Necesito ese instrumento con urgencia.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "No, no he visto nada parecido.";
				link.l1 = "Ya veo. Bueno, ¡hora de preguntar por ahí!";
				link.l1.go = "exit";
			}
		break;
		
		//============================ Генератор мэра. Квест по розыску шпиона на улице ============================
		case "SitySpy":
			dialog.text = NPCStringReactionRepeat(NPCharSexPhrase(npchar,"¿Y qué tiene que ver eso conmigo? ¡Soy de aquí!","¡Vaya, por qué me molestas con esto? Vivo en esta ciudad y no sé nada de tales cosas!"),NPCharSexPhrase(npchar,"¿Qué quieres de mí otra vez? ¿No te he dicho ya que no soy el espía?!","¿No te dije ya que soy de aquí?!"),NPCharSexPhrase(npchar,"¡Mi querido, eres tú de nuevo! Déjame en paz, soy de aquí.","¿Por qué me molestas con tus estúpidas preguntas otra vez?"),NPCharSexPhrase(npchar,"¡Otra vez! ¡Esto es un ultraje!","Escucha, solo déjame en paz, ¿vale? ¡Por favor!"),"block",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("¿Quién puede confirmar tu declaración?","Oh, lo siento, ya te había preguntado...","Lo siento, hay tantas personas...","Está bien, está bien...",npchar,Dialog.CurrentNode);
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
				dialog.text = "¡Cualquiera puede! Escucha, ¿por qué sigues molestándome?! Si tienes un problema, ve a ver al gobernador y resuélvelo todo!",link.l1 ="Hmm... Probablemente sea mejor no molestarlo por algo tan insignificante. Te creo.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "¡Cualquiera en esta ciudad! "+NPCharSexPhrase(npchar,GetFullName(&characters[sti(pchar.GenQuest.SeekSpy.Idx)])+" puede hacerlo, por ejemplo, ahora que "+NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.Idx)],"él","ella")+" está parado justo allí.","Oh, Señor, bueno, por ejemplo, "+NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.Idx)],GetAddress_FormToNPC(NPChar)+" "+characters[sti(pchar.GenQuest.SeekSpy.Idx)].lastname,GetFullName(&characters[sti(pchar.GenQuest.SeekSpy.Idx)]))+" puede hacerlo.");				
			link.l1 = "Está bien, veamos entonces.";
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
			dialog.text = "Sí, "+NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.BaseIdx)]," de hecho es de aquí.","ella es de aquí.");
			link.l1 = RandPhraseSimple("Lo veo"+GetSexPhrase("","")+". Gracias por la ayuda.","Todo despejado. Gracias por la ayuda.");
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
			dialog.text = "Verás, ayer estaba fuera de la ciudad, dando un paseo, y perdí mi anillo de bodas..."+GetSexPhrase("Capitán, ¿podrías buscarlo por favor?","Señora, por favor, ¡ayúdame a encontrarlo!")+"";
			link.l1 = "Por supuesto "+GetSexPhrase("¡Puedo! Para una chica tan bella como tú, puedo hacer cualquier cosa!","Te ayudaré. La Iglesia nos enseña a ayudar a los necesitados.")+"";
			link.l1.go = "CitizenFindItem_2";
			link.l2 = LinkRandPhrase("No, no puedo. Lo siento. Tengo demasiado que hacer.","Lo siento, no puedo. Acabo de recordar"+GetSexPhrase("","")+", que aún tengo negocios sin terminar...","Tengo muy poco tiempo, así que no puedo ayudarte con nada...");
			link.l2.go = "CitizenFindItem_NoQuest";
			break;
			
		case "CitizenFindItem_2":
			dialog.text = ""+GetSexPhrase("Capitán","Dama")+", ¡eso es realmente genial! Por favor, encuentra este anillo para mí, mi marido llega en solo "+sti(NPChar.LifeDay)+" días, y no querría que me viera sin mi anillo de bodas.";
			link.l1 = RandPhraseSimple("¿Dónde dices que lo perdiste?","¿Dónde realmente lo perdiste?");
			link.l1.go = "CitizenFindItem_3";
		break;
			
		case "CitizenFindItem_3":
			dialog.text = "Justo más allá de las puertas de la ciudad...";
			link.l1 = "Bueno, entonces me voy a buscarlo...";
			link.l1.go = "CitizenFindItem_4";
		break;
			
		case "CitizenFindItem_4":
			dialog.text = "Sí, por favor hazlo. Y apúrate, recuerda que solo tienes "+sti(NPChar.LifeDay)+" días.";
			link.l1 = "Recuerdo.";
			link.l1.go = "exit";
			PChar.GenQuest.CitizenFindItem.StartQuest = true;
			PChar.GenQuest.CitizenFindItem.City = NPChar.City;
			PChar.GenQuest.CitizenFindItem.CitizenID = NPChar.ID;
				
			sCity = NPChar.City + "_ExitTown";
				
			//sTemp = "randitem" + (rand(1)+1); // Т.е. может получиться, что его вовсе найти не удастся. И это гуд.
			sTemp = "randitem1";
			Log_TestInfo("El anillo estará en la ubicación, " + sTemp);
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
			dialog.text = ""+GetSexPhrase("Capitán","señorita")+"¡Estoy tan feliz! ¿Cómo puedo agradecerte?";
			link.l1 = "Oh, no hace falta agradecer, lo hice bastante desinteresadamente.";
			link.l1.go = "CitizenFindItem_Complete_2";
			link.l2 = "Un par de cientos de pesos ciertamente no harían daño...";
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
			dialog.text = "Oh, "+GetSexPhrase("Capitán, eres una persona tan noble","señora, eres tan noble")+"¡Seguro que rezaré por ti en la iglesia! Adiós...";
			link.l1 = "Adiós, "+NPChar.name+".";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(PChar,"nobility" ,1);
			AddCharacterExpToSkill(PChar, "Leadership", 10);
			AddCharacterExpToSkill(PChar, "Fortune", 10);
		break;
			
		case "CitizenFindItem_Complete_3":
			iTemp = (rand(3)+1)*50;
			dialog.text = "Oh, pero por supuesto. Aquí -"+FindRussianMoneyString(iTemp)+". Eso es todo lo que tengo. Por favor, toma este dinero... Y adiós.";
			link.l1 = "Adiós, "+GetFullName(NPChar)+".";
			link.l1.go = "exit";
			AddMoneyToCharacter(PChar, iTemp);
		break;
		// <-- Мини квест на поиск обручального кольца
		
		//=================== ноды квеста священника. поиск грабителей (квест №2)==================
		case "Citiz_GenQuest_Church_2_1":
			if(rand(3) != 1)
			{
				dialog.text = LinkRandPhrase("No, no sé nada al respecto.","No sé nada al respecto.","No sé nada.");
					link.l1 = LinkRandPhrase("Está bien, gracias.","Veo, gracias.","Bien, por favor discúlpame.");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("No sé nada al respecto, pero puedes preguntar a los clientes en la taberna, seguro que te dirán una cosa o dos.","No puedo decirte nada. Pregunta en la taberna.","No sé nada en particular, pero he oído que había chismes en la taberna.");
				link.l1 = "Bueno, es algo al menos.";
				link.l1.go = "exit";
			}
			
			NPChar.GenQuest.ChurchQuest_2.AskedPeople = true;
		break;		
		
		//замечение по обнажённому оружию
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Escucha, como ciudadano de esta ciudad, debo pedirte que te abstengas de andar con una espada desenvainada.","Escucha, como ciudadano de esta ciudad, debo pedirte que te abstengas de andar con una espada desenvainada.");
				link.l1 = LinkRandPhrase("Bien.","Bien.","Como usted diga...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sostén tus caballos "+GetSexPhrase("compañero","chica")+" cuando corres alrededor con un arma en la mano. Eso me pone nervioso...","No me gusta cuando "+GetSexPhrase("hombres","alguien")+"anda por ahí con las armas listas. Me asusta...");
				link.l1 = RandPhraseSimple("Lo tengo.","Lo guardaré.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

	}
}
