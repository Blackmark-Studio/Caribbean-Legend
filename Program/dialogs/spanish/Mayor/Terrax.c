// Маркус Тиракс, барон Ла Веги
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc, sTemp;
	int i;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

// ------------------------------------------блок angry-----------------------------------------------
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                break;
            }
        }
    }
// ------------------------------------------блок angry-----------------------------------------------

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
			// Addon 2016-1 Jason пиратская линейка патч 17/1
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && !CheckAttribute(npchar, "quest.mtraxx_complete")) 
			{
				if (pchar.questTemp.Mtraxx == "full_complete_end" || pchar.questTemp.Mtraxx == "full_complete")
				{
					dialog.text = "Ah Príncipe, finalmente estás aquí. ¡Al menos uno de vosotros se ha molestado en aparecer! ¡El trabajo está esperando y todos vosotros habéis desaparecido! ¿Dónde diablos está todo el mundo?";
					link.l1 = "Ni idea... Marcus, estoy fuera. He tenido suficiente. Los muertos vienen a mí en mis sueños y el mismo Lucifer me respira en la nuca. Demasiada sangre se ha derramado recientemente.";
					link.l1.go = "mtraxx_113";
					break;
				}
			}
			// Jason НСО
			// если Сага завалена, то у Маркуса ноды в двух местах и оплата вперед
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "¿Tienes algún 'asunto' para mí?";
				link.l1 = "Saludos, Marcus. Sí, tengo un 'asunto'. Rentable y práctico.";
				link.l1.go = "patria_x";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Condotier.NeedMoney") && pchar.questTemp.Patria == "epizode_12_pirates" && sti(pchar.money) >= 100000)
			{
				dialog.text = "¿Trajiste el dinero?";
				link.l1 = "Lo hice.";
				link.l1.go = "patria_x8";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "¡Ese es nuestro cliente! El trabajo está hecho, tu Barón está sentado en una mazmorra bien custodiada. ¿Quizás te gustaría echar un vistazo, je-je?!";
				link.l1 = "Tendré mucho tiempo para hacer eso, ja-ja. ¿Lo tratan bien?";
				link.l1.go = "patria_10";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "¡Charles!, ¿qué demonios?";
				link.l1 = "Marcus, todo salió mal. No pude ni venir ni informarte...";
				link.l1.go = "patria_x33";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "¡Aquí está nuestro titiritero!";
				link.l1 = "¡Ja, ja! ¡El espectáculo fue perfecto!";
				link.l1.go = "patria_x29";
				break;
			}
            dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("¿Tienes algo que decirme? ¿No? ¡Entonces déjame en paz!","Ja, "+pchar.name+"¡Tienes algún asunto conmigo? ¿No? Entonces no me molestes.")+"","Pensé que me había explicado claramente... ¡Te dije que te fueras, pero sigues molestándome!","Bien, me estoy cansando de esta grosería.","repeat",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Ya me voy.","Claro, Marcus...","Lo siento, Marcus...","Ups...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("¿Estás loco? ¿Querías jugar al carnicero, eh? Todos los piratas están enfadados contigo, muchacho, será mejor que te largues de aquí...","   Parece que te has convertido en un perro rabioso, chico. ¿Querías estirar un poco las manos? Sin ofender, pero aquí no hay nada para ti. ¡Piérdete!");
				link.l1 = RandPhraseSimple("Escucha, quiero arreglar la situación.","Ayúdame a resolver este problema, por favor...");
				link.l1.go = "pirate_town";
				break;
			}
			// Сага - завершаем искушение барбазона
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "terrax")
			{
				// Addon 2016-1 Jason пиратская линейка патч 17/1
				if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
				{
					link.l1 = "Marcus, ¿alguna vez dejarás de estar enojado conmigo? Salvé a tu amigo, Vincent, quien asaltó Cartagena con nosotros, ¡y también te salvé a ti! ¿O acaso Bernard ni siquiera te lo ha dicho?";
					link.l1.go = "Temptation_13";
				}
				else
				{
					link.l1 = "¿Por qué eres tan grosero, Marcus? ¿No dijo Bernard nada sobre mí?";
					link.l1.go = "Temptation";
				}
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "to_lavega")
			{
				link.l2 = "Estoy buscando un trabajo... ¿Tienes algo rentable en mente?";
				link.l2.go = "Mtraxx";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkTrade") && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "Tengo algo de seda para vender.";
				link.l2.go = "Mtraxx_silktrade";
			}
			if (pchar.questTemp.Mtraxx == "silk_14")
			{
				link.l1 = "He encontrado un comprador. Es un constructor de barcos de Port Royal. Necesita seda de barco para su producción y podrá comprar lotes de cien rollos cada mes por 25 doblones por rollo. Sus hombres recibirán las mercancías del 10 al 15, por la noche, la ubicación es el Cabo Negril. La contraseña es: 'Un comerciante de Lyon'. Bald Geffrey ya ha entregado el primer lote a Jamaica.";
				link.l1.go = "mtraxx_13";
			}
			if (pchar.questTemp.Mtraxx == "silk_15")
			{
				link.l1 = "He encontrado un comprador para ti. Es un constructor naval de Port Royal. Necesita seda de barco para su producción y podrá comprar lotes de cien rollos cada mes por 25 doblones por rollo. Sus hombres recibirán las mercancías del 10 al 15, por la noche, la ubicación es Cabo Negril. La contraseña es: 'Un comerciante de Lyons'. Me tomó más de dos meses encontrar a tal comprador, Geffrey ya debe haber vendido la seda a los contrabandistas. Lo siento, Marcus.";
				link.l1.go = "mtraxx_15";
			}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("¿Estás loco? ¿Querías jugar al carnicero? Todos los piratas están enfadados contigo, chico, será mejor que te largues de aquí..."," Parece que te has convertido en un perro rabioso, chico. ¿Querías estirar un poco las manos? Sin ánimo de ofender, pero no hay lugar para ti aquí. ¡Lárgate!");
				link.l1 = RandPhraseSimple("Escucha, quiero arreglar la situación..."," Ayúdame a resolver este problema, por favor...");
				link.l1.go = "pirate_town";
				break;
			}
			// Jason НСО
			if(!CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "¡Charles!, ¿qué demonios?";
				link.l1 = "Marcus, todo salió mal. No pude ni venir ni informarte...";
				link.l1.go = "patria_33";
				break;
			}
			if(!CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "¡Me alegra verte, amigo!";
				link.l1 = "Me alegra verte también. ¡Gracias por el espectáculo asombroso!";
				link.l1.go = "patria_29";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "¡Me alegra verte, muchacho! ¿En qué puedo ayudarte?";
				link.l1 = "Tengo una propuesta para ti. ¡Adecuada para un pirata, ya sabes!";
				link.l1.go = "patria";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "¡Ese es nuestro cliente! El trabajo está hecho, tu Barón está sentado en una mazmorra bien custodiada. ¿Quizás te gustaría echar un vistazo, je-je?!";
				link.l1 = "Tendré mucho tiempo para hacer eso, ja-ja. ¿Lo tratan bien?";
				link.l1.go = "patria_10";
				break;
			}
			// если Сага завалена, то у Маркуса ноды в двух местах и оплата вперед
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "¿Tienes algún asunto para mí?";
				link.l1 = "Saludos, Marcus. Sí, un asunto. Rentable y pirático.";
				link.l1.go = "patria_x";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Condotier.NeedMoney") && pchar.questTemp.Patria == "epizode_12_pirates" && sti(pchar.money) >= 100000)
			{
				dialog.text = "¿Trajiste el dinero?";
				link.l1 = "Lo hice.";
				link.l1.go = "patria_x8";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "¡Ese es nuestro cliente! El trabajo está hecho, tu Barón está sentado en una mazmorra bien custodiada. ¿Quizás te gustaría echar un vistazo, eh-eh?!";
				link.l1 = "Tendré mucho tiempo para hacer eso, ja-ja. ¿Lo tratan bien?";
				link.l1.go = "patria_10";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "¡Charles!, ¿qué demonios?";
				link.l1 = "Marcus, todo salió mal. No pude ni venir ni informarte...";
				link.l1.go = "patria_x33";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "¡Aquí está nuestro titiritero!";
				link.l1 = "¡Ja-ja! ¡El espectáculo fue perfecto!";
				link.l1.go = "patria_x29";
				break;
			}
			// Тени прошлого
			if(CheckAttribute(pchar, "questTemp.Saga.Shadows") && pchar.questTemp.Saga.Shadows == "islatesoro" && npchar.location == "Pirates_townhall")
			{
				dialog.text = "¡Me alegra verte, muchacho! ¿Cómo puedo ayudarte?";
				link.l1 = "Marcus, tengo que hablar contigo. No estoy seguro de que te gustará, pero necesito tu ayuda de todos modos.";
				link.l1.go = "shadows";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "islatesoro" && npchar.location == "Pirates_townhall")
			{
				dialog.text = "Ja, aquí estás, "+pchar.name+" He estado esperando tu llegada. El Diablo del Bosque me ha desconcertado con tu problema sobre Tortuga...";
				link.l1 = "Me dijo que encontraste una solución. ¿Tengo razón?";
				link.l1.go = "terrapin";
				break;
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkTrade") && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "Tengo seda para vender.";
				link.l2.go = "Mtraxx_silktrade";
			}
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar)+", ¡me alegra verte! ¿Qué necesitas esta vez, camarada?","¿Qué quieres?","¿Otra vez? ¡No molestes a la gente si no tienes nada que hacer!","Eres un "+GetSexPhrase("buen corsario","buena chica")+", así que puedes vivir por ahora. Pero no quiero hablar contigo más.","repeat",10,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Solo quería verte.","Nada.","Está bien, Marcus, lo siento.","¡Maldita sea, lo siento mucho, Marcus!",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("¡Robo!!! Eso es inaceptable! Prepárate para morir, rata...","¡Oye, ¿qué haces ahí?! ¿Pensaste que podrías robarme? Estás acabado...","Espera, ¿qué demonios?! ¡Resulta que eres un ladrón! Hasta aquí llegaste, bastardo...");
			link.l1 = LinkRandPhrase("¡Mierda!","¡Caramba!","¡Ah, maldita sea!");
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+GetSexPhrase("Vete","Aléjate")+" ¡fuera de aquí!","¡Fuera de mi casa!");
			link.l1 = "Ups...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "No me distraigas de mi trabajo con tus charlas inútiles. La próxima vez no te irá tan bien...";
        			link.l1 = "Entendido, Marcus.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = RandPhraseSimple("Estoy harto de ti.","No quiero hablar contigo, así que será mejor que te mantengas alejado de mí.");
			link.l1 = RandPhraseSimple("Bueno...","Mm, está bien entonces...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Espero que no me molestes más con tus charlas vacías o tendré que matarte. Digo que no estaré contento de hacerlo.";
        			link.l1 = "Puedes estar seguro de eso, Marcus, no lo haré...";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("Lavega_town","reload","reload6");
		break;
		// <<<<<<<<<<<<============= блок нод angry =============================
		
//--> -----------------------------Сага - Искушение Барбазона завершающие этапы---------------------------
		case "Temptation":
			dialog.text = "¡Ja! ¿El héroe de los Turcos? Perdona por el rudo saludo, muchacho. Bernard ya me ha contado sobre tu maravillosa participación y dijo algo acerca de una trampa para mí. Me gustaría escuchar los detalles...";
			link.l1 = "Fue una trampa, en efecto. Te estaban cazando a ti, no a Bernard. Él solo era el cebo.";
			link.l1.go = "Temptation_1";
		break;
		
		case "Temptation_1":
			dialog.text = "";
			link.l1 = "El plan era sencillo. Se suponía que debías salvar a tu amigo y ser el primero en abordar el 'Separador'. Y justo en ese momento habrían disparado al barco y lo habrían hecho pedazos. El bergantín estaba cargado de pólvora como el infierno con azufre.";
			link.l1.go = "Temptation_2";
		break;
		
		case "Temptation_2":
			dialog.text = "¡Maldita sea! ¿De quién fue la idea de esa locura? ¡¿Y cómo podría averiguar dónde escondían a Bernard?!";
			link.l1 = "Los autores de ese plan fueron Jackman y su hermano David. Un mensajero te habría informado que el 'Separador' estaba esperando tu ayuda en la bahía sur de los Turcos. Me han elegido a mí como ese mensajero y ese fue su error.";
			link.l1.go = "Temptation_3";
		break;
		
		case "Temptation_3":
			dialog.text = "¡No lo entiendo! ¿Cuál es tu papel en todo esto?";
			link.l1 = "He estado observando a ese bastardo de Jackman durante mucho tiempo. Trabajo con Jan Svenson si no lo sabes. Yo y el Diablo del Bosque hemos decidido desenmascararlo. Jan está seguro de que él es el culpable de la muerte de Blaze y Steven fue acusado sin razón.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end") link.l1.go = "Temptation_14";
			else link.l1.go = "Temptation_4"; //патч 17/1
		break;
		
		case "Temptation_4":
			dialog.text = "¡Heh! Pero se encontró un diente de tiburón con sus iniciales en el cuerpo de Blaze con sus iniciales - S.D. - esta cosa le pertenece a Steven, todo el mundo lo sabe...";
			link.l1 = "Fue una trampa. Jackman apostó alto. Se deshizo de Nathaniel Hawk y tomó su lugar en Maroon Town, luego asesinó a Sharp e hizo responsable a Shark del asesinato. Tengo suficientes pruebas de sus crímenes. Las encontré en el cofre de Jacob. Ahí es donde estaban la segunda parte del mapa de Sharp y el fragmento de Hawk.";
			link.l1.go = "Temptation_5";
		break;
		
		case "Temptation_5":
			dialog.text = "¡Maldita sea! ¿Así que Steven es inocente? ¿Y por qué Jacob ha hecho todo esto?";
			link.l1 = "Esperaba convertirse en el jefe de los Hermanos y esperaba algo relacionado con Isla Tesoro. No pudo conseguir tu apoyo ni el de Svenson, así que decidió deshacerse de ambos. Tú eras el primero en la lista. Jan, siendo el más peligroso, era el segundo.";
			link.l1.go = "Temptation_6";
		break;
		
		case "Temptation_6":
			dialog.text = "¿Dónde está ese bastardo? ¡Lo destrozaré!";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) // Акула жив
			{
				link.l1 = "Jackman y su hermano están muertos al igual que el resto de sus cazadores. Me he encargado personalmente de ellos. Este bastardo no hará daño a nadie más. Marcus, ¿votarías por Steven Dodson? Este es mi favor personal.";
				link.l1.go = "Temptation_7";
			}
			else
			{
				link.l1 = "Jackman y su hermano están muertos, así como el resto de los cazadores. Me encargué personalmente de ellos. Este bastardo no hará daño a nadie más. Desafortunadamente, Steven fue asesinado...";
				link.l1.go = "Temptation_10";
			}
		break;
		
		case "Temptation_7":
			dialog.text = "¡Claro que votaré! Siempre consideré a Shark el más digno de nosotros después de Blaze. Y casi había creído en su culpabilidad. ¡Todos lo hemos hecho! Aquí, toma mi fragmento.";
			link.l1 = "¡Muy bien! Ahora puedes respirar libremente.";
			link.l1.go = "Temptation_8";
		break;
		
		case "Temptation_8":
			GiveItem2Character(pchar, "splinter_mt"); // дать осколок
			dialog.text = "Verdadero... Según entiendo, ¿representas los intereses de Tiburón?";
			link.l1 = "Sí. Yo y Jan Svenson. Bien, Marcus, ¡nos vemos!";
			link.l1.go = "Temptation_9";
		break;
		
		case "Temptation_10":
			dialog.text = "¿¡Muerto?! ¿Cómo? ¿También obra de Jackman?";
			link.l1 = "No. Lo hizo su propio contramaestre, Chad Kapper era su nombre. Ya recibió lo que merecía... Marcus, Svenson cree que tú eres el más digno de ser el nuevo líder de los Hermanos. El resto de los barones apoyará esta decisión. ¿Aceptas esto?";
			link.l1.go = "Temptation_11";
		break;
		
		case "Temptation_11":
			dialog.text = "¡Je! No necesitas pedírmelo dos veces. ¡Es un gran honor ser el Jefe de los Hermanos! Ni pienses que voy a estar en desacuerdo.";
			link.l1 = "Genial. Me alegra que hayas aceptado esto.";
			link.l1.go = "Temptation_12";
		break;
		
		case "Temptation_12":
			GiveItem2Character(pchar, "splinter_mt"); // дать осколок
			dialog.text = "Aquí, toma mi fragmento. Entrégaselo a Svenson. ¿Supongo que él está a cargo?";
			link.l1 = "Sí, lo es. Bien, Marcus, ¡nos vemos!";
			link.l1.go = "Temptation_9";
		break;
		
		case "Temptation_9":
			dialog.text = "Sí, y quiero agradecerte por salvar a mi amigo Bernard. Aquí, toma esta bolsa llena de oro.";
			link.l1 = "¡Gracias! ¡Adiós!";
			link.l1.go = "Temptation_exit";
		break;
		
		case "Temptation_exit":
			DialogExit();
			TakeNItems(pchar, "gold_dublon", 300);
			Log_Info("Has recibido 300 doblones");
			PlaySound("interface\important_item.wav");
			NextDiag.CurrentNode = "I_know_you_good";
			AddQuestRecord("BarbTemptation", "25");
			if (CheckCharacterItem(pchar, "splinter_mt") && CheckCharacterItem(pchar, "splinter_jb") && CheckCharacterItem(pchar, "splinter_zm")) Saga_GiveCalendar();
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "Temptation_13":
			dialog.text = "Sí, me contó sobre la magnífica llegada de Charlie Prince a Turks... ¿Dices que me salvó el trasero? ¿Cómo? Bernard me dijo algo sobre una trampa...";
			link.l1 = "Sí, era una trampa. Tú eras el objetivo, Bernard solo era el cebo...";
			link.l1.go = "Temptation_1";
		break;
		
		case "Temptation_14":
			dialog.text = "Ja-ja-ja, trabajando para el Diablo del Bosque, ¿eh Príncipe? Entonces, ¿ganas mejor dinero con él que conmigo? ¡Dime con toda honestidad!";
			link.l1 = "Marcus, dejemos el pasado de lado para siempre. Ahora tenemos un objetivo común y es más importante que saquear caravanas. ¡Maldita sea! ¡Es lo más importante ahora! ¡El futuro de los Hermanos está en juego!";
			link.l1.go = "Temptation_15";
		break;
		
		case "Temptation_15":
			dialog.text = "¡Muy bien, Príncipe, lo entiendo! Después de todo, eres un corsario libre, trabajar para el Diablo del Bosque fue tu elección, y has tomado una buena decisión... Steven entonces... Dijiste que fue calumniado, ¿verdad?";
			link.l1 = "Absolutamente correcto.";
			link.l1.go = "Temptation_4";
		break;
		
		// Тени прошлого
		case "shadows":
			dialog.text = "¡Claro, haré mi mejor esfuerzo para ayudarte! Adelante.";
			link.l1 = "Échale un vistazo, Marcus... Aquí tienes un diente de tiburón. ¿Qué puedes decirme sobre él?";
			link.l1.go = "shadows_1";
		break;
		
		case "shadows_1":
			RemoveItems(pchar, "shark_teeth", 1);
			dialog.text = "¡Ja! Es el diente de un tiburón blanco que fue asesinado por Steven Dodson, él esperaba impresionar a una chica. La gente ha comenzado a llamarlo Tiburón desde entonces. Solo unos pocos podrían hacer eso bajo el agua usando un simple sable. Pero él era joven y estúpido y Beatrice Sharp era la chica más hermosa del Caribe... Entonces, ¿cómo lo conseguiste?";
			link.l1 = "Me lo dio el ex-verdugo de San Juan. Este diente fue usado para matar a un hombre. Su nombre era... Joshua Leadbeater.";
			link.l1.go = "shadows_2";
		break;
		
		case "shadows_2":
			dialog.text = "Esa es una vieja historia. Steven mató a ese hombre. Estaba conmocionado por la muerte de Beatrice y pensó que Leadbeater era la única persona viva responsable de su fallecimiento. Pero más tarde encontró algunos papeles en el cadáver de Joshua, los estudió y se arrepintió de su acto.\nLa Máscara no tenía la culpa de la muerte de Beatrice, él solo necesitaba al Carnicero. La celosa exnovia del Carnicero, Jessica, había organizado todo esto.";
			link.l1 = "¿Has leído esos papeles?";
			link.l1.go = "shadows_3";
		break;
		
		case "shadows_3":
			dialog.text = "¿Por qué debería? Por supuesto que no. No me interesaban. Pero puedo decirte por qué la Máscara perseguía al Carnicero si tienes algo de tiempo libre. El borracho Steven me contó esta historia muchas veces.";
			link.l1 = "Tengo tiempo. Confía en mí, mi interés tiene un propósito. Incluso puedo escribir esta historia.";
			link.l1.go = "shadows_4";
		break;
		
		case "shadows_4":
			dialog.text = "Lo sé, que nunca pierdes el tiempo. Escucha entonces. Joshua Leadbeater era el capitán naval inglés y el legendario 'Neptune' estaba bajo su mando...";
			link.l1 = "... ";
			link.l1.go = "shadows_5";
		break;
		
		case "shadows_5":
			DialogExit();
			SetLaunchFrameFormParam("Una hora más tarde", "Saga_FinalLedbitterStory", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "shadows_6":
			AddQuestRecordInfo("Mask", "1");
			dialog.text = "... pero Leadbeater sobrevivió y fue recogido por algún barco. Su herida lo desfiguró y desde entonces había estado usando una máscara. Con el tiempo, la gente comenzó a llamarlo la Máscara. La venganza contra el hombre que lo había marcado de por vida se convirtió en su objetivo de vida.";
			link.l1 = "Ya veo... He escrito todo. Creo que tengo que releerlo y hacer paralelismos con toda la información que ya tengo. Una historia triste, sin duda. ¿Has visto alguna vez a Jessica?";
			link.l1.go = "shadows_7";
		break;
		
		case "shadows_7":
			dialog.text = "¡Claro! Ella acompañó a Carnicero en todos sus viajes hasta que él la dejó por Beatrice. Jess no pudo perdonárselo. La gente la llamaba el talismán del Carnicero, porque siempre tenía suerte mientras ella estaba allí con él.\nCréelo o no, pero tan pronto como se deshizo de ella en Barbados, su negocio fue mal, el botín se volvió pobre y el 'Neptune' se convirtió en un visitante frecuente del astillero de Isla Tesoro. Pero eso se puede explicar por el hecho de que Carnicero había pasado la mayor parte de su tiempo con Beatrice en la cabina en lugar de en el puente.\nBeatrice no era como Jessica, no era adicta a las aventuras y la guerra, aunque Nicholas le enseñó esgrima y navegación. Sí, le gustaban los romances marinos, pero no tenía la suficiente dureza en su interior. El 'Neptune' de Carnicero no era el lugar adecuado para ella. Al final, eso la mató.";
			link.l1 = "¿Y qué hay de Jessica?";
			link.l1.go = "shadows_8";
		break;
		
		case "shadows_8":
			dialog.text = "Oh, ella era algo de verdad... Todos los marineros del 'Neptune' obedecían sus órdenes y no solo porque era la novia del capitán. Jess era una maestra de la esgrima y la navegación, los esfuerzos de Butcher no fueron en vano. Era dura e imprudente, y era tan hermosa.\nMuchos hombres querían compartir una cama con ella, pero solo quería a Butcher, molestarla era realmente arriesgado, muchos sintieron los resultados en su propia piel literalmente, y para los más persistentes sus lecciones de esgrima resultaron ser las últimas de sus vidas.\nJess poseía una espada muy especial, la única de su clase en el Caribe, no tengo idea de dónde la consiguió. Una espada de hoja flameante. La hoja no podía ser agarrada con la mano e incluso el más mínimo toque dejaba una herida terrible.\nJess era una aventurera no de nacimiento, sino de vocación. Por cierto, si necesitas saber más sobre ella, puedes hablar con un conocido tuyo. Él puede contarte mucho más sobre ella de lo que yo puedo.";
			link.l1 = "¿De veras? ¿Y quién es este hombre?";
			link.l1.go = "shadows_9";
		break;
		
		case "shadows_9":
			dialog.text = "Jan Svenson. El Diablo del Bosque nunca lo admitirá, pero tenía planes con Jessica. Fue en el tiempo cuando ya había tomado el Dominio Occidental para sí mismo y su fama era algo de envidiar, así que la tigresa era buena para él. \nDespués de que el Carnicero se deshiciera de Jess, Jan empezó a visitar Barbados sospechosamente a menudo, haciendo temblar de miedo a la guarnición, je. Como bien sabes, Jessica era hija del plantador de Bridgetown. \nEn fin, sus planes eran bien conocidos en círculos privados, pero nadie se atrevía a expresar su opinión al respecto. Jan puede que ahora se siente en sus posaderas en Blueweld, pero en aquel entonces cualquier palabra equivocada dirigida a él podía resultar mal. \nAl final, no les resultó. Jess no pudo vivir con el dolor causado por la traición del Carnicero, y se vengó un año después con la ayuda de la Máscara. Esta venganza terminó terrible para todos: para el Carnicero, para Beatrice, para la Máscara y para ella misma. Todos murieron.";
			link.l1 = "No. El Carnicero sigue vivo.";
			link.l1.go = "shadows_10";
		break;
		
		case "shadows_10":
			dialog.text = "¿Qué?! ¿He oído mal?! ¿¡Él está vivo?!";
			link.l1 = "Sí. El Capitán Carnicero no fue ahorcado. Hm, en realidad lo fue, pero gracias a Jacob Jackman y Henry el Verdugo, quienes habían asustado al verdugo, él sobrevivió. La ejecución fue solo una actuación. Tengo pruebas.";
			link.l1.go = "shadows_11";
		break;
		
		case "shadows_11":
			dialog.text = "¡Increíble! ¿Y dónde está ahora?";
			link.l1 = "Se le conoce como Lawrence Beltrop y vive en Port-Royal. Pero parece que no ha cambiado y sigue siendo peligroso. Jackman, quien ha causado mucho alboroto entre los Hermanos, estaba siguiendo sus órdenes.";
			link.l1.go = "shadows_12";
		break;
		
		case "shadows_12":
			dialog.text = "¡Maldita sea! ¡El contramaestre ha encontrado a su capitán después de todo! Después de tantos años... Dices Beltrop... ¡espera! Ahora veo por qué en los papeles de Blaze estaba ese extraño protocolo de interrogatorio... Parece que Blaze descubrió algo interesante sobre Butcher-Beltrop...";
			link.l1 = "¿De qué estás hablando?";
			link.l1.go = "shadows_13";
		break;
		
		case "shadows_13":
			dialog.text = "Cuando he tomado esta residencia, me he permitido un tiempo para echar un vistazo a los papeles de Blaze. He encontrado un protocolo de interrogatorio de alguien llamado Samuel Brooks. Había muchos detalles sobre las aventuras de Thomas Beltrope, un famoso pirata y el amigo más cercano de Nicolas Sharp. Parece que él es el padre de Carnicero.";
			link.l1 = "Interesante. Parece que los hijos de Beltrop y Sharp han continuado el trabajo de sus padres...";
			link.l1.go = "shadows_14";
		break;
		
		case "shadows_14":
			dialog.text = "Así parece... Dime, amigo, ¿por qué estás tan interesado en el pasado de personas que ya llevan mucho tiempo muertas? ¿De qué se trata todo esto?";
			link.l1 = "Necesito papeles que puedan probar que Ellen McArthur es la hija de Beatrice Sharp y la nieta de Nicolas Sharp y tiene todos los derechos para llevar este apellido. No me importa que su apellido pueda ser Beltrop.";
			link.l1.go = "shadows_15";
		break;
		
		case "shadows_15":
			dialog.text = "He encontrado nada sobre Ellen McArthur en los archivos de Blaze. Es extraño que Beatrice no le haya contado a Blaze sobre el nacimiento de su sobrina. No es su estilo.";
			link.l1 = "Escucha, ¿quizás haya algo más en los papeles de Sharp sobre esta historia? ¡Necesito cada detalle que pueda conseguir!";
			link.l1.go = "shadows_16";
		break;
		
		case "shadows_16":
			dialog.text = "Mm... Quizás. Según las notas de Blaze, él estaba tratando de encontrar la isla donde su hermana había muerto. Hay copias de documentos de archivo sobre la expedición punitiva de Leadbeater. Nada interesante, excepto por algunos números de latitud.\nEste paralelo cruza el mar Caribe en su parte norte. Pero no hay indicio de longitud. Obviamente, las búsquedas de Blaze fracasaron, no puedes ni imaginar cuántas islas pequeñas hay en esa latitud.";
			link.l1 = "¿Y cuál es la latitud?";
			link.l1.go = "shadows_17";
		break;
		
		case "shadows_17":
			dialog.text = "Veamos... Aquí: 21 32' Norte. No sé cómo puede ayudarte.";
			link.l1 = "Puede ser. Muchas gracias, Marcus, por tu franca historia. ¡Hasta luego!";
			link.l1.go = "shadows_18";
		break;
		
		case "shadows_18":
			DialogExit();
			pchar.questTemp.Saga.Shadows = "jessika";
			AddQuestRecord("Shadows", "6");
			LAi_SetHuberType(npchar);
			NextDiag.CurrentNode = "I_know_you_good";
			sld = characterFromId("Svenson");
			sld.quest.jessika = "true";
			// рифы доступны для посещения
			i = FindIsland("RockIsland");
			Islands[i].visible = true;
			Islands[i].reload_enable = true;
			// для любителей самостоятельно добавлять локаторы
			LAi_LocationDisableOfficersGen("Shore67", true);//офицеров не пускать
			// и сразу прерывание
			pchar.quest.Saga_Jess_Island.win_condition.l1 = "location";
			pchar.quest.Saga_Jess_Island.win_condition.l1.location = "Shore67";
			pchar.quest.Saga_Jess_Island.function = "Saga_JessikaIsland"; 
			// активируем квест хронометра Алекса
			pchar.questTemp.AlexClock = "terrax"; // 280912
		break;		
		
		// суп из черепахи
		case "terrapin":
			dialog.text = "Bueno, puedo hacer algo por ti. Como sabes, la seguridad de Tortuga no solo está garantizada por el fuerte La Roche, sino también por un escuadrón pirata que constantemente vigila las costas de la isla. El puerto de Tortuga es seguro, estos muchachos saben su negocio y tienen barcos poderosos. Levasseur lleva tiempo atrayendo a estos capitanes.\nSon capaces de luchar incluso contra un escuadrón de línea y serán oponentes serios. Así que, siendo el guardián del Código y también el líder de los Hermanos de la Costa, puedo hacer que estos perros guardianes se alejen de las costas de Tortuga.";
			link.l1 = "¿Y eso es todo?";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = "¿No es eso suficiente? No puedo ayudarte más de todos modos. Tienes que destruir el fuerte, pero al menos no necesitas luchar contra esos barcos de guardia. Créeme, son más peligrosos que el fuerte, así que mi ayuda hará que todo sea más fácil.";
			link.l1 = "Bueno, si tengo que atacarlo de todos modos, la partida del escuadrón pirata realmente ayudará. ¡Gracias, Marcus! ¿Cuándo puedo atacar Tortuga?";
			link.l1.go = "terrapin_2";
		break;
		
		case "terrapin_2":
			dialog.text = "Cuando quieras. Los barcos de guardia partirán a mi señal.";
			link.l1 = "Está bien. Entonces tengo que irme a prepararme.";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			DialogExit();
			// Левассера - к барьеру!
			sld = characterFromId("Tortuga_Mayor");
			LAi_LoginInCaptureTown(sld, true);
			pchar.questTemp.Sharlie.Hardcore_Tortuga = "true";
			pchar.questTemp.Terrapin = "hardcore";
			pchar.questTemp.Sharlie.DelTerGuard = "true"; // убираем пиратскую эскадру
		break;
		
		case "pirate_town":
            dialog.text = "¿Resolver el problema? ¿Tienes alguna idea de lo que has hecho? De todas formas, tráeme un millón de pesos y persuadiré a los muchachos para que olviden tu hazaña. Si no te gusta la idea, entonces puedes irte al infierno.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "Está bien, estoy listo para pagar.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "Adiós...";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//закрыть переход
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "¡Bien! Considérate limpio de nuevo. Pero espero que no vuelvas a hacer cosas tan repugnantes.";
			link.l1 = "No lo haré. Demasiado caro para mí. Adiós...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
		
		// Addon 2016-1 Jason ------------------------- пиратская линейка --------------------------
		case "Mtraxx":
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				dialog.text = "Primero consigue un barco para ti mismo, luego pide un trabajo. Un terrícola no tiene nada que hacer aquí. ¡Piérdete!";
				link.l1 = "Mm... Ya veo.";
				link.l1.go = "exit";
				break;
			}
			if(ChangeCharacterHunterScore(Pchar, "spahunter", 0) > 10)
			{
				dialog.text = "¿Estás completamente loco? La mitad del mundo español te está persiguiendo. Harás más daño que bien. Resuelve tus problemas, luego postúlate. ¡Eso es todo lo que quería decir! ¡Fuera de aquí!";
				link.l1 = "Mm... ya veo.";
				link.l1.go = "exit";
				break;
			}
            dialog.text = "¿Quieres un poco de acción, eh? ¡Ja-ja! Bien... Aunque te advierto, chico, no encontrarás paz conmigo. Si le tienes miedo al olor de la pólvora o no puedes derramar sangre, la puerta está detrás de ti. No soporto a los nenazas. Además, no durarás mucho conmigo si eres un soplón o una rata que se deleita robando la parte del botín de un compañero. ¿Entonces qué? ¿Estás dentro?";
			link.l1 = "Estoy dentro, Marcus. No tengo miedo de pelear y no hay perro que pueda acusarme de ser un cobarde o una rata.";
			link.l1.go = "Mtraxx_1";
			link.l2 = "¡Uy, eso es demasiado para mí! Perdón, Marcus, pero mejor me retiro...";
			link.l2.go = "Mtraxx_exit";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("LaVega");
		break;
		
		case "Mtraxx_exit":
            DialogExit();
			pchar.questTemp.Mtraxx = "fail";
		break;
		
		case "mtraxx_wait":
            dialog.text = "¿Qué, todavía estás aquí?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkTrade") && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "Tengo algo de seda para vender.";
				link.l2.go = "Mtraxx_silktrade";
				link.l1 = "Ya me voy.";
				link.l1.go = "exit";
				break;
			}
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		case "Mtraxx_1":
            dialog.text = "Ja-ja, bueno-bueno, mi valiente piratilla, hablemos de negocios entonces. Mi fuente en Santo Domingo me informó sobre un capitán español que es tan rico en ámbar azul que lo está regalando a las rameras. ¿Has oído hablar del ámbar azul?";
			link.l1 = "Tengo. Una piedra rara y valiosa.";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "Precisamente. Incluso aquí, los banqueros y joyeros pagan buen dinero por ello y en la vieja y buena Europa puedes conseguir diez veces más por ello. El ámbar no es una piedra rara en el Caribe, pero el azul es una rareza. Y ahora tenemos a algún perro astuto castellano jactándose de que tiene más ámbar azul que los banqueros de Cuba y La Española tienen de ámbar amarillo juntos.";
			link.l1 = "¿Se puede confiar en los cuentos de un español borracho? Encontró tres doblones y anda diciendo a todos que ha encontrado El Dorado";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "No lo habría hecho, pero en realidad estaba regalando ámbar azul a las putas. Algo en su fanfarronería debe ser digno de confianza. Ve a Santo Domingo e investiga. Si encuentras el yacimiento de ámbar azul, será aún mejor. Haz esto y puedo garantizarte una recompensa y respeto en La Vega.";
			link.l1 = "¿Y si tu información no vale nada?";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
            dialog.text = "Entonces demuéstrame que el castellano es un mentiroso.";
			link.l1 = "Muy bien. ¿Quién es tu fuente en Santo Domingo?";
			link.l1.go = "mtraxx_5";
		break;
		
		case "mtraxx_5":
			// belamour legendary edition даем флаг и лизензию ГВИК если отсутствует -->
			bOk = IsCharacterPerkOn(pchar,"FlagSpa") || IsCharacterPerkOn(pchar,"FlagHol");
			if(CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 60 && bOk) sTemp = ".";
			else 
			{
				if(bOk) 
				{
					if(!CheckCharacterItem(pchar, "HolTradeLicence") || GetDaysContinueNationLicence(HOLLAND) < 60) 
					{
						sTemp = ". Wait a minute, take a trading license for 60 days."; 
						GiveNationLicence(HOLLAND, 60);
					}
				}
				else // нет флага
				{
					if(!CheckCharacterItem(pchar, "HolTradeLicence")) 
					{
						sTemp = ". Espera un minuto, toma una licencia de comercio de 60 días y una bandera española para desembarcar en Santo Domingo. A partir de ahora, recomiendo obtener la tuya propia, te ayudará a engañar al vigia de la oficina del puerto. Ya me la devolverás.";
						GiveNationLicence(HOLLAND, 60);
						SetCharacterPerk(pchar, "FlagSpa");
						log_info("Ha recibido la bandera española");
						pchar.questTemp.GiveMeSpaFlag = true;
					}
					else // есть лицензия
					{	
						if(GetDaysContinueNationLicence(HOLLAND) < 60) 
						{
							sTemp = ". Espera, ¡¿cómo vas a comerciar sin tener la bandera adecuada?! Aquí tienes, una licencia de comercio de 60 días, superior a la tuya. Así como la bandera española para desembarcar en Santo Domingo. A partir de ahora, te recomiendo que te hagas con la tuya, te ayudará a engañar al vígia de la oficina del puerto. Ya me la devolverás.";
							GiveNationLicence(HOLLAND, 60);
							SetCharacterPerk(pchar, "FlagSpa");
							log_info("Ha recibido la bandera española");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
						else 
						{
							sTemp = ". Espera, ¿cómo vas a comerciar sin tener la bandera adecuada? Toma, coge la bandera española para el desembarcar en Santo Domingo. A partir de ahora, te recomiendo que te hagas con la tuya, te ayudará a engañar al vigía de la oficina portuaria. Ya me la devolverás.";
							SetCharacterPerk(pchar, "FlagSpa");
							log_info("Ha recibido la bandera española");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
					}
				}
			}
			// <-- legendary edition
            dialog.text = "Necesitas a una chica del burdel llamada Gabriela Chapado. Di mi nombre y la contraseña es: 'Collar de Ámbar'. Ella te dará detalles. Y no pierdas tiempo - la información aún está fresca, pero en un día o dos puede volverse obsoleta."+sTemp;
			link.l1 = "Entendido, Marcus. Me dirijo a Santo Domingo.";
			link.l1.go = "mtraxx_6";
		break;
		
		case "mtraxx_6":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_1";
			pchar.questTemp.Mtraxx.AffairOfHonor = "true"; // конфликт с делом чести
			pchar.questTemp.ZA.Block = true;			// конфликт с квестом "Заносчивый аристократ"
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_1", "1");
			Mtraxx_JewelryBegin();
			AddMapQuestMarkCity("SantoDomingo", false);
		break;
		
		case "mtraxx_7":
			i = GetCharacterItem(pchar, "jewelry7");
            dialog.text = "Ya me han informado de tu llegada. ¡Dame un informe!";
			link.l1 = "He tratado con ese amante del ámbar azul, aunque no fue fácil. He logrado encontrar sus depósitos y saquearlos. Te he traído "+FindRussianQtyString(i)+" piezas de ámbar azul.";
			link.l1.go = "mtraxx_8";
			DelLandQuestMark(characterFromId("Terrax"));
			DelMapQuestMarkCity("LaVega");
		break;
		
		case "mtraxx_8":
			if (sti(pchar.questTemp.Mtraxx.JewQty) > GetCharacterItem(pchar, "jewelry7"))
			{
				PlaySound("interface\important_item.wav");
				Log_Info("Has entregado "+FindRussianQtyString(GetCharacterItem(pchar, "jewelry7"))+" trozos de ámbar azul");
				RemoveItems(pchar, "jewelry7", GetCharacterItem(pchar, "jewelry7"));
				dialog.text = "Bueno, bueno... Hijo, ¿recuerdas mi advertencia sobre los peligros de ser una rata? ¿Qué me dijiste entonces? ¿Que ningún perro puede culparte por eso? ¿Crees que soy estúpido, chico? Estoy perfectamente consciente de que has saqueado "+FindRussianQtyString(sti(pchar.questTemp.Mtraxx.JewQty))+" piezas de ámbar azul en la Costa de los Mosquitos. ¡Ahora corre, pequeña rata, corre, y reza para que nunca nos volvamos a encontrar!";
				link.l1 = "¡Maldita sea!";
				link.l1.go = "AngryExitAgainWithOut";
				pchar.questTemp.Mtraxx = "fail";
				npchar.Dialog.currentnode = "First time";
				CloseQuestHeader("Roger_1");
				// belamour legendary edition забрать флаг обратно
				if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
				{
					DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
					DeleteAttribute(pchar,"perks.list.FlagSpa"); 
					log_info("Has entregado bandera española");
				}
			}
			else
			{
				PlaySound("interface\important_item.wav");
				Log_Info("Has entregado "+FindRussianQtyString(GetCharacterItem(pchar, "jewelry7"))+" trozos de ámbar azul");
				RemoveItems(pchar, "jewelry7", sti(pchar.questTemp.Mtraxx.JewQty));
				dialog.text = "¡Bien hecho, muchacho! Te has mostrado desde tu mejor lado: te ocupaste de un asunto difícil y trajiste todo lo que saqueaste. ¡Buen trabajo! Me alegra no haberme equivocado contigo.";
				link.l1 = "¿Qué hay de mi parte, Marcus?";
				link.l1.go = "mtraxx_9";
			}
		break;
		
		case "mtraxx_9":
			i = sti(pchar.questTemp.Mtraxx.JewQty)/2;
			PlaySound("interface\important_item.wav");
			Log_Info("Has recibido "+FindRussianQtyString(i)+" trozos de ámbar azul");
			TakeNItems(pchar, "jewelry7", i);
			// belamour legendary edition забрать флаг обратно
			if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
			{
				DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
				DeleteAttribute(pchar,"perks.list.FlagSpa"); 
				log_info("Has entregado una bandera española");
			}
            dialog.text = "¡Hablado como un verdadero pirata, ja-ja-ja! La mitad del botín es tuyo. Tómalo.";
			link.l1 = "Gracias, capitán. ¿Tienes algo más para mí?";
			link.l1.go = "mtraxx_10";
			DeleteAttribute(pchar, "questTemp.Mtraxx.JewQty");
			CloseQuestHeader("Roger_1");
			Achievment_Set("ach_57");
		break;
		
		case "mtraxx_10":
            dialog.text = "Siempre tengo tareas para muchachos capaces. Hay un asunto delicado que quiero que manejes. Hay un barco estacionado en Capsterville, llamado 'Serpiente', bajo el mando de Geffrey Brooke, también conocido como Geffrey el Calvo. Trabaja para mí. Un excelente luchador, sabe todo sobre armas y espadas, pero un completo idiota en cualquier otro aspecto de la vida. Pero no seamos duros con Calvito, nadie es perfecto, ¡ja-ja!\nAsí que. Este tipo duro atacó un convoy holandés al norte de Saint Martin y capturó una barca llena de sacos de trigo. La cuestión es que logró encontrar seda de barco escondida entre los sacos. Una carga realmente grande. Esta mercancía es extremadamente valiosa y rara, los holandeses la traen de Europa solo para las necesidades de su ejército. Esta seda se usa para velas especiales que aumentan la velocidad del barco y la capacidad de navegar con el viento.\nEs casi imposible de comprar, venderla no es un problema, pero es difícil encontrar el precio adecuado. ¡Estos malditos comerciantes siempre reducen el precio! Sé que hay gente en el Caribe que está dispuesta a dar un buen precio en doblones para comprar esta seda y tu objetivo es encontrar a esas personas.\n¿Qué? Cualquier tonto puede saquear caravanas, pero el comercio es solo para personas con al menos una señal de existencia de cerebro en el cráneo. Planeo vender seda de barco mensualmente, así que tu objetivo es encontrar un comprador regular que pague al menos veinte doblones de oro por un rollo. Tienes dos meses para hacerlo, no puedo mantener a Geffrey el Calvo en Capsterville para siempre.\nEso es todo. Zarpa hacia Capsterville y habla con Geffrey antes de que venda la carga a los contrabandistas por una miseria. Ya te dije que es un poco 'simple'.";
			link.l1 = "Mm... Lo tengo. Ya estoy en camino.";
			link.l1.go = "mtraxx_11";
		break;
		
		case "mtraxx_11":
            DialogExit();
			pchar.questTemp.Mtraxx = "silk_1";
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_2", "1");
			Mtraxx_SilkBegin();
		break;
		
		case "mtraxx_12":
            dialog.text = "¡Ja! Aquí está el valiente capitán "+GetFullName(pchar)+". ¿Qué hay del comprador?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkLate"))
			{
				link.l1 = "He encontrado un comprador. Es un constructor naval de Port Royal. Necesita seda para su producción y podrá comprar lotes de cien rollos cada mes por 25 doblones el rollo. Sus hombres recibirán la mercancía del 10 al 15, por la noche, el lugar es Cabo Negril. La contraseña es: 'Un comerciante de Lyon'. Me tomó más de dos meses encontrar tal comprador, Geffrey ya debe haber vendido la seda a los contrabandistas. Lo siento, Marcus.";
				link.l1.go = "mtraxx_15";
			}
			else
			{
				link.l1 = "Te he encontrado un comprador. Es un constructor de barcos de Port Royal. Necesita seda para barcos para su producción y podrá comprar lotes de cien rollos cada mes por 25 doblones el rollo. Sus hombres recibirán las mercancías del 10 al 15, por la noche, el lugar es Cabo Negril. La contraseña es: 'Un mercader de Lyons'. El Calvo Geffrey ya ha entregado el primer lote a Jamaica.";
				link.l1.go = "mtraxx_13";
			}
		break;
		
		case "mtraxx_13":
            dialog.text = "¡Eso es estupendo, amigo mío! Bien hecho. Es difícil encontrar a un hombre capaz de usar tanto las manos como la cabeza. Ven a verme en 20 días para recoger tu recompensa. Para entonces, Calvo Geffrey habrá traído el dinero de la primera transacción."; // правки прогона 3
			link.l1 = "Muy bien, Marcus. Nos vemos pronto. Espero que tengas otro trabajo para mí.";
			link.l1.go = "mtraxx_14";
		break;
		
		case "mtraxx_14":
            dialog.text = "Lo haré. Nos vemos luego.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkLate"))
			{
				SetFunctionTimerCondition("Mtraxx_SilkPay", 0, 0, 30, false);
				//SetFunctionTimerCondition("Mtraxx_SilkPayLate", 0, 0, 40, false);
				AddQuestRecord("Roger_2", "23");
			}
			else
			{
				SetFunctionTimerCondition("Mtraxx_SilkPay", 0, 0, 20, false); // правки прогона 3
				//SetFunctionTimerCondition("Mtraxx_SilkPayLate", 0, 0, 30, false);
				AddQuestRecord("Roger_2", "24");
			}
		break;
		
		case "mtraxx_15":
			pchar.quest.Mtraxx_SilkTimeLateAll.over = "yes";
            dialog.text = "Lástima, pero aun así es un gran éxito. ¡Hiciste un buen trabajo! No recibirás tu parte del lote de Geffrey, pero aún mereces una recompensa. Ven a verme en un mes, habré vendido la primera partida a tu comprador para entonces, luego hablaremos.";
			link.l1 = "Muy bien, Marcus. Hasta pronto. Espero que tengas otro trabajo para mí.";
			link.l1.go = "mtraxx_14";
		break;
		
		case "mtraxx_16":
			//pchar.quest.Mtraxx_SilkPayLate.over = "yes";
            dialog.text = "Ahí estás, "+pchar.name+". Hablemos de tu recompensa.";
			link.l1 = "¡Me gustan las charlas como esta, ja-ja-ja! Estoy todo oídos.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkLate")) link.l1.go = "mtraxx_19";
			else link.l1.go = "mtraxx_17";
		break;
		
		case "mtraxx_17":
            dialog.text = "Bald Geffrey ha vendido a tu comprador el primer lote de 105 rollos de seda de barco. Como esperaba venderlo por veinte doblones por rollo, creo que sería justo darte la diferencia. Esa es mi decisión. Tu parte es de 525 doblones más un bono: un doblón por rollo. Son 630 doblones en total. Aquí, tómalo.";
			link.l1 = "¡Gracias, Marcus!";
			link.l1.go = "mtraxx_18";
		break;
		
		case "mtraxx_18":
			TakeNItems(pchar, "gold_dublon", 630);
			Log_Info("Has recibido 630 doblones");
			PlaySound("interface\important_item.wav");
            dialog.text = "Una cosa más. Puedes obtener un beneficio extra de esto.";
			link.l1 = "Interesante... Continúa.";
			link.l1.go = "mtraxx_19";
		break;
		
		case "mtraxx_19":
            dialog.text = "Tu comprador quiere más de 100 rollos de seda para ser entregados en los próximos dos meses. Si tienes alguno, tráeme de 20 a 100 rollos por un precio de 24 doblones. La oferta estará vigente por dos meses.";
			link.l1 = "¡Está bien! Traeré más si tengo.";
			link.l1.go = "mtraxx_20";
			pchar.questTemp.Mtraxx.SilkTrade = "true";
			SetFunctionTimerCondition("Mtraxx_SilkTradeOver", 0, 0, 60, false);
		break;
		
		// торговля шелком
		case "mtraxx_silktrade":
			iTotalTemp = GetSquadronGoods(pchar, GOOD_SHIPSILK);
            dialog.text = "¿Cuánto tienes?";
			link.l1 = ""+FindRussianQtyString(iTotalTemp)+".";
			if (iTotalTemp > 100) link.l1.go = "mtraxx_silktrade_2";
			else link.l1.go = "mtraxx_silktrade_1";
		break;
		
		case "mtraxx_silktrade_1":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, iTotalTemp);
			TakeNItems(pchar, "gold_dublon", iTotalTemp*24);
            dialog.text = "Muy bien. Toma el oro - 24 doblones por una tirada como acordamos.";
			link.l1 = "¡Gratitud!";
			link.l1.go = "mtraxx_silktrade_3";
		break;
		
		case "mtraxx_silktrade_2":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 100);
			TakeNItems(pchar, "gold_dublon", 2400);
            dialog.text = "Me llevaré cien rollos. Toma el oro - 24 doblones por rollo como acordamos.";
			link.l1 = "¡Agradecimiento!";
			link.l1.go = "mtraxx_silktrade_3";
		break;
		
		case "mtraxx_silktrade_3":
            DialogExit();
			npchar.dialog.currentnode = "First time";
			DeleteAttribute(pchar, "questTemp.Mtraxx.SilkTrade");
		break;
		
		case "mtraxx_20":
            dialog.text = "Hablemos de algo más urgente, ¿quieres lidiar con algo peligroso?";
			link.l1 = "¡Claro! Mis hombres y yo estamos listos para zarpar de inmediato.";
			link.l1.go = "mtraxx_24";
		break;
		
		case "mtraxx_22":
            dialog.text = "Por el amor de Dios, "+pchar.name+", ¿dónde demonios has estado? ¿Recuerdas cuando te dije que vinieras a verme? Tenía un trabajo para ti y ahora está perdido gracias a tu excelente sentido del tiempo. Me has hecho enfadar mucho, chico. Piérdete, no trabajo con personas en las que no puedo confiar.";
			link.l1 = "Bueno, mierda...";
			link.l1.go = "mtraxx_23";
		break;
		
		case "mtraxx_23":
			DialogExit();
            npchar.dialog.currentnode = "First time";
			CloseQuestHeader("Roger_2");
			pchar.questTemp.Mtraxx = "fail";
		break;
		
		case "mtraxx_24":
			// belamour legendary edition даем флаг и лизензию ГВИК если отсутствует -->
			bOk = IsCharacterPerkOn(pchar,"FlagSpa") || IsCharacterPerkOn(pchar,"FlagHol");
			if(CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 40 && bOk) sTemp = ".";
			else 
			{
				if(bOk) 
				{
					if(!CheckCharacterItem(pchar, "HolTradeLicence") || GetDaysContinueNationLicence(HOLLAND) < 40) 
					{
						sTemp = ", así como una licencia comercial válida para 40 días."; 
						GiveNationLicence(HOLLAND, 40);
					}
				}
				else // нет флага
				{
					if(!CheckCharacterItem(pchar, "HolTradeLicence")) 
					{
						sTemp = ", así como una licencia de comercio para 40 días. Además, ¡¿cómo vas a engañar al vigía del fuerte?! Algún día me decepcionarás con tanta dejadez... Aquí tienes... Me la devolverás cuando llegues. La nuevas generación, pah ...";
						GiveNationLicence(HOLLAND, 40);
						SetCharacterPerk(pchar, "FlagSpa");
						log_info("Ha recibido la bandera española");
						pchar.questTemp.GiveMeSpaFlag = true;
					}
					else // есть лицензия
					{	
						if(GetDaysContinueNationLicence(HOLLAND) < 40) 
						{
							sTemp = ". Dime, ¿cómo vas a engañar al vigía del fuerte? Este documento no te ayudará sin la bandera correcta. Siento que algún día me decepcionarás con tanta dejadez... Toma, una licencia de comercio para 40 días, superior a la tuya. Así como la bandera española para desembarcar en Maracaibo. Me la devolverás al llegar. Las nuevas generaciones, pah...";
							GiveNationLicence(HOLLAND, 40);
							SetCharacterPerk(pchar, "FlagSpa");
							log_info("Ha recibido la bandera española");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
						else 
						{
							sTemp = ". Dime, ¿cómo vas a engañar al vigía del fuerte? Este papel no te ayudará sin la bandera correcta. Siento que algún día me decepcionarás con tanta dejadez... Aqui tienes... Me la devolverás cuando llegues. Las nuevas generaciones, pah...";
							SetCharacterPerk(pchar, "FlagSpa");
							log_info("Ha recibido la bandera española");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
					}
				}
			}
			// <-- legendary edition
            dialog.text = "Entonces escucha con atención. Hace dos meses tenía una cita con un capitán llamado Jean Picard, también conocido como Jean Handsome. No se presentó y como iba a discutir asuntos serios con él, hice algunas averiguaciones sobre su paradero. Resultó que nuestro valiente corsario y su bergantín se habían enzarzado en una pelea con un galeón pesado español al mando de don Eduardo de Losad y éste es un duro hijo de puta. Como resultado, Jean y lo que quedaba de su tripulación fueron llevados a Maracaibo y vendidos a la plantación. Allí es donde se encuentra, ocupado en trabajos honestos, en este momento.\nTus tareas son: Primero, investigar los detalles de sus desgracias y para a continuación, sacarlo vivo de la plantación y traerlo aquí. Realmente necesito conocer los detalles de su historia. Le asigno el capitán de un barquentine llamado 'Moray' para ayudarle en esto. El nombre del capitán es Paul Chant también conocido como Pelly el Cutlass. ¿Recuerdas a Geffrey? Es casi tan tonto como él, pero también es bueno luchando.\nTe estará esperando en cabo Ragget Point, en Barbados. Encuéntralo junto a su 'Moray' y navega hasta Maracaibo. Cutlass seguirá tus órdenes sin hacer preguntas estúpidas. En realidad, no hará preguntas en absoluto. Haz tu trabajo y vuelve aquí, te estaré esperando. Aquí hay diez mil pesos para gastos futuros "+sTemp+". ¿Alguna pregunta?";
			link.l1 = "No. Todo está claro. Rumbo a Barbados.";
			link.l1.go = "mtraxx_25";
		break;
		
		case "mtraxx_25":
			AddMoneyToCharacter(pchar, 10000);
            dialog.text = "Entonces, te deseo suerte. Sé rápido, no hagas esperar a Cutlass y al pobre Jean.";
			link.l1 = "¡Seguro, jefe! En camino.";
			link.l1.go = "mtraxx_26";
		break;
		
		case "mtraxx_26":
            DialogExit();
			CloseQuestHeader("Roger_2");
			npchar.dialog.currentnode = "mtraxx_wait";
			// belamour legendary edition по пути могут заскочить к Московиту, если рабов нет
			pchar.questTemp.Mtraxx.GiveMeSlaves = "Baster";
			AddQuestRecord("Roger_3", "1");
			AddLandQuestMark(characterFromId("Fadey"), "questmarkmain");
			AddMapQuestMarkCity("baster", false);
			Mtraxx_PlantBegin();
		break;
		
		case "mtraxx_27":
			pchar.quest.Mtraxx_PlantGoHomeOver.over = "yes"; 
            dialog.text = "¡Bienvenido de nuevo, mi valiente corsario, ja-ja! ¿Derribaste a un escuadrón español? Picard ya me lo ha contado. ¡Bien hecho!";
			link.l1 = "Sí, mis muchachos les dieron duro cuando navegábamos lejos de Maracaibo.";
			link.l1.go = "mtraxx_28";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup3"))
			{
				dialog.text = "¡Bienvenido de nuevo, mi valiente corsario, ja-ja! Picard ya me ha contado. ¡Bien hecho!";
				link.l1 = "...";
				link.l1.go = "mtraxx_28";
			}
		break;
		
		case "mtraxx_28":
            dialog.text = "Veo en tus ojos que estás esperando tu recompensa. Justo. Jean te pagará, después de todo, era su vida la que intentábamos salvar allí. Envíale la factura pero más tarde, el muchacho no tiene tripulación ni barco. Es un chico listo como tú, así que su situación actual no durará mucho.";
			link.l1 = "Mm... Bueno... Esperaré mi momento. ¿Algún trabajo para mí, Marcus? Sin salvar o buscar a nadie?";
			link.l1.go = "mtraxx_29";
		break;
		
		case "mtraxx_29":
            dialog.text = "¿Cansado de ser la vela más brillante? Tengo que decepcionarte: ya tengo suficientes brutos sin cerebro como Cutlass, tus talentos los usaré en consecuencia. Tendré un trabajo para ti en un mes, ahora deberías navegar hacia Isla Tesoro y ver a Pasquale Lavoisier, es un comerciante de Sharptown.\nPidió que le enviaran un pirata rudo lo antes posible para un asunto serio - probablemente lo que deseas: menos pensar y más disparar. Tienes una semana para presentarte ante él, así que no pierdas tiempo o perderás esta misión. Y sé educado, no intentes engañarlo, este hombre es respetado entre los Hermanos. Ahora ve y nos vemos en un mes. ¡No llegues tarde!";
			link.l1 = "Bien, Marcus. ¡Nos vemos!";
			link.l1.go = "mtraxx_30";
		break;
		
		case "mtraxx_30":
            DialogExit();
			// belamour legendary edition забрать флаг обратно
			if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
			{
				DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
				DeleteAttribute(pchar,"perks.list.FlagSpa"); 
				log_info("Has entregado una bandera española");
			}
			CloseQuestHeader("Roger_3");
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_4", "1");
			pchar.questTemp.Mtraxx = "pasq_start";
			Mtraxx_PasqualeBegin();
			SetFunctionTimerCondition("Mtraxx_PlantFithTaskTimer", 0, 0, 35, false);
			SaveCurrentNpcQuestDateParam(npchar, "task_date");
		break;
		
		case "mtraxx_31":
            dialog.text = "¡Guau! ¡Un hombre muerto ha regresado! ¡Ya te habíamos enterrado, muchacho! Pero parece que aún estás vivo";
			link.l1 = "Como puedes ver, Marcus...";
			link.l1.go = "mtraxx_32";
		break;
		
		case "mtraxx_32":
            dialog.text = "Entonces, ¿por qué tardaste tanto en llegar a La Española desde Maracaibo? Ahora estás fuera de mi organización, chico. Me alegra mucho verte vivo, pero aquí ya no hay más trabajos para ti.";
			link.l1 = "¡Eh!.. Qué pena...";
			link.l1.go = "mtraxx_33";
		break;
		
		case "mtraxx_33":
            DialogExit();
            npchar.dialog.currentnode = "First time";
			pchar.questTemp.Mtraxx = "fail";
		break;
		
		case "mtraxx_34x":
            DialogExit();
            npchar.dialog.currentnode = "mtraxx_34";
		break;
		
		case "mtraxx_34":
			/*if (GetNpcQuestPastDayParam(npchar, "task_date") >= 35 && !bImCasual) // опоздал
			{
				dialog.text = "Maldita sea "+pchar.name+", ¿dónde has estado?! ¡Te dije que me vieras en un mes! ¡Esto no es el ejército, pero se espera algo de maldita disciplina! ¡Piérdete, no trabajaré más contigo!";
				link.l1 = "Como desees...";
				link.l1.go = "mtraxx_33";
				break;
			}*/
			if (GetNpcQuestPastDayParam(npchar, "task_date") < 28) // рано пришёл
			{
				dialog.text = ""+pchar.name+", te dije 'vuelve a verme en un mes'. No tengo tiempo para ti ahora mismo.";
				link.l1 = "Bien...";
				link.l1.go = "mtraxx_34x";
				break;
			}
			if (pchar.questTemp.Mtraxx == "pasq_angry")
			{
				dialog.text = "Un agente de Lavoisier me dijo que lo habías jodido con su madera negra. Te advertí que no fueras una rata y que fueras justo con Pasquale. Has roto ambas de mis reglas. Eres un chico listo, pero esto es inaceptable. Lárgate de aquí y olvida el camino a este lugar.";
				link.l1 = "Mierda...";
				link.l1.go = "AngryExitAgainWithOut";
				pchar.questTemp.Mtraxx = "fail";
				npchar.dialog.currentnode = "First time";
				CloseQuestHeader("Roger_4");
				break;
			}
			if (pchar.questTemp.Mtraxx == "pasq_fail")
			{
				dialog.text = "Un agente de Lavoisier me dijo que le jodiste con su madera negra - no trajiste todo el lote. Si hubiera sido un Cutlass o Bald sin cerebro, tal vez habría creído que realmente no capturaron toda la carga, pero un chico tan listo como tú... ¿Decidiste engañar a Pasquale? ¡Te pedí que 'no lo engañaras'! Ya no tengo confianza en ti, y tampoco tengo más negocios contigo. ¡Lárgate de aquí y olvida el camino a este lugar!";
				link.l1 = "¡Tu Lavoisier es un maldito traidor!";
				link.l1.go = "AngryExitAgainWithOut";
				pchar.questTemp.Mtraxx = "fail";
				npchar.dialog.currentnode = "First time";
				CloseQuestHeader("Roger_4");
				break;
			}
			if (pchar.questTemp.Mtraxx == "pasq_late" || pchar.questTemp.Mtraxx == "pasq_sink" || pchar.questTemp.Mtraxx == "pasq_esc")
			{
				pchar.questTemp.Mtraxx.CharleePrince = "true"; // атрибут - ГГ известный пират // правки прогона 3
				dialog.text = "¡Ja! ¡Charlie Prince, un valiente capitán! Es tu nuevo nombre en La Vega por si no lo sabías. Entonces, ¿disfrutaste ser un bruto? ¿No? ¿La Dama Fortuna te ha dado la espalda esta vez? Así es como viven mis agentes descerebrados como Cutlass: hoy se divierte en un burdel, malgastando todo lo que ganó, y en una semana está en mi puerta suplicando por un par de miles para pagar a su tripulación llena de idiotas, igual que él. Lo que sea. ¿Hablemos de negocios?";
				link.l1 = "¡Por supuesto!";
				link.l1.go = "mtraxx_36";
				break;
			}
            dialog.text = "¡Ja! ¡Charlie Prince, un valiente capitán! ¡Ja-ja! Un agente de Lavoisier me dijo que lo hiciste bien. Me alegra que hayas logrado mostrar algo de respeto a nuestro usurero.";
			link.l1 = "No le vendría mal ser más generoso...";
			link.l1.go = "mtraxx_35";
		break;
		
		case "mtraxx_35":
			pchar.questTemp.Mtraxx.Pasquale.Continue = "true"; // правки прогона 3
            dialog.text = "¿Recuerdas lo que dije sobre los brutos descerebrados y los compradores de bienes robados? Correcto. Nunca aceptes un trabajo como este en el futuro. Déjaselo a Cutlass y a gente como él. Lo que sea. ¿Hablemos de negocios?";
			link.l1 = "¡Claro!";
			link.l1.go = "mtraxx_36";
		break;
		
		case "mtraxx_36":
            dialog.text = "¡Estupendo! Jean Picard viene aquí, te contará más. Tú y Jean trabajaréis juntos en esta misión. Además, es su oportunidad para saldar su deuda contigo... ¡Ahí está!";
			link.l1 = "...";
			link.l1.go = "mtraxx_37";
		break;
		
		case "mtraxx_37":
            DialogExit();
            npchar.dialog.currentnode = "mtraxx_38";
			chrDisableReloadToLocation = true;
			// преобразуем Пикара
			sld = characterFromId("Mrt_Rocur");
			sld.model = "Jan_Pikar";
			SetCharacterPerk(sld, "SwordplayProfessional");
			SetCharacterPerk(sld, "GunProfessional");
			RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
			GiveItem2Character(sld, "blade_17");
			EquipCharacterbyItem(sld, "blade_17");
			GiveItem2Character(sld, "pistol6");
			EquipCharacterbyItem(sld, "pistol6");
			TakeNItems(sld, "cartridge", 40);
			LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "cartridge");
			GiveItem2Character(sld, "cirass7");
			EquipCharacterbyItem(sld, "cirass7");
			sld.dialog.currentnode = "rocur_29";
			sld.greeting = "Rocur_03";
			Characters_RefreshModel(sld);
			LAi_SetCheckMinHP(sld, 10, true, "");
			TakeNItems(sld, "potion2", 7);
			TakeNItems(sld, "potion3", 7);
			TakeNItems(sld, "potion4", 7);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "mtraxx_38":
            dialog.text = "Mi hombre se unirá a tu incursión. Se llama Luka Bayard, más conocido como Luke Leprechaun. Él y sus hombres son bucaneros, cazadores que pasaron la mayor parte de sus vidas cazando en los bosques de La Española. Así que son maestros en atravesar la jungla. Añade a ellos tus combatientes y considera Mérida tuya. Te llevarás la tercera parte del botín. El resto será tomado por Jean. Jean, entregarás tu deuda a este valiente capitán de tu parte y luego me traerás lo que quede. Lo resolveremos entre nosotros entonces. ¿Preguntas? ¡Espléndido! Leprechaun te estará esperando en nuestro puerto. Buena suerte, corsarios, ¡ja-ja!";
			link.l1 = "...";
			link.l1.go = "mtraxx_39";
		break;
		
		case "mtraxx_39":
            DialogExit();
			CloseQuestHeader("Roger_4");
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_5", "1");
			pchar.questTemp.Mtraxx = "merida_start";
			Mtraxx_MeridaBegin();
			LAi_SetHuberType(npchar);
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "Mtraxx_MeridaAddPicar", 5.0);
			pchar.GenQuest.HunterLongPause = true;
		break;
		
		case "mtraxx_40":
            dialog.text = "¡Bienvenido de nuevo, mi valiente sanguinario! Los rumores de tu incursión ya nos han llegado.";
			link.l1 = "No puedo decir que me guste escucharlo. Esas cosas es mejor que permanezcan desconocidas...";
			link.l1.go = "mtraxx_41";
		break;
		
		case "mtraxx_41":
            dialog.text = "Confía en mí, nunca lo son, amigo mío. Lo que sea. ¿Picard saldó su deuda contigo?";
			link.l1 = "Sí.";
			link.l1.go = "mtraxx_42";
		break;
		
		case "mtraxx_42":
            dialog.text = "Muy bien. ¿Luke Leprechaun te causó una buena impresión?";
			link.l1 = "Lo hizo.";
			link.l1.go = "mtraxx_43";
		break;
		
		case "mtraxx_43":
            dialog.text = "Perfecto entonces. Todos están felices, todos están pagados.";
			link.l1 = "¿Tienes un trabajo para mí, Marcus?";
			link.l1.go = "mtraxx_44";
			// belamour legendary edition отказ после событий Мериды
			link.l2 = "Sabes, Marcus, he sopesado todo y este trabajo no es para mí. Lo siento, pero ya he tomado una decisión.";
			link.l2.go = "mtraxx_44a";
		break;
		
		case "mtraxx_44":
            dialog.text = "Aún no hay un trabajo real. Aunque tengo un favor personal que pedir. ¿Interesado?";
			link.l1 = "Claro, jefe. ¿Qué favor?";
			link.l1.go = "mtraxx_45";
		break;
		
		case "mtraxx_45":
            dialog.text = "Hay una pinaza 'Kittie' cerca de las costas de La Vega. Ha estado allí durante días esperando una escolta hasta Bridgetown. No voy a dejar que navegue sola hasta allí por razones obvias. ¿Serías tan amable de acompañarla? Tendré un trabajo de verdad para ti cuando regreses. Y, por supuesto, dinero para pagarte por esta escolta.";
			link.l1 = "Trato.";
			link.l1.go = "mtraxx_46";
		break;
		
		case "mtraxx_46":
            dialog.text = "¡Genial! Buena navegación.";
			link.l1 = "¡Gracias!";
			link.l1.go = "mtraxx_47";
		break;
		
		case "mtraxx_47":
            DialogExit();
			sld = characterFromId("Mrt_Rocur");
			RemovePassenger(pchar, sld);
			sld = characterFromId("Lepricon");
			RemovePassenger(pchar, sld);
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "none", "", "");
			CloseQuestHeader("Roger_5");
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_6", "1");
			pchar.questTemp.Mtraxx = "ignasio_start";
			sld = characterFromId("Mtr_KittyCap");
			DeleteAttribute(sld, "DontDeskTalk");
			LocatorReloadEnterDisable("LaVega_port", "boat", false);
		break;
		// belamour legendary edition -->
		case "mtraxx_44a":
            dialog.text = "¿Qué?! ¡Te saqué de la calle, llené tus bolsillos de ámbar y gemas! ¿Así es como me lo pagas?";
			link.l1 = "Merida me mostró que no soy lo suficientemente despiadado para este trabajo. No tan despiadado como tú y tus muchachos. No seas malvado.";
			link.l1.go = "mtraxx_45a";
		break;
		
		case "mtraxx_45a":
            dialog.text = "¡Debilucho! ¡Pues, piérdete! ¡Ve a cargar fletes o, mejor aún, emborráchate hasta morir como el resto de los perdedores!";
			link.l1 = "...";
			link.l1.go = "mtraxx_46a";
		break;
		
		case "mtraxx_46a":
            DialogExit();
			sld = characterFromId("Mrt_Rocur");
			RemovePassenger(pchar, sld);
			sld = characterFromId("Lepricon");
			RemovePassenger(pchar, sld);
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "none", "", "");
			CloseQuestHeader("Roger_5");
			npchar.dialog.currentnode = "First time";
			Group_DelCharacter("Mtr_Kitty", "Mtr_KittyCap");
			sld = characterFromId("Mtr_KittyCap");
			sld.lifeday = 0;
			LocatorReloadEnterDisable("LaVega_port", "boat", false);
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.questTemp.Mtraxx = "fail";
			if(CheckAttribute(pchar, "GenQuest.HunterLongPause")) DeleteAttribute(pchar, "GenQuest.HunterLongPause");
			DoQuestReloadToLocation("LaVega_town", "reload", "reload6", ""); // выставим за дверь
		break;
		// <--- legendary edition
		case "mtraxx_48":
			AddMoneyToCharacter(pchar, 10000);
            dialog.text = "Ah, ahí estás... Ya te estaba esperando. Aquí tienes 10.000 por escoltar al 'Kittie'.";
			link.l1 = "Gracias... Tengo algo que discutir contigo, Marcus.";
			link.l1.go = "mtraxx_49";
		break;
		
		case "mtraxx_49":
            dialog.text = "¿Lo haces? ¡Ja-ja! ¡Dispara!..";
			link.l1 = "¿Recuerdas cómo Jean Picard fue esclavizado? Primero saqueó una caravana holandesa junto con un corsario británico y luego le hicieron lo mismo a él con un galeón español pesado.";
			link.l1.go = "mtraxx_50";
		break;
		
		case "mtraxx_50":
            dialog.text = "Recuerda. ¿Y?";
			link.l1 = "Se me acercó Ignacio Marco en Bridgetown. El mismo corsario portugués que sirve a Inglaterra. Me ofreció saquear una caravana holandesa cerca de las costas de una isla deshabitada entre Curazao y Trinidad.";
			link.l1.go = "mtraxx_51";
		break;
		
		case "mtraxx_51":
            dialog.text = "Bueno-bueno... ¿Estuviste de acuerdo?";
			link.l1 = "Lo hice. Primero, fue un buen trato. En segundo lugar, recordé la historia de Picard y decidí investigar...";
			link.l1.go = "mtraxx_52";
		break;
		
		case "mtraxx_52":
            dialog.text = "Apuesto a que lo hiciste.";
			link.l1 = "Sí. Había una caravana, hicimos el trabajo bien y limpio. Luego dividimos el botín en la orilla, pero primero envié en silencio a un vigía con un catalejo a una colina. Y valió la pena, ya que poco después apareció una escuadra española liderada por un galeón pesado.";
			link.l1.go = "mtraxx_53";
		break;
		
		case "mtraxx_53":
            dialog.text = "¿Tu socio seguramente huyó para que los españoles te persiguieran?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.LosadaSink")) 
			{
				link.l1 = "Exactamente. Ni siquiera le prestaron atención. Mala suerte para ellos: luchamos contra los españoles tan ferozmente que nunca lo olvidarán. Estos castellanos eran buenos combatientes, pero logramos derribar a toda la escuadra.";
				link.l1.go = "mtraxx_53x";
			}
			else
			{
				link.l1 = "Exactamente. Ni siquiera le prestaron atención. Aunque logré escapar. Gracias a mi vigía...";
				link.l1.go = "mtraxx_53y";
			}
		break;
		
		case "mtraxx_53x":
			DeleteAttribute(pchar, "questTemp.Mtraxx.LosadaSink");
            dialog.text = "¡Heh! ¡Derribar un escuadrón de Eduardo de Losad! ¡Eres un Demonio del Mar, Príncipe! Apuesto a que los españoles ya han enviado cazadores tras tu trasero.";
			link.l1 = "Mal para ellos... Sin embargo, debemos tratar con esa escoria Ignacio. Si sabes a qué me refiero.";
			link.l1.go = "mtraxx_54";
		break;
		
		case "mtraxx_53y":
            dialog.text = "¡Je! ¡Puedo imaginarme el caos que ocurrió cuando los castellanos se dieron cuenta de que te habías escapado de ellos! ¡Bien hecho!";
			link.l1 = "Su problema, no el mío. No obstante, deberíamos ocuparnos de esta escoria, Ignacio. Si entiendes lo que quiero decir.";
			link.l1.go = "mtraxx_54";
		break;
		
		case "mtraxx_54":
            dialog.text = "Me encargaré de ello. Deberíamos aprender más sobre este Ignacio Marco. Podría estar trabajando para alguien. Su 'interés' en mis hombres es sospechoso. ¿Qué barco posee?";
			link.l1 = "Un polacra, el 'Torero'. Un navío único, debe ser un diseño original.";
			link.l1.go = "mtraxx_55";
		break;
		
		case "mtraxx_55":
            dialog.text = "Bien, más fácil seguirle la pista entonces... Lo tengo. Y para ti, Príncipe, tengo un trabajo. ¿Listo para ello?";
			link.l1 = RandSwear()+"¡Por supuesto, jefe!";
			link.l1.go = "mtraxx_56";
		break;
		
		case "mtraxx_56":
            dialog.text = "Escucha entonces. Hace algún tiempo tuvimos un pirata curioso en nuestra región. Se llama Wulfric Iogansen, también conocido como Lobo Rojo. Un personaje muy pintoresco. Vino aquí desde el norte de Europa hace un par de años. Este vikingo no le pagaba a Levasseur su tarifa de protección, no hacía amigos y se mantenía solo. Un tipo muy reservado, nadie había dejado su tripulación con vida. Había rumores de que él mismo cortaba las lenguas de aquellos en su tripulación cuyas lenguas se soltaban en las tabernas hablando de sus incursiones... A diferencia de la mayoría de los nuestros, Wulfric nunca desperdició dinero en putas o bebidas. Nunca vendió su botín por centavos. Nunca confió en los banqueros y nunca cambió de barcos. Tenía una buena corbeta, la 'Freyja' y una tripulación leal a la que pagaba bien por servir y por guardar silencio. Creo que estaba planeando acumular tanto oro como fuera posible y luego regresar a Europa y vivir allí como un rey. No le salió bien gracias a los cazadores españoles. Este hombre había infligido un daño colosal y pérdidas a España, por lo que expediciones punitivas lo cazaron dentro de las aguas de La Española y hundieron el 'Freyja' y mataron a toda la tripulación junto con el Lobo. Rodeado en aguas poco profundas por los barcos españoles, Lobo Rojo encontró su muerte. La cosa es que todos en La Vega sabían sobre los tesoros del Lobo e incluso encontraron un 'Freyja' hundido, pero ni los buzos locales ni los indios encontraron tesoros. No era un tonto y debía tener un gran escondite en algún lugar de esa ubicación que solo él y su tripulación conocían, pero no podemos preguntarles por... razones obvias. Pero ahora viene la parte interesante: tengo su diario de navegación intacto, que estaba escondido en el cofre cerrado de su barco. No tiene pistas obvias sobre el tesoro, pero puedes intentar encontrarlas entre las palabras. Lee el diario, averigua dónde el vikingo escondió sus tesoros después de dos años de robo en el Caribe y encuéntralos. Si tienes éxito, dos tercios son tuyos. ¿Aceptas?";
			link.l1 = "Mm... suena como buscar un gato negro en una habitación oscura. ¿Dónde está el registro?";
			link.l1.go = "mtraxx_57";
		break;
		
		case "mtraxx_57":
            dialog.text = "Aquí, tómalo. ¡Buena suerte!";
			link.l1 = "Gracias, lo voy a necesitar...";
			link.l1.go = "mtraxx_58";
		break;
		
		case "mtraxx_58":
            DialogExit();
			CloseQuestHeader("Roger_6");
			npchar.dialog.currentnode = "mtraxx_wait";
			GiveItem2Character(pchar, "wolfreeks_book");
			AddQuestRecord("Roger_7", "1");
			pchar.questTemp.Mtraxx = "wolfreek_start";
			pchar.questTemp.Mtraxx.Logbook.CanRead = "true";
			pchar.questTemp.Mtraxx.Logbook.Page1 = "true";
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
		break;
		
		case "mtraxx_59":
            dialog.text = "Ah, ahí está nuestro valiente capitán. ¿Qué hay de los tesoros de Lobo Rojo?";
			link.l1 = "Estoy trabajando en ello. Necesito tu ayuda en esto.";
			link.l1.go = "mtraxx_60";
		break;
		
		case "mtraxx_60":
            dialog.text = "Soy todo oídos.";
			link.l1 = "Hay una palabra desconocida para mí escrita varias veces en el diario de Wulfric 'Gord'. Debo conocer su significado para avanzar en mi investigación.";
			link.l1.go = "mtraxx_61";
		break;
		
		case "mtraxx_61":
            dialog.text = "Hm... Gord dices... Nunca lo había oído antes tampoco. Muy bien, ven a verme en una semana: consultaré con algunos cerebritos que sirven como intendentes en los barcos. Al menos saben contar y leer. Puede que nos den alguna idea.";
			link.l1 = "Está bien, Marcus. Nos vemos en una semana entonces.";
			link.l1.go = "mtraxx_62";
		break;
		
		case "mtraxx_62":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			SetFunctionTimerCondition("Mtraxx_WolfreekTimer", 0, 0, 7, false);
		break;
		
		case "mtraxx_63":
            dialog.text = "Tengo una respuesta para ti. Un listillo me ha iluminado. Gord es un asentamiento fortificado de un jarl libre.";
			link.l1 = "¿Un jarl libre? ¿Quién es ese?";
			link.l1.go = "mtraxx_64";
		break;
		
		case "mtraxx_64":
            dialog.text = "Algún tipo de almirante pirata de vikingos. Por ejemplo, yo soy un jarl libre y La Vega es mi gorda. ¡Parece que Lobo Rojo disfrutó de la historia de sus antepasados, ja-ja! ¿Te ayudó esta información?";
			link.l1 = "No lo sé todavía. Primero debería comparar las notas. Gord significa asentamiento entonces... ¡Gracias Marcus!";
			link.l1.go = "mtraxx_65";
		break;
		
		case "mtraxx_65":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			Mtraxx_WolfreekReadLogbookFourth();
		break;
		
		case "mtraxx_66":
            dialog.text = "¿Y bien? Tu cara de suficiencia me dice que tuviste éxito.";
			link.l1 = "Sí. ¡Se encontró el tesoro del Lobo Rojo! Aunque no fue fácil.";
			link.l1.go = "mtraxx_67";
		break;
		
		case "mtraxx_67":
            dialog.text = "¿Cuánto ocultó nuestro vikingo?";
			link.l1 = "750.000 pesos y 900 doblones.";
			link.l1.go = "mtraxx_68";
		break;
		
		case "mtraxx_68":
            dialog.text = "¡Jo-jo! Lo hiciste bien, Príncipe. ¿Y mi parte?";
			if (sti(pchar.money) >= 250000 && PCharDublonsTotal() >= 300) // belamour legendary edition
			{
				link.l1 = "Aquí, toma esto. Según nuestro acuerdo: 250 000 pesos y 300 doblones.";
				link.l1.go = "mtraxx_69";
			}
			else
			{
				link.l1 = "¡Todos los pesos y doblones están en mi camarote! ¡Dame un minuto para traerlos aquí!";
				link.l1.go = "mtraxx_68_1";
			}
		break;
		
		case "mtraxx_68_1":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_68_2";
		break;
		
		case "mtraxx_68_2":
            dialog.text = "¿Trajiste mi parte?";
			if (sti(pchar.money) >= 250000 && PCharDublonsTotal() >= 300) // belamour legendary edition
			{
				link.l1 = "Aquí, toma esto. Según nuestro acuerdo: 250 000 pesos y 300 doblones.";
				link.l1.go = "mtraxx_69";
			}
			else
			{
				link.l1 = "Sí-sí, ¡voy en camino!";
				link.l1.go = "mtraxx_68_1";
			}
		break;
		
		case "mtraxx_69":
			AddMoneyToCharacter(pchar, -250000);
			RemoveDublonsFromPCharTotal(300); // belamour legendary edition
			PlaySound("interface\important_item.wav");
            dialog.text = "Muy bien. Lo hiciste de nuevo. ¡Bien hecho!";
			link.l1 = "Marcus, ¿descubriste algo sobre Ignacio Marco?";
			link.l1.go = "mtraxx_70";
			// mitrokosta возможность отстройки исламоны
			pchar.questTemp.IslaMona = "start";
		break;
		
		case "mtraxx_70":
            dialog.text = "Sí, pero necesito verificarlo primero...";
			link.l1 = "¿Qué?";
			link.l1.go = "mtraxx_71";
		break;
		
		case "mtraxx_71":
            dialog.text = "Tengo la sospecha de que Marco está conectado con alguien... Y necesito que lo averigües. Navega a Martinica. Deja tu barco en Saint-Pierre y llega a Le Francois a través de la jungla. Me dijeron que han visto a nuestro hombre allí. No preguntes a los piratas, solo observa y vigila. Una vez que encuentres al tipo, síguelo y ve a dónde va o con quién se encuentra. ¡No lo ataques a él o a su barco porque al hacerlo arruinarías un plan que estoy preparando ahora mismo! ¡Te lo he advertido!\nSíguelo y obsérvalo, regresa una vez que hayas aprendido lo suficiente. Entiendo que tus manos están deseando estrangular al bastardo, pero mantén la calma. Ahora vete. Tienes tres semanas. Buena suerte.";
			link.l1 = "En camino, jefe.";
			link.l1.go = "mtraxx_72";
		break;
		
		case "mtraxx_72":
            DialogExit();
			CloseQuestHeader("Roger_7");
			RemoveItems(pchar, "wolfreeks_book", 1);
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_8", "1");
			pchar.questTemp.Mtraxx = "corrida_start";
			pchar.quest.mtraxx_corrida_martinique.win_condition.l1 = "location";
			pchar.quest.mtraxx_corrida_martinique.win_condition.l1.location = "Martinique";
			pchar.quest.mtraxx_corrida_martinique.function = "Mtraxx_CorridaStart";
			pchar.quest.mtraxx_pasq_continue.win_condition.l1 = "location";
			pchar.quest.mtraxx_pasq_continue.win_condition.l1.location = "LaVega_exittown";
			pchar.quest.mtraxx_pasq_continue.function = "Mtraxx_PasqualeJan";
			bDisableFastReload = true;
			//SaveCurrentNpcQuestDateParam(npchar, "task_date");
		break;
			
		case "mtraxx_73":
			/*if (GetNpcQuestPastDayParam(npchar, "task_date") >= 22) // опоздал
			{
				dialog.text = "¡Maldita sea, Príncipe! Podrías haber tenido venganza y una suma infernal de dinero si no fueras tan lento. ¡No esperaba esto de ti, pero como eres un buen chico, te perdono. Tendrás la oportunidad de recuperar tu reputación a mis ojos en un mes. ¡Estoy reuniendo a todos para un saqueo!\nVen a mí en un mes en un solo barco, pero poderoso. Luke, Cutlass, Geffrey y Jean también participarán en esto. ¡No llegues tarde, ni siquiera un día!";
				link.l1 = "Entiendo Marcus. ¡No volverá a suceder!";
				link.l1.go = "mtraxx_73x";
				break;
			}*/
			dialog.text = "¡Buen momento! Infórmame ahora.";
			link.l1 = "He rastreado a mi deudor en Le Francois. Su polacra formaba parte de un escuadrón compuesto por una corbeta y una fragata. Marco en persona fue a visitar a Barbaszon, tuvieron una reunión en su lugar durante dos horas, otros visitantes fueron despachados por sus guardias. Luego salió de la casa con dos tipos sombríos: uno era pelirrojo y barbudo con una coraza de reiter, el otro tenía bigote y llevaba una armadura pesada de trincheras. Todos se dirigieron al puerto y zarparon antes de que yo llegara a Saint-Pierre.";
			link.l1.go = "mtraxx_74";
		break;
		
		/*case "mtraxx_73x":
            DialogExit();
            npchar.dialog.currentnode = "First time";
			pchar.questTemp.Mtraxx = "wait_month";
			AddQuestRecord("Roger_8", "5");
			SetFunctionTimerCondition("Mtraxx_CartahenaTavernPrepare", 0, 0, 1, false); // belamour legendary edition увеличим таймер 
			SetFunctionTimerCondition("Mtraxx_CartahenaPrepare", 0, 0, 1, false);
			SetFunctionTimerCondition("Mtraxx_CartahenaLate", 0, 0, 92, false);
		break;*/
		
		case "mtraxx_74":
            dialog.text = "Está bien. Ahora veo todo el panorama. Esos dos bastardos que viste trabajan para Barbazon o para Jackman. Son casi como mi Calvo y Sable, pero ellos pelean mejor. El pelirrojo se llama Merodeador, es el capitán del 'Sepia', un corbeta, y el tipo con el bigote es Espectro, navega en el 'Despiadado', una fragata. En cuanto a nuestro amigo Ignacio, él trabaja no solo para los británicos y el español don Losad, sino también para Barbazon. Por eso trató de incriminarte a ti y a Picard.";
			link.l1 = "¿Por qué?";
			link.l1.go = "mtraxx_75";
		break;
		
		case "mtraxx_75":
            dialog.text = "La orden de Barbazon. No sabías, pero Jacques nunca pierde la oportunidad de mear en mi gachas. Nunca se opondría abiertamente a mí por razones obvias, así que me traiciona en secreto. Sabía que Picard y tú sois mis hombres. Enviarte a su mercenario era su estilo y no envió a un idiota, como te has asegurado.";
			link.l1 = "Iré a visitar a Barbazón tan pronto como me encargue de Marco...";
			link.l1.go = "mtraxx_76";
		break;
		
		case "mtraxx_76":
            dialog.text = "¡Sácate esa mierda de la cabeza! No tienes ninguna oportunidad contra Barbazon en un conflicto abierto. Él te joderá fácilmente. Le pagaremos con su propia astucia, atacando a sus asociados. ¿Listo para eso? Es un asunto sucio.";
			link.l1 = "¡Suena como mi tipo de negocio!";
			link.l1.go = "mtraxx_77";
		break;
		
		case "mtraxx_77":
            dialog.text = "Ignacio Marco, Merodeador, Goul y otro tipo de Barbazon llamado Joker Jim tienen un plan para capturar uno de los barcos españoles de la Flota de Oro. Toda la operación fue diseñada por el propio Barbazon y he logrado averiguar los detalles a través de mis espías. Un galeón pesado de la flota de oro se retrasó en La Habana en el astillero, mientras toda la escuadra partió hacia España. El galeón fue reparado y pronto se dirigirá a Europa, junto con otros dos barcos. La escuadra irá de Cuba al noreste, pero no sé qué ruta tomará.\nHe sido informado de que los barcos españoles iban a navegar hacia Santo Domingo, luego a lo largo de las costas de Puerto Rico y directamente al océano. Barbazon también sabe esto. Sin embargo, dado que La Española se puede rodear no solo por el sur, sino también por el norte, cambiando la ruta y saliendo al océano a través de los Turcos o Isla-Tesoro, sin entrar en Santo Domingo, Jacques decidió jugar a lo seguro y envió al astuto zorro Ignacio a Cuba.\nMarco tiene la tarea de obtener un horario de navegación del galeón español que va a zarpar de Cuba y se supone que alcanzará al resto de la Flota más tarde. Tiene conexiones dentro de los españoles, así que esta tarea no será un problema para él. El resto de la banda de Barbazon está esperando a Marco en San Martín, que es un lugar óptimo para comenzar a cazar este premio. Dado que Marco y los holandeses no son muy buenos amigos, no podrá entrar en las aguas de San Martín, así que tendrá que enviar un mensaje distante a sus compañeros...";
			link.l1 = "Supongo que sé lo que se supone que debo hacer aquí...";
			link.l1.go = "mtraxx_78";
		break;
		
		case "mtraxx_78":
            dialog.text = "Me parece que eres muy listo, pero aún no he terminado. He interferido en este plan con la ayuda de Gabriela Chapada. La conoces. Juntos informamos a los españoles que la emboscada pirata se establecerá no lejos de Puerto Rico. Así que el galeón no navegará por esa área, pero en secreto enviaron allí un escuadrón de cazadores de piratas. Tienes varias tareas. La primera será encontrar y capturar el 'Torero'. Supongo que sabes qué hacer con su capitán.";
			link.l1 = "Naturalmente...";
			link.l1.go = "mtraxx_79";
		break;
		
		case "mtraxx_79":
            dialog.text = "En segundo lugar, tendrás que averiguar el rumbo real del galeón de oro español. Marco debe tener su itinerario. Consíguelo y envíamelo.";
			link.l1 = "¿Cómo?";
			link.l1.go = "mtraxx_80";
		break;
		
		case "mtraxx_80":
			GiveItem2Character(pchar, "Dove"); 
            dialog.text = "Por aire. Toma una jaula... Este es Spyke, un palomo mensajero nacido y criado aquí, en La Vega. Siempre encontrará el camino de regreso, incluso desde Trinidad. Una vez que obtengas el horario, escribe una nota, pégala a su pata y suéltalo. Spyke volará hacia mí en unas pocas horas. ¡Cuídalo, Príncipe!";
			link.l1 = "¡Por supuesto, jefe!";
			link.l1.go = "mtraxx_81";
		break;
		
		case "mtraxx_81":
            dialog.text = "Tercero, navega a San Martín en el 'Torero'. ¡Solo en ella! De lo contrario, se pondrán sospechosos demasiado pronto. Envíales una señal para navegar a Puerto Rico, donde los españoles esperan. Sus códigos de señales deben estar en los papeles de Marco. O puedes aprenderlos de él personalmente.";
			link.l1 = "Ya veo. ¡Una jugada inteligente enviar a los hombres de Barbazon a los españoles, ja-ja!";
			link.l1.go = "mtraxx_82";
		break;
		
		case "mtraxx_82":
            dialog.text = "¡Exactamente! Le daré un golpe desde las sombras. Tal como él lo hizo. Y una última cosa: una vez que les envíes una señal, navega de inmediato para interceptar al galeón español y su escolta. No habrá tiempo que perder.";
			link.l1 = "¿En una polacra? ¿Contra un galeón pesado y dos barcos más, y ciertamente no son goletas? ¡Me destrozarán!";
			link.l1.go = "mtraxx_83";
		break;
		
		case "mtraxx_83":
            dialog.text = "¡Deja de llorar como una niña pequeña! ¿Por qué crees que me enviarás a Spyke? No te quedarás sin refuerzos. Solo no dejes que la caravana huya, no dejes que lleguen al océano. ¿Entendido?";
			link.l1 = "Sí, jefe.";
			link.l1.go = "mtraxx_84";
		break;
		
		case "mtraxx_84":
            dialog.text = "Tu recompensa será una gran carga de oro más la polacra de Marco. La gente dice que es un maldito buen barco. ¿Alguna pregunta? ¿Entiendes tu misión?";
			link.l1 = "No soy Cutlass, sé qué hacer. ¿Dónde debo interceptar el 'Torero'?";
			link.l1.go = "mtraxx_85";
		break;
		
		case "mtraxx_85":
            dialog.text = "Mientras estamos teniendo esta charla, el barco navega rápidamente hacia Philipsburg desde Cuba. Debe estar alrededor de Tortuga ahora o un poco al este de allí. Así que levanta anclas y navega hacia Saint Martin, alcanza el 'Torero' no lejos de la isla, solo no dejes que los hombres de Barbazon vean la pelea, de lo contrario mi plan se arruina.";
			link.l1 = "¡Enseguida!";
			// belamour legendary edition испанский флаг к выдаче -->
			if(IsCharacterPerkOn(pchar,"FlagSpa")) link.l1.go = "mtraxx_86";
			else link.l1.go = "mtraxx_85f";
		break;
		
		case "mtraxx_85f":
			SetCharacterPerk(pchar, "FlagSpa");
			log_info("Has recibido una bandera española");
			pchar.questTemp.GiveMeSpaFlag = true;
            dialog.text = "¿Qué demonios? Eso te rompería con un atizador de la chimenea, Príncipe. No pensé que tendría que hablar de cosas elementales. Sostén la bandera española, de lo contrario arruinarás todo, sin siquiera comenzar. Devuélvemela. ¡Ahora lárgate de aquí!";
			link.l1 = "Ya estoy en el mar, Jefe";
			link.l1.go = "mtraxx_86";
		break;
		// <-- legendary edition
		case "mtraxx_86":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			AddQuestRecord("Roger_8", "6");
			pchar.questTemp.Mtraxx = "corrida_marko";
			/*pchar.quest.mtraxx_corrida_landtimer.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.hour  = sti(GetTime()+1);
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.mtraxx_corrida_landtimer.function = "Mtraxx_CorridaLandTimer";
			pchar.quest.mtraxx_corrida_checktime.win_condition.l1 = "location";
			pchar.quest.mtraxx_corrida_checktime.win_condition.l1.location = "Hispaniola1";
			pchar.quest.mtraxx_corrida_checktime.function = "Mtraxx_CorridaCheckTime";*/
			pchar.quest.mtraxx_corrida_torero.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.hour  = sti(GetTime()+12);
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_corrida_torero.function = "Mtraxx_CorridaToreroOnMap";
			SetFunctionTimerCondition("Mtraxx_CorridaTimeFindTorero", 0, 0, 7, false); // время на перехват Тореро, снимать при потоплении или захвате
		break;
		
		case "mtraxx_87":
            dialog.text = "Así que Príncipe, lo echas todo a perder, ¿eh?";
			link.l1 = "Lo hice. Esta misión fue un desafío mucho mayor de lo que pensaba. Puedes darme un discurso enfurecedor y mostrarme la puerta.";
			link.l1.go = "mtraxx_88";
		break;
		
		case "mtraxx_88": // belamour legendary edition увеличиваем срок
            dialog.text = "Vamos, déjalo. Sucede. Eres un buen corsario y todos fallamos a veces. Lástima que no conseguimos ese oro... pero si no lo conseguimos en un lugar, lo conseguiremos en otro, ¡ja-ja! Tendrás la oportunidad de recuperar tu reputación: ven a verme en tres semanas, y preferiblemente en un barco más fuerte, pero solo en uno - seremos toda una escuadra. ¡Estoy reuniendo a todos para una incursión!\nLlega a mí en tres semanas en un solo pero poderoso barco. Luke, Cutlass, Geffrey y Jean también participarán en esto. ¡No llegues tarde!";
			link.l1 = "¡No lo haré, jefe!";
			link.l1.go = "mtraxx_89";
		break;
		
		case "mtraxx_89":
            DialogExit();
			// belamour legendary edition забрать флаг обратно
			if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
			{
				DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
				DeleteAttribute(pchar,"perks.list.FlagSpa"); 
				log_info("Has entregado una bandera española");
			}
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Mtraxx = "wait_month";
			AddQuestRecord("Roger_8", "22");
			SetFunctionTimerCondition("Mtraxx_CartahenaTavernPrepare", 0, 0, 1, false); // belamour legendary edition увеличим таймер 
			SetFunctionTimerCondition("Mtraxx_CartahenaPrepare", 0, 0, 1, false);
			//SetFunctionTimerCondition("Mtraxx_CartahenaLate", 0, 0, 92, false);
			if (CheckCharacterItem(pchar, "Dove")) RemoveItems(pchar, "Dove", 1);
		break;
		
		case "mtraxx_board":
            dialog.text = "¡Ho-ho, Ahoy, chiquillo! ¿No esperabas verme aquí, verdad? ¡Ja-ja-ja! Al fin hemos encontrado la caravana española...";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Gold")) // был абордаж
			{
				link.l1 = "Sí jefe, lo hemos hecho, aunque no fue fácil.";
				link.l1.go = "mtraxx_board_1";
			}
			else
			{
				link.l1 = "Sí, pero el galeón dorado se hundió con todo su oro.";
				link.l1.go = "mtraxx_board_7";
			}
		break;
		
		case "mtraxx_board_1":
			iTotalTemp = GetSquadronGoods(pchar, GOOD_GOLD);
            dialog.text = "¿Cuánto oro conseguimos, Príncipe?";
			if (iTotalTemp < 1) link.l1 = "Eh... Nada.";
			else link.l1 = "Heh... "+iTotalTemp+"¡en total!";
			link.l1.go = "mtraxx_board_2";
		break;
		
		case "mtraxx_board_2":
			if (iTotalTemp < 20)
			{
				dialog.text = "¡Maldita sea! Los españoles debieron lanzarlo al mar para que no lo consiguiéramos. Al menos lo pagaron. Lo mismo que los hombres de Barbazón, lo cual también es una victoria...";
				link.l1 = "Lo siento por el oro... ¿Qué sigue Marcus? ¿Vamos a La Vega?";
				link.l1.go = "mtraxx_board_4";
				AddQuestRecord("Roger_8", "18");
				break;
			}
			if (iTotalTemp >= 20 && iTotalTemp < 300)
			{
				dialog.text = "Patético. Ni siquiera compensa mi viaje aquí. Los españoles deben haberlo arrojado al mar para que no lo consiguiéramos. Al menos pagaron por ello. Al igual que los hombres de Barbazon, lo cual también es una victoria...";
				link.l1 = "Lo siento por el oro... Vamos a dividirlo de todos modos.";
				link.l1.go = "mtraxx_board_3";
				AddQuestRecord("Roger_8", "19");
				break;
			}
			if (iTotalTemp >= 300 && iTotalTemp < 700)
			{
				dialog.text = "Este es un pobre botín. Apenas suficiente para cubrir los gastos. Los españoles deben haber arrojado una parte al mar para que no lo consiguiéramos. Al menos lo pagaron. Al igual que los hombres de Barbazon, lo cual también es una victoria...";
				link.l1 = "Lo siento por el oro... Vamos a dividirlo de todas formas.";
				link.l1.go = "mtraxx_board_3";
				AddQuestRecord("Roger_8", "19");
				AddCharacterExpToSkill(pchar, "Fortune", 100);
				break;
			}
			if (iTotalTemp >= 700 && iTotalTemp < 1000)
			{
				dialog.text = "No está mal, aunque esperaba algo mejor. Los españoles debieron arrojar una parte al mar para que no la obtuviéramos. Al menos pagaron por ello. Al igual que los hombres de Barbazon, lo cual también es una victoria...";
				link.l1 = "¡Repartamos el premio!";
				link.l1.go = "mtraxx_board_3";
				AddQuestRecord("Roger_8", "20");
				AddCharacterExpToSkill(pchar, "Fortune", 200);
				break;
			}
			dialog.text = "¡Espléndido! ¡Conseguimos un buen botín, mi amigo! Y los hombres de Barbazon obtuvieron lo que merecían, ¡ja-ja!";
			link.l1 = "Je, ¡eso es un montón de oro! ¡Vamos a dividirlo!";
			link.l1.go = "mtraxx_board_3";
			AddQuestRecord("Roger_8", "21");
			AddCharacterExpToSkill(pchar, "Fortune", 300);
		break;
		
		case "mtraxx_board_3":
			RemoveCharacterGoods(pchar, GOOD_GOLD, makeint(iTotalTemp/2));
			WaitDate("", 0, 0, 0, 3, 10);
			LAi_Fade("", "");
            dialog.text = "... como siempre hacemos en la Hermandad - un corte justo para cada uno. Puedes quedarte con el 'Torero', es tu premio.";
			link.l1 = "¿Qué sigue Marcus? ¿Iremos a La Vega?";
			link.l1.go = "mtraxx_board_4";
		break;
		
		case "mtraxx_board_4": // belamour legendary edition увеличиваем срок до 3х месяцев
            dialog.text = "Definitivamente estaré en La Vega, te esperaré allí durante tres semanas. Ven cuando estés listo. Preferiblemente en un barco más fuerte, pero solo en uno - seremos toda una escuadra. Estoy poniendo a toda mi gente en marcha. Irás bajo mi mando, así como Jean Handsome, Geoffrey el Calvo, Pelly el Cuchillo y Luke el Duende. Prepárate. Nos espera una expedición seria y un botín bastante grande. Descubrirás todos los detalles más tarde.";
			link.l1 = "¡Está bien, jefe! Nos vemos en La Vega en tres semanas.";
			link.l1.go = "mtraxx_board_5";
		break;
		
		case "mtraxx_board_5":
            dialog.text = "¡Adiós, malandrín! ¡Ja-ja!";
			link.l1 = "...";
			link.l1.go = "mtraxx_board_6";
		break;
		
		case "mtraxx_board_6":
            DialogExit();
            npchar.dialog.currentnode = "mtraxx_board_6x";
			npchar.DeckDialogNode = "mtraxx_board_6x";
			npchar.DontDeskTalk = true;
			Ship_SetTaskRunAway(SECONDARY_TASK, sti(npchar.index), sti(pchar.index));
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.quest.mtraxx_corrida_complete.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_corrida_complete.function = "Mtraxx_CorridaComplete";
			RemoveItems(pchar, "wolfreeks_book", 1);
			// belamour legendary edition забрать флаг обратно
			if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
			{
				DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
				DeleteAttribute(pchar,"perks.list.FlagSpa"); 
				log_info("Has dado una bandera española");
			}
		break;
		
		case "mtraxx_board_6x":
            dialog.text = "¿Algo más?";
			link.l1 = "No, no lo creo. Ya voy a mi barco.";
			link.l1.go = "mtraxx_board_6y";
		break;
		
		case "mtraxx_board_6y":
            DialogExit();
			npchar.DeckDialogNode = "mtraxx_board_6x";
		break;
		
		case "mtraxx_board_7":
            dialog.text = "¡Je! ¿Y de quién es culpa eso, Príncipe? ¿Fue la tuya?";
			link.l1 = "Lamento, jefe, pero ambos fuimos bastante buenos... También hiciste un excelente trabajo disparando. Buen apunte, por cierto...";
			link.l1.go = "mtraxx_board_8";
		break;
		
		case "mtraxx_board_8":
            dialog.text = "Lo que sea. La culpa es de ambos. No obstante, no estamos con las manos vacías - los hombres de Barbazon obtuvieron lo que teníamos para ellos, una victoria en sí misma...";
			link.l1 = "Lo siento por el oro... ¿Qué sigue Marcus? ¿Vamos a La Vega?";
			link.l1.go = "mtraxx_board_4";
		break;
		
		case "mtraxx_90x":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_90";
		break;
		
		case "mtraxx_90":
			pchar.quest.Mtraxx_CartahenaLate.over = "yes";
			if (GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "Príncipe, ¿te has vuelto descerebrado? ¡Te dije que trajeras solo un barco! ¡Ve a deshacerte del extra y regresa lo antes posible! ¡Ahora!";
				link.l1 = "¡Está bien, está bien!";
				link.l1.go = "mtraxx_90x";
				break;
			}
			if (RealShips[sti(pchar.Ship.Type)].Type.Merchant) // торговые
			{
				dialog.text = "Príncipe, ¿has decidido ser mi segundo Alfanje? ¿Por qué me trajiste un barco mercante? ¡Contaba contigo! ¡Ve a traer un barco de guerra decente! ¡Ahora!";
				link.l1 = "¡Está bien, está bien!";
				link.l1.go = "mtraxx_90x";
				break;
			}
			if (sti(RealShips[sti(pchar.ship.type)].Class) > 3)
			{
				dialog.text = "Príncipe, me has sorprendido. ¡Te dije que trajeras un barco de guerra! ¿Cómo piensas ayudarme en esta bañera? ¡Vuelve aquí en un barco de tercer o segundo rango, ni menos ni más alto! ¡Ahora! No voy a esperar a nadie.";
				link.l1 = "¡Está bien, está bien!";
				link.l1.go = "mtraxx_90x";
				break;
			}
			if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
			{
				dialog.text = "Príncipe, ¿por qué no traes aquí al Soberano de los Mares? ¡Cuando te dije que trajeras un buque de guerra, no quise decir que trajeras una maldita nave de línea! ¡Vuelve aquí en un barco de tercera o segunda clase! ¡Ahora! No voy a esperar a nadie.";
				link.l1 = "¡Está bien, está bien!";
				link.l1.go = "mtraxx_90x";
				break;
			}
            dialog.text = "¡Buen momento, corsario! ¡Me alegra verte entero! ¿Listo para un viaje?";
			link.l1 = "Por supuesto, jefe. Siempre listo.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Barbazon")) link.l1.go = "mtraxx_91";
			else link.l1.go = "mtraxx_94";
		break;
		
		case "mtraxx_91":
            dialog.text = "Por cierto, ¿quieres saber sobre la escuadra de Barbazon que enviaste a Puerto Rico?";
			link.l1 = "Se me han escapado por completo de la mente. Claro que quiero. ¿Encontraron su perdición?";
			link.l1.go = "mtraxx_92";
		break;
		
		case "mtraxx_92":
            dialog.text = "¡Infiernos, sí lo hicieron! El buque insignia - la fragata 'Búho' de Joker Jim, se quemó hasta los cimientos. El propio Joker Jim ha desaparecido sin dejar rastro. A Vagabundo y Alimaña les dieron una buena paliza, pero lograron escapar: el Vagabundo - a Tortuga, bajo la protección de los cañones de La Rocha, el Alimaña - a Isla Tesoro. Pasquale me dijo que Alimaña también encalló su barco en los arrecifes cerca de Sharptown y apenas logró salir de ellos. Maestro Alexus tiene mucho trabajo que hacer ahora, jeje. En general, los españoles me decepcionaron un poco. Pensé que matarían a todos.";
			link.l1 = "Heh. Lo que sea, aún le meamos en las botas a Barbazon. Le dimos un mensaje.";
			link.l1.go = "mtraxx_93";
		break;
		
		case "mtraxx_93":
            dialog.text = "Verdad. Hablemos de negocios.";
			link.l1 = "Soy todo oídos.";
			link.l1.go = "mtraxx_94";
		break;
		
		case "mtraxx_94":
            dialog.text = "Mi servicio de inteligencia en la forma de mi buen amigo Bernard Vensan informó sobre una enorme pila de lingotes de oro que los españoles guardaron en Cartagena. Bajo su fuerte, para ser más específicos. Normalmente se hubiera atribuido a la Flota de Oro de España, pero esta vez es nuestro para tomar. Nos dirigimos al Continente Sur para asaltar Cartagena.";
			link.l1 = "¡Argh! ¿Lo oí bien? ¿Vamos a saquear toda una colonia, con un maldito fuerte?";
			link.l1.go = "mtraxx_95";
			// belamour legendary edition отказ от великого похода
			link.l2 = "No voy a Cartagena contigo, Marcus. Incendiar una ciudad entera no es mi historia.";
			link.l2.go = "mtraxx_94a";
		break;
		
		case "mtraxx_95":
            dialog.text = "Lo oíste bien. Es exactamente lo que vamos a hacer. Mi barco de guerra se encargará del fuerte, con tu ayuda, por supuesto. El audaz Jeffrey llevará tropas terrestres en su nuevo barco de la India Oriental robado a los holandeses. Pelly finalmente se deshizo de su maltrecha bergantina y consiguió una corbeta decente, no sin mi ayuda financiera, claro está. Paul Chant y tú sois responsables de acabar con la flota de patrulla, también vuestras tripulaciones participarán en el asalto, y tú, Charles, tan buen luchador y capitán, me ayudarás a destruir el fuerte.\nJean Picard no se presentó, lo cual es extraño ya que su corbeta ha sido vista en Port Royal. Bueno, si no está interesado en el oro español es su problema, así que que se joda. En su lugar, mi amigo Bernard Vensan se unirá al asalto. Además, Leprechaun con sus bucaneros asistirá a nuestras tropas. Tomaremos el oro del fuerte y el rescate de la ciudad. ¡No lo olvidarán, ja-ja!\n Ahora, ve a descansar. ¡Y ven a reunirte conmigo y otros capitanes en la taberna esta noche! ¡Deberíamos beber por nuestra causa! Ordenaré al tabernero que eche a todos los alcohólicos locales, así que solo nosotros seis y algunas chicas encantadoras estaremos en la taberna. Esta noche bebes con tus camaradas, y mañana por la mañana liderarás el escuadrón, trazarás el rumbo. Y trata de llevarnos a Cartagena lo más pronto posible. ¿Todo claro?";
			link.l1 = "¡Aye, aye, jefe!";
			link.l1.go = "mtraxx_96";
		break;
		
		case "mtraxx_96":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			chrDisableReloadToLocation = true;
			CloseQuestHeader("Roger_8");
			pchar.questTemp.Mtraxx = "cartahena";
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "LaVega_townhall", "goto", "goto3");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Mtraxx_CartahenaReloadInTavern", 10.0);
			pchar.worldmapencountersoff = "1"; // уберем враждебные энкаунтеры
		break;
		// belamour legendary edition -->
		case "mtraxx_94a":
            dialog.text = "¡Tú... tú... Príncipe loco! ¿Me estás tendiendo una trampa? ¡Sabes qué, al diablo contigo! Tuviste la oportunidad de unirte a la Hermandad, tuviste la oportunidad de escapar de las filas de todo este ganado inútil. Y simplemente dejaste pasar esta oportunidad como un cobarde. ¡Fuera con tus quejas! ¡Débil! ¡La próxima vez que te vea, soltaré a los perros!";
			link.l1 = "...";
			link.l1.go = "mtraxx_95a";
		break;
		
		case "mtraxx_95a":
            DialogExit();
			QuestSetCurrentNode("Terrax", "First time");
			CloseQuestHeader("Roger_8");
			DeleteAttribute(pchar, "questTemp.Mtraxx.Corrida");
			DeleteAttribute(pchar, "questTemp.Mtraxx.InTavern");
			LocatorReloadEnterDisable("LaVega_town", "reload6", true); // закрыть на месяц
			SetFunctionTimerCondition("Mtraxx_CartahenaLateOpen", 0, 0, 30, false);
			Mtraxx_TerraxReset(8);
			DoQuestReloadToLocation("LaVega_town", "reload", "reload6", ""); // выставим за дверь
		break;
		// <-- legendary edition
		case "mtraxx_97":
            dialog.text = "Prince, ¡por fin! Miren, chicos... le hemos preparado un regalo y él anda por ahí, ¿quién sabe dónde? ¡Siéntate, empezamos!\nBien, ¡valientes corsarios! ¡El oro de Cartagena nos espera, ja-ja! Y lo conseguiremos, lo juro por el trueno! Pero aquellos que trabajan bien también deben descansar bien. ¡Por eso hoy pasaremos un tiempo maravilloso en este magnífico establecimiento! ¡Sirve un poco de ron, cuanto más, mejor! ¡Llenen sus jarras hasta el borde! ¡Por el viento del tesoro, por el viento de la suerte! ¡Brindamos hasta el fondo!\n¡Para ustedes, la mejor bebida de los sótanos de nuestra taberna, y las damas más hermosas de la isla, ja-ja-ja!\nY para ti, Charles, de nuestra parte... un espléndido sombrero. ¡Póntelo y no discutas!\n¡Corsarios, canten nuestra canción! ¡Nuestra favorita!...";
			link.l1 = "";
			link.l1.go = "mtraxx_98";
		break;
		
		case "mtraxx_98":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			LAi_SetSitType(npchar);
			GiveItem2Character(PChar, "hat8");
			EquipCharacterByItem(PChar, "hat8");
			DoQuestCheckDelay("Mtraxx_CartahenaTavernSong", 1.0);
		break;
		
		case "mtraxx_99":
            dialog.text = "Es hora de mostrarles quiénes somos, corsarios. ¡Duende! Llévate a tus hombres y toma el control de las puertas de la ciudad. ¡No queremos que envíen refuerzos al fuerte! ¡Golpéales fuerte por la espalda cuando ataquemos a los soldados del fuerte!";
			link.l1 = "";
			link.l1.go = "mtraxx_100";
		break;
		
		case "mtraxx_100":
            dialog.text = "¡Príncipe y Paul! Visteis la escuadra militar con tres barcos, deshacéos de ellos. Manteneos alejados del fuerte y no abordéis sus naves. No tenemos ni tiempo ni posición para lidiar con premios. ¿Todo claro?! Príncipe, ¡te hablo especialmente a ti, sé de tu adicción al heroísmo, tendrás oportunidad para eso más tarde!\nNo os acerquéis demasiado al fuerte, deshacéos de esos barcos y regresad. ¡Os estaremos esperando aquí! ¿Todo claro? ¡Genial, ja-ja-ja-ja! ¡Carga!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CartahenaSquadronAttack");
		break;
		
		case "mtraxx_101":
            dialog.text = "Entonces, la escuadra española se ha ido para siempre. Ahora es momento de que el 'Dragón Rojo' haga su parte. Convertiremos el fuerte de Cartagena en un montón de escombros. ¿Estás conmigo?";
			link.l1 = "¡Claro!";
			link.l1.go = "mtraxx_102";
		break;
		
		case "mtraxx_102":
            dialog.text = "El 'Dragón Rojo' es un barco muy robusto con una artillería poderosa, el tuyo no es rival para él. Así que ten cuidado, no te hagas el héroe y mantente alejado de mis cañones.";
			link.l1 = "... ";
			link.l1.go = "mtraxx_103";
		break;
		
		case "mtraxx_103":
            DialogExit();
			
			Weather.Wind.Speed = 16.0;
			pchar.wind.speed = Weather.Wind.Speed;
			fWeatherSpeed = stf(Weather.Wind.Speed);//халява первого выхода
	
			Weather.Wind.Angle = 0.0;
			pchar.wind.angle = Weather.Wind.Angle;
			fWeatherAngle = stf(Weather.Wind.Angle);//халява первого выхода
			
            npchar.dialog.currentnode = "mtraxx_board_6x";
			npchar.DeckDialogNode = "mtraxx_board_6x";
			npchar.DontDeskTalk = true;
			Group_FindOrCreateGroup("Terrax_SeaGroup2");
			Group_DelCharacter("Terrax_SeaGroup", "Jeffry");
			Group_DelCharacter("Terrax_SeaGroup", "Mtr_Vensan");
			Group_AddCharacter("Terrax_SeaGroup2", "Jeffry");
			Group_AddCharacter("Terrax_SeaGroup2", "Mtr_Vensan");
			Group_AddCharacter("Terrax_SeaGroup2", "Pelly");
			Group_SetGroupCommander("Terrax_SeaGroup2", "Jeffry");
			Group_SetTaskNone("Terrax_SeaGroup2");
			Group_LockTask("Terrax_SeaGroup2");
			sld = CharacterFromID("Cartahena Fort Commander");
			LAi_SetImmortal(sld, false);
			Ship_SetTaskAttack(SECONDARY_TASK, sti(npchar.index), sti(sld.index));
			AddQuestRecord("Roger_9", "5");
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.questTemp.Mtraxx.Cartahena.Fort = "true";
			SetFunctionExitFromLocationCondition("Mtrxtofort", pchar.location, false);
		break;
		
		case "mtraxx_104":
            dialog.text = RandSwear()+"¡Pelea infernal! ¡Esto es todo, mis valientes corsarios! ¡Cartagena es nuestra! ¡La resistencia ha caído! ¡Audaz, Duende! Ven conmigo al fuerte - Bernie debe haber encontrado el oro ya. Príncipe, lleva a Cutlass y negocia con el gobernador para que nos pague un rescate de 250.000 pesos. Tienen el dinero, así que sé persistente. Sé que puedes.";
			link.l1 = "¡Je! ¡Con gusto, jefe!";
			link.l1.go = "mtraxx_105";
		break;
		
		case "mtraxx_105":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "Cartahena_fort", "goto", "goto10", "", 5.0);
			sld = CharacterFromID("Jeffry");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "gate_back", "Cartahena_fort", "goto", "goto11", "", 5.0);
			sld = CharacterFromID("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "gate_back", "Cartahena_fort", "goto", "goto12", "", 5.0);
			sld = CharacterFromID("Pelly");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			AddQuestRecord("Roger_9", "6");
			// запрещаем драки в городе, резиденции, форте
			LAi_LocationFightDisable(&Locations[FindLocation("Cartahena_fort")], true);
			LAi_LocationFightDisable(&Locations[FindLocation("Cartahena_town")], true);
			LAi_LocationFightDisable(&Locations[FindLocation("Cartahena_townhall")], true);
			LAi_LocationDisableOfficersGen("Cartahena_townhall", true);
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1 = "locator";
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1.location = "Cartahena_town";
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1.locator_group = "reload";
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1.locator = "reload3_back";
			pchar.quest.mtraxx_cartahena_townhall.function = "Mtraxx_CartahenaToResidence";
		break;
		
		case "mtraxx_106":
            dialog.text = "¿Cómo te va, Príncipe?";
			link.l1 = "Todo es espléndido. Forcé a los más ricos de Cartagena a pagar 350.000 pesos.";
			link.l1.go = "mtraxx_107";
		break;
		
		case "mtraxx_107":
            if (sti(Pchar.money) < 350000)
			{
				dialog.text = "¡Jo-jo, ese es mi chico! Pero, ¿dónde está el dinero?";
				link.l1 = RandSwear()+"¡Lo traeré en un momento!";
				link.l1.go = "mtraxx_107x";
			}
			else
			{
				dialog.text = "¡Ja-ja, ese es mi chico! Tú y el Cutlass pueden quedarse con 50.000 cada uno como bonificación por velocidad y astucia. El resto se repartirá entre todos nosotros más tarde.";
				link.l1 = "¡Aquí tienes!";
				link.l1.go = "mtraxx_109";
			}
		break;
		
		case "mtraxx_107x":
           DialogExit();
		   npchar.dialog.currentnode = "mtraxx_108";
		break;
		
		case "mtraxx_108":
            if (sti(Pchar.money) < 350000)
			{
				dialog.text = "¿Y bien? ¡Deja de jugar y trae las monedas aquí!";
				link.l1 = "¡En camino!";
				link.l1.go = "mtraxx_107x";
			}
			else
			{
				dialog.text = "¡Estupendo! Tú y el Cutlass pueden quedarse con 50.000 cada uno como bono por rapidez y habilidad. El resto se dividirá entre todos nosotros más tarde.";
				link.l1 = "¡Aquí tienes!";
				link.l1.go = "mtraxx_109";
			}
		break;
		
		case "mtraxx_109":
			AddMoneyToCharacter(pchar, -300000);
            dialog.text = "¿Debes estar preocupado por nuestro oro? Se ha encontrado - 5.000 unidades y ya se está transportando a nuestros barcos. La división ya se hizo, los hombres estuvieron de acuerdo con ella, esperamos que Cutlass y tú no objetéis tampoco.";
			link.l1 = "¿Cuál es mi parte?";
			link.l1.go = "mtraxx_110";
		break;
		
		case "mtraxx_110":
            dialog.text = "Dado que toda la operación fue planeada por mí, además el 'Dragón Rojo' hizo el trabajo más duro al lidiar con el fuerte, yo y mis hombres recibiremos la mitad del botín. La otra mitad se compartirá entre los capitanes de los otros cuatro barcos según el número de sus tripulaciones. Tienes "+GetCrewQuantity(pchar)+" hombres a tu disposición, tu parte es "+sti(pchar.questTemp.Mtraxx.Cartahena.Gold)+" unidades de oro y "+sti(pchar.questTemp.Mtraxx.Cartahena.Money)+" pesos.";
			link.l1 = "Bueno, ya que todos están de acuerdo con esto, ¡yo también lo estoy!";
			link.l1.go = "mtraxx_111";
		break;
		
		case "mtraxx_111":
            dialog.text = "Espléndido. ¡Felicitaciones por este exitoso viaje, corsarios! No queda nada para nosotros aquí, es hora de ir a casa. Todos nosotros, incluyéndome a mí, recibimos un mes de vacaciones. Pero tú no, Prince, tengo otra tarea para ti. Mira, Janette, la Madame del burdel de Tortuga, se quejó de ti: dijo que Charlie Prince no presta mucha atención y amor a su establecimiento. Por lo tanto, te ordeno que navegues a Tortuga, vayas a ver a Janette y gastes tus bonificaciones allí. Te lo has ganado. Haz feliz a la Madame y a sus chicas. No quiero verte antes de que te hayas descansado en Tortuga, ¡ja-ja-ja!";
			link.l1 = "Entendido, jefe. Esta es la tarea más agradable que he recibido. ¡Será hecho!";
			link.l1.go = "mtraxx_112";
		break;
		
		case "mtraxx_112":
            dialog.text = "¡Adiós, caballeros! ¡Suban a sus barcos y levanten velas! ¡Nos vemos todos en La Vega!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CartahenaFinal");
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "mtraxx_113":
            dialog.text = "¿Qué?! ¡Jean ahora es una puta de los ingleses, Bold y Cutlass han desaparecido, Leprechaun y sus hombres no se encuentran por ningún lado! ¿Y ahora tú?!";
			link.l1 = "Marcus, he tomado mi decisión. He ganado buen dinero, tú también hiciste una fortuna conmigo. Pero he terminado. Me voy.";
			link.l1.go = "mtraxx_114";
		break;
		
		case "mtraxx_114":
            dialog.text = "¿Tú, al igual que Picard, piensas que puedes ganar más por tu cuenta? ¿Sí? ¿Piensas que puedes arreglártelas sin mí? ¡Ja-ja-ja! ¡Lárgate de aquí, príncipe, no te voy a retener! Muy pronto, muy pronto verás lo equivocado que estabas y entonces volverás rogándome que acepte tu patético trasero de vuelta. ¿Y sabes qué? ¡No lo haré! ¡Ja-ja! ¡Fuera de mi vista!";
			link.l1 = "...";
			link.l1.go = "mtraxx_115";
		break;
		
		case "mtraxx_115":
            DialogExit();
		    npchar.quest.mtraxx_complete = "true";
		break;
		
		// Jason НСО
		case "patria":
			dialog.text = "¡Jo-jo! ¡Has venido al lugar correcto! ¡Escúpelo!";
			link.l1 = "Hay un tipo que no le teme a los piratas. No los toma en serio. Necesita que le den una lección de respeto. Recuerda, no lo mates.";
			link.l1.go = "patria_1";
		break;
		
		case "patria_1":
			dialog.text = "¡Ja! ¡No es otro que el viejo Charles! ¡Apuesto a que te has metido en algún lío otra vez! Vamos a los detalles, ¿quién es el objetivo esta vez y qué le enseñaremos?";
			link.l1 = "Un huésped de Europa, un inspector del Ministerio de Finanzas francés - barón Noel Forget. Quiere establecer una Compañía Comercial Francesa aquí, pero yo y un amigo cercano nos oponemos a ello. Intentamos convencer al Barón de que comerciar aquí sería muy arriesgado debido a los holandeses, ingleses y especialmente a los piratas después de que Levasseur fue derrotado, pero no escuchó. Necesitamos infundirle miedo, para que lo sienta en su propia piel.";
			link.l1.go = "patria_2";
		break;
		
		case "patria_x":
			dialog.text = "¡Ho-ho! ¡Has llegado al lugar correcto! ¡Escúpelo!";
			link.l1 = "Hay un tipo que no teme a los piratas. No los toma en serio. Necesita aprender una lección de respeto. Recuerda, no lo mates.";
			link.l1.go = "patria_x1";
		break;
		
		case "patria_x1":
			dialog.text = "¡Eh! ¿Por qué decidiste de repente montar a los piratas? Está bien, no me importa mientras me pagues. Vamos a los detalles, ¿quién es el objetivo esta vez y qué le enseñamos?";
			link.l1 = "Un invitado de Europa, un inspector del Ministerio de Finanzas de Francia: el barón Noel Forget. Quiere establecer una Compañía Comercial Francesa aquí, pero yo y un amigo cercano nos oponemos. Intentamos convencer al Barón de que comerciar aquí sería muy arriesgado por los holandeses, los ingleses y especialmente los piratas después de que Levasseur fuese derrotado, pero no nos escuchó. Necesitamos infundirle miedo, hacer que lo sienta en su propia piel.";
			link.l1.go = "patria_2";
		break;
		
		case "patria_2":
			dialog.text = "Sí-sí... ¡Un verdadero barón! ¿Deberíamos asaltar su barco?";
			link.l1 = "Aquí está el plan: su navío partirá hacia Capsterville desde Port-au-Prince pronto. Debes interceptar al Barón cerca de Saint Kitts y tomarlo como rehén. Sería mejor si no hundieras el barco y evitaras matar hombres. Los franceses son nuestros amigos, después de todo. ¿Podrás manejar eso?";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			dialog.text = "Bueno, no puedo prometer nada. Pero lo intentaré. ¿Qué barco es?";
			link.l1 = "Un bergantín llamado 'Favory'.";
			link.l1.go = "patria_4";
		break;
		
		case "patria_4":
			dialog.text = "Una bergantina no es rival para mi 'Dragón Rojo'. Nos ocuparemos de ellos con facilidad. Si se rinden, dejaré que todos vivan.";
			link.l1 = "Perfecto. Infunde miedo y ofréceles rendirse. Después, envía al Barón al calabozo infestado de ratas. Intenta encontrar el lugar más sucio que puedas, pero no lo mantengas allí más de un día, o podría enfermarse y morir. Luego acomódalo en la cabina, encuentra y enciérralo en algún lugar apartado. Viste a algunos de tus hombres como comerciantes franceses capturados y haz que actúen como tales. Durante tres días seguidos, deben contarle todo sobre cómo los despiadados piratas los persiguen, los roban, exigen rescates, los torturan... con todos los detalles requeridos.";
			link.l1.go = "patria_5";
		break;
		
		case "patria_5":
			dialog.text = "¡Ja-ja-ja! ¡Este debe ser el trabajo más divertido que he tomado en mucho tiempo! Bueno, entonces, encontraré tales actores, muchacho. No tengas dudas, después de sus historias, ¡tu Barón se cagará en los pantalones! Le mostrarán cicatrices de sables y baquetas calientes...";
			link.l1 = "¡Perfecto! Entonces le obligarás a escribir una carta a de Poincy, pidiendo un rescate. Treinta y cinco mil para un pez gordo como él no es tanto.";
			link.l1.go = "patria_6";
		break;
		
		case "patria_6":
			dialog.text = "Bien. ¿Qué haremos después?";
			link.l1 = "Y luego llevarás al Barón a los Turcos. Allí tomarás el rescate, y me entregarás al Barón. Y además deberías decirle, que todos los franceses pagarán por Tortuga y Levasseur, y no solo una vez.";
			if (CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax")) link.l1.go = "patria_x7";
			else link.l1.go = "patria_7";
		break;
		
		case "patria_7":
			dialog.text = "¡Ja-ja-ja! ¡Eso sí que es un truco del demonio! Nosotros personalmente, bueno, ya sabes lo que le hicimos a Levasseur, y ahora... ¡ja-ja-ja!.. Está bien, muchacho. ¡Se hará! ¿Entonces dices que el barco llegará pronto?";
			link.l1 = "Pronto. Necesitamos estar atentos.";
			link.l1.go = "patria_8";
		break;
		
		case "patria_x7":
			dialog.text = "¡Ja-ja-ja! ¡Eso es un truco del demonio! ¿Cuánto debo cobrarte por esta farsa? Bien, cien mil sellarán el trato. Dame el dinero.";
			if (sti(pchar.money) >= 100000) 
			{
				link.l1 = "Tómalo.";
				link.l1.go = "patria_x8";
			}
			else
			{
				link.l1 = "Está bien, lo traeré.";
				link.l1.go = "patria_xwait";
			}
		break;
		
		case "patria_xwait":
			DialogExit();
			pchar.questTemp.Patria.Condotier.NeedMoney = "true";
		break;
		
		case "patria_x8":
			AddMoneyToCharacter(pchar, -100000);
			dialog.text = "¡Perfecto! ¿Dices que el barco llegará pronto?";
			link.l1 = "Pronto. Necesitamos estar atentos.";
			link.l1.go = "patria_8";
		break;
		
		case "patria_8":
			dialog.text = "No te preocupes, no te defraudaré. Me encargaré personalmente de esto. Cuando escuches un rumor de que el Barón fue capturado, ven a verme.";
			link.l1 = "Bien. Mis gracias, Marcus.";
			link.l1.go = "patria_9";
		break;
		
		case "patria_9":
			DialogExit();
			AddQuestRecord("Patria", "71");
			pchar.questTemp.Patria = "epizode_12_wait";
			pchar.questTemp.Patria.Condotier.Success = "true";
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax")) LocatorReloadEnterDisable("Pirates_town", "reload3_back", true);
			else LocatorReloadEnterDisable("Lavega_town", "reload6", true);
		break;
		
		case "patria_10":
			dialog.text = "Por supuesto, muchacho. Según lo acordado. Historias aterradoras sobre piratas malvados, masacrando mercaderes franceses inocentes, los sonidos de un látigo, gemidos y gritos. Brasero con carbón y esposas chamuscadas. Tal como debe ser.";
			link.l1 = "¡Eh, eh! ¡Tranquilo! Lo necesito vivo";
			link.l1.go = "patria_11";
		break;
		
		case "patria_11":
			dialog.text = "No te preocupes, vivirá. Ha escrito esta carta con mano temblorosa. Aquí está.";
			link.l1 = "¿Qué está escrito allí? ¿Está rogando a Poincy que lo saque de esto?";
			link.l1.go = "patria_12";
		break;
		
		case "patria_12":
			dialog.text = "¡Así es, muchacho! ¡Está suplicando, ja!";
			link.l1 = "Tira esta carta, o mejor - quémala. Nos encontraremos en Turks en una semana. Debe parecer que necesitamos tiempo para reunir el rescate.";
			link.l1.go = "patria_13";
		break;
		
		case "patria_13":
			dialog.text = "Entendido. En una semana, en el golfo norte de los Turcos. No olvides llevar el dinero: esto debe lucir bien. Después de todo esto, ven a verme, lo discutiremos.";
			link.l1 = "¡Por supuesto, nos vemos luego, Marcus!";
			link.l1.go = "patria_14";
		break;
		
		case "patria_14":
			DialogExit();
			AddQuestRecord("Patria", "73");
			pchar.questTemp.Patria = "epizode_12_terks";
			SetFunctionTimerCondition("Patria_CondotierTerks", 0, 0, 7, false);
			SetFunctionTimerCondition("Patria_CondotierTerksOver", 0, 0, 14, false);
			if(bImCasual) NewGameTip("Modo exploración: el temporizador no está desactivado. ¡Cumple el plazo!");
		break;
		
		case "patria_15":
			pchar.quest.Patria_CondotierTerksOver.over = "yes"; //снять таймер
			dialog.text = "¡Eh, comefrogs! ¡Alto!";
			link.l1 = "No me muevo.";
			link.l1.go = "patria_16";
		break;
		
		case "patria_16":
			dialog.text = "Aquí está tu Barón. Un poco desgastado, je, pero entero. ¿Todavía es reconocible? ¡Ja-ja-ja!";
			link.l1 = "Sí... algo.";
			link.l1.go = "patria_17";
		break;
		
		case "patria_17":
			dialog.text = "Perfecto. ¡Ahora entrega el dinero o está acabado! Y no intentes engañarnos, te tenemos en la mira.";
			if (sti(pchar.money) >= 350000)
			{
				link.l1 = "Aquí, tómalo.";
				link.l1.go = "patria_18";
			}
			else
			{
				link.l1 = "¡Maldita sea! Lo he olvidado en el barco...";
				link.l1.go = "patria_22";
			}
		break;
		
		case "patria_18":
			AddMoneyToCharacter(pchar, -350000);
			dialog.text = "¡Ja-ja-ja! Eres un chico listo, francesito. Toma tu 'eminencia'. Y dile a Poincy que debe preparar el dinero: tendrás que pagar por lo que hiciste a Levasseur y Tortuga. Y tus mercaderes nos pagarán con sus bienes y barcos. ¡Ja-ja-ja! No olvides traernos más barones al archipiélago, ¡nos traen mucho provecho! ¡Ja-ja-ja!";
			link.l1 = "Por favor, ve a mi barco, Barón.";
			link.l1.go = "patria_19";
		break;
		
		case "patria_19":
			sld = CharacterFromID("Noel");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
			dialog.text = "Y ni siquiera pienses en perseguirnos, capitán. Sabes quién soy. Tengo más comedores de ranas cautivos, y si no vuelvo a casa a tiempo, serán todos ejecutados. ¿Entendido?";
			link.l1 = "¡Llegará el momento y trataremos con vosotros, malditos blasfemos!";
			link.l1.go = "patria_20";
		break;
		
		case "patria_20":
			dialog.text = "¡Ja-ja-ja-ja! ¡Seguro que lo harás!";
			link.l1 = "... ";
			link.l1.go = "patria_21";
		break;
		
		case "patria_21":
			DialogExit();
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Patria", "74");
			LAi_SetActorType(npchar);
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax"))
			{
				LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
				Island_SetReloadEnableGlobal("Bermudes", false); // закрыть остров до отвоза барона
			}
			else LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierTerraxNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_baronalive";
			pchar.questTemp.Patria.DodsonAgain = "true";
			sld = CharacterFromID("Noel");
			AddPassenger(pchar, sld, false);//добавить пассажира
			SetCharacterRemovable(sld, false);
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1 = "location";
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_Condotier_toPuancie.function = "Patria_CondotierEnCapstervil";
			// Теркс в норму
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_22":
			dialog.text = "¿¡Me estás tomando el pelo?! ¿¡Es algún tipo de truco?!";
			link.l1 = "Un minuto, lo traigo...";
			link.l1.go = "patria_23";
		break;
		
		case "patria_23":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "Patria_CondotierBaronDie", 1.0);
		break;
		
		case "patria_24":
			dialog.text = "";
			link.l1 = "¡Argh, Marcus, qué ha hecho tu necio!";
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax")) link.l1.go = "patria_25";
			else link.l1.go = "patria_x25";
		break;
		
		case "patria_25":
			dialog.text = "Charles, ¿qué estabas haciendo? ¿Dónde está el dinero? No les dije a mis muchachos que esto no era real... y entonces este idiota decidió que querías engañarnos...";
			link.l1 = "¡Es un desastre! El Barón está muerto... ¿Qué hará de Poincy ahora?";
			link.l1.go = "patria_26";
		break;
		
		case "patria_x25":
			dialog.text = "Charles, ¿qué estabas haciendo? ¿Dónde está el dinero? No les dije a mis muchachos que esto no era real... y entonces este idiota decidió que querías engañarlos...";
			link.l1 = "¡Es un desastre! El Barón está muerto... ¿Qué hará de Poincy ahora?";
			link.l1.go = "patria_x26";
		break;
		
		case "patria_x26":
			dialog.text = "Bueno, muchacho, eso es culpa tuya, espero que lo entiendas. Quizás sea lo mejor, un hombre muerto no puede causar ningún daño.";
			link.l1 = "¡Qué idiota soy! Lo eché todo a perder. Está bien, iré a Poincy... Perdóname por ser un tonto, Marcus, nos vemos.";
			link.l1.go = "patria_28";
		break;
		
		case "patria_26":
			dialog.text = "Bueno, muchacho, es tu culpa, espero que lo entiendas. Quizás sea lo mejor.";
			link.l1 = "¡Qué idiota soy! Lo arruiné todo. Bien, iré a Poincy... Perdóname por ser un tonto, Marcus, nos vemos.";
			link.l1.go = "patria_27";
		break;
		
		case "patria_27":
			dialog.text = "Necesitas descansar, estás perdiendo el toque. Ven a verme de vez en cuando, te conseguiré algo de ron y buenas doncellas.";
			link.l1 = "Gracias, te haré una visita cuando pueda.";
			link.l1.go = "patria_28";
		break;
		
		case "patria_28":
			DialogExit();
			AddQuestRecord("Patria", "75");
			LAi_SetActorType(npchar);
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax")) LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
			else LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierTerraxNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_barondie";
			// Теркс в норму
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_29":
			dialog.text = "De nada, muchacho. ¡Para mí esto fue lo más divertido que he tenido este año! ¡Nos reímos tanto, yo y mis muchachos! Así que me gustaría agradecerte por esto. Aquí está tu dinero.";
			link.l1 = "Deberías guardar una parte de ello por tu actuación.";
			link.l1.go = "patria_30";
		break;
		
		case "patria_x29":
			AddMoneyToCharacter(pchar, 350000);
			dialog.text = "Toma tu dinero, 'conspirador'. ¡Ja, ja! Esto fue divertido.";
			link.l1 = "Gracias por tu ayuda, Marcus. ¡Buena suerte!";
			link.l1.go = "patria_32";
		break;
		
		case "patria_30":
			AddMoneyToCharacter(pchar, 350000);
			dialog.text = "Olvídalo. Hice esto por el bien de nuestra amistad. La Hermandad de la Costa te debe mucho más, sin embargo, no pediste ni un solo doblón.";
			link.l1 = "Aún así, toma al menos cincuenta mil por los servicios y la compensación. ¡Gracias, Marcus!";
			link.l1.go = "patria_31";
		break;
		
		case "patria_31":
			AddMoneyToCharacter(pchar, -50000);
			dialog.text = "De nada. ¡Charles, ven a verme cuando tengas algo de tiempo!";
			link.l1 = "¡Con gusto!";
			link.l1.go = "patria_32";
		break;
		
		case "patria_32":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Patria.DodsonAgain");
		break;
		
		case "patria_33":
			dialog.text = "¡Llegas una semana tarde! No les dije a mis chicos que esto no era real... ¡Se negaron a esperar más y decidieron acabar con tu Barón!";
			link.l1 = "¡Qué idiota soy! ¡Eché todo a perder! ¿Qué le voy a decir a Poincy?";
			link.l1.go = "patria_34";
		break;
		
		case "patria_x33":
			dialog.text = "¡Llegas una semana tarde! No les dije a mis muchachos que esto no era real... ¡Se negaron a esperar más y decidieron acabar con tu Barón!";
			link.l1 = "¡Qué idiota soy! ¡Lo eché todo a perder! ¿Qué le voy a decir a Poincy?";
			link.l1.go = "patria_x34";
		break;
		
		case "patria_34":
			dialog.text = "Bueno, muchacho, es tu culpa, espero que entiendas eso. Quizás, será mejor para ti.";
			link.l1 = "Está bien, iré a Poincy... Perdóname por ser un necio, Marcus, nos vemos..";
			link.l1.go = "patria_35";
		break;
		
		case "patria_x34":
			dialog.text = "Te has metido en este lío, es tu culpa.";
			link.l1 = "Nos vemos luego, supongo...";
			link.l1.go = "patria_36";
		break;
		
		case "patria_35":
			dialog.text = "Necesitas descansar, estás perdiendo tu toque. Ven a verme de vez en cuando, te conseguiré algo de ron y buenas doncellas.";
			link.l1 = "Gracias, te haré una visita cuando pueda.";
			link.l1.go = "patria_36";
		break;
		
		case "patria_36":
			DialogExit();
			AddQuestRecord("Patria", "75");
			pchar.questTemp.Patria = "epizode_12_barondie";
			DeleteAttribute(pchar, "questTemp.Patria.DodsonFail");
		break;
		
		// Rebbebion, квест "Путеводная звезда"
		case "PZ1":
			DelLandQuestMark(npchar);
			
			if (pchar.questTemp.Mtraxx == "full_complete")
			{
				dialog.text = "Ha pasado un tiempo, Príncipe.";
				link.l1 = "No estoy seguro de que este nombre me haya traído algo más que mala suerte, Marcus.";
				link.l1.go = "PZ_Prince1";
			}
			else
			{
				dialog.text = "¡De Maure! ¿Qué te trae por aquí?";
				link.l1 = "Ahoy, Marcus. Quería preguntarte algo.";
				link.l1.go = "PZ_DeMaure1";
			}
		break;
		
		case "PZ_Prince1":
			dialog.text = "Veo que es lo contrario. ¿Qué te trae por aquí?";
			link.l1 = "¿Has oído sobre el nuevo burdel en Tortuga?";
			link.l1.go = "PZ2";
		break;
		
		case "PZ_DeMaure1":
			dialog.text = "Entonces, por supuesto, pregunta. Sabes que no me gustan las formalidades, así que ve al grano.";
			link.l1 = "¿Has oído sobre el nuevo burdel en Tortuga?";
			link.l1.go = "PZ2";
		break;
		
		case "PZ2":
			dialog.text = "¿Estás borracho? ¿Qué clase de pregunta es esa? No me hagas perder el tiempo si de verdad querías hablar de eso.";
			link.l1 = "¿Supongo que no escuchaste? Un nuevo burdel abrió recientemente allí - uno muy caro, donde sólo trabajan las chicas más bellas, sanas y bien vestidas.";
			link.l1.go = "PZ3";
		break;
		
		case "PZ3":
			dialog.text = "¡Oh, eso! Por supuesto que lo he oído, ¿quién no?";
			link.l1 = "Bueno, solo me enteré el otro día.";
			link.l1.go = "PZ4";
		break;
		
		case "PZ4":
			dialog.text = "¡Ja-ja-ja-ja, bribón, que me condenen! Pero aún así, ¿por qué lo discutes conmigo? ¿Por qué no pruebas con Hawks primero? Je je. Aunque... ¿ya te has divertido un poco allí?";
			if (CheckAttribute(pchar, "questTemp.PZ.EliteWhoreFucked"))
			{
				link.l1 = "He hecho. Por cierto, solo aceptan doblones.";
				link.l1.go = "PZ_Fucked1";
			}
			else
			{
				link.l1 = "Visité el lugar, pero no participé en los servicios. Sin embargo...";
				link.l1.go = "PZ_NoFucked1";
			}
		break;
		
		case "PZ_Fucked1":
			dialog.text = "¡Así que has venido a presumir! Ja, qué bribón.";
			link.l1 = "En realidad, no. Realmente quería preguntarte algo, Marcus.";
			link.l1.go = "PZ5";
		break;
		
		case "PZ_NoFucked1":
			dialog.text = "¿No lo hiciste?! Eres un idiota, De Maure. Si yo fuera tú...";
			link.l1 = "Hubieras comenzado una verdadera orgía, lo sé. Pero eso no es exactamente lo que quería discutir contigo.";
			link.l1.go = "PZ5";
		break;
		
		case "PZ5":
			dialog.text = "¿Qué pasa? Vamos, no me tengas en suspenso.";
			link.l1 = "Estoy buscando a la dueña de ese lugar. Me dijeron que quería conocerte y ofrecerte una oportunidad de inversión en su comercio. No puedes confundirla, es china.";
			link.l1.go = "PZ6";
		break;
		
		case "PZ6":
			dialog.text = "Jo jo. No, no he tenido el placer de conocer a ninguna mujer china últimamente. Pero no me importaría conocerla e invertir en su negocio. Después de todo, no se puede simplemente pasear por el territorio de Levasseur, y como súbdito de tu rey, se vería obligado a disparar sus embarcaciones costeras contra mi 'Dragón' en el momento en que la vea.";
			link.l1 = "Parece que está considerando Puerto Príncipe primero...";
			link.l1.go = "PZ7";
		break;
		
		case "PZ7":
			dialog.text = "¿Eso crees? Eso es un error. Incluso si de Mussac tiene más dinero que yo, lo cual dudo, no puede permitirse asignar ninguna parte del presupuesto de la ciudad a un burdel, sin importar cuánto oro genere.";
			link.l1 = "Buen punto. Claramente no ha pensado bien esta ambición suya.";
			link.l1.go = "PZ8";
		break;
		
		case "PZ8":
			dialog.text = "Sabes, siempre me pregunté cómo otros burdeles se mantienen a flote. No es la capacidad de una mujer para pensar y, especialmente, para gobernar - marca mis palabras.";
			link.l1 = "Bueno, te equivocas en eso. ¡Gracias por tu tiempo, Marcus! Si me encuentro con ella primero, le haré saber que te alegraría verla.";
			link.l1.go = "Exit";
			
			AddQuestRecord("PZ", "32");
			
			pchar.quest.PZ_SetHeavyFrigate.win_condition.l1 = "location";
			pchar.quest.PZ_SetHeavyFrigate.win_condition.l1.location = "Hispaniola1";
			pchar.quest.PZ_SetHeavyFrigate.win_condition = "PZ_SetHeavyFrigate";
			DelMapQuestMarkCity("LaVega");
			AddMapQuestMarkCity("PortPax", false);
			LocatorReloadEnterDisable("LaVega_ExitTown", "reload1_back", true);
			LocatorReloadEnterDisable("PortPax_town", "gate_back", true);
		break;
	}
}