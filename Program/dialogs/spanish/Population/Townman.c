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
				    dialog.text = RandPhraseSimple("Dicen que eres dueño de este pueblo, "+GetSexPhrase("señor","señorita")+".","¡Qué agradable encuentro, "+GetSexPhrase("señor","señorita")+"!");
					link.l1 = RandPhraseSimple("He cambiado de opinión. ¡Buena suerte!","Solo paseando por el pueblo. Adiós.");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("Tengo una pregunta para ti.","Necesito información.");
					link.l2.go = "quests";//(перессылка в файл города)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("Quiero discutir asuntos financieros.","Sobre las finanzas...");
							link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
						}
					}
					break;
				}
				else
				{ // пираты, не наши
					if (sti(pchar.GenQuest.Piratekill) > 20)
					{
						dialog.text = RandPhraseSimple("¡Alarma! ¡Un lunático armado está aquí! ¡A las armas!","¡A las armas! ¡Un lunático armado está aquí!");
						link.l1 = RandPhraseSimple("¿Qué?!","¿Qué estás haciendo?!");
						link.l1.go = "pirate_fight";
					}
					else
					{
						dialog.text = RandPhraseSimple("¿Qué quieres? Sigue adelante.","Deja de bloquear mi camino, piérdete.");
						link.l1 = RandPhraseSimple("¿Sabes qué? ¡No ladres!","¡Cálmate! ¡O lo haré yo mismo!");
						link.l1.go = "exit";
						link.l2 = RandPhraseSimple("Quiero preguntarte.","Un momento de su atención, por favor. Una pregunta.");
						link.l2.go = "quests";//(перессылка в файл города)
						if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
						{
							if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
							{
								link.l3 = RandPhraseSimple("Quiero discutir asuntos financieros.","Sobre las finanzas...");
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
					dialog.text = "Buen día, "+GetAddress_Form(NPChar)+"Veo que eres capitán de tu propio barco. Quiero pedirte un favor...";
					link.l1 = "Estoy escuchando, "+GetAddress_FormToNPC(NPChar)+"¿Qué quieres?";
					link.l1.go = "passenger";
					link.l2 = "Lo siento, "+GetAddress_FormToNPC(NPChar)+", pero tengo prisa.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}

                // homo 05/08/06
				dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("Yo soy ","Mi nombre es ","Puedes llamarme ")+GetFullName(npchar)+LinkRandPhrase("¿Qué quieres?",". No te he visto antes. ¿Quién eres?","¿Quién eres y qué quieres de mí?"),LinkRandPhrase("Saludos, "+GetAddress_Form(NPChar)+". Mi nombre es "+GetFullName(npchar)+"¿Y cuál es tu nombre?","Hola, "+GetAddress_Form(NPChar)+"¡ Soy "+GetFullName(npchar)+"¿Puedo saber tu nombre?","Sí, "+GetAddress_Form(NPChar)+". ¿Qué quieres? Y por cierto, mi nombre es "+GetFullName(npchar)+"¿Y cómo te llamas?"));

				Link.l1 = pcharrepphrase(LinkRandPhrase("¡Maldita sea!","¡Maldita sea! ","¡Maldito seas! ")+"Sí, soy el capitán "+GetFullName(Pchar)+LinkRandPhrase(", ¿nunca has oído "+NPCharSexPhrase(NPChar,", bastardo?","?")," y "+GetSexPhrase("el pirata más famoso","la pirata-chica más famosa")+" ¡en el mar!","¡y maldita sea si me equivoco!"),LinkRandPhrase("Yo soy "+GetFullName(Pchar)+", capitán.","Mi nombre es "+GetFullName(Pchar)+".","Puedes llamarme capitán "+GetFullName(Pchar)+"."));
				Link.l1.go = "Meeting";
				
				//==> прибыла инспекция на Святом Милосердии
				if (CheckAttribute(pchar, "questTemp.SantaMisericordia.ColonyZapret") && pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_town")
				{
					dialog.Text = LinkRandPhrase(LinkRandPhrase("La ciudad entera está en vilo, don Fernando de Alamida, el inspector real, ha llegado. Sabes, he visto mucho aquí, pero esto... No es el dolor lo que cambia a las personas, sino cómo lo enfrentan. Dicen que se convirtió en otro hombre después de la muerte de su padre. Ahora no encontrarás un servidor más incorruptible y... despiadado de la Corona en todo el Archipiélago.","¡Solo mira el 'Santa Misericordia'! Dicen que el propio rey ordenó construirlo según diseños especiales. Y fíjate, ni un solo rasguño. Como si la Virgen María misma lo protegiera. Aunque he oído rumores... tal vez no sea la Virgen en absoluto.","¿Sabes cuántas veces han intentado matar a don Fernando? ¡Doce ataques en aguas abiertas y eso solo en el último año! Bueno, con una tripulación tan leal y entrenada, y bajo la protección del Señor, ¡sobrevivirá al decimotercer también!"),LinkRandPhrase("¿Has oído? Don Fernando de Alamida ha llegado a nuestra ciudad, y dicen que está en las calles ahora mismo. Me encantaría verlo con mis propios ojos...","Un hombre complicado, este don Fernando. Algunos dicen que es un salvador, limpiando la Madre Patria de la inmundicia. Otros susurran que algo se rompió en él tras la muerte de su padre y pronto todos estaremos llorando. Pero te diré esto: no le temas a él. Teme a aquellos que lo hicieron lo que es.","¡Qué hombre tan apuesto, este don Fernando! ¿Pero sabes qué es extraño? Es como si no notara a nadie. Todo deber y servicio. Escuché que había una chica... pero después de reunirse con algún sacerdote, rechazó completamente los placeres mundanos. Como si hubiera hecho un voto."),RandPhraseSimple(RandPhraseSimple("¡Maldito inspector! Mientras está aquí, la ciudad está como muerta. No hay comercio, ni diversión. Incluso parece que respirar debe ser más silencioso. ¿Y sabes qué es lo más aterrador? Es lo mismo en cada puerto. Como un reloj. ¡Su Majestad Real no podría haber inventado deliberadamente esta tortura para todos nosotros!","Don Fernando visitó el orfanato de nuevo. Dona generosamente, reza durante horas. ¡Un hombre tan digno debería ser puesto como ejemplo para esos malditos malversadores!"),RandPhraseSimple("¡Ja! El 'Santo' Fernando cerró todos los burdeles de nuevo. Bueno, no importa, pronto zarpará y los volverán a abrir.","¡El ins... inspector ha llegado, eso es! Don Fernando de Almeyda, o, ¿cómo se llama, Alamida? Tan importante que el propio gobernador anda de puntillas a su alrededor. Dicen que te mira a los ojos y ve todos tus pecados de inmediato. ¡Aterrador!")));
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
				link.l1 = PCharRepPhrase("Solo quiero preguntar algo sobre este agujero que llamas 'la ciudad'.","Quiero preguntarte algo sobre este pueblo.");
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
						link.l3 = RandPhraseSimple("Quiero discutir asuntos financieros.","Sobre finanzas...");
						link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
					}
				}
				
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
				{
					link.l16 = "Escucha, espero que puedas ayudarme. Quiero comprar un "+pchar.GenQuest.Device.Shipyarder.Type+", y me han dicho que esta cosa se vendía en tu pueblo. Bueno, alguien la estaba vendiendo por las calles. ¿Sabes algo?";
					link.l16.go = "Device_Citizen";
				}
				// <-- генератор Неудачливый вор
				
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	            {
					link.l5 = LinkRandPhrase("¿Sabes ","¿Estás al tanto ","¿Has oído ")+" ¿que la iglesia ha sido robada recientemente?";
					link.l5.go = "Citiz_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				
				dialog.Text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("Ah, eres tú "+GetFullName(Pchar)+" "+GetSexPhrase("¡viejo amigo!","- ¡bonita!")+"","Me alegra verte, "+GetSexPhrase("¡viejo amigo!","¡hermosa!")+" "+Pchar.name,"Oh, eso es el "+GetSexPhrase("el capitán mismo","la capitana misma")+" "+GetFullName(Pchar))+RandPhraseSimple("¡Pensé que estabas muerto!",". Y quizás "+GetSexPhrase("borracho como siempre.","un poco borracho."))+LinkRandPhrase(" Continúa, ¿qué necesitas?"," ¿Qué es esta vez?"," ¿Molestándome otra vez?"),LinkRandPhrase(TimeGreeting()+", capitán ","Buen día para ti, "+GetAddress_Form(NPChar)+" ","Saludos, capitán ")+GetFullName(Pchar)+LinkRandPhrase(". ¿Cómo puedo ayudar a "+GetSexPhrase("un hombre tan digno","una chica tan digna")+", como tú?","¿Por qué estás aquí?",". ¿Qué quieres saber esta vez?")),PCharRepPhrase(LinkRandPhrase("Hola, capitán ","Saludos, ah, eres tú "+GetAddress_Form(NPChar)+" ","Ah, capitán ")+GetFullName(Pchar)+LinkRandPhrase(", pensé que nunca nos volveríamos a encontrar, y",", no diré que me alegra verte pero",", veo que todavía estás vivo, qué pena y")+LinkRandPhrase(" ¿Qué quieres?"," ¿por qué estás aquí?"," ¿cómo puedo ayudarte?"),LinkRandPhrase(TimeGreeting()+", capitán "+GetFullName(Pchar)+"¿Cómo puedo ayudarte?","Ah, ese es el capitán "+GetFullName(Pchar)+"¡Cómo puedo ayudarte?","Saludos, "+GetAddress_Form(NPChar)+" "+Pchar.lastname+"¿Quieres algo?")));  
	   			link.l6 = PCharRepPhrase(RandPhraseSimple("Tus oídos te engañan. Tengo que irme.","No, no es nada, iba de camino a la taberna."),RandPhraseSimple("Está bien, lo que sea. ¡Buena suerte!","Solo paseando por la ciudad. Adiós."));
				link.l6.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "ShipLetters_7":
			dialog.text = "¿Preguntas?";
			link.l1 = "¿El nombre en estos papeles significa algo para ti?";
			link.l1.go = "ShipLetters_8";
		break;
		
		case "ShipLetters_8":
			dialog.text = LinkRandPhrase("No me importa un carajo un papel cualquiera y además no sé leer. Ve al usurero, dicen que él sabe hacer mierda con las letras, ¡ja!","No sé de qué estás hablando, pregunta a alguien más, capitán"+GetFullName(Pchar)+".","No sé cómo ayudarte, capitán "+GetFullName(Pchar)+" Intenta hablar con el usurero, quizá sepa algo.");
			link.l1 = "Gracias.";
			link.l1.go = "exit";
		break;
		
		case "Meeting":
		    dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("¿No estás mintiendo, capitán "+GetFullName(Pchar)+"?","¿Entonces qué, "+PChar.name+"?","Te recordaré, "+GetFullName(Pchar)+".")+" Ahora dime qué quieres.",LinkRandPhrase("Encantado de conocerte, capitán "+PChar.name,"Me alegra nuestro encuentro, "+GetAddress_Form(NPChar)+" "+PChar.lastname,"Es un placer, capitán "+PChar.name)+" Pero dudo que solo estuvieras interesado en saber mi nombre, ¿verdad?");
            link.l1 = PCharRepPhrase("Solo quiero preguntar algo sobre este maldito agujero que llamáis 'pueblo'.","Quiero preguntarte algo sobre este pueblo.");
			link.l1.go = "new question";
            Link.l2 = RandPhraseSimple("Tengo una pregunta para ti.","Necesito algo de información.");
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
					link.l3 = RandPhraseSimple("Quiero hablar sobre asuntos financieros.","Sobre las finanzas...");
					link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
			}
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "Escucha, espero que puedas ayudarme. Quiero comprar un "+pchar.GenQuest.Device.Shipyarder.Type+", y me han dicho que esta cosa se ha vendido en tu ciudad. Bueno, alguien la estaba vendiendo en las calles. ¿Sabes algo al respecto?";
				link.l16.go = "Device_Citizen";
			}
			// <-- генератор Неудачливый вор
			
			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	        {
				link.l5 = LinkRandPhrase("¿Sabes ","¿Estás al tanto ","¿Has oído ")+"¿que la iglesia fue robada recientemente?";
				link.l5.go = "Citiz_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.
			
			Link.l6 = PCharRepPhrase(RandPhraseSimple("Tus oídos te engañan. Tengo que irme.","No, no es nada, iba de camino a la taberna."),RandPhraseSimple("Bueno, no es nada, ¡Buena suerte!","Solo paseando por la ciudad. Adiós."));
			Link.l6.go = "exit";
		break;
		
		case "new question":
            dialog.text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("Ah, y me alegra verte como me alegra una botella de ron, pregunta lo que quieras.","¿Te gusta hablar, capitán? A mí también... Especialmente con una copa de ron.","¿Sí, "+PChar.name+"?"),LinkRandPhrase("¿Qué más quieres?","Tomo eso, capitán "+PChar.name+", ¿que te gusta charlar?")),PCharRepPhrase(LinkRandPhrase("¿Qué más quieres, "+GetAddress_Form(NPChar)+"?","Te escucho, capitán.","Necesito irme, así que pregúntame rápido, capitán."),LinkRandPhrase("Siempre me alegra una compañía agradable, "+GetAddress_Form(NPChar)+" "+PChar.lastname+". Habla.","¿Sí, "+GetAddress_Form(NPChar)+"?","¿Te gusta hablar, capitán? A mí también... ")));
			link.l1 = LinkRandPhrase("¿Qué rumores corren por esta ciudad?","¿Alguna noticia en esta tierra?","¿Cómo va la vida en tierra firme?");
			link.l1.go = "rumours_townman";
			link.l2 = LinkRandPhrase("¿Puedes mostrarme el camino?","No puedo encontrar el camino a un lugar..."," Ayúdame a llegar a un lugar...");
			link.l2.go = "town";  //(перессылка в файл города)
			link.l3 = RandPhraseSimple("Quiero saber qué dice la gente sobre una persona.","¿Sabes lo que dice la gente sobre una persona?");
			link.l3.go = "info"; //(перессылка в файл города)
			link.l4 = RandPhraseSimple("Quiero saber más sobre los lugareños.","¿Puedes contarme algo sobre los lugareños?");
			link.l4.go = "RumourAboutOwners";
			link.l5 = PCharRepPhrase(RandPhraseSimple("Tus oídos te engañan. Tengo que irme.","No, no es nada, estoy de camino a la taberna."),RandPhraseSimple("Bueno, no es nada. ¡Buena suerte!","Solo paseando por la ciudad. Adiós."));
			link.l5.go = "exit";
		break;
		
		case "RumourAboutOwners":
			Dialog.Text = "¿En quién estás interesado?";
			if(GetCharacterIndex(NPChar.city + "_Mayor") != -1)
			{
				link.l1 = "Quiero saber más sobre el gobernador.";
				link.l1.go = "RumourAboutOwners_Mayor";
			}
			if(GetCharacterIndex(NPChar.city + "_TavernKeeper") != -1)
			{
				link.l2 = "Quiero saber más sobre el dueño de la taberna.";
				link.l2.go = "RumourAboutOwners_TavernKeeper";
			}
			if(GetCharacterIndex(NPChar.city + "_ShipYarder") != -1)
			{
				link.l3 = "Quiero saber más sobre el maestro del astillero.";
				link.l3.go = "RumourAboutOwners_ShipYarder";
			}
			if(GetCharacterIndex(NPChar.city + "_Trader") != -1)
			{
				link.l4 = "Quiero saber más sobre el dueño de la tienda.";
				link.l4.go = "RumourAboutOwners_Trader";
			}
			link.l9 = "No es nada. Olvídalo.";
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
		
		//Jason --> генератор Неудачливый вор
		case "Device_Citizen":
           dialog.text = "Hmm, ¿"+pchar.GenQuest.Device.Shipyarder.Type+"? Nunca he oído hablar de eso... He estado viviendo aquí por mucho tiempo y nunca he visto algo así.";
			link.l1 = "Bueno, esa es una herramienta de construcción naval, "+pchar.GenQuest.Device.Shipyarder.Describe+". ¿Alguien ha estado vendiendo algo así en la ciudad? ¿O tal vez lo lleva consigo y lo has notado?";
			link.l1.go = "Device_Citizen_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Citizen_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) > 3 && sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 6 && npchar.sex != "woman")
			{
				dialog.text = "Mm... Sí, vi a un hombre con esa cosa hace varias horas. Estaba caminando por las calles. Era una herramienta interesante.";
				link.l1 = "¿Cómo se veía y hacia dónde se dirigía? Realmente necesito algo así.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "No, no he visto nada parecido.";
				link.l1 = "Ya veo. Seguiré preguntando entonces.";
				link.l1.go = "exit";
			}
		break;
		
		//=================== ноды квеста священника. поиск грабителей (квест №2)==================
		case "Citiz_GenQuest_Church_2_1":
			if(rand(3) != 1)
			{
				dialog.text = LinkRandPhrase("No, no sé nada sobre eso.","No, debo irme.","No sé nada.");
					link.l1 = LinkRandPhrase("Bien, gracias.","Ya veo, gracias.","Está bien, discúlpeme.");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("No sé nada sobre eso, pero puedes intentar preguntar a los habituales en la taberna, seguro que te contarán más.","No puedo decirte nada, pregunta a alguien en la taberna.");
				link.l1 = "Gracias por eso.";
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
				dialog.text = "Capitán, necesito llegar a la colonia llamada "+XI_ConvertString("Colony"+pchar.GenQuest.Townpassenger.City)+", lo antes posible, está en "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Townpassenger.City)+"Dat")+", en "+FindRussianDaysString(sti(pchar.GenQuest.Townpassenger.DaysQty))+". Tu barco parece sólido en comparación con la mayoría de esos pequeños botes que navegan por aquí. Puedo pagarte "+FindRussianMoneyString(sti(pchar.GenQuest.Townpassenger.Money))+" ¿Qué dices?";
			}
			else
			{
				dialog.text = "Capitán, necesito llegar a la colonia llamada "+XI_ConvertString("Colony"+pchar.GenQuest.Townpassenger.City)+", está en "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Townpassenger.City)+"Voc")+", en "+FindRussianDaysString(sti(pchar.GenQuest.Townpassenger.DaysQty))+". Sé que esto suena extremadamente arriesgado, ¿pero tal vez "+FindRussianDublonString(sti(pchar.GenQuest.Townpassenger.Money))+" sea suficiente incentivo para ti?";
			}
			link.l1 = "Hum. Yo también me dirijo en esa dirección, así que estoy listo para llevarte a bordo en estos términos.";
			link.l1.go = "passenger_1";
			link.l2 = "Lo siento, "+GetAddress_FormToNPC(NPChar)+", pero estoy navegando en otra dirección. No puedo ayudarte.";
			link.l2.go = "passenger_exit";
		break;
		
		case "passenger_exit":
			dialog.text = "Qué lástima. Bueno, esperaré otro barco. Adiós.";
			link.l1 = "Nos vemos.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Townpassenger");
		break;
		
		case "passenger_1":
			dialog.text = "Genial, porque estoy cansado de esperar. Recibirás tu pago cuando lleguemos allí.";
			link.l1 = "Ve a mi barco, "+GetAddress_FormToNPC(NPChar)+"Nos vamos pronto.";
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
			sTemp = XI_ConvertString("Colony" +pchar.GenQuest.Townpassenger.City) + ", que se encuentra en " + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Townpassenger.City)+"Voc")+"."; // belamour gen
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
			dialog.text = "¡Aquí estamos, excelente! Este viaje en tu barco fue bastante satisfactorio. Mis agradecimientos. Tome su dinero, señor.";
			link.l1 = "Buena suerte, "+GetAddress_FormToNPC(NPChar)+"¡Adiós!";
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
				dialog.text = NPCharSexPhrase(NPChar,"Escucha, como ciudadano de este pueblo te pido que envaines tu espada.","Escucha, como ciudadano de este pueblo te pido que envaines tu espada.");
				link.l1 = LinkRandPhrase("Bien.","Como desees.","Como usted diga...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ten cuidado al correr con un arma. Puedo ponerme nervioso...","No me gusta cuando algún extraño camina frente a mí con una espada desenvainada...");
				link.l1 = RandPhraseSimple("Lo tengo.","No te preocupes.");
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
