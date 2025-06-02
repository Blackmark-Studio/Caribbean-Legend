// аббат Бенуа
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int rate;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		if (CheckAttribute(pchar, "questTemp.Sharlie.BenuaLoan.Late")) // Addon 2016-1 Jason пиратская линейка 1
		{
			dialog.text = "Es bueno verte, hijo mío. ¿Estás aquí para saldar tu deuda?";
			if (PCharDublonsTotal() >= 100 && sti(pchar.money) >= 50000)
			{
				link.l1 = "Sí, padre.";
				link.l1.go = "FastStart_7";
			}
			else
			{
				link.l1 = "Lamento la demora, pero no estoy aquí por eso. Pero lo estaré pronto, no te preocupes.";
				link.l1.go = "exit";
			}
			break;
		}
		if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "benua_final")
		{
			dialog.text = "¿Hay algo que necesites, hijo mío?";
			link.l1 = "Sí, padre. Me gustaría ver a mi hermano, Michel de Monper. Él dijo...";
			link.l1.go = "escape";
			break;
		}
		dialog.text = "¿Hay algo que necesites, hijo mío?";
		if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && !CheckAttribute(npchar, "quest.FastStart") && !CheckAttribute(npchar, "quest.meet")) // ещё не виделись
		{
			link.l1 = "Sí, padre. Necesito tu ayuda. Mi nombre es " + GetFullName(pchar) + ". Michel de Monper me aconsejó hablar contigo.";
			link.l1.go = "FastStart";
		}
		if (CheckAttribute(npchar, "quest.help") && !CheckAttribute(npchar, "quest.meet")) // ещё не виделись
		{
			link.l1 = "Sí, padre. Necesito tu ayuda. Mi nombre es " + GetFullName(pchar) + ". Me aconsejó hablar contigo mi hermano, Michel de Monper.";
			link.l1.go = "meet";
		}
		if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && !CheckAttribute(npchar, "quest.FastStart") && CheckAttribute(npchar, "quest.meet"))
		{
			link.l1 = "Sí, padre. Necesito un barco para ayudar a Michel, pero acabo de llegar al Caribe y mi cartera está vacía. Mi hermano me dijo que podrías prestarme algo de dinero...";
			link.l1.go = "FastStart_2";
		}
		if (CheckAttribute(npchar, "quest.help") && CheckAttribute(npchar, "quest.meet"))
		{
			link.l1 = "Sí, padre. Necesito tu ayuda.";
			if (CheckAttribute(npchar, "quest.relation_info"))
				link.l1.go = "help";
			else
				link.l1.go = "help_start";
		}
		if (CheckAttribute(pchar, "questTemp.Sharlie.BenuaLoan") && PCharDublonsTotal() >= 100 && sti(pchar.money) >= 50000)
		{
			link.l2 = "Sí, padre. Estoy list"+GetSexPhrase("o","a")+" para pagar mi deuda.";
			link.l2.go = "FastStart_7";
		}
		link.l9 = "No, nada, padre.";
		link.l9.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	case "Benua_meeting":
		DelLandQuestMark(npchar);
		if (CheckAttribute(pchar, "questTemp.Sharlie.Citcount"))
			DeleteAttribute(pchar, "questTemp.Sharlie.Citcount");
		DelLandQuestMark(characterFromId("FortFrance_Mayor"));
		dialog.text = "¿Qué te trae a mí, hijo mío?";
		link.l1 = "Hola, padre. Me aconsejaron hablar contigo. Mi nombre es Charles de Maure. Estoy buscando a Michel de Monper. Por lo que sé, debería estar en algún lugar de Martinica. Yo soy... su hermano.";
		link.l1.go = "Benua_meeting_1";
		break;

	case "Benua_meeting_1":
		dialog.text = "¿Hermano de Michel de Monper? ¿De Maure? Qué extraño...";
		link.l1 = "Entiendo tus dudas, padre. Simplemente tenemos apellidos diferentes. Mi padre es Henri de Monper.";
		link.l1.go = "Benua_meeting_2";
		break;

	case "Benua_meeting_2":
		dialog.text = "A-ah, ahora veo. Solía conocer personalmente a Henri de Monper. Acércate a la luz, joven. ¡Correcto! Te pareces mucho a él. ¡Los mismos rasgos, la misma nobleza! Me alegra ver a un hijo de Henri de Monper en nuestra parroquia.\nY con respecto a tu pregunta, te diré que Michel es un oficial de alto rango de la Orden de Malta, pero está... en problemas. Afortunadamente, uno de los caballeros de la Orden me está visitando actualmente. Creo que podría aceptar acompañarte a ver a tu desafortunado hermano, que el Señor tenga piedad de su destino...";
		link.l1 = "¿Quién es este hombre, santo padre?";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Sharlie_enterMaltie");
		NextDiag.TempNode = "First time";
		npchar.quest.meet = true;
		if (GetCharacterIndex("SharlieKnown") != -1)
		{
			sld = characterFromId("SharlieKnown");
			sld.lifeday = 0;
		}
		break;

	case "Benua_meeting_3":
		DialogExit();
		NextDiag.CurrentNode = "Benua_meeting_repeat";
		AddQuestRecord("Sharlie", "4");
		pchar.quest.Sharlie_Benua.win_condition.l1 = "Timer";
		pchar.quest.Sharlie_Benua.win_condition.l1.date.hour = 6;
		pchar.quest.Sharlie_Benua.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
		pchar.quest.Sharlie_Benua.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
		pchar.quest.Sharlie_Benua.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
		pchar.quest.Sharlie_Benua.function = "Sharlie_BenuaMaltie";
		break;

	case "Benua_meeting_repeat":
		dialog.text = "Hijo mío, vuelve mañana por la mañana. Por el momento, no tengo nada más que decirte.";
		link.l1 = "Está bien.";
		link.l1.go = "exit";
		NextDiag.TempNode = "Benua_meeting_repeat";
		break;

		/* case "Benua_maltie":
			dialog.text = "Hola, hijo mío. Como prometí, la persona que mencioné ayer ya está aquí esperándote. Está listo para llevarte con tu hermano, quien, según he oído, está desdichado. Que el Señor tenga piedad de su alma...";
			link.l1 = "¿Quién es este hombre, santo padre?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Sharlie_enterMaltie");
			NextDiag.TempNode = "First time";
			npchar.quest.meet = true;
		break; */

	case "escape":
		dialog.text = "Sí, Charles, soy consciente de eso. Pero debo decepcionarte. Michel no está aquí.";
		link.l1 = "¿Qué quieres decir con que no está aquí? ¡Dijo que me estaría esperando en la iglesia! Padre, ¿qué ha pasado? ¿Dónde está mi hermano?!";
		link.l1.go = "escape_1";
		break;

	case "escape_1":
		dialog.text = "Hijo mío, tu hermano estuvo aquí, y salió de mi modesto tabernáculo tarde por la noche. A dónde fue, no lo sé. Pero te ha dejado esta carta.";
		link.l1 = "No puedo creerlo... ¡después de todo lo que hice por él! ¡Dame esa carta!";
		link.l1.go = "escape_2";
		break;

	case "escape_2":
		dialog.text = "No te enfurezcas tanto, Charles. Aquí está la carta. Léela y luego... luego me gustaría hablar contigo. Pero primero, lee el mensaje de tu hermano.";
		link.l1 = "¡Estoy ardiendo de impaciencia!";
		link.l1.go = "escape_3";
		break;

	case "escape_3":
		DialogExit();
		GiveItem2Character(pchar, "specialletter");
		ChangeItemDescribe("specialletter", "itmdescr_specialletter_mishelle");
		sld = ItemsFromID("specialletter");
		sld.text = "Letter_Mishelle";
		NextDiag.CurrentNode = "escape_4";
		LocatorReloadEnterDisable("FortFrance_town", "reload91", false); // лесник открыл входы
		LocatorReloadEnterDisable("FortFrance_town", "reload_jail", false);
		break;

	case "escape_4":
		if (CheckAttribute(pchar, "GenQuest.specialletter.read") && pchar.GenQuest.specialletter.read == "Letter_Mishelle")
		{
			dialog.text = "Veo que has leído la carta. Ahora, me gustaría decirte algo, Charles...";
			link.l1 = "Pero... ¿cómo puede ser eso? ¿Qué clase de patrañas son estas? Sé que mi hermano es peculiar, ¡pero no es un loco!";
			link.l1.go = "escape_5";
		}
		else
		{
			dialog.text = "Hijo mío, lee la carta. Hablaremos más tarde.";
			link.l1 = "Sí, padre...";
			link.l1.go = "exit";
			NextDiag.TempNode = "escape_4";
		}
		break;

	case "escape_5":
		dialog.text = "Las acciones de tu hermano también me sorprendieron, Charles. Aún siento momentos de perplejidad. Un leal servidor de la Orden y la Trinidad, y se está comportando como un desertor.";
		link.l1 = "¿Tienes alguna idea de cuáles podrían ser las razones de su comportamiento tan extraño?";
		link.l1.go = "escape_6";
		break;

	case "escape_6":
		dialog.text = "Por desgracia, no. Pero supongo que él tiene sus propios motivos, motivos profundos. Abrogar todo su pasado sugeriría una razón extremadamente significativa. Ni siquiera puedo imaginar lo que podría ser. Pero siento que involucra algo extremadamente malo... incluso terrible.";
		link.l1 = "¿Qué podría ser, padre?";
		link.l1.go = "escape_7";
		break;

	case "escape_7":
		dialog.text = "Hijo mío, un sacerdote no ve con sus ojos, sino con su corazón. No puedo explicártelo con palabras, pero... tu hermano se ha propuesto hacer algo impuro, sucio. Nunca pensé que mi boca pudiera pronunciar esto. Sin embargo...";
		link.l1 = "Bueno, no dudo que mi hermano haya planeado algo sucio. Incluso puedo imaginarme exactamente lo que está planeando hacer. Este 'algo' involucra algo amarillo, y hace un agradable sonido de tintineo.";
		link.l1.go = "escape_8";
		break;

	case "escape_8":
		dialog.text = "No creo que la codicia por el oro sea lo que impulsa a tu hermano. Diría que él necesita algo más grande.";
		link.l1 = "He aprendido mucho de Michel y he comprendido su filosofía, así que creo que soy capaz de asumir qué es importante para él y qué no lo es. Pero tendré en cuenta tus valiosas palabras, padre.";
		link.l1.go = "escape_9";
		break;

	case "escape_9":
		dialog.text = "¡Dios te bendiga, hijo mío. Ve, ve ahora. ¡Que el Señor vele por ti!";
		link.l1 = "Gracias, padre. ¡Adiós!";
		link.l1.go = "escape_10";
		break;

	case "escape_10":
		DialogExit();
		NextDiag.CurrentNode = "first time";
		pchar.questTemp.Sharlie = "escape";
		CloseQuestHeader("Sharlie");
		AddQuestRecord("Guardoftruth", "1");
		pchar.questTemp.Guardoftruth = "begin";
		DeleteAttribute(pchar, "questTemp.GoldenGirl_Block"); // Разрешаем квест Дороже Золота
		// ставим пленного испанца
		sld = GetCharacter(NPC_GenerateCharacter("spa_baseprisoner", "q_spa_off_1", "man", "man", 30, SPAIN, -1, true, "quest"));
		FantomMakeCoolFighter(sld, 30, 80, 80, "blade_13", "pistol1", "bullet", 150);
		sld.dialog.FileName = "Quest\Sharlie\Guardoftruth.c";
		sld.dialog.currentnode = "spa_prisoner";
		RemoveAllCharacterItems(sld, true);
		LAi_SetStayType(sld);
		LAi_SetImmortal(sld, true);
		ChangeCharacterAddressGroup(sld, "Fortfrance_dungeon", "quest", "quest1");
		LAi_CharacterDisableDialog(sld); // запрет диалога
		break;

	// уменьшение награды за голову
	case "meet":
		dialog.text = "¿El hermano de Michel de Monper? ¿De Maure? Qué extraño...";
		link.l1 = "Entiendo tus dudas, padre. Simplemente tenemos apellidos diferentes. Mi padre es Henri de Monper.";
		link.l1.go = "meet_1";
		break;

	case "meet_1":
		dialog.text = "¡A-ah! Ya veo. Conocí personalmente a Henri de Monper. Acércate a la luz, joven... ¡Correcto! Te pareces a él. ¡Mismo aspecto, mismo perfil noble! Me alegra ver a un hijo de Henri de Monper en nuestra parroquia.\nYa he oído que a Michel lo visitó un hombre que llegó de Europa, pero ni siquiera podía imaginarme que era su propio hermano. Espero que puedas ayudar a Michel, está pasando por un momento difícil. En cualquier caso, ¿en qué puedo servirte?";
		link.l1 = "Michel me dijo que podrías ayudarme si alguna vez tuviera problemas con las autoridades.";
		link.l1.go = "help_info";
		npchar.quest.meet = true;
		break;

	case "help_info":
		dialog.text = "¿Eso es lo que te dijo Michel? Ya veo. Bueno, puedo ser de ayuda en tales asuntos. Tengo cierta influencia dentro de la Santa Iglesia Romana y las colonias holandesas. Por lo tanto, podría interceder entre tú y las autoridades españolas, así como las holandesas. Seguramente, no podré hacer mucho si tu mala conducta ha llegado demasiado lejos; en ese caso, solo se podrá lograr una pequeña atenuación.\nSe requerirán varias intercesiones para una reconciliación completa. Además, en cualquier caso, tendrás que proveerme de doblones de oro para obras de caridad y gastos de viaje. También, solo puedo ayudarte con una nación a la vez. Si encuentras estos términos aceptables, no dudes en acudir a mí, y veremos qué se puede hacer.";
		link.l1 = "¡Gracias! Lo tendré en cuenta.";
		link.l1.go = "exit";
		npchar.quest.relation_info = "true";
		break;

	case "help_start":
		dialog.text = "¿Qué puedo hacer por ti, hijo mío? Habla, te escucho.";
		link.l1 = "Michel me dijo que podrías ayudarme si alguna vez tengo problemas con las autoridades.";
		link.l1.go = "help_info";
		break;

	case "help":
		dialog.text = "¿Cómo puedo ayudarte, hijo mío?";
		if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
		{
			link.l1 = "Me he metido en problemas con las autoridades españolas.";
			link.l1.go = "relation_spa";
		}
		if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
		{
			link.l2 = "Me he metido en problemas con las autoridades holandesas.";
			link.l2.go = "relation_hol";
		}
		link.l9 = "Lo siento, creo que esta vez me ocuparé de las cosas yo mismo.";
		link.l9.go = "exit";
		break;

	case "relation_spa": // patch-10
		pchar.GenQuest.BenuaNation = SPAIN;
		dialog.text = "Así que, los nobles señores están ansiosos por meterte en las mazmorras de La Habana...";
		link.l1 = "Exactamente, padre...";
		link.l1.go = "relation";
		break;

	case "relation_hol":
		pchar.GenQuest.BenuaNation = HOLLAND;
		dialog.text = "Así que, los astutos mercaderes están ansiosos por meterte en las mazmorras de Willemstad...";
		link.l1 = "Exactamente, padre...";
		link.l1.go = "relation";
		break;

	case "relation":
		rate = abs(ChangeCharacterNationReputation(pchar, sti(pchar.GenQuest.BenuaNation), 0));
		if (rate <= 10)
		{
			dialog.text = "Sí, esos rumores también han llegado a nuestra iglesia. Puedo ayudarte con tu dilema. Es algo que se puede resolver. Necesito doscientos cincuenta doblones de oro para suavizar tu situación.";
			if (PCharDublonsTotal() >= 250) // Sinistra legendary edition
			{
				link.l1 = "¡Estupendo! Aquí está el oro.";
				link.l1.go = "agree";
				iTotalTemp = 250;
			}
			link.l2 = "Entonces, es el momento adecuado para que encuentre los doblones.";
			link.l2.go = "exit";
		}
		else
		{
			if (rate <= 20)
			{
				dialog.text = "Sí, los rumores de tus 'hazañas' han llegado también a nuestra iglesia. Has empañado tu reputación, hijo mío. Deberías ser más prudente. Pero puedo ayudarte. Necesito quinientos doblones de oro para suavizar tu aprieto.";
				if (PCharDublonsTotal() >= 500) // Sinistra legendary edition
				{
					link.l1 = "¡Estupendo! Aquí está el oro.";
					link.l1.go = "agree";
					iTotalTemp = 500;
				}
				link.l2 = "Entonces, es el momento adecuado para encontrar los doblones.";
				link.l2.go = "exit";
			}
			else
			{
				dialog.text = "Sí, hijo mío. Eres tan desesperado como tu hermano... Probablemente sea un rasgo de familia. No puedo corregir completamente la situación, pero, sin embargo, creo que puedo mitigar tu lamentable predicamento. Y más tarde podemos hacer más ofrendas si lo deseas. Necesito seiscientos doblones de oro por ahora, y comenzaré a resolver tu dilema de inmediato.";
				if (PCharDublonsTotal() >= 600) // Sinistra legendary edition
				{
					link.l1 = "¡Estupendo! Aquí está el oro.";
					link.l1.go = "agree";
					iTotalTemp = 600;
				}
				link.l2 = "Entonces, es el momento adecuado para que encuentre los doblones.";
				link.l2.go = "exit";
			}
		}
		break;

	case "agree":
		RemoveDublonsFromPCharTotal(iTotalTemp); // Sinistra legendary edition
		Log_Info("¡Has dado " + iTotalTemp + " doblones!");
		PlaySound("interface\important_item.wav");
		dialog.text = "Ahora tendrás que esperar al menos dos semanas. Creo que dentro de este tiempo podré reunirme y hablar con las personas adecuadas.";
		link.l1 = "¡Gracias, padre! Estaré esperando...";
		link.l1.go = "agree_1";
		break;

	case "agree_1":
		DialogExit();
		SetFunctionTimerCondition("ChangeNationRelationFromBenuaComplete", 0, 0, 10 + rand(5), false);
		pchar.GenQuest.BenuaNation.Rate = abs(ChangeCharacterNationReputation(pchar, sti(pchar.GenQuest.BenuaNation), 0));
		npchar.quest.relation = "true";
		break;

	// Addon 2016-1 Jason пиратская линейка 1
	case "FastStart":
		dialog.text = "¿De Maure? ¿Y eres hermano de Michel de Monper? Extraño...";
		link.l1 = "Entiendo tus dudas, padre. Mi padre es Henri de Monper.";
		link.l1.go = "FastStart_1";
		break;

	case "FastStart_1":
		dialog.text = "A-ah, ya veo. Conocí personalmente a Henri de Monper. Acércate hacia la luz, joven. ¡Correcto! ¡Los mismos ojos, las mismas características nobles! Me complace ver a un hijo de Henri de Monper en mi iglesia. Espero que puedas ayudar a tu hermano. Ha tenido mucha mala suerte últimamente.";
		link.l1 = "Sí, padre. Necesito un barco para ayudar a Michel, pero acabo de llegar al Caribe y mi bolsillo está vacío. Mi hermano me dijo que podrías prestarme algo de dinero...";
		link.l1.go = "FastStart_2";
		npchar.quest.meet = true;
		break;

	case "FastStart_2":
		DelLandQuestMark(npchar);
		dialog.text = "¿Te lo dijo Michel?";
		link.l1 = "Padre, puede que no suene muy confiable, pero es cierto. Cuanto antes consiga un barco, antes podré sacar a mi hermano de la cárcel.";
		link.l1.go = "FastStart_3";
		break;

	case "FastStart_3":
		dialog.text = "Ya veo, hijo mío. Puedo escuchar que hablas con la verdad. Bien, por el bien de Michel y de tu padre te ayudaré. Tengo algunos ahorros, tómalos. Supongo que 50 000 pesos y 100 doblones serán suficientes.";
		link.l1 = "Gracias, padre. ¿Cuáles son los términos?";
		link.l1.go = "FastStart_4";
		break;

	case "FastStart_4":
		AddMoneyToCharacter(pchar, 50000);
		TakeNItems(pchar, "gold_dublon", 100);
		dialog.text = "Sin presión. Medio año para el reembolso será suficiente.";
		link.l1 = "Muy bien, santo padre. ¡Gracias de nuevo!";
		link.l1.go = "FastStart_5";
		break;

	case "FastStart_5":
		dialog.text = "Ve con mi bendición, hijo mío.";
		link.l1 = "...";
		link.l1.go = "FastStart_6";
		break;

	case "FastStart_6":
		DialogExit();
		NextDiag.CurrentNode = "first time";
		npchar.quest.FastStart = "true";
		pchar.questTemp.Sharlie.BenuaLoan = "true";
		SetFunctionTimerCondition("Sharlie_BenuaLoanTime", 0, 0, 180, false);
		AddQuestRecord("Sharlie", "5-2");
		break;

	case "FastStart_7":
		dialog.text = "Espléndido, hijo mío. Espero que ese dinero te haya servido de algo.";
		link.l1 = "¡En efecto, así fue! ¡Gracias!";
		link.l1.go = "FastStart_8";
		break;

	case "FastStart_8":
		DialogExit();
		NextDiag.CurrentNode = "first time";
		AddMoneyToCharacter(pchar, -50000);
		RemoveDublonsFromPCharTotal(100);
		pchar.quest.Sharlie_BenuaLoanTime.over = "yes";
		DeleteAttribute(pchar, "questTemp.Sharlie.BenuaLoan");
		AddQuestRecord("Sharlie", "5-3");
		break;

	// Jason Долго и счастливо
	case "LH_abbat":
		dialog.text = "¡Charles, no puedo creerlo! ¿Qué te trae por aquí?!";
		link.l1 = "Bendígame, Santo Padre, porque vengo con buenas noticias: ¡Me voy a casar! Y me gustaría verle como el sacerdote de mi boda.";
		link.l1.go = "LH_abbat_1";
		break;

	case "LH_abbat_1":
		dialog.text = "¡Hijo mío, esto es maravilloso! ¿Así que recibiste esa carta de tu padre y decidiste, como de costumbre, actuar según tu propio entendimiento? ¡Me alegra sinceramente por ti! Pero me temo que no puedo ayudarte a menos que decidas casarte en esta iglesia.";
		link.l1 = "Entiendo que su misión está en un impasse, Santo Padre. ¿Puedo ayudarle en algo? Dado que el matrimonio se celebrará en una capilla española, por supuesto, es una aventura que me gustaría emprender, pero estoy decidido a celebrar la ceremonia en Martinica. Moderadamente magnífica, y en presencia de testigos respetables e invitados honorables.";
		link.l1.go = "LH_abbat_2";
		break;

	case "LH_abbat_2":
		dialog.text = "Lo siento, hijo mío, pero toda tu autoridad no vale nada contra la obstinación de los más altos jerarcas de la Iglesia Católica, especialmente en las colonias españolas. No nos pusimos de acuerdo en la cuestión de compartir la influencia de las misiones católicas entre nuestros países, y ahora estoy aquí, como un invitado de honor y un rehén de honor. Los españoles están esperando una mejor oferta de nuestra parte. Envié un mensaje a Europa, con suerte la respuesta llegará en dos meses y podremos reanudar las negociaciones. Si no llega en dos meses, definitivamente estará aquí en los próximos seis meses. \nY sí, aunque el Papa y Mazarino han llegado a un compromiso en las últimas semanas, es demasiado pronto para hablar de una relación realmente entrañable. Honestamente, no estoy seguro de que alguna vez lleguemos a algún acuerdo. Me parece que Palotti simplemente me mantiene como un argumento en sus propios juegos de poder político. Sin embargo, debo decir que el inquisidor tiene un excelente café.";
		link.l1 = "¡No tengo ni seis meses, ni dos meses! Debo cumplir el deseo de mi padre, o él me obligará a casarme sin mi consentimiento. Y su salud no es tan buena como solía ser, pero me gustaría tener tiempo para presentarle a mi elegida, y la futura dama de Monper.";
		link.l1.go = "LH_abbat_3";
		break;

	case "LH_abbat_3":
		dialog.text = "Me temo que tendrás que encontrar otro sacerdote para tu boda entonces, hijo mío. Ay, me quedaré aquí por mucho tiempo.";
		link.l1 = "¿Qué dirías si te aparto del café del inquisidor?";
		link.l1.go = "LH_abbat_4";
		break;

	case "LH_abbat_4":
		dialog.text = "Aceptaría con gusto tu ayuda. Sospecho que no fui elegido para esta misión por casualidad. En el peor de los casos, simplemente se olvidarán del padre Benoit. Y, aunque el Señor me mandó a soportar, estoy agobiado por mi conclusión, a pesar de todas sus... bendiciones. Pero, repito, es poco probable que el padre Palotti escuche tus peticiones.";
		link.l1 = "Entonces me ahorraré algo de tiempo y no intentaré convencerlo. Simplemente saldremos de la iglesia tan pronto como termine el servicio, y nos dirigiremos a mi barco. No dude, Santo Padre, vieron nuestra reunión y me reconocerán, y será mucho más difícil ayudarle si tengo que sacarlo de la mansión del gobernador.";
		link.l1.go = "LH_abbat_5";
		break;

	case "LH_abbat_5":
		dialog.text = "Es arriesgado, hijo mío, muy arriesgado. Un grupo de guardias está esperando afuera para escoltarme a la mansión, y la ciudad está llena de soldados.";
		link.l1 = "Iremos con el elemento sorpresa, Padre Benoit. Solo tienes que confiar en mí y todo saldrá bien. Tengo algo de... experiencia en estos asuntos.";
		link.l1.go = "LH_abbat_6";
		break;

	case "LH_abbat_6":
		dialog.text = "Como desees. ¡Pero, por favor, hazlo sin derramamiento de sangre innecesario! Yo también he tenido algunas experiencias de este tipo... Guíanos, hijo mío. Estoy justo detrás de ti. Pero no voy a tomar un arma, así que ni lo pidas.";
		link.l1 = "Ni siquiera lo pensé, Padre. Puedo manejarlo. Sígueme, pero ten cuidado, podrían dispararnos.";
		link.l1.go = "LH_abbat_7";
		break;

	case "LH_abbat_7":
		DialogExit();
		LongHappy_SantiagoBenuaEscape();
		break;

	case "LH_abbat_8":
		LocatorReloadEnterDisable("FortFrance_town", "reload1_back", false);
		LocatorReloadEnterDisable("FortFrance_town", "reload2_back", false);
		LocatorReloadEnterDisable("FortFrance_town", "gate_back", false);
		dialog.text = "Hijo mío, no tuve tiempo de agradecerte por mi liberación. Aparentemente, el obispo español y el inquisidor Palotti querían interrumpir las apenas establecidas relaciones entre nuestro cardenal y la Santa Sede, así que actuaste completamente dentro de los intereses de nuestro país. Una vez más. Pero nadie te dirá 'gracias', excepto yo.";
		link.l1 = "Cosa común, Santo Padre. Me alegra haber podido ayudar. Pero, también tengo que pedirle algo, ¿recuerda?";
		link.l1.go = "LH_abbat_9";
		break;

	case "LH_abbat_9":
		dialog.text = "¡Por supuesto! Entonces vamos a ocuparnos del negocio placentero, Charles. ¿cómo van los preparativos para tu día más importante?";
		link.l1 = "Está tomando forma lentamente. Conozco campañas militares que se prepararon más fácil y rápido, ¡pero vale la pena!";
		link.l1.go = "LH_abbat_10";
		break;

	case "LH_abbat_10":
		dialog.text = "¡Claro, hijo mío! Y, en esta ocasión, quiero aclarar algo, ¿cómo ves tu ceremonia de boda?";
		link.l1 = "¿Te refieres a qué tan pomposo?";
		link.l1.go = "LH_abbat_11";
		break;

	case "LH_abbat_11":
		dialog.text = "¡Por supuesto! Porque debo preparar la iglesia, y quizás, querrás invitar a algunas personas importantes.";
		link.l1 = "Nada especial, Santo Padre. Aquellos a quienes considero nuestros amigos nos estarán esperando en otro lugar. Aquí solo habrá algunos oficiales, mis muchachos y algunos espectadores comunes.";
		link.l1.go = "LH_abbat_12";
		break;

	case "LH_abbat_12":
		dialog.text = "Bueno, entonces, creo que nos las arreglaremos con una pequeña donación.";
		link.l1 = "Eso no suena tan aterrador. ¿Y cuánto es tal donación en oro?";
		link.l1.go = "LH_abbat_13";
		break;

	case "LH_abbat_13":
		dialog.text = "Para el coro, servicio solemne y otros gastos: ciento cincuenta, no más. Además, la donación habitual de los recién casados, en total: doscientos doblones.";
		if (PCharDublonsTotal() >= 200) // Sinistra legendary edition
		{
			link.l1 = "Aquí tiene, Santo Padre.";
			link.l1.go = "LH_abbat_15";
		}
		else
		{
			link.l1 = "Sobre esas campañas militares... Tendré que darme un paseo hasta el banco y regresar.";
			link.l1.go = "LH_abbat_14";
		}
		break;

	case "LH_abbat_14":
		DialogExit();
		npchar.dialog.currentnode = "LH_abbat_14_1";
		break;

	case "LH_abbat_14_1":
		dialog.text = "¿Qué hay de tu donación, hijo mío?";
		if (PCharDublonsTotal() >= 200) // Sinistra legendary edition
		{
			link.l1 = "Aquí tiene, Santo Padre.";
			link.l1.go = "LH_abbat_15";
		}
		else
		{
			link.l1 = "Sí, sí, lo traeré pronto...";
			link.l1.go = "LH_abbat_14";
		}
		break;

	case "LH_abbat_15":
		RemoveDublonsFromPCharTotal(200); // Sinistra legendary edition
		dialog.text = "Aún hay una pregunta que necesita ser respondida: ¿quién entregará a la novia y testificará el matrimonio de su parte?";
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
		{
			pchar.questTemp.LongHappy.Pater1 = "Svenson";
			link.l1 = "Jan Svensson, de Blueweld. Es un inglés, pero una persona respetada y apegada a Helen como si fuera su propia hija, y su madre adoptiva es Gladys McArthur.";
		}
		else
		{
			if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor"))
			{
				pchar.questTemp.LongHappy.Pater1 = "Noel";
				link.l1 = "Barón Noel Forget, estoy seguro de que me hará el honor.";
			}
			else
			{
				pchar.questTemp.LongHappy.Pater1 = "Puancie";
				link.l1 = "Chevalier Philippe de Poincy, estoy seguro de que me hará el honor.";
			}
		}
		link.l1.go = "LH_abbat_16";
		break;

	case "LH_abbat_16":
		dialog.text = "Bueno, ¿y quién testificará por el novio? Recuerda, debe ser un hombre de noble cuna y reputación digna.";
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
		{
			if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor"))
			{
				link.l1 = "Barón Noel Forget, estoy seguro de que me hará el honor.";
				link.l1.go = "LH_abbat_17_1";
			}
			else
			{
				link.l1 = "Chevalier Philippe de Poincy, estoy seguro de que me hará el honor.";
				link.l1.go = "LH_abbat_17_2";
			}
			link.l2 = "Fadey, un respetable comerciante de Guadalupe. Solo necesito abastecerme de su licor favorito.";
			link.l2.go = "LH_abbat_17_3";
		}
		else
		{
			link.l1 = "Fadey, un comerciante respetable de Guadalupe. Solo necesito abastecerme de su licor favorito.";
			link.l1.go = "LH_abbat_17_3";
		}
		break;

	case "LH_abbat_17_1":
		pchar.questTemp.LongHappy.Pater2 = "Noel";
		dialog.text = "Estupendo, enviaré las invitaciones, pero los invitados necesitarán algo de tiempo para llegar aquí. Creo que todo estará listo en un mes, y las personas indicadas habrán llegado a la ciudad.";
		link.l1 = "¡Bien! Entonces tengo tiempo para hacer un par de recados. ¡Nos vemos pronto, Santo Padre, y deséame suerte!";
		link.l1.go = "LH_abbat_18";
		break;

	case "LH_abbat_17_2":
		pchar.questTemp.LongHappy.Pater2 = "Puancie";
		dialog.text = "Estupendo, enviaré las invitaciones, pero los invitados necesitarán algo de tiempo para llegar aquí. Creo que todo estará listo en un mes y las personas indicadas habrán llegado a la ciudad.";
		link.l1 = "¡Bien! Entonces tengo tiempo para hacer un par de recados. ¡Nos vemos pronto, Santo Padre, y deséame buena suerte!";
		link.l1.go = "LH_abbat_18";
		break;

	case "LH_abbat_17_3":
		pchar.questTemp.LongHappy.Pater2 = "Fadey";
		dialog.text = "Estupendo, enviaré las invitaciones, pero los invitados necesitarán algo de tiempo para llegar aquí. Creo que todo estará listo en un mes, y las personas indicadas habrán llegado a la ciudad.";
		link.l1 = "¡Bien! Entonces tengo tiempo para hacer un par de recados. ¡Nos vemos pronto, Santo Padre, y deséame buena suerte!";
		link.l1.go = "LH_abbat_18";
		break;

	case "LH_abbat_18":
		DialogExit();
		AddQuestRecord("LongHappy", "11");
		SetFunctionTimerCondition("LongHappy_SenPierreGuests", 0, 0, 31, false); // таймер
		if (!CheckAttribute(pchar, "questTemp.LongHappy.MarryRum"))
		{
			pchar.questTemp.LongHappy = "toIslaTesoro";
			LocatorReloadEnterDisable("Pirates_town", "reload4_back", true); // закрыть таверну Исла-Тесоро
		}
		npchar.dialog.currentnode = "First time";
		break;

	case "LH_abbat_19":
		dialog.text = "¡Entonces, ha llegado el día, hijo mío! Todo está listo: en un par de horas podremos empezar. ¡Pareces pálido!";
		link.l1 = "Tengo un poco de nervios, Santo Padre.";
		link.l1.go = "LH_abbat_20";
		break;

	case "LH_abbat_20":
		dialog.text = "Eso es común. Este es el día más importante de tu vida, y estoy sinceramente feliz por ti, como todos los que vinieron. Espero que al menos recuerdes las oraciones básicas, nunca has mimado mucho a la iglesia con tu atención, ¿verdad? Sin embargo, te ayudaré en cualquier caso.\nY una cosa más: por lo que entiendo, la novia no cambiará sus principios y no la veremos en un vestido, ¿verdad? Bueno, la alta sociedad está a punto de ver otra sorpresa de tu parte, estás lleno de ellas. De todos modos, ve hijo mío, ponte en forma adecuada y comenzaremos.";
		link.l1 = "Sí, Santo Padre. Hagámoslo.";
		link.l1.go = "LH_abbat_21";
		break;

	case "LH_abbat_21":
		DialogExit();
		chrDisableReloadToLocation = true;
		WaitDate("", 0, 0, 0, 2, 0);
		DoQuestReloadToLocation("FortFrance_church", "reload", "reload1", "LongHappy_MarryInit");
		break;

	case "LH_abbat_22":
		pchar.questTemp.LongHappy.Mistake = 0;
		dialog.text = "Pater noster, qui es in caelis, sanctificetur nomen tuum, ad...";
		link.l1 = "... venga tu reino";
		link.l1.go = "LH_abbat_23_1";
		link.l2 = "...requiem aeternam dona eis.";
		link.l2.go = "LH_abbat_23_2";
		break;

	case "LH_abbat_23_1":
		dialog.text = "...hágase tu voluntad, así en la tierra como en el cielo. Danos hoy nuestro pan de cada día, y perdona nuestras deudas...";
		link.l1 = "...así como nosotros perdonamos a nuestros deudores.";
		link.l1.go = "LH_abbat_24_1";
		link.l2 = "...sicut erat in principio, et nunc et semper, et in saecula saeculorum. Amén.";
		link.l2.go = "LH_abbat_24_2";
		break;

	case "LH_abbat_23_2":
		pchar.questTemp.LongHappy.Mistake = sti(pchar.questTemp.LongHappy.Mistake) + 1;
		dialog.text = "¿E-e... Hm...?";
		link.l1 = "";
		link.l1.go = "LH_abbat_23_1";
		break;

	case "LH_abbat_24_2":
		pchar.questTemp.LongHappy.Mistake = sti(pchar.questTemp.LongHappy.Mistake) + 1;
		dialog.text = "E-e... Hm...";
		link.l1 = "";
		link.l1.go = "LH_abbat_24_1";
		break;

	case "LH_abbat_24_1":
		dialog.text = "et ne nos inducas in tentationem; sed libera nos a malo. Amén.";
		link.l1 = "Amén.";
		link.l1.go = "LH_abbat_25";
		break;

	case "LH_abbat_25":
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			sld = characterFromId("Helena");
		else
			sld = characterFromId("Mary");
		dialog.text = "Amados, estamos aquí reunidos ante la vista de Dios, y ante esta congregación, para unir a este hombre y mujer en santo Matrimonio. Amados " + sld.name + " y Charles, escuchaste la palabra de Dios, quien te recordó el significado del amor humano y el matrimonio. Ahora, en nombre de la santa Iglesia, deseo desafiar tus intenciones.\n" + sld.name + " y Charles, ¿tienen el deseo voluntario y sincero de unirse en el vínculo del matrimonio, ante nuestro Señor?";
		link.l1 = "Sí.";
		link.l1.go = "LH_abbat_26";
		break;

	case "LH_abbat_26":
		DialogExit();
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			sld = characterFromId("Helena");
		else
			sld = characterFromId("Mary");
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;

	case "LH_abbat_27":
		dialog.text = "¿Tienen intención de ser fieles el uno al otro, en la salud y la enfermedad, en la felicidad y la desgracia, hasta que la muerte los separe?";
		link.l1 = "Sí.";
		link.l1.go = "LH_abbat_28";
		break;

	case "LH_abbat_28":
		DialogExit();
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			sld = characterFromId("Helena");
		else
			sld = characterFromId("Mary");
		sld.dialog.currentnode = "LongHappy_22";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;

	case "LH_abbat_29":
		dialog.text = "¿Tienes la intención de amar y aceptar a los hijos que nuestro Señor te enviará y criarlos en la fe cristiana?";
		link.l1 = "Sí.";
		link.l1.go = "LH_abbat_30";
		break;

	case "LH_abbat_30":
		DialogExit();
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			sld = characterFromId("Helena");
		else
			sld = characterFromId("Mary");
		sld.dialog.currentnode = "LongHappy_24";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;

	case "LH_abbat_31":
		dialog.text = "Bueno, volveos el uno al otro y haced un juramento.";
		link.l1 = "";
		link.l1.go = "LH_abbat_32";
		break;

	case "LH_abbat_32":
		DialogExit();
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			sld = characterFromId("Helena");
		else
			sld = characterFromId("Mary");
		sld.dialog.currentnode = "LongHappy_26";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;

	case "LH_abbat_33":
		dialog.text = "Si alguien aquí presente conoce alguna razón por la cual esta pareja no deba unirse en santo matrimonio, que hable ahora o calle para siempre.\nEn este caso, ante el rostro del Señor y las personas reunidas aquí, ¡os declaro marido y mujer! In nomine Patris, et Filii, et Spiritus Sancti. Amén.";
		link.l1 = "Amén.";
		link.l1.go = "LH_abbat_34";
		break;

	case "LH_abbat_34":
		DialogExit();
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			sld = characterFromId("Helena");
		else
			sld = characterFromId("Mary");
		sld.dialog.currentnode = "LongHappy_29";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;

	case "LH_abbat_35":
		string sTemp;
		if (sti(pchar.questTemp.LongHappy.Mistake) > 1)
			sTemp = "(Susurrando) Charles, hijo mío, mueve los labios, te lo ruego, no intentes emitir ningún sonido....";
		else
			sTemp = "";
		dialog.text = "Recién casados, arrodillaos y rezad juntos. Oratio fidelium." + sTemp + "";
		link.l1 = "";
		link.l1.go = "LH_abbat_36";
		break;

	case "LH_abbat_36":
		DialogExit();
		SetLaunchFrameFormParam("Ha pasado algún tiempo...", "", 0.1, 3.0);
		LaunchFrameForm();
		WaitDate("", 0, 0, 0, 1, 0);
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			sld = characterFromId("Helena");
		else
			sld = characterFromId("Mary");
		sld.lastname = "de Maure";
		sld.dialog.currentnode = "LongHappy_31";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 4.0);
		break;

	case "LH_abbat_37":
		dialog.text = "Mis felicitaciones, hijo. Tu padre puede estar orgulloso de ti, y yo también lo estoy. Sed felices y cuidaos el uno al otro en estos tiempos difíciles.";
		link.l1 = "Gracias, Santo Padre. Fue un servicio maravilloso y me alegra que haya sido usted quien lo ofició.";
		link.l1.go = "LH_abbat_38";
		break;

	case "LH_abbat_38":
		DialogExit();
		LAi_CharacterDisableDialog(npchar);
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}
