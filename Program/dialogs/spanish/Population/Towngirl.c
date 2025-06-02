//Jason общий диалог мещанок
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
			if (sti(NPChar.nation) == PIRATE)
			{
				if (sti(rColony.HeroOwn) == true) // наш горожанин
				{
				    dialog.text = RandPhraseSimple("Dicen que eres el dueño de esta ciudad, "+GetSexPhrase("señor","señorita")+".","¡Qué agradable encuentro! ¡Qué agradable encuentro! ¡El gobernador mismo está hablando conmigo!");
					link.l1 = RandPhraseSimple("He cambiado de opinión. ¡Buena suerte!","Solo paseando por la ciudad. Adiós.");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("Tengo una pregunta para ti.","Necesito información.");
					link.l2.go = "quests";//(перессылка в файл города)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("Quiero discutir asuntos financieros.","Sobre finanzas...");
							link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
						}
					}
					break;
				}
				else
				{ // пираты, не наши
				    dialog.text = RandPhraseSimple("¿Qué quieres? Sigue adelante.","Deja de bloquear mi camino, piérdete.");
					link.l1 = RandPhraseSimple("¿Qué estás haciendo?","Tranquilízate. O lo haré yo mismo.");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("Quiero preguntarte.","Solo un minuto de tu atención, por favor. Una pregunta.");
					link.l2.go = "quests";//(перессылка в файл города)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("Quiero hablar de asuntos financieros.","Sobre las finanzas...");
							link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
						}
					}
					break;
				}
			}
            if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";
				dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("Soy","Mi nombre es ","Puedes llamarme ")+GetFullName(npchar)+LinkRandPhrase("¿Qué quieres?",". No te he visto antes "+", ¿quién eres?",". ¿Quién eres y qué quieres de mí?"),LinkRandPhrase("Saludos, "+GetAddress_Form(NPChar)+". Mi nombre es "+GetFullName(npchar)+"¿Y cuál es tu nombre?","Hola "+GetAddress_Form(NPChar)+"¡ Soy "+GetFullName(npchar)+". ¿Puedo saber tu nombre?","Sí, "+GetAddress_Form(NPChar)+". ¿Qué quieres? Y por cierto, mi nombre es "+GetFullName(npchar)+"¿Y cuál es tu nombre?"));
				Link.l1 = pcharrepphrase(LinkRandPhrase("¡Maldita sea!","¡Maldita sea! ","¡Maldito seas! ")+"Sí, soy el capitán "+GetFullName(Pchar)+LinkRandPhrase(", ¿nunca has oído hablar de mí, bastardo?"," y "+GetSexPhrase("el pirata más famoso","la pirata-chica más famosa")+"¡en el mar!"," ¡y maldíceme si estoy equivocado!"),LinkRandPhrase("Soy "+GetFullName(Pchar)+", capitán.","Mi nombre es "+GetFullName(Pchar)+".","Puedes llamarme capitán "+GetFullName(Pchar)+"."));
				Link.l1.go = "Meeting";
				
				//==> прибыла инспекция на Святом Милосердии
				if (CheckAttribute(pchar, "questTemp.SantaMisericordia.ColonyZapret") && pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_town")
				{
					dialog.Text = LinkRandPhrase(LinkRandPhrase("  Toda la ciudad está en vilo, don Fernando de Alamida, el inspector real, ha llegado. Sabes, he visto mucho aquí, pero esto... No es el dolor lo que cambia a las personas, sino cómo lo manejan. Dicen que se convirtió en un hombre diferente después de la muerte de su padre. Ahora no encontrarás un servidor de la Corona más incorruptible y... despiadado en todo el Archipiélago.","¡Solo mira la 'Santa Misericordia'! Dicen que el mismo rey ordenó construirla según diseños especiales. Y mira, ni un solo rasguño. Como si la misma Virgen María la protegiera. Aunque he oído rumores... tal vez no sea la Virgen en absoluto.","¿Sabes cuántas veces han intentado matar a don Fernando? ¡Doce ataques en aguas abiertas, y eso solo en el último año! Pues bien, con una tripulación tan leal y entrenada, y bajo la protección del Señor, ¡sobrevivirá al decimotercero también!"),LinkRandPhrase("¿Has oído? Don Fernando de Alamida ha llegado a nuestra ciudad, y dicen que está en alguna parte de las calles ahora mismo. Me encantaría verlo con mis propios ojos...","Un hombre complicado, este don Fernando. Algunos dicen que es un salvador, limpiando la Madre Patria de la inmundicia. Otros susurran que algo se rompió en él tras la muerte de su padre y pronto todos estaremos llorando. Pero te diré esto: no le temas a él. Teme a aquellos que lo hicieron lo que es.","¡Qué hombre tan apuesto, este don Fernando! Pero, ¿sabes qué es extraño? Es como si no notara a nadie. Todo deber y servicio. Escuché que había una chica... pero después de reunirse con algún sacerdote, rechazó completamente los placeres mundanos. Como si hubiera hecho un voto."),RandPhraseSimple(RandPhraseSimple("¡Maldito inspector! Mientras él está aquí, la ciudad está muerta. Sin comercio, sin diversión. Incluso respirar, parece, debe ser más silencioso. ¿Y sabes qué es lo más aterrador? Es lo mismo en cada puerto. Como un reloj. ¡Su Majestad Real no podría haber inventado esta tortura deliberadamente para todos nosotros!","Don Fernando visitó el orfanato de nuevo. Dona generosamente, reza durante horas. ¡Un hombre tan digno debería ser un ejemplo para esos malditos malversadores!"),RandPhraseSimple("¡Ja! 'San' Fernando cerró todos los burdeles otra vez. Bueno, no importa, pronto zarpará y los volverán a abrir.","¡El insp... inspector ha llegado, eso es! Don Fernando de Almeyda, o, cómo se llama, ¡Alamida! Tan importante que el propio gobernador anda de puntillas a su alrededor. Dicen que te mira a los ojos y ve todos tus pecados de inmediato. ¡Es aterrador!")));
					link.l1 = "... ";
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
				link.l1 = "Solo quería hablar sobre esta ciudad.";
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
						link.l3 = RandPhraseSimple("Quiero discutir asuntos financieros.","Sobre las finanzas...");
						link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
					}
				}
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
				{
					link.l16 = "Escucha, espero que puedas ayudarme. Quiero comprar un "+pchar.GenQuest.Device.Shipyarder.Type+", y me han dicho que esta cosa se ha vendido en tu pueblo. Bueno, alguien la estaba vendiendo en el mercado callejero. ¿Sabes algo al respecto?";
					link.l16.go = "Device_Citizen";
				}
				// <-- генератор Неудачливый вор
				
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	            {
					link.l5 = LinkRandPhrase("¿Sabes ","¿Eres consciente ","¿Has oído ")+"¿que la iglesia ha sido robada recientemente?");
					link.l5.go = "Citiz_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				
                dialog.Text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("Ah, eres tú "+GetFullName(Pchar)+" "+GetSexPhrase("¡viejo amigo!","¡preciosa!")+"","Me alegra verte, "+GetSexPhrase("¡viejo amigo!","¡preciosa!")+" "+Pchar.name,"Ah, eso es el "+GetSexPhrase("el propio capitán","la capitana en persona")+" "+GetFullName(Pchar))+RandPhraseSimple("¡Pensé que estabas muerto!",". Y quizás "+GetSexPhrase("borracho como siempre.","un poco borracho."))+LinkRandPhrase(" Adelante, ¿qué necesitas?","¿Qué es esta vez?"," ¿Molestándome otra vez?"),LinkRandPhrase(TimeGreeting()+", capitán ","Buen día para ti, "+GetAddress_Form(NPChar)+" ","Saludos, capitán ")+GetFullName(Pchar)+LinkRandPhrase(". ¿Cómo puedo ayudar a "+GetSexPhrase("tan digno hombre","una chica tan digna")+", como tú?","¿Por qué estás aquí?",". ¿Qué quieres saber esta vez?")),PCharRepPhrase(LinkRandPhrase("Hola, capitán ","Saludos, ah, eres tú "+GetAddress_Form(NPChar)+" ","Ah, capitán ")+GetFullName(Pchar)+LinkRandPhrase(", pensé que nunca nos volveríamos a encontrar, y",", no diré que me alegra verte pero",", veo que aún estás vivo, qué lástima y")+LinkRandPhrase(" ¿qué quieres?"," ¿por qué estás aquí?"," ¿Cómo puedo ayudarte?"),LinkRandPhrase(TimeGreeting()+", capitán "+GetFullName(Pchar)+"¿Cómo puedo ayudarte?","Oh, ese es el capitán "+GetFullName(Pchar)+"¡Cómo puedo ayudarte?","Saludos, "+GetAddress_Form(NPChar)+" "+Pchar.lastname+"¿Deseas algo?")));  
	   			link.l6 = PCharRepPhrase(RandPhraseSimple("Tus oídos te engañan. Debo irme.","No, no es nada, iba de camino a la taberna."),RandPhraseSimple("Está bien, lo que sea. ¡Buena suerte!","Solo paseando por la ciudad. Adiós."));
				link.l6.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "ShipLetters_7":
			dialog.text = "¿Preguntas?";
			link.l1 = "¿El nombre en estos documentos significa algo para usted?";
			link.l1.go = "ShipLetters_8";
		break;
		
		case "ShipLetters_8":
			dialog.text = LinkRandPhrase("No me importa un comino el papel desconocido y no sé leer. Ve al usurero, dicen que él sabe leer esas letras del diablo.","No sé de qué estás hablando, pregunta a otros ciudadanos del pueblo, capitán"+GetFullName(Pchar)+".","No sé ni cómo ayudarte, capitán "+GetFullName(Pchar)+". Intenta hablar con el usurero, él podría saber.");
			link.l1 = "¡Seguiré tu consejo con gran placer!";
			link.l1.go = "exit";
		break;
		
		case "Meeting":
		    dialog.Text = NPCharRepPhrase(npchar,LinkRandPhrase("¿No estás mintiendo, capitán "+GetFullName(Pchar)+"?","¿Entonces qué, "+PChar.name+"?","Te recordaré, "+GetFullName(Pchar)+".")+" Ahora dime, ¿qué quieres?",LinkRandPhrase("Encantado de conocerte, capitán "+PChar.name,"Me alegra nuestro encuentro,"+GetAddress_Form(NPChar)+" "+PChar.lastname,"Es un placer, capitán "+PChar.name)+". Pero dudo que solo quisieras saber mi nombre, ¿verdad?");
            link.l1 = PCharRepPhrase("Solo quiero preguntar algo sobre este agujero que llamas 'el pueblo'.","Quiero preguntarte algo sobre esta ciudad.");
			link.l1.go = "new question";
            Link.l2 = RandPhraseSimple("Tengo una pregunta para ti.","Necesito   información.");
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
					link.l3 = RandPhraseSimple("Quiero discutir asuntos financieros.","Sobre las finanzas...");
					link.l3.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
			}
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "Escucha, espero que puedas ayudarme. Quiero comprar un "+pchar.GenQuest.Device.Shipyarder.Type+" y me han dicho que esta cosa se ha vendido en tu pueblo. Bueno, alguien la estaba vendiendo en las calles. ¿Sabes algo sobre eso?";
				link.l16.go = "Device_Citizen";
			}
			// <-- генератор Неудачливый вор

			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	        {
				link.l5 = RandPhraseSimple("¿Sabes ","¿Estás al tanto ","¿Has oído ")+" ¿que la iglesia ha sido robada recientemente?");
				link.l5.go = "Citiz_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.
			Link.l6 = PCharRepPhrase(RandPhraseSimple("Tus oídos te engañan. Tengo que irme.","No, no es nada, iba camino a la taberna."),RandPhraseSimple("Bueno, no es nada, ¡Buena suerte!","Solo paseando por la ciudad. Adiós."));
			Link.l6.go = "exit";
		break;
		
		case "new question":
            dialog.text = NPCharRepPhrase(npchar,PCharRepPhrase(LinkRandPhrase("¡Oh, y me alegra verte como me alegra el aguardiente, pregunta lo que quieras!","¿Te gusta hablar, capitán? A mí también... Especialmente con una copa de ron.","¿Sí, "+PChar.name+"?"),RandPhraseSimple("¿Qué más quieres?","Tomo eso, capitán "+PChar.name+", ¿que te gusta charlar?")),PCharRepPhrase(LinkRandPhrase("¿Qué más quieres "+GetAddress_Form(NPChar)+"?","Estoy escuchando, capitán.","Tengo que irme, así que pregúntame rápido, capitán."),LinkRandPhrase("Siempre me alegra una compañía agradable, "+GetAddress_Form(NPChar)+" "+PChar.lastname+"Habla.","¿Sí, "+GetAddress_Form(NPChar)+"?","¿Te gusta hablar, capitán? A mí también... ")));
			link.l1 = LinkRandPhrase("¿Qué rumores hay por esta villa?","¿Alguna novedad en estas tierras?","¿Cómo va la vida en tierra?");
			link.l1.go = "rumours_towngirl";
			link.l2 = LinkRandPhrase("¿Puedes mostrarme el camino?","No puedo encontrar el camino a un lugar...","Ayúdame a llegar a un lugar...");
			link.l2.go = "town";  //(перессылка в файл города)
			link.l3 = RandPhraseSimple("Quiero saber qué dice la gente sobre una persona.","¿Sabes lo que dice la gente sobre una persona?");
			link.l3.go = "info"; //(перессылка в файл города)
			link.l4 = RandPhraseSimple("Quiero saber más sobre los lugareños.","¿Puedes contarme algo sobre los lugareños?");
			link.l4.go = "RumourAboutOwners";
			link.l5 = PCharRepPhrase(RandPhraseSimple("Tus oídos te engañan. Debo irme.","No, no es nada, iba camino a la taberna."),RandPhraseSimple("Bueno, no es nada. ¡Buena suerte!","Solo paseando por el pueblo. Adiós."));
			link.l5.go = "exit";
		break;
		
		case "RumourAboutOwners":
			Dialog.Text = "¿Quién te interesa?";
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
           dialog.text = "Mm, "+pchar.GenQuest.Device.Shipyarder.Type+"¿Nunca lo he oído... He estado viviendo aquí por mucho tiempo y nunca he visto algo así?";
			link.l1 = "Bueno, eso es una herramienta de construcción naval, "+pchar.GenQuest.Device.Shipyarder.Describe+"¿Ha estado alguien vendiendo algo así en el pueblo? ¿O quizás llevándolo y lo has notado?";
			link.l1.go = "Device_Citizen_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Citizen_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) > 3 && sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 6 && npchar.sex != "woman")
			{
				dialog.text = "Mm... Sí, vi a un hombre con esa cosa hace varias horas. Estaba caminando por las calles. Era una herramienta interesante.";
				link.l1 = "¿Cómo era él y hacia dónde se dirigía? Realmente necesito algo así.";
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
					link.l1 = LinkRandPhrase("Bien, gracias.","Entiendo, gracias.","Está bien, discúlpame.");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple("No sé nada sobre eso, pero puedes intentar preguntar a algunos de los habituales en la taberna, seguramente te contarán más.","No puedo decirte nada, pregunta a alguien en la taberna.");
				link.l1 = "Gracias por eso.";
				link.l1.go = "exit";
			}
			NPChar.GenQuest.ChurchQuest_2.AskedPeople = true;
		break;		
		
		//замечение по обнажённому оружию
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Escucha, como ciudadano de esta ciudad te estoy pidiendo que envaines tu espada.","Escucha, como ciudadano de esta ciudad te pido que envaines tu espada.");
				link.l1 = LinkRandPhrase("Bien.","Como desees.","Como usted diga...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ten cuidado al correr con un arma. Puedo ponerme nervioso...","No me gusta cuando algún desconocido pasa delante de mí con un arma desenvainada. Me asusta...");
				link.l1 = RandPhraseSimple("Lo tengo.","No te preocupes.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

	}
}
