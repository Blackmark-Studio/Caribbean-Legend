// Джино Гвинейли - алхимик
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		// --> Страж истины
		if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "jino1")
		{
			dialog.text = "¡Oh! Buen día, señor. ¿Cómo llegaste aquí?";
			link.l1 = "Buen día, Gino. Vamos a conocernos. Soy el Capitán " + GetFullName(pchar) + " y estoy aquí con el permiso de John. Voy a dejarlo claro - necesito tu ayuda, pero también puedo ayudarte.";
			link.l1.go = "guardoftruth_0";
			npchar.quest.meeting = "1";
			DelLandQuestMark(npchar);
			break;
		}
		if (npchar.quest.meeting == "0")
		{
			dialog.text = "¡Oh! Buenos días, señor. ¿Cómo llegó aquí? ¿Y dónde está John?";
			link.l1 = "Bueno, bueno... ¡Y eso es quien siempre se escondía detrás de esta puerta cerrada! Interesante... Sobre John... Se ha ido. Y esta casa es mía ahora. Pero no te preocupes. Vamos a conocernos, ¿quién eres y qué haces aquí?";
			link.l1.go = "meeting";
			npchar.quest.meeting = "1";
			DelLandQuestMark(npchar);
		}
		else
		{
			// --> Страж истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "threeitems")
			{
				dialog.text = "Hola, " + pchar.name + ". Tu rostro me dice que has encontrado algo importante. ¿Has hallado todos los componentes del Guardián de la Verdad?";
				link.l1 = "¡Exactamente! Tengo los tres objetos conmigo: el puñal, el mapa y la brújula!";
				link.l1.go = "guardoftruth_34";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "jino")
			{
				dialog.text = "Hola, " + pchar.name + ". ¿Qué ha pasado? Tienes una expresión extraña en el rostro...";
				link.l1 = "Tengo algo de qué hablar contigo, Gino. Es importante.";
				link.l1.go = "guardoftruth";
				break;
			}
			// Ксочитэм
			if (CheckAttribute(pchar, "questTemp.Ksochitam") && pchar.questTemp.Ksochitam == "begin")
			{
				dialog.text = TimeGreeting() + ", " + pchar.name + "Sí, recuerdo, han pasado dos días y quieres saber sobre el Guardián de la Verdad, ¿verdad?";
				link.l1 = "¡Sí, lo eres! ¿Pudiste desenterrar algo?";
				link.l1.go = "ksochitam";
				break;
			}
			//--> Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal.Nomoney"))
			{
				dialog.text = "¿Has traído 5 000 pesos, " + pchar.name + "?";
				if (sti(pchar.money) >= 5000)
				{
					link.l1 = "Claro. Aquí, toma el dinero y compra todo lo que necesites.";
					link.l1.go = "Portugal_3";
					SetFunctionTimerCondition("Portugal_TreatmentOver", 0, 0, 1, false);
					DeleteAttribute(pchar, "questTemp.Portugal.Nomoney");
					pchar.quest.Portugal_Ill1.over = "yes";
					pchar.quest.Portugal_Ill.win_condition.l1 = "Timer";
					pchar.quest.Portugal_Ill.win_condition.l1.date.hour = sti(GetTime());
					pchar.quest.Portugal_Ill.win_condition.l1.date.day = GetAddingDataDay(0, 0, 7);
					pchar.quest.Portugal_Ill.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
					pchar.quest.Portugal_Ill.win_condition.l1.date.year = GetAddingDataYear(0, 0, 7);
					pchar.quest.Portugal_Ill.function = "Portugal_ToAntiguaOver";
				}
				else
				{
					link.l1 = "Desafortunadamente, no tengo el dinero conmigo en este momento.";
					link.l1.go = "Portugal_nomoney";
				}
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Portugal.Die"))
			{
				dialog.text = "¡Ay, " + pchar.name + ", lo siento mucho - el paciente ha muerto. De repente empeoró y falleció muy rápido.";
				link.l1 = "Qué pena... ¡Que Dios tenga misericordia de su alma!";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Portugal.Die");
				pchar.quest.Remove_Avendel.win_condition.l1 = "Location_Type";
				pchar.quest.Remove_Avendel.win_condition.l1.location_type = "town";
				pchar.quest.Remove_Avendel.function = "RemoveAvendelnDoc";
				AddQuestRecord("Portugal", "6");
				CloseQuestHeader("Portugal");
				pchar.questTemp.Portugal = "end";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "ToAntigua")
			{
				dialog.text = "Hola, " + pchar.name + ". ¿Ha pasado algo? Pareces muy preocupado...";
				link.l1 = "¡Gino, tengo una petición inusual para ti! Hay un hombre con fiebre alta en mi barco. Está delirante e inconsciente... ¿puedes ayudarlo?";
				link.l1.go = "Portugal";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "Portugal_wait")
			{
				dialog.text = "" + pchar.name + ", estoy esperando al paciente. Apresúrate, cuanto antes lo traigas aquí, mayores serán las posibilidades de que pueda salvarlo.";
				link.l1 = "Sí, sí, será entregado aquí de inmediato.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentStart")
			{
				dialog.text = "Lo has traído justo a tiempo, " + pchar.name + ". Está en estado crítico, pero aún hay una oportunidad.\nCapitán, me estoy quedando sin ingredientes y no tenemos tiempo para recogerlos en las junglas. Tengo que comprarlos todos a los herboristas locales por 5 000 pesos. ¿Puede proporcionar la suma?";
				if (sti(pchar.money) >= 5000)
				{
					link.l1 = "Claro. Aquí, toma el dinero y compra todo lo que necesites.";
					link.l1.go = "Portugal_3";
					SetFunctionTimerCondition("Portugal_TreatmentOver", 0, 0, 1, false);
				}
				else
				{
					link.l1 = "Desafortunadamente, no tengo el dinero ahora mismo.";
					link.l1.go = "Portugal_nomoney";
					pchar.quest.Portugal_Ill.over = "yes";
					pchar.quest.Portugal_Ill1.win_condition.l1 = "Timer";
					pchar.quest.Portugal_Ill1.win_condition.l1.date.hour = sti(GetTime());
					pchar.quest.Portugal_Ill1.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
					pchar.quest.Portugal_Ill1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
					pchar.quest.Portugal_Ill1.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
					pchar.quest.Portugal_Ill1.function = "Portugal_ToAntiguaOver"; // не принесёт через 1 день - Португальцу капут
				}
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentCurrent")
			{
				dialog.text = "No tengo nada que decir ahora, " + pchar.name + ". Estoy luchando por la vida del paciente. Todavía hay algo de esperanza. Ven a verme más tarde, supongo que pronto podré decirte algo más específico.";
				link.l1 = "Está bien, Gino, regresaré más tarde.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentFinish")
			{
				pchar.quest.Portugal_Ill.over = "yes";
				dialog.text = "Tengo noticias," + pchar.name + ". No diré que tu hombre está bien, pero vive. La enfermedad está retrocediendo y se puede ver progreso. Para ser honesto, no esperaba que mis pociones lo ayudarán tanto.";
				link.l1 = "Eso son buenas noticias, Gino, pero dime ¿cuándo podré llevármelo? Tenemos un largo camino por navegar y el tiempo apremia.";
				link.l1.go = "Portugal_4";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentComplete")
			{
				dialog.text = "Buen día, Capitán. Me alegra verte.";
				link.l1 = "¿Cómo está nuestro paciente, Gino?";
				if (GetQuestPastDayParam("questTemp.Portugal_threedays") > 2)
					link.l1.go = "Portugal_9";
				else
					link.l1.go = "Portugal_threedays";
				break;
			}
			// <--Португалец
			dialog.text = "Buen día, Capitán. ¿Cómo está? ¿Necesita mi ayuda?";
			if (!CheckAttribute(npchar, "quest.rome"))
			{
				link.l1 = "Sí. Gino, supongo que eres un hombre erudito y quizás incluso sepas latín...";
				link.l1.go = "rome";
			}
			if (CheckCharacterItem(pchar, "chemistry"))
			{
				link.l2 = "Tengo algo diferente. Un pequeño regalo para ti. Aquí, echa un vistazo a este libro.";
				link.l2.go = "chemistry";
			}
			if (CheckAttribute(npchar, "quest.colt") && CheckCharacterItem(pchar, "pistol7"))
			{
				link.l2 = "Sí, Gino. Quiero mostrarte esta pistola. ¿Has visto algo parecido?";
				link.l2.go = "colt";
			}
			if (CheckAttribute(npchar, "quest.sample") && CheckCharacterItem(pchar, "pistol7") && CheckCharacterItem(pchar, "GunCap_colt") && CheckCharacterItem(pchar, "shotgun_cartridge"))
			{
				link.l2 = "Te he traído un ejemplo de la carga para mi pistola.";
				link.l2.go = "colt_1";
			}
			if (CheckAttribute(npchar, "quest.cartridge"))
			{
				link.l2 = "¿Y qué hay de los cargos por la pistola? ¿Tienes alguna pista ya?";
				link.l2.go = "cartridge";
			}
			// Addon 2016-1 Jason Пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Gord"))
			{
				link.l3 = "Gino, he encontrado la palabra 'gord', que me resulta desconocida, en el cuaderno de bitácora de un capitán. ¿Sabes qué significa?";
				link.l3.go = "mtraxx";
			}
			link.l9 = "Buen día, Gino. Estoy bien, no necesito ayuda. Solo quería saludarte y charlar un poco.";
			link.l9.go = "exit";
		}
		NextDiag.TempNode = "First time";
		break;

	case "meeting":
		pchar.questTemp.HWIC.Jino = "true"; // Addon 2016-1 Jason Пиратская линейка
		dialog.text = "Mi nombre es Gino. Gino Gvineili. Soy un científico. Mi trabajo es hacer polvos, mezclas y otras medicinas para el señor Murdock. Pero desde que él se fue...";
		link.l1 = "Bueno, yo soy " + GetFullName(pchar) + "    Capitán de mi propio barco. Entonces, ¿eres alquimista?";
		link.l1.go = "meeting_1";
		break;

	case "meeting_1":
		dialog.text = "No solo un alquimista, sino también un médico. Poseo bastante conocimiento en medicina. Conozco muchas cosas sobre hierbas curativas y soy capaz de preparar mezclas y pociones con ellas. Pero la química es mi vocación, hago muchos experimentos y algunos de mis inventos podrían ayudar a personas como tú.\nSé latín, francés, inglés e italiano. Mi ayuda será indispensable si planeas manejar una botica como lo hizo el señor Murdock...";
		link.l1 = "¡Oh, oh! No todos los días se encuentra uno con un hombre tan erudito. El negocio de la farmacia está bien seguro, pero soy un marinero... hm, eso suena extraño incluso para mí... de todos modos, estoy seguro de que nos haremos amigos, Gino. Puedes seguir viviendo aquí y hacer tus cosas de ciencia...";
		link.l1.go = "meeting_2";
		break;

	case "meeting_2":
		dialog.text = "";
		link.l1 = "Y si alguna vez necesito ayuda de un alquimista, un curandero o un científico, sabré a quién preguntar... Dime, ¿por qué siempre vives encerrado? ¿No sales nunca?";
		link.l1.go = "meeting_3";
		break;

	case "meeting_3":
		dialog.text = "Salgo cuando necesito comprar algunos ingredientes o hierbas para mis experimentos. Me gusta vivir solo, esa es mi manera. He dedicado mi vida a la ciencia y no encuentro interés en la vida ordinaria. Libros, escritos, tubos de ensayo, retortas...\nEl señor Murdock me dio tal oportunidad a cambio de ayudarle a hacer drogas.";
		link.l1 = "Ahora tendrás aún más tiempo, Gino. Pero tendrás que ceder algo del tiempo de tus experimentos en caso de que necesite tu ayuda, ¿trato?";
		link.l1.go = "meeting_4";
		break;

	case "meeting_4":
		dialog.text = "Por supuesto, Capitán. Te llamaré Capitán, " + GetAddress_Form(NPChar) + ", si no te importa. Dejaré todas mis investigaciones por si necesitas mis habilidades prácticas o conocimientos teóricos.";
		link.l1 = "Espléndido. Me alegra que nos hayamos entendido tan rápido. No te preocupes por tus gastos, mi intendente o yo te dejaremos sumas razonables de vez en cuando.";
		link.l1.go = "meeting_5";
		break;

	case "meeting_5":
		dialog.text = "Gracias, Capitán. No necesito mucho... Capitán, tengo una idea... ¿por qué no aprendes algunas habilidades de alquimia? Podría serte realmente útil.";
		link.l1 = "Hum. Como me dijo mi hermano una vez: no seas quisquilloso al aprender a hacer cosas con tus propias manos. Así que claro, ¿por qué no? ¿Qué puedes mostrarme?";
		link.l1.go = "meeting_6";
		break;

	case "meeting_6":
		dialog.text = "Bueno, ciertamente, no podrás convertir el hierro en oro, es imposible... todavía, pero puedes aprender a mezclar ingredientes según las instrucciones para obtener pociones u otros objetos útiles como resultado. Aquí, toma esta bolsa. Contiene todo lo que necesitará el alquimista principiante. Tubos de ensayo, matraces, retortas, alambiques, espátulas, tubos de vidrio, un quemador y así sucesivamente...";
		link.l1 = "¡Fascinante!";
		link.l1.go = "meeting_7";
		break;

	case "meeting_7":
		Log_Info("Has recibido un kit de alquimista");
		GiveItem2Character(pchar, "alchemy_tool");
		PlaySound("interface\important_item.wav");
		dialog.text = "Debes conocer una receta para poder hacer una poción o un objeto. Las recetas se pueden comprar a los mercaderes o encontrar en cualquier parte. Una vez que hayas estudiado una receta, deberías reunir cada ingrediente necesario y hacer exactamente lo que está escrito allí.\n Usa tus herramientas de alquimia, encuentra o compra un mortero y mano, busca un crisol, ay, no poseo uno extra para darte. Hierbas, espíritus, pociones, minerales, basura - todo servirá, siempre y cuando tengas la receta y las herramientas adecuadas.";
		link.l1 = "Entiendo. Intentaré mezclar algo en mi tiempo libre. ¡Gracias, Gino! ¿Puedes darme alguna receta sencilla? ¿Algo para empezar?";
		link.l1.go = "meeting_8";
		break;

	case "meeting_8":
		dialog.text = "No tengo cosas simples... pero aquí, toma esta receta de un antídoto. Supongo que puedes manejar esta tarea. Tómalo.";
		link.l1 = "¡Gratitud! Lo aprenderé. ¡Adiós ahora, Gino! Cuida mi casa, temo que no visitaré este lugar muy a menudo, así que eres bienvenido a usar no solo tu habitación, sino también el resto del edificio.";
		link.l1.go = "meeting_9";
		break;

	case "meeting_9":
		DialogExit();
		GiveItem2Character(pchar, "recipe_potion4"); // belamour legendary edition
		Log_Info("Has recibido la receta de un antidoto");
		PlaySound("interface\notebook.wav");
		Log_Info("Necesitas tener la habilidad Alquimia para crear pociones, amuletos y objetos.");
		NextDiag.CurrentNode = "First time";
		break;

	case "rome":
		dialog.text = "Sí, Capitán, conozco la lengua de los antiguos romanos. Todo científico, especialmente un sanador o un alquimista, debe conocer el latín. ¿Necesitas mis conocimientos de latín?";
		link.l1 = "Sí. Gino, no me tomes por tonto pero... bueno, cómo explicar...";
		link.l1.go = "rome_1";
		break;

	case "rome_1":
		dialog.text = "Hable sin rodeos, capitán. No sea tímido.";
		link.l1 = "Está bien. ¿Puedes hacerme una lista de aforismos latinos eruditos? Verás, hay... un hombre que gusta de alardear de su 'erudición' y a veces usa esas frases en latín para mostrarme mi ignorancia comparada con la suya. Algo como... 'paxem-bellum'...";
		link.l1.go = "rome_2";
		break;

	case "rome_2":
		dialog.text = "'Si vis pacem, para bellum', ¿quieres decir?";
		link.l1 = "Sí, sí. Quiero aprenderlas para vencer a mi arrogante he... mi amigo.";
		link.l1.go = "rome_3";
		break;

	case "rome_3":
		AddQuestRecordInfo("Rome", "1");
		dialog.text = "No hay nada extraño o vergonzoso en su petición, capitán. Conocer los aforismos de los antiguos que pasaron a la historia, lo convierte en un hombre educado. Aquí, tome este texto. Es lo que ha pedido.";
		link.l1 = "¡Gracias, Gino! ¡Lo aprecio! Lo leeré en mi tiempo libre...";
		link.l1.go = "exit";
		npchar.quest.rome = true;
		NextDiag.TempNode = "First time";
		break;

	case "chemistry":
		RemoveItems(pchar, "chemistry", 1);
		Log_Info("Has entregado El libro de química de Lavoisier");
		dialog.text = "Muéstrame... (leyendo) ¡Imposible! ¿Un 'pequeño regalo', dices? ¡Este libro no tiene precio! ¿De dónde lo sacaste? ¡Esto es... un verdadero tesoro!";
		link.l1 = "Me alegra que te guste.";
		link.l1.go = "chemistry_1";
		break;

	case "chemistry_1":
		dialog.text = "¡(Leyendo) Increíble! Nunca había oído hablar de eso... ¿y esto? No entiendo ni una palabra aquí... ¡pero lo haré, maldita sea! ¡Oh, pronto el trabajo estará hirviendo en mi laboratorio!" + pchar.name + ", ni siquiera te das cuenta de LO que me has dado...";
		link.l1 = "¿Por qué no? Sí lo hago. Un libro científico para un científico...";
		link.l1.go = "chemistry_2";
		break;

	case "chemistry_2":
		dialog.text = "¿Pero quién es el autor de este milagro? Antoine-Laurent de Lavoisier, Francia... Nunca he oído hablar de él. ¡Pero espera! ¿Cómo es posible? ¿El año de impresión es 1789? Pero cómo...";
		link.l1 = "No sé por qué ese año está escrito ahí tampoco. Bueno, tal vez sí lo sepa. Pero te aconsejo que no le des demasiadas vueltas. El libro es útil y eso es lo único que importa.";
		link.l1.go = "chemistry_3";
		break;

	case "chemistry_3":
		dialog.text = "Es prometedor más allá de toda medida y ese año debe ser un error de impresión de algún tipo... Lo que sea. ¡Muchas gracias, capitán!";
		link.l1 = "Bienvenido, Gino. Todo es tuyo.";
		link.l1.go = "exit";
		if (CheckCharacterItem(pchar, "pistol7"))
		{
			link.l1 = "Eso no es todo, Gino. Quiero mostrarte esta pistola. ¿Alguna vez has visto algo así?";
			link.l1.go = "colt";
		}
		npchar.quest.colt = true;
		break;

	case "colt":
		dialog.text = "No soy armero, pero echaré un vistazo... no, nunca he visto algo así. ¿Por qué preguntas?";
		link.l1 = "Esta pistola es poderosa y destructiva, pero se necesitan cargas especiales para usarla. Nada más funcionaría. Y no tengo idea de cómo hacer más municiones para ella. Así que vine aquí por tu consejo.";
		link.l1.go = "colt_1";
		break;

	case "colt_1":
		dialog.text = "¿Tienes al menos una ronda para mostrarme como ejemplo? Si no, me temo que no podré ayudar.";
		if (CheckCharacterItem(pchar, "GunCap_colt") && CheckCharacterItem(pchar, "shotgun_cartridge"))
		{
			link.l1 = "Lo hago. La carga se compone de dos partes: la bala misma con una bala y esta cosa que hace explotar la pólvora.";
			link.l1.go = "colt_2";
		}
		else
		{
			link.l1 = "¡Qué fracaso! ¡Qué vergüenza! Bien, quizás encuentre más y te los traiga.";
			link.l1.go = "exit";
			npchar.quest.sample = true;
		}
		DeleteAttribute(npchar, "quest.colt");
		break;

	case "colt_2":
		RemoveItems(pchar, "pistol7", 1);
		RemoveItems(pchar, "GunCap_colt", 1);
		RemoveItems(pchar, "shotgun_cartridge", 1);
		Log_Info("Has entregado una cartucho del revólver");
		Log_Info("Has entregado una capsula");
		PlaySound("interface\important_item.wav");
		dialog.text = "¡Interesante! Eso parece sencillo, hay pólvora dentro, una bala entra por arriba, pero parece un poco extraño. Y esta 'cosa'... hm. La pólvora no explota sin ella, ¿verdad? Curioso... Mira, Capitán, deja todo esto en mis manos: la pistola y las cargas. Ven a verme en un mes, necesito tiempo para descifrarlo.";
		link.l1 = "¡Estupendo! Trata de entender cómo funciona, realmente quiero disparar esta pistola.";
		link.l1.go = "colt_3";
		break;

	case "colt_3":
		dialog.text = "El principal problema es descubrir de qué está hecha esta sustancia que hace explotar la pólvora. Este libro será útil. Intentaré averiguar esto.";
		link.l1 = "Está bien. ¡Adiós, Gino!";
		link.l1.go = "colt_4";
		break;

	case "colt_4":
		DialogExit();
		DeleteAttribute(npchar, "quest.sample");
		SetFunctionTimerCondition("Colt_Timer", 0, 0, 30, false); // таймер
		break;

	case "cartridge":
		dialog.text = "Sí, he descubierto de qué están hechas las cargas para la pistola. Tengo que darle crédito al libro que me diste. No habría funcionado sin él. Pero tengo que advertirte, Capitán, no será fácil crear balas y cápsulas para esta arma.";
		link.l1 = "¿Cápsulas?";
		link.l1.go = "cartridge_1";
		break;

	case "cartridge_1":
		dialog.text = "La cápsula es esa 'cosa' que, como dijiste, hace explotar la pólvora. Pero empecemos desde el principio. ¿Estás listo?";
		link.l1 = "¡Sí! Te estoy escuchando con mucho cuidado.";
		link.l1.go = "cartridge_2";
		break;

	case "cartridge_2":
		AddQuestRecordInfo("Recipe", "shotgun_bullet");
		SetAlchemyRecipeKnown("shotgun_bullet");
		dialog.text = "Entonces, primero, necesitas fabricar una bala especial. Las balas comunes no funcionarán. Debe tener una forma cónica especial. Tendrás que encontrar un molde para tales balas, el molde de bala como lo he llamado. Toma balas de plomo ordinarias, fúndelas en un crisol y vierte el plomo fundido en el molde de bala. Congela este molde y saca de él la bala terminada.";
		link.l1 = "¿Y dónde puedo encontrar un molde para balas así?";
		link.l1.go = "cartridge_3";
		break;

	case "cartridge_3":
		dialog.text = "No sé, Capitán. Soy un alquimista, no un herrero. Toma esta bala como ejemplo, tal vez descubras qué hacer.";
		link.l1 = "Está bien. Continúa...";
		link.l1.go = "cartridge_4";
		break;

	case "cartridge_4":
		AddQuestRecordInfo("Recipe", "shotgun_cartridge");
		SetAlchemyRecipeKnown("shotgun_cartridge");
		dialog.text = "Entonces tienes que hacer un contenedor para la pólvora. Inyectas la bala allí. He escrito una buena instrucción para ti. Léela con atención y dale una oportunidad.";
		link.l1 = "Bueno...";
		link.l1.go = "cartridge_5";
		break;

	case "cartridge_5":
		AddQuestRecordInfo("Recipe", "GunCap_colt");
		SetAlchemyRecipeKnown("GunCap_colt");
		dialog.text = "Ahora tenemos que conseguir las cápsulas. Necesitarás una lámina de cobre muy fina - fabrícala tú mismo con una pepita de cobre. Corta círculos en ella del mismo tamaño que las balas. Luego pon plata fulminante dentro de ellas usando cera.";
		link.l1 = "¿Plata fulminante? ¿Qué es eso?";
		link.l1.go = "cartridge_6";
		break;

	case "cartridge_6":
		dialog.text = "No lo sabía yo mismo, aprendí el secreto de tu libro. Es un polvo blanco que se puede hacer de plata, espíritu y ácido nítrico. Explota fácilmente al frotarlo o agitarlo, por eso sirve bien para encender la pólvora en las balas de tu pistola. Una cosa desagradable, explotó dos veces durante mis pruebas hasta que di con la receta.";
		link.l1 = "¡Tuve la suerte de tener este libro conmigo!";
		link.l1.go = "cartridge_7";
		break;

	case "cartridge_7":
		dialog.text = "¡Ten mucho cuidado, esta cosa es explosiva como el demonio! Podría hacer un poco yo mismo, pero almacenar plata fulminante es demasiado peligroso, es vital que la pongas en las cápsulas justo después de su creación. No puedo fabricar cápsulas de cobre, no soy herrero como ya te he dicho.";
		link.l1 = "Está bien. Dame la receta, la aprenderé yo mismo.";
		link.l1.go = "cartridge_8";
		break;

	case "cartridge_8":
		AddQuestRecordInfo("Recipe", "OxyHydSilver");
		SetAlchemyRecipeKnown("OxyHydSilver");
		dialog.text = "Seas bienvenido. Sigue la receta con precisión y ten cuidado con el orden del proceso o volarás por los aires con tus frascos.";
		link.l1 = "Seré cuidadoso.";
		link.l1.go = "cartridge_9";
		break;

	case "cartridge_9":
		dialog.text = "Además, lleva estos dos frascos. Este contiene ácido nítrico y este tiene espíritu. Podrás hacer suficiente plata fulminante para llenar unas 20 cápsulas.";
		link.l1 = "¡Gracias, Gino!";
		link.l1.go = "cartridge_10";
		break;

	case "cartridge_10":
		GiveItem2Character(pchar, "Mineral29");
		GiveItem2Character(pchar, "Mineral28");
		Log_Info("Has recibido un matraz de ácido nítrico");
		Log_Info("Has recibido un frasco de alcohol");
		PlaySound("interface\important_item.wav");
		dialog.text = "También lleva tu pistola y la carga de ejemplo. Buena suerte, Capitán, en tu elaboración de cargas. Espero que te mantengas vivo y entero.";
		link.l1 = "Haré lo que pueda para protegerme. Y, Gino, ¿te he dicho que eres un genio?";
		link.l1.go = "cartridge_11";
		break;

	case "cartridge_11":
		TakeNItems(pchar, "pistol7", 1);
		TakeNItems(pchar, "shotgun_cartridge", 3);
		TakeNItems(pchar, "GunCap_colt", 1);
		dialog.text = "Me estás haciendo sonrojar, Capitán, hablo en serio...";
		link.l1 = "Bien. ¡Adiós, Gino! ¡Eres mi mejor alquimista!";
		link.l1.go = "cartridge_12";
		break;

	case "cartridge_12":
		DialogExit();
		DeleteAttribute(npchar, "quest.cartridge");
		break;

	// Addon 2016-1 Jason Пиратская линейка
	case "mtraxx":
		dialog.text = "¡Gordo, gordo... ¿Podrías contarme más sobre el capitán? ¿De dónde es?";
		link.l1 = "Ni idea, aunque nació en algún lugar del Norte, a veces lo llamaban un vikingo.";
		link.l1.go = "mtraxx_1";
		break;

	case "mtraxx_1":
		dialog.text = "¡Un vikingo! Sí-sí, lo recuerdo, he leído sobre esto en un libro de historia. Gord es un asentamiento fortificado de un jarl libre.";
		link.l1 = "¿Un jarl libre? ¿Quién sería eso?";
		link.l1.go = "mtraxx_2";
		break;

	case "mtraxx_2":
		dialog.text = "Es un príncipe de los hombres del norte. Jarls libres con sus bandas de guerra solían saquear y saquear Europa hace siglos en sus barcos, Drakkars. Podrías llamarlos piratas, supongo. Los gords eran sus bases y hogares, lugares donde podían descansar, cultivar y festejar.";
		link.l1 = "Ya veo. Este refugio debe ser su guarida pirata entonces... ¡Gracias, Gino!";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Mtraxx_WolfreekReadLogbookFourth");
		break;

		// ----------------------------------------- Португалец ----------------------------------------------------
	case "Portugal":
		dialog.text = "Fiebre y delirios, dices, eso es intrigante. ¡Tráelo aquí de inmediato! Veré qué puedo hacer. Pero no puedo prometerte nada si su condición es demasiado grave... ¿Es tu oficial?";
		link.l1 = "No, gracias a Dios, no lo está. ¡Gino, escucha, no preguntes quién es, solo haz lo que puedas, es realmente importante para mí!";
		link.l1.go = "Portugal_1";
		break;

	case "Portugal_1":
		dialog.text = "Está bien, llévalo a la casa, a tu habitación. Prepararé algunas mezclas... quizás esta raíz...";
		link.l1 = "¡Voy a entregarlo aquí de inmediato!";
		link.l1.go = "Portugal_2";
		break;

	case "Portugal_2":
		DialogExit();
		PChar.quest.Portugal_DoctorPodhodit.win_condition.l1 = "location";
		PChar.quest.Portugal_DoctorPodhodit.win_condition.l1.location = "SentJons_HouseF3";
		PChar.quest.Portugal_DoctorPodhodit.function = "Portugal_DoctorPodhodit";
		break;

	case "Portugal_nomoney":
		dialog.text = "Entonces trata de encontrarlo lo antes posible, no podré curarlo sin medicinas y podría ser demasiado tarde si no te apresuras.";
		link.l1 = "Está bien, encontraré el dinero.";
		link.l1.go = "exit";
		pchar.questTemp.Portugal.Nomoney = "true";
		break;

	case "Portugal_3":
		AddMoneyToCharacter(pchar, -5000);
		dialog.text = "Espléndido, Capitán. Ahora me ocuparé de preparar algunas mezclas y le recomiendo que deje a mi paciente. Vuelva aquí mañana.";
		link.l1 = "Está bien, Gino. Confío en tus mezclas y en tu genio.";
		link.l1.go = "exit";
		pchar.questTemp.Portugal = "TreatmentCurrent";
		// pchar.GenQuest.CannotWait = true;//запрет ожидания
		break;

	case "Portugal_4":
		dialog.text = "Bueno, creo que estará bien en dos semanas. No puedo prometer que podrá bailar, pero al menos se mantendrá en pie por sí mismo, eso es seguro.";
		link.l1 = "¡Maldita sea, no tengo estas dos semanas! Necesito... zarpar lo antes posible!";
		link.l1.go = "Portugal_5";
		break;

	case "Portugal_5":
		dialog.text = "Capitán, no soy un mago y puedo asegurarle que el hombre está demasiado débil por ahora. No estoy seguro de que sobreviva unos días en el barco, ¡no puede moverlo!";
		link.l1 = "Está bien, está bien, pero dos semanas, no, ¡incluso una semana es demasiado!";
		link.l1.go = "Portugal_6";
		break;

	case "Portugal_6":
		dialog.text = "Tres días... sí, supongo que en tres días podrías intentar zarpar, pero necesitará cuidados y medicinas y tendrás que hacer paradas.";
		link.l1 = "He conseguido un médico, él se encargará de él. Volveré en tres días y lo llevaremos, es lo máximo que puedo permitirme. Tenemos que movernos, incluso con paradas... sí, y una cosa más, ¡Gino, eres un genio!";
		link.l1.go = "Portugal_7";
		break;

	case "Portugal_7":
		dialog.text = "Gracias, capitán.  Vuelve por tu amigo en tres días, pero no lo molestes hasta entonces. Necesita descanso completo.";
		link.l1 = "Está bien, lo entiendo. Lo llevaré en tres días.";
		link.l1.go = "Portugal_8";
		break;

	case "Portugal_8":
		DialogExit();
		SaveCurrentQuestDateParam("questTemp.Portugal_threedays");
		pchar.quest.Portugal_Ill2.win_condition.l1 = "Timer";
		pchar.quest.Portugal_Ill2.win_condition.l1.date.hour = sti(GetTime());
		pchar.quest.Portugal_Ill2.win_condition.l1.date.day = GetAddingDataDay(0, 0, 5);
		pchar.quest.Portugal_Ill2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 5);
		pchar.quest.Portugal_Ill2.win_condition.l1.date.year = GetAddingDataYear(0, 0, 5);
		pchar.quest.Portugal_Ill2.function = "Portugal_ToAntiguaOver"; // чтобы не тянул
		pchar.questTemp.Portugal = "TreatmentComplete";
		pchar.quest.Avendel_room.win_condition.l1 = "location";
		pchar.quest.Avendel_room.win_condition.l1.location = "SentJons_HouseF3";
		pchar.quest.Avendel_room.function = "AvendelSpeach";
		break;

	case "Portugal_threedays":
		dialog.text = "Está bien, pero el progreso es lento. No puede ser capturado todavía.";
		link.l1 = "Sí - sí, Gino, lo recuerdo. Tres días...";
		link.l1.go = "exit";
		break;

	case "Portugal_9":
		pchar.quest.Portugal_Ill2.over = "yes";
		dialog.text = "No hay deterioro, pero tampoco ha mejorado realmente. Todavía está inconsciente, no entiende dónde está ni por qué está aquí, aunque no parece preocuparle mucho. Todavía tiene fiebre, así que no estoy seguro de que llevarlo a bordo ahora sea una buena idea.";
		link.l1 = "No puedo esperar más, ya hemos estado aquí demasiado tiempo. Empaca tus mezclas que le ayudarán en el viaje y nos vamos. Espero que este bastardo sea lo suficientemente fuerte como para sobrevivir el viaje y enfrentar su sentencia de muerte...";
		link.l1.go = "Portugal_10";
		break;

	case "Portugal_10":
		dialog.text = "¡Espera, Capitán! ¿He estado tratando con condenados? ¿Qué demonios? Se ha hecho un gran trabajo aquí, ¿tienes idea de lo difícil que es hacer la pólvora seca...?";
		link.l1 = "Gino, no necesitabas saber eso. No te preocupes demasiado, él es un pirata y uno de los más terribles de su clase. Tengo que llevarlo a Curazao para una cita con las autoridades de la Compañía lo antes posible. Punto.";
		link.l1.go = "Portugal_11";
		break;

	case "Portugal_11":
		dialog.text = "Está bien, tú sabes mejor. Pirata entonces... Curazao. Lo que sea, pero escúchame, él estará durmiendo la mayor parte del tiempo, pero el vaivén del barco y el calor sofocante pueden retrasar todo el proceso. Recomiendo hacer una parada después de unos días de navegación y dejar que tu... prisionero descanse en tierra. De lo contrario, existe el riesgo de que tengan que colgar un cadáver en Curazao...";
		link.l1 = "Está bien, lo haré. Martinica estará bien, está casi a mitad de camino hacia Curazao. Espero que el viento sea favorable. Voy a llevarlo ahora y nos iremos. Gracias de nuevo, Gino.";
		link.l1.go = "Portugal_12";
		break;

	case "Portugal_12":
		dialog.text = "De nada, Capitán. Recuerda que tienes cuatro días, bueno, cinco, pero no más. Y una última cosa... sabes, suelo curar a la gente no porque quiera que los cuelguen después de mi tratamiento. El doctor es responsable de sus pacientes sin importar quiénes sean. Y me siento realmente mal...";
		link.l1 = "Lamento haberte arrastrado a todo esto, pero no teníamos ninguna oportunidad sin ti. Tenemos que zarpar ahora o los chicos portugueses lograrán reunirse en nuestras puertas para encontrarse con su jefe.";
		link.l1.go = "Portugal_13";
		break;

	case "Portugal_13":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1", "SentJons_HouseF3_Room", "goto", "goto2", "Portugal_JinoNorm", -1); // Джино в свою комнату
		DeleteAttribute(pchar, "GenQuest.CannotWait");																		   // можно мотать время
		pchar.quest.Portugal_Ill3.win_condition.l1 = "Timer";
		pchar.quest.Portugal_Ill3.win_condition.l1.date.hour = sti(GetTime());
		pchar.quest.Portugal_Ill3.win_condition.l1.date.day = GetAddingDataDay(0, 0, 5);
		pchar.quest.Portugal_Ill3.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 5);
		pchar.quest.Portugal_Ill3.win_condition.l1.date.year = GetAddingDataYear(0, 0, 5);
		pchar.quest.Portugal_Ill3.function = "Portugal_ToAntiguaOver"; // 5 дней до Мартиники
		pchar.questTemp.Portugal = "ToMartinique";
		pchar.quest.Avendel_room1.win_condition.l1 = "location";
		pchar.quest.Avendel_room1.win_condition.l1.location = "SentJons_HouseF3";
		pchar.quest.Avendel_room1.function = "AvendelSpeach";
		pchar.quest.Portugal_street.win_condition.l1 = "location";
		pchar.quest.Portugal_street.win_condition.l1.location = "SentJons_town";
		pchar.quest.Portugal_street.function = "PortugalOnStreet";
		break;
	// <-- Португалец
	case "guardoftruth_0":
		dialog.text = "Intrigante... ¿Y cómo puedes ayudarme? No necesito ayuda y no la he pedido...";
		link.l1 = "Pero lo necesitarás. Escúchame primero y luego concluye.";
		link.l1.go = "guardoftruth";
		break;

	case "guardoftruth":
		dialog.text = "Estoy todo oídos.";
		link.l1 = "He estado en Santiago recientemente... visitando al padre Vincento. Estaba buscando a su secretario desaparecido llamado... Jesús, ¿por qué te has puesto tan pálido, Gino?";
		link.l1.go = "guardoftruth_1";
		break;

	case "guardoftruth_1":
		dialog.text = "¿Has visto al inquisidor? ¿Está él...?";
		link.l1 = "No te preocupes, Gino. No hay manera de que te entregue a él, aunque esa fue su orden: encontrarte y llevarte a él. Necesito obtener información sobre un indio del pueblo Itza. Cuéntame sobre Tayasal, sus tesoros y el 'mal' que lo rodea.";
		link.l1.go = "guardoftruth_2";
		break;

	case "guardoftruth_2":
		dialog.text = "Veo que estás bien informado. ¿Te lo dijo el padre Vincento?";
		link.l1 = "Conseguí algo de información de él y algo más de otras personas. Pero me gustaría escucharte. Fuiste su secretario una vez, así que debiste haber creado un protocolo del interrogatorio, ¿verdad?";
		link.l1.go = "guardoftruth_3";
		break;

	case "guardoftruth_3":
		dialog.text = "¡No puedes imaginar lo que le estaba haciendo a ese pobre indio!.. Me da escalofríos cada vez que recuerdo ese interrogatorio en mi mente.";
		link.l1 = "Aún así, hablemos de eso. ¿Quién era ese indio? ¿Cómo llegó a manos del padre Vincento?";
		link.l1.go = "guardoftruth_4";
		break;

	case "guardoftruth_4":
		dialog.text = "Estaba entre los indios del pueblo Itza que viajaron desde Tayasal en busca de la Máscara de Kukulcán, un artefacto del antiguo dios maya - Kukulcán. Esos indios se enfrentaron a un grupo de aventureros blancos liderados por Archibald Calhoun, un cazador de tesoros de Escocia. Solo un indio sobrevivió, su nombre era Ksatl Cha. Tenía tres objetos interesantes consigo, te contaré sobre ellos más tarde.\Calhoun intentó obligar al prisionero a hablarle sobre tesoros, pero él permaneció en silencio. Así que el escocés lo entregó a Santiago, al padre Vincento, a cambio de un permiso para visitar ciudades españolas durante un año. Sabía que el inquisidor estaba muy interesado en todo tipo de misterios y leyendas locales. Vincento hizo que el indio hablara. Comenzó a hablar mucho, nos contó todo lo que sabía y la información que obtuvimos de él sorprendió al mismo inquisidor.";
		link.l1 = "¿No me digas? ¿Y qué podría hacer temblar a Su Gracia?";
		link.l1.go = "guardoftruth_5";
		break;

	case "guardoftruth_5":
		dialog.text = "Te contaré todo en orden. Hay una antigua ciudad maya llamada Tayasal en las profundidades de las selvas del Yucatán. Está habitada por los descendientes de los mayas: el pueblo Itza. Intentan vivir sus vidas según las reglas y tradiciones de sus ancestros. Seguramente, no les gusta el estado del mundo moderno, me refiero al dominio del hombre blanco.\nSueñan con los buenos tiempos de antaño. Y aquí viene la parte más interesante. Un grupo de aventureros blancos accidentalmente se acercó a Tayasal y secuestró a la hija del jefe supremo del pueblo Itza. Sucedió hace casi un cuarto de siglo.\nEsta fue la gota que colmó el vaso y Kanek, el jefe, se enfureció. Decidió realizar el ritual más peligroso y secreto de los mayas: invocar a un dios indio para borrar a toda la descendencia de los conquistadores blancos...";
		link.l1 = "Mm... Ese debe ser el demonio del que hablaba el padre Vincento. Pero, ¿cómo debería este dios indio tratar con los colonos blancos? ¿Mostrándose en forma de dragón y quemándolos a todos?";
		link.l1.go = "guardoftruth_6";
		break;

	case "guardoftruth_6":
		dialog.text = "¡Oh, " + pchar.name + ", ¡deja esos cuentos de monstruos de fuego para las viejas abuelas! En realidad, no estás tan equivocado, pero nuestro caso es más difícil y serio. Ni siquiera el Diluvio podrá detener a Europa de expandirse en el Nuevo Mundo. Vendrán diez más para reemplazar a uno muerto. Kanek necesitaba destruir la posibilidad misma de la colonización europea.";
		link.l1 = "Bueno, ya sucedió.";
		link.l1.go = "guardoftruth_7";
		break;

	case "guardoftruth_7":
		dialog.text = "Estás pensando en la dirección correcta, Capitán... El propósito del rito de Kanek no era solo invocar al ser supremo, sino también crear un agujero espaciotemporal.";
		link.l1 = "¿Qué?";
		link.l1.go = "guardoftruth_8";
		break;

	case "guardoftruth_8":
		dialog.text = "Los antiguos del pueblo maya poseían bastante conocimiento, Capitán. Kanek encontró la descripción de un rito que permite controlar el tiempo.";
		link.l1 = "¡Vaya! ¡Increíble!";
		link.l1.go = "guardoftruth_9";
		break;

	case "guardoftruth_9":
		dialog.text = "Escucha. El objetivo final del ritual es alterar el pasado para hacer imposible la aparición del hombre blanco en el Nuevo Mundo. Para lograr tal cosa, van a enviar a alguien al pasado, alguien que tenga autoridad, poder y la capacidad de cambiar los destinos de las personas. Pero lo más importante, esa persona debe poseer conocimientos modernos.\nPiensa en ello, " + pchar.name + ", ¿qué habría pasado con Colón si sus carabelas hubieran sido encontradas por una flota india de fragatas y galeones armados con cañones modernos? ¿Y qué si las espingardas de los soldados blancos no hubieran estado enfrentando arcos y lanzas, sino morteros y mosquetes?";
		link.l1 = "Supongo que las Américas no habrían sido descubiertas en absoluto....";
		link.l1.go = "guardoftruth_10";
		break;

	case "guardoftruth_10":
		dialog.text = "¡Exactamente! Y quizás algún 'Colón' indio habría descubierto Europa...";
		link.l1 = "Interesante, ¿y a quién enviará Kanek al pasado? ¿A uno de sus guerreros desnudos? Dudo que pueda enseñar a sus antepasados...";
		link.l1.go = "guardoftruth_11";
		break;

	case "guardoftruth_11":
		dialog.text = "No te rías, Capitán. Kanek no estaba perdiendo años en los templos mayas leyendo sus escrituras. Un dios indio debe ser enviado al pasado en forma humana...";
		link.l1 = "Gino, ¿de qué tonterías estás hablando? ¿Eres tú....?";
		link.l1.go = "guardoftruth_12";
		break;

	case "guardoftruth_12":
		dialog.text = "Incluso el Hijo de nuestro Señor, Jesucristo, ha venido a nuestra tierra en forma humana y nació de una mujer humana, la Santa Virgen María...";
		link.l1 = "Jesús, Gino... ¿hablas en serio?";
		link.l1.go = "guardoftruth_13";
		break;

	case "guardoftruth_13":
		dialog.text = "Claro que sí. Ksatl Cha fue muy persuasivo...";
		link.l1 = "¿Pero qué Dios eligió Kanek para tan 'noble' misión?";
		link.l1.go = "guardoftruth_14";
		break;

	case "guardoftruth_14":
		dialog.text = "El rito estaba destinado a convocar solo a un Ser Supremo. La serpiente emplumada, Quetzalcoatl, Kukulcán...";
		if (CheckAttribute(pchar, "questTemp.Dolly"))
			link.l1 = "¿Kukulcán?! Ya he tenido la imprudencia de encontrarme con su 'espíritu' que habita en las estatuas. Ahora veo... ¡continúa!";
		else
			link.l1 = "Mm. Interesante. Ya he oído ese nombre del padre Vincento... ¡continúa!";
		link.l1.go = "guardoftruth_15";
		break;

	case "guardoftruth_15":
		dialog.text = "Kanek decidió invocar a Kukulcán, ya que los Itza ya tenían un antiguo artefacto de este dios: la Máscara de Kukulcán. Quien posee la máscara es capaz de atravesar el portal y solo él será aceptado por los antiguos mayas como un dios viviente.\nEl sacerdote realizó el ritual, invocando a Kukulcán para que se encarnara en el cuerpo de algún mortal. También creó un agujero temporal que extrajo a varias personas al azar del futuro hacia nuestro tiempo.\nEl objetivo de esta extracción era presentar la encarnación de Kukulcán no solo con el conocimiento de nuestros tiempos, sino también del futuro. Pero algo salió mal y todas esas personas llegaron a otro lugar y no a Tayasal. Nunca he conocido a ninguno de ellos.\nSe crearon varios portales dentro del archipiélago, se suponía que transportarían a los poseedores del conocimiento futuro y a los agentes Itza por toda el área y a Tayasal. Pero estos portales fallaron en su propósito, nadie ha sido llevado a Tayasal en los últimos 25 años...";
		if (CheckAttribute(pchar, "questTemp.Dolly"))
		{
			link.l1 = "Claro... Porque estos portales transfieren a las personas capturadas solo entre sí. ¡Increíble!";
			link.l1.go = "guardoftruth_15a";
		}
		else
		{
			link.l1 = "Interesante...";
			link.l1.go = "guardoftruth_16";
		}
		break;

	case "guardoftruth_15a":
		dialog.text = "¿Has visto esos portales? ¡Dime!";
		link.l1 = "Quizás más tarde, Gino... Estoy más interesado en tu historia en este momento. ¡Continúa!";
		link.l1.go = "guardoftruth_16";
		break;

	case "guardoftruth_16":
		dialog.text = "El Padre Vincento está al tanto de todo lo que te he contado. Esto le preocupó, por supuesto. Si Kukulcán, encarnado en forma humana, llega al portal junto con la Máscara y todo el conocimiento que ha reunido... Fin de los tiempos. Apocalipsis.\nSi el pasado se altera, el futuro hace lo mismo. Nuestra realidad cambiará, desaparecerá, se disolverá. Tú y yo quizás nunca nazcamos. O seremos diferentes. Una vez que Kukulcán alcance el pasado, dejaremos de existir.";
		link.l1 = "¿Y quién es la encarnación de Kukulcán?";
		link.l1.go = "guardoftruth_17";
		break;

	case "guardoftruth_17":
		dialog.text = "Quién sabe. Podría estar en cualquiera que haya nacido hace un cuarto de siglo, cuando se llevó a cabo el ritual. En ti, por ejemplo... es broma. Pero aún tenemos una oportunidad. Primero, la encarnación de Kukulcán es solo una persona mortal, puede ahogarse, ser apuñalado, recibir un disparo o morir de fiebre. Y en tal caso, nunca ocurrirá ningún apocalipsis.\nSegundo, es imposible alcanzar el pasado sin la máscara, Kanek la escondió muy bien, tal vez demasiado bien parece. Podría ser, que incluso el Kukulcán encarnado no logre encontrarla.";
		link.l1 = "Cuéntame más.";
		link.l1.go = "guardoftruth_18";
		break;

	case "guardoftruth_18":
		dialog.text = "Algún tiempo después del ritual, un grupo de conquistadores españoles casi llegó a Tayasal y casi llegó al tesoro. Los Itza lograron matar a todos, excepto a uno: un gigante fuerte de siete pies de altura.\nKanek estaba preocupado de que la Máscara pudiera ser robada por cualquier extraño, así que decidió proteger la reliquia. Inventó su propio ritual, usando el conocimiento de los antiguos mayas. Tomó tres objetos que, él creía, poseían el poder del hombre blanco. Un puñal, que una vez perteneció al propio Cortés, y una brújula. También usó ese puñal para cortar un trozo de piel de la espalda del gigante español capturado como el tercer objeto. El hombre mismo fue sacrificado en el altar de Kukulcán. Tres objetos fueron utilizados en el ritual.\nY de este ritual nació una nueva isla, en mar abierto, no lejos de Yucatán. Nadie conoce su ubicación, pero la Máscara está escondida allí. Para encontrarla, uno debe usar el puñal, la brújula y el trozo de piel. Además, todos los objetos del tesoro están malditos, ninguno de ellos puede salir del archipiélago.\nUn intento de hacerlo causará una tormenta que llevará el barco directamente a las rocas de la isla donde está escondida la máscara. Se llama Ksocheatem. Astuto, ¿verdad?";
		link.l1 = "Tal vez demasiado inteligente. No se puede discutir eso. Pero, ¿cómo demonios estaba Ksatl Cha tan bien informado? Dudo que Kanek compartiera tal conocimiento con guerreros comunes...";
		link.l1.go = "guardoftruth_19";
		break;

	case "guardoftruth_19":
		dialog.text = "La cosa es que el actual jefe de los Itza, Urakan, el hijo de Kanek, le había contado todo a este guerrero. Envió a Ksatl Cha con un grupo de guerreros para encontrar la isla secreta y la Máscara de Kukulcán. Le había dado el Guardián de la Verdad para hacerlo, es el nombre de los tres objetos juntos: el puñal, la brújula y el mapa hecho de piel humana.";
		link.l1 = "¿El mapa? ¿Y por qué necesitaba Urakan la Máscara? ¿Decidió alterar el pasado él mismo?";
		link.l1.go = "guardoftruth_20";
		break;

	case "guardoftruth_20":
		dialog.text = "La piel tiene contornos del archipiélago en ella, por eso la llaman el mapa. Urakan quería la Máscara por una razón muy simple: no quiere destruir la realidad existente ni sacrificar su vida y las vidas de su gente para la gloria de los antiguos. \nPor eso iba a destruir la Máscara a toda costa. Pero Ksatl Cha fue capturado por Calhoun y... bueno, ya conoces el resto de la historia. Nunca llegó a Ksocheatem.";
		link.l1 = "¿Entonces es posible prevenir el fin de los tiempos encontrando y destruyendo la Máscara? ¿Y dónde está ahora ese... Guardián de la Verdad?";
		link.l1.go = "guardoftruth_21";
		break;

	case "guardoftruth_21":
		dialog.text = "La daga 'Garra del Jefe' y la brújula 'Flecha del Camino' fueron dejadas a Calhoun y el mapa de piel 'De dos apariencias' todavía está en algún lugar de la inquisición. Calhoun lo usó como mordaza para cerrar la boca del prisionero. No tenía idea para qué servían estos objetos.";
		link.l1 = "¿Qué acabas de decir? ¿'Garra del Jefe'? ¡Maldita sea, esta daga la tengo conmigo ahora mismo! ¡Fadey me la ha dado como pago de su deuda con mi hermano! ¡Echa un vistazo!";
		link.l1.go = "guardoftruth_22";
		break;

	case "guardoftruth_22":
		dialog.text = "Increíble... Realmente lo es. Lo recuerdo.";
		link.l1 = "Gino, dime, ¿qué exactamente sabe el padre Vincento de tu historia?";
		link.l1.go = "guardoftruth_23";
		break;

	case "guardoftruth_23":
		dialog.text = "Todo, excepto la información sobre el Guardián de la Verdad y cómo hacer que muestre la ubicación de la isla secreta donde está escondida la Máscara de Kukulcán. Ksatl Cha me contó sobre eso cuando estábamos solos justo antes de que le diera una mezcla de veneno para terminar con su sufrimiento. Murió con una sonrisa en el rostro. \nPor supuesto, no podía quedarme en Santiago después de lo que hice. Tenía serias sospechas de que me había convertido en un testigo importante y peligroso para el inquisidor. El Padre Vincento siempre obtiene lo que quiere, sin importar el costo. Ksatl Cha le habló sobre el tesoro en Tayasal.";
		link.l1 = "Estos tesoros ya fueron encontrados por un aventurero llamado Miguel Dichoso. ¿Has oído hablar de él?";
		link.l1.go = "guardoftruth_24";
		break;

	case "guardoftruth_24":
		dialog.text = "No. ¿Y dónde está él ahora con sus tesoros?";
		link.l1 = "Yo mismo quiero saberlo. Por eso vine a ti, estoy buscando ese oro indio. Dichoso ha llevado los tesoros a Europa y desaparecido con ellos.";
		link.l1.go = "guardoftruth_25";
		break;

	case "guardoftruth_25":
		dialog.text = "Te diré dónde están los tesoros y el mismo Dichoso.";
		link.l1 = "Gino, me sorprendes. ¿Cómo lo sabrías?!";
		link.l1.go = "guardoftruth_26";
		break;

	case "guardoftruth_26":
		dialog.text = "Eres capaz de deducirlo tú mismo a partir de mi historia, Capitán. Los tesoros de Tayasal estaban malditos - ni un solo objeto puede ser llevado del archipiélago. Cualquier barco...";
		link.l1 = "... ¡serán atrapados por la tormenta y arrojados a la isla donde se esconde la Máscara de Kukulcán! Yo estaba ciego, pero ahora veo. Parece que sé lo suficiente para encontrar a Ksocheatem, los tesoros y la propia Máscara!";
		link.l1.go = "guardoftruth_27";
		break;

	case "guardoftruth_27":
		dialog.text = "¿Quieres salvar el mundo, Capitán?";
		link.l1 = "Quiero encontrar a mi hermano pródigo... Gino, ¿cómo puedo hacer que el Guardián de la Verdad me muestre la ubicación de la isla? ¡Dijiste que sabías cómo!";
		link.l1.go = "guardoftruth_28";
		break;

	case "guardoftruth_28":
		dialog.text = "Conozco el método, pero no sé los detalles. No podré ayudarte hasta que tenga todos los componentes del Guardián.";
		link.l1 = "Mm. Ya tenemos el puñal. Solo quedan la brújula y el mapa. Calhoun tiene la brújula y el padre Vincento tiene el mapa...";
		link.l1.go = "guardoftruth_29";
		break;

	case "guardoftruth_29":
		dialog.text = "¿Vas a regresar al inquisidor? Pero, ¿cómo vas a informar sobre...?";
		link.l1 = "Tengo que convencer al padre Vincento de que estás muerto, Gino. Solo entonces detendrá sus búsquedas. Digamos que tuviste un ataque repentino al verme. Debes darme un objeto que pueda usar como prueba de tu muerte.";
		link.l1.go = "guardoftruth_30";
		break;

	case "guardoftruth_30":
		dialog.text = "Vincento no creerá en la versión del ataque al corazón, pero te creerá si le dices que me suicidé bebiendo algún veneno con olor a almendra. Dale mi almanaque, sabe que nunca me separo de él.";
		link.l1 = "Está bien. Porque necesito esa conexión con el inquisidor. Probablemente sabe mucho sobre nuestro negocio.";
		link.l1.go = "guardoftruth_31";
		break;

	case "guardoftruth_31":
		dialog.text = "Ten cuidado con el padre Vincento. Es tan peligroso como un tigre y juega su propio juego. No compartirá ni tesoros ni fama contigo.";
		link.l1 = "Entiendo eso. Está bien, Gino, dame tu almanaque y trata de recordar lo que te dijo el indio sobre el Guardián de la Verdad, porque quiero ensamblarlo. Necesito encontrar a Ksocheatem, estoy seguro de que allí encontraré no solo la máscara y los tesoros, sino también a mi querido hermano.";
		link.l1.go = "guardoftruth_32";
		break;

	case "guardoftruth_32":
		dialog.text = "Tómalo. ¡Buena suerte, capitán!";
		link.l1 = "No me estoy despidiendo, Gino...";
		link.l1.go = "guardoftruth_33";
		break;

	case "guardoftruth_33":
		DialogExit();
		Log_Info("Has recibido un almanaque");
		PlaySound("interface\important_item.wav");
		GiveItem2Character(pchar, "Almanac");
		ChangeItemDescribe("Almanac", "itmdescr_jinobook");
		pchar.questTemp.Guardoftruth = "twoitems";
		AddQuestRecord("Guardoftruth", "37");
		break;

	case "guardoftruth_34":
		dialog.text = "¿Fue difícil, Capitán?";
		link.l1 = "No hablemos de ello... Demasiadas personas murieron por conseguir estos objetos. Demasiadas. Parece que no soy el único ansioso por encontrar al misterioso Ksocheatem. ";
		link.l1.go = "guardoftruth_35";
		break;

	case "guardoftruth_35":
		dialog.text = "Me lo imagino... Por cierto, ¿cómo está el padre Vincento? ¿Te comunicas regularmente con él?";
		link.l1 = "Por ahora sí, pero creo que ya no hay necesidad de hacerlo. Tengo todos los componentes del Guardián de la Verdad, lo que significa que tengo la clave para la ubicación de Ksocheatem. No estoy ansioso por informar de mi éxito a Su Gracia por alguna razón.";
		link.l1.go = "guardoftruth_36";
		break;

	case "guardoftruth_36":
		dialog.text = "Ten cuidado, " + pchar.name + ". El padre Vincento tiene cientos de ojos y manos. Manos muy largas...";
		link.l1 = "He pasado por mucho en los últimos meses y en este punto ciertamente no tengo miedo, ni del padre Vincento ni de sus ojos y manos. Lo que sea. Es hora de que encontremos a Ksocheatem usando los componentes del Guardián. ¿Sabes cómo hacer eso?";
		link.l1.go = "guardoftruth_37";
		break;

	case "guardoftruth_37":
		dialog.text = "No realmente. Ksatl Cha fue bastante vago. Creo que el indio realmente no sabía cómo hacer funcionar al Guardián. Déjame los componentes y trataré de resolverlo. Ven a verme en dos días y quizás haya resuelto este enigma.";
		link.l1 = "Está bien, Gino. Cuento contigo. Aquí, tómelos.";
		link.l1.go = "guardoftruth_38";
		break;

	case "guardoftruth_38":
		dialog.text = "Puedes estar seguro de que estarán a salvo y en una sola pieza conmigo.";
		link.l1 = "No lo dudo. Bueno, no te molestaré por ahora, Gino. ¡Buena suerte con tu investigación!";
		link.l1.go = "guardoftruth_39";
		break;

	case "guardoftruth_39":
		DialogExit();
		NextDiag.CurrentNode = "First time";
		RemoveItems(pchar, "knife_01", 1);
		RemoveItems(pchar, "skinmap", 1);
		RemoveItems(pchar, "arrowway", 1);
		pchar.questTemp.Guardoftruth = "end";
		SetFunctionTimerCondition("Ksochitam_StartSearchIsland", 0, 0, 2, false);
		CloseQuestHeader("Guardoftruth");
		AddQuestRecord("Ksochitam", "1");
		break;

	case "ksochitam":
		dialog.text = "En parte. Quiero decir, tengo algo, pero no sé cómo hacer que todo funcione de verdad. Intentemos resolver este rompecabezas juntos.";
		link.l1 = "¡Intentémoslo! Dame tus ideas.";
		link.l1.go = "ksochitam_1";
		break;

	case "ksochitam_1":
		dialog.text = "Ksatl Cha dijo algo así: 'La Garra del Jefe hará que el mapa se revele. La Flecha del Camino mostrará la dirección de las apariciones.";
		link.l1 = "¿Y qué has logrado hacer?";
		link.l1.go = "ksochitam_2";
		break;

	case "ksochitam_2":
		dialog.text = "He adivinado cómo hacer que el mapa se 'revele'. ¿Has echado un vistazo al mapa de Dos Apariciones?";
		link.l1 = "Hm. ¿Y hubo algo especial? Unos contornos ocultos del archipiélago...";
		link.l1.go = "ksochitam_3";
		break;

	case "ksochitam_3":
		GiveItem2Character(pchar, "skinmap");
		dialog.text = "Tómalo y vuelve a mirar. Sé atento.";
		link.l1 = "Bueno, hagámoslo si insistes.";
		link.l1.go = "ksochitam_4";
		break;

	case "ksochitam_4":
		DialogExit();
		NextDiag.CurrentNode = "ksochitam_wait";
		pchar.questTemp.Ksochitam = "skinmap_1";
		chrDisableReloadToLocation = true; // закрыть локацию
		break;

	case "ksochitam_wait":
		dialog.text = "No has echado un vistazo al mapa, " + pchar.name + "...";
		link.l1 = "Sí-sí, lo haré ahora...";
		link.l1.go = "exit";
		NextDiag.TempNode = "ksochitam_wait";
		break;

	case "ksochitam_5":
		dialog.text = "";
		link.l1 = "He visto. No vi nada nuevo. Sólo algunas formas oscurecidas de islas y del continente. ¿Qué se supone que debo ver allí?";
		link.l1.go = "ksochitam_6";
		break;

	case "ksochitam_6":
		dialog.text = "Espera un segundo. Ahora tienes que hacer que este mapa se revele. Toma el puñal y toca suavemente el mapa con el filo. No empujes, necesitamos evitar cualquier daño. Toma el puñal. ¡Y obsérvalo cuidadosamente!";
		link.l1 = "¡Interesante! Vamos a ver...";
		link.l1.go = "ksochitam_7";
		break;

	case "ksochitam_7":
		DialogExit();
		GiveItem2Character(pchar, "knife_01");
		NextDiag.CurrentNode = "ksochitam_wait";
		pchar.questTemp.Ksochitam = "skinmap_2";
		sld = ItemsFromID("skinmap");
		sld.mark = 2;
		break;

	case "ksochitam_8":
		dialog.text = "Bueno, ¿ves alguna diferencia ahora?";
		link.l1 = "Sí. Cuando tocas el mapa con la daga, aparecen dos marcas de calaveras y siempre están en los mismos lugares...";
		link.l1.go = "ksochitam_9";
		break;

	case "ksochitam_9":
		dialog.text = "En los DOS mismos lugares, " + pchar.name + "¡Por eso se llamaba el mapa de las Dos Apariencias!";
		link.l1 = "¿Y qué significa eso?";
		link.l1.go = "ksochitam_10";
		break;

	case "ksochitam_10":
		dialog.text = "Mucho, creo... Pero más acertijos vienen a continuación. Supongo que estos cráneos son las apariciones de las que hablaba Ksatl Cha. Así que la brújula debe mostrar la dirección correcta a Ksocheatem desde ellos. ¿Has visto la brújula, " + pchar.name + "?";
		link.l1 = "Sí. Parece una brújula naval ordinaria, pero se comporta de manera extraña, su flecha se sacude en diferentes direcciones o comienza a girar a una velocidad salvaje.";
		link.l1.go = "ksochitam_11";
		break;

	case "ksochitam_11":
		dialog.text = "Pensé que al plantar la brújula sobre las calaveras detendría su flecha y mostraría alguna dirección clara en el mapa. Para lograrlo, la planté en una calavera y luego en la otra mientras tocaba el mapa con la daga.";
		link.l1 = "¿Y?";
		link.l1.go = "ksochitam_12";
		break;

	case "ksochitam_12":
		dialog.text = "Infructuosamente. La brújula no cambió su comportamiento. La flecha sigue girando salvajemente. Parece que estoy haciendo algo mal. O no entendí correctamente las palabras de Ksatl Cha.";
		link.l1 = "¿Entonces el puñal y el mapa funcionan y la brújula no?";
		link.l1.go = "ksochitam_13";
		break;

	case "ksochitam_13":
		dialog.text = "La Flecha del Camino debe estar operativa con certeza, simplemente no sabemos cómo hacer que funcione, todavía." + pchar.name + ",  conoces la geografía del archipiélago mejor que yo... Dime, ¿qué lugares revela el mapa de las dos apariencias?";
		link.l1 = "¡Un segundo! (echando un vistazo)... Bueno-bueno... La apariencia a la izquierda es el continente occidental. La de la derecha parece la isla de Dominica. Algo así.";
		link.l1.go = "ksochitam_14";
		break;

	case "ksochitam_14":
		dialog.text = "Y dime: ¿hay... algo notable en esos lugares?";
		link.l1 = "¿Qué quieres decir?";
		link.l1.go = "ksochitam_15";
		break;

	case "ksochitam_15":
		dialog.text = "No estoy seguro yo mismo... Bueno, ¿algo especial?";
		link.l1 = "Gino, no hables en acertijos. Explícalo sencillamente.";
		link.l1.go = "ksochitam_16";
		break;

	case "ksochitam_16":
		dialog.text = "Solo puedo suponer que estas calaveras nos muestran algunos lugares reales. La Flecha del Camino no funciona mientras está colocada en las apariencias del mapa. ¿Quizás funcionará cerca de las apariencias geográficas reales que fueron reveladas por el mapa?";
		link.l1 = "¡Gino, eres un genio! ¿Tierra Firme occidental, Dominica? Las calaveras son demasiado grandes para mostrar las ubicaciones exactas.";
		link.l1.go = "ksochitam_17";
		break;

	case "ksochitam_17":
		chrDisableReloadToLocation = false; // открыть локацию
		dialog.text = "" + pchar.name + ", hagamos lo siguiente: Tráeme un mapa de papel del archipiélago, combínalo con el mapa de Dos Apariciones y marca las apariciones con cruces. ¿Quizás esto te dará algunas suposiciones?";
		if (CheckCharacterItem(pchar, "map_bad"))
		{
			link.l1 = "Tengo este viejo mapa del archipiélago.";
			link.l1.go = "ksochitam_17_1";
		}
		if (CheckCharacterItem(pchar, "map_normal"))
		{
			link.l2 = "Tengo este fino mapa del archipiélago.";
			link.l2.go = "ksochitam_17_2";
		}
		if (CheckCharacterItem(pchar, "Map_Best"))
		{
			link.l3 = "Tengo este excelente mapa del archipiélago.";
			link.l3.go = "ksochitam_17_3";
		}
		link.l4 = "Trato hecho. Te traeré un mapa y continuaremos...";
		link.l4.go = "ksochitam_17_4";
		break;

	case "ksochitam_17_1":
		dialog.text = "Vamos, " + pchar.name + "¡Este pergamino de la época de Colón no es mucho mejor que el mapa de piel. Estoy seguro de que hay algo mejor que esta basura en el mundo. ¡Tráeme otro mapa, uno más nuevo!";
		link.l1 = "Bien...";
		link.l1.go = "exit";
		NextDiag.TempNode = "ksochitam_map_wait";
		break;

	case "ksochitam_17_2":
		dialog.text = "¡Espléndido! Ahora marca los lugares de las apariciones en él. Será más fácil construir suposiciones.";
		link.l1 = "¡Un segundo, Gino!";
		link.l1.go = "ksochitam_18";
		break;

	case "ksochitam_17_3":
		dialog.text = "De ninguna manera arruinaremos un mapa tan maravilloso con nuestras marcas. Lo necesitarás tú mismo, " + pchar.name + "¡Tráeme otro mapa, uno un poco más modesto!";
		link.l1 = "Está bien...";
		link.l1.go = "exit";
		NextDiag.TempNode = "ksochitam_map_wait";
		break;

	case "ksochitam_17_4":
		DialogExit();
		NextDiag.CurrentNode = "ksochitam_map_wait";
		break;

	case "ksochitam_map_wait":
		dialog.text = "¿Me has traído un mapa del archipiélago, " + pchar.name + "?";
		if (CheckCharacterItem(pchar, "map_bad"))
		{
			link.l1 = "Tengo este viejo mapa del archipiélago.";
			link.l1.go = "ksochitam_17_1";
		}
		if (CheckCharacterItem(pchar, "map_normal"))
		{
			link.l2 = "Tengo este fino mapa del archipiélago.";
			link.l2.go = "ksochitam_17_2";
		}
		if (CheckCharacterItem(pchar, "Map_Best"))
		{
			link.l3 = "Tengo este excelente mapa del archipiélago.";
			link.l3.go = "ksochitam_17_3";
		}
		link.l4 = "Aún no, pero ya lo he encargado. Pronto lo tendré y continuaremos...";
		link.l4.go = "ksochitam_17_4";
		break;

	case "ksochitam_18":
		chrDisableReloadToLocation = true; // закрыть локацию
		DialogExit();
		NextDiag.CurrentNode = "ksochitam_19";
		LAi_SetActorType(pchar);
		LAi_ActorGoToLocator(pchar, "goto", "goto1", "Ksochitam_SitTable", -1);
		break;

	case "ksochitam_19":
		dialog.text = "";
		link.l1 = "Hecho... He creado las marcas, pero todavía es información inexacta. El primer lugar está en algún lugar al noroeste de Blueweld. El segundo está en el centro de la isla Dominica.";
		link.l1.go = "ksochitam_20";
		break;

	case "ksochitam_20":
		dialog.text = "¿Alguna idea?";
		link.l1 = "No. Pero creo que deberíamos llevar la Flecha del Camino allí y observar su comportamiento. Por supuesto, es como buscar una aguja en un pajar, pero de todos modos no tenemos mejores ideas.";
		link.l1.go = "ksochitam_21";
		break;

	case "ksochitam_21":
		dialog.text = "Estoy de acuerdo contigo, " + pchar.name + ". ¿Me dejarás navegar contigo?";
		link.l1 = "¿Estás interesado en comprobar tus suposiciones? Sería un honor tenerte en las cubiertas de mi barco, Gino. ¡Empaca tus cosas!";
		link.l1.go = "ksochitam_22";
		break;

	case "ksochitam_22":
		dialog.text = "No tomará mucho tiempo. Estaré listo en unas pocas horas. Aquí, toma la Flecha del Camino.";
		link.l1 = "¡Bienvenido a bordo!";
		link.l1.go = "ksochitam_23";
		break;

	case "ksochitam_23":
		LAi_SetOwnerType(npchar);
		DialogExit();
		NextDiag.CurrentNode = "ksochitam_24";
		chrDisableReloadToLocation = false; // открыть локацию
		LAi_SetPlayerType(pchar);
		GiveItem2Character(pchar, "arrowway");
		pchar.questTemp.Ksochitam = "seekway";
		sld = ItemsFromID("skinmap");
		sld.mark = 1;
		pchar.quest.Ksochitam_room.win_condition.l1 = "ExitFromLocation";
		pchar.quest.Ksochitam_room.win_condition.l1.location = pchar.location;
		pchar.quest.Ksochitam_room.function = "Ksochitam_JinoPassenger";
		AddQuestRecord("Ksochitam", "2");
		break;

	case "ksochitam_24":
		dialog.text = "Sí-sí, " + pchar.name + ", me estoy preparando. Estaré listo pronto.";
		link.l1 = "...";
		link.l1.go = "exit";
		NextDiag.TempNode = "ksochitam_24";
		break;

	case "ksochitam_25":
		dialog.text = "¿Y qué, " + pchar.name + ", ¿tenemos suerte en nuestras búsquedas?";
		link.l1 = "Tuvimos razón. Esto es. El ídolo indio es una de las apariencias.";
		link.l1.go = "ksochitam_26";
		break;

	case "ksochitam_26":
		dialog.text = "¡Oh! Debe ser uno de esos ídolos que supuestamente teleportaban a la gente a Tayasal. Te estaba contando sobre ellos, ¿recuerdas? Entonces, ¿hacia dónde apunta la Flecha del Camino?";
		link.l1 = "Está orientado al noroeste. He marcado la dirección en un mapa. Aunque la línea dibujada cruza casi todo el mar Caribe. Tenemos que encontrar otra aparición en Dominica para hallar a Ksocheatem.";
		link.l1.go = "ksochitam_27";
		break;

	case "ksochitam_27":
		dialog.text = "Estoy seguro de que encontraremos otro ídolo allí... ¿estás de acuerdo con mi hipótesis, " + pchar.name + "?";
		link.l1 = "Lo hago, Gino. Ahora no perdamos tiempo y empecemos a buscar.";
		link.l1.go = "ksochitam_28";
		break;

	case "ksochitam_28":
		DialogExit();
		locations[FindLocation(pchar.location)].DisableEncounters = false; // энкаутеры открыть
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 20.0);
		break;

	case "ksochitam_29":
		dialog.text = "¿Y qué? " + pchar.name + ", ¿has encontrado algo de interés?";
		link.l1 = "Teníamos razón. Esto es. El ídolo indio es una de las apariciones.";
		link.l1.go = "ksochitam_30";
		break;

	case "ksochitam_30":
		dialog.text = "¡Oh! ¡Debe ser uno de esos ídolos que se suponía teletransportaban a la gente a Tayasal! Te estaba hablando de ellos, ¿recuerdas? Entonces, ¿a dónde apunta la Flecha del Camino?";
		link.l1 = "Noroeste. He marcado la dirección en un mapa. Aunque la línea dibujada cruza casi todo el mar Caribe. Tenemos que encontrar otra aparición en el Continente para encontrar a Ksocheatem.";
		link.l1.go = "ksochitam_27";
		break;

	case "ksochitam_31":
		dialog.text = "Entonces, ¿qué, " + pchar.name + ", ¿has encontrado el segundo ídolo?";
		link.l1 = "Sí. He trazado la dirección que fue mostrada por la Flecha del Camino. Ahora sabemos la ubicación de Ksocheatem, no es la ubicación exacta, ¡pero sabemos dónde buscar! Buscaré toda el área donde se cruzan las líneas y encontraré esa maldita isla.";
		link.l1.go = "ksochitam_32";
		break;

	case "ksochitam_32":
		dialog.text = "Me alegra escuchar tanto entusiasmo en tu voz. Pero tenemos que prepararnos bien para la próxima expedición, es incierto lo que encontraremos allí. Dudo que recibamos una cálida bienvenida allí...";
		link.l1 = "¿Te preocupa algo en específico o solo estás expresando inquietudes?";
		link.l1.go = "ksochitam_33";
		break;

	case "ksochitam_33":
		dialog.text = "Piensa en ello, " + pchar.name + ".. Ksocheatem fue creado por magia maya realizada por Kanek. No es una formación natural y tiene poderes malignos y destructivos. Es desconocido lo que nos espera allí, dudo que encontremos sol, mares tranquilos, putas y viento calmo allí.";
		link.l1 = "Está bien, Gino. Consideraré tus palabras y me prepararé para la expedición. Pondré mi barco a punto y me ocuparé de las pociones y municiones...";
		link.l1.go = "ksochitam_34";
		break;

	case "ksochitam_34":
		dialog.text = "Una decisión muy sabia. Bueno, ¿volvemos al barco?";
		link.l1 = "¡Por supuesto! ¡Vamos!";
		link.l1.go = "ksochitam_28";
		break;

	case "ksochitam_35":
		dialog.text = "Hemos llegado, " + pchar.name + "¡Uh, el viento está aullando!";
		link.l1 = "Sí, Gino, tenías razón, no hay sol para recibirnos... Tampoco veo prostitutas. En realidad, no se sabe qué nos espera aquí en absoluto.";
		link.l1.go = "ksochitam_36";
		break;

	case "ksochitam_36":
		dialog.text = "¡Vaya, has elegido un lugar tan malo para desembarcar, capitán! ¡Solo rocas y acantilados por todas partes! ¿Y cómo piensas llegar al interior de la isla desde aquí?";
		link.l1 = "¡No vi ninguna otra bahía adecuada para desembarcar en esta isla por esta maldita tormenta! Sea como sea, esto es mejor que nada. Me las arreglaré para encontrar mi camino entre estas rocas, he tenido peores. ¡No te asustes, amigo!";
		link.l1.go = "ksochitam_37";
		break;

	case "ksochitam_37":
		dialog.text = "No me gusta esta isla, " + pchar.name + "¡Es espeluznante! Y esta tormenta debe estar ligada a la isla. Este lugar está condenado, ¡eso es seguro!";
		link.l1 = "¡Tampoco me gusta mucho este lugar, Gino! Pero esta isla sí existe, lo que significa que la historia de Kukulcán es verdadera. Todos estaremos en peligro si logra llegar a Tayasal con la Máscara...";
		link.l1.go = "ksochitam_38";
		break;

	case "ksochitam_38":
		dialog.text = "¡Intenta encontrar la Máscara, Capitán! ¡Es más importante que todos los tesoros del mundo! ¡Debe estar por algún lado! Una vez que la tengamos, destruiremos los planes de Kukulcán y no le dejaremos alterar el pasado!";
		link.l1 = "¿Y cómo se ve esta máscara, lo sabes?";
		link.l1.go = "ksochitam_39";
		break;

	case "ksochitam_39":
		dialog.text = "¡Ni idea! Pero creo que lo reconocerás, es un artefacto indio antiguo, ¡es difícil confundirlo con cualquier otra cosa!";
		link.l1 = "Ya veo. ¡Mantendré los ojos abiertos! Bien, ¡Gino, regresa al barco! No tienes que caminar por la isla, tu cabeza es demasiado valiosa para arriesgarla.";
		link.l1.go = "ksochitam_40";
		break;

	case "ksochitam_40":
		dialog.text = "No voy a mentir, Capitán, soy un luchador pésimo y no me siento cómodo en este lugar. ¿Le gustaría escuchar un consejo? Cada componente del Guardián está conectado a la magia de esta isla. Ksatl Cha mencionó que la daga tiene poder sobre los habitantes locales, aunque no sé a qué se refería.\nMe quedaré a bordo. Búsqueme allí si necesita mi ayuda.";
		link.l1 = "Bien. ¡Y ahora deséame suerte, Gino!";
		link.l1.go = "ksochitam_41";
		break;

	case "ksochitam_41":
		dialog.text = "Buena suerte, " + pchar.name + "¡Que Dios te favorezca y te preserve!";
		link.l1 = "... ";
		link.l1.go = "ksochitam_42";
		break;

	case "ksochitam_42":
		DialogExit();
		NextDiag.CurrentNode = "adversary";
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "My_Campus", "rld", "aloc0", "Ksochitam_JinoStay", 10.0);
		AddQuestRecord("Ksochitam", "6");
		break;

	case "adversary":
		dialog.text = "¿Cómo te va, " + pchar.name + "¿Necesitas un consejo?";
		if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L1"))
		{
			link.l1 = "Esta maldita isla está infestada de muertos vivientes y esos malditos esqueletos son sorprendentemente duros. No tengo idea de cómo luchar contra ellos.";
			link.l1.go = "adversary_1";
		}
		if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L2"))
		{
			link.l1 = "Si vas a la izquierda en la bifurcación, eventualmente llegarás a la caverna. Pero, ¿a dónde debería ir después? Temo que la caverna sea un callejón sin salida...";
			link.l1.go = "adversary_2";
		}
		if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L3"))
		{
			link.l1 = "He encontrado mi camino dentro de la caverna húmeda, puedes sumergirte en su parte submarina. Pero no veo ninguna salida desde allí...";
			link.l1.go = "adversary_3";
		}
		if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L4"))
		{
			link.l1 = "Si vas a la izquierda en la bifurcación, llegarás a la caverna. Pero, ¿a dónde debo ir después? Temo que la caverna sea un callejón sin salida...";
			link.l1.go = "adversary_4";
		}
		if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L5"))
		{
			link.l1 = "Hay un lugar en la gran caverna donde puedes bucear en la parte inundada. Pero parece que no hay salida de allí...";
			link.l1.go = "adversary_5";
		}
		link.l10 = "Todo está bien hasta ahora, Gino, estoy bien.";
		link.l10.go = "exit";
		NextDiag.TempNode = "adversary";
		break;

	case "adversary_1":
		dialog.text = "Ksatl Cha mencionó la Garra del Jefe. Intenta usarla contra los esqueletos, el indio dijo que este puñal tiene poder sobre los habitantes de Ksocheatem.";
		link.l1 = "¡Lo intentaré seguro!";
		link.l1.go = "exit";
		DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L1");
		break;

	case "adversary_2":
		dialog.text = "¿Y cómo es esta cueva?";
		link.l1 = "Bueno, hay una pequeña cueva en una roca, está húmeda y el agua se balancea en el fondo como las olas...";
		link.l1.go = "adversary_2_1";
		break;

	case "adversary_2_1":
		dialog.text = "Si el agua se mueve, entonces la caverna tiene alguna conexión con el mar y no puede ser un callejón sin salida. Busca un pasaje, debe estar allí.";
		link.l1 = "En camino...";
		link.l1.go = "exit";
		DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L2");
		break;

	case "adversary_3":
		dialog.text = "Si hay un camino hacia la caverna inundada desde la principal y si el agua se balancea como un oleaje en la caverna principal, entonces la cueva inundada tiene un segundo pasaje. Búscala mejor, pero ten cuidado o te ahogarás.";
		link.l1 = "Voy a zambullirme...";
		link.l1.go = "exit";
		DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L3");
		break;

	case "adversary_4":
		dialog.text = "¿Y cómo luce esta cueva?";
		link.l1 = "Bueno, es bastante grande con unas pocas cavernas, está húmedo y hay un pequeño agujero con agua estancada...";
		link.l1.go = "adversary_4_1";
		break;

	case "adversary_4_1":
		dialog.text = "Si el agua está tranquila, entonces la cueva no tiene conexión con el mar y podría ser un callejón sin salida.";
		link.l1 = "Pensé lo mismo. He estado buscando allí por mucho tiempo y solo hay una entrada que también es una salida...";
		link.l1.go = "exit";
		DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L4");
		break;

	case "adversary_5":
		dialog.text = "Si el agua sigue en la caverna entonces, quizás, tienes razón. Busca un poco más, pero no te entristezcas si no encuentras nada. Es probable que sea un callejón sin salida.";
		link.l1 = "Ya veo...";
		link.l1.go = "exit";
		DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L5");
		break;

	case "adversary_6":
		dialog.text = "" + pchar.name + ", ¡los barcos españoles nos están siguiendo! ¡No es el mejor momento para hablar!";
		link.l1 = "Sí, claro...";
		link.l1.go = "exit";
		NextDiag.TempNode = "adversary_6";
		break;

	case "ksochitam_43":
		dialog.text = "Tus ojos felices me dicen que has encontrado lo que buscabas.";
		link.l1 = "Sí. Tesoros de Miguel Dichoso y la Máscara de Kukulcán. ¡Ahora su encarnación nunca podrá cambiar el futuro!";
		link.l1.go = "ksochitam_44";
		break;

	case "ksochitam_44":
		dialog.text = "¡Increíble! Eres un héroe, " + pchar.name + "...";
		link.l1 = "Gino, ¿estás seguro de que esto es suficiente para detener a Kukulcán?";
		link.l1.go = "ksochitam_45";
		break;

	case "ksochitam_45":
		dialog.text = "Según Ksatl Cha - sí. Y estaba citando a Urakan. Su padre Kanek fue quien comenzó todo este lío. ¿Alguna duda?";
		link.l1 = "He sido recibido en la bahía por un invitado del pasado - Alonso de Maldonado. Estaba en Tayasal cuando Kanek estaba realizando el ritual para crear al Guardián de la Verdad. Fue arrastrado al agujero espaciotemporal, y sin embargo, permaneció con vida... Hasta hoy.";
		link.l1.go = "ksochitam_46";
		break;

	case "ksochitam_46":
		dialog.text = "";
		link.l1 = "Dijo que tengo que cerrar el portal mismo para proteger nuestro mundo de una vez por todas. Para hacerlo, tengo que destruir la Máscara en algún altar en Tayasal.";
		link.l1.go = "ksochitam_47";
		break;

	case "ksochitam_47":
		dialog.text = "¿Y vas a ir a Tayasal? ¡Esto es una locura! " + pchar.name + ", ¡tienes la máscara y la encarnación de Kukulcán no podrá hacer nada! ¡Y Kanek mismo está seguro de eso! ¡Por eso Urakan ha enviado a Ksatl Cha a encontrar a Ksocheatem - para conseguir la Máscara y destruirla!";
		link.l1 = "¿Y qué si este Urakan planeaba destruir la máscara en Tayasal?";
		link.l1.go = "ksochitam_48";
		break;

	case "ksochitam_48":
		dialog.text = "" + pchar.name + ", solo un hombre ha logrado escapar con vida de Tayasal hasta ahora y fue Miguel Dichoso. También Maldonado, pero él fue una excepción. ¡Incluso si la encarnación de Kukulcán llegara al pasado, sería asesinado por los antiguos mayas!";
		link.l1 = "¿Y si no lo matan, sino que lo reconocen?";
		link.l1.go = "ksochitam_49";
		break;

	case "ksochitam_49":
		dialog.text = "¿Entonces estás planeando una expedición a Tayasal?";
		link.l1 = "No lo sé, Gino. Realmente no...";
		link.l1.go = "ksochitam_50";
		break;

	case "ksochitam_50":
		dialog.text = "Entonces piénsalo, ¿por qué harías eso? Has escuchado mi opinión. Ahora depende de ti..." + pchar.name + ", ¿me llevarás a St. John's?";
		link.l1 = "Claro, Gino. Zarpemos tan pronto como sea posible. Ya he tenido suficiente de esta horrible isla.";
		link.l1.go = "ksochitam_51";
		break;

	case "ksochitam_51":
		DialogExit();
		NextDiag.CurrentNode = "ksochitam_52";
		bQuestDisableMapEnter = false; // открыть карту
		DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		DeleteAttribute(pchar, "GenQuest.CannotWait"); // можно мотать время
		AddQuestRecord("Ksochitam", "16");
		pchar.quest.Ksochitam_gohome.win_condition.l1 = "location";
		pchar.quest.Ksochitam_gohome.win_condition.l1.location = "sentjons_town";
		pchar.quest.Ksochitam_gohome.function = "Ksochitam_ArriveHome";
		pchar.questTemp.Ksochitam = "gohome";
		break;

	case "ksochitam_52":
		dialog.text = "¿Estaremos en casa pronto, " + pchar.name + "¿Realmente extraño mis frascos y tubos...?";
		link.l1 = "Sí-sí, Gino, pronto estaremos en Antigua.";
		link.l1.go = "exit";
		NextDiag.TempNode = "ksochitam_52";
		break;

	case "ksochitam_53":
		dialog.text = "¡Me alegra que por fin hayamos vuelto! No puedo imaginar cómo vosotros, marineros, pasáis tanto tiempo en vuestros barcos...";
		link.l1 = "Es cuestión de hábito, Gino.";
		link.l1.go = "ksochitam_54";
		break;

	case "ksochitam_54":
		dialog.text = "Me acostaré en mi cama sobre tierra firme con gran placer... Espero, " + pchar.name + ", que hayas abandonado la idea de visitar Tayasal.";
		link.l1 = "No lo sé aún, Gino. Para ser honesto, todavía no estoy seguro.";
		link.l1.go = "ksochitam_55";
		break;

	case "ksochitam_55":
		dialog.text = "Destruye la máscara de Kukulcán y vive sin preocupaciones, Capitán. Si lo deseas, disolveremos la máscara en el ácido más poderoso que tengo. No guardaré rencor por tal asunto.";
		link.l1 = "Sabes, esperaré un rato. Siempre tendremos tiempo para destruirlo.";
		link.l1.go = "ksochitam_56";
		break;

	case "ksochitam_56":
		dialog.text = "Es tu decisión. Si decides librar a este mundo de este artefacto, ven a mí. ¡Gratitud por un maravilloso viaje, capitán!";
		link.l1 = "En cualquier momento, Gino. ¡Nos vemos!";
		link.l1.go = "exit";
		NextDiag.TempNode = "first time";
		AddDialogExitQuestFunction("Ksochitam_TripComplete");
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	//--> блок реагирования на попытку залезть в сундук
	case "Man_FackYou":
		dialog.text = LinkRandPhrase("Eres un " + GetSexPhrase("¡ladrón, señor! Guardias, llévenlo", "¡ladrona, chica! Guardias, llévensela ") + "!!!", "¡Mira eso! ¡Tan pronto como me perdí en la contemplación, decidiste registrar mi cofre! ¡Atrapen al ladrón!", "¡Guardias! ¡Robo! ¡Atrapen al ladrón!!!");
		link.l1 = "¡Maldita sea!";
		link.l1.go = "exit";
		LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
