// Слухи - диалог по типажам

#define MAX_RUMOURS_ABOUT_OWNERS 7

void ProcessCommonDialogRumors(ref NPChar, aref Link, aref NextDiag);
{
	string strum;
	string srum;
	bool bOk1, bOk2;
	switch (Dialog.CurrentNode)
	{
/////////////////////////////////////////////////---слухи мещанок---////////////////////////////////////////////
	case "rumours_towngirl":
		NextDiag.CurrentNode = "rumours";

		//--> Тёмные воды исцеления
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		if (bOk1 || bOk2)
        {
			dialog.text = "¿Lo habéis oído? Dicen que la hija de Thomas Morrison lleva ya medio año postrada en la cama. Los médicos están completamente impotentes ante su enfermedad. La única que podría ayudarla es una gitana famosa por sus brebajes, capaces de sanar incluso a los más enfermos. Pero se negó rotundamente a hacer nada por la pobre muchacha.";
			link.l1 = "Gracias, debería irme.";
			link.l1.go = "exit";
			
			SetQuestHeader("DWH");
			AddQuestRecord("DWH", "1");
			pchar.questTemp.DWH_Start = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("DWH_gypsy", "gipsy_2", "woman", "towngirl", 10, PIRATE, -1, true, "citizen"));
			ChangeCharacterAddressGroup(sld, "SentJons_town", "goto", "goto1");
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "dwh_gypsy_0";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_SetLoginTime(sld, 07.00, 21.99);
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Тёмные воды исцеления
		//--> Грани справедливости
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		if (bOk1 || bOk2)
        {
			dialog.text = "Anteayer hubo un atrevido intento de asesinato contra el jefe de autoridad portuaria. El asesino lo esperaba a la salida de su oficina, pero logró pedir ayuda. Un mosquetero llegó a tiempo e hirió al atacante, pero el criminal logró escapar de la ciudad\nDicen que el jefe del puerto está ofreciendo una generosa recompensa por su cabeza. Hasta ahora, ningún valiente se ha presentado.";
			link.l1 = "Gracias, debería irme.";
			link.l1.go = "exit";
			
			SetQuestHeader("GS");
			AddQuestRecord("GS", "1");
			pchar.questTemp.GS_Start = true;
			pchar.questTemp.GS_Portman = true;
			AddLandQuestMark(characterFromId("Beliz_portman"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Грани справедливости
		//--> Торговля по закону
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		if (bOk1 || bOk2)
        {
			dialog.text = "¿Habéis oído las nuevas?! ¡Es una maldita vergüenza! Ni una gota de ron o vino queda en la taberna - ¿cómo ha de encontrar uno alivio en este calor infernal? El tabernero nos lleva alimentando con promesas vacías toda una semana de que la bebida volverá a fluir, ¡pero no ha habido nada! ¿Se espera que sequemos nuestras gargantas hasta el Día del Juicio?";
			link.l1 = "Gracias, debería irme.";
			link.l1.go = "exit";
			
			SetQuestHeader("TPZ");
			AddQuestRecord("TPZ", "1");
			pchar.questTemp.TPZ_Start = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Торговля по закону
		//--> Украденное воспоминание
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		if (bOk1 || bOk2)
        {
			dialog.text = "Se rumorea en el puerto que Julie d'Armagnac, la sobrina del gobernador, se ha convertido en una mera sombra de lo que era. Antes radiante y llena de vida, ahora deambula por las calles con una tristeza inconfundible grabada en su rostro. Los habitantes del pueblo murmuran y se preguntan qué podría haberle sucedido, pero nadie conoce la verdad. ¿Quizás algún canalla le ha roto el corazón?"+GetSexPhrase(" ¿Fue usted, Capitán?","")+"";
			link.l1 = ""+GetSexPhrase("Lo dudo. ","")+"Gracias, debería irme.";
			link.l1.go = "exit";
			
			SetQuestHeader("UV");
			AddQuestRecord("UV", "1");
			pchar.questTemp.UV_Start = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("UV_Juli", "women_4", "woman", "woman", sti(pchar.rank), FRANCE, -1, false, "quest"));
			sld.name = StringFromKey("Neutral_6");
			sld.lastname = StringFromKey("Neutral_7");
			sld.City = "PortPax";
			ChangeCharacterAddressGroup(sld, "PortPax_town", "goto", "goto9");
			sld.dialog.filename = "Quest\MiniEvents\StolenMemory_dialog.c";
			sld.dialog.currentnode = "Juli";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_SetImmortal(sld, true);
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Украденное воспоминание
		//--> В плену великого улова andre39966
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		if (bOk1 || bOk2)
        {
			dialog.text = "Anteayer hubo un atrevido intento de asesinato contra el jefe de autoridad portuaria. El asesino lo esperaba a la salida de su oficina, pero logró pedir ayuda. Un mosquetero llegó a tiempo e hirió al atacante, pero el criminal logró escapar de la ciudad\nDicen que el jefe del puerto está ofreciendo una generosa recompensa por su cabeza. Hasta ahora, ningún valiente se ha presentado. ¿Sabes? Aunque ofreciera mil doblones, yo no aceptaría...";
			link.l1 = "Gracias, debería irme.";
			link.l1.go = "exit";
			
			SetQuestHeader("VPVL");
			AddQuestRecord("VPVL", "1");
			pchar.questTemp.VPVL_Start = true;
			AddDialogExitQuest("VPVL_Gegerate_Lea");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- В плену великого улова 
		//--> Тайна Бетси Прайс
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		if (bOk1 || bOk2)
        {
			dialog.text = "Capitán, ¿ha oído? Hay una nueva camarera trabajando en nuestra taberna. Dicen que es toda una belleza. Hombres de todas partes han estado acudiendo solo para verla. Pero hace tres días no se presentó a trabajar, lo que disgustó mucho al tabernero, quien había estado obteniendo enormes ganancias desde su llegada. Dicen que incluso está dispuesto a pagar a quien pueda encontrarla.​";
			link.l1 = "Gracias, debería irme.";
			link.l1.go = "exit";
			
			SetQuestHeader("TBP");
			AddQuestRecord("TBP", "1");
			pchar.questTemp.TBP_Start = true;
			pchar.questTemp.TBP_Tavern = true;
			AddLandQuestMark(CharacterFromID("Villemstad_tavernkeeper"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Тайна Бетси Прайс
		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 2)
			srum = SelectRumourEx("towngirl", NPChar);
		else
			srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
		string posrep1, posrep2, answ1, answ2, answ3, answ4;
		if (RumourHasInformation(srum))
		{
			posrep1 = RandPhraseSimple(" Eso es todo...", " Puedes encontrarlo gracioso.");
			posrep2 = " Oye, capitán, ¿tienes noticias para nuestra colonia?";
			answ1 = RandPhraseSimple(RandSwear() + "Estás diciendo cosas interesantes, " + GetFullName(NPChar) + ".",
									 "Entonces, cuéntame sobre...");
			answ2 = RandPhraseSimple(RandSwear() + "¡Qué interesante! Hay una cosa más que quería preguntar...", "Una pregunta más.");
			answ3 = RandPhraseSimple("Ese tipo de cosas suceden todo el tiempo. Lo siento, pero no tengo nada especial que contarte. ", "Tengo mucha prisa, quizás la próxima vez.");
			answ4 = "";
		}
		else
		{
			posrep1 = " Es un lugar bastante aburrido. Si algo sucede, todos hablarán sobre eso.";
			posrep2 = " No hay nada de interés. ¿" + GetAddress_Form(NPChar) + " podría saber algo?";
			answ1 = RandPhraseSimple("Cuéntame sobre...", RandSwear() + "¡No sabes nada! Está bien, sobre otro tema...");
			answ2 = RandPhraseSimple("Tendrá que ser así, dime algo más...", "Sí, no fuiste de mucha ayuda, ¿tienes algo más que compartir conmigo?");
			answ3 = RandPhraseSimple("Dudo que tengas algo de interés que contarme.", "Será un placer, pero hablemos la próxima vez.");
			answ4 = "";
		}
		Dialog.Text = NPCStringReactionRepeat(srum,
											  srum + posrep1,
											  srum + posrep2,
											  RandPhraseSimple("Por desgracia, no tengo nada más que decirte, déjame pasar.", "Ya tuve suficientes preguntas, discúlpame, tengo asuntos que atender."), "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(answ1,
										   answ2,
										   answ3,
										   answ4,
										   npchar, Dialog.CurrentNode);
		link.l1.go = "new question";
		link.l2 = RandPhraseSimple("Gracias, debería irme.", "Adiós.");
		link.l2.go = "exit";
		break;

		/////////////////////////////////////////////////---слухи мещан---////////////////////////////////////////////
	case "rumours_townman":
		NextDiag.CurrentNode = "rumours";

		//--> Тёмные воды исцеления
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		if (bOk1 || bOk2)
        {
			dialog.text = "¿Lo habéis oído? Dicen que la hija de Thomas Morrison lleva ya medio año postrada en la cama. Los médicos están completamente impotentes ante su enfermedad. La única que podría ayudarla es una gitana famosa por sus brebajes, capaces de sanar incluso a los más enfermos. Pero se negó rotundamente a hacer nada por la pobre muchacha.";
			link.l1 = "Gracias, debería irme.";
			link.l1.go = "exit";
			
			SetQuestHeader("DWH");
			AddQuestRecord("DWH", "1");
			pchar.questTemp.DWH_Start = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("DWH_gypsy", "gipsy_2", "woman", "towngirl", 10, PIRATE, -1, true, "citizen"));
			ChangeCharacterAddressGroup(sld, "SentJons_town", "goto", "goto1");
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "dwh_gypsy_0";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_SetLoginTime(sld, 07.00, 21.99);
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Тёмные воды исцеления
		
		//--> Грани справедливости
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		if (bOk1 || bOk2)
        {
			dialog.text = "Anteayer hubo un atrevido intento de asesinato contra el jefe de autoridad portuaria. El asesino lo esperaba a la salida de su oficina, pero logró pedir ayuda. Un mosquetero llegó a tiempo e hirió al atacante, pero el criminal logró escapar de la ciudad\nDicen que el jefe del puerto está ofreciendo una generosa recompensa por su cabeza. Hasta ahora, ningún valiente se ha presentado. ¿Sabes? Aunque ofreciera mil doblones, yo no aceptaría...";
			link.l1 = "Gracias, debería irme.";
			link.l1.go = "exit";
			
			SetQuestHeader("GS");
			AddQuestRecord("GS", "1");
			pchar.questTemp.GS_Start = true;
			pchar.questTemp.GS_Portman = true;
			AddLandQuestMark(characterFromId("Beliz_portman"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Грани справедливости
		
		//--> Торговля по закону
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		if (bOk1 || bOk2)
        {
			dialog.text = "¿Habéis oído las nuevas?! ¡Es una maldita vergüenza! Ni una gota de ron o vino queda en la taberna - ¿cómo ha de encontrar uno alivio en este calor infernal? El tabernero nos lleva alimentando con promesas vacías toda una semana de que la bebida volverá a fluir, ¡pero no ha habido nada! ¿Se espera que sequemos nuestras gargantas hasta el Día del Juicio?";
			link.l1 = "Gracias, debería irme.";
			link.l1.go = "exit";
			
			SetQuestHeader("TPZ");
			AddQuestRecord("TPZ", "1");
			pchar.questTemp.TPZ_Start = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Торговля по закону
		
		//--> Украденное воспоминание
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		if (bOk1 || bOk2)
        {
			dialog.text = "Se rumorea en el puerto que Julie d'Armagnac, la sobrina del gobernador, se ha convertido en una mera sombra de lo que era. Antes radiante y llena de vida, ahora deambula por las calles con una tristeza inconfundible grabada en su rostro. Los habitantes del pueblo murmuran y se preguntan qué podría haberle sucedido, pero nadie conoce la verdad. ¿Quizás algún canalla le ha roto el corazón?"+GetSexPhrase(" ¿Fue usted, Capitán?","")+"";
			link.l1 = ""+GetSexPhrase("Lo dudo. ","")+"Gracias, debería irme.";
			link.l1.go = "exit";
			
			SetQuestHeader("UV");
			AddQuestRecord("UV", "1");
			pchar.questTemp.UV_Start = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("UV_Juli", "women_4", "woman", "woman", sti(pchar.rank), FRANCE, -1, false, "quest"));
			sld.name = StringFromKey("Neutral_6");
			sld.lastname = StringFromKey("Neutral_7");
			sld.City = "PortPax";
			ChangeCharacterAddressGroup(sld, "PortPax_town", "goto", "goto9");
			sld.dialog.filename = "Quest\MiniEvents\StolenMemory_dialog.c";
			sld.dialog.currentnode = "Juli";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_SetImmortal(sld, true);
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Украденное воспоминание
		
		//--> В плену великого улова andre39966
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		if (bOk1 || bOk2)
        {
			dialog.text = "Anteayer hubo un atrevido intento de asesinato contra el jefe de autoridad portuaria. El asesino lo esperaba a la salida de su oficina, pero logró pedir ayuda. Un mosquetero llegó a tiempo e hirió al atacante, pero el criminal logró escapar de la ciudad\nDicen que el jefe del puerto está ofreciendo una generosa recompensa por su cabeza. Hasta ahora, ningún valiente se ha presentado. ¿Sabes? Aunque ofreciera mil doblones, yo no aceptaría...";
			link.l1 = "Gracias, debería irme.";
			link.l1.go = "exit";
			
			SetQuestHeader("VPVL");
			AddQuestRecord("VPVL", "1");
			pchar.questTemp.VPVL_Start = true;
			AddDialogExitQuest("VPVL_Gegerate_Lea");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- В плену великого улова 
		//--> Тайна Бетси Прайс
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		if (bOk1 || bOk2)
        {
			dialog.text = "Capitán, ¿ha oído? Hay una nueva camarera trabajando en nuestra taberna. Dicen que es toda una belleza. Hombres de todas partes han estado acudiendo solo para verla. Pero hace tres días no se presentó a trabajar, lo que disgustó mucho al tabernero, quien había estado obteniendo enormes ganancias desde su llegada. Dicen que incluso está dispuesto a pagar a quien pueda encontrarla.​";
			link.l1 = "Gracias, debería irme.";
			link.l1.go = "exit";
			
			SetQuestHeader("TBP");
			AddQuestRecord("TBP", "1");
			pchar.questTemp.TBP_Start = true;
			pchar.questTemp.TBP_Tavern = true;
			AddLandQuestMark(CharacterFromID("Villemstad_tavernkeeper"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Тайна Бетси Прайс
		
		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 2)
			srum = SelectRumourEx("townman", NPChar);
		else
			srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
		if (RumourHasInformation(srum))
		{
			posrep1 = RandPhraseSimple(" Eso es todo...", " Puedes encontrarlo gracioso.");
			posrep2 = " Oye, capitán, ¿tienes noticias para nuestra colonia?";
			answ1 = RandPhraseSimple(RandSwear() + "Estás diciendo cosas interesantes, " + GetFullName(NPChar) + ".",
									 "Cuéntame sobre...");
			answ2 = RandPhraseSimple(RandSwear() + "¡Qué interesante! Hay una cosa más que quería preguntar...", "Una pregunta más.");
			answ3 = RandPhraseSimple("Este tipo de cosas suceden todo el tiempo. Lo siento, pero no tengo nada especial que contarte. ", "Tengo mucha prisa, quizás la próxima vez.");
			answ4 = "";
		}
		else
		{
			posrep1 = " Es un lugar bastante aburrido, si algo sucede, todos hablarán sobre ello.";
			posrep2 = " No hay nada de interés. ¿" + GetAddress_Form(NPChar) + " podría saber algo?";
			answ1 = RandPhraseSimple("Cuéntame sobre...", RandSwear() + "¡No sabes nada! Está bien, sobre otro tema...");
			answ2 = RandPhraseSimple("Tendrá que ser así, dime algo más...", "Sí, no fuiste de mucha ayuda, ¿tienes algo más que compartir conmigo?");
			answ3 = RandPhraseSimple("Dudo que tengas algo de interés que contarme.", "Será un placer, hablemos la próxima vez.");
			answ4 = "";
		}
		Dialog.Text = NPCStringReactionRepeat(srum,
											  srum + posrep1,
											  srum + posrep2,
											  RandPhraseSimple("Por desgracia, no tengo nada más que decirte, déjame pasar.", "Ya tuve suficiente con las preguntas, discúlpame, tengo asuntos que atender."), "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(answ1,
										   answ2,
										   answ3,
										   answ4,
										   npchar, Dialog.CurrentNode);
		link.l1.go = "new question";
		link.l2 = RandPhraseSimple("Gracias, debería irme.", "Adiós.");
		link.l2.go = "exit";
		break;

	///////////////////////////////////---слухи тёмных личностей---////////////////////////////////////////////
	case "rumours_marginal":
		NextDiag.CurrentNode = "rumours";

		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 2)
			srum = SelectRumourEx("townman", NPChar);
		else
			srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
		if (RumourHasInformation(srum))
		{
			posrep1 = RandPhraseSimple(" Eso es todo...", " Puedes encontrarlo gracioso.");
			posrep2 = " Oye, capitán, ¿tienes noticias para nuestra colonia?";
			answ1 = RandPhraseSimple(RandSwear() + "Estás diciendo cosas interesantes, " + GetFullName(NPChar) + ".",
									 "Cuéntame sobre...");
			answ2 = RandPhraseSimple(RandSwear() + "Tendrá que ser así, dime algo más...", "Sí, no fuiste de mucha ayuda, ¿tienes algo más que compartir conmigo?");
			answ3 = RandPhraseSimple("Este tipo de cosas suceden todo el tiempo. Lo siento, pero no tengo nada especial que contarte. ", "Tengo mucha prisa, quizás la próxima vez.");
			answ4 = "";
		}
		else
		{
			posrep1 = " Es un lugar bastante aburrido, si algo sucede, todos hablarán sobre ello.";
			posrep2 = " No hay nada de interés. " + GetAddress_Form(NPChar) + " podría saber algo.";
			answ1 = RandPhraseSimple("Cuéntame sobre...", RandSwear() + "¡No sabes nada! Está bien, sobre otro tema...");
			answ2 = RandPhraseSimple("Tendrá que ser así, dime algo más...", "Sí, no fuiste de mucha ayuda, ¿tienes algo más que compartir conmigo?");
			answ3 = RandPhraseSimple("Dudo que tengas algo de interés que contarme.", "Será un placer, hablemos la próxima vez.");
			answ4 = "";
		}
		Dialog.Text = NPCStringReactionRepeat(srum,
											  srum + posrep1,
											  srum + posrep2,
											  RandPhraseSimple("Por desgracia, no tengo nada más que decirte, déjame pasar.", "Ya tuve suficiente con las preguntas, discúlpame, tengo asuntos que atender."), "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(answ1,
										   answ2,
										   answ3,
										   answ4,
										   npchar, Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("Gracias, debería irme.", "Adiós.");
		link.l2.go = "exit";
		break;

		/////////////////////////////////////////////////---слухи дворян---////////////////////////////////////////////
	case "rumours_nobleman":
		srum = SelectRumourEx("nobleman", NPChar);
		
		//--> Украденное воспоминание
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		if (bOk1 || bOk2)
        {
			dialog.text = "Se rumorea en el puerto que Julie d'Armagnac, la sobrina del gobernador, se ha convertido en una mera sombra de lo que era. Antes radiante y llena de vida, ahora deambula por las calles con una tristeza inconfundible grabada en su rostro. Los habitantes del pueblo murmuran y se preguntan qué podría haberle sucedido, pero nadie conoce la verdad. ¿Quizás algún canalla le ha roto el corazón?"+GetSexPhrase(" ¿Fue usted, Capitán?","")+"";
			link.l1 = ""+GetSexPhrase("Lo dudo. ","")+"Gracias, debería irme.";
			link.l1.go = "exit";
			
			SetQuestHeader("UV");
			AddQuestRecord("UV", "1");
			pchar.questTemp.UV_Start = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("UV_Juli", "women_4", "woman", "woman", sti(pchar.rank), FRANCE, -1, false, "quest"));
			sld.name = StringFromKey("Neutral_6");
			sld.lastname = StringFromKey("Neutral_7");
			sld.City = "PortPax";
			ChangeCharacterAddressGroup(sld, "PortPax_town", "goto", "goto9");
			sld.dialog.filename = "Quest\MiniEvents\StolenMemory_dialog.c";
			sld.dialog.currentnode = "Juli";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_SetImmortal(sld, true);
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Украденное воспоминание
		
		if (RumourHasInformation(srum))
		{
			posrep1 = RandPhraseSimple(" Eso es todo...", " Puedes encontrarlo gracioso.");
			posrep2 = " Oye, capitán, ¿tienes noticias para nuestra colonia?";
			answ1 = RandPhraseSimple(RandSwear() + "Estás diciendo cosas interesantes, " + GetFullName(NPChar) + ".",
									 "Cuéntame sobre...");
			answ2 = RandPhraseSimple(RandSwear() + "Tendrá que ser así, dime algo más...", "Sí, no fuiste de mucha ayuda, ¿tienes algo más que compartir conmigo?");
			answ3 = RandPhraseSimple("Este tipo de cosas suceden todo el tiempo. Lo siento, pero no tengo nada especial que contarte. ", "Tengo mucha prisa, quizás la próxima vez.");
			answ4 = "";
		}
		else
		{
			posrep1 = " Es un lugar bastante aburrido, si algo sucede, todos hablarán sobre ello.";
			posrep2 = " No hay nada de interés. " + GetAddress_Form(NPChar) + " podría saber algo.";
			answ1 = RandPhraseSimple("Cuéntame sobre...", RandSwear() + "¡No sabes nada! Está bien, sobre otro tema...");
			answ2 = RandPhraseSimple("Tendrá que ser así, dime algo más...", "Sí, no fuiste de mucha ayuda, ¿tienes algo más que compartir conmigo?");
			answ3 = RandPhraseSimple("Dudo que tengas algo de interés que contarme.", "Será un placer, hablemos la próxima vez.");
			answ4 = "";
		}
		Dialog.Text = NPCStringReactionRepeat(srum,
											  srum + posrep1,
											  srum + posrep2,
											  RandPhraseSimple("Por desgracia, no tengo nada más que decirte, déjame pasar.", "Ya tuve suficiente con las preguntas, discúlpame, tengo asuntos que atender."), "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(answ1,
										   answ2,
										   answ3,
										   answ4,
										   npchar, Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("Gracias, debería irme.", "Adiós.");
		link.l2.go = "exit";
		break;

		/////////////////////////////////////////////////---слухи дворянок---////////////////////////////////////////////
	case "rumours_noblegirl":
		srum = SelectRumourEx("noblegirl", NPChar);
		
		//--> Украденное воспоминание
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		if (bOk1 || bOk2)
        {
			dialog.text = "Se rumorea en el puerto que Julie d'Armagnac, la sobrina del gobernador, se ha convertido en una mera sombra de lo que era. Antes radiante y llena de vida, ahora deambula por las calles con una tristeza inconfundible grabada en su rostro. Los habitantes del pueblo murmuran y se preguntan qué podría haberle sucedido, pero nadie conoce la verdad. ¿Quizás algún canalla le ha roto el corazón?"+GetSexPhrase(" ¿Fue usted, Capitán?","")+"";
			link.l1 = ""+GetSexPhrase("Lo dudo. ","")+"Gracias, debería irme.";
			link.l1.go = "exit";
			
			SetQuestHeader("UV");
			AddQuestRecord("UV", "1");
			pchar.questTemp.UV_Start = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("UV_Juli", "women_4", "woman", "woman", sti(pchar.rank), FRANCE, -1, false, "quest"));
			sld.name = StringFromKey("Neutral_6");
			sld.lastname = StringFromKey("Neutral_7");
			sld.City = "PortPax";
			ChangeCharacterAddressGroup(sld, "PortPax_town", "goto", "goto9");
			sld.dialog.filename = "Quest\MiniEvents\StolenMemory_dialog.c";
			sld.dialog.currentnode = "Juli";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_SetImmortal(sld, true);
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Украденное воспоминание
		
		if (RumourHasInformation(srum))
		{
			posrep1 = RandPhraseSimple(" Eso es todo...", " Puedes encontrarlo gracioso.");
			posrep2 = " Oye, capitán, ¿tienes noticias para nuestra colonia?";
			answ1 = RandPhraseSimple(RandSwear() + "Estás diciendo cosas interesantes, " + GetFullName(NPChar) + ".",
									 "Cuéntame sobre...");
			answ2 = RandPhraseSimple(RandSwear() + "Tendrá que ser así, dime algo más...", "Sí, no fuiste de mucha ayuda, ¿tienes algo más que compartir conmigo?");
			answ3 = RandPhraseSimple("Este tipo de cosas suceden todo el tiempo. Lo siento, pero no tengo nada especial que contarte. ", "Tengo mucha prisa, quizás la próxima vez.");
			answ4 = "";
		}
		else
		{
			posrep1 = " Es un lugar bastante aburrido, si algo sucede, todos hablarán sobre ello.";
			posrep2 = " No hay nada de interés. " + GetAddress_Form(NPChar) + " podría saber algo.";
			answ1 = RandPhraseSimple("Cuéntame sobre...", RandSwear() + "¡No sabes nada! Está bien, sobre otro tema...");
			answ2 = RandPhraseSimple("Tendrá que ser así, dime algo más...", "Sí, no fuiste de mucha ayuda, ¿tienes algo más que compartir conmigo?");
			answ3 = RandPhraseSimple("Dudo que tengas algo de interés que contarme.", "Será un placer, hablemos la próxima vez.");
			answ4 = "";
		}
		Dialog.Text = NPCStringReactionRepeat(srum,
											  srum + posrep1,
											  srum + posrep2,
											  RandPhraseSimple("Por desgracia, no tengo nada más que decirte, déjame pasar.", "Ya tuve suficiente con las preguntas, discúlpame, tengo asuntos que atender."), "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(answ1,
										   answ2,
										   answ3,
										   answ4,
										   npchar, Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("Gracias, debería irme.", "Adiós.");
		link.l2.go = "exit";
		break;

	///////////////////////////////////////////---слухи матросов---////////////////////////////////////////////
	case "rumours_sailor":
		NextDiag.CurrentNode = "rumours";

		//--> Грани справедливости
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		if (bOk1 || bOk2)
        {
			dialog.text = "Anteayer hubo un atrevido intento de asesinato contra el jefe de autoridad portuaria. El asesino lo esperaba a la salida de su oficina, pero logró pedir ayuda. Un mosquetero llegó a tiempo e hirió al atacante, pero el criminal logró escapar de la ciudad\nDicen que el jefe del puerto está ofreciendo una generosa recompensa por su cabeza. Hasta ahora, ningún valiente se ha presentado. ¿Sabes? Aunque ofreciera mil doblones, yo no aceptaría...";
			link.l1 = "Gracias, debería irme.";
			link.l1.go = "exit";
			
			SetQuestHeader("GS");
			AddQuestRecord("GS", "1");
			pchar.questTemp.GS_Start = true;
			pchar.questTemp.GS_Portman = true;
			AddLandQuestMark(characterFromId("Beliz_portman"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Грани справедливости
		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 2)
			srum = SelectRumourEx("sailor", NPChar);
		else
			srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
		if (RumourHasInformation(srum))
		{
			posrep1 = RandPhraseSimple(" Eso es todo...", " Puedes encontrarlo gracioso.");
			posrep2 = " Oye, capitán, ¿tienes noticias para nuestra colonia?";
			answ1 = RandPhraseSimple(RandSwear() + "Estás diciendo cosas interesantes, " + GetFullName(NPChar) + ".",
									 "Cuéntame sobre...");
			answ2 = RandPhraseSimple(RandSwear() + "Tendrá que ser así, dime algo más...", "Sí, no fuiste de mucha ayuda, ¿tienes algo más que compartir conmigo?");
			answ3 = RandPhraseSimple("Este tipo de cosas suceden todo el tiempo. Lo siento, pero no tengo nada especial que contarte. ", "Tengo mucha prisa, quizás la próxima vez.");
			answ4 = "";
		}
		else
		{
			posrep1 = " Es un lugar bastante aburrido, si algo sucede, todos hablarán sobre ello.";
			posrep2 = " No hay nada de interés. " + GetAddress_Form(NPChar) + " podría saber algo.";
			answ1 = RandPhraseSimple("Cuéntame sobre...", RandSwear() + "¡No sabes nada! Está bien, sobre otro tema...");
			answ2 = RandPhraseSimple("Tendrá que ser así, dime algo más...", "Sí, no fuiste de mucha ayuda, ¿tienes algo más que compartir conmigo?");
			answ3 = RandPhraseSimple("Dudo que tengas algo de interés que contarme.", "Será un placer, hablemos la próxima vez.");
			answ4 = "";
		}
		Dialog.Text = NPCStringReactionRepeat(srum,
											  srum + posrep1,
											  srum + posrep2,
											  RandPhraseSimple("Por desgracia, no tengo nada más que decirte, déjame pasar.", "Ya tuve suficiente con las preguntas, discúlpame, tengo asuntos que atender."), "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(answ1,
										   answ2,
										   answ3,
										   answ4,
										   npchar, Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("Gracias, debería irme.", "Adiós.");
		link.l2.go = "exit";
		break;
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Алкашня
	case "rumours_habitue":
		//-->работорговец
		if (pchar.questTemp.Slavetrader == "FindRatJamaica_H" && npchar.location == "FortOrange_tavern")
		{
			dialog.text = "(Cantando) Puse mi mano sobre su rodilla. ¡Yo Ho! ¡Yo Ho! Puse mi mano sobre su rodilla. ¡Yo Ho! ¡Yo Ho! Puse mi mano sobre su rodilla y me dijo: '¡Oye marinero, estás bromeando! Entra o sal y deja de joder' ¡Yo Ho! ¡Yo Ho! ¡Yo Ho! Hey, marinero, ¿cómo estás? ¿Cómo está el mar?";
			link.l1 = "¿Mar? La misma mierda de siempre, sal y olas. Cuéntame algo sobre mi amigo Gontier que alquiló una habitación no hace mucho tiempo.";
			link.l1.go = "Jamaica_ratH_1";
			break;
		}
		if (pchar.questTemp.Slavetrader == "EscapeSlaveVillemstad_H" && npchar.location == "Villemstad_tavern")
		{
			dialog.text = "(Cantando) ¡Quince hombres en el cofre de un muerto! Yo-ho-ho y una botella de ron. ¡La bebida y el diablo habían hecho el resto! ¡Yo-ho-ho y una botella de ron! ¡Sirve a este marinero! Es el primer día en la orilla y todavía estoy tratando de recomponerme";
			link.l1 = "¡Toma un trago, amigo! ¿Cómo está el mar?";
			link.l1.go = "EscapeSlave_Villemstad_H1";
			break;
		}
		//<--работорговец

		// Голландский Гамбит, против всех
		if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "LetterToLucasSent" && npchar.location == "Villemstad_tavern")
		{
			dialog.text = "Eh, el mar... ¡Ojalá estuviera en tus zapatos!";
			link.l1 = "No veo ningún problema, amigo. Únete a mi equipo en cualquier momento.";
			link.l1.go = "Lucas_Tavern";
			break;
		}
		// Голландский Гамбит

		//--> поиск дезертира
		if (CheckAttribute(pchar, "GenQuest.FindFugitive") && sti(NPChar.nation) == PIRATE && !CheckAttribute(npchar, "quest.fugitive"))
		{
			dialog.text = LinkRandPhrase("¡Bebe ron, vete como un valiente y encuentra miles de amigos! ¡Ja-ja!", "¡Después de una jarra de ron decente, incluso un carcelero parecerá encantador! ¡Ja-ja!", "El ron y la cerveza te llevarán al cielo, ¡así que bebe, maldición! ¡Ha!");
			link.l1 = "Claro, vamos a compartir un trago... Dime, buen hombre, ¿conoces a " + pchar.GenQuest.FindFugitive.Name + "? Era mi compañero de escuadrón y algunos muchachos me dijeron que movió su trasero a este lugar...";
			link.l1.go = "FindFugitiveHb";
			break;
		}
		//<-- поиск дезертира

		//--> карибские нравы
		if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy" && npchar.location == "Portobello_tavern")
		{
			dialog.text = "¿Noticias? ¡Hip! ¿No lo has oído? Nuestros soldados capturaron a un espía francés. ¡Ese furtivo pretendía actuar como un comerciante, pero *hip* nuestro comandante es un duro bastardo!";
			link.l1 = "¡Si tú lo dices! ¿Y qué trató de olfatear esa comadreja?";
			link.l1.go = "trial_spy";
			break;
		}
		if (CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskAlcash") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
		{
			dialog.text = "Eh, " + GetAddress_Form(pchar) + " en qué mundo vivimos... ¡Cabrones de mierda todos!";
			link.l1 = "¿Qué quieres decir, colega?";
			link.l1.go = "Alcogol_GenQuest_Church_2_1";
			break;
		}
		//<-- карибские нравы

		//--> Sinistra Длинные тени старых грехов
		if (CheckAttribute(pchar, "questTemp.DTSG_NightIskat") && npchar.city == "SentJons")
		{
			dialog.text = "¡¿Lo has oído?! ¡No puedo creerlo! ¡El famoso Capitán Fleetwood fue brutalmente asesinado en Londres! Perseguía la gloria, lo tenía todo y sólo encontró la muerte... Si se hubiera quedado aquí, estaría más seguro. A veces es mejor apreciar lo que se tiene en vez de perseguir el dinero o el rango, ¡recuerde mis palabras, señor!";
			link.l1 = "Amigo, sabes dónde vive cada uno en la colonia, ¿verdad?";
			link.l1.go = "DTSG_NightIskat";
			break;
		}
		//<-- Длинные тени старых грехов

		//--> Rebbebion, квест "Путеводная звезда"
		if (CheckAttribute(pchar, "questTemp.Beliz.AskForLatterAndSotta") && !CheckAttribute(npchar, "questTemp.Sotta") && !CheckAttribute(npchar, "questTemp.Lutter") && npchar.city == "Beliz")
		{
			link.l1 = "El héroe del día, el capitán Edgardo Sotta. ¿Qué se dice de él? ¿Y qué piensa usted? Tenía muchas ganas de conocerlo.";
			link.l1.go = "Sotta1";
			link.l2 = "Amigo, ¿por qué bebes solo? Todo el mundo se está reuniendo para ver el Windbag que Matt está colgando ahora mismo.";
			link.l2.go = "Lutter1";
			break;
		}

		if (CheckAttribute(pchar, "questTemp.PZ.TortugaCitizensAsk") && !CheckAttribute(pchar, "questTemp.PZ.TortugaHabitueBlock") && npchar.city == "Tortuga")
		{
			link.l1 = "Escucha, amigo, he estado tratando de encontrar a alguien llamado Joep van der Vink. Necesito darle un mensaje. ¿Sabes cómo es o algo sobre él?";
			link.l1.go = "Sepp1";
			break;
		}
		//<-- квест "Путеводная звезда"
		
		//--> Тёмные воды исцеления
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		if (bOk1 || bOk2)
        {
			dialog.text = "¿Lo habéis oído? Dicen que la hija de Thomas Morrison lleva ya medio año postrada en la cama. Los médicos están completamente impotentes ante su enfermedad. La única que podría ayudarla es una gitana famosa por sus brebajes, capaces de sanar incluso a los más enfermos. Pero se negó rotundamente a hacer nada por la pobre muchacha.";
			link.l1 = RandPhraseSimple(RandSwear() + "Esto merece otra taza...",
								   "Bien, bebamos una vez más.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Gracias, debería irme.",
									   "Eh, vaya ron. Bien, debo irme, que te diviertas.");
			link.l2.go = "exit_sit";
			
			SetQuestHeader("DWH");
			AddQuestRecord("DWH", "1");
			pchar.questTemp.DWH_Start = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("DWH_gypsy", "gipsy_2", "woman", "towngirl", 10, PIRATE, -1, true, "citizen"));
			ChangeCharacterAddressGroup(sld, "SentJons_town", "goto", "goto1");
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "dwh_gypsy_0";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_SetLoginTime(sld, 07.00, 21.99);
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Тёмные воды исцеления
		
		//--> Грани справедливости
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		if (bOk1 || bOk2)
        {
			dialog.text = "Anteayer hubo un atrevido intento de asesinato contra el jefe de autoridad portuaria. El asesino lo esperaba a la salida de su oficina, pero logró pedir ayuda. Un mosquetero llegó a tiempo e hirió al atacante, pero el criminal logró escapar de la ciudad\nDicen que el jefe del puerto está ofreciendo una generosa recompensa por su cabeza. Hasta ahora, ningún valiente se ha presentado. ¿Sabes? Aunque ofreciera mil doblones, yo no aceptaría...";
			link.l1 = RandPhraseSimple(RandSwear() + "Esto merece otra taza...",
								   "Bien, bebamos una vez más.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Gracias, debería irme.",
									   "Eh, vaya ron. Bien, debo irme, que te diviertas.");
			link.l2.go = "exit_sit";
			
			SetQuestHeader("GS");
			AddQuestRecord("GS", "1");
			pchar.questTemp.GS_Start = true;
			pchar.questTemp.GS_Portman = true;
			AddLandQuestMark(characterFromId("Beliz_portman"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Грани справедливости
		
		//--> Торговля по закону
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		if (bOk1 || bOk2)
        {
			dialog.text = "¿Habéis oído las nuevas?! ¡Es una maldita vergüenza! Ni una gota de ron o vino queda en la taberna - ¿cómo ha de encontrar uno alivio en este calor infernal? El tabernero nos lleva alimentando con promesas vacías toda una semana de que la bebida volverá a fluir, ¡pero no ha habido nada! ¿Se espera que sequemos nuestras gargantas hasta el Día del Juicio?";
			link.l1 = RandPhraseSimple(RandSwear() + "Esto merece otra taza...",
								   "Bien, bebamos una vez más.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Gracias, debería irme.",
									   "Eh, vaya ron. Bien, debo irme, que te diviertas.");
			link.l2.go = "exit_sit";
			
			SetQuestHeader("TPZ");
			AddQuestRecord("TPZ", "1");
			pchar.questTemp.TPZ_Start = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
			
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Торговля по закону
		
		//--> Старые счёты
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.OS_Start") && npchar.city == "PuertoPrincipe";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.OS_Start") && npchar.city == "PuertoPrincipe";
		if (bOk1 || bOk2)
        {
			dialog.text = "¡Corre la voz por los muelles que nuestro tabernero está en apuros! ¡Alguien le ha robado su ginebra! No solo una botella, sino un barril entero del producto - ¡de ese tipo que no encontrarás en ninguna otra parte de estas islas! Traído desde Europa, dicen. El viejo zorro no dirá para quién lo guardaba, pero una cosa es segura: ¡si ese barril no aparece pronto, el pobre desgraciado las pagará muy caras!";
			link.l1 = RandPhraseSimple(RandSwear() + "Esto merece otra taza...",
								   "Bien, bebamos una vez más.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Gracias, debería irme.",
									   "Eh, vaya ron. Bien, debo irme, que te diviertas.");
			link.l2.go = "exit_sit";
			
			SetQuestHeader("OS");
			AddQuestRecord("OS", "1");
			pchar.questTemp.OS_Start = true;
			pchar.questTemp.OS_Tavern_1 = true;
			AddLandQuestMark(characterFromId("PuertoPrincipe_tavernkeeper"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Старые счёты
		
		//--> Украденное воспоминание
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		if (bOk1 || bOk2)
        {
			dialog.text = "Se rumorea en el puerto que Julie d'Armagnac, la sobrina del gobernador, se ha convertido en una mera sombra de lo que era. Antes radiante y llena de vida, ahora deambula por las calles con una tristeza inconfundible grabada en su rostro. Los habitantes del pueblo murmuran y se preguntan qué podría haberle sucedido, pero nadie conoce la verdad. ¿Quizás algún canalla le ha roto el corazón?"+GetSexPhrase(" ¿Fue usted, Capitán?","")+"";
			link.l1 = RandPhraseSimple(RandSwear() + "Esto merece otra taza...",
								   "Bien, bebamos una vez más.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Gracias, debería irme.",
									   "Eh, vaya ron. Bien, debo irme, que te diviertas.");
			link.l2.go = "exit_sit";
			
			SetQuestHeader("UV");
			AddQuestRecord("UV", "1");
			pchar.questTemp.UV_Start = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("UV_Juli", "women_4", "woman", "woman", sti(pchar.rank), FRANCE, -1, false, "quest"));
			sld.name = StringFromKey("Neutral_6");
			sld.lastname = StringFromKey("Neutral_7");
			sld.City = "PortPax";
			ChangeCharacterAddressGroup(sld, "PortPax_town", "goto", "goto9");
			sld.dialog.filename = "Quest\MiniEvents\StolenMemory_dialog.c";
			sld.dialog.currentnode = "Juli";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_SetImmortal(sld, true);
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Украденное воспоминание
		
		//--> В плену великого улова andre39966
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		if (bOk1 || bOk2)
        {
			dialog.text = "Se rumorea que el pescador Pierre Carno ha desaparecido sin dejar rastro. Hace dos albas, se hizo a la mar y desde entonces no hay señal de él. Su esposa, Lea, está desconsolada. Día y noche mantiene su vigilia en el muelle, con la mirada fija en las aguas interminables, suplicando por un atisbo de la vela de su amado.";
			link.l1 = RandPhraseSimple(RandSwear() + "Esto merece otra taza...",
								   "Bien, bebamos una vez más.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Gracias, debería irme.",
									   "Eh, vaya ron. Bien, debo irme, que te diviertas.");
			link.l2.go = "exit_sit";
			
			SetQuestHeader("VPVL");
			AddQuestRecord("VPVL", "1");
			pchar.questTemp.VPVL_Start = true;
			AddDialogExitQuest("VPVL_Gegerate_Lea");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- В плену великого улова
		//--> Тайна Бетси Прайс
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		if (bOk1 || bOk2)
        {
			dialog.text = "Capitán, ¿ha oído? Hay una nueva camarera trabajando en nuestra taberna. Dicen que es toda una belleza. Hombres de todas partes han estado acudiendo solo para verla. Pero hace tres días no se presentó a trabajar, lo que disgustó mucho al tabernero, quien había estado obteniendo enormes ganancias desde su llegada. Dicen que incluso está dispuesto a pagar a quien pueda encontrarla.​";
			link.l1 = RandPhraseSimple(RandSwear() + "Esto merece otra taza...",
								   "Bien, bebamos una vez más.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Gracias, debería irme.",
									   "Eh, vaya ron. Bien, debo irme, que te diviertas.");
			link.l2.go = "exit_sit";
			
			SetQuestHeader("TBP");
			AddQuestRecord("TBP", "1");
			pchar.questTemp.TBP_Start = true;
			pchar.questTemp.TBP_Tavern = true;
			AddLandQuestMark(CharacterFromID("Villemstad_tavernkeeper"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Тайна Бетси Прайс
		
		Dialog.Text = LinkRandPhrase("¡Buen... hic! ", "¡Ah, buen ron! ", "¡Buen... ") + SelectRumourEx("habitue", NPChar);
		link.l1 = RandPhraseSimple(RandSwear() + "Esto merece otra taza...",
								   "Bien, bebamos una vez más.");
		link.l1.go = "sit_3";
		link.l2 = RandPhraseSimple("Gracias, debería irme.",
								   "Eh, vaya ron. Bien, debo irme, que te diviertas.");
		link.l2.go = "exit_sit";
		break;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case "rumours_trader":
		if (!CheckAttribute(NPChar, "quest.repeat.rumours_trader") || NPChar.quest.repeat.rumours_trader != 3)
			strum = SelectRumourEx("trader", NPChar);
		else
			strum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
		Dialog.Text = NPCStringReactionRepeat(strum, strum + " Yup, no hay nada más que decir.",
											  strum + " Ahora debería ir directo al asunto.", RandPhraseSimple("¡Ya te dije que no tengo tiempo para charlar!", "¡Soy un hombre ocupado, no tengo tiempo para hablar de chismes!"), "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(pcharrepphrase(RandSwear() + "¡Interesante! Pero vayamos al grano.", "Muchas gracias, pero hay una cosa más."), pcharrepphrase("" + GetSexPhrase("¡Maldita sea", "¡Interesante") + "! Eres un conversador, pero tengo una pregunta más.", "No perdamos más tiempo y hablemos de negocios."),
										   pcharrepphrase(RandSwear() + " Un tema más y me iré.", "Tienes razón, el tiempo es dinero."), pcharrepphrase("Siempre pensando en tu propio beneficio. Está bien, no te vuelvas loco.", "Perdóname, hablemos de negocios."), npchar, Dialog.CurrentNode);
		link.l1.go = "business";
		link.l2 = HeroStringReactionRepeat(NPCharRepPhrase(npchar, pcharrepphrase("Adiós, viejo borracho.", "Adiós, " + GetAddress_FormToNPC(NPChar) + " " + GetFullName(npchar) + "."), pcharrepphrase("¡Rayos! No te vayas lejos, volveré en breve.", "¡Es un placer verte, " + GetAddress_FormToNPC(NPChar) + " " + GetFullName(npchar) + "! ¡Adiós!")), NPCharRepPhrase(npchar, pcharrepphrase("¡Suelten amarras!", "¡Adiós!"), pcharrepphrase("¡Oye! ¿Qué estás escondiendo ah? ¿Ron? ¿¡No!?! Tendrá que ser así, tomaré algo de beber.", "Lo siento, tengo un negocio importante en la ciudad.")), NPCharRepPhrase(npchar, pcharrepphrase("¡Hey! ¡Nos vemos!", "¡Debería irme, adiós, " + GetAddress_FormToNPC(NPChar) + " " + GetFullName(npchar) + "!"), pcharrepphrase("¡No te atrevas a discutir conmigo! ¡No deseo esto!", "¡Creo que debería revisar mi barco, nos vemos, " + GetAddress_FormToNPC(NPChar) + " " + GetFullName(npchar) + "!")), NPCharRepPhrase(npchar, pcharrepphrase("¿Qué te pasa, amigo? ¡Soy " + GetFullName(pchar) + "! Duerme una siesta, hablaremos más tarde.", "Temo que tu hígado te matará antes de volver aquí."), pcharrepphrase("¡Cuenta tu plata, perro astuto! Te veré más tarde.", "¡Es un placer verte, " + GetAddress_FormToNPC(NPChar) + " " + GetFullName(npchar) + "!")), npchar, Dialog.CurrentNode);
		link.l2.go = "Exit";
		break;
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case "rumours_capitan":
		Dialog.Text = SelectRumourEx("capitan", NPChar);
		Link.l1 = RandPhraseSimple(RandSwear() + "¡Qué interesante! Hay una cosa más que quería preguntar...",
								   "Una pregunta más.");
		Link.l1.go = "quests";
		Link.l2 = RandPhraseSimple("Gracias, debería irme.",
								   "Adiós.");
		Link.l2.go = "exit";
		NextDiag.TempNode = "quests";
		NPChar.talk_date = lastspeakdate();
		break;

	case "rumours_landcaptain":
		Dialog.Text = SelectRumourEx("landcaptain", NPChar);
		Link.l1 = RandPhraseSimple(RandSwear() + "¡Qué interesante! Hay una cosa más que quería preguntar...",
								   "Una pregunta más.");
		Link.l1.go = "question";
		Link.l2 = RandPhraseSimple("Gracias, debería irme.",
								   "Adiós.");
		Link.l2.go = "exit";
		NextDiag.TempNode = "question";
		NPChar.talk_date = lastspeakdate();
		break;
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case "rumours_tavern": // homo 03/08/06
		if (startHeroType == 4)
		{
			Dialog.Text = NPCStringReactionRepeat(LinkRandPhrase("Ya conoces el precio. La información es como una habitación, una comida o una bebida: cuesta. Son mil pesos.",
																 "Ya conoces el precio. La información es como una habitación, comida o bebida: cuesta. Son mil pesos.",
																 "Ya conoces el precio. La información es como una habitación, una comida o una bebida: cuesta. Son mil pesos."),
												  "Nada más que añadir. Ahora, discúlpenme, debo irme.",
												  "", "", "block", 1, npchar, Dialog.CurrentNode);

			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("En realidad, ¿por qué pregunto? Se lo puedo preguntar a cualquier otro. Perdona que te moleste.",
																"En realidad, ¿por qué pregunto? Se lo puedo preguntar a cualquier otro. Perdona que te moleste."),
											   "", "", "", npchar, Dialog.CurrentNode);
			link.l1.go = HeroStringReactionRepeat("rumours_tavern_no", "first time", "first time", "first time", npchar, Dialog.CurrentNode); //"rumours_tavern_no";
			NextDiag.CurrentNode = NextDiag.TempNode;
			if (makeint(pchar.money) >= 1000)
			{
				link.l2 = HeroStringReactionRepeat(RandPhraseSimple("Lo sé, por supuesto. Aquí está mi pago.", "Lo sé, por supuesto. Aquí está mi pago."),
												   "", "", "", npchar, Dialog.CurrentNode);
				link.l2.go = HeroStringReactionRepeat("rumours_tavern_yes", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
			}
			else
			{
				link.l2 = HeroStringReactionRepeat("No tengo esa cantidad de dinero.", "", "", "", npchar, Dialog.CurrentNode);
				link.l2.go = HeroStringReactionRepeat("rumours_tavern_no", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
			}
		}
		else
		{
			Dialog.Text = NPCStringReactionRepeat(LinkRandPhrase("La información cuesta dinero. 1000 pesos y te diré todo lo que sé.",
																 "Algo le pasa a mi memoria, 1000 trozos de ocho podrían ayudarme a recordar algo.",
																 "Estoy ansioso por compartir con la información. Pero le costará 1000 piezas de ocho. Sin regateo."),
												  "No tengo nada más que agregar. Discúlpame, debería irme.",
												  "", "", "block", 1, npchar, Dialog.CurrentNode);

			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(RandSwear() + "No voy a pagar por una cháchara sin valor.",
																"Pensaré en mejores formas de gastar este dinero."),
											   "Cambiemos de tema.", "Cambiemos de tema.", "Cambiemos de tema.", npchar, Dialog.CurrentNode);
			link.l1.go = HeroStringReactionRepeat("rumours_tavern_no", "first time", "first time", "first time", npchar, Dialog.CurrentNode); //"rumours_tavern_no";
			NextDiag.CurrentNode = NextDiag.TempNode;
			if (makeint(pchar.money) >= 1000)
			{
				link.l2 = HeroStringReactionRepeat(RandPhraseSimple("Los tendrás si aprendo algo digno de ti.", "Pagaré si me das algo de valor."),
												   "", "", "", npchar, Dialog.CurrentNode);
				link.l2.go = HeroStringReactionRepeat("rumours_tavern_yes", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
			}
			else
			{
				link.l2 = HeroStringReactionRepeat("No tengo esa suma.", "", "", "", npchar, Dialog.CurrentNode);
				link.l2.go = HeroStringReactionRepeat("rumours_tavern_no", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
			}
		}

		break;

	case "rumours_tavern_yes":
		if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation"))
		{
			bool bOk = (pchar.questTemp.Saga.BarbTemptation == "silk") || (pchar.questTemp.Saga.BarbTemptation == "give_silk");
			if (bOk && npchar.location == "Marigo_tavern" && !CheckAttribute(npchar, "quest.barbtemptation"))
			{
				AddMoneyToCharacter(pchar, -1000);
				Dialog.Text = "Nuestra patrulla ha destruido recientemente el bergantín del contrabandista francés Morel que está en una mazmorra y se enfrenta a una sentencia de muerte. Todavía están intentando encontrar la mercancía, ese bastardo morirá sin hablar.";
				link.l1 = "Interesante... Está bien, toma el dinero. ¿Me tienes que decir algo más?";
				link.l1.go = "rumours_tavern";
				Saga_CreateMorelle(); // ставим Мореля
				npchar.quest.barbtemptation = "true";
				pchar.questTemp.Saga.BarbTemptation.Prison = "true";
				break;
			}
		}
		// Addon-2016 Jason ФМК-Гваделупа
		if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "headhunter_portobello" && npchar.location == "portobello_tavern")
		{
			DelLandQuestMark(npchar);
			AddMoneyToCharacter(pchar, -1000);
			Dialog.Text = "Se ha celebrado una gran fiesta en el palacio del gobernador, Don Carlos de Milyar, el amigo de su excelencia ha regresado. Fue capturado en una batalla naval, pero logró escapar con la ayuda de un teniente francés. Don Carlos además de inteligente también es un hombre muy generoso. El teniente Jean Deno, ahora es el capitán del 'Sario'. Por lo que he oído, también fue premiado con una pequeña plantación. ¡Ahora ese comer ranas se llama Juan! ¡Qué historia!";
			link.l1 = "Intrigante... Está bien, el dinero es tuyo, toma. ¿Tienes algo más que decir?";
			link.l1.go = "rumours_tavern";
			pchar.questTemp.FMQG = "headhunter_juan";
			AddQuestRecord("FMQ_Guadeloupe", "10");
			pchar.quest.FMQG_Juanship.win_condition.l1 = "location";
			pchar.quest.FMQG_Juanship.win_condition.l1.location = "PortoBello";
			pchar.quest.FMQG_Juanship.function = "FMQG_CreateJuanship";
			break;
		}
		// Addon-2016 Jason ФМК-Сент-Кристофер
		if (CheckAttribute(pchar, "questTemp.FMQN") && pchar.questTemp.FMQN == "town" && npchar.location == "Marigo_tavern")
		{
			AddMoneyToCharacter(pchar, -1000);
			Dialog.Text = "Nuestro comandante ha enviado fuerzas adicionales para patrullar la jungla además de la guardia de la ciudad. Hay rumores de que los ingleses planean infiltrarse en Philipsburg para liberar a los oficiales capturados.";
			link.l1 = "¿No me digas? ¿Realmente tienen agallas para intentar tal hazaña? ¿Y de qué oficiales me estás hablando?";
			link.l1.go = "FMQN_r";
			break;
		}
		// Addon 2016-1 Jason пиратская линейка
		if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_3" && npchar.location == "Havana_tavern")
		{
			AddMoneyToCharacter(pchar, -1000);
			Dialog.Text = "El otro día toda la ciudad se soliviantó. Un oficial de un lugre militar se emborrachó en mi taberna y casi viola a una chica casada y luego intentó golpear al marido que defendió a su esposa, amenazándolo con la espada. ¡Todo esto pasó frente a la guardia de la ciudad! Como dicen, el perro no come perro. Los soldados simplemente se dieron la vuelta mientras ese bastardo estaba furioso\nPero el sinvergüenza fue desarmado por, quién lo habría pensado, algunos marineros del barco de un comerciante. Casi lo inmovilizan, aunque ese bastardo se escapó y se escondió en su barco. El comandante y el alcalde intentaron esconderlo bajo la alfombra, pero el hombre agraviado era un ciudadano respetado y recurrió a Su Excelencia don Diego de Toledo, e hizo ruido entre la burguesía de la ciudad.\nEmitieron el arresto del oficial y sugirieron a su capitán que abandonara apresuradamente el puerto para que se llevara a ese sinvergüenza a un lugar diferente. Sin embargo, el capitán del lugre, Esberdo Cabanas, es un hombre de honor. Una vez que se enteró de lo que había hecho el oficial, inmediatamente arrestó al sinvergüenza y lo envió de vuelta al muelle. Ese bastardo se está pudriendo en la cárcel con futuro previsible, donde pertenece si me preguntas.";
			link.l1 = "Espera, ¿dijiste 'capitán Esberdo Cabanas'? ¿Eh... es una historia emocionante!.. De acuerdo, te has ganado el dinero, aquí tienes. ¿Algo más que puedas decirme?";
			link.l1.go = "rumours_tavern";
			Mtraxx_CreateOfficer(); // ставим офицера-негодяя
			pchar.questTemp.Mtraxx = "jewelry_4";
			pchar.GenQuest.PrisonQuestLock = "true";
			AddQuestRecord("Roger_1", "7");
			DelLandQuestMark(characterFromId("Havana_tavernkeeper"));
			AddLandQuestMarkToPhantom("havana_prison", "havanaJailOff");
			break;
		}
		// Jason Исла Мона
		if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "rumours" && rand(2) == 1)
		{
			AddMoneyToCharacter(pchar, -1000);
			Dialog.Text = "Se dice que algunos criminales desembarcaron en una de las islas desiertas. Monstruos tan feroces que ni el verdugo ni los santos padres se meterían con ellos. ¡¿Pero por qué siempre nos los traen a nosotros?!";
			link.l1 = "Hmmm.... Eso es interesante. Tal vez deberíamos encontrarlos y meterlos en la tripulación, siempre necesito chicos desesperados.... ¿Por qué estás pálido? Estoy bromeando, estoy bromeando. Te has ganado tu dinero. Aquí tienes. ¿Sabes algo más interesante?";
			link.l1.go = "rumours_tavern";
			IslaMona_TerksCreateHimenes();
			break;
		}
		string RumText = SelectRumourEx("tavern", NPChar); // fix

		if (!RumourHasInformation(RumText))
		{
			Dialog.Text = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
			if (startHeroType == 4)
			{
				link.l1 = "Resulta que no sabes nada después de todo. No esperaba que me engañaras así. No muy inteligente. Bueno, adiós".;
			}
			else
			{
				link.l1 = RandPhraseSimple("Mierda sin valor. ¡No te voy a pagar ni un solo peso! Adios.", "Tu información no cuesta nada, así que no recibirás nada.");
			}
			link.l1.go = "Exit";
			NextDiag.CurrentNode = NextDiag.TempNode;
		}
		else
		{
			AddMoneyToCharacter(pchar, -1000);
			Dialog.Text = RumText;
			if (startHeroType == 4)
			{
				link.l1 = "¿De verdad? Interesante, gracias. Bueno, debo irme, hasta la próxima.";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = RandPhraseSimple("Gracias, toma el dinero. ¿Algo más que contar?", "Bien, toma el dinero. ¿Algo más que contar?");
				link.l1.go = "rumours_tavern";
			}
			NextDiag.CurrentNode = NextDiag.TempNode;
		}
		break;

	case "rumours_tavern_no":
		if (startHeroType == 4)
		{
			Dialog.Text = "Podrías haber ayudado con alguna moneda. A diferencia de ti, Helen, no tengo al Barón de los Hermanos apoyándome.";
			link.l1 = "Tienes todo un establecimiento. Y yo llegué donde estoy por mi cuenta. Bueno, aparte de la nave, los cañones, la tripulación, y los suministros que el Barón me consiguió. Está bien, no importa.";
			link.l1.go = "exit";
			NextDiag.CurrentNode = NextDiag.TempNode;
		}
		else
		{
			Dialog.Text = "Entiéndeme bien, necesito alimentar a mi familia.";
			link.l1 = "Cambiemos de tema.";
			link.l1.go = "first time";
			NextDiag.CurrentNode = NextDiag.TempNode;
			link.l2 = LinkRandPhrase("Gracias, debería irme.",
									 "Adiós.", "Adiós.");
			link.l2.go = "Exit";
		}
		break;
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case "rumours_poor":
		if (!CheckAttribute(NPChar, "quest.repeat.rumours_poor") || NPChar.quest.repeat.rumours_poor <= 1)
		{
			Dialog.Text = SelectRumourEx("poor", NPChar);
			Link.l1 = RandPhraseSimple(RandSwear() + "Interesante, una pregunta más...",
									   "Hm, deja que te pregunte algo más...");
			Link.l1.go = "rumours_poor_2";
			Link.l2 = RandPhraseSimple("Bueno, adiós.",
									   "Nos vemos, colega.");
			Link.l2.go = "exit";
			NPChar.quest.repeat.rumours_poor = sti(NPChar.quest.repeat.rumours_poor) + 1;
		}
		else
		{
			Dialog.Text = RandPhraseSimple("Te dije todo lo que sé.",
										   "No tengo nada más que compartir, lo siento...");
			Link.l1 = RandPhraseSimple("Ya veo, adiós.",
									   "Adiós, amigo...");
			Link.l1.go = "exit";
		}
		NPChar.talk_date = lastspeakdate();
		break;
	case "rumours_poor_2":
		if (NPChar.quest.repeat.rumours_poor <= 1)
		{
			Dialog.Text = SelectRumourEx("poor", NPChar);
			Link.l1 = RandPhraseSimple(RandSwear() + "Interesante, una pregunta más...",
									   "Hm, deja que te pregunte algo más...");
			Link.l1.go = "rumours_poor";
			Link.l2 = RandPhraseSimple("Bueno, adiós.",
									   "Adiós, amigo.");
			Link.l2.go = "exit";
			NPChar.quest.repeat.rumours_poor = sti(NPChar.quest.repeat.rumours_poor) + 1;
		}
		else
		{
			Dialog.Text = RandPhraseSimple("Te dije todo lo que sé.",
										   "No tengo nada más que compartir, lo siento...");
			Link.l1 = RandPhraseSimple("Ya veo. Adiós.",
									   "Adiós, colega...");
			Link.l1.go = "exit";
		}
		NPChar.talk_date = lastspeakdate();
		break;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case "rumours_LSC":
		if (CheckNPCQuestDate(NPChar, "quest.repeat.rumours"))
		{
			Dialog.Text = SelectRumourExSpecial("LSC", NPChar);
			Link.l1 = RandPhraseSimple("Entendido...",
									   "Ya veo...");
			Link.l1.go = "exit";
			SetNPCQuestDate(NPChar, "quest.repeat.rumours");
		}
		else
		{
			Dialog.Text = NPCharSexPhrase(npchar, RandPhraseSimple("Te dije todo lo que sé.", "Te dije todo lo que sé, lo siento..."),
										  RandPhraseSimple("Te dije todo lo que sé.", "Te dije todo lo que sé, lo siento..."));
			Link.l1 = RandPhraseSimple("Ya veo. Adiós.", "Adiós.");
			Link.l1.go = "exit";
		}
		break;

		// Jason -------------слухи смотрителей маяков, идентичны таверне, но бесплатны, по 1 шт за день--------------------
	case "rumours_lighthouse":
		Dialog.Text = NPCStringReactionRepeat(RandPhraseSimple("¡Eh, capitán! Siempre está bien conversar contigo, vivir solo es bastante aburrido a veces...", "Vivo solo y me visitan en contadas ocasiones, siempre estoy de humor para hablar."), "¿Te apetece una pequeña charla, capitán? Bueno, podría tener algo más que decir...", "Trae una botella de ron la próxima vez que me visites...", "Por desgracia, te dije todo lo que sé.", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Luego compartiré tu información, me gusta hablar con la gente como sabes...", "¡Dime! ¿Sabes lo que dicen sobre el valor de la información?"), "¿Cómo que?", "¡Por todos los medios! ¿Tienes algo más para compartir?", "Está bien, tuvimos una agradable conversación de todas formas.", npchar, Dialog.CurrentNode);
		link.l1.go = HeroStringReactionRepeat("rumours_lighthouse_yes", "rumours_lighthouse_void", "rumours_lighthouse_void", "exit", npchar, Dialog.CurrentNode);
		break;

	case "rumours_lighthouse_yes":
		RumText = SelectRumourEx("tavern", NPChar);
		if (!RumourHasInformation(RumText))
		{
			Dialog.Text = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)];
			link.l1 = RandPhraseSimple("¡Gracias! ¿Algo más?", "¡Es muy interesante! ¿Algo más?");

			link.l1.go = "rumours_lighthouse";
			link.l2 = RandPhraseSimple("¡Muchas gracias! Fue bastante entretenido...", "¡Gracias por decírmelo!");
			link.l2.go = "exit";
			NextDiag.CurrentNode = NextDiag.TempNode;
		}
		else
		{
			Dialog.Text = RumText;
			link.l1 = RandPhraseSimple("¡Gracias! ¿Algo más?", "¡Es muy interesante! ¿Algo más?");
			link.l1.go = "rumours_lighthouse";
			link.l2 = RandPhraseSimple("¡Muchas gracias! Fue bastante entretenido...", "¡Gracias por decírmelo!");
			link.l2.go = "exit";
			NextDiag.CurrentNode = NextDiag.TempNode;
		}
		break;

	case "rumours_lighthouse_void":
		Dialog.Text = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)];
		link.l1 = RandPhraseSimple("¡Gracias! ¿Algo más?", "¡Es muy interesante! ¿Algo más?");

		link.l1.go = "rumours_lighthouse";
		link.l2 = RandPhraseSimple("¡Muchas gracias! Fue bastante entretenido...", "¡Gracias por decírmelo!");
		link.l2.go = "exit";
		NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		// Jason ------------------------------------почтовый генератор 2 уровня-------------------------------------------
	case "Postcureer_LevelUp_ForAll":
		// начинаем проверять
		if (!CheckCharacterItem(pchar, pchar.questTemp.WPU.Current.Item))
		{
			dialog.text = "Pero, ¿dónde está el paquete? ¿No lo tienes?";
			link.l1 = "Bueno... se suponía que debía entregarlo. Pero... para ser completamente honesto, me lo han arrebatado. No pude defenderme y se lo tuve que dar. ";
			link.l1.go = "Postcureer_LevelUp_complete_fail";
			break;
		}

		if (sti(pchar.questTemp.WPU.Postcureer.AgentChance) == 4) // раскрыли обман
		{
			dialog.text = "Hm. ¡Disculpa, el paquete ya ha sido abierto! Tan claro como el cristal, han vuelto a poner el lacre...";
			link.l1 = "" + GetAddress_FormToNPC(NPChar) + ", es el paquete que me dieron en la oficina portuaria de " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Postcureer.StartCity + "Gen") + ". No veo porque...";
			link.l1.go = "Postcureer_LevelUp_complete_Agentfail";
			break;
		}

		if (pchar.questTemp.WPU.Postcureer == "late") // опоздали
		{
			int iTime = makeint(GetQuestPastDayParam("questTemp.Postcureer.Late")) + 1;
			pchar.questTemp.WPU.Postcureer.Money = makeint(sti(pchar.questTemp.WPU.Postcureer.Money) / (sti(iTime) + 1)); // сильно снижаем оплату
			dialog.text = "Te estaba esperando. ¡Pero llegas " + FindRussianDaysString(iTime) + " tarde! La información que traes me será menos útil... Todavía tiene algo de valor, así que te pagaré " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)) + ". Por favor, toma el dinero y adiós.";
			link.l1 = "Supongo que gracias.";
			link.l1.go = "Postcureer_LevelUp_complete";
			pchar.quest.PostcureerTime_FullOver.over = "yes";									  // снять второй таймер
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count) - 1; // опоздавший рейс не засчитываем
			AddQuestRecord("Postcureer", "8");
			AddQuestUserData("Postcureer", "sDay", FindRussianDaysString(iTime));
			AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)));
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("", ""));
			break;
		}

		if (pchar.questTemp.WPU.Postcureer == "lost") // опоздали совсем
		{
			dialog.text = "¡Así que eres tú! Te he estado esperando bastante tiempo, incluso tomé medidas para recuperar el paquete. Dámelo, gracias a tu tardanza ya no lo necesito, pero me gustaría guardarlo.\nComo entenderás, no puedo pagarte nada, pero me aseguraré de que tu buen nombre se restaure.";
			link.l1 = "Supongo que se lo tengo que agradecer. Lamento el retraso, realmente lo siento. Adiós.";
			link.l1.go = "Postcureer_LevelUp_complete_bad";
			break;
		}
		dialog.text = "Te estaba esperando. Llegas justo a tiempo, daré un buen uso a la información que me traes. Por favor, acepta estos " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)) + " por tu trabajo. Gracias por tu tiempo.";
		link.l1 = "¡De nada, adiós!";
		link.l1.go = "Postcureer_LevelUp_complete";
		pchar.quest.PostcureerTime_Over.over = "yes"; // снять таймер
		AddQuestRecord("Postcureer", "10");
		break;

	case "Postcureer_LevelUp_complete":
		RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
		AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Postcureer.Money));
		CloseQuestHeader("Postcureer");
		DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
		DeleteAttribute(pchar, "questTemp.WPU.Current");
		DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
		pchar.questTemp.WPU.Postcureer = "complete";
		AddCharacterExpToSkill(pchar, "Sailing", 120);	  // навигация
		AddCharacterExpToSkill(pchar, "Sneak", 120);	  // скрытность
		AddCharacterExpToSkill(pchar, "Leadership", 150); // авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 150);	  // везение
		ChangeCharacterComplexReputation(pchar, "nobility", 2);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), 2);
		Group_DeleteGroup("Fraht_Attack");
		DialogExit();
		break;

	case "Postcureer_LevelUp_complete_bad":
		RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
		AddQuestRecord("Postcureer", "9");
		AddQuestUserData("Postcureer", "sSex", GetSexPhrase("", ""));
		CloseQuestHeader("Postcureer");
		ChangeCharacterComplexReputation(pchar, "nobility", 10);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), 33);
		DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
		DeleteAttribute(pchar, "questTemp.WPU.Current");
		DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
		pchar.questTemp.WPU.Postcureer = "complete";
		DialogExit();
		break;

	case "Postcureer_LevelUp_complete_fail":
		dialog.text = "Eh, sabía que terminaría de esta manera... Debería haber contratado un barco de mensajería militar, no a un capitán civil... Tendrá que ser así, " + GetAddress_Form(NPChar) + ". Como no eres un soldado, no hay nada de que culparte. Adiós.";
		link.l1 = "Adiós, " + GetAddress_FormToNPC(NPChar) + ".";
		link.l1.go = "exit";
		if (pchar.questTemp.WPU.Postcureer == "begin")
			pchar.quest.PostcureerTime_Over.over = "yes"; // снять таймер
		if (pchar.questTemp.WPU.Postcureer == "late")
			pchar.quest.PostcureerTime_FullOver.over = "yes"; // снять второй таймер
		CloseQuestHeader("Postcureer");
		ChangeCharacterComplexReputation(pchar, "nobility", -2);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), -2);
		pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count) - 3; // скрутим счетчик
		DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
		DeleteAttribute(pchar, "questTemp.WPU.Current");
		DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
		pchar.questTemp.WPU.Postcureer = "complete";
		break;

	case "Postcureer_LevelUp_complete_Agentfail":
		dialog.text = "Sir, conozco al encargado de la autoridad portuaria de " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Postcureer.StartCity + "Gen") + " personalmente y es un hombre honesto. ¡Además, no tiene sentido que abriera el mensaje! ¡" + GetAddress_Form(NPChar) + ", eres un fraude! No te pagaré ni un simple cobre. ¡Piérdete!";
		link.l1 = "Hm...";
		link.l1.go = "Postcureer_LevelUp_complete_Agentfail_1";
		break;

	case "Postcureer_LevelUp_complete_Agentfail_1":
		if (pchar.questTemp.WPU.Postcureer == "begin")
			pchar.quest.PostcureerTime_Over.over = "yes"; // снять таймер
		if (pchar.questTemp.WPU.Postcureer == "late")
			pchar.quest.PostcureerTime_FullOver.over = "yes"; // снять второй таймер
		RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
		AddQuestRecord("Postcureer", "17");
		AddQuestUserData("Postcureer", "sSex", GetSexPhrase("", ""));
		CloseQuestHeader("Postcureer");
		ChangeCharacterComplexReputation(pchar, "nobility", -10);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), -2);
		pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count) - 3; // скрутим счетчик
		DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
		DeleteAttribute(pchar, "questTemp.WPU.Current");
		DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Postcureer.AgentChance");
		pchar.questTemp.WPU.Postcureer = "complete";
		DialogExit();
		break;

		// <--почтовый генератор 2 уровня

		// Jason --> ---------------------------------генератор Неудачливый вор--------------------------------------------
	case "Device_Common":
		dialog.text = "Se parecía a un desgraciado, un mendigo o un vagabundo. No puedo decir donde fue exactamente, ni intenté seguirlo.";
		link.l1 = "Eso es mejor que nada. ¡Gracias, debería irme!";
		link.l1.go = "Device_Common_1";
		break;

	case "Device_Common_1":
		string sNation = pchar.GenQuest.Device.Shipyarder.Nation;
		sld = GetCharacter(NPC_GenerateCharacter("Device_poorman", "panhandler_" + (rand(5) + 1), "man", "man", sti(pchar.rank) + 5, sNation, 20, true, "quest"));
		SetFantomParamFromRank(sld, sti(pchar.rank) + 5, true);
		GiveItem2Character(sld, "slave_02");
		EquipCharacterbyItem(sld, "slave_02");
		LAi_SetCitizenType(sld);
		LAi_group_MoveCharacter(sld, sNation + "_CITIZENS");
		sld.Dialog.Filename = "Quest\Other_Quests_NPC.c";
		sld.dialog.currentnode = "Device_poorman";
		sld.greeting = "Gr_poorman";
		switch (sti(pchar.GenQuest.Device.Shipyarder.Chance2))
		{
		case 0: // в городе
			sld = characterFromId("Device_poorman");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.City + "_town", "goto", LAi_FindFarLocator("goto", locx, locy, locz));
			break;
		case 1: // за воротами
			sld = characterFromId("Device_poorman");
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.City + "_ExitTown", "goto", "goto1");
			break;
		case 2: // в бухте
			sld = characterFromId("Device_poorman");
			pchar.GenQuest.Device.Shipyarder.Shore = SelectQuestShoreLocation();
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.Shore, "goto", "goto1");
			break;
		case 3: // в доме
			sld = characterFromId("Device_poorman");
			pchar.GenQuest.Device.Shipyarder.Location = GetDeviceLocation(npchar); // определяем локацию
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.Location, "goto", "goto1");
			if (pchar.GenQuest.Device.Shipyarder.Location == "none" || CheckAttribute(pchar, "GenQuest.SeekSpy.Location")) // если вдруг мимо или взят поиск шпиона
			{
				pchar.GenQuest.Device.Shipyarder.Shore = SelectQuestShoreLocation();
				ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.Shore, "goto", "goto1");
			}
			break;
		}
		pchar.GenQuest.Device.Shipyarder = "inSeek";
		DialogExit();
		AddQuestRecord("Device", "9");
		break;
	//<-- генератор Неудачливый вор

	// Addon-2016 Jason ФМК-Сент-Кристофер
	case "FMQN_r":
		DelLandQuestMark(npchar);
		Dialog.Text = "No hace mucho, un buque inglés fue capturado en aguas de Sint-Maarten; en él viajaban algunos oficiales de alto rango. Se decidió enviarlos a Willemstad, pero en este momento están retenidos aquí, en nuestras cómodas mazmorras. Dicen que uno de los soldados capturados ha informado a nuestro comandante de las intenciones de los ingleses de enviar aquí una partida de asalto para rescatar a los oficiales. Por eso nuestro buen comandante está listo y armado. ¿Por qué no habría de estarlo? ¡Si los prisioneros desaparecen, será degradado a soldado raso!";
		link.l1 = "Intrigante... Bien, el dinero es tuyo. Toma esto. ¿Algo más que decirme?";
		link.l1.go = "rumours_tavern";
		pchar.questTemp.FMQN = "governor";
		pchar.quest.FMQN_governor.win_condition.l1 = "location";
		pchar.quest.FMQN_governor.win_condition.l1.location = "Marigo_town";
		pchar.quest.FMQN_governor.function = "FMQN_ToGovernor";
		if (Whr_IsDay())
			AddDialogExitQuest("FMQN_GetRumoursDay");
		else
			AddDialogExitQuest("FMQN_GetRumoursNight");
		break;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////		Квесты мэра, проникновение во враждебный город
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case "IntelligenceForAll":
		Dialog.Text = RandPhraseSimple("Muy bien, tengo un paquete listo para la entregar, toma.\nNo vengas más y no me hables. Es demasiado peligroso, cuidado por ahí...",
									   "Hm, genial. Toma el paquete y asegúrate de entregárselo al hombre del que acabamos de hablar.\nAdiós y no vuelvas a hablar conmigo, es demasiado peligroso.");
		link.l1 = RandPhraseSimple("Comprendo. Adiós...", "Adiós y buena suerte.");
		link.l1.go = "exit";
		pchar.GenQuest.Intelligence = "Execute";
		GiveItem2Character(pchar, "sicretLetter");
		AddCharacterExpToSkill(pchar, "Sneak", 200);
		ref rItem = ItemsFromID("sicretLetter");
			rItem.City = XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.Intelligence.MayorId)].city+"Gen"));
			rItem.Mayor = GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId));
			AddQuestRecord("MayorsQuestsList", "7");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony" + characters[GetCharacterIndex(pchar.GenQuest.Intelligence.MayorId)].city + "Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Intelligence.City + "Voc")); // belamour gen
			AddQuestUserData("MayorsQuestsList", "sWho", GetWorkTypeOfMan(&characters[GetCharacterIndex(pchar.GenQuest.Intelligence.SpyId)], "Gen"));
			AddQuestUserData("MayorsQuestsList", "SpyName", GetFullName(&characters[GetCharacterIndex(pchar.GenQuest.Intelligence.SpyId)]));
			break;

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			/////////		Грабеж среди бела дня, попытка залезть в сундуки
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case "Man_FackYou":
		dialog.text = LinkRandPhrase("¡Un robo a la luz del día! ¡¿De verdad?! Quédate donde estás, amigo...", "Oye, ¿qué estás haciendo ah? Parece que alguien iba a robarme, estás acabado...", "Espera, ¿te vas? ¡Un ladrón! Fin de la línea, amigo...");
		link.l1 = LinkRandPhrase("¡¡Rayos!!", "¡¡Demonios!!", "¡Maldición!");
		link.l1.go = "fight_owner";
		break;
	case "fight_owner":
		LAi_SetOwnerTypeNoGroup(NPChar);
		LAi_group_Attack(NPChar, Pchar);
		if (rand(3) != 1)
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		NextDiag.CurrentNode = "First time";
		DialogExit();
		break;
	}
}

string sRumourAboutOwners_CityRumour(string sCity, string sOwnerType) // Здесь идёт распределение по городам
{
	string sRetRumour = "Parece que has encontrado un error, avisa a los desarrolladores.";
	// флаг - PChar.QuestTemp.RumoursAboutOwners.(sOwner) - для проверок, какой вопрос выпал. Ножно будет юзать для квестов
	switch (sCity)
	{
	case "Tortuga":
		sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
		PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 0;
		break;

	case "PortRoyal":
		sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
		PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 1;
		break;

	case "FortOrange":
		sRetRumour = sRumourAboutOwners_Init(sOwnerType, 2);
		PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 2;
		break;

	case "Beliz":
		sRetRumour = sRumourAboutOwners_Init(sOwnerType, 3);
		PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 3;
		break;

	case "PortoBello":
		sRetRumour = sRumourAboutOwners_Init(sOwnerType, 4);
		PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 4;
		break;

	case "Cartahena":
		sRetRumour = sRumourAboutOwners_Init(sOwnerType, 5);
		PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 5;
		break;

	case "Maracaibo":
		sRetRumour = sRumourAboutOwners_Init(sOwnerType, 6);
		PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 6;
		break;

	case "Caracas":
		sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
		PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 7;
		break;

	case "Cumana":
		sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
		PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 8;
		break;

	case "SantaCatalina":
		sRetRumour = sRumourAboutOwners_Init(sOwnerType, 2);
		PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 9;
		break;

	case "SanJuan":
		sRetRumour = sRumourAboutOwners_Init(sOwnerType, 3);
		PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 10;
		break;

	case "Marigo":
		sRetRumour = sRumourAboutOwners_Init(sOwnerType, 4);
		PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 11;
		break;

	case "Charles":
		sRetRumour = sRumourAboutOwners_Init(sOwnerType, 5);
		PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 12;
		break;

	case "SentJons":
		sRetRumour = sRumourAboutOwners_Init(sOwnerType, 6);
		PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 13;
		break;

	case "FortFrance":
		sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
		PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 14;
		break;

	case "BasTer":
		sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
		PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 15;
		break;

	case "Bridgetown":
		sRetRumour = sRumourAboutOwners_Init(sOwnerType, 2);
		PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 16;
		break;

	case "PortSpein":
		sRetRumour = sRumourAboutOwners_Init(sOwnerType, 3);
		PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 17;
		break;

	case "Havana":
		sRetRumour = sRumourAboutOwners_Init(sOwnerType, 4);
		PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 18;
		break;

	case "Villemstad":
		sRetRumour = sRumourAboutOwners_Init(sOwnerType, 5);
		PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 19;
		break;

	case "Santiago":
		sRetRumour = sRumourAboutOwners_Init(sOwnerType, 6);
		PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 20;
		break;

	case "PortPax":
		sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
		PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 21;
		break;

	case "SantoDomingo":
		sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
		PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 22;
		break;
	}

	return sRetRumour;
}

string sRumourAboutOwners_Init(string sOwnerType, int iRumourNum) // База слухов жителей. Можно менять без новой игры
{

	string STR_MAYOR[MAX_RUMOURS_ABOUT_OWNERS]; // Губернаторы
	STR_MAYOR[0] = "Oh, nuestro gobernador es un hombre excelente. Gobierna nuestra colonia con gran habilidad y nunca ha tenido un solo conflicto desde el día de su toma de posesión.\nSu único defecto es... es... bueno... es bastante ahorrativo. Aunque podría ser una virtud.";
	STR_MAYOR[1] = "Oh, nuestro gobernador es un hombre excelente. Gobierna nuestra colonia con gran habilidad y nunca ha tenido un solo conflicto desde el día de su toma de posesión.\nSu único defecto es... es... bueno... es bastante ahorrativo. Aunque podría ser una virtud.";
	STR_MAYOR[2] = "Nuestro gobernador es un buen hombre pero tiene un carácter débil. Si tuviera un poco de firmeza en su alma, nuestros comerciantes podrían tener pequeñas exenciones fiscales... Y ya es hora de asignar fondos para la reparación del fuerte.";
	STR_MAYOR[3] = "Hmm ... Recientemente fue nombrado gobernador. Es bastante joven y tiene mucha iniciativa, con él nuestra colonia está floreciendo.";
	STR_MAYOR[4] = "Nuestro gobernador es relativamente joven. Dicen que es el hijo bastardo de un conde español que han enviado lejos de su casa para no de avergonzar a su familia. Ha sido nombrado hace poco y no ha tenido tiempo de hacer nada memorable.";
	STR_MAYOR[5] = "Hmm ... Recientemente se ha convertido en nuestro gobernador. Es bastante joven y tiene mucha iniciativa. Con él nuestra colonia está floreciendo";
	STR_MAYOR[6] = "Bueno... Nada... No puedo decir nada malo de él...";

	string STR_TAVERNKEEPER[MAX_RUMOURS_ABOUT_OWNERS]; // Тавернщики
	STR_TAVERNKEEPER[0] = "No le confiaría mi propiedades a ese pillo. No me malinterpretes, pero me parece que es la persona menos fiable de nuestra ciudad. He oído que trabaja con piratas y contrabandistas que a menudo se ven por su taberna.";
	STR_TAVERNKEEPER[1] = "¿Qué puedo decir de él? Puede que sea un cobarde, pero tampoco es la persona más inteligente que conozco. Además, es muy codicioso con el dinero. ¡Por eso se mete en problemas constantemente! Siempre está al tanto de todas las noticias.";
	STR_TAVERNKEEPER[2] = "Es un tipo bastante agradable. Siempre es grato pasar tiempo en su taberna y también tiene un gran sentido del humor. Lo más importante es que mantiene la taberna en orden y evita que los delincuentes borrachos molesten a los buenos ciudadanos.";
	STR_TAVERNKEEPER[3] = "Es un hombre increíble. No debería tener una taberna, tendría que ser informante del servicio de inteligencia. A veces parece que sabe literalmente todo lo que pasa en nuestra ciudad y eso me asusta.";
	STR_TAVERNKEEPER[4] = "No sé qué decirte. Ese hombre, tiene una taberna y lo sabe todo sobre la ciudad y sus ciudadanos.";
	STR_TAVERNKEEPER[5] = "Dicen que se puede confiar en él. Por otro lado, he oído que no le gustan los riesgos innecesarios y que siempre tiene cuidado al hacer sus negocios. Ah, los negocios turbios no son de su preferencia...";
	STR_TAVERNKEEPER[6] = "Heredó la taberna de su padre. Su padre tenía una taberna no lejos de aquí, en la isla de Highrock que está en otro archipiélago. Cuando su padre se mudó, construyó esta taberna y ahora su hijo la dirige.";

	string STR_SHIPYARDER[MAX_RUMOURS_ABOUT_OWNERS]; // Верфисты
	STR_SHIPYARDER[0] = "Construye naves y es un hombre tranquilo y pacífico. Supongo que es un buen hombre.";
	STR_SHIPYARDER[1] = "Construye naves y es un hombre tranquilo y pacífico. Supongo que es un buen hombre.";
	STR_SHIPYARDER[2] = "Es un buen hombre, pero dicen que es demasiado duro. Reprende continuamente a todos sus empleados por lo que suelen abandonarlo. A pesar de eso, es un excelente constructor de barcos.";
	STR_SHIPYARDER[3] = "Es una persona muy educada. Escuché que estudió construcción naval en Inglaterra y luego en Holanda. Al final terminó lejos de la metrópoli, en este archipiélago.\nLa gente dice que se granjeó problemas con la Santa Inquisición y tuvo que huir a esta colonia.";
	STR_SHIPYARDER[4] = "Ese anciano tiene que retirarse y dejar vía libre a la sangre fresca. Sueña constantemente con los tiempos pasados y se queja cuando alguien le pide algo a parte de carabelas o galeones.";
	STR_SHIPYARDER[5] = "Es un gran muchacho y siempre está dispuesto a ayudar. Debo decir que construye buenos barcos teniendo en cuenta donde estamos.";
	STR_SHIPYARDER[6] = "Era un prisionero y fue desterrado desde Europa a nuestra colonia hasta que resultó que tenía talento para la construcción naval. Después de que fueran construidos dos magníficos bergantines bajo su dirección en el astillero, le fueron perdonados todos sus delitos y ahora es un miembro de pleno derecho de nuestra sociedad.";

	string STR_TRADER[MAX_RUMOURS_ABOUT_OWNERS]; // Магазинщики
	STR_TRADER[0] = "No puedo decir nada malo de él. Es un ciudadano decente, que visita a menudo nuestra capilla. Parece que a la gente le gusta, nadie se ha enfadado con él.";
	STR_TRADER[1] = "Es el principal proveedor de nuestro gobernador y eso le depara buenos ingresos. Parece que lleva sus asuntos con honestidad, al menos no se le ha notado nada que le avergüence.";
	STR_TRADER[2] = "Ese gordo es muy respetado en nuestra ciudad. Sus productos son excelentes y no recuerdo ni un solo caso en el que haya engañado a alguien.";
	STR_TRADER[3] = "Es un inútil de solemnidad. Hace negocios que no tienen sentido, algunas veces tiene algún artículo agotado, otras veces más y las menos la mitad de los bienes... Ni siquiera puede librarse de las deudas.";
	STR_TRADER[4] = "No es un buen hombre, monsieur. Oí que era la mano derecha de Piere Thiers, el anterior comerciante, pero lo arruinó y le compró la tienda. No sé si los productos que vende son de calidad, pero como persona es muy desagradable.";
	STR_TRADER[5] = "¡Oh! Es una persona horrible, no te aconsejaría que tuvieras ningún negocio con él.\n¡Mantiene endeudada a la mitad de los habitantes de nuestra ciudad! Los productos que vende en su tienda, siempre son de mala calidad.";
	STR_TRADER[6] = "En realidad nadie sabe nada de él. Se ha mudado recientemente y abrió de inmediato ese negocio. Honestamente, no le han pillado con contrabando.";

	string sTempMayor = STR_MAYOR[iRumourNum];
	string sTempTavernkeper = STR_TAVERNKEEPER[iRumourNum];
	string sTempShipyarder = STR_SHIPYARDER[iRumourNum];
	string sTempTrader = STR_TRADER[iRumourNum];

	if (sOwnerType == "Mayor")
		return sTempMayor;
	if (sOwnerType == "TavernKeeper")
		return sTempTavernkeper;
	if (sOwnerType == "ShipYarder")
		return sTempShipyarder;
	if (sOwnerType == "Trader")
		return sTempTrader;
}

string GetDeviceLocation(ref npchar)
{
	aref arCommon, arRld, arRld2;
	int i, n, Qty, Qty2;
	string LocId;
	string storeArray[50];
	int howStore = 0;
	makearef(arRld, Locations[FindLocation(npchar.city + "_town")].reload);
	Qty = GetAttributesNum(arRld);
	if (CheckAttribute(pchar, "questTemp.jailCanMove.Deliver.locationId") || CheckAttribute(pchar, "GenQuest.SeekSpy.Location")) // если взят квест по доставке малявы или шпиона
	{
		for (i = 0; i < Qty; i++)
		{
			arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
			if (findsubstr(LocId, "Common", 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId && LocId != pchar.GenQuest.SeekSpy.Location)
			{
				storeArray[howStore] = LocId;
				howStore++;
			}
			if (arCommon.label != "Sea")
			{
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n = 0; n < Qty2; n++)
				{
					arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common", 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId && LocId != pchar.GenQuest.SeekSpy.Location && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2" && arCommon.name != "reload1") // mitrokosta fix
					{
						storeArray[howStore] = LocId;
						howStore++;
					}
				}
			}
		}
	}
	else
	{
		for (i = 0; i < Qty; i++)
		{
			arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
			if (findsubstr(LocId, "Common", 0) != -1)
			{
				storeArray[howStore] = LocId;
				howStore++;
			}
			if (arCommon.label != "Sea")
			{
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n = 0; n < Qty2; n++)
				{
					arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common", 0) != -1 && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2" && arCommon.name != "reload1") // mitrokosta fix
					{
						storeArray[howStore] = LocId;
						howStore++;
					}
				}
			}
		}
	}
	if (howStore == 0)
		return "none";
	LocId = storeArray[hrand(howStore - 1)];
	SetOpenDoorCommonLoc(npchar.city, LocId); // открываем дверь
	for (n = 0; n < MAX_CHARACTERS; n++)
	{
		if (CheckAttribute(&characters[n], "locations") && characters[n].locations == LocId)
		{
			characters[n].lifeDay = 0;
		}
	}
	return LocId;
}
