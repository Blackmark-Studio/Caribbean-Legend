// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué quieres? Pregunta lo que quieras.", "Te escucho, ¿cuál es la pregunta?"), "Es la segunda vez que intentas preguntar...", "Es la tercera vez que intentas preguntar de nuevo...", "¿Cuándo va a terminar?! ¡Soy un hombre ocupado, trabajando en asuntos de la colonia y tú sigues intentando preguntar algo!", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión...", "Ahora no. Lugar y momento equivocados."), "Verdad... Pero más tarde, no ahora...", "Preguntaré... Pero un poco más tarde...", "Lo siento, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		if (CheckAttribute(pchar, "questTemp.Guardoftruth.Baster_church") && !CheckAttribute(npchar, "quest.utensil"))
		{
			link.l1 = "Tengo un asunto delicado para ti. No hace mucho, un corsario donó una cruz de oro con un lazurita a la parroquia de Basse-Terre. El problema es que la cruz fue robada de la parroquia de Santiago y un clérigo fue asesinado durante el robo...";
			link.l1.go = "guardoftruth";
		}
		// Jason НСО
		if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_9_continue" && !CheckAttribute(npchar, "quest.frigate"))
		{
			link.l1 = "Llegué por orden del Gobernador General Philippe de Poincy para tomar el mando de vuestra fragata armada.";
			link.l1.go = "patria";
		}
		if (CheckAttribute(npchar, "quest.frigate.wait") && GetCompanionQuantity(pchar) < 5)
		{
			link.l1 = "Estoy listo para llevar la fragata a la escuadra.";
			link.l1.go = "patria_2";
		}
		// Jason Дороже золота
		if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "baster")
		{
			link.l1 = "Tengo una reunión aquí con una persona...";
			link.l1.go = "baster_goldengirl";
		}
		//--> Торговля по закону
			if (CheckAttribute(pchar, "questTemp.TPZ_guber_1"))
			{
				link.l1 = "Señor, planeo emprender una actividad comercial en esta ciudad. En particular, me interesa el comercio de bebidas alcohólicas a gran escala y de forma regular.";
				link.l1.go = "TPZ_guber_1";
			}
			//<-- Торговля по закону

		break;
	//************************** Квестовые штрумы ************************
	case "Cupture_after":
		dialog.text = RandPhraseSimple("Ya te has llevado todo. ¿Qué más quieres?", "¿Queda algo que no hayas agarrado?");
		link.l1 = RandPhraseSimple("Sólo estoy echando un vistazo...", "Solo comprobando, podría olvidar llevar algo...");
		link.l1.go = "exit";
		NextDiag.TempNode = "Cupture_after";
		break;

	case "guardoftruth":
		dialog.text = "Mm. Eso es bastante interesante. Pero ¿por qué crees que me importan los problemas de los españoles?";
		link.l1 = "No se trata de los españoles, Monsieur. La religión no divide a las personas por nacionalidad. Hay un objeto cubierto con la sangre del santo servidor en su parroquia y se cometió una profanación en la parroquia de Santiago...";
		link.l1.go = "guardoftruth_1";
		break;

	case "guardoftruth_1":
		dialog.text = "";
		link.l1 = "Le pido que muestre justicia y ordene al santo padre devolver la cruz a sus dueños.";
		link.l1.go = "guardoftruth_2";
		break;

	case "guardoftruth_2":
		dialog.text = "¿Y desde cuándo te has convertido en un verdadero y sincero creyente, " + pchar.name + "? Los españoles no son nuestros amigos y no veo razón para presionar al santo padre en este asunto. La cruz fue un regalo y está bien. Nuestro sacerdote no tiene conexión con ese robo y asesinato, así que...";
		link.l1 = "Y no puedes ayudarme, ¿verdad?";
		link.l1.go = "guardoftruth_3";
		break;

	case "guardoftruth_3":
		dialog.text = "Para ser honesto, " + pchar.name + ", no siento que deba hacerlo. No tengo amor por esos fanáticos papistas.";
		link.l1 = "Ya veo. Perdón por molestarte, Monsieur...";
		link.l1.go = "guardoftruth_4";
		break;

	case "guardoftruth_4":
		DialogExit();
		npchar.quest.utensil = "true";
		AddQuestRecord("Guardoftruth", "28");
		break;

	// Jason НСО
	case "patria":
		if (GetCompanionQuantity(pchar) > 4)
		{
			dialog.text = "La nave está lista, pero no tienes un lugar libre para ella en tu escuadrón. Capitán, reduce tu escuadrón y regresa, entonces te entregaré inmediatamente la fragata.";
			link.l1 = "Bien.";
			link.l1.go = "patria_1";
		}
		else
		{
			dialog.text = "Sí, por supuesto, el barco está listo para zarpar. Su capitán está al tanto y seguirá todas sus órdenes.";
			link.l1 = "Entonces partimos. Adiós, Su Gracia.";
			link.l1.go = "patria_3";
		}
		break;

	case "patria_1":
		DialogExit();
		npchar.quest.frigate.wait = "true";
		break;

	case "patria_2":
		DeleteAttribute(npchar, "quest.frigate.wait");
		dialog.text = "Excelente. Prepárate para recibir tu nuevo barco. Su capitán está al tanto y seguirá todas tus órdenes.";
		link.l1 = "Entonces zarpamos. Adiós, Su Gracia.";
		link.l1.go = "patria_3";
		break;

	case "patria_3":
		DialogExit();
		npchar.quest.frigate = "true";
		Patria_BastionFrigateGlp(); // присоединяем фрегат
		break;

	// Jason Дороже золота
	case "baster_goldengirl":
		dialog.text = "¡Ah, Monsieur Charles de Maure, perfecto timing! Mi viejo amigo está muy ansioso por conocerte y pidió que le informara de tu llegada. Por favor, ven a mi sala de estar, avisaré a Angerran inmediatamente. ¿Cómo os conocisteis, por cierto?";
		link.l1 = "Jugamos juntos. Él perdió, tuvimos una pequeña pelea. Supongo que Monsieur de Chievous querría arreglar las cosas entre nosotros.";
		link.l1.go = "baster_goldengirl_1";
		break;

	case "baster_goldengirl_1":
		dialog.text = "¡Sin duda! Espero que arreglen las cosas entre ustedes dos. Angerran puede no ser la persona más agradable con quien tratar, pero es astuto y honorable, al igual que tú. Es una raza rara.";
		link.l1 = "Me halagas, Excelencia. Esperaré por él en la sala de estar si no te importa.";
		link.l1.go = "baster_goldengirl_2";
		break;

	case "baster_goldengirl_2":
		dialog.text = "Pero por supuesto, como guste, siéntase como en casa. Quizás tendrá que esperar un poco. Ordenaré que traigan algunas bebidas.";
		link.l1 = "Gracias, Excelencia, pero pasaré. Solo me sentaré y esperaré a nuestro mutuo... amigo.";
		link.l1.go = "baster_goldengirl_3";
		break;

	case "baster_goldengirl_3":
		DialogExit();
		pchar.questTemp.GoldenGirl = "baster1";
		DoQuestReloadToLocation("CommonResidence_3", "reload", "reload1", "GoldenGirl_AngerranInResidence");
		break;
		
	//--> Торговля по закону
	case "TPZ_guber_1":
		dialog.text = "Capitán, hizo bien en acudir a mí. Estamos haciendo todo lo posible para combatir el comercio ilegal en la isla, y me alegra sinceramente cuando capitanes honestos vienen a mí para organizar todo legalmente.";
		link.l1 = "Entonces, ¿cuáles son las condiciones y pasos necesarios para comenzar a comerciar?";
		link.l1.go = "TPZ_guber_2";
		DelLandQuestMark(npchar);
	break;

	case "TPZ_guber_2":
		dialog.text = "Es bastante simple. Para comerciar con bebidas alcohólicas, deberá pagar un impuesto al tesoro de cien doblones al mes, además de llevar documentación y presentar informes regularmente sobre su actividad. Una vez que haya depositado el dinero en el tesoro, puede comenzar a comerciar con confianza.";
		link.l1 = "Excelente. Las condiciones son bastante aceptables. En mi nombre, un residente local, Christian Delouche, se encargará de los asuntos aquí. ¿Espero que no haya problemas con eso?";
		link.l1.go = "TPZ_guber_3";
	break;

	case "TPZ_guber_3":
		dialog.text = "Como desee, capitán. Sin embargo, recuerde: toda la responsabilidad por su protegido recae sobre usted, y en caso de sus faltas, compartirá su destino.";
		link.l1 = "Por supuesto. Gracias por las aclaraciones, señor gobernador. Prepararemos todo, y Christian pagará el impuesto.";
		link.l1.go = "TPZ_guber_4";
	break;

	case "TPZ_guber_4":
		dialog.text = "Excelente. Me complace ver un enfoque tan diligente. Le deseo éxito en su empresa.";
		link.l1 = "Gracias. Estoy seguro de que nuestra cooperación beneficiará a la ciudad. Adiós.";
		link.l1.go = "TPZ_guber_5";
	break;

	case "TPZ_guber_5":
		DialogExit();
		DeleteAttribute(pchar, "questTemp.TPZ_guber_1");
		AddQuestRecord("TPZ", "11");

		sld = CharacterFromID("TPZ_Kristian");
		sld.dialog.filename = "Quest\MiniEvents\TradingByLaw_dialog.c";
		sld.dialog.currentnode = "Kristian_21";
		ChangeCharacterAddressGroup(sld, "BasTer_houseF3", "barmen", "stay");
		LAi_SetStayType(sld);
		AddLandQuestMark(sld, "questmarkmain");
	break;
	//<-- Торговля по закону
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}
