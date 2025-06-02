// Addon-2016 Jason, французские миниквесты (ФМК) Последний урок
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		dialog.text = "Un error obvio. Informa a los desarrolladores sobre ello.";
		link.l1 = "Oh, lo haré.";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	case "greguar":
		PlaySound("Voice\Spanish\LE\Greguar\Greguar_04.wav");
		pchar.quest.FMQL_delete_guide.over = "yes";
		DelLandQuestMark(npchar);
		DelMapQuestMarkCity("Fortfrance");
		if (CheckAttribute(pchar, "questTemp.HWIC") || pchar.Ship.Type == SHIP_NOTUSED)
		{
			dialog.text = "Oh, " + GetFullName(pchar) + "¡Te ves diferente, amigo mío, y eres exitoso! Empiezan a hablar de ti, ¿sabes? Aprendes rápido, monsieur, me siento realmente orgulloso de ti. ¡Te deseo más fortunas y suerte en el futuro! ¡Un placer verte de nuevo!";
			link.l1 = "¡Monsieur Gregoire Valinnie, qué encuentro! Le debo mucho por mis humildes logros. ¡Un placer conocerle también! ¡Buena suerte!";
			link.l1.go = "greguar_exit_1";
		}
		else
		{
			dialog.text = "Oh, " + GetFullName(pchar) + "¡Te ves diferente, amigo mío, y eres exitoso! Empiezan a hablar de ti, ¿sabes? Aprendes rápido, monseniour, debo decir que me has hecho sentir orgulloso.";
			link.l1 = "Monsieur Gregoire Valinnie, ¡qué encuentro! Le debo mucho por mis humildes logros. ¡Un placer conocerte! Déjame adivinar, ¿tienes una propuesta de negocio para mí?";
			link.l1.go = "greguar_1";
		}
		break;

	case "greguar_1":
		dialog.text = "¡Ay! Eso hago. Seré breve, el tiempo es oro. Entonces, un escuadrón de la corona holandesa que navegaba de Brasil a Curazao con una carga de bienes de valor estratégico fue emboscado por los ingleses entre Trinidad y el continente. Un filibote de la Compañía logró huir y atracar en la Costa de Boca de la Serpiente. Salvó parte de la carga, pero no por mucho tiempo: fueron atacados por una tribu india. Según mi información, han exterminado a todos los holandeses en esa costa y llevaron la carga a su aldea. Los indios también se apoderaron de las armas de fuego holandesas, pero sufrieron grandes bajas. ¡Esta es nuestra oportunidad! Los británicos y los holandeses todavía están luchando en esa región y están demasiado ocupados para preocuparse por el filibote perdido. Por ahora... Tienes un barco y una tripulación. Podemos navegar allí, desembarcar y acabar con los indios. La carga es extremadamente valiosa y hay una gran cantidad de ella allí. Ya he enviado una pequeña expedición para hacer el reconocimiento, eso era todo lo que podía permitirme, problemas de dinero, ¿recuerdas? Tengo un comprador de confianza, puedes contar con mi espada y mis mercenarios. División al cincuenta por ciento, tenemos una semana para llegar allí. Entonces, amigo mío, ¿estás dentro?";
		link.l1 = "Perdóname, monsieur, pero pasaré. Acabo de llegar de un viaje difícil, no tenemos suficiente tiempo para hacer reparaciones y reclutamiento. Incluso en este lugar olvidado por Dios un hombre no puede tenerlo todo.";
		link.l1.go = "greguar_exit";
		link.l2 = "Suena como un negocio peligroso con olor a buen beneficio y aventuras. ¡Por supuesto que estoy dentro! ¡No perdamos tiempo!";
		link.l2.go = "greguar_2";
		break;

	case "greguar_exit":
		dialog.text = "Lástima. Entonces, es tu decisión. Que Dios te acompañe, monseñor, de todos modos me dirigiré allí. Un hombre debe intentarlo, ¿eh?";
		link.l1 = "¡Buen viento, señor Valinnie!";
		link.l1.go = "greguar_exit_1";
		break;

	case "greguar_exit_1":
		DialogExit();
		npchar.lifeday = 0;
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload5_back", "none", "", "", "", 20.0);
		break;

	case "greguar_2":
		dialog.text = "¡Elección correcta, amigo mío! Puedes usar dinero extra, ¿correcto? ¿Cómo está tu hermano, por cierto?";
		link.l1 = "Siempre puedo usar dinero extra. ¿Michel? Mi hermano está en buena salud y está aburrido. A veces lo envidio... ¡Hora de zarpar!";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("FMQL_Begin");
		break;

	case "greguar_3":
		PlaySound("Voice\Spanish\QuestMan02.wav");
		dialog.text = "¡Pan comido! Estos fueron los novatos que sobrevivieron a la escaramuza con los holandeses. Debemos adentrarnos más en el continente, ¡mi expedición debe estar allí!";
		link.l1 = "Parecía demasiado fácil... pero es demasiado pronto para celebrar, monseniour Valinnie. Mira por allá...";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("FMQL_SecondCoastBattle");
		break;

	case "greguar_4":
		PlaySound("Voice\Spanish\LE\Greguar\Greguar_05.wav");
		dialog.text = "¡Malditos sean estos salvajes de piel roja! ¡Casi nos atraparon! Ahora estoy seguro de que solo quedan mujeres y niños en la aldea. ¡Marchen!";
		link.l1 = "No estoy tan seguro de que mencionaste mosquetes, no los vi... Ah, lo que sea. ¡Vamos!";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("FMQL_GoToJungle");
		break;

	case "greguar_5":
		PlaySound("Voice\Spanish\LE\Greguar\Greguar_06.wav");
		dialog.text = "¿Te das cuenta? ¡Los holandeses y nosotros debimos haberlos matado a todos!";
		link.l1 = "";
		link.l1.go = "greguar_6";
		break;

	case "greguar_6":
		DialogExit();
		if (CheckAttribute(pchar, "questTemp.Prosper_fmql"))
			sld = CharacterFromID("FMQL_Prosper");
		else
			sld = CharacterFromID("FMQL_mercen");
		sld.dialog.currentnode = "prosper_3";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;

	case "greguar_7":
		dialog.text = "¿Huir? ¿Estáis loco? ¡Casi hemos llegado! ¿Tenéis miedo de un montón de salvajes pintarrajeados?";
		link.l1 = "";
		link.l1.go = "greguar_8";
		break;

	case "greguar_8":
		DialogExit();
		if (CheckAttribute(pchar, "questTemp.Prosper_fmql"))
			sld = CharacterFromID("FMQL_Prosper");
		else
			sld = CharacterFromID("FMQL_mercen");
		sld.dialog.currentnode = "prosper_5";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;

	case "greguar_9":
		dialog.text = "Lo más bajo de lo bajo, capitán. Estoy volviendo a Europa. ¡Estoy decepcionado! ¡En ti, en estos cobardes y en esta maldita región!";
		link.l1 = "...";
		link.l1.go = "greguar_10";
		break;

	case "greguar_10":
		DialogExit();
		DoQuestReloadToLocation("shore18", "goto", "goto8", "FMQL_JungleExit");
		break;

	case "greguar_11":
		dialog.text = "¡Fuh! ¡Lo hicimos!";
		link.l1 = "¡Pero a qué precio! ¡Mira! Casi todos de nuestro escuadrón están muertos. Deberíamos retirarnos, Gregoire, no hay garantías de que no haya más guerreros esperándonos. Además, simplemente nos faltan números para llevar el botín.";
		link.l1.go = "greguar_12";
		break;

	case "greguar_12":
		dialog.text = "¡Maldita sea! Es triste, pero tienes razón, " + pchar.name + ":  incluso si los salvajes están todos muertos, no podremos llevarnos la carga antes de que los holandeses o los ingleses lleguen aquí. ¡Debemos irnos ahora! ¡Al diablo con esta maldita costa!";
		link.l1 = "...";
		link.l1.go = "greguar_10";
		break;

	case "greguar_13":
		dialog.text = "¡Fuh! ¡Lo hicimos! Bien hecho, " + pchar.name + "¡Ahora movámonos al cubil de los salvajes por nuestro premio! ¡Nada puede detenernos ahora!";
		link.l1 = "Deberíamos apresurarnos mientras los británicos y los holandeses todavía están ocupados entre ellos. ¡Vamos!";
		link.l1.go = "greguar_14";
		break;

	case "greguar_14":
		DialogExit();
		DoQuestCheckDelay("FMQL_RunToGrabbing", 1.0);
		break;

	case "greguar_15":
		dialog.text = "Lo hicimos bien, " + pchar.name + "Ahora todo lo que necesitamos es vender la carga sin levantar sospechas. Tengo un comprador fiable, nos esperará en la bahía de Lamentin a medianoche. No lleves a ningún oficial y evita el lugar antes de la reunión, el cliente es un tipo muy nervioso.";
		link.l1 = "Negocios son negocios. La carga debe venderse y debe hacerse de manera segura, de lo contrario mi deuda con Poincy aumentará aún más. Muy bien, estaré allí a medianoche.";
		link.l1.go = "greguar_16";
		break;

	case "greguar_16":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 10.0);
		pchar.quest.FMQL_goods_timer.win_condition.l1 = "Timer";
		pchar.quest.FMQL_goods_timer.win_condition.l1.date.hour = 0.0;
		pchar.quest.FMQL_goods_timer.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
		pchar.quest.FMQL_goods_timer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
		pchar.quest.FMQL_goods_timer.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
		pchar.quest.FMQL_goods_timer.function = "FMQL_MeetingOnLamanten";
		AddQuestRecord("FMQ_Lesson", "7");
		LAi_LocationDisableOfficersGen("Shore38", true); // may-16
		LAi_LocationFightDisable(&Locations[FindLocation("Shore38")], true);
		locations[FindLocation("Shore38")].DisableEncounters = true;
		Pchar.GenQuest.Hunter2Pause = true;
		break;

	case "greguar_17":
		PlaySound("Voice\Spanish\Master_01.wav");
		pchar.quest.FMQL_goods_over.over = "yes"; // лесник снято прерывание на встречу.
		dialog.text = "Está hecho. El cargamento está descargada, el cliente está aquí. Vamos a hablar.";
		link.l1 = "...";
		link.l1.go = "greguar_18";
		break;

	case "greguar_18":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorFollowEverywhere(npchar, "", -1);
		for (i = 1; i <= 3; i++)
		{
			sld = CharacterFromID("FMQL_contra_" + i);
			if (i == 2)
			{
				LAi_CharacterEnableDialog(sld);
				AddLandQuestMark(sld, "questmarkmain");
			}
		}
		break;

	case "greguar_19":
		dialog.text = "¡Sorpresa, bastardos!";
		link.l1 = "";
		link.l1.go = "exit";
		AddDialogExitQuest("FMQL_LookOnGuards");
		break;

	case "greguar_20":
		PlaySound("Voice\Spanish\LE\Greguar\Greguar_06.wav");
		dialog.text = "¡Ah, Johnny, qué tipo! ¡Genial! ¿Tienes algo que decir, " + pchar.name + "?";
		link.l1 = "No. ¡De hecho, sí! ¡¿Qué carajo?!";
		link.l1.go = "greguar_21";
		break;

	case "greguar_21":
		dialog.text = "No burles del muerto, monsieur. ¿Dónde están tus modales?.. El dinero está aquí, la carga la cuido yo y mis amigos. No los envié a la costa, habría sido un desperdicio. Especialmente enviar a Johnny allí. ¿Ves a ese piel roja con una culebrina en las manos? Sabes, a Johnny nunca le gustó realmente su propia tribu.";
		link.l1 = "Ya veo... ¿Y ahora qué? ¿Vas a matarme también?";
		link.l1.go = "greguar_22";
		break;

	case "greguar_22":
		dialog.text = "Bueno, debería. Pero soy sentimental. Vete y llévate una cuarta parte del dinero. La carga y el resto del dinero se quedan aquí conmigo. No intentes hacerte el héroe, esto no son las selvas del continente. No tienes ninguna oportunidad.";
		link.l1 = "¿Y dónde están tu nobleza y modales, Gregoire? No esperaba esto de ti. Me voy, pero no olvidaré esto.";
		link.l1.go = "greguar_23";
		link.l2 = "No estoy jugando a ser un héroe, nunca lo hice. ¡Simplemente los mataré a todos! ¡Primero a estas damas, luego al simio con el lanzagranadas y luego a ti!";
		link.l2.go = "greguar_25";
		break;

	case "greguar_23":
		dialog.text = "No hay ni nobles, ni matones en esta playa, monsieur. Solo hay cinco hombres, un gran cañón y una víctima. Esto sucede aquí todo el tiempo, pero has tomado la única decisión correcta. Bien hecho. ¿Sabes que en lugar de ti podrían haber dos más en tus zapatos, parados aquí mismo, ahora mismo? Son casi como tú. Pero tú estás aquí y ellos no, y creo que perecerán por eso.";
		link.l1 = "No entiendo...";
		link.l1.go = "greguar_24";
		break;

	case "greguar_24":
		dialog.text = "Un día lo harás. Ellos no recibieron su lección final. Tú sí. De nada. Adiós, monseñor. ¡Bienvenido al Caribe!";
		link.l1 = "...";
		link.l1.go = "exit";
		AddDialogExitQuest("FMQL_PeaceFinal");
		break;

	case "greguar_25":
		dialog.text = "Ahh... No eres el estudiante más brillante que he tenido. Muy bien... ¡cada quien a lo suyo!";
		link.l1 = "...";
		link.l1.go = "exit";
		AddDialogExitQuest("FMQL_BattleOnBeach");
		break;

	case "mercen":
		PlaySound("Voice\Spanish\EvilPirates06.wav");
		dialog.text = "¡Justo a tiempo! Apenas huimos de la horda de los caribes, se dirigían en tu dirección y, por tu aspecto, ya te los has encontrado. Su aldea está cerca, pero nuestros problemas apenas comienzan.";
		link.l1 = "";
		link.l1.go = "prosper_2";
		break;

	case "prosper":
		dialog.text = "" + GetFullName(pchar) + "¡Tú estás aquí! ¡Y por qué no me sorprende! Perfecto timing, mi amigo. Apenas huimos de la horda de los caribes, ellos se dirigían hacia tu dirección y, por tu aspecto, ya los has encontrado.";
		link.l1 = "¡Prospera! ¡Y estoy sorprendido! ¿Haciendo agujeros en los indios otra vez? ¿Espero que Selina esté bien?";
		link.l1.go = "prosper_1";
		break;

	case "prosper_1":
		dialog.text = "Fue una locura unirme a esta expedición, me pregunto si mi hija volverá a verme alguna vez. ¿Selina? ¡Pues se está sentando en casa y soñando contigo! Los jóvenes de Martinica han perdido toda esperanza ya... Sabes, ya no me arrepiento de haber comprado este mosquete. Un arma sólida. Confiable. También una razón adicional para participar en otra empresa suicida, aunque ahora es un poco menos suicida desde que apareciste. Su aldea está cerca, pero nuestros problemas apenas están por comenzar.";
		link.l1 = "";
		link.l1.go = "prosper_2";
		break;

	case "prosper_2":
		DialogExit();
		sld = CharacterFromID("Guide_y");
		sld.dialog.currentnode = "greguar_5";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;

	case "prosper_3":
		dialog.text = "No todos ellos. Nuestro explorador fue disparado, pero aún así logró llegar a su guarida. Un jefe mismo viene aquí con sus guardias. Y tienen mosquetes holandeses. Tienen ventaja en número y están furiosos como el infierno. El jefe es el mejor guerrero de su tribu, sus hombres son demonios en carne. Debemos decidir rápidamente, aquí y ahora mismo. O les damos pelea o huimos. Prefiero lo último, para ser honesto...";
		link.l1 = "";
		link.l1.go = "prosper_4";
		break;

	case "prosper_4":
		DialogExit();
		sld = CharacterFromID("Guide_y");
		sld.dialog.currentnode = "greguar_7";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;

	case "prosper_5":
		dialog.text = "¡No los has visto, buen hombre! Estos 'salvajes' tienen mosquetes y son sorprendentemente buenos con ellos. ¡Alguien les ha estado dando lecciones, de eso no hay duda! ¡Así que no me llames cobarde de nuevo!";
		link.l1 = "Calmémonos y decidamos qué hacer. Todavía hay tiempo.";
		link.l1.go = "prosper_6";
		break;

	case "prosper_6":
		int n = 0;
		for (i = 1; i <= 5; i++)
		{
			if (GetCharacterIndex("FMQL_sailor_" + i) != -1)
				n++;
		}
		dialog.text = "Estoy escuchando, " + pchar.name + ".";
		if (n > 2 && GetSummonSkillFromName(pchar, SKILL_SNEAK) > 30)
		{
			link.l1 = "¡Les daremos pelea, muchachos! ¡Hay bienes y dinero justo detrás de esta colina! Estamos aquí por ellos y no nos iremos. ¡De ninguna manera un grupo de pieles rojas, incluso con mosquetes, puede detenernos! ¡Enterremos a esos cabrones y terminemos el trabajo! Tenemos suficientes hombres, hay oportunidad de emboscarlos. Cuatro hombres los recibirán con fuego desde los flancos y el resto de nosotros tomaremos posiciones aquí. ¡Reduzcamos su número y acabemos con ellos!";
			link.l1.go = "prosper_8";
		}
		else
		{
			if (n > 0)
			{
				link.l1 = "¡Les daremos pelea, muchachos! ¡Hay bienes y dinero justo detrás de esta colina! Estamos aquí por ellos y no nos iremos. ¡De ninguna manera un grupo de pieles rojas, incluso con mosquetes, puede detenernos! ¡Enterremos a esos cabrones y terminemos el trabajo!";
				link.l1.go = "prosper_7";
			}
			else
			{
				link.l1 = "Las probabilidades están en nuestra contra de todas las formas posibles. No olvides a los holandeses justo detrás de nosotros.";
				link.l1.go = "prosper_9";
			}
		}
		break;

	case "prosper_9":
		DialogExit();
		sld = CharacterFromID("Guide_y");
		sld.dialog.currentnode = "greguar_9";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;

	case "prosper_7":
		DialogExit();
		pchar.questTemp.FMQL = "battle";
		AddDialogExitQuestFunction("FMQL_PrepareAttack");
		break;

	case "prosper_8":
		DialogExit();
		pchar.questTemp.FMQL = "sneak";
		AddDialogExitQuestFunction("FMQL_PrepareSneakAttack");
		break;

	case "prosper_9x":
		dialog.text = "¡Estamos vivos y estamos en casa! Te juro, ya tuve suficientes aventuras... por los próximos meses, ¡ja-ja! Debería ir con mi hija, por favor ven a visitarnos, " + pchar.name + ". Y por favor, ten cuidado.";
		link.l1 = "Sin promesas, Prosper. ¡Buena suerte!";
		link.l1.go = "prosper_10";
		break;

	case "prosper_10":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 10.0);
		break;

	case "prosper_11":
		pchar.quest.FMQL_prosper_dead.over = "yes";
		LAi_RemoveCheckMinHP(npchar);
		PlaySound("Voice\Spanish\LE\Trubal\Prosper_Trubal_07.wav");
		dialog.text = "Te he advertido, capitán, ¡ten cuidado! Tenía sospechas sobre ese bastardo.";
		link.l1 = "¡Prospera! ¡Gracias! ¿Pero cómo?";
		link.l1.go = "prosper_12";
		break;

	case "prosper_12":
		sTemp = "";
		if (CheckAttribute(pchar, "questTemp.FMQL.PirateDead"))
			sTemp = "Pobre muchacho, aunque era un pirata.";
		dialog.text = "Johnny se puso demasiado hablador. El tipo piel roja en la arena. Vino a un burdel e intentó ligar con una chica. Se negaron a atenderlo, Johnny se enfureció, comenzó a gritar que pronto sería rico, una vez que él y sus compañeros mataran a un capitán en la jungla. Vi lo que se avecinaba y corrí hacia tu oficial que también logró ganar algo de infamia en la ciudad." + sTemp + " Te debo mucho, " + pchar.name + ", así que no hay necesidad de agradecerme mucho.";
		link.l1 = "Y aún así, ¡muchas gracias, Prosper! Fue duro aquí... demasiado duro. ¿Quieres unirte a mi tripulación? Necesito un oficial como tú. Es difícil encontrar hombres leales hoy en día, especialmente buenos tiradores.";
		link.l1.go = "prosper_13";
		break;

	case "prosper_13":
		dialog.text = "No, mi amigo. Tengo obligaciones con mi hija. Ella me hizo jurar dejar mis aventuras atrás. Fue mi última. Maldita sea, qué lástima, pero amo a mi hija más que a nada en el mundo. Adiós, " + pchar.name + ". Y... Selina habla de ti todo el tiempo. Quizás podrías hacernos una visita algún día.";
		link.l1 = "¿Quién sabe?, tal vez lo haga... ¡Adiós, Prosper! Deseo que tu hija encuentre un buen esposo... (para sí mismo) Lección aprendida, monsieur Gregoire, lección aprendida... a cada uno lo suyo, decía... Recordaré esto.";
		link.l1.go = "prosper_14";
		break;

	case "prosper_14":
		DialogExit();
		LAi_SetActorType(npchar);
		npchar.lifeday = 0;
		LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 15.0);
		chrDisableReloadToLocation = false;
		InterfaceStates.Buttons.Save.enable = true; // разрешим сохраняться
		AddQuestRecord("FMQ_Lesson", "15");
		CloseQuestHeader("FMQ_Lesson");
		pchar.questTemp.FMQL = "end";
		break;

	case "contra":
		DelLandQuestMark(npchar);
		dialog.text = "¿Quién demonios eres?";
		link.l1 = "Tenemos la carga. ¿Interesado?";
		link.l1.go = "contra_1";
		break;

	case "contra_1":
		dialog.text = "Ja. Muy interesado. Especialmente mi cliente. ¿Cuál es la ganancia?";
		link.l1 = "" + FindRussianQtyString(sti(pchar.questTemp.FMQL.Sanl)) + " de sándalo, " + FindRussianQtyString(sti(pchar.questTemp.FMQL.Silk)) + " de barco de seda, " + FindRussianQtyString(sti(pchar.questTemp.FMQL.Rope)) + " de soga y " + FindRussianQtyString(sti(pchar.questTemp.FMQL.Oil)) + " de resina.";
		link.l1.go = "contra_2";
		break;

	case "contra_2": // Addon 2016-1 Jason пиратская линейка
		iTotalTemp = 2200 * sti(pchar.questTemp.FMQL.Sanl) + 1600 * sti(pchar.questTemp.FMQL.Silk) + 1000 * sti(pchar.questTemp.FMQL.Rope) + 900 * sti(pchar.questTemp.FMQL.Oil);
		dialog.text = "Muy bien. 2200 pesos por cada pieza de sándalo, 900 pesos por resina, 1600 pesos por seda de barco y 1000 pesos por cuerdas. ¿Qué tenemos aquí...? Bueno-bueno. " + iTotalTemp + " pesos. ¿Trato hecho?";
		link.l1 = "¡Trato hecho!";
		link.l1.go = "contra_3";
		break;

	case "contra_3":
		LAi_Fade("", "");
		FMQL_CreateGuidesWarriors();
		dialog.text = "¡Espléndido! Trae más. Los holandeses nunca dejan de ser generosos con los pieles rojas... ¿Y quiénes son estos invitados? ¡¿Qué demonios?!";
		link.l1 = "";
		link.l1.go = "contra_4";
		break;

	case "contra_4":
		DialogExit();
		sld = CharacterFromID("Guide_y");
		sld.dialog.currentnode = "greguar_19";
		AddMoneyToCharacter(sld, iTotalTemp);
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;

	case "FMQL_beach":
		pchar.quest.FMQL_pirate_dead.over = "yes";
		LAi_RemoveCheckMinHP(npchar);
		dialog.text = "Sí, capitán. Me había pasado de copas en la navegación por una razón.";
		link.l1 = "¿Tú? ¡¿Cómo?!";
		link.l1.go = "FMQL_beach_1";
		break;

	case "FMQL_beach_1":
		dialog.text = "Lamento, capitán. Tuve que tomar una copa o dos después de ese lío con los indios. Había una chica, tomé una habitación por cien pesos y ella... ella...";
		link.l1 = "¿Qué? ¿Te robaron?";
		link.l1.go = "FMQL_beach_2";
		break;

	case "FMQL_beach_2":
		sld = CharacterFromID("FMQL_Prosper");
		dialog.text = "¡No! ¡Se enamoró! ¡Maldita sea, debería haber huido de allí! Pero luego aparece tu amigo, gritándome sobre esa escoria, tu antiguo compañero, que quiere engañarte y matarte.";
		if (LAi_GetCharacterHP(sld) > 0)
		{
			link.l1 = "Bien hecho, Prosper...";
			link.l1.go = "FMQL_beach_3";
		}
		else
		{
			link.l1 = "Próspero... Lo siento mucho. Cuidaré de tu hija. Lección aprendida, monsieur Gregoire... ¿Qué dijiste? ¿A cada cual lo suyo? Debería recordar esto.";
			link.l1.go = "FMQL_beach_3";
		}
		break;

	case "FMQL_beach_3":
		dialog.text = "¿Nos vamos, capitán?";
		link.l1 = "Sí. Gracias por tu servicio. Mantente alejado de la copa y te salvaremos de esa belleza. Vamos.";
		if (CheckAttribute(pchar, "questTemp.FMQL.ProsperDead"))
			link.l1.go = "FMQL_beach_5";
		else
			link.l1.go = "FMQL_beach_4";
		break;

	case "FMQL_beach_4": // Проспер жив
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload_sea", "none", "", "", "FMQL_PirateNormal", 10.0);
		sld = CharacterFromID("FMQL_Prosper");
		sld.Dialog.currentnode = "prosper_11";
		sld.MusketerDistance = 20;
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

	case "FMQL_beach_5":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "FMQL_PirateNormal", 10.0);
		if (sti(pchar.money) >= 20000)
			DoQuestFunctionDelay("FMQL_MoneyForSelina", 0.5);
		else
		{
			pchar.quest.FMQL_money_20k.win_condition.l1 = "Money";
			pchar.quest.FMQL_money_20k.win_condition.l1.value = 20000;
			pchar.quest.FMQL_money_20k.win_condition.l1.operation = ">=";
			pchar.quest.FMQL_money_20k.function = "FMQL_MoneyForSelina";
		}
		chrDisableReloadToLocation = false;
		InterfaceStates.Buttons.Save.enable = true; // разрешим сохраняться
		AddQuestRecord("FMQ_Lesson", "10");
		CloseQuestHeader("FMQ_Lesson");
		pchar.questTemp.FMQL = "end";
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}
