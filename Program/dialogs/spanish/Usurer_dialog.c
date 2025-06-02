// общий диалог ростовщиков
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, chr, sld;
	aref Link, NextDiag;
	string NPC_Area, sTemp, sTitle, sDepositType1, sDepositType2;
	int LoanSum, LoanInterest, LoanPeriod, LoanResult, iPastMonths, DepositSum, DepositInterest, DepositResult, iNum, iTemp, iTotalDublonQty;
	int iRes, iPer, iDep;

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
					dialog.text = "Se acabó. Ahora deja este lugar, "+pchar.name+". Limpiaré todo este desorden.";
					link.l1 = "¡De acuerdo, zarparé!";
					link.l1.go = "exit";
					break;
				}
				//<-- работорговец
			
       			dialog.text = NPCharRepPhrase(pchar,
					LinkRandPhrase("¡La ciudad está en alarma y te están buscando por todas partes! Si fuera tú, no me quedaría aquí por mucho tiempo.","¡Todos los guardias te buscan! ¡No soy un idiota, y no me arriesgaré hablando contigo!","Corre, "+GetSexPhrase("amigo","muchacha")+", antes de que los soldados te hagan un colador..."),
					LinkRandPhrase("¿Qué quieres, vil criatura? ¡Los guardias de la ciudad están al tanto de tu posición y no te escaparás, "+GetSexPhrase("pirata inmundo","puta pirata")+"!","¡Asesino sucio, aléjate de este lugar! ¡Guardias!","¡No te temo, vil criatura! Pronto serás colgado en nuestro fuerte, no te escaparás..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("¡Je! No es un problema para mí...","  Nunca me atraparán."),
					RandPhraseSimple("Cierra la boca, "+GetWorkTypeOfMan(npchar,"")+", ¡o te cortaré la maldita lengua!","Heh, "+GetWorkTypeOfMan(npchar,"")+", ¿quieres atrapar a un pirata también? Escucha, muchacho, siéntate aquí tranquilamente y vivirás..."));
				link.l1.go = "fight";
				break;
			}
		//Jason ---------------------------------------Бремя гасконца------------------------------------
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.location == "Fortfrance_bank")
			{
				dialog.text = "¿Necesita algo, monsieur?";
				Link.l1 = "Necesito información... Quiero preguntarte algo.";
				Link.l1.go = "quests";
				Link.l2 = "¿Qué tal un pequeño préstamo?";
				Link.l2.go = "sharlie_credit";
				Link.l3 = "No, he cambiado de opinión.";
				Link.l3.go = "exit";
				if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
				{
					link.l4 = "Tome un vistazo a estos pendientes, monsieur. Los encontré en el bolsillo de un bandido en la jungla. Esto es claramente obra de un fino joyero que, estoy seguro, no es de este páramo. ¿Qué dice?";
					link.l4.go = "Sharlie_junglejew";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskiper")
				{
					link.l1 = "Sé que tienes un deudor llamado Folke Deluc. Dime, ¿qué tan grave es su... morosidad?";
					link.l1.go = "Sharlie";
				}	
				if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipermoney")
				{
					link.l1 = "Estoy aquí por la deuda de Folke Deluc.";
					link.l1.go = "Sharlie_repeat";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipercaptive")
				{
					link.l1 = "He completado su tarea, monsieur. Aquí está su... amigo español.";
					link.l1.go = "Sharlie_14";
				}
				break;
			}			
		//<-- Бремя гасконца
			
			//--> работорговец
			if (pchar.questTemp.Slavetrader == "canTakeQuest" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Bueno, al fin un capitán digno visita este lugar. Estoy tan cansado de idiotas que piensan que simplemente planto sus doblones y guineas, y cosecho cada mes para pagarles sus intereses.\nEllos vigilan cada penique, mientras no tienen idea de cómo el pobre usurero recurre a varios trucos para evitar morir de hambre él mismo y, al mismo tiempo, proporcionarles la oportunidad de comprar un ganso para Navidad.";
				Link.l1 = "Supongo que a tus clientes no les agradará escuchar tales palabras del hombre que guarda sus ahorros.";
				Link.l1.go = "GiveTaskSlave";
				npchar.quest.slave = "current";//чтобы камнем не долбил
				break;
			}	
			
			if (pchar.questTemp.Slavetrader == "TakeShoreCap_end" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "...";
				Link.l1 = "¡Escucha, viejo hámster, realmente tienes que hacer todo lo posible ahora para explicarme todo! ¡No había esclavos en la carga de ese barco, sino una compañía de soldados! ¡Fue bastante difícil tratar con ellos! Estoy muy enfadado, así que será mejor que te expliques.";
				Link.l1.go = "Slaveshore_5";
				break;
			}	
			if (pchar.questTemp.Slavetrader == "Win_HavanaFort" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "¡Ah, por fin estás aquí! Todo el archipiélago chismea sobre tu audaz ataque. ¡Me alegra verte!";
				Link.l1 = "Preferiría la oscuridad a ese tipo de fama... Es demasiado peligroso.";
				Link.l1.go = "Win_Havana_Fort";
				break;
			}	
			if (pchar.questTemp.Slavetrader == "Havana_seekslaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "¿Has traído mis cinco mil esclavos?";
				if (GetSquadronGoods(Pchar, GOOD_SLAVES) >= 5000)
				{
					Link.l1 = "Así es. Están en mi bodega de carga.";
					Link.l1.go = "Havana_Fort_yesA";
				}
				else
				{
					Link.l1 = "No, todavía estoy trabajando en ello.";
					Link.l1.go = "exit";
				}
				break;
			}	
			
			if (pchar.questTemp.Slavetrader == "End_quest_bad" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Mm... ¿Sigues con vida? Extraño. Pero no durará mucho. ¡Soldados! ¡Ayuda! ¡Tengo un bandido aquí!";
				link.l1 = "¡Qué bastardo!";
				link.l1.go = "exit";
				LAi_group_Attack(NPChar, Pchar);
				break;
			}
			
			if(pchar.questTemp.Slavetrader == "wait_6" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_6") > 6 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Buenos días. Mi nombre es "+GetFullName(npchar)+". ¿En qué puedo servirle?";
				link.l1 = "¡Oh! ¿Qué hace usted aquí, señor?";
				link.l1.go = "Usurer_Escape";
				break;
			}
			//<-- работорговец
			// ФМК-Гваделупа
			if(CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "killers" && npchar.location == "BasTer_bank")
			{
				dialog.Text = "...";
				link.l1 = "Hola, bastardo. ¿Se te ocurrió una brillante idea? ¿Contrataste matones para matarme? ¿Querías silenciarme? ¡Habla, ahora!";
				link.l1.go = "FMQG_x";
				break;
			}
			// Леди Бет -->
			if (pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_Bank" && !CheckAttribute(pchar, "questTemp.LadyBeth_Usurer")) // Блеквуд в городе
			{
				dialog.Text = "¡Oh, Capitán! Por favor, mire lo que tengo hoy. Algunos artículos que adquirí de los hombres de Blackwood. Necesitan dinero para una nueva expedición, y para nosotros... el beneficio, ¿no es así?";
				link.l1 = "¿Sabe Blackwood que sus hombres están vendiendo sus hallazgos?";
				link.l1.go = "LadyBeth_Usurer_1";
				break;
			}
			// Леди Бет <--
			if(NPChar.quest.meeting == "0")
			{
				dialog.Text = LinkRandPhrase(LinkRandPhrase("Buen día para usted, "+GetAddress_Form(NPChar)+"¿Cómo puedo ayudarle? ¿Le conozco?","Entra, capitán. Me llamo "+GetFullName(npchar)+" y soy el banquero.","Encantado de conocerte, "+GetAddress_Form(NPChar)+"¡Soy el banquero, y si tienes algún problema de dinero, entonces puedo ayudarte!"),LinkRandPhrase("¿Nos hemos conocido antes, capitán? Yo soy "+GetFullName(npchar)+", y soy el banquero.","Entra, capitán. Mi nombre es "+GetFullName(npchar)+" y soy el banquero.","Saludos, "+GetAddress_Form(NPChar)+". Yo soy "+GetFullName(npchar)+", el banquero."),LinkRandPhrase("Encantado de conocerte, "+GetAddress_Form(NPChar)+", yo soy "+GetFullName(npchar)+", solo un modesto banquero en esta maravillosa ciudad.","¡Es tu decisión, capitán! ¿Quieres pedirme prestadas unas monedas, o prestar dinero con interés?","¡Señor capitán! ¡Me alegra tanto que haya visitado mi modesta oficina!"));
				link.l1 = RandPhraseSimple(LinkRandPhrase("¡Un placer! Acabo de dar un paseo por la ciudad y decidí visitarte.","Un placer, soy "+GetFullName(pchar)+", encantado de conocerte.",""+GetFullName(pchar)+", capitán del barco llamado "+pchar.ship.name+", encantado de conocerte. Esto es un banco, ¿verdad?"),RandPhraseSimple("Encantado de conocerte. Soy "+GetFullName(pchar)+". Capitán del barco llamado "+pchar.ship.name+". Solo quería conocerte.","Ajá, entonces tienes un banco aquí, ¿verdad? Encantado de conocerte, soy "+GetFullName(pchar)+", capitán de mi propio navío."));
				link.l1.go = "next";
				NPChar.quest.meeting = "1";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_bank")
				{
					dialog.text = "Lady MacArthur, bienvenida, pase adelante.";
					link.l1 = "Gracias, "+npchar.lastname;
					link.l1.go = "Helen_next";
				}
			}
			else
			{
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("¡Eres tú! ¿Qué quieres, "+GetAddress_Form(NPChar)+"?","¿Cuál es tu negocio aquí, capitán? Lo siento, pero tu reputación no te hace un cliente muy deseado.","¡Aha, otro cliente! Al principio pensé que eras un ladrón... ja-ja, sólo estoy bromeando."),LinkRandPhrase("¡Oh! ¿Qué quieres? Esto es un banco, no una taberna.","Buen día para usted, capitán. Debo informarle que soy bastante selectivo al elegir a mis clientes.","¿Qué deseas, "+GetFullName(pchar)+"? Espero que recuerdes que tu renombre no te permitirá obtener un gran préstamo."),LinkRandPhrase("Espero que desees invertir dinero, "+GetAddress_Form(NPChar)+", no te será fácil conseguir un préstamo.","Capitán "+GetFullName(pchar)+" ¿Qué deseas del modesto banquero? Lo siento, pero no podré arreglar un préstamo para ti. Solo puedo recibir inversiones con interés.","Entre, "+GetAddress_Form(NPChar)+". Lamento informar que no es el cliente más bienvenido, pero no suelo rechazar a las personas de inmediato.")),LinkRandPhrase(LinkRandPhrase("Hola, señor "+GetFullName(pchar)+". ¡Siempre estoy listo para ayudarle con sus problemas de negocios!","Hola, señor "+GetAddress_Form(NPChar)+"Siempre estoy dispuesto a otorgar un préstamo o aceptar cualquier inversión.","Querido "+GetFullName(pchar)+", ¡me alegra verte! ¿Qué deseas?"),LinkRandPhrase("Capitán "+GetFullName(pchar)+", ¡siempre estoy a su servicio! ¿Desea obtener un préstamo o invertir dinero a interés?","¡Saludos a usted, capitán! Siempre es un cliente deseado aquí. ¡Tiene una excelente reputación comercial!","Buen día, "+GetFullName(pchar)+". Me alegra que me hayas visitado de nuevo. Espero que hayas venido por un acuerdo comercial rentable."),LinkRandPhrase("¡Buenos días, capitán! ¿Qué desea? ¿Quiere solicitar un préstamo o hacer una inversión?","Capitán "+GetFullName(pchar)+", ¿desea prestar dinero en condiciones rentables? Siempre me alegra ver a un cliente tan respetable.","¡Encantado de verte de nuevo, capitán! Siempre estoy listo para ayudarte, ya sea para obtener un préstamo o para hacer una inversión.")));
				link.l1 = pcharrepphrase(RandPhraseSimple(LinkRandPhrase("Sin bromas, banquero, tengo un negocio para ti.","Demasiada charla, camarada. Vamos directo al grano.","¿Has oído que el dinero no tiene olor? Así que tapa tu nariz y vayamos al grano."),LinkRandPhrase("¿Y así es como recibes a tus clientes? Suerte para ti que estoy de buen humor hoy.","¡Ja! No te alegras de verme, ¿eh? Y no soy yo un doblón de oro para causarte una buena impresión. En fin, hagamos negocios, usurero.","Eh, me gustaría enseñarte un poco de respeto pero no tengo tiempo para esto. Hablemos de dinero en su lugar.")),
				RandPhraseSimple(LinkRandPhrase("¡Me alegra ver a mi viejo amigo!","Siempre es un placer venir aquí, camarada. Vayamos directo al grano.","Yo también me alegro mucho. Hablemos de negocios, amigo."),LinkRandPhrase("Estoy realmente encantado de verte. ¿Qué hay de nuevo en los mares financieros?","Me alegra que todavía me recuerdes. Tengo prisa, así que vayamos directo al grano.","¡Hola, viejo amigo! ¡Me alegra verte de nuevo!")));
				link.l1.go = "next";
			}
			break;
			
			case "next":
			dialog.text = NPCStringReactionRepeat("¿Cómo puedo ayudarle?",
				"¿Qué quieres esta vez?",
				"Mm... ¿cuáles son tus preocupaciones?",
				"Eh, "+GetAddress_Form(npchar)+", no puedes ni imaginar lo molestos que pueden ser los clientes...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("No gracias, solo estoy paseando y charlando con la gente.",
				"Soy yo otra vez. Solo quería hablar contigo.",
				"Sí, soy yo de nuevo. Nada serio, solo quería hablar contigo.",
				"Sí, ser banquero no es tan fácil a veces. Solo quería hablar...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			link.l2 = "Quiero discutir nuestros asuntos financieros.";
			link.l2.go = "LoanUsurer";//(на кредитный генератор)
			link.l3 = "Estoy interesado en joyas y en ídolos, o gemas inusuales.";
			if (!isMultiObjectKnown("gold_dublon"))
			{
				link.l3.go = "items_0";
			}
			else
			{
				link.l3.go = "items_1";
			}	
			link.l4 = "Necesito algo de información. Bueno, tengo algo que preguntarte.";
			link.l4.go = "quests";//(перессылка в файл города)
//Jason, генер почтового курьера 2 уровня
			if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
			{
				if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					link.l12 = "He traído los documentos comerciales de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
					link.l12.go = "Postcureer_LevelUp_ForAll";
				}
			}
			//квесты мэра, проникновение во враждебный город
  			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
			{
				link.l7 = RandPhraseSimple("Estoy aquí por las órdenes de un hombre. Es el gobernador "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",
					GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" me envió aquí. Tengo que obtener algo de usted.");
				link.l7.go = "IntelligenceForAll";
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "usurer_keeper")
			{
				link.l9 = "Buen día, fui invitado por su hijo."; 
				link.l9.go = "EncGirl_4";
				pchar.quest.EncGirl_GetLoverFather.over = "yes";
			}	
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer"))
			{
				link.l10 = "Me interesa saber quién es el propietario del documento.";
				link.l10.go = "ShipLetters_Usurer1";			
			}
			
			//--> семейная реликвия // лесник переписал с нпчара на чара 
			if (CheckAttribute(pchar, "GenQuest.Noblelombard") && npchar.city == pchar.GenQuest.Noblelombard.City && !CheckAttribute(pchar, "quest.noblelombard"))// вот тут 
			{
				link.l11 = "Quiero hablar sobre la deuda de su cliente. Su nombre es "+pchar.GenQuest.Noblelombard.Name+". Él empeñó la reliquia de su familia. En este momento represento sus intereses, y tengo derechos para discutir con usted la devolución.";
				link.l11.go = "Noblelombard";			
			}
			if (CheckAttribute(pchar, "GenQuest.Noblelombard.Giveregard") && npchar.city == pchar.GenQuest.Noblelombard.City)
			{
				link.l11 = "Tuvimos una reunión hace tres meses y hablamos sobre la reliquia de un hombre. Su nombre era "+pchar.GenQuest.Noblelombard.Name+". ¿Lo recuerdas? Tuvo que abrir un depósito a mi nombre. La suma es "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Regard))+"...";
				link.l11.go = "Noblelombard_5";			
			}
			//<-- семейная реликвия
			
			//-->работорговец
			if (pchar.questTemp.Slavetrader == "Seek_slaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id) 
			{
				link.l8 = "Se trata de tu ... asignación de esclavo.";
				link.l8.go = "Checkslaves";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Buen día, "+NPChar.name+". Hablemos de tu asignación.";
				link.l8.go = "Takeslaves_4_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway_pinas" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Buen día, "+NPChar.name+". Hablemos sobre tu asignación.";
				link.l8.go = "Pinas_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "died" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Buen día, "+NPChar.name+". Hablemos de tu asignación.";
				link.l8.go = "Takeslaves_4_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait") > 20 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "He venido, como acordamos. ¿Tienes trabajo para mí?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "waitship" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Vine como prometí. ¿Qué tal un trabajo?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_1" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_1") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Buen día, "+npchar.name+". ¿Cómo le va? ¿Tiene algún trabajo para mí?";
				link.l8.go = "EscapeSlave";
				break;
			}
			if(pchar.questTemp.Slavetrader == "escapeslave_win" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Tu misión está cumplida. Pude encontrar a esos fugitivos. Sin embargo, no fue tan fácil.";
				link.l8.go = "Escape_slaves_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_2" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_2") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Buen día, "+npchar.name+". He venido por una nueva tarea rentable.";
				link.l8.go = "Slaveshore";
				break;
			}			
			
			if(pchar.questTemp.Slavetrader == "goodbye" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Malas noticias,"+npchar.name+". No logré conseguir el bergantín.";
				link.l8.go = "Brig_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goodbye_1" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Mira,  "+npchar.name+". He perseguido al bergantín, pero no encontré ningún documento. ¿Estás seguro de que estaban allí?";
				link.l8.go = "Letter_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "winbrig" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Buenas noticias,"+npchar.name+". He podido cazar ese bergantín, y encontrar los documentos. Aquí están.";
				link.l8.go = "Brig_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_3" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_3") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Buen día, "+npchar.name+". ¿Has preparado una nueva misión para mí?";
				link.l8.go = "SlaveGalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wingalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", pude interceptar ese llamado 'galéon'.";
				link.l8.go = "Wingalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostgalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", lo siento mucho, pero no pude abordar el galeón.";
				link.l8.go = "Lostgalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_4" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_4") > 4 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Buen día, "+npchar.name+". He venido por mi dinero.";
				link.l8.go = "FindRat";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wincorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", tu misión está completa. Ese bastardo de Gontier está muerto, al igual que su tripulación.";
				link.l8.go = "Wincorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostcorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", lo lamento, pero no he logrado atrapar a Francois Gontier, aunque lo estuve siguiendo hasta Tortuga. Logró escapar de mí en su corbeta.";
				link.l8.go = "lostcorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_5" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_5") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Buen día,"+npchar.name+". Cuéntame sobre esa nueva misión que has preparado para mí.";
				link.l8.go = "Havana_fort";
				break;
			}
			//<--работорговец
			NextDiag.TempNode = "First time";
		break;
		
		case "Helen_next":
			dialog.text = NPCStringReactionRepeat("No diría que necesitas dinero o que buscas hacer crecer tu riqueza. ¿Qué te trae a mi oficina?",
				"¿Qué deseas esta vez?",
				"Mm... ¿cuáles son tus preocupaciones?",
				"Eh, "+GetAddress_Form(npchar)+", ni siquiera puedes imaginar cuán molestos pueden ser los clientes...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("No gracias, solo estoy paseando y conversando.",
				"Yo otra vez. Solo quería hablar contigo.",
				"Sí, soy yo otra vez. Nada serio, solo quería hablar contigo.",
				"Sí, ser banquero no es tan fácil a veces. Solo quería hablar...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			link.l2 = "Quiero discutir nuestros asuntos financieros.";
			link.l2.go = "LoanUsurer";//(на кредитный генератор)
			link.l3 = "Me interesan las joyas y los ídolos, o gemas inusuales.";
			if (!isMultiObjectKnown("gold_dublon"))
			{
				link.l3.go = "items_0";
			}
			else
			{
				link.l3.go = "items_1";
			}	
			link.l4 = "Necesito información. Bueno, tengo algo que preguntarte.";
			link.l4.go = "quests";//(перессылка в файл города)
//Jason, генер почтового курьера 2 уровня
			if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
			{
				if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					link.l12 = "He traído los documentos comerciales de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
					link.l12.go = "Postcureer_LevelUp_ForAll";
				}
			}
			//квесты мэра, проникновение во враждебный город
  			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
			{
				link.l7 = RandPhraseSimple("Estoy aquí por las órdenes de un hombre. Él es el gobernador "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",
					GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" me envió aquí. Tengo que obtener algo de usted.");
				link.l7.go = "IntelligenceForAll";
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "usurer_keeper")
			{
				link.l9 = "Buen día, fui invitado por su hijo."; 
				link.l9.go = "EncGirl_4";
				pchar.quest.EncGirl_GetLoverFather.over = "yes";
			}	
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer"))
			{
				link.l10 = "Me interesa saber quién es el propietario del documento.";
				link.l10.go = "ShipLetters_Usurer1";			
			}
			
			//--> семейная реликвия // лесник переписал с нпчара на чара 
			if (CheckAttribute(pchar, "GenQuest.Noblelombard") && npchar.city == pchar.GenQuest.Noblelombard.City && !CheckAttribute(pchar, "quest.noblelombard"))// вот тут 
			{
				link.l11 = "Quiero hablar sobre la deuda de tu cliente. Su nombre es "+pchar.GenQuest.Noblelombard.Name+". Empeñó su reliquia familiar. Yo represento sus intereses aquí y tengo derecho a discutir contigo la devolución.";
				link.l11.go = "Noblelombard";			
			}
			if (CheckAttribute(pchar, "GenQuest.Noblelombard.Giveregard") && npchar.city == pchar.GenQuest.Noblelombard.City)
			{
				link.l11 = "Tuvimos una reunión hace tres meses y hablamos sobre la reliquia de un hombre. Su nombre era "+pchar.GenQuest.Noblelombard.Name+". ¿Lo recuerdas? Tenía que abrir un depósito a mi nombre. La suma era de "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Regard))+"...";
				link.l11.go = "Noblelombard_5";			
			}
			//<-- семейная реликвия
			
			//-->работорговец
			if (pchar.questTemp.Slavetrader == "Seek_slaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id) 
			{
				link.l8 = "Se trata de tu ... asignación de esclavo.";
				link.l8.go = "Checkslaves";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Buen día, "+NPChar.name+", hablemos de tu misión.";
				link.l8.go = "Takeslaves_4_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway_pinas" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Buen día, "+NPChar.name+", hablemos de tu asignación.";
				link.l8.go = "Pinas_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "died" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Buen día, "+NPChar.name+", hablemos sobre tu tarea.";
				link.l8.go = "Takeslaves_4_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait") > 20 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "He venido, tal como acordamos. ¿Tienes algún trabajo para mí?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "waitship" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Vine como prometí. ¿Qué tal un trabajo?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_1" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_1") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Buen día, "+npchar.name+". ¿Cómo estás? ¿Tienes una nueva tarea para mí?";
				link.l8.go = "EscapeSlave";
				break;
			}
			if(pchar.questTemp.Slavetrader == "escapeslave_win" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "La misión está cumplida. Pude encontrar a esos fugitivos. Sin embargo, no fue tan fácil.";
				link.l8.go = "Escape_slaves_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_2" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_2") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Buen día, "+npchar.name+". Vine por una nueva tarea rentable.";
				link.l8.go = "Slaveshore";
				break;
			}			
			
			if(pchar.questTemp.Slavetrader == "goodbye" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Malas noticias,"+npchar.name+". He fallado en conseguir el bergantín.";
				link.l8.go = "Brig_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goodbye_1" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Mira, "+npchar.name+". He perseguido al bergantín, pero no encontré papeles. ¿Estás seguro de que estaban allí?";
				link.l8.go = "Letter_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "winbrig" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Buenas noticias,"+npchar.name+". Pude cazar a ese bergantín, y encontrar los documentos. Aquí están.";
				link.l8.go = "Brig_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_3" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_3") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Buen día, "+npchar.name+". ¿Ha preparado una nueva tarea para mí?";
				link.l8.go = "SlaveGalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wingalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", pude interceptar ese llamado 'galeón'.";
				link.l8.go = "Wingalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostgalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", lo siento mucho pero no pude abordar este galeón.";
				link.l8.go = "Lostgalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_4" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_4") > 4 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Buen día, "+npchar.name+". Vine por mi dinero.";
				link.l8.go = "FindRat";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wincorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", tu misión está completa. Ese bastardo de Gontier está muerto, y su tripulación también.";
				link.l8.go = "Wincorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostcorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", lo lamento, pero no he podido atrapar a Francois Gontier, aunque lo estuve siguiendo hasta Tortuga. Logró escapar de mí en su corbeta.";
				link.l8.go = "lostcorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_5" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_5") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Buen día,"+npchar.name+". Háblame de esa nueva misión que has preparado para mí.";
				link.l8.go = "Havana_fort";
				break;
			}
			//<--работорговец
			NextDiag.TempNode = "First time";
		break;

		case "items_0":
			dialog.text = "¿Quieres comprar algunos doblones de oro o cofres para ellos? Confía en mí, es una inversión muy valiosa.";
			link.l1 = "Sí, eso es muy interesante.";
			link.l1.go = "items";
			AddQuestRecordInfo("Recipe", "Gold_dublon");
			SetAlchemyRecipeKnown("gold_dublon");
			SetAlchemyRecipeKnown("Chest");
			npchar.quest.meeting = "1"; 			
		break;
		
		case "items_1":
			dialog.text = "¿Quieres comerciar por pesos o doblones?";
			link.l1 = "Por pesos.";
			link.l1.go = "items";
			link.l2 = "Por doblones.";
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
			dialog.text = "Me tomará mucho tiempo leer estos documentos, y mi tiempo cuesta mucho.";
			link.l1 = "¿Tal vez "+sti(pchar.questTemp.different.GiveShipLetters.price1)+" pesos compensen su tiempo?";
			link.l1.go = "ShipLetters_Usurer2";
			link.l2 = "Como desees. ¡Adiós!";
			link.l2.go = "exit";
		break;
		
		case "ShipLetters_Usurer2":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.GiveShipLetters.price1));
			pchar.questTemp.different.GiveShipLetters.speakUsurer_1 = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Déjame echar un vistazo. No, nunca he visto este nombre antes. Muéstraselo a nuestro maestro de puerto.";
				link.l1 = "¡Lo siento, pero teníamos un trato! ¡Prometiste hablarme de este capitán!";
				link.l1.go = "ShipLetters_Usurer2_1";
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
			{
				s1 = "Bueno... Conozco al dueño de este barco. No es un hombre muy rico, pero tiene algo de opulencia.";
				dialog.text = s1+"Dicen que es un contrabandista exitoso. ¿Eso es lo que querías escuchar?";
				link.l1 = "Al parecer, sí...";
				link.l1.go = "ShipLetters_Usurer2_2";
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
			{
				s1 = "Bueno... No estoy seguro de poder felicitarle por su hallazgo.";
				dialog.text = s1+"Estos documentos están firmados para nuestro barco de patrulla colonial y su capitán es conocido por sus fuertes principios.";
				link.l1 = "¿Una patrulla? ¿Bajo el mando del comandante?";
				link.l1.go = "ShipLetters_Usurer2_3";
			}
		break;
		
		case "ShipLetters_Usurer2_1":
			dialog.text = "Te prometí echar un vistazo a esos papeles y nada más. Puedes irte.";
			link.l1 = "Gracias... supongo.";
			link.l1.go = "exit";
		break;
		
		case "ShipLetters_Usurer2_2":
			dialog.text = "Es tu decisión. Nuestro comandante ha mostrado bastante 'interés' por esta persona, desde hace mucho tiempo. ¿Tienes alguna idea ya? Y aquí tenemos conocimientos de embarque sin marcas...";
			link.l1 = "Ya veo. ¡Le estoy agradecido!";
			link.l1.go = "exit";		
		break;
		
		case "ShipLetters_Usurer2_3":
			s1 = "Exactamente. Por cierto, nuestros contrabandistas le guardan rencor a ese capitán.";
			dialog.text = s1+"Y como mencioné antes, el dueño del papel es un hombre de principios, y realmente no le gustan los crímenes locales.";
			link.l1 = "Ya veo. ¡Gracias!";
			link.l1.go = "exit";		
		break;

		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "Ah, ¿supongo que eres el capitán que trajo a mi hijo pródigo con su joven esposa?";
				link.l1 = "Sí, fui yo quien les ayudó a escapar.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "Ah, aquí estás, mi benefactor. ¿Esperando una recompensa, supongo?";
				link.l1 = "Tu agradecimiento sería suficiente al menos...";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "Estoy realmente agradecido por ayudar a mi hijo y no dejarlo en esa situación problemática. Por favor, permíteme agradecerte de la mejor manera posible. Acepta esta modesta suma y un pequeño obsequio de mi parte.";
			link.l1 = "Mis agradecimientos. Fue un placer ayudar a esta joven pareja.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "¿Gracias? ¿Por qué? ¡Este cabezón estuvo desempleado la mitad del año y ya ha encontrado tiempo para conseguirse una chica! Yo manejaba mi propio negocio a su edad. ¡Hay una hija del gobernador en edad de casarse, y él trae a esta ramera aquí! ¡Señor, perdóname por decirlo! ¡¿Y ahora busca mi bendición?!";
			link.l1 = "¿Supongo que no crees en los sentimientos?";
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
			dialog.text = "¿Sentimientos? ¿Qué clase de sentimientos? ¿Eres un hombre adulto y también hablas de esos sentimientos? Qué vergüenza que seas un alcahuete para la juventud. Separaste a la chica de sus padres, y destruiste la vida de mi hijo. No recibirás ningún agradecimiento de mi parte. Adiós.";
			link.l1 = "Adiós, entonces...";
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
					dialog.text = "Hablemos de ello. Estoy escuchando.";
				}
				else
				{
					dialog.text = "Uh, uh. Me temo que debo rechazarle, "+GetAddress_Form(NPChar)+". Lo siento, pero mi banco no ofrece servicios a los enemigos de España.";
					link.l1 = "El dinero no tiene nacionalidad, señor banquero.";
					if (CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold"))
					{
						if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)) && makeint(Pchar.Quest.Deposits.(sDepositType1)) == true)
						{
							dialog.text = "Ajá, "+GetAddress_Form(NPChar)+". Debo informarle que su depósito ya no es válido.";
							Link.l1 = "¡¿En qué fundamentos?!";
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
			dialog.text = "Hablemos de eso. Estoy escuchando.";
			//кредиты
            if(CheckAttribute(Pchar, "Quest.Loans." + (NPC_Area)) && makeint(Pchar.Quest.Loans.(NPC_Area)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Loans.(NPC_Area).StartYear),makeint(Pchar.Quest.Loans.(NPC_Area).StartMonth),makeint(Pchar.Quest.Loans.(NPC_Area).StartDay), makefloat(Pchar.Quest.Loans.(NPC_Area).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				Pchar.Quest.Loans.(NPC_Area).Result = makeint(Pchar.Quest.Loans.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Loans.(NPC_Area).Sum)/100)*makeint(Pchar.Quest.Loans.(NPC_Area).Interest))*(iPastMonths+1);// boal 23.01.2004
				if(makeint(PChar.money) >= makeint(Pchar.Quest.Loans.(NPC_Area).Result))
				{
					Link.l5 = "Te debo "+FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).Result))+LinkRandPhrase(", estoy listo para devolver tu dinero",". Quiero saldar la deuda.",". Por fin, es hora de pagar.");
					Link.l5.go = "loan_return";	
					sTemp = "credit";
				}					
			}
			else
			{
				Link.l6 = LinkRandPhrase("Quiero pedir prestadas algunas monedas.","Realmente necesito conseguir algunos pesos.","¿Qué tal un pequeño préstamo?");
				Link.l6.go = "loan";					
				if(makeint(Pchar.money) >= 100)
				{
					Link.l7 = LinkRandPhrase("Me gustaría depositar mi dinero para obtener intereses.","¿Aceptarías guardar algunos sacos de dinero?","¿Puedo dejarte algo de dinero para un día desafortunado?"); // patch
					Link.l7.go = "deposit";				
				}			
				if(CheckUseDublons(NPChar))
				{
					Link.l8 = "Quiero depositar algunos doblones para obtener intereses.";
					Link.l8.go = "deposit_dub";				
				}
			}
			
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)) && makeint(Pchar.Quest.Deposits.(sDepositType1)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Deposits.(sDepositType1).StartYear),makeint(Pchar.Quest.Deposits.(sDepositType1).StartMonth),makeint(Pchar.Quest.Deposits.(sDepositType1).StartDay), makefloat(Pchar.Quest.Deposits.(sDepositType1).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)+ ".Rem"))
				{
					Pchar.Quest.Deposits.(sDepositType1).Result = makeint(Pchar.Quest.Deposits.(sDepositType1).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType1).Sum)/100)*makeint(Pchar.Quest.Deposits.(sDepositType1).Interest))*iPastMonths+sti(Pchar.Quest.Deposits.(sDepositType1).Rem);
				}
				else
				{
					Pchar.Quest.Deposits.(sDepositType1).Result = makeint(Pchar.Quest.Deposits.(sDepositType1).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType1).Sum)/100)*makeint(Pchar.Quest.Deposits.(sDepositType1).Interest))*iPastMonths;
				}
				Link.l9 = LinkRandPhrase("Estoy aquí para recuperar mi inversión, en pesos.","Es hora de recuperar el dinero que me debes.","Necesito recuperar mi inversión en pesos, con todos los intereses.");
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
				Link.l10 = LinkRandPhrase("Quiero recuperar mi inversión en doblones.","Es hora de recuperar el oro que me debes.","Necesito recuperar mi inversión en doblones, con todos los intereses.");
				Link.l10.go = "Deposit_return_dub";									
			}
/*			
			
*/			
			//выход
			if (sTemp == "credit")
			{
				link.l11 = "Recuerdo mi deuda, pero aún no estoy listo para pagar...";
				link.l11.go = "Loan_Remind";
			}
			else
			{
				link.l11 = "Error mío, no tengo asuntos financieros aquí. Adiós.";
				link.l11.go = "exit";
			}
		break;
		
		//============== кредиты ===============
		case "loan":
            if (sti(NPChar.nation) == PIRATE)
            {
                dialog.text = "No, no puedo ayudarte. Solo puedo aceptar inversiones en este lugar problemático. Puedes invertir pesos de plata o doblones de oro.";				
                if(makeint(Pchar.money) >= 100)
				{
	                Link.l1 = "Quiero invertir pesos. Hablemos sobre la suma.";
	                Link.l1.go = "deposit";
				}				
				if(CheckUseDublons(NPChar))
				{
					Link.l2 = "Quiero invertir doblones. Aclarémos la suma.";
					Link.l2.go = "deposit_dub";
				}
                Link.l3 = "No estoy interesado.";
				link.l3.go = "exit";
                break;
            }
			// проверка на проф пригодность -->
            if (isBadReputation(pchar, 42))
            {
                dialog.text = RandSwear()+"Tu nombre es "+GetFullName(pchar)+", ¿verdad? Tienes "+RandPhraseSimple("una mala reputación","una mala reputación")+", por lo que no tengo interés en hacer negocios contigo.";
				link.l1 = RandPhraseSimple("¿No puede un hombre cometer un error?",RandSwear()+"¡Lo que sea!");
				link.l1.go = "exit";
                break;
            }
            // проверка на проф пригодность <--
			Dialog.snd = "voice\Spanish\bank\Rostovschiki-27.wav";
			dialog.text = "Ah, siempre eres bienvenido. ¿Qué suma necesitas?";
			Link.l1 = "Uno pequeño.";
			Link.l1.go = "Small";
			Link.l2 = "Moderado.";
			Link.l2.go = "Medium";
			Link.l3 = "Tan grande como sea posible.";
			Link.l3.go = "Large";
		break;

		case "small":
			Pchar.Quest.Loans.(NPC_Area).Sum = 500*makeint(Pchar.rank);
			Dialog.snd = "voice\Spanish\bank\Rostovschiki-26.wav";
			dialog.text = "¡Excelente! Siempre es mucho más fácil tratar con sumas pequeñas, menos riesgo para ambas partes. Puedo ofrecerte "+FindRussianMoneyString(sti(Pchar.Quest.loans.(NPC_Area).sum))+"...";
			Link.l1 = "Trato hecho. ¿Qué hay de tus intereses?";
			Link.l1.go = "Interest";
			Link.l2 = "No me sirve. Cambiémoslo.";
			Link.l2.go = "Loan";
			Link.l3 = "Supongo que es mejor no endeudarme. Adiós.";
			Link.l3.go = "ExitDelLoan1";
			Pchar.Quest.Loans.(NPC_Area).Interest = 22 - makeint((GetSummonSkillFromName(pchar, "Commerce")+GetSummonSkillFromName(pchar, "Leadership"))/10);
		break;

		case "Medium":
			Pchar.Quest.Loans.(NPC_Area).Sum = 1500*makeint(Pchar.rank)+325*GetSummonSkillFromName(pchar,SKILL_COMMERCE);
			Dialog.snd = "voice\Spanish\bank\Rostovschiki-01.wav";
			dialog.text = "Sin problema. Espero que la suma de "+FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).sum))+" ayude a resolver tus problemas. Esta es una suma bastante sustancial.";
			Link.l1 = "Trato hecho. ¿Qué pasa con los intereses?";
			Link.l1.go = "Interest";
			Link.l2 = "No me sirve. Cambiémoslo.";
			Link.l2.go = "Loan";
			Link.l3 = "Supongo que es mejor mantenerse alejado de las deudas, por ahora. Adiós.";
			Link.l3.go = "ExitDelLoan1";
			Pchar.Quest.Loans.(NPC_Area).Interest = 27 - makeint((GetSummonSkillFromName(pchar, "Commerce")+GetSummonSkillFromName(pchar, "Leadership"))/10);
		break;

		case "Large":
			Pchar.Quest.Loans.(NPC_Area).Sum = 4000*makeint(Pchar.rank)+600*GetSummonSkillFromName(pchar,SKILL_COMMERCE);
			Dialog.snd = "voice\Spanish\bank\Rostovschiki-29.wav";
			dialog.text = "Bueno... es arriesgado. Está bien, estoy listo para concederte un préstamo por "+FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).sum))+". Espero que comprenda, capitán, esta es una suma realmente sustancial. Le pido que lo tome en serio.";
			Link.l1 = "Trato hecho. ¿Qué pasa con los intereses?";
			Link.l1.go = "Interest";
			Link.l2 = "No funcionará para mí. Cambiémoslo.";
			Link.l2.go = "Loan";
			Link.l3 = "Supongo que es mejor mantenerme alejado de las deudas. Adiós.";
			Link.l3.go = "ExitDelLoan1";
			Pchar.Quest.Loans.(NPC_Area).Interest = 37 - makeint((GetSummonSkillFromName(pchar, "Commerce")+GetSummonSkillFromName(pchar, "Leadership"))/10);
		break;

		case "Interest":
			//Pchar.Quest.Loans.(NPC_Area).Interest = 16 - makeint(Pchar.skill.commerce);
			// Rebbebion, добавил фикс отображения знака процента
			Dialog.snd = "voice\Spanish\bank\Rostovschiki-25.wav";
			dialog.text = Pchar.Quest.Loans.(NPC_Area).Interest+"%% por mes. No puedo ofrecerte mejores condiciones basándome en lo que sé de ti."; 
			Link.l1 = "Me parece bien. Hablemos del tiempo.";
			Link.l1.go = "Period";
			Link.l3 = "Supongo que es mejor mantenerme alejado de las deudas. Adiós.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Period":
			Pchar.Quest.Loans.(NPC_Area).Period = makeint(makeint(Pchar.reputation.nobility)/20) + 1;			
			Dialog.snd = "voice\Spanish\bank\Rostovschiki-23.wav";
			dialog.text = "Teniendo en cuenta mi información sobre usted, "+Pchar.name+", esperaré el retorno de este préstamo por "+FindRussianMonthString(sti(Pchar.Quest.Loans.(NPC_Area).Period))+". Después de eso tomaré ciertas medidas. Espero que entienda eso."; 
			Link.l1 = "Acepto gustosamente los términos... y las monedas.";
			Link.l1.go = "LoanGranted";
			Link.l3 = "Disculpe, pero no funcionará para mí. Adiós.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "LoanGranted":
			Dialog.snd = "voice\Spanish\bank\Rostovschiki-04.wav";
			dialog.text = "Sinceramente, estoy muy contento. Pero permíteme advertirte. He estado haciendo esto durante mucho tiempo, y sé cómo recuperar mis inversiones. Así que si alguna vez tienes alguna idea tonta, te sugiero que la dejes de lado.\nSin ofender, solo es una advertencia.";
			Link.l1 = "Mm... Bueno. Adiós.";
			Link.l1.go = "LoanGranted_exit";
		break;

		case "Loan_Remind":
			Dialog.snd = "voice\Spanish\bank\Rostovschiki-03.wav";
			dialog.text = "Es tu elección, capitán. El interés está creciendo, y no tienes tanto tiempo.";
			Link.l1 = "No te preocupes por ello. Nos vemos.";
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
			dialog.text = LinkRandPhrase("¡Maravilloso! Ven a mí cuando necesites monedas. Estaré a tu servicio en cualquier momento.","Mil gracias. Siempre es un placer tratar con un hombre que es capaz de saldar sus deudas a tiempo. A veces suceden cosas, y puedo entenderlo, ¿sabe?... pero prefiero que los problemas se resuelvan.","Oh, tenía razón al confiar en ti, "+GetAddress_Form(NPChar)+" ¡Espero que no sea la última vez que uses mis servicios! Tal vez incluso podamos hacer mejores tratos, ya que ahora sé que eres un hombre honesto.");
			Link.l1 = LinkRandPhrase("Quiero pedir prestado algo de dinero.","Realmente necesito conseguir algunos pesos.","¿Qué tal un pequeño préstamo?");
			Link.l1.go = "loan";			
			if(makeint(PChar.money) >= 100)
			{
				Link.l2 = LinkRandPhrase("Me gustaría invertir mi dinero.","¿Guardarás algún botín pirata?","¿Puedo dejarte algo de dinero para un día de mala suerte?");
				Link.l2.go = "deposit";				
			}		
			if(CheckUseDublons(NPChar))	
			{
				Link.l3 = "Quisiera invertir algunos doblones para obtener intereses";
				Link.l3.go = "deposit_dub";				
			}
			Link.l4 = "Adiós, "+NPchar.name+".";
			Link.l4.go = "ExitDelLoan1";
		break;

		case "deposit":
			dialog.text = LinkRandPhrase("¡Veo a un hombre sabio! ¿Qué suma le gustaría invertir?","Bien. Confía en mí, esta suma te esperará aquí con seguridad y con todos sus intereses.","Veo que sabes lo que realmente importa en esta vida. ¿Cuánto te gustaría invertir?");
			link.l1.edit = 3;
			link.l1 = "";	
			Link.l1.go = "result";
		break;
		
		case "result":
			Pchar.QuestTemp.Deposits.(sDepositType1).Interest = makeint((GetSummonSkillFromName(pchar, "Commerce")+GetSummonSkillFromName(pchar, "Leadership"))/10.0/4.0 + 0.66) + 1; 
			Pchar.QuestTemp.Deposits.(sDepositType1).Sum = dialogEditStrings[3];
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp <= 0)
			{
				dialog.text = "Con que bromeando, ¿eh?";
				link.l1 = "Ha sido error mío.";
				link.l1.go = "exit";
				break;
			}
			if (iTemp > sti(pchar.money))
			{
				dialog.text = "Hum, desafortunadamente no tienes tanto dinero. Seamos serios...";
				link.l1 = "Bien.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Está bien. Puedo ofrecerte... digamos..."+Pchar.QuestTemp.Deposits.(sDepositType1).Interest+" %. Por mes, por supuesto.";
			Link.l1 = "Bien, funciona para mí.";
			Link.l1.go = "Deposit_placed";
			Link.l2 = "Sería mejor cambiar la suma.";
			Link.l2.go = "Deposit";
			Link.l3 = "Parece que esto fue una mala idea... Adiós.";
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
			    dialog.text = "Perdóneme, capitán, pero esta suma es demasiado grande para mi banco colonial. No podré pagarle sus intereses. Y la falta de una guardia confiable... Espero que lo entienda. De todos modos, la suma máxima que puedo aceptar de usted es "+FindRussianMoneyString(MakeMoneyShow(sti(NPChar.UsurerDeposit)*1000,MONEY_SIGN,MONEY_DELIVER))+".";
				Link.l1 = "Lástima, tendré que buscar otro banquero entonces.";
				Link.l1.go = "Exit";
			}
			else
			{
				dialog.text = "Ahora puedes estar seguro de que ni la tormenta más fuerte te dejará sin una moneda.";
				Link.l1 = "De acuerdo. Nos vemos.";
				Link.l1.go = "Deposit_Exit";
			}
		break;
		
		case "Deposit_return":
			Dialog.snd = "voice\USDI\USDI034";
			dialog.text = "Teniendo en cuenta el interés prometido y el tiempo transcurrido, te debo "+FindRussianMoneyString(sti(Pchar.Quest.Deposits.(sDepositType1).Result))+"... ¿Estás seguro de que quieres tomar el dinero?";
			Link.l1 = "Absolutamente. Entrégamelo.";			
			Link.l1.go = "Deposit_return_1";		
			Link.l2 = "Quiero retirar parte de mi dinero.";			
			Link.l2.go = "Deposit_return_part";
			Link.l3 = "Ya veo. Lo dejaré contigo por un tiempo más. Que tengas un buen día.";			
			Link.l3.go = "Exit";		
		break;		
		
		case "Deposit_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)+ ".Rem"))
			{
				DeleteAttribute(Pchar,"Quest.Deposits." + (sDepositType1)+ ".Rem");
			}
			Pchar.Quest.Deposits.(sDepositType1).Interest = sti(Pchar.QuestTemp.Deposits.(sDepositType1).Interest);
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
			dialog.text = "¿Y cuánto?";
			link.l1.edit = 4;
			link.l1 = "";	
			Link.l1.go = "result_part";
		break;

		case "result_part":
			iTemp = sti(dialogEditStrings[4]);
			if (iTemp <= 0)
			{
				dialog.text = "¡Esa fue una broma tan estúpida, señor!";			
				link.l1 = "¡Maldita sea! Lo siento mucho... Cambiemos la suma.";	
				Link.l1.go = "Deposit_return_part";
				break;
			}
			if (iTemp > sti(Pchar.Quest.Deposits.(sDepositType1).Result))
			{
				dialog.text = "No tienes tanto dinero en tu cuenta.";			
				link.l1 = "¡Maldita sea! Mi error. Cambiemos la suma.";	
				Link.l1.go = "Deposit_return_part";
				break;
			}
			if (iTemp == sti(Pchar.Quest.Deposits.(sDepositType1).Result))
			{
				dialog.text = "¿Todo? Bien, como quieras. Aquí está todo el dinero.";			
				link.l1 = "¡Muchas gracias!";	
				Link.l1.go = "Deposit_return_all";
				break;
			}
			dialog.text = "Está bien. Tómalo. Aquí está tu dinero.";			
			link.l1 = "¡Gracias!";	
			Link.l1.go = "result_part_1";
		break;
		
		case "result_part_1":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			addMoneyToCharacter(Pchar, iTemp);
			iRes = sti(Pchar.Quest.Deposits.(sDepositType1).Result)-iTemp; //остаток на счете
			iPer = sti(Pchar.Quest.Deposits.(sDepositType1).Interest);
			iDep = sti(Pchar.Quest.Deposits.(sDepositType1).Sum); //стартовая сумма
			if (iRes <= sti(Pchar.Quest.Deposits.(sDepositType1).Sum)) // стало меньше начальной суммы
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
				Pchar.Quest.Deposits.(sDepositType1).Interest = iPer;
				Pchar.Quest.Deposits.(sDepositType1).Sum = iRes;
				Pchar.Quest.Deposits.(sDepositType1).Result = 0;
			}
			else // если остаток больше начальной суммы - проценты продолжаем считать с неё, а не с остатка, ибо нефиг, дельту приплюсуем к набежавшим процентам - банкир Jason :) 
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
				Pchar.Quest.Deposits.(sDepositType1).Interest = iPer;
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
			dialog.text = "Oh... Es tan difícil perderlo. Realmente me había acostumbrado a este dinero. Ven de nuevo de todos modos.";			
			Link.l1 = "Lo haré si lo necesito. Adiós.";			
			Link.l1.go = "Exit";
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
		break;
		
		//  ugeen -> вклады в дублонах	
		case "deposit_dub":
			dialog.text = LinkRandPhrase("¡Veo a un hombre sabio! ¿Qué suma le gustaría invertir?","Bien. Confía en mí, esta suma te esperará aquí a salvo y con todos tus intereses.","Veo que sabes lo que realmente importa en esta vida. ¿Cuánto te gustaría invertir?");
			link.l1.edit = 3;
			link.l1 = "";	
			Link.l1.go = "result_dub";
		break;
		
		case "result_dub":		
			iTotalDublonQty = GetCharacterItem(pchar,"gold_dublon") + CheckItemMyCabin("gold_dublon");		
			Pchar.QuestTemp.Deposits.(sDepositType2).Interest = makeint((GetSummonSkillFromName(pchar, "Commerce")+GetSummonSkillFromName(pchar, "Leadership"))/20.0/4.0 + 0.66) + 1; 
			Pchar.QuestTemp.Deposits.(sDepositType2).Sum = dialogEditStrings[3];
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp <= 0)
			{
				dialog.text = "Con que bromeando, ¿eh?";
				link.l1 = "Mm, ha sido mi error...";
				link.l1.go = "exit";
				break;
			}						
			if (iTemp > iTotalDublonQty)
			{
				dialog.text = "Hum, desafortunadamente no tienes tanto dinero. Seamos serios...";
				link.l1 = "Mm... bien.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Está bien. Puedo ofrecerte... digamos..."+Pchar.QuestTemp.Deposits.(sDepositType2).Interest+" %. Por mes, por supuesto.";
			Link.l1 = "Me funciona.";
			Link.l1.go = "Deposit_placed_dub";
			Link.l2 = "Mejor cambiaré la suma.";
			Link.l2.go = "Deposit_dub";
			Link.l3 = "Supongo que es mejor guardar mi oro. Adiós.";
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
			    dialog.text = "Perdóneme, capitán, pero esta suma es demasiado grande para mi banco colonial. No podré pagarle sus intereses. Y la falta de una guardia confiable... Espero que lo entienda. De todos modos, la suma máxima que puedo aceptar de usted es "+FindRussianDublonString(MakeMoneyShow(sti(NPChar.UsurerDeposit)*10,MONEY_SIGN,MONEY_DELIVER))+".";
				Link.l1 = "Lástima, tendré que encontrar otro banquero entonces.";
				Link.l1.go = "Exit";
			}
			else
			{
				dialog.text = "Ahora puedes estar seguro de que ni la tormenta más fuerte te dejará sin una moneda.";
				Link.l1 = "Bien. Adiós.";
				Link.l1.go = "Deposit_Exit_dub";
			}
		break;
		
		case "Deposit_return_dub":
			Dialog.snd = "voice\USDI\USDI034";
			dialog.text = "Teniendo en cuenta el interés prometido y el tiempo transcurrido, te debo "+FindRussianDublonString(sti(Pchar.Quest.Deposits.(sDepositType2).Result))+"... ¿Estás seguro de que quieres tomar el dinero?";
			Link.l1 = "Absolutamente. Dámelo.";			
			Link.l1.go = "Deposit_return_dub_1";		
			Link.l2 = "Quiero retirar parte de mi dinero.";			
			Link.l2.go = "Deposit_return_dub_part";
			Link.l3 = "Ya veo. Lo dejaré contigo por un tiempo más. Que tengas un buen día.";			
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
			dialog.text = "¿Y cuánto?";
			link.l1.edit = 4;
			link.l1 = "";	
			Link.l1.go = "result_dub_part";
		break;
		
		case "result_dub_part":
			iTemp = sti(dialogEditStrings[4]);
			if (iTemp <= 0)
			{
				dialog.text = "¡Qué broma tan estúpida, señor!";			
				link.l1 = "¡Maldita sea! Lo siento mucho... Cambiemos la suma...";	
				Link.l1.go = "Deposit_return_dub_part";
				break;
			}			
			if (iTemp > sti(Pchar.Quest.Deposits.(sDepositType2).Result))
			{
				dialog.text = "No tienes tanto oro en tu cuenta, señor.";			
				link.l1 = "¡Maldita sea! Mi error. Cambiemos la suma...";	
				Link.l1.go = "Deposit_return_dub_part";
				break;
			}			
			if (iTemp == sti(Pchar.Quest.Deposits.(sDepositType2).Result))
			{
				dialog.text = "¿Todo eso? Bien, como usted diga. Aquí está su dinero.";			
				link.l1 = "¡Gracias!";	
				Link.l1.go = "Deposit_return_dub_all";
				break;
			}
			dialog.text = "Está bien. Tómalo. Aquí está tu dinero.";			
			link.l1 = "¡Muchas gracias!";	
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
			dialog.text = "Oh... Es tan difícil perderlo. Realmente me había acostumbrado a este dinero. Vuelve de todos modos.";			
			Link.l1 = "Lo haré si lo necesito. Adiós.";			
			Link.l1.go = "Exit";
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
		break;
		//  ugeen <- вклады в дублонах	
		
		case "DeadMotherfucker":
			Dialog.TempNode = "DeadMotherFucker_1";
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "¿Sigues vivo? ¿Quizás quieras devolverme mi dinero? ¡Maldito seas! ¡He perdido tanto dinero que nunca podrías devolvérmelo! ¡Y no encontraré descanso hasta ver tu cuerpo sin vida!";
            Link.l1 = "Solo quiero resolver las cosas de manera pacífica.";
			Link.l1.go = "LoanRestore_1";
			Link.l2 = LinkRandPhrase("Muy bien, ¡veamos entonces! ¡Sepa que usted tampoco está protegido de la muerte!","¡¿Una amenaza?! Veamos entonces qué vas a hacer...","El dinero no es lo más importante en nuestra vida. No te aflijas demasiado por ello y mates a la gente. Vamos, te reto.");
			Link.l2.go = "ExitDelLoan2";
		break;

		case "DeadMotherFucker_1":			
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "¡Fuera! Ojalá nunca te vuelva a ver.";			
			Link.l1 = "...";			
			Link.l1.go = "ExitDelLoan2";
            Dialog.TempNode = "DeadMotherFucker_1";
		break;
		// boal обратимость факапства -->
		case "LoanRestore_1":
            iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Loans.(NPC_Area).StartYear),makeint(Pchar.Quest.Loans.(NPC_Area).StartMonth),makeint(Pchar.Quest.Loans.(NPC_Area).StartDay), makefloat(Pchar.Quest.Loans.(NPC_Area).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
			Pchar.Quest.Loans.(NPC_Area).Result = makeint(Pchar.Quest.Loans.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Loans.(NPC_Area).Sum)/100)*makeint(Pchar.Quest.Loans.(NPC_Area).Interest))*(iPastMonths+1);
			dialog.text = "¿De veras? ¿Y cuáles son tus preocupaciones?";
			Link.l1 = "Por hoy te debo "+FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).Result))+". Y te ofrezco este dinero.";
			Link.l1.go = "DeadMotherFucker_1";
            if (sti(Pchar.Money) >= 2*sti(Pchar.Quest.Loans.(NPC_Area).Result))
            {
    			Link.l2 = "Te ofrezco mi deuda para restablecer buenas relaciones contigo. El monto es de "+FindRussianMoneyString(2*sti(Pchar.Quest.Loans.(NPC_Area).Result))+".";
    			Link.l2.go = "LoanRestore_2";
			}
		break;
		
		case "LoanRestore_2":
			dialog.text = "¡Ahora estamos hablando! Después de todo, puedo hacer negocios contigo.";
			Link.l1 = "Gracias. No te defraudaré más.";
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
			dialog.Text = "¡Ah, vamos! Somos personas serias, tú y yo, somos mejores que esos idiotas que están listos para morir por un solo doblón, pero nunca intentan hacer dos doblones con él.\nEstoy buscando un hombre al que ofrecer un negocio serio. Un hombre valiente y activo, honesto y puntual, pero no agobiado con... eh... demasiada escrupulosidad respecto a dilemas morales. Y espero que tú seas el hombre que estoy buscando.";
			Link.l1 = "Dependerá del tipo de 'trato' que me ofrezcas.";
			Link.l1.go = "GiveTaskSlave_1";
		break;
			
		case "GiveTaskSlave_1":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity(npchar.city);
			dialog.Text = "Muy bien, escucha entonces. La esclavitud es el negocio más rentable en el Caribe hoy en día. No soy un esclavista, pero tengo clientes de confianza.\nPor lo tanto, necesito la siguiente cantidad de esclavos... "+pchar.questTemp.Slavetrader.iSlaveQuantity+" cabezas. Estoy dispuesto a pagarte 250 pesos por cada una. Créeme, es un buen precio. En total ganarás "+FindRussianMoneyString(sti(pchar.questTemp.Slavetrader.iSlaveMoney))+" pesos.";
			Link.l1 = "No, no soy un traficante de esclavos. Encuentra otro asistente que no se preocupe por su conciencia.";
			Link.l1.go = "exit_slaves";
			Link.l2 = "Una oferta tentadora. Me gustaría hacerlo. ¿Cuándo necesitarás a los esclavos?";
			Link.l2.go = "GiveTaskSlave_2";
		break;
			
		case "exit_slaves":
			dialog.Text = "Meh, parece que nadie está ansioso por mover su trasero y tomar el oro bajo sus pies. Estoy decepcionado, mucho. Adiós, y ni siquiera pienses en difundir chismes sobre nuestra conversación. Mi brazo tiene un largo alcance...";
			Link.l1 = "Tu alcance es 'sucio'... igual que tu lengua. Adiós.";
			Link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "End_quest";
			DeleteAttribute(npchar, "quest.slave");
		break;
			
		case "GiveTaskSlave_2":
			dialog.Text = "No limitaré tu tiempo, pero intenta cumplir con tu misión lo antes posible. La demanda de 'marfil negro' es enorme. Si haces bien tu trabajo, entonces te estaré dando este tipo de trabajos de vez en cuando en el futuro.";
			Link.l1 = "Suena bien. Bueno, espera las buenas noticias.";
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
			dialog.Text = "¿Has logrado conseguir ese cargamento de 'marfil negro'?";
            if (amount < 0)
			{
				Link.l1 = "Todavía no. Solo verificando si nuestro acuerdo sigue vigente.";
            	Link.l1.go = "exit";
			}
			else
			{
				Link.l1 = "Todo listo. Todos están en mi bodega.";
            	Link.l1.go = "Takeslaves";
			}
		break;
		
		case "Takeslaves":
			amount = sti(pchar.questTemp.Slavetrader.iSlaveQuantity);
			dialog.Text = "Espléndido. Mis hombres los llevarán... No te preocupes por la aduana o el comandante del fuerte. Estoy llevando a cabo una operación enorme aquí, así que no esperes problemas, y nadie te acusará de contrabando.";
			Link.l1 = "Parece que tienes una posición fuerte aquí... ¿Qué tal mi pago?";
            Link.l1.go = "Takeslaves_1";
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, amount);
		break;
		
		case "Takeslaves_1":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			dialog.Text = "Aquí está. No hablo por hablar. Quédate conmigo, capitán, y pronto poseerás tanto oro que necesitarás un galeón para moverlo.";
			Link.l1 = "Eso sería genial, ja-ja... ¿Qué es lo que sigue?";
            Link.l1.go = "Takeslaves_2";
		break;
		
		case "Takeslaves_2":
			dialog.Text = "¿Lo que sigue? Vuelve aquí en tres semanas. Estoy preparando un trato ahora mismo y debería estar listo para entonces.";
			Link.l1 = "Muy bien, trato hecho. Adiós.";
            Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "2");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.questTemp.Slavetrader = "wait";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait");//запомнить дату
		break;
		
		case "Takeslaves_3":
			if (4-sti(RealShips[sti(pchar.ship.type)].Class) < 0)//проверка класса корабля
			{
				dialog.Text = "Tengo un trabajo, pero tu barco no tiene las capacidades. No quiero que fracases en la misión y tampoco quiero enviarte a una muerte segura. Todavía hay tiempo, así que consíguete un barco más grande, como un bergantín o al menos un filibote. ¡No pierdas el tiempo!";
				Link.l1 = "Entiendo, me encargaré de ello. Nos vemos.";
            	Link.l1.go = "Takeslaves_3_smallship";
			}
			else
			{
				dialog.Text = "¡Por fin! Te estaba esperando. Ahora vayamos directo al grano. Como sabes, siempre hay competidores en cualquier negocio... y yo tengo los míos. ¡Estos miserables codiciosos y sin escrúpulos siempre están ansiosos por quitarme un cliente! En realidad, quiero eliminar a uno de ellos, y al mismo tiempo hacer una buena moneda.";
				Link.l1 = "Soy todo oídos.";
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
			dialog.text = "Excelente. Ahora escucha. Este bribón se llama "+GetName(NAMETYPE_ORIG,pchar.questTemp.Slavetrader.UnknownPirateName,NAME_NOM)+". Ha traído esclavos de África y echado anclas en "+XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore+"Gen")+". Está en una isla llamada "+XI_ConvertString(pchar.questTemp.Slavetrader.Island)+". Allí espera a los contrabandistas. Su galeón se llama '"+pchar.questTemp.Slavetrader.ShipName+"'. ¡Su trato debe romperse a cualquier costo!";
			link.l1 = "¿Y qué hay de los esclavos? ¡Sería un desperdicio hundirlos!";
			link.l1.go = "Takeslaves_5";
		break;
		
		case "Takeslaves_5":
			dialog.Text = "¿Por qué harías eso? No hay necesidad de eso. "+GetName(NAMETYPE_ORIG,pchar.questTemp.Slavetrader.UnknownPirateName,NAME_NOM)+" tiene mala reputación y nadie se molestará por su desaparición. Aborda su galeón, mata al hombre y asegúrate de que permanezca muerto. Tráeme la carga y la venderé. Según mis fuentes, hay alrededor de mil quinientos esclavos.";
			Link.l1 = "Vaya. Esa es una cifra considerable. ¿Qué hay de mi pago?";
            Link.l1.go = "Takeslaves_6";
			Link.l2 = "No, señor. Estas intrigas no son para mí. ¿Por qué debería estropear mis relaciones con los contrabandistas?";
            Link.l2.go = "exit_slaves_1";
		break;
		
		case "exit_slaves_1":
			dialog.Text = "Bueno... Parece que me equivoqué contigo... Adiós y olvídate de nuestra charla. Y no divulges chismes sobre lo que has escuchado aquí. Yo soy el dueño de este pueblo. Y si planeas abordar el '"+pchar.questTemp.Slavetrader.ShipName+" para ti mismo... Me aseguraré de que termines en la horca. Considéralo.";
			Link.l1 = "No te preocupes, no informaré a las autoridades y no necesito tu galeón. Adiós.";
            Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase(" agreed"," agreed"));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";//конец квеста
		break;
		
		case "Takeslaves_6":
			dialog.Text = "Teniendo en cuenta que te he dado la ubicación del cargamento, y que no necesitas navegar en busca de 'un premio', el pago es un poco más bajo: 200 pesos por cabeza. Y aun así, es una gran suma: trescientos mil pesos en caso de éxito y el barco.";
			Link.l1 = "Trato hecho. ¿De cuánto tiempo dispongo?";
            Link.l1.go = "Takeslaves_7";
			Link.l2 = "¡Ja-ja! ¡Dices eso como si esos esclavos nadaran solos hacia mi barco esperando entrar en mi bodega lo antes posible! ¿De verdad quieres que mi gente arriesgue sus cabezas por una suma tan pequeña? Aumenta mi recompensa o me salgo del negocio.";
            Link.l2.go = "exit_slaves_1";
		break;
		
		case "Takeslaves_7":
			dialog.text = "Tienes dos semanas. No llegues tarde o él transferirá su cargamento y todo habrá terminado.";
			link.l1 = "Tengo que darme prisa entonces. Espérame con las buenas noticias.";
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
			dialog.text = "Bueno, "+GetFullName(pchar)+", ¿qué hay de nuestra misión? Tu cara sombría me dice que has fallado.";
			link.l1 = "Maldita sea, tienes razón... Yo... bueno, ya sabes... Llegué tarde. Parecía que ya se había ido del lugar, porque no encontré a nadie allí. Tuve que navegar todo el camino con el viento, maldita sea... ";
			link.l1.go = "Takeslaves_5_lose";
		break;
		
		case "Takeslaves_4_win":
			dialog.text = "Bueno, "+GetFullName(pchar)+", ¿cuál es tu captura de hoy? ¡Me dijeron que "+GetName(NAMETYPE_ORIG,pchar.questTemp.Slavetrader.UnknownPirateName,NAME_NOM)+" alimenta a los peces! ¡Ja-ja-ja!";
			link.l1 = "¡Sí, llegué justo a tiempo! "+GetName(NAMETYPE_ORIG,pchar.questTemp.Slavetrader.UnknownPirateName,NAME_NOM)+" estaba transfiriendo esclavos al barco del contrabandista. Tuve que abordarlos a ambos y enviarlos con el mismo Davy Jones, así que ahora tienes menos competidores.";
			link.l1.go = "Takeslaves_5_win";
		break;
		
		case "Takeslaves_5_lose":
			dialog.text = "Sí, supongo que me equivoqué contigo. ¿Llegaste tarde? ¿O simplemente tenías demasiado miedo para pelear? Lo que sea. No tiene sentido ahora. Piérdete. He terminado contigo. Olvida todo lo que viste o escuchaste aquí.";
			link.l1 = "Entonces, adiós.";
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
				dialog.text = "Tenía razón sobre ti, "+GetSexPhrase("eres un bribón apuesto","eres una fiera Doncella")+". ¡Necesito hombres como tú! Has cumplido tu misión de la manera más excelente: ¡has traído más de mil quinientos esclavos! Desafortunadamente, solo puedo pagarte por mil seiscientos esclavos. No tengo suficiente dinero para pagarte por el resto, así que tendrás que venderlos tú mismo. Tu recompensa es de 320.000 pesos.";
				link.l1 = "Gracias. ¡Un placer hacer negocios contigo, "+npchar.name+"!";
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
				dialog.text = "Tenía razón sobre ti, "+GetSexPhrase("eres un bribón atrevido","eres una fiera Doncella")+". ¡Necesito hombres como tú! Has cumplido tu misión de la manera más excelente: me has traído "+sTemp+" esclavos. Tu recompensa es "+FindRussianMoneyString(iSlaveMoney)+".";
				link.l1 = "Gracias. ¡Un placer hacer negocios contigo, "+npchar.name+"!";
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
				dialog.text = "Al menos has sobrevivido a la situación más difícil con todo el honor. Aunque el premio es menor de lo que esperaba, aún estoy satisfecho. Has traído "+sTemp+" esclavos. Tu recompensa es de "+FindRussianMoneyString(iSlaveMoney)+".";
				link.l1 = "Gracias. ¡Un placer hacer negocios contigo, "+npchar.name+"!";
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
				dialog.text = "Ya veo... Puedo entender eso, pero esperaba mucho más. Solo has traído "+sTemp+" esclavos. Al menos has destruido a mis competidores y eso vale algo. Tu recompensa es de "+FindRussianMoneyString(iSlaveMoney)+".";
				link.l1 = "Estoy agradecido. ¡Aprecio su comprensión, "+npchar.name+"!";
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
				dialog.text = "Suena genial pero... hmmm. Parece que me equivoqué contigo. ¿Qué has traído? ¿"+sTemp+" esclavos? ¿Y qué hay del resto? Y no me digas que los has hundido. Estoy seguro de que los has vendido a contrabandistas, o incluso peor, a ese bastardo de Lavoisier. ¡Lárgate, no quiero tener más negocios contigo!";
				link.l1 = "Como desees, adiós.";
				link.l1.go = "node_hanter_1";
				break;
			}
			dialog.text = "Suena genial, pero... ¿dónde están nuestros esclavos? ¿Dónde está nuestra carga? Y no me digas que lo has hundido. Debes haberlo vendido a los contrabandistas o peor, a ese bastardo de Lavoisier. Piérdete, he terminado contigo.";
			link.l1 = "Como desees, adiós.";
			link.l1.go = "node_hanter_1";
		break;
		
		case "node_hanter_1":
			dialog.text = "Esto no ha terminado. ¡Nadie se atreve a engañarme! Y pagarás por tu intento. Me aseguraré de que tengas problemas. ¡Ahora sal de aquí!";
			link.l1 = "¡Que te jodan a ti y a tu comercio de esclavos! Debería cortarte justo donde estás, pero soy un hombre mejor de lo que tú jamás serás.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 30);
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Takeslaves_6_win":
			dialog.text = "Parece que estamos trabajando bien juntos, "+pchar.name+" . Me alegra mucho. Ven a verme en un mes y, tal vez, encontraré un trabajo solo para ti. Ya tengo algunas ideas.";
			link.l1 = "Claro, te veré en un mes. Mi trabajo contigo es muy lucrativo.";
			link.l1.go = "Takeslaves_7_win";
		break;
			
		case "Takeslaves_7_win":
			dialog.text = "La fortuna llegará a ti... Una última pregunta, "+pchar.name+", ¿has encontrado algo inusual en el camarote del galeón?";
			link.l1 = "Realmente nada especial... ¿Me perdí de algo?";
			link.l1.go = "Nostatue";
			if (CheckCharacterItem(pchar, "talisman8"))
			{
				link.l2 = "¿Te refieres a esta vieja hebilla? Algún amuleto de 'escorpión'...";
				link.l2.go = "Yestatue";
			}
		break;
			
		case "Nostatue":
			dialog.text = "Quizás lo hiciste, y quizás no ... No importa ahora. Nos vemos en un mes. ¡Adiós!";
			link.l1 = "Nos vemos, "+npchar.name+".";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Yestatue":
			dialog.text = "¡Exactamente! Este es un talismán de los Medici... ¿has oído hablar de ellas? Eso significa que realmente estaba en la cabina del bastardo... ¿Puedo echarle un vistazo?";
			link.l1 = "Claro, aquí tienes.";
			link.l1.go = "Yestatue_1";
			RemoveItems(PChar, "talisman8", 1);
		break;
			
		case "Yestatue_1":
			Log_Info("Has entregado un talismán");
			PlaySound("interface\important_item.wav");
			dialog.text = "Vaya-vaya... Así es. Escucha, "+pchar.name+", véndemelo. Estoy dispuesto a pagar cien mil pesos.";
			link.l1 = "¿Cien mil? Hm.. Estoy de acuerdo. ¡Ahí tienes!";
			link.l1.go = "Buystatue";
			link.l2 = "No, no lo venderé. El verdadero valor de este talismán no puede ser tasado en plata o en oro. Sé cómo funcionan estas cosas.";
			link.l2.go = "Nobuystatue";
		break;
			
		case "Buystatue":
			dialog.text = "¡Perfecto! Me alegra que hayamos llegado a un acuerdo. Toma tu dinero. Espero verte en un mes.";
			link.l1 = "Adiós, "+npchar.name+".";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 100000);
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Nobuystatue":
			dialog.text = "Verás, ¡necesito desesperadamente este talismán! Estoy completamente de acuerdo contigo, no se puede valorar con dinero, cualquier vendedor tonto ni siquiera te pagará cinco mil por ella. Pero parece que realmente sabes lo que puede hacer, ya que te niegas a venderla por tal suma.\n¿Puedo ofrecerte un intercambio, si no quieres dinero? Tengo algo que podría interesarte. Aquí, echa un vistazo. ¡Una asombrosa armadura ligera! ¡Mírala por ti mismo! Te la ofrezco a cambio del talismán.\nPor cierto, no es única. Ustedes, los marineros, siempre pueden encontrar más para ustedes y yo no puedo. ¿Estás de acuerdo ahora?";
			link.l1 = "Heh... Supongo. Dame la armadura y toma este talismán.";
			link.l1.go = "Nobuystatue_yes";
			link.l2 = "No, este talismán tiene un valor mucho mayor para mí que esta armadura. Me la quedaré para mí.";
			link.l2.go = "Nobuystatue_no";
		break;
			
		case "Nobuystatue_yes":
			dialog.text = "¡Espléndido! Me alegra que tengamos un trato. Esta es tu armadura ahora. Tómala. Nos vemos en un mes. Adiós.";
			link.l1 = "Nos vemos, "+npchar.name+".";
			link.l1.go = "exit";
			TakeNItems(pchar, "cirass7", 1);
			Log_Info("Has recibido una Brigandine");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Nobuystatue_no":
			dialog.text = "Qué lástima... Muy mal. Bueno, ten esto. No te juzgo. Nos vemos en un mes. Adiós.";
			link.l1 = "Adiós.";
			link.l1.go = "exit";
			TakeNItems(pchar, "talisman8", 1);
			Log_Info("Has recibido un talismán");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "EscapeSlave":
			dialog.text = "Has llegado justo a tiempo, "+pchar.name+". Tengo una misión para ti si estás listo para comenzarla.";
			link.l1 = "Claro, estoy listo.";
			link.l1.go = "EscapeSlave_1";
		break;
			
		case "EscapeSlave_1":
			dialog.text = "¡Excelente! Ahora, al grano. ¿Has oído las últimas noticias?";
			link.l1 = "Mm, ¿qué quieres decir? Hay muchas noticias llegando cada día.";
			link.l1.go = "EscapeSlave_2";
		break;
			
		case "EscapeSlave_2":
			dialog.text = "Este trata sobre nuestro negocio. ¡Hubo la mayor fuga de esclavos en la historia del Nuevo Mundo! Más de mil almas han escapado y, mientras tanto, han destruido y quemado algunos puestos avanzados holandeses.";
			link.l1 = "Intrigante. Continúa.";
			link.l1.go = "EscapeSlave_3";
		break;
			
		case "EscapeSlave_3":
			dialog.text = "¡Pero no solo huyeron, de alguna manera lograron salir de la isla! No dejaron rastros. Mathias Beck está indignado. Pero ese no es el punto... El punto es que te pido que navegues hacia Curazao, averigües qué sucedió allí, encuentres a los refugiados y los captures.\nY, por supuesto, que los salves de las manos de la justicia holandesa, que sería despiadada con ellos. Pagaré 300 pesos por cabeza, he oído que son muy buenos esclavos.";
			link.l1 = "Entendido. Me dirijo a Curazao. Espérame con las buenas noticias.";
			link.l1.go = "EscapeSlave_yes";
			link.l2 = "Sabes, no aceptaré la misión. No privaré a la gente de su libertad. Han arriesgado sus vidas para conseguirla. Se la han ganado.";
			link.l2.go = "EscapeSlave_no";
		break;
			
		case "EscapeSlave_no":
			dialog.text = "Qué lástima... No esperaba eso de ti... y en el momento más inoportuno. Supongo que te queda claro que nuestra asociación ha terminado. Adiós.";
			link.l1 = "Que tengas un buen día.";
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
				dialog.text = "¡Ja! No sólo has cumplido con tu difícil misión, sino que has traído más esclavos de los que he solicitado... "+sTemp+" esclavos. Pero "+sNum+" los esclavos no escaparon de Curazao. Te pago 100 pesos por cabeza. Supongo que eso te servirá. Tu recompensa es de 330.000 pesos y "+FindRussianMoneyString(iSlaveMoneyH)+" por un exceso, ja-ja.";
				link.l1 = "¡Ja! Definitivamente no se te puede engañar. Estoy de acuerdo, ¡lo que digas, "+npchar.name+"!";
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
				dialog.text = "Has terminado esa difícil misión de la manera más excelente, y me has traído "+sTemp+" esclavos. Tu recompensa es de "+FindRussianMoneyString(iSlaveMoney)+".";
				link.l1 = "Gracias. ¡Un placer hacer negocios contigo, "+npchar.name+"!";
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
				dialog.text = "Has tenido éxito en esa difícil misión. El premio no es tan rico como esperaba, pero estoy satisfecho de todos modos. Así que has traído aquí "+sTemp+" esclavos. Tu recompensa es "+FindRussianMoneyString(iSlaveMoney)+".";
				link.l1 = "Gracias. ¡Un placer hacer negocios contigo, "+npchar.name+"!";
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
				dialog.text = "¿Los has encontrado? Hm... ¿qué me has traído? ¿"+sTemp+" esclavos? ¿Dónde está el resto de la carga? Y ni siquiera intentes decirme que la has hundido. Debes haberla vendido a contrabandistas, o peor aún, a ese bastardo Lavoisier de Isla-Tesoro. Aléjate de aquí, no tengo deseo de trabajar contigo nunca más.";
				link.l1 = "Adiós.";
				link.l1.go = "node_hanter_1";
				break;
			}
			dialog.text = "¿Los encontraste? ¿Qué hay de los esclavos? ¿Dónde está nuestra carga? Y ni se te ocurra decirme que la hundiste. Debes haberla vendido a contrabandistas, o peor aún, a ese bastardo Lavoisier de Isla-Tesoro. Lárgate de aquí, no tengo deseos de trabajar contigo nunca más.";
			link.l1 = "Adiós.";
			link.l1.go = "node_hanter_1";
		break;
		
		case "Escape_slaves_win_1":
			dialog.text = "Realmente te aprecio, "+pchar.name+", de verdad. Vuelve aquí en un mes y prepararé un nuevo negocio, rentable para ambos.";
			link.l1 = "También estoy satisfecho con nuestra asociación, "+npchar.name+". Nos vemos en un mes.";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_2");
			pchar.questTemp.Slavetrader = "wait_2";
		break;
			
		case "Slaveshore":
			dialog.text = "Eres muy oportuno, "+pchar.name+" . Estoy buscando un marinero valiente y poco escrupuloso, ja-ja. ¿Estás listo para encargarte de mi trabajo?";
			link.l1 = "Soy todo oídos.";
			link.l1.go = "Slaveshore_1";
		break;
			
		case "Slaveshore_1":
			pchar.questTemp.Slavetrader.Island = Islands[GetCharacterCurrentIsland(pchar)].id;
			pchar.questTemp.Slavetrader.Island.Shore = GetIslandRandomShoreId(pchar.questTemp.Slavetrader.Island);
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.questTemp.Slavetrader.Nation = NPChar.nation;
			dialog.text = "Es bastante sencillo esta vez. Hoy, una pinaza '"+pchar.questTemp.Slavetrader.ShipName+" bajo la bandera de "+NationNameGenitive(sti(npchar.nation))+" ha echado el ancla en "+XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore+"Gen")+" bahía. Estaba cargado con un gran lote de 'ébano' con la ayuda de los contrabandistas locales. Dos mil cabezas, no menos.\nNo hay soldados en la tripulación y el capitán es un comerciante. En general, ninguna amenaza en absoluto. Aborda el barco y tráeme la carga. 200 pesos por cabeza como de costumbre.";
			link.l1 = "Mm... No es lo mismo que el último trabajo. ¡Me sugieres atacar un barco de tu propia nación!";
			link.l1.go = "Slaveshore_2";
		break;
			
		case "Slaveshore_2":
			dialog.text = "No lo entiendo, "+pchar.name+". ¿Acaso importa el pabellón del barco? ¿Realmente te importa eso?";
			link.l1 = "¿Qué? No, me importa un carajo, el oro no tiene nacionalidad. Solo fue un poco inesperado...";
			link.l1.go = "Slaveshore_3_yes";
			link.l2 = "Me importa. No quiero tener a "+NationNameAblative(sti(npchar.nation))+" entre mis enemigos.";
			link.l2.go = "Slaveshore_3_no";
		break;
			
		case "Slaveshore_3_no":
			dialog.text = "¿Hablas en serio? Debes estar bromeando, no se puede confiar en nadie estos días... En ese caso, aléjate. ¡Y olvídate de todo lo que viste o escuchaste aquí!";
			link.l1 = "Nos vemos, "+npchar.name+".";
			link.l1.go = "node_hanter_1";
		break;
			
		case "Slaveshore_3_yes":
			dialog.text = "¿Por qué te sorprende? ¿Por qué me debería importar la nacionalidad de las monedas? Te aseguro que, en efecto, no me importa. Para ser honesto, el patriotismo es malo para un banquero profesional, a menos que esté ansioso por arruinarse algún día.\nPero basta de filosofía. Vamos al grano: el barco se quedará aquí hasta la medianoche, así que no te queda mucho tiempo. ¿Estás listo para proceder?";
			link.l1 = "Sí, "+npchar.name+", estoy en camino.";
			link.l1.go = "Slaveshore_4";
		break;
			
		case "Slaveshore_4":
			dialog.text = "Espléndido. No tengo duda de que tendrás éxito en nuestra misión. Buena suerte, "+pchar.name+".";
			link.l1 = "¡Gracias! Adiós.";
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
		dialog.text = "Bueno, "+GetFullName(pchar)+", ¿qué hay de tu misión? Tu cara triste me dice que has fallado.";
			link.l1 = "Tienes toda la maldita razón... Yo... Bueno... Llegué demasiado tarde. Estaba en la taberna y cuando zarpé, no había nadie en el mar.";
			link.l1.go = "Takeslaves_5_lose";
		break;
			
		case "Slaveshore_5":
			dialog.text = ""+pchar.name+", por favor, cálmate. ¡No es mi culpa! Maldita sea, he recibido el informe demasiado tarde... ¡Hubo una traición! ¡Uno de mis hombres de confianza me ha vendido!";
			link.l1 = "Está bien, veo que dices la verdad. Tienes suerte de que el capitán de la pinaza me haya dicho que nuestro 'negocio' fue descubierto. Ya te habría matado si no lo hubiera soltado. ¡Pero tú, maldito saco de dinero, me estabas diciendo todo el tiempo que 'este pueblo es tuyo'!";
			link.l1.go = "Slaveshore_6";
		break;
			
		case "Slaveshore_6":
			dialog.text = "La emboscada no fue organizada por las autoridades locales, de lo contrario, yo lo habría sabido... "+pchar.name+", no es el momento adecuado para peleas. Ambos estamos en peligro, uno de mis antiguos contratistas nos ha tendido una trampa.\nLogré averiguar que todas las pruebas reunidas, un paquete de documentos, están siendo transportadas a nuestro gobernador general. ¡Si las consigue, estamos acabados! Tú sufrirás más, por cierto.";
			link.l1 = "¡Ahora veo lo que quiso decir ese maldito capitán!";
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
			dialog.text = "Escucha con atención. Todavía tenemos una oportunidad. El paquete fue enviado en el bergantín '"+pchar.questTemp.Slavetraderbrig.ShipName+"'. Eso es lo único de lo que estoy seguro. Los papeles serán entregados al gobernador general en su residencia en "+XI_ConvertString(pchar.questTemp.Slavetraderbrig.Island)+". Debes interceptarlo, abordarlo y encontrar esas pruebas descalificadoras.";
			link.l1 = "No tengo muchas opciones aquí. Reza por mí, por ti mismo y espera que pueda atraparlo. Hablaremos de todo esto de nuevo cuando regrese. No pienses que simplemente lo dejaré pasar.";
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
			dialog.text = "¡Obtener este paquete es tu máxima prioridad! No estaré seguro de mi integridad hasta que me lo entregues... Maldita sea... "+pchar.name+", parece que tenemos un problema aquí...";
			link.l1 = "¿De qué se trata?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Slavetrader_enterSoldiers");
			break;
			
		case "Brig_lose":
			dialog.text = "Maldición... Contaba contigo, "+pchar.name+". Está bien, entonces. Pero no haremos más negocios. Si no puedo sobornar a un investigador, tendré que huir. Y no te recomiendo quedarte aquí, los soldados pueden venir en cualquier momento. Adiós.";
			link.l1 = "Adiós, "+npchar.name+".";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Letter_lose":
			dialog.text = "Ellos estaban allí. Bueno, no podemos hacer negocios juntos, ya no es seguro. Adiós.";
			link.l1 = "Adiós, "+npchar.name+".";
			link.l1.go = "exit";
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Brig_win":
			dialog.text = "¡Excelente! No tenía dudas sobre ti, "+pchar.name+". Por favor, dame esos papeles, estoy demasiado nervioso.";
			link.l1 = "Tómalos.";
			link.l1.go = "Brig_win_1";
		break;
			
		case "Brig_win_1":
			RemoveItems(PChar, "letter_1", 1);
			dialog.text = "Bien... Ahora estoy a salvo. El gobernador general no sabrá nada y ya he resuelto todos los problemas con las autoridades locales, pero fue caro, te lo aseguro.";
			link.l1 = "Suena genial, pero ¿no crees que deberías compensarme por mis problemas debido a tus acciones irreflexivas?";
			link.l1.go = "Brig_win_2";
		break;
			
		case "Brig_win_2":
			dialog.text = "Claro, "+pchar.name+". Es más, te debo mucho. Y realmente espero continuar con nuestro negocio. Pero te pido que me entiendas: he gastado una suma enorme. La lealtad del gobernador y del comandante cuesta mucho. Y tuve que lidiar con ese asesinato de toda la patrulla en mi banco...";
			link.l1 = "¡¿Quieres decir que no compensarás mis costos?!";
			link.l1.go = "Brig_win_3";
		break;
			
		case "Brig_win_3":
			dialog.text = "No seas tan duro, "+pchar.name+". Realmente tengo problemas con el dinero ahora mismo, así que te ofrezco un tipo de pago diferente.";
			link.l1 = "Te escucho entonces.";
			link.l1.go = "Brig_win_4";
		break;
			
		case "Brig_win_4":
			dialog.text = "Mi compañero y yo fuimos atrapados por una tormenta cerca de las costas del sur del Continente hace un año. Nuestros barcos fueron lanzados contra las rocas de la costa de Boca de la Serpiente, aunque se hundieron pronto, logramos arrastrar nuestra carga a la orilla. Cofres llenos de piedras preciosas y joyas. La bahía parecía bastante acogedora, así que escondimos los tesoros sin problema.\nPero fuimos atacados por los indios a la mañana siguiente en cuanto la tormenta terminó. Así fue como murió la mayoría de los sobrevivientes, incluido mi compañero. Yo y unos pocos marineros logramos escapar en un bote.\nLlegamos sanos y salvos a Cumaná, pero no me atreví a regresar por los tesoros. Estoy seguro de que los salvajes locales todavía están protegiendo su costa así como mis cofres. Pero tú puedes lidiar con ese grupo de pieles rojas.\nLas joyas que encontrarás allí son suficientes para cubrir todos tus gastos, incluida una expedición al sur del Continente.";
			link.l1 = "Mm... bien. Entonces me dirijo a Cumaná";
			link.l1.go = "Brig_win_5";
		break;
			
		case "Brig_win_5":
			dialog.text = "Puedes estar seguro, "+pchar.name+", que todo lo que he dicho era verdad. Espero verte en un mes. Ya tengo en mente otro trato, y cómo debería ayudar a mi tambaleante negocio. Adiós.";
			link.l1 = "Nos vemos, "+npchar.name+".";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_3");
			pchar.questTemp.Slavetrader = "wait_3";
			Pchar.quest.Slavetrader_Bonanza.win_condition.l1 = "location";
            Pchar.quest.Slavetrader_Bonanza.win_condition.l1.location = "Shore18";
            Pchar.quest.Slavetrader_Bonanza.function = "Slavetrader_Bonanza";
		break;
			
		case "SlaveGalleon":
			dialog.text = "Y aquí estás, "+pchar.name+".  Bueno, llegas justo a tiempo como siempre. Me gustaría darte más información sobre el mercado de esclavos del Caribe antes de darte la próxima misión. ¿Sabes qué significa la palabra 'repartimiento'?";
			link.l1 = "Hm, no, "+npchar.name+", no. Pero supongo que se trata de quitarle algo a alguien. ¿Tengo razón?";
			link.l1.go = "SlaveGalleon_1";
		break;
			
		case "SlaveGalleon_end":
			dialog.text = "Me sorprendes. ¿Qué esperabas de mí? ¡Vete!";
			link.l1 = "Un negocio ilegal es demasiado duro para mi moral. Especialmente el comercio de esclavos.";
			link.l1.go = "node_hanter_1";
		break;
			
		case "SlaveGalleon_1":
			dialog.text = "Casi aciertas,"+pchar.name+". Quitarle la libertad a alguien. El repartimiento es una forma complicada y legal de esclavizar a los indios locales. Por así decirlo. Las autoridades españolas lo utilizan contra los nativos del continente. ¿Te interesa saber más?";
			link.l1 = "¿Por qué no?";
			link.l1.go = "SlaveGalleon_2";
		break;
			
		case "SlaveGalleon_2":
			dialog.text = "Representantes de la corona española visitan los asentamientos indios. Usando engaños cínicos y amenazas directas, obligan a los indios a comprar toda clase de basura como carne podrida y viejas navajas a precios fabulosos. A crédito.\nAlgún tiempo después, digamos un año, los representantes regresan y exigen un pago. Si los indios no pueden pagar, que es lo que suele suceder, los españoles se llevan a algunos de sus hombres capaces de trabajar, supuestamente por un tiempo, y para 'enseñarles a cultivar la tierra'.\nComo comprenderás, nunca regresan a sus asentamientos. Así es como nuestros confiados pieles rojas terminan en las plantaciones de azúcar y fábricas de caoba.";
			link.l1 = "Maldición... de verdad... ¿Qué hacen los indios al respecto? ¿Resisten cuando los españoles los esclavizan? ¿O simplemente no entienden lo que está pasando?";
			link.l1.go = "SlaveGalleon_3";
		break;
			
		case "SlaveGalleon_3":
			dialog.text = "Supongo que siempre lo ven venir, pero solo unos pocos se atreven a oponerse abiertamente, especialmente cuando los españoles muestran un papel con la huella del cacique. Claro, tales tácticas normalmente se aplican a las tribus pacíficas como los arawaks o miskitos. Tal truco no funcionará con los belicosos itza o akawoys.\nBien, hablemos de tu misión.";
			link.l1 = "¡Ya siento el olor de muchas monedas! Te escucho, "+npchar.name+".";
			link.l1.go = "SlaveGalleon_4";
		break;
			
		case "SlaveGalleon_4":
			Slavetrader_GetHispanShore();
			sTemp = pchar.questTemp.SlavetraderAreal.add; 
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(SPAIN);
			dialog.text = "Pronto, desde Caracas, zarpará un galeón pesado. Se llama "+pchar.questTemp.Slavetrader.ShipName+". Contiene una enorme cantidad de esclavos... unos 3000 hombres, indios del Orinoco, capturados de acuerdo con la política de repartimientos. El galeón navega hacia Santiago, las plantaciones de azúcar de Cuba necesitan muchos trabajadores. Debes capturar el galeón con su carga. Yo llevaría al menos dos barcos conmigo si fuera tú, dicen que el galeón es el mejor de su tipo. Las tarifas de pago se mantienen usuales, 200 pesos por cabeza. ";
			link.l1 = "¡Je! Suena bien. Estoy de acuerdo.";
			link.l1.go = "SlaveGalleon_5";
			link.l2 = "Sabes que no me gusta ese repartimiento tuyo. Es demasiado cínico. No voy a hacer esto.";
			link.l2.go = "SlaveGalleon_end";
		break;
			
		case "SlaveGalleon_5":
			sTemp = pchar.questTemp.SlavetraderAreal.add; 
			dialog.text = "Te deseo suerte entonces. Ten en cuenta que el capitán de este galeón es un marinero de guerra muy hábil y experimentado. No será una pelea fácil, así que prepárate. No pierdas tiempo, al barco le tomará quince o veinte días llegar "+sTemp+" Santiago. Trata de no perderlo, aunque este galeón es realmente difícil de pasar por alto.\n¡Sí! ¡Casi lo olvido! Hay un montón de baratijas indias en el barco, los pieles rojas a menudo pagan sus deudas con sus objetos de culto y artesanía. Tráeme cualquier cosa especial que encuentres, te pagaré muy bien por cada objeto valioso que traigas.";
			link.l1 = "Entiendo.";
			link.l1.go = "exit";
			SlavetraderGalleonInWorld();
			if(bImCasual) NewGameTip("¡Modo exploración: el temporizador no está desactivado. Cumple el plazo!");
			SetFunctionTimerCondition("Slavetrader_SlaveGalleonOver", 0, 0, 20, false);
			pchar.questTemp.Slavetrader = "wait1";
			AddQuestRecord("Slavetrader", "18");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
			AddQuestUserData("Slavetrader", "sAreal", sTemp);
		break;
			
		case "Lostgalleon":
			dialog.text = "Bueno, "+pchar.name+", era mi última esperanza... Por eso te he ofrecido este trabajo. Nadie más que tú es capaz de hacerlo... y veo que tú tampoco eres capaz. Entonces, digamos adiós. Después del último fracaso y todos esos rumores, todos mis clientes se han ido. Y estoy casi en bancarrota, tal vez deba dejar este pueblo. No te culpo, este trabajo era demasiado difícil. Eh... Adiós, "+pchar.name+".";
			link.l1 = "Lo siento mucho, "+npchar.name+", esto fue demasiado lejos. Lo siento mucho. Tal vez todo se calme. Adiós.";
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
				dialog.text = "Fuh, me siento mejor ahora... Tenía razón al confiar en ti... ¿De dónde viene esta ironía? ¿Qué pasa?";
				link.l1 = "Querido señor, no era un galeón... o un galeón muy grande... ¡Maldita sea! ¡Era un barco de línea! ¡Y ni siquiera me advertiste! Pero he logrado abordarlo. Tengo "+sTemp+" esclavos y estoy listo para transferirlos. Según nuestro trato me debe "+FindRussianMoneyString(iSlaveMoney)+". Sería excelente obtener alguna compensación por la desinformación.";
				link.l1.go = "Wingalleon_1";
			}
			else
			{
			dialog.text = "¿Encontraste el galeón? ¿Qué hay de los esclavos? ¡Se supone que deben ser tres mil y no menos! ¡Maldita sea, todos son unas ratas y traidores! No lo esperaba de ti... eras mi última esperanza.\nMuy bien... juro que gastaré cada moneda que me queda para destruirte, ¡para matarte! ¡Toda la flota de "+NationNameGenitive(sti(npchar.nation))+" te estará cazando! ¡Aléjate de aquí!";
				link.l1 = "Bueno...";
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
			dialog.text = "¡No me digas! Te juro que no tenía idea. Se suponía que iba a zarpar un galeón pesado, ¡no un maldito navío de línea! Parece que cambiaron sus planes en el último momento... ¡Pero aún así has tenido éxito!\nEstoy completamente de acuerdo contigo sobre el dinero y la compensación de tus gastos, la cosa es que no poseo tal suma en este momento. Sabes sobre mis problemas recientes... Pero no te enojes, "+pchar.name+", por el amor de Dios. Me das la carga y yo la venderé, mi cliente ya está esperando\nTendré toda la suma en cinco días, así que recibirás lo que mereces. Puedes confiar en mí. Toma, lleva todo el dinero que tengo ahora mismo.";
			link.l1 = "Hm... Esperaba recibir el dinero ahora. ¡Desearía que supieras qué clase de pelea tuve que pasar! Ah, lo que sea... Me compadeceré de ti. Pero ten en cuenta que si intentas engañarme, te encontraré incluso en Europa.";
			link.l1.go = "Wingalleon_yes";
			link.l2 = "Sabes, "+npchar.name+"¡Que te jodan! No fue un trato. Ni te imaginas qué clase de pelea tuve que manejar. Me quedo con todos los esclavos y los vendo sin tu agencia.";
			link.l2.go = "Wingalleon_no";
		break;
			
		case "Wingalleon_no":
			dialog.text = "¡Así que ahora estás hablando! Parece que un desprevenido "+npchar.name+" solo era una vaca para ordeñar, un simple retraso es suficiente para que me engañes y comiences una operación por tu cuenta. Parece que has olvidado que fui yo quien te dio el trabajo y el soplo sobre el botín\nMuy bien... Lo juro, gastaré cada moneda que me queda para destruirte, ¡para matarte! Toda la flota de "+NationNameGenitive(sti(npchar.nation))+"¡te estará cazando! ¡Fuera de mi vista!";
			link.l1 = "No te atrevas a asustarme, un cofre de dinero vacío. Hundiré todas tus flotas y las alimentaré a los cangrejos con él.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 70);
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Wingalleon_yes":
			dialog.text = "Gracias por su comprensión, "+pchar.name+". Prometo que todo estará bien, no hay necesidad de tus amenazas\nToma esto como un adelanto. Quince cofres. Cinco de ellos servirán como una compensación por el daño moral. Ven a verme en cinco días para obtener el resto.\nNo olvides traer todos los objetos indios que hayas encontrado en el barco... si es que los encontraste, por supuesto. No tengo nada para pagarte por ellos de todos modos.";
			link.l1 = "En cinco días,"+npchar.name+"En cinco días...";
			link.l1.go = "Wingalleon_yes_1";
		break;
			
		case "Wingalleon_yes_1":
			TakeNItems(pchar, "chest", 15);
			Log_Info("Has recibido unos cofres");
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
			dialog.text = "Como prometí, "+pchar.name+", estoy listo para pagarte. Los esclavos se han vendido, el cliente está contento y nosotros también. Después de deducir un adelanto, tu recompensa es"+FindRussianMoneyString(sti(pchar.questTemp.Slavetrader.iSlaveMoney))+". Por favor, tome su dinero.";
			link.l1 = "Espléndido, "+npchar.name+". Es bueno tratar con un hombre que puede cumplir su palabra...";
			link.l1.go = "FindRat_1";
		break;
			
		case "FindRat_1":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			dialog.text = "Siempre puedes confiar en mi palabra, "+pchar.name+". Nunca te he dado ninguna razón para dudar de mí. Los socios deben ser honestos entre sí, esa es la clave del negocio\nHablemos ahora de los artefactos indios. Muéstrame lo que tienes, no hagas esperar a un coleccionista como yo.";
			link.l1 = "Hm... Echa un vistazo.";
			link.l1.go = "FindRat_2";
		break;
			
		case "FindRat_2":
			if (CheckCharacterItem(pchar, "talisman16"))
			{
				dialog.text = "¡Sí! ¡Excelente! ¡Un cuchillo ritual dorado! Es algo raro. Siempre he querido tener algo así en mi colección. Te ofrezco 30 000 por él o un amuleto de 'Ehecatl' a cambio. De todos modos, tengo dos de ellos.";
				link.l1 = "Tomaré el dinero.";
				link.l1.go = "BG_money";
				link.l2 = "Tomaré el amuleto de 'Ehecatl' a cambio.";
				link.l2.go = "BG_change";
				link.l3 = "Mejor me quedo con este cuchillo.";
				link.l3.go = "BG_no";
			}
			else
			{
				dialog.text = "Veamos... Desafortunadamente, no tienes nada interesante para mí.";
				link.l1 = "Lo que digas.";
				link.l1.go = "BG_PF";
			}
		break;
			
		case "BG_money":
			dialog.text = "Espléndido. Toma tus 30 000 y este cuchillo indio es mío ahora.";
			link.l1 = "Bien. ¿Y eso es todo lo que te interesa...?";
			link.l1.go = "BG_PF";
			AddMoneyToCharacter(pchar, 30000);
			Log_Info("Has entregado un cuchillo de oro");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "talisman16", 1);
		break;
			
		case "BG_change":
			dialog.text = "¡Espléndido! Aquí tienes tu amuleto y este cuchillo indio es mío ahora.";
			link.l1 = "Bien. Y eso es todo en lo que estás interesado...";
			link.l1.go = "BG_PF";
			Log_Info("Has entregado un cuchillo de oro");
			Log_Info("Has recibido un amuleto de 'Ehecatl'");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "talisman16", 1);
			TakeNItems(pchar, "obereg_9", 1);
		break;
			
		case "BG_no":
			dialog.text = "Lo que sea. Pero es una lástima de todos modos...";
			link.l1 = "Bien. ¿Y eso es todo en lo que estás interesado...?";
			link.l1.go = "BG_PF";
		break;
			
		case "BG_PF":
			dialog.text = "¡Espera! Déjame echar otro vistazo...";
			link.l1 = "Claro. Ven a echar un vistazo y elige lo que quieras.";
			link.l1.go = "PF_check";
		break;
			
		case "PF_check":
			if (CheckCharacterItem(pchar, "mineral31"))
			{
				dialog.text = "¡Esto! Y ni siquiera lo noté al principio. Estoy interesado en este hueso con un anillo de cobre. Una cosa tan interesante, te diré... Puedo pagarte 20 000 pesos o darte un amuleto de 'Cimaruta' a cambio.";
				link.l1 = "Tomaré el dinero.";
				link.l1.go = "PF_money";
				link.l2 = "Tomaré el amuleto de 'Cimaruta' a cambio.";
				link.l2.go = "PF_change";
				link.l3 = "Mantendré este artefacto conmigo.";
			link.l3.go = "PF_no";
			}
			else
			{
				dialog.text = "No... no tienes nada más de interés aquí.";
				link.l1 = "¡Lo que sea!";
				link.l1.go = "FindRat_3";
			}
		break;
			
		case "PF_money":
			dialog.text = "¡Excelente! Aquí tienes tus 20 000 pesos y este hueso es mío ahora.";
			link.l1 = "Bien. Me siento bien con nuestro trato.";
			link.l1.go = "FindRat_3";
			AddMoneyToCharacter(pchar, 20000);
			Log_Info("Has entregado un hueso mágico");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "mineral31", 1);
		break;
			
		case "PF_change":
			dialog.text = "¡Espléndido! Aquí está tu amuleto y este hueso es mío ahora.";
			link.l1 = "Excelente. Me siento bien con nuestro trato.";
			link.l1.go = "FindRat_3";
			Log_Info("Has dado un hueso mágico");
			Log_Info("He recibido un amuleto de 'Cimaruta'");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "mineral31", 1);
			TakeNItems(pchar, "amulet_11", 1);
		break;
			
		case "PF_no":
			dialog.text = "Lo que sea. Pero es una lástima de todos modos...";
			link.l1 = "Necesito ese hueso para mí, lo siento mucho.";
			link.l1.go = "FindRat_3";
		break;
			
		case "FindRat_3":
			dialog.text = "Bueno... al abordar el galeón, oh lo siento, el Navío de Línea, me has salvado. Realmente aprecio nuestra asociación, "+pchar.name+". Eres mi mejor agente.";
			link.l1 = "Me siento halagado. Estás sobreestimando mis logros...";
			link.l1.go = "FindRat_4";
		break;
			
		case "FindRat_4":
			dialog.text = "Estoy completamente serio. Y voy a pedirte que cumplas otra misión debido a tus habilidades extraordinarias y porque confío en ti.";
			link.l1 = "¡Eh! ¡Sorprendente! Estoy escuchando. ¿Dónde está otro galeón con esclavos?";
			link.l1.go = "FindRat_5";
		break;
			
		case "FindRat_5":
			dialog.text = "El asunto no se trata de esclavos esta vez. ¿Sorprendido? Te pagaré bien por la misión... Muy bien.";
			link.l1 = "A ir directo al grano.";
			link.l1.go = "FindRat_6";
		break;
			
		case "FindRat_6":
			dialog.text = "Este negocio está relacionado con los recientes acontecimientos de los que también fuiste parte... Así que, como bien sabes, llevo un negocio bastante ilegal: el tráfico de esclavos. También sabrás que contrato corsarios como tú para todo tipo de misiones\nUno de mis hombres me traicionó no hace mucho por razones desconocidas. Reunió pruebas e hizo un informe a las autoridades. Tuviste el placer de ver las consecuencias con tus propios ojos. Un barco con soldados llegó aquí... ya sabes el resto\nMe costó bastante esfuerzo resolver la situación. Como probablemente entiendas, no puedo dejar que esta traición quede sin respuesta. Además, no puedo vivir y trabajar tranquilo sabiendo que la rata sigue viva. He enviado cazadores de recompensas, pero aún no hay resultados\nTe pido que te encargues personalmente de este asunto. Más aún, sus acciones también te afectaron a ti.";
			link.l1 = "Hum... ¡este bastardo debe ser colgado de una verga! Cuéntame más sobre él y, por supuesto, sobre mi pago por el trabajo.";
			link.l1.go = "FindRat_7";
		break;
			
		case "FindRat_7":
			dialog.text = "No te preocupes por eso. Pagaré una buena suma por su eliminación y no hablo solo de dinero. No escatimaré en los mejores artículos de mis colecciones. Hablemos del hombre. Su nombre es Francois Gontier\nEstá al tanto de mi cacería, por lo que vendió su fragata para ocultar sus huellas. Mis colegas me dijeron que lo vieron en Panamá. Creo que deberías comenzar tu búsqueda desde allí.";
			link.l1 = "Bueno, estoy en camino entonces.";
			link.l1.go = "FindRat_8";
		break;
			
		case "FindRat_8":
			dialog.text = "Te deseo suerte entonces. Sabe que este Gontier es un marinero muy experimentado y tiene una tripulación de despiadados asesinos. No tiene nada que perder, así que peleará de una manera muy desesperada.";
			link.l1 = "No le tengo miedo a gente como él, pero consideraré lo que has dicho. Adiós, y estate seguro de que lo atraparé incluso en el infierno.";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(SPAIN);
			AddQuestRecord("Slavetrader", "21");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.questTemp.Slavetrader = "FindRatPanama";
		break;
			
		case "Wincorvette":
			dialog.text = "¡Espléndido! Ahora puede escribir sus informes a las medusas. Nadie se atreve a meterse conmigo. Mis agradecimientos a usted, "+pchar.name+", eres un hombre indispensable.";
			link.l1 = "Gracias, "+npchar.name+", por una valoración tan positiva de mis acciones. ¿Qué hay de mi pago?";
			link.l1.go = "Wincorvette_1";
		break;
			
		case "Wincorvette_1":
			dialog.text = "Claro. Pagaría el precio adecuado por un trabajo tan difícil. Primero, te presento este excelente catalejo.";
			link.l1 = "¡Vaya, qué regalo!";
			link.l1.go = "Wincorvette_2";
		break;
			
		case "Wincorvette_2":
			dialog.text = "Aparte, aquí tienes 100 000 pesos como tu pago principal y 50 000 como compensación por tus propios gastos.";
			link.l1 = "Gracias, "+npchar.name+"Reitero que es un verdadero placer tratar con usted.";
			link.l1.go = "Wincorvette_3";
			Log_Info("Has recibido un excelente catalejo");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "spyglass4", 1);
		break;
			
		case "Wincorvette_3":
			dialog.text = "Te estaré esperando en un mes, como siempre. Es un asunto muy grande en camino y necesitarás un escuadrón bien equipado. Te pido que entiendas eso y te prepares bien. Si mi plan funciona, seremos ricos.";
			link.l1 = "Bueno,"+npchar.name+" . Volveré cuando esté listo.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 150000);
			AddQuestRecord("Slavetrader", "21_13");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_5");
			pchar.questTemp.Slavetrader = "wait_5";
		break;
			
		case "Lostcorvette":
			dialog.text = "Qué lástima, qué pena... Bueno, no te sientas mal, no eres el primer hombre al que ese canalla engañó. Lo atraparé algún día de todos modos\nEn cuanto a ti, ven a verme en un mes. Será grande, así que reúne un escuadrón bien equipado y armado. Por favor, tómalo en serio y haz todo lo posible para prepararte. Si mi plan funciona, seremos ricos.";
			link.l1 = "Bien, "+npchar.name+". Volveré cuando esté listo.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_14");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_5");
			pchar.questTemp.Slavetrader = "wait_5";
		break;
		
		case "Havana_fort":
			dialog.text = "Estás justo a tiempo, "+pchar.name+"¡Estuve a punto de empezar a preocuparme! Iba a enviar a un hombre a buscarte.\n¡Empecemos! Tu misión ahora es realmente grande y arriesgada, pero la recompensa es adecuada. Recibirás más de un millón de pesos después de que el trabajo esté hecho.";
			link.l1 = "¡Ahora estamos hablando! Estoy escuchando, "+npchar.name+".";
			link.l1.go = "Havana_fort_1";
		break;
		
		case "Havana_fort_1":
			dialog.text = "Los indios esclavizados estaban siendo trasladados en pequeños grupos a La Habana desde todo el continente, además llegaron algunos galeones de África y fueron descargados. Ahora hay casi cinco mil esclavos detrás de los altos muros del fuerte de La Habana.";
			link.l1 = "Tengo la sensación de que el trato consiste en asaltar La Habana.";
			link.l1.go = "Havana_fort_2";
		break;
		
		case "Havana_fort_2":
			dialog.text = "Tienes un buen presentimiento, "+pchar.name+". Eso es exactamente lo que quiero pedirte que hagas. Tú y sólo tú. Dudo que alguno de mis otros agentes sea capaz de hacer esto\n¿Creo que estás dentro?";
			link.l1 = "Para ser honesto, "+npchar.name+", estoy un poco desconcertado ahora. No tenía idea de que tu actividad fuera tan... a gran escala. Claro, estoy dentro. "+RandSwear()+"";
			link.l1.go = "Havana_fort_3";
			link.l2 = "¿Sabes qué, "+npchar.name+"?, esto está yendo demasiado lejos. He tenido suficiente de tus sorpresas. La próxima vez, tu codicia querrá que declare la guerra a España y tendré que luchar contra ellos yo solo. Si realmente necesitas esos esclavos, entonces asalta La Habana por ti mismo.";
			link.l2.go = "Havana_fort_not";
		break;
		
		case "Havana_fort_not":
			dialog.text = "No esperaba eso de ti... Maldición, ¿qué se supone que debo decirle a mi cliente? Está bien. Es tu decisión y tengo que encontrar un nuevo socio. Adiós, "+pchar.name+". Y no usaré tus servicios en el futuro. Recuerda que has dejado caer el trato que podría hacer ricos a tus descendientes hasta la séptima generación.";
			link.l1 = "No puedes conseguir todo el dinero del mundo, y muerdes más de lo que puedes masticar. Adiós, "+npchar.name+".";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
		
		case "Havana_fort_3":
			dialog.text = "Sabía que estarías de acuerdo. Ahora, escucha los detalles. El fuerte de La Habana siempre ha sido un objetivo difícil, pero ahora es aún más complicado.\nDos navíos de línea están custodiando las costas de Cuba, y debes enfrentarte a ellos primero antes de asaltar el fuerte...";
			link.l1 = "Veo. No será la primera vez que luche contra Navíos de Línea, ja-ja. ¿Cuánto tiempo tengo?";
			link.l1.go = "Havana_fort_4";
		break;
		
		case "Havana_fort_4":
			dialog.text = "No mucho. No más de tres semanas, y después de eso los esclavos serán trasladados a los puestos avanzados españoles de Cuba. Debes darte prisa. ";
			link.l1 = "No perdamos más tiempo entonces. ¡Estoy en camino!";
			link.l1.go = "Havana_fort_5";
		break;
		
		case "Havana_fort_5":
			dialog.text = "¡Un momento!"+pchar.name+", usted y yo nunca tuvimos malentendidos ni desacuerdos. Sin embargo, quiero que sepa lo que está sucediendo aquí. Cuento con usted, y el cliente cuenta conmigo\nHemos invertido mucho esfuerzo y dinero en esta operación. Cada esclavo, los cinco mil deben ser entregados a mí\nDe lo contrario, tomaremos medidas muy radicales contra usted. Sin ofender, esto es solo una advertencia. ";
			link.l1 = "No te preocupes, "+npchar.name+", entiendo lo que es el negocio, por eso también debes recordar pagarme una vez que los entregue. Adiós.";
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
				dialog.text = "Bueno.. ¿Y qué hay del premio de tu victoria?";
				link.l1 = "Tengo "+sTemp+" esclavos.";
				link.l1.go = "Havana_Fort_yes";
				break;
			}
			if (amount < 4500 && amount >= 1)
			{
				dialog.text = "Bueno, bueno. ¿Olvidaste lo que dije? Tenías que traerme aquí no menos de cinco mil esclavos y tienes "+sTemp+"¿Por qué es eso?";
				link.l1 = "Hmm.. Parte de ellos no han sobrevivido el camino desde La Habana... la comida y las medicinas se estaban agotando.";
				link.l1.go = "Havana_Fort_no";
				break;
			}
			dialog.text = "Bueno, bueno... ¿Quieres engañarme? ¿Olvidaste lo que te dije? ¡Dónde están mis esclavos te pregunto! ¡¿Dónde están?!";
			link.l1 = "Mm.. Bueno, ves...";
			link.l1.go = "Havana_Fort_no";
		break;
		
		case "Havana_Fort_no":
			dialog.text = "Bien. No necesito tus explicaciones. Teníamos un trato y te daré una semana para conseguir no menos de cinco mil esclavos. De lo contrario, tendrás muchos problemas.";
			link.l1 = "Está bien, está bien, relájate, se los conseguiré.";
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
			dialog.text = "¡Espléndido! Has cumplido mi tarea como siempre. Estoy muy complacido contigo.";
			link.l1 = "Yo también... Pero estaría aún más complacido cuando reciba mi dinero por el cargamento.";
			link.l1.go = "Havana_Fort_yes_1";
		break;
		
		case "Havana_Fort_yesA":
		dialog.text = "Estoy muy contento por eso. Llegaste tarde, pero has cumplido mi tarea de manera excelente.";
			link.l1 = "Y ahora quiero obtener dinero por la carga.";
			link.l1.go = "Havana_Fort_yes_1";
			pchar.quest.Slavetrader_HavanaSeekOver.over = "yes";
		break;
		
		case "Havana_Fort_yes_1":
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			dialog.text = "Claro. Voy a vender los esclavos a mi cliente, él pagará y tú recibirás tus monedas. Igual que la última vez. Veamos, has traído aquí "+sTemp+" esclavos. La suma es "+FindRussianMoneyString(iSlaveMoney)+". Ven aquí para el pago en una semana.";
			link.l1 = "Bien, "+npchar.name+", tenemos un trato. Estaré aquí en una semana. Pero ten mucho cuidado...";
			link.l1.go = "Havana_Fort_yes_2";
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
		break;
		
		case "Havana_Fort_yes_2":
			dialog.text = ""+pchar.name+", por favor, no. Somos socios y no hay lugar para trampas y desconfianza entre nosotros. Te prometí muchas monedas y las has recibido. Te prometí tareas interesantes y también las has recibido. Siempre he estado compensando tus costos incluso en los días más oscuros para mi negocio. ¿Acaso no he cumplido siempre mi palabra?";
			link.l1 = "Hmm... No... Solo quiero que me paguen, eso es todo.";
			link.l1.go = "Havana_Fort_yes_3";
		break;
		
		case "Havana_Fort_yes_3":
			dialog.text = "Ve ahora..."+pchar.name+", eres mi mejor agente y cuento con hacer negocios contigo de nuevo en el futuro. ";
			link.l1 = "Bien, "+npchar.name+". Pero debe entenderme también, un millón de pesos es una suma enorme.";
			link.l1.go = "Havana_Fort_yes_4";
		break;
		
		case "Havana_Fort_yes_4":
			dialog.text = "Te entiendo muy bien, pero primero tengo que vender a los esclavos y solo entonces recibiré el dinero.";
			link.l1 = "De acuerdo. Creo que nos entendimos.";
			link.l1.go = "Havana_Fort_yes_5";
		break;
		
		case "Havana_Fort_yes_5":
			dialog.text = "Espléndido. Nos vemos en una semana. Y ahora tengo que prepararme y partir para comerciar con mi cliente.";
			link.l1 = "No te molestaré entonces. Nos vemos en una semana, "+npchar.name+".";
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
			dialog.text = "¿Qué hago aquí? Bueno... es mi banco. Lo compré hace dos días. Eres mi primer cliente y puedo ofrecerte unas condiciones de crédito muy tentadoras...";
			link.l1 = "¡Maldita sea con los créditos! ¿Dónde está "+pchar.questTemp.Slavetrader.Name+"?";
			link.l1.go = "Usurer_Escape_1";
		break;

		case "Usurer_Escape_1":
			dialog.text = "¡Cálmese, por favor! Se escapó hace mucho tiempo.";
			link.l1 = "¿Cómo?";
			link.l1.go = "Usurer_Escape_2";
		break;
		
		case "Usurer_Escape_2":
			dialog.text = "¿No lo sabes? Desapareció hace una semana. Resultó que se llevó todas las inversiones de sus clientes. Dicen que hasta el gobernador sufrió. Esta casa quedó vacía y la compré de la colonia.";
			link.l1 = "¿Desaparecido? ¿Cómo?";
			link.l1.go = "Usurer_Escape_3";
		break;
		
		case "Usurer_Escape_3":
			dialog.text = "He oído que ha huido de nuestra colonia... Supongo que también te debe a ti. ¿Mucho?";
			link.l1 = "¡Más de un millón! ¡Pero atraparé a esa rata de todos modos! ¿A dónde ha ido? ¿Nombre de su barco?";
			link.l1.go = "Usurer_Escape_4";
		break;
		
		case "Usurer_Escape_4":
			dialog.text = "Nadie está al tanto. En serio. Simplemente se ha ido. El barco llamado 'Mauritius' o 'Maurdius' había zarpado ese día, quizás lo usó para escapar.";
			link.l1 = "¡Maldita sea! ¡Y yo confié en ese bastardo! ¡Tenía un olor a traidor desde el primer día! ¡Y fui tan tonto como para creer que éramos verdaderos socios! Pero haré que se arrepienta algún día... Está bien,"+npchar.name+", le pido disculpas por mi comportamiento... Si es un buen hombre, trataré con usted en el futuro, esté seguro de ello, pero por ahora, adiós.";
			link.l1.go = "Usurer_Escape_5";
		break;
		
		case "Usurer_Escape_5":
			string sColony;
			sColony = npchar.city;
			SetNull2Deposit(sColony);
			dialog.text = "Está bien. Lo entiendo. Si necesitas algo de dinero o deseas invertir, siempre estoy a tu servicio.";
			link.l1 = "Gracias. Pero es mejor que guarde mi dinero conmigo. Nos vemos.";
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
			dialog.text = "¿De veras? Parece que él no quiere hablar conmigo directamente... Está bien, discutamos el asunto contigo. "+pchar.GenQuest.Noblelombard.Name+" me debe "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Summ))+": "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Money))+" y también el interés, "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Percent))+" durante tres meses. Si no veo dinero en el día más cercano, entonces venderé su reliquia y no me importa su valor para él. Negocios son negocios.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Summ))
			{
				link.l1 = "¡Espléndido! En ese caso, voy a pagarte la suma completa con todos los intereses de inmediato... "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Summ))+". Él tomará su reliquia por sí mismo. Aquí está tu dinero.";
				link.l1.go = "Noblelombard_1";
			}
			if(sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Percent)*2)
			{
				link.l2 = "Mi cliente tendrá el dinero en tres meses. Hagamos un trato, te pagaré los intereses de los últimos tres meses y de los próximos tres meses."+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Percent)*2)+". Y la deuda misma se te pagará más tarde.";
				link.l2.go = "Noblelombard_2";
			}
			if(sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Percent))
			{
				link.l3 = "Mi cliente tendrá dinero en tres meses. ¿Qué tal si le pago los intereses de los últimos tres meses y usted espera hasta que mi cliente tenga suficiente dinero?";
				link.l3.go = "Noblelombard_3";
			}
			link.l4 = "¡Esta rareza cuesta una fortuna! Parece que mi cliente tendrá que pagarla él mismo.";
			link.l4.go = "Noblelombard_4";
			pchar.quest.noblelombard = "true";//лесник с нпчара на пчара
		break;
		
		case "Noblelombard_1":
			dialog.text = "¡Excelente! Todo salió bien, conseguí mi dinero y "+pchar.GenQuest.Noblelombard.Name+" recuperará su reliquia.";
			link.l1 = "Un placer hacer negocios contigo, "+npchar.name+"¡Adiós ahora!";
			link.l1.go = "exit";
			pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Summ)*2;
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Summ));
			pchar.GenQuest.Noblelombard = "full";
			AddCharacterExpToSkill(pchar, "Leadership", 150);
	
		break;
		
		case "Noblelombard_2":
			if(sti(pchar.GenQuest.Noblelombard.Chance) < 7)
			{
				dialog.text = "Mm.. Bien. Esto me sirve. Pero si "+pchar.GenQuest.Noblelombard.Name+" no encuentra dinero en tres meses, entonces no haré otro retraso. Asegúrate de que lo sepa.";
				link.l1 = "¡Lo haré! Me alegra que hayamos llegado a un acuerdo. Hasta luego.";
				link.l1.go = "exit";
				pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Percent)*4;
				AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Percent)*2);
				pchar.GenQuest.Noblelombard = "maxpercent";
				AddCharacterExpToSkill(pchar, "Leadership", 50);
				AddCharacterExpToSkill(pchar, "Fortune", 70);
			
			}
			else
			{
				dialog.text = "No. No funcionará. Necesito toda la suma y antes del atardecer. Asegúrate de que tu 'cliente' lo sepa. No tengo nada más que decirte.";
				link.l1 = "Mm... bien. Qué pena que no quieras comprometerte.";
				link.l1.go = "Noblelombard_4";
				AddCharacterExpToSkill(pchar, "Fortune", 30);
			
			}
		break;
		
		case "Noblelombard_3":
			if(sti(pchar.GenQuest.Noblelombard.Chance) < 3)
			{
				dialog.text = "Hm.. Está bien. Lo acepto solo por respeto a tu cliente. Pero si "+pchar.GenQuest.Noblelombard.Name+" no encuentra dinero en tres meses, entonces no haré un retraso nuevamente. Asegúrate de que lo sepa.";
				link.l1 = "¡Lo haré! Me alegra que hayamos llegado a un acuerdo. Hasta luego.";
				link.l1.go = "exit";
				pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Percent)*2;
				AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Percent));
				pchar.GenQuest.Noblelombard = "minpercent";
				AddCharacterExpToSkill(pchar, "Leadership", 50);
				AddCharacterExpToSkill(pchar, "Fortune", 150);
			}
			else
			{
				dialog.text = "No. No funcionará. Necesito la suma completa y antes del atardecer. Asegúrate de que tu 'cliente' lo sepa. No tengo nada más que decirte.";
				link.l1 = "Mm... está bien. Qué lástima que no quieras comprometerte.";
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
				dialog.text = "¡No me digas! "+pchar.GenQuest.Noblelombard.Name+" no ha abierto un depósito a su nombre. Ni siquiera está en nuestra colonia, se ha ido a Europa. Le digo que nunca he visto a un hombre tan deshonesto. Quiso engañarme, pero fracasó; yo también tengo algunos de mis propios trucos...";
				link.l1 = "¡Bastardo! Me ha dado su palabra....";
				link.l1.go = "Noblelombard_6";
			}
			else
			{	// Addon-2016 Jason уменьшаем раздачу дублонов
				dialog.text = "Correcto. "+pchar.GenQuest.Noblelombard.Name+" ha hecho un depósito a tu nombre. Por favor, tómalo...";
				link.l1 = "¡Espléndido! Adiós, "+npchar.name+".";
				link.l1.go = "Noblelombard_9";
			}
		break;
		
		case "Noblelombard_6":
			dialog.text = "No hay tal cosa para personas como "+pchar.GenQuest.Noblelombard.Name+" porque no tienen honor ni conciencia. ¿Supongo que te ha engañado?";
			link.l1 = "Lo ha hecho, supongo. Sea como fuere, "+npchar.name+", tampoco voy a quedarme aquí mucho tiempo y Europa es pequeña... Quizás, algún día nos encontremos. ¡Adiós!";
			link.l1.go = "Noblelombard_7";
		break;
		
		case "Noblelombard_7":
			DialogExit();
			AddQuestRecord("Noblelombard", "6");
			AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
			CloseQuestHeader("Noblelombard");
			DeleteAttribute(Pchar, "GenQuest.Noblelombard");
			DeleteAttribute(Pchar, "quest.noblelombard"); // лесник с нпчара на пчара
		break;
		
		case "Noblelombard_9":
			DialogExit();
			iTemp = sti(pchar.GenQuest.Noblelombard.Regard); // Addon-2016 Jason уменьшаем раздачу дублонов
			AddMoneyToCharacter(pchar, iTemp);
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Noblelombard", "7");
			AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
			CloseQuestHeader("Noblelombard");
			DeleteAttribute(Pchar, "GenQuest.Noblelombard");
			DeleteAttribute(Pchar, "quest.noblelombard");// с нпчара на пчара  лесник
		break;
//<-- семейная реликвия

		// Бремя гасконца
		case "sharlie_credit":
			dialog.text = "Monsieur, no le conozco. Solo presto dinero a los ciudadanos locales o a los capitanes. Discúlpeme...";
			link.l1 = "Ya veo. Aunque es una lástima.";
			link.l1.go = "exit";
		break;
		// Бремя гасконца
		
		// Addon-2016 Jason, французские миниквесты (ФМК)
		// ФМК-Гваделупа
		case "FMQG_x":
			DelLandQuestMark(npchar);
			dialog.text = "¿Q-qué... Qué quieres decir?";
			link.l1 = "Eres una maldita rata. Ahora escúchame con mucho cuidado: no soy tan estúpido. Pinette escribió dos copias de la carta. Te di una de ellas, la segunda está en posesión de mi agente de confianza. Si algo me sucede, mi hombre la entregará directamente en manos del gobernador...";
			link.l1.go = "FMQG_x1";
		break;
		
		case "FMQG_x1":
			dialog.text = "";
			link.l1 = "Así que te sugiero rezar por mi buena salud en la iglesia cada mañana en lugar de enviar asesinos a por mi vida. ¡Una última advertencia! Haz un movimiento contra mí y estás jodido. ¿Entendido? Bien. Respira hondo y sigue contando tus doblones.";
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
			dialog.text = "No quiero hablar contigo.";
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		// Леди Бет -->
		case "LadyBeth_Usurer_1":
			dialog.text = "Por supuesto. Muchos sólo quieren conseguir su dinero e irse. Especialmente considerando los recientes rumores...";
			link.l1 = "¿Qué rumores?";
			link.l1.go = "LadyBeth_Usurer_2";
		break;

		case "LadyBeth_Usurer_2":
			dialog.text = "Dicen que las condiciones de su tripulación son cada vez peores. Monsieur Blackwood incluso ha comenzado a tolerar pérdidas regulares, algo que nunca había sucedido antes. Pero ese no es mi negocio. Yo sólo vendo mercancías. Entonces, ¿qué cosas le interesan?";
			link.l1 = "Vayamos al grano.";
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
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
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
	//Log_TestInfo("El capitán del galeón zarpó de " + sld.city + " y se dirige a " + sld.quest.targetShore);
	//==> на карту
	sld.mapEnc.type = "trade";
	//выбор типа кораблика на карте
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = "Galleon '" + sName + " '";
	int daysQty = 20; //дней доехать даем с запасом
	Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, daysQty);//вот он, сам запуск энкаунтера
}
