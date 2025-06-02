void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i, iRnd, iRnd1;
	string sTemp, sGems;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "exit_1":
		AddDialogExitQuest("LandEnc_RapersTalk");
		Diag.CurrentNode = Diag.TempNode;
		DialogExit();
		break;

	case "exit":
		LAi_SetCitizenTypeNoGroup(NPChar);
		Diag.CurrentNode = Diag.TempNode;
		DialogExit();
		break;

	case "Begin_1":
		LAi_RemoveCheckMinHP(npchar);
		for (i = 1; i <= 3; i++)
		{
			if (GetCharacterIndex("GangMan_" + i) == -1)
				continue;
			sld = CharacterFromID("GangMan_" + i);
			LAi_type_actor_Reset(sld);
		}
		dialog.text = RandPhraseSimple("" + GetSexPhrase("Capitán", "Señora") + "¡Por favor, sé misericordioso! Protégeme, te lo suplico!", "¡Ayuda! " + GetSexPhrase("Extranjero", "Señorita") + ", ¡sálvame, te lo suplico!");
		link.l1 = LinkRandPhrase("¿Qué ocurrió?", "¿Qué pasa?", RandPhraseSimple("¿Cuál es el problema?", "¿Qué está pasando?"));
		link.l1.go = "Begin_11";
		break;

	case "Begin_2":
		LAi_RemoveCheckMinHP(NPChar);
		for (i = 1; i <= 3; i++)
		{
			if (GetCharacterIndex("GangMan_" + i) == -1)
				continue;
			sld = CharacterFromID("GangMan_" + i);
			LAi_type_actor_Reset(sld);
		}
		dialog.text = RandPhraseSimple("" + GetSexPhrase("¡Capitán! ¡Capitán!", "¡Chica! ¡Chica!") + ", ¡por favor aguanta!", "Espera, " + GetSexPhrase("Capitán", "joven dama") + "¡Por favor.");
		link.l1 = LinkRandPhrase("¿Qué pasó?", "¿Qué pasa?", RandPhraseSimple("¿Cuál es el problema?", "¿Qué está pasando?"));
		link.l1.go = "Begin_21";
		break;

	case "Begin_3":
		LAi_RemoveCheckMinHP(NPChar);
		for (i = 1; i <= 3; i++)
		{
			if (GetCharacterIndex("GangMan_" + i) == -1)
				continue;
			sld = CharacterFromID("GangMan_" + i);
			LAi_type_actor_Reset(sld);
		}
		dialog.text = "¡Oh, señor" + GetSexPhrase("", "ita") + " ¡Por favor, ayuda a una pobre chica, te lo suplico! ¡Esas personas quieren hacerme algo terrible!";
		link.l1 = LinkRandPhrase("¿Qué ha ocurrido?", "¿Qué pasa?", RandPhraseSimple("¿Cuál es el problema?", "¿Qué está pasando?"));
		link.l1.go = "Begin_31";
		break;

	case "Begin_11":
		dialog.text = RandPhraseSimple("¡Estos villanos van a violarme! ¡Por todo lo que es bueno, no los dejes!", "¡Por el amor de Dios, protégeme de estos monstruos! ¡Van a deshonrarme!");
		link.l1 = "Deja de entrar en pánico" + GetSexPhrase(", belleza", "") + "¿. Qué ocurrió aquí?";
		link.l1.go = "exit_1";
		break;

	case "Begin_21":
		dialog.text = RandPhraseSimple("¡Me están persiguiendo violadores!" + GetSexPhrase("¿Defenderías el honor de una dama?", "") + "", "Capitán, " + GetSexPhrase("sé un hombre,", "tú también eres una mujer,") + " ¿salvarás a una chica de la deshonra?");
		link.l1 = "Deja de entrar en pánico" + GetSexPhrase(", belleza", "") + "¿Qué ha sucedido aquí?";
		link.l1.go = "exit_1";
		break;

	case "Begin_31":
		dialog.text = "¡Me están persiguiendo! ¡Los bandidos! Diles que me dejen en paz!";
		link.l1 = "Deja de entrar en pánico" + GetSexPhrase(", belleza", "") + "¿Qué ha ocurrido aquí?";
		link.l1.go = "exit_1";
		break;

	case "First time":
		LAi_RemoveCheckMinHP(npchar);
		for (i = 1; i <= 3; i++)
		{
			if (GetCharacterIndex("GangMan_" + i) == -1)
				continue;
			sld = CharacterFromID("GangMan_" + i);
			LAi_type_actor_Reset(sld);
		}
		dialog.text = LinkRandPhrase("¡Ayuda! ¡Ayuda! ¡Me están persiguiendo! ¡Sálvame!", "¡Aaah! Ayuda, " + GetSexPhrase("extraño", "joven dama") + "¡Sálvame de estos malhechores!", "¡Muestra misericordia y protégeme de estos malandrines! ¡Por favor!");
		Link.l1 = LinkRandPhrase("¿Qué está pasando?", "¿Qué pasa?", "¿Qué pasó?");
		Link.l1.go = "Node_2";
		break;

	case "Node_2":
		dialog.text = LinkRandPhrase("¡Ellos... ellos van a violarme! ¡Por todo lo que es bueno, no los dejes! ¡Por favor!", "Estas bestias... están planeando algo horrible... Protégeme de ellas, por favor!", "¡En el nombre de nuestro Señor, sálvame de estas bestias lujuriosas! ¡Quieren deshonrarme!");
		Link.l1 = "Vamos a averiguarlo todo, entonces.";
		Link.l1.go = "exit_1";
		break;

	case "ThanksForHelp":
		if (pchar.GenQuest.EncGirl == "Begin_11")
		{
			if (rand(1) == 0)
			{
				dialog.text = RandPhraseSimple("Gracias, " + GetSexPhrase("Capitán", "señorita") + ". ¡Estaba tan asustado!", "¡Gracias por salvarme! ¡Estoy tan agradecido contigo!");
				link.l1 = "Está bien, " + GetSexPhrase("belleza", "querido") + ", cálmate, todo eso es cosa del pasado.";
				link.l1.go = "Node_11";
			}
			else
			{
				dialog.text = "Oh, gracias, " + GetSexPhrase("¡noble hombre! ¡Eres un verdadero caballero!", "¡Señora! ¡Me has salvado!") + "";
				link.l1 = "No podía hacer de otra manera.";
				link.l1.go = "Node_12";
			}
		}
		if (pchar.GenQuest.EncGirl == "Begin_22")
		{
			if (rand(1) == 0)
			{
				dialog.text = "Oh, gracias, " + GetSexPhrase("¡noble hombre! ¡Eres un verdadero caballero!", "¡forastero! ¡Me has salvado!") + "";
				link.l1 = "No podía hacer de otra manera.";
				link.l1.go = "Node_12";
			}
			else
			{
				dialog.text = "¿Qué has hecho? ¡¿Por qué los has matado?! ¡Ahora me buscarán a mí! Dios mío, ¿qué he hecho para merecer esto?";
				link.l1 = "¡Eso sí que es gratitud!";
				link.l1.go = "Node_22";
			}
		}
		if (pchar.GenQuest.EncGirl == "Begin_33")
		{
			dialog.text = "¿Qué has hecho, " + GetSexPhrase("capitán", "señorita") + "? ¿Por qué los has matado? En realidad, fueron enviados por mi padre... Ay Dios, ahora seguro que me va a matar...";
			link.l1 = "¡Eso sí que son noticias! ¿Y qué te creías gritando que eras perseguida por bandidos?";
			link.l1.go = "Node_31";
		}
		break;

	case "Node_11":
		Diag.TempNode = "Node_1Next";
		addMoneyToCharacter(pchar, makeint((sti(pchar.rank)) * 25 + frand(2) * 500));
		dialog.text = "Tengo algo de dinero, por favor, acéptalo como muestra de mi gratitud. Ahora se lo diré a todos, " + GetSexPhrase("qué hombre tan bueno y noble eres", "qué buena y noble mujer eres") + ".";
		link.l1 = "Claro que lo harás. Gracias... Ahora solo vete a casa.";
		link.l1.go = "exit";
		pchar.GenQuest.EncGirl = "close";
		sGlobalTemp = "Saved_CangGirl";
		Diag.CurrentNode = Diag.TempNode;
		break;

	case "Node_12":
		dialog.text = "Todavía no puedo recomponerme. ¿Podría por favor acompañarme, señor" + GetSexPhrase("", "ita") + ", al asentamiento de " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + "? Sabes... Ahora siento que hay violadores escondidos detrás de cada arbusto.";
		link.l1 = RandPhraseSimple("No te preocupes tanto, de verdad... Bien, vamos.", "¿Eres un cobarde, no es cierto? De acuerdo, te llevaré allí.");
		link.l1.go = "Node_121Next";
		link.l2 = "Lo siento, cariño, pero simplemente no tengo tiempo, estoy demasiado ocupado.";
		link.l2.go = "Node_3End";
		break;

	case "Node_22":
		dialog.text = "¡Pensaba que solo los asustarías! Ahora debes llevarme a la taberna en el asentamiento de " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + ", no tengo a nadie más que a ti para pedir ayuda.";
		link.l1 = "¡Oh, maldita sea! Bueno, vamos. Solo no te quedes atrás.";
		link.l1.go = "Node_122Next";
		link.l2 = "No, eso es todo, " + GetSexPhrase("hermosura", "querido") + "¡Ya he tenido suficientes sorpresas por hoy. Busca a alguien más para que te ayude.";
		link.l2.go = "Node_3End";
		break;

	case "Node_31":
		dialog.text = "¿Y qué tenía que hacer yo?! Mi padre quiere que me case con el hijo del usurero, ese lechón... sólo porque su papi tiene un montón de dinero en sus cofres! ¡Pero yo amo a otro hombre! Llévame a él, por favor...";
		link.l1 = "¡Qué carga eres! Bueno, está bien, vamos. No puedo simplemente dejarte aquí, ¿verdad?.. ¿Cómo se llama tu elegido, a dónde debo llevarte?";
		link.l1.go = "Node_32";
		link.l2 = "No, eso es todo, " + GetSexPhrase("belleza", "querido") + "¡He tenido suficientes sorpresas por hoy. Busca a alguien más para que te ayude.";
		link.l2.go = "Node_3End";
		break;

	case "Node_32":
		pchar.GenQuest.EncGirl.sLoverId = GenerateRandomName(sti(npchar.nation), "man");
		dialog.text = "Su nombre es " + pchar.GenQuest.EncGirl.sLoverId + ", él es un recién llegado. Ahora mismo se queda en el asentamiento de " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + ", intenté encontrar un trabajo allí, pero estos son tiempos difíciles. Todos siguen hablando de una crisis... Y ahora, de todos modos, no hay vuelta atrás para mí.";
		link.l1 = "¿Una crisis? Ja... Para un verdadero pirata, una crisis es cuando hay una caravana comercial en el horizonte, pero no hay viento para llenar las velas...";
		link.l1.go = "Node_12Next";
		break;

	case "Node_12Next":
		pchar.quest.LandEnc_RapersBadExit.over = "yes";
		Diag.TempNode = "Node_12End";
		Diag.CurrentNode = Diag.TempNode;
		pchar.GenQuest.EncGirl = "FindLover";
		pchar.GenQuest.EncGirl.MeetSoldiers = 2;
		AddDialogExitQuestFunction("EncGirl_GirlFollow");
		DialogExit();
		break;

	case "Node_121Next":
		pchar.quest.LandEnc_RapersBadExit.over = "yes";
		Diag.TempNode = "Node_253";
		pchar.GenQuest.EncGirl = "FindCoins";
		pchar.GenQuest.EncGirl.MeetSoldiers = 1;
		Diag.CurrentNode = Diag.TempNode;
		pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
		pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_town";
		pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";
		AddDialogExitQuestFunction("EncGirl_GirlFollow");
		DialogExit();
		break;

	case "Node_122Next":
		pchar.quest.LandEnc_RapersBadExit.over = "yes";
		Diag.TempNode = "Node_12End";
		pchar.GenQuest.EncGirl = "HorseToTavern";
		pchar.GenQuest.EncGirl.MeetSoldiers = 1;
		Diag.CurrentNode = Diag.TempNode;
		pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
		pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
		pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";
		AddDialogExitQuestFunction("EncGirl_GirlFollow");
		DialogExit();
		break;

	case "Node_12End":
		Diag.TempNode = "Node_12End";
		dialog.text = RandPhraseSimple("Sabes, " + GetSexPhrase("capitán", "señorita") + ", estaba tan asustada que mis piernas todavía están un poco temblorosas.", "Oh, estaba tan asustada. Es un milagro que Dios te haya enviado por mi camino.");
		link.l1 = RandPhraseSimple("Gracias a Dios que todavía estás viva.", "No te lo tomes a pecho. Es bueno que haya terminado así, ya sabes.");
		link.l1.go = "exit";
		break;

	case "Node_1Next":
		dialog.text = RandPhraseSimple("Gracias, " + GetSexPhrase("capitán", "señorita") + ", una vez más. Realmente, estoy tan endeudado contigo.", "Muchas gracias, " + GetSexPhrase("capitán", "señorita") + ". No tengo idea de qué haría sin tu ayuda.");
		link.l1 = RandPhraseSimple("Esa debería ser una lección para ti. Bien, buena suerte...", "La próxima vez debes tener más cuidado... Ahora, vete a casa, tengo cosas que hacer.");
		link.l1.go = "Node_1End";
		link.l2 = "¿Cómo pudiste ser tan descuidado? ¿Por qué te adentraste en la jungla solo?";
		link.l2.go = "Node_13";
		break;

	case "Node_1End":
		sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "", "OpenTheDoors", -1.0);
		pchar.GenQuest.EncGirl = "close";
		sGlobalTemp = "Saved_CangGirl";
		DialogExit();
		AddDialogExitQuest("pchar_back_to_player");
		break;

	case "Node_3End":
		Diag.TempNode = "Node_3Final";
		sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "", "OpenTheDoors", -1.0);
		pchar.GenQuest.EncGirl = "close";
		sGlobalTemp = "Saved_CangGirl";
		ChangeCharacterComplexReputation(pchar, "nobility", -3);
		Diag.CurrentNode = Diag.TempNode;
		DialogExit();
		break;

	case "Node_3Final":
		Diag.TempNode = "Node_3Final";
		dialog.text = RandPhraseSimple("¿Has cambiado de opinión?", "¡Capitán, es estupendo que hayas cambiado de opinión!");
		link.l1 = RandPhraseSimple("No-no, querido, yo paso.", "No tengas falsas esperanzas...");
		link.l1.go = "exit";
		break;

	case "Node_13":
		if (pchar.GenQuest.EncGirl == "FindCoins")
		{
			pchar.quest.LandEnc_RapersBadExit.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LandEnc_RapersBadExit.win_condition.l1.location = pchar.location;
			pchar.quest.LandEnc_RapersBadExit.win_condition = "LandEnc_RapersBadExit";
		}
		pchar.GenQuest.EncGirl = "Begin_11";
		switch (sti(pchar.GenQuest.EncGirl.variant))
		{
		case 0:
			if (rand(1) == 0)
			{
				dialog.text = "Probablemente te rías de mí, pero... estaba recolectando una poción de amor... Una bruja me dijo que había una raíz que puede ayudar en asuntos de amor.";
				link.l1 = "¡Dios mío! " + GetSexPhrase("¿En qué están pensando estas mujeres?", "¿En qué estabas pensando?") + " Al parecer, has recogido a muchos de ellos, había bastantes pretendientes persiguiéndote, me ha costado mucho trabajo ahuyentarlos a todos. Ja-ja-ja-ja... Adiós.";
				link.l1.go = "Node_1End";
			}
			else
			{
				dialog.text = "Acabo de salir a pasear para recolectar algunas hierbas y respirar aire fresco. Aparentemente, no era el mejor momento para caminar.";
				link.l1 = "¡Qué descuido! Gracias a Dios que llegué a tiempo. Bueno, te deseo la mejor de las suertes.";
				link.l1.go = "Node_1End";
			}
			break;
		case 1:
			dialog.text = "Mi señora perdió las perlas de su collar por aquí, cuando estaba de paseo. Cuando llegó a casa, me gritó y ordenó salir a recogerlas. Ella dijo, '¡Ni siquiera muestres tu rostro aquí hasta que las recojas todas!', Y ni siquiera sé el lugar exacto. Además, ¿cómo se supone que las encuentre en esta hierba tan espesa? Las perlas son tan pequeñas... Entonces, solo estoy vagando aquí sin tener idea de qué debería hacer...";
			link.l1 = "¿Y qué tipo de collar era? Quizás, ¿sería más fácil simplemente comprar uno nuevo en lugar de vagar por la jungla? ¿Cuántas perlas ha perdido tu ama?";
			link.l1.go = "Node_131";
			break;
		case 2:
			dialog.text = "Mi difunto padre me dejó un mapa, y sus compañeros querían arrebatármelo. Mientras él estaba vivo, todos temblaban de miedo ante él, pero justo cuando lo había enterrado, comenzaron los tiempos difíciles. Primero intentaron comprar este mapa de mí, pero me negué, y entonces comenzaron a intimidarme.";
			link.l1 = "¿Y por qué no lo vendiste simplemente? ¿Qué tiene de especial este mapa, que las bandas de piratas lo buscan?";
			link.l1.go = "Node_132";
			break;
		}
		break;

	case "Node_131":
		pchar.GenQuest.EncGirl.SmallCoins = rand(25) + 20;
		pchar.GenQuest.EncGirl.BigCoins = rand(15) + 5;
		dialog.text = "Ese collar estaba compuesto de perlas seleccionadas, esas no se pueden comprar baratas. Había " + sti(pchar.GenQuest.EncGirl.BigCoins) + " perlas grandes y " + sti(pchar.GenQuest.EncGirl.SmallCoins) + " más pequeños. Si se encontraran esas perlas, podríamos encargar otro collar como ese.";
		link.l1 = "Seguramente este no será un trabajo fácil... Bueno, si tu señora te dio una orden, entonces no hay mucho que puedas hacer. Intenta encontrar las perlas. Buena suerte.";
		link.l1.go = "Node_131End";
		link.l2 = "Es inútil. Sería más fácil encontrar una aguja en un pajar que las perlas en esta hierba espesa. Sin mencionar que ni siquiera conoces el lugar donde se perdieron las perlas...";
		link.l2.go = "Node_133";
		break;

	case "Node_131End":
		Diag.TempNode = "Node_12End";
		pchar.GenQuest.EncGirl = "close";
		sGlobalTemp = "Saved_CangGirl";
		ChangeCharacterComplexReputation(pchar, "nobility", -2);
		Diag.CurrentNode = Diag.TempNode;
		DialogExit();
		pchar.quest.LandEnc_RapersBadExit.win_condition.l1 = "ExitFromLocation";
		pchar.quest.LandEnc_RapersBadExit.win_condition.l1.location = pchar.location;
		pchar.quest.LandEnc_RapersBadExit.win_condition = "LandEnc_RapersBadExit";
		AddDialogExitQuest("pchar_back_to_player");
		break;

	case "Node_132":
		pchar.GenQuest.EncGirl.mapOwner = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
		dialog.text = "Mi padre marcó un lugar en él donde había escondido su tesoro. ¿Has oído hablar del famoso pirata " + GetName(NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_VOC) + "?";
		link.l1 = "No, nunca he oído hablar de él.";
		link.l1.go = "Node_132_1";
		break;

	case "Node_132_1":
		dialog.text = "Bueno, " + GetName(NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_NOM) + " era mi padre. Todos le tenían miedo, nadie se atrevía a decir una palabra. Ahora, por supuesto, se han vuelto descarados. Cuando me negué a venderles el mapa, afirmaron que ellos también deben tener su parte del tesoro. Quería esconder el mapa, pero aún así me rastrearon...";
		link.l1 = "¿Y por qué lo ocultarías, en primer lugar? Fleta un barco y vete, reclama tu tesoro. Tu padre no lo habría ocultado por nada.";
		link.l1.go = "Node_132_2";
		break;

	case "Node_132_2":
		dialog.text = "Más fácil decirlo que hacerlo. No tengo dinero para fletar un barco, y... tengo miedo... ¿Cómo se supone que debo desenterrarlo todo, llevarlo al barco... Y a dónde llevaría el tesoro luego? Sería presa fácil para cualquiera en el camino...";
		link.l1 = "Eso es un buen punto... Está bien, adelante y esconde tu mapa, entonces. Solo recuerda colocarlo bien.";
		link.l1.go = "Node_132_2End";
		if (GetCharacterItem(pchar, "map_full") == 0)
		{
			link.l2 = "Hmm... Probablemente eso sea cierto. Más aún, deberías haberlo vendido.";
			link.l2.go = "Node_132_3";
		}
		link.l3 = "¿Has intentado encontrar un compañero?";
		link.l3.go = "Node_132_8";
		break;

	case "Node_132_2End":
		Diag.TempNode = "Node_12End";
		pchar.GenQuest.EncGirl = "close";
		sGlobalTemp = "Saved_CangGirl";
		sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "", "OpenTheDoors", -1.0);
		Diag.CurrentNode = Diag.TempNode;
		DialogExit();
		AddDialogExitQuest("pchar_back_to_player");
		break;

	case "Node_132_3":
		dialog.text = "Me entristece perder una oportunidad así... Papá me contó sobre los tesoros que había escondido allí. Nadie me pagaría tanto...";
		link.l1 = "Bueno, no lo vendas demasiado barato. Y, de todas formas, el oro no vale tu vida. Sin mencionar que esta es la manera más fácil para ti, simplemente recoges tu dinero y te libras de todos los problemas...";
		link.l1.go = "Node_132_4";
		break;

	case "Node_132_4":
		pchar.GenQuest.EncGirl.mapPrice = 20000 + 500 * sti(pchar.rank);
		dialog.text = "Eso suena tentador... ¿Y cuánto puedes ofrecerme por ello?";
		link.l1 = "No creo que pueda valer más que " + sti(pchar.GenQuest.EncGirl.mapPrice) + " pesos.";
		link.l1.go = "Node_132_5";
		break;

	case "Node_132_5":
		if ((GetSummonSkillFromName(pchar, SKILL_COMMERCE) + GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) + GetSummonSkillFromName(pchar, SKILL_FORTUNE)) > (rand(220) + 100) && (makeint(pchar.money) >= sti(pchar.GenQuest.EncGirl.mapPrice)))
		{
			dialog.text = "Je, ser mujer no es fácil... Bien, estoy de acuerdo. Finalmente esta pesadilla terminará... Quizás, es mejor que este mapa te pertenezca," + GetSexPhrase("un caballero noble", "") + ", que a esos granujas.";
			link.l1 = "Bueno. Aquí está tu dinero... solo intenta no gastarlo todo de una vez.";
			link.l1.go = "Node_132_6";
		}
		else
		{
			dialog.text = "No, " + GetSexPhrase("capitán", "joven dama") + ". No lo venderé. Me casaré con un buen hombre, y luego reclamaremos el tesoro juntos.";
			link.l1 = "Bueno, eso es para que tú decidas. Tu pedazo de papel no vale más, de todos modos.";
			link.l1.go = "Node_132_2End";
		}
		break;

	case "Node_132_6":
		AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.mapPrice)));
		ref rMap = ItemsFromID("map_full"); // mitrokosta фикс пустой карты
		FillMapForTreasure(rMap);
		GiveItem2Character(pchar, "map_full");
		Diag.TempNode = "Node_12End";
		pchar.GenQuest.EncGirl = "close";
		sGlobalTemp = "Saved_CangGirl";
		Diag.CurrentNode = Diag.TempNode;
		DialogExit();
		AddDialogExitQuest("pchar_back_to_player");
		break;

	case "Node_132_8":
		dialog.text = "¿Y dónde los encontraré? Los jóvenes no son confiables, y no les importan tanto los tesoros como, otras cosas. Y temo a los más viejos, todos me recuerdan a los amigos de mi padre. Tan astutos y traicioneros, nunca sabrías qué esperar de ellos.";
		link.l1 = "Ja-ja-ja... Está bien, ¿pero me llevarás contigo?";
		link.l1.go = "Node_132_9";
		break;

	case "Node_132_9":
		dialog.text = "¿Tú? ¿Y te irías? Pero entonces tendrás que traerme de vuelta aquí, al asentamiento de " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + ", ¿de acuerdo?";
		link.l1 = "Bien, te doy mi palabra. Solo muéstrame el camino.";
		link.l1.go = "Node_132_10";
		break;

	case "Node_132_10":
		EncGirl_GenQuest_GetChestPlaceName();
		dialog.text = "El tesoro está escondido en la cueva en " + XI_ConvertString(pchar.GenQuest.EncGirl.islandId + "Acc") + ", necesitamos desembarcar en " + XI_ConvertString(pchar.GenQuest.EncGirl.shoreId + "Gen") + ", el lugar donde me mostraré... ¡Pero no olvides, solo conseguirás la mitad!";
		link.l1 = "De acuerdo, no te engañaré, lo prometo. Sígueme y no te quedes atrás.";
		link.l1.go = "Node_132_11";
		break;

	case "Node_132_11":
		ReOpenQuestHeader("JungleGirl");
		AddQuestRecord("JungleGirl", "4");
		AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
		AddQuestUserData("JungleGirl", "sPirateName", GetName(NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_GEN));
		AddQuestUserData("JungleGirl", "sTreasureLoc", XI_ConvertString(pchar.GenQuest.EncGirl.islandId));
		AddQuestUserData("JungleGirl", "sShore", XI_ConvertString(pchar.GenQuest.EncGirl.shoreId + "Gen"));
		AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
		pchar.quest.EncGirl_Death.win_condition.l1 = "NPC_Death";
		pchar.quest.EncGirl_Death.win_condition.l1.character = npchar.id;
		pchar.quest.EncGirl_Death.function = "EncGirl_Death";
		pchar.quest.EncGirl_FindChest.win_condition.l1 = "location";
		pchar.quest.EncGirl_FindChest.win_condition.l1.location = pchar.GenQuest.EncGirl.placeId;
		pchar.quest.EncGirl_FindChest.function = "EncGirl_FindChest";
		SetFunctionExitFromLocationCondition("EncGirl_AddPassenger", pchar.location, false);
		SetFunctionLocationCondition("EncGirl_DialogAtShore", pchar.GenQuest.EncGirl.shoreId, false);
		Diag.TempNode = "Node_12End";
		pchar.GenQuest.EncGirl = "GetChest";
		Diag.CurrentNode = Diag.TempNode;
		DialogExit();
		AddDialogExitQuest("pchar_back_to_player");
		break;

	case "Node_132_11_1":
		dialog.text = "Capitán, ahora debemos encontrar la cueva.";
		link.l1 = "Está bien, echemos un vistazo ahora.";
		link.l1.go = "exit";
		Diag.TempNode = "Node_132_11_2";
		Diag.CurrentNode = Diag.TempNode;
		AddDialogExitQuestFunction("EncGirl_GirlFollow");
		break;

	case "Node_132_11_2":
		Diag.TempNode = "Node_132_11_2";
		dialog.text = "Capitán, debemos encontrar la cueva.";
		link.l1 = "Está bien, echemos un vistazo ahora.";
		link.l1.go = "exit";
		break;

	case "Node_132_12":
		dialog.text = "¡Aquí! ¡Lo encontré! ¡Justo como dijo mi padre! ¡Un enorme montón de tesoro! La mitad es tuya, como acordamos.";
		link.l1 = "¿Ves? Eso no fue difícil, así que no había nada que temer.";
		link.l1.go = "Node_132_13";
		break;

	case "Node_132_13":
		dialog.text = "¡Ja-ja-ja! ¡Ahora soy rico! ¿Vas a tomar tu parte ahora?";
		link.l1 = "Supongo.";
		link.l1.go = "Node_132_15";
		break;

	case "Node_132_15":
		dialog.text = "Entonces tómalo y por favor ayúdame a llevar todas esas cosas al barco. ¿Todavía recuerdas que prometiste llevarme de vuelta a casa?";
		link.l1 = "¡No lo he olvidado! Claro, te llevaré.";
		link.l1.go = "Node_132_16";
		break;

	case "Node_132_16":
		pchar.quest.EncGirl_DeathSimple.over = "yes";
		PChar.quest.EncGirl_DialogAtShore.over = "yes"; // лесник . снял прерывание  , если не с той бухты зашёл.
		LAi_LocationDisableMonstersGen(pchar.location, false);
		chrDisableReloadToLocation = false;
		Log_Info("Has recibido tu parte del tesoro");
		PlaySound("interface\important_item.wav");
		TakeNItems(pchar, "icollection", 1 + hrand(1));
		TakeNItems(pchar, "chest", 2 + hrand(6));
		TakeNItems(pchar, "jewelry1", 30 + hrand(15));
		TakeNItems(pchar, "jewelry2", 30 + hrand(15));
		TakeNItems(pchar, "jewelry3", 30 + hrand(15));
		TakeNItems(pchar, "jewelry4", 30 + hrand(15));
		TakeNItems(pchar, "jewelry5", 30 + rand(10));
		TakeNItems(pchar, "jewelry6", 10 + rand(10));
		TakeNItems(pchar, "jewelry42", 20 + rand(10));
		TakeNItems(pchar, "jewelry44", 30 + rand(10));
		TakeNItems(pchar, "jewelry46", 50 + rand(20));
		AddQuestRecord("JungleGirl", "6");
		AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("", ""));
		AddQuestUserData("JungleGirl", "sPirateName", GetName(NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_GEN));
		AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
		AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
		pchar.GenQuest.EncGirl = "ChestGetted";
		pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
		pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_town";
		pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";
		pchar.quest.EncGirl_DeathAgain.win_condition.l1 = "NPC_Death";
		pchar.quest.EncGirl_DeathAgain.win_condition.l1.character = npchar.id;
		pchar.quest.EncGirl_DeathAgain.function = "EncGirl_DeathAgain";
		Diag.TempNode = "Node_132_17";
		Diag.CurrentNode = Diag.TempNode;
		DialogExit();
		AddDialogExitQuestFunction("EncGirl_GirlFollow");
		pchar.quest.EncGirl_AddPassenger.win_condition.l1 = "location"; // лесник на корабль девицу.
		pchar.quest.EncGirl_AddPassenger.win_condition.l1.location = pchar.location.from_sea;
		pchar.quest.EncGirl_AddPassenger.function = "EncGirl_AddPassenger";
		break;

	case "Node_132_17":
		Diag.TempNode = "Node_132_17";
		dialog.text = "¡Ser rico es simplemente genial! Me siento tan diferente ahora.";
		link.l1 = "Me alegro por ti.";
		link.l1.go = "exit";
		break;

	case "Node_132_18":
		dialog.text = "Bien, capitán. Mi viaje ha terminado ahora. Gracias por tu ayuda.";
		link.l1 = "De nada... Entonces, ¿qué planeas hacer con tus nuevas riquezas? ¿Comprar una plantación con esclavos?";
		link.l1.go = "Node_132_19";
		break;

	case "Node_132_19":
		dialog.text = "No lo sé, aún no he decidido. Quizás, me traslade a Europa...";
		link.l1 = "¡Bueno, bien! Buena suerte para ti.";
		link.l1.go = "Node_132_20";
		break;

	case "Node_132_20":
		dialog.text = "Espera... Este trinkete estaba entre los tesoros de mi padre. No tengo uso para él, pero a ti podría gustarte. Por favor, acéptalo como mi gratitud personal por lo que has hecho por mí. ¡Eso es de mi parte, ja-ja-ja!";
		link.l1 = "Vaya, eso sí que es un regalo bonito. Gracias" + GetSexPhrase(", belleza", "") + ". Encuentra un buen novio para ti, ¿si?";
		link.l1.go = "Node_132_21";
		break;

	case "Node_132_21":
		chrDisableReloadToLocation = false;
		RemovePassenger(pchar, npchar);
		GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item);
		AddQuestRecord("JungleGirl", "8");
		AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("", ""));
		AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
		CloseQuestHeader("JungleGirl");
		LAi_CharacterDisableDialog(npchar);
		npchar.lifeDay = 0;
		DeleteAttribute(pchar, "GenQuest.EncGirl");
		DialogExit();
		AddDialogExitQuest("pchar_back_to_player");
		LAi_SetActorType(npchar); // отправил восвояси чтоб не стояла. лесник.
		LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
		pchar.quest.EncGirl_EnterToSea.over = "yes";	// лесник . снял прерывание  , если не с той бухты зашёл.
		PChar.quest.EncGirl_DialogAtShore.over = "yes"; // лесник . снял прерывание  , если не с той бухты зашёл.
		break;

	case "Node_133":
		dialog.text = "¿Pero qué puedo hacer? No puedo ignorar las órdenes de mi ama, me desollará viva.";
		link.l1 = "Espérame en la iglesia del asentamiento de " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + ", te traeré las perlas para hacer un nuevo collar.";
		link.l1.go = "Node_133_1";
		if (sti(pchar.money) >= 15000)
		{
			link.l2 = "Aquí. Toma estos 15000 pesos. Eso debería ser más que suficiente para seleccionar las perlas para el collar, o para comprar uno nuevo.";
			link.l2.go = "Node_135";
		}
		break;

	case "Node_133_1":
		pchar.GenQuest.EncGirl = "GetCoins";
		pchar.quest.EncGirl_Coins.win_condition.l1 = "ExitFromLocation";
		pchar.quest.EncGirl_Coins.win_condition.l1.location = pchar.location;
		pchar.quest.EncGirl_Coins.function = "EncGirl_toChurch";
		pchar.quest.EncGirl_GetCoins.win_condition.l1 = "Timer";
		pchar.quest.EncGirl_GetCoins.win_condition.l1.date.day = GetAddingDataDay(0, 0, 10);
		pchar.quest.EncGirl_GetCoins.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
		pchar.quest.EncGirl_GetCoins.win_condition.l1.date.year = GetAddingDataYear(0, 0, 10);
		pchar.quest.EncGirl_GetCoins.function = "EncGirl_GenQuest_GetCoins";
		sTemp = LAi_FindNearestFreeLocator2Pchar("reload"); // лесник - девица убегает если ГГ сказал ждать в цервки
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "", "OpenTheDoors", -1.0);
		Diag.TempNode = "Node_134";
		Diag.CurrentNode = Diag.TempNode;
		ReOpenQuestHeader("JungleGirl");
		AddQuestRecord("JungleGirl", "1");
		AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("", ""));
		AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
		AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
		AddQuestUserData("JungleGirl", "sText1", sti(pchar.GenQuest.EncGirl.BigCoins));
		AddQuestUserData("JungleGirl", "sText2", sti(pchar.GenQuest.EncGirl.SmallCoins));
		DialogExit();
		AddDialogExitQuest("pchar_back_to_player");
		break;

	case "Node_134":
		dialog.text = RandPhraseSimple("" + GetSexPhrase("Capitán", "Joven señorita") + ", ¡Estoy tan feliz de verte de nuevo! ¿Has logrado recolectar perlas para el collar?", "¡Hola, capitán! ¿Me has traído las perlas? Como puedes imaginar, mi señora se está poniendo tan nerviosa...");
		if (GetCharacterItem(pchar, "jewelry52") >= sti(pchar.GenQuest.EncGirl.BigCoins) && GetCharacterItem(pchar, "jewelry53") >= sti(pchar.GenQuest.EncGirl.SmallCoins))
		{
			link.l1 = "Sí. Aquí están tus perlas. Llévaselas a tu señora y dile que sea más cuidadosa la próxima vez.";
			link.l1.go = "Node_134_1";
		}
		else
		{
			link.l1 = "Aún no. No es tan fácil, ya sabes... Pero los traeré, solo espera.";
			link.l1.go = "Node_134_2";
		}
		break;

	case "Node_134_1":
		TakeNItems(pchar, "jewelry52", -sti(pchar.GenQuest.EncGirl.BigCoins));
		TakeNItems(pchar, "jewelry53", -sti(pchar.GenQuest.EncGirl.SmallCoins));
		pchar.quest.EncGirl_GetCoins.over = "yes";
		pchar.quest.EncGirl_DeathSimple.over = "yes";
		dialog.text = "Oh, " + GetSexPhrase("Capitán", "señorita") + ", estoy tan feliz de haberte conocido! Como muestra de mi gratitud por todo lo que has hecho por mí, quiero darte este amuleto y estas gemas. Espero que los encuentres útiles.";
		link.l1 = "¡Vaya! Bueno, gracias a ti también" + GetSexPhrase(", belleza", "") + ", no esperaba... Adiós, y sé feliz.";
		link.l1.go = "Node_134_End";
		break;

	case "Node_134_2":
		dialog.text = "Oh, " + GetSexPhrase("capitán", "señorita") + ", estoy contando contigo.";
		link.l1 = "...";
		link.l1.go = "exit";
		LAi_SetStayType(NPChar);
		break;

	case "Node_134_End":
		GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item);
		TakeNItems(pchar, "jewelry1", 15 + hrand(8));
		AddQuestRecord("JungleGirl", "2");
		AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("", ""));
		AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
		CloseQuestHeader("JungleGirl");
		LAi_CharacterDisableDialog(npchar);
		npchar.lifeDay = 0;
		DeleteAttribute(pchar, "GenQuest.EncGirl");
		DialogExit();
		break;

	case "Node_135":
		addMoneyToCharacter(pchar, -15000);
		ChangeCharacterComplexReputation(pchar, "nobility", 10);
		dialog.text = "Oh, " + GetSexPhrase("capitán", "Joven señorita") + ", me has ayudado por segunda vez hoy. Muchas gracias. Nunca olvidaré tu bondad.";
		link.l1 = "De nada. Di 'hola' a tu señora...";
		link.l1.go = "Node_135End";
		break;

	case "Node_135End":
		pchar.quest.LandEnc_RapersBadExit.over = "yes";
		NPChar.lifeDay = 0;
		sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "", "OpenTheDoors", -1.0);
		DeleteAttribute(pchar, "GenQuest.EncGirl");
		DialogExit();
		AddDialogExitQuest("pchar_back_to_player");
		break;

	case "ThanksForSave":
		if (npchar.city == "Bridgetown" || npchar.city == "Charles" || npchar.city == "FortFrance" || npchar.city == "Marigo" || npchar.city == "Panama" || npchar.city == "PortRoyal" || npchar.city == "SantoDomingo" || npchar.city == "Tortuga")
		{
			if (CheckAttribute(pchar, "GenQuest.EncGirl.Horse"))
			{
				iRnd = 2;
				pchar.GenQuest.EncGirl.BrothelCity = true;
			}
			else
			{
				iRnd = 1;
			}
		}
		else
		{
			iRnd = 1;
		}
		switch (rand(iRnd))
		{
		case 0:
			dialog.text = RandPhraseSimple("No deberías haberles dado dinero. Estaban mintiendo.", "No les creas. Son mentirosos. Y no deberías haberles dado dinero.");
			link.l1 = "¿Debería haberlos matado?";
			link.l1.go = "Node_200";
			break;
		case 1:
			dialog.text = "¡Oh, qué noble acción! Pude ver de inmediato que eras " + GetSexPhrase("un verdadero caballero", "una dama noble") + ". ¡Por favor, acepta mi más sincera gratitud. Espero que no hayas creído lo que decían estos granujas.";
			link.l1 = "Eso no importa. Una chica y una banda de pillos en la jungla, es simplemente tan natural...";
			link.l1.go = "Node_210";
			link.l2 = "¿De qué estás hablando, " + GetSexPhrase("linda", "querido") + "? ¿Cómo podría?";
			link.l2.go = "Node_211";
			break;
		case 2:
			dialog.text = "Gracias, capitán. Lamento haberte involucrado en este desagradable asunto, pero simplemente no tenía otra opción.";
			link.l1 = "Bueno, veo que también estás bastante atascado. ¿Cómo llegaste a esto?";
			link.l1.go = "Node_220";
			break;
		}
		break;

	case "Node_200":
		if (rand(1) == 0)
		{
			dialog.text = "Quizás... Nunca me dejarán en paz ahora.";
			link.l1 = "¡Vamos, vamos! Solo vuelve a casa, ya no tienes nada que temer.";
			link.l1.go = "Node_200End";
			link.l2 = "¡Vaya! ¿Por qué tienes tal aversión por los hombres?";
			link.l2.go = "Node_201";
		}
		else
		{
			dialog.text = "¡Por supuesto que no! Pero de todos modos, no me dejarán en paz. ¿Me llevarías al asentamiento de " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + ", ¿por favor?";
			link.l1 = "Solo vuelve a casa, no te tocarán. Deberían estar yendo a la taberna ahora mismo para desperdiciar su dinero fácil.";
			link.l1.go = "Node_200End";
			link.l2 = RandPhraseSimple("No te preocupes tanto, de verdad... Bueno, vamos.", "¿Eres tal cobarde, no es cierto? Está bien, te llevaré allí..");
			link.l2.go = "Node_121Next";
		}
		break;

	case "Node_201":
		dialog.text = "¡Oh no!, ¿qué estás diciendo? Conozco a estos canallas demasiado bien. Son antiguos compañeros de mi padre. Están tratando de localizar el lugar donde escondió sus tesoros.";
		link.l1 = "¿Y qué pasa con tu padre?";
		link.l1.go = "Node_202";
		break;

	case "Node_202":
		dialog.text = "Solía ser el capitán de un barco pirata. Recientemente murió... Todos fueron tan corteses durante el entierro, pero con el paso del tiempo, lo han olvidado, y poco después también su honor y honestidad. Es bueno que los haya notado. Tan pronto como descubran dónde están los tesoros, estoy perdido.";
		link.l1 = "Esa es una triste historia. Entonces, ¿planeas seguir escondiéndote de ellos?";
		link.l1.go = "Node_203";
		break;

	case "Node_203":
		dialog.text = "No puedo guardar joyas en casa, no tengo a nadie que me proteja. Así que voy por la noche a la cueva, cuando se acaba el dinero...\nLlévame, por favor, a la cueva, y te daré el dinero que les has dado ... Creo, los piratas no se arriesgarían a seguirnos mientras estés conmigo.";
		link.l1 = "Lo siento, cariño, pero tengo planes diferentes. Recogerás tu tesoro en otro momento.";
		link.l1.go = "Node_200End";
		link.l2 = "Está bien, vámonos, si no me temes.";
		link.l2.go = "Node_204";
		break;

	case "Node_204":
		dialog.text = "Sabes, por alguna razón, no estoy...";
		link.l1 = "Bueno, eso es una buena cosa.";
		link.l1.go = "Node_205";
		break;

	case "Node_205":
		Diag.TempNode = "Node_206";
		EncGirl_GenerateChest(npchar);
		Diag.CurrentNode = Diag.TempNode;
		AddDialogExitQuestFunction("EncGirl_GirlFollow");
		DialogExit();
		break;

	case "Node_206":
		Diag.TempNode = "Node_206";
		dialog.text = "Capitán, prometiste llevarme a la cueva.";
		link.l1 = "Vamos...";
		link.l1.go = "exit";
		break;

	case "Node_207":
		dialog.text = "Está bien, capitán, he tomado todo lo que necesitaba. Ahora podemos regresar.";
		link.l1 = "Veo que tus colegas no están cerca.";
		link.l1.go = "Node_208";
		break;

	case "Node_208":
		dialog.text = "Gracias a Dios. No necesito más problemas... Aquí, toma estos lingotes... eso debería ser suficiente para cubrir tus gastos. Ve solo, yo tomaré un camino diferente...";
		link.l1 = "Bien, buena suerte para ti, si no tienes miedo.";
		link.l1.go = "Node_209";
		break;

	case "Node_209":
		LAi_LocationDisableMonstersGen(pchar.location, false);
		i = makeint(sti(pchar.GenQuest.EncGirl.price) / 100.0);
		TakeNItems(pchar, "jewelry6", i);
		sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "", "OpenTheDoors", -1.0);
		npchar.lifeDay = 0;
		pchar.quest.EncGirl_RapersExit.win_condition.l1 = "ExitFromLocation";
		pchar.quest.EncGirl_RapersExit.win_condition.l1.location = pchar.location;
		pchar.quest.EncGirl_RapersExit.function = "EncGirl_MeetRapers";
		DialogExit();
		break;

	case "Node_200End":
		pchar.quest.LandEnc_RapersBadExit.over = "yes";
		AddDialogExitQuestFunction("EncGirl_GirlGoAway");
		DialogExit();
		break;

	case "Node_210":
		dialog.text = "Mmm, " + GetSexPhrase("capitán", "señorita") + ", no me gusta tu ironía.";
		link.l1 = "Estás listo para ir, " + GetSexPhrase("belleza", "querido") + ". Y más te vale apurarte a la ciudad, antes de que te persigan de nuevo.";
		link.l1.go = "Node_1End";
		break;

	case "Node_211":
		dialog.text = "¡Estaba tan agitada! ¿Podrías llevarme a la taberna en el asentamiento de " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + "? De lo contrario, me temo, van a perseguirme de nuevo.";
		link.l1 = "Tienes razón. Vamos...";
		link.l1.go = "Node_122Next";
		ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

	case "Node_220":
		dialog.text = "¡Oh, capitán, es una larga historia y no estoy seguro de que la encuentres interesante. Aunque... aún no lo haré sin tu ayuda ahora. ¿Podrías llevarme a la taberna en el asentamiento de " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + "¿Temo que simplemente no me dejen en paz?";
		link.l1 = "Lo siento, cariño, no tengo tiempo para eso. Tengo cosas que hacer.";
		link.l1.go = "Node_221";
		link.l2 = "¿Por qué eres tan reservado?";
		link.l2.go = "Node_222";
		break;

	case "Node_221":
		ChangeCharacterComplexReputation(pchar, "nobility", -2);
		AddDialogExitQuestFunction("EncGirl_GirlGoAway");
		DialogExit();
		break;

	case "Node_222":
		dialog.text = "¿Y cómo puedo no ser reservado, si todos intentan sacar provecho de mi desgracia?";
		link.l1 = "Bueno, entonces...";
		link.l1.go = "Node_223";
		break;

	case "Node_223":
		Diag.TempNode = "Node_224";
		pchar.GenQuest.EncGirl = "HorseToTavern";
		pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
		pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
		pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";
		Diag.CurrentNode = Diag.TempNode;
		AddDialogExitQuestFunction("EncGirl_GirlFollow");
		DialogExit();
		break;

	case "Node_224":
		dialog.text = "Capitán, prometiste llevarme a la taberna en el asentamiento de " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + ".";
		link.l1 = RandPhraseSimple("Recuerdo.", "No te preocupes, te veré allí.");
		link.l1.go = "exit";
		break;

	case "Node_225":
		chrDisableReloadToLocation = false;
		if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
		{
			if (CheckAttribute(pchar, "GenQuest.EncGirl.BrothelCity") && sti(pchar.rank) > 15)
			{
				dialog.text = "Hay demasiada gente allí. Vayamos a la sala privada. Necesito contarte algo.";
				link.l1 = LinkRandPhrase("Ya he hecho demasiado por ti, así que ahora te digo adiós.", "No deberías estar abusando de mi favor. Nos vemos, cariño.", "No necesito tus cuentos a partir de ahora, puedes averiguarlo todo por ti mismo.");
				link.l1.go = "Node_226";
				link.l2 = "Hmm, está bien. Tomaré las llaves del cantinero entonces.";
				link.l2.go = "Node_227";
			}
			else
			{
				dialog.text = "Muchas gracias por tu ayuda, capitán. No lo olvidaré.";
				link.l1 = "Oh, no te molestes. Solo intenta ser más cuidadoso en el futuro.";
				link.l1.go = "Node_226_1";
			}
		}
		else
		{
			if (CheckAttribute(pchar, "questTemp.FMQP") && pchar.questTemp.FMQP == "begin") // Addon-2016 Jason, французские миниквесты (ФМК)
			{
				dialog.text = "Muchas gracias por tu ayuda, capitán. No lo olvidaré.";
				link.l1 = "Oh, no te molestes. Solo trata de ser más cuidadoso en el futuro.";
				link.l1.go = "Node_226_1";
			}
			else
			{
				dialog.text = "Hay demasiada gente aquí. Vamos a la habitación privada. Necesito contarte algo.";
				link.l1 = LinkRandPhrase("Ya he hecho demasiado por ti, así que adiós ahora.", "No deberías estar abusando de mi favor. Nos vemos, cariño.", "No necesito tus historias a partir de ahora, puedes resolverlo todo tú mismo.");
				link.l1.go = "Node_226";
				link.l2 = "Hmm, está bien. Tomaré las llaves del cantinero entonces.";
				link.l2.go = "Node_227";
			}
		}
		break;

	case "Node_226":
		ChangeCharacterComplexReputation(pchar, "nobility", -1);
		sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "", "OpenTheDoors", -1.0);
		npchar.lifeDay = 0;
		DeleteAttribute(pchar, "GenQuest.EncGirl");
		DialogExit();
		AddDialogExitQuest("pchar_back_to_player");
		break;

	case "Node_226_1":
		ChangeCharacterComplexReputation(pchar, "nobility", 3);
		sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "", "OpenTheDoors", -1.0);
		npchar.lifeDay = 0;
		DeleteAttribute(pchar, "GenQuest.EncGirl");
		DialogExit();
		AddDialogExitQuest("pchar_back_to_player");
		break;

	case "Node_227":
		pchar.GenQuest.EncGirl = "EncGirl_ToTavern";
		pchar.quest.EncGirl_inRoom.win_condition.l1 = "location";
		pchar.quest.EncGirl_inRoom.win_condition.l1.location = npchar.city + "_tavern_upstairs";
		pchar.quest.EncGirl_inRoom.function = "EncGirl_SpeakInRoom";
		DialogExit();
		AddDialogExitQuest("pchar_back_to_player");
		break;

	case "Node_228":
		if (CheckAttribute(pchar, "GenQuest.EncGirl.Horse") && CheckAttribute(pchar, "GenQuest.EncGirl.BrothelCity") && sti(pchar.rank) > 15) // душещипательная история о невинной девочке попавшей в бордель
		{
			DeleteAttribute(pchar, "GenQuest.EncGirl.BrothelCity");
			dialog.text = "¿Entonces aún quieres escuchar mi historia?";
			link.l1 = "Hmm... Supongo que, es hora de que me vaya. ¡Adiós!";
			link.l1.go = "Node_232";
			link.l2 = "Bueno, escúpelo, entonces.";
			link.l2.go = "Node_233";
		}
		else
		{
			dialog.text = "Oh, mi noble salvador, finalmente puedo agradecerte de la única forma en que una mujer puede agradecer\nCuando te vi en la jungla, todo cambió dentro de mí. Olvidé a los violadores y las agudas hojas de palma que azotaban mis mejillas. Olvidé a dónde correr, por qué correr... Sólo te vi a ti. Y sólo te quería a ti... Y después de lo que has hecho por mí...";
			link.l1 = "¡Vaya! ¡Qué temperamento! Tus perseguidores seguramente sabían a quién perseguir...";
			link.l1.go = "Node_229"; // ГГ допрыгался - щас его попросту трахнут
			link.l2 = "Escucha, belleza, puedo entenderlo perfectamente, pero por favor, guarda tu temperamento para ti mismo.";
			link.l2.go = "Node_230"; // Послал в пешее эротическое путешествие
		}
		break;

	case "Node_229":
		dialog.text = "Ven a mí ahora, mi héroe...";
		link.l1 = "Oh, querido...";
		link.l1.go = "exit";
		pchar.GenQuest.EncGirl = "EncGirl_facking";
		DoQuestCheckDelay("PlaySex_1", 3.0);
		break;

	case "Node_230":
		dialog.text = "¡Oh! ¿Cómo... ¿Cómo te atreves?! ¡Qué bastardo! Una chica te agradeció con todo su corazón y alma, y tú...";
		link.l1 = "Bueno, si no estuvieras coqueteando tanto y echándole los tejos al primer hombre que encuentras, seguramente tendrías menos problemas. Ya no rescato a tales coquetas en la jungla...";
		link.l1.go = "Node_231";
		break;

	case "Node_231":
		dialog.text = "¡Nunca he escuchado tales palabras de nadie antes! ¡Y no las perdonaré! ¡Todavía me recordarás!";
		link.l1 = "Vete ya, ¿de acuerdo? Y trata de refrescarte un poco, a menos que quieras ser rescatado otra vez...";
		link.l1.go = "Node_231_1";
		break;

	case "Node_231_1":
		ChangeCharacterComplexReputation(pchar, "nobility", 1);
		sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "", "", -1.0);
		npchar.lifeDay = 0;
		DoQuestFunctionDelay("EncGirl_SetBerglar", 5.0);
		DialogExit();
		break;

	case "Node_232":
		ChangeCharacterComplexReputation(pchar, "nobility", -3);
		sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "", "OpenTheDoors", -1.0);
		npchar.lifeDay = 0;
		DeleteAttribute(pchar, "GenQuest.EncGirl");
		DialogExit();
		break;

	case "Node_233":
		pchar.GenQuest.EncGirl.Parents_City = GetQuestNationsCity(sti(pchar.GenQuest.EncGirl.nation));
		dialog.text = "Mi familia vive en el asentamiento de " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City) + ". Llegué aquí por casualidad, en el barco, en el que mi prometido me estaba llevando a sus padres, pero fue capturado por piratas. El barco fue llevado, y los pasajeros fueron desembarcados en la bahía no muy lejos de aquí. Mi prometido fue asesinado durante el abordaje del barco, y yo estuve gravemente enferma durante el tránsito por la jungla\nLa Señora del burdel me trató, y cuando me puse en pie, ella exigió trabajar el dinero gastado en el tratamiento. Fui una puta pero no agradé a la Madame, y entonces la Señora me vendió a unos bandidos para ganar al menos algo de dinero. La otra parte de la historia ya la conoces.";
		link.l1 = "¡Así que simplemente renuncia y regresa a casa! ¿Por qué permites que te traten como a un esclavo?!";
		link.l1.go = "Node_234";
		break;

	case "Node_234":
		dialog.text = "¡No puedo! Todas mis pertenencias: ropa decente, dinero, documentos... Todo está en el burdel en mi bolsa de viaje. La he escondido en la sala de citas. Y mientras esté vestido así, todos los marineros del puerto me perseguirán. ¿Y quién me llevará a bordo sin documentos ni dinero? Y ahora ni siquiera puedo mostrar mi cara en la ciudad, o me encerrarán en la cárcel...";
		link.l1 = "No debería ser un problema. Vamos. Te llevaré a casa yo mismo.";
		link.l1.go = "Node_235";
		link.l2 = "Espera aquí. Te traeré tu bolsa de viaje.";
		link.l2.go = "Node_236";
		if (sti(pchar.money) >= 5000)
		{
			link.l3 = "¿A quién le importan tus papeles? ¿Cuánto dinero necesitas para volver a casa?";
			link.l3.go = "Node_237";
		}
		break;

	case "Node_235":
		dialog.text = "Oh, gracias, capitán... Pero... sabes, no tengo nada con qué pagarte.";
		link.l1 = "¿De qué pago estás hablando? Vamos antes de que nos encuentren...";
		link.l1.go = "Node_240";
		break;

	case "Node_240":
		ReOpenQuestHeader("JungleGirl");
		AddQuestRecord("JungleGirl", "20");
		AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("", ""));
		AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City));
		AddQuestUserData("JungleGirl", "sBrothelCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city + "Gen"));
		AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);

		AddPassenger(pchar, npchar, false);
		SetCharacterRemovable(npchar, false);
		OfficersReaction("bad");
		chrDisableReloadToLocation = false;
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 3.0);
		pchar.quest.EncGirl_DeliveToParents.win_condition.l1 = "location";
		pchar.quest.EncGirl_DeliveToParents.win_condition.l1.location = pchar.GenQuest.EncGirl.Parents_City + "_town";
		pchar.quest.EncGirl_DeliveToParents.function = "EncGirl_DeliveToParents";
		DialogExit();
		break;

	case "Node_236":
		dialog.text = "Oh, capitán, sabes, nunca me atrevería a preguntar...";
		link.l1 = "No tengas miedo. Pronto volveré.";
		link.l1.go = "Node_239";
		break;

	case "Node_239":
		ReOpenQuestHeader("JungleGirl");
		AddQuestRecord("JungleGirl", "21");
		AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("", ""));
		AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);

		pchar.quest.EncGirl_GenerateBag.win_condition.l1 = "location";
		if (GetSummonSkillFromName(pchar, SKILL_FORTUNE) > rand(100))
		{
			pchar.GenQuest.EncGirl = "Bag_BrothelRoomUp";
			pchar.quest.EncGirl_GenerateBag.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_Brothel_room";
		}
		else
		{
			pchar.GenQuest.EncGirl = "Bag_BrothelRoom";
			pchar.quest.EncGirl_GenerateBag.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_SecBrRoom";
		}
		pchar.quest.EncGirl_GenerateBag.function = "EncGirl_GenerateLeatherBag";

		pchar.quest.EncGirl_GetBagFail.win_condition.l1 = "Timer";
		pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
		pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
		pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
		pchar.quest.EncGirl_GetBagFail.function = "EncGirl_GenQuest_GetBag";

		pchar.quest.EncGirl_ExitRoom.win_condition.l1 = "ExitFromLocation";
		pchar.quest.EncGirl_ExitRoom.win_condition.l1.location = pchar.location;
		pchar.quest.EncGirl_ExitRoom.function = "EncGirl_ExitTavernRoom";

		AddDialogExitQuest("OpenTheDoors");
		DialogExit();
		break;

	case "Node_240_1":
		pchar.quest.EncGirl_GetBagFail.over = "yes";
		dialog.text = "Oh, ya estaba preocupándome de que algo te hubiera sucedido.";
		if (CheckCharacterItem(pchar, "leather_bag"))
		{
			link.l1 = "¿Qué podría pasar? Aquí, toma tus cosas.";
			link.l1.go = "Node_241";
		}
		else
		{
			link.l1 = "Escucha, no he encontrado nada allí. ¿Estás seguro de que dejaste tu bolsa de viaje en la sala de citas?";
			link.l1.go = "Node_242";
		}
		break;

	case "Node_241":
		TakeNItems(pchar, "leather_bag", -1);
		dialog.text = "Gracias, " + GetSexPhrase("noble capitán", "chica noble") + ". Nunca olvidaré lo que has hecho por mí. No tengo mucho, pero por favor acepta este amuleto. Quizás, fue ese trasto el que salvó mi vida durante el ataque pirata.";
		link.l1 = "¡Gracias y buen viaje! Adiós ahora...";
		link.l1.go = "Node_243";
		break;

	case "Node_242":
		dialog.text = "¿Realmente encontraron mi bolsa?";
		if (sti(pchar.money) >= 5000)
		{
			link.l1 = "¿Cuánto dinero necesitas para volver a casa?";
			link.l1.go = "Node_237";
		}
		link.l2 = "Quizás lo hicieron. De todos modos, nuestros caminos se separan aquí ahora. ¡Adiós!";
		link.l2.go = "Node_244";
		break;

	case "Node_243":
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
		npchar.lifeDay = 0;
		TakeNItems(pchar, pchar.GenQuest.EncGirl.item, 1);
		AddQuestRecord("JungleGirl", "23");
		AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("", ""));
		AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("", ""));
		AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
		CloseQuestHeader("JungleGirl");
		ChangeCharacterComplexReputation(pchar, "nobility", 1);
		DeleteAttribute(pchar, "GenQuest.EncGirl");
		DialogExit();
		break;

	case "Node_244":
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
		npchar.lifeDay = 0;
		AddQuestRecord("JungleGirl", "23");
		AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
		CloseQuestHeader("JungleGirl");
		ChangeCharacterComplexReputation(pchar, "nobility", -5);
		DeleteAttribute(pchar, "GenQuest.EncGirl");
		DialogExit();
		break;

	case "Node_245":
		dialog.text = "Gracias, capitán. Sabes, es difícil creer que finalmente estoy en casa. Por favor, ven conmigo, te presentaré a mis padres.";
		link.l1 = "Escucha, " + GetSexPhrase("belleza", "cielito") + ", realmente no tengo tiempo para eso. ¿Quizás en otro momento?";
		link.l1.go = "Node_246";
		break;

	case "Node_246":
		dialog.text = "Qué lástima... Bueno, adiós entonces, y que el Señor te vigile. No tengo nada con qué recompensarte, pero por favor acepta este amuleto.";
		link.l1 = "¡Gracias! Corre a casa ahora, haz felices a tus padres!";
		link.l1.go = "Node_247";
		break;

	case "Node_247":
		sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "", "OpenTheDoors", -1.0);
		TakeNItems(pchar, pchar.GenQuest.EncGirl.item, 1);
		AddQuestRecord("JungleGirl", "24");
		AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("", ""));
		AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
		AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City));
		CloseQuestHeader("JungleGirl");
		npchar.lifeDay = 0;
		DeleteAttribute(pchar, "GenQuest.EncGirl");
		DialogExit();
		break;

	case "Node_248":
		break;

	case "Node_237":
		dialog.text = "Bueno, no lo sé... Quizás, tendré que esperar un viaje de paso. Pero no puedo pedirte dinero.";
		if (makeint(pchar.money) >= 5000)
		{
			link.l1 = "Ya veo. Está bien, toma 5000 pesos. Eso debería ser suficiente.";
			link.l1.go = "Node_237_1";
		}
		if (makeint(pchar.money) >= 25000)
		{
			link.l2 = "Entiendo. Está bien, toma 25000 pesos y vete a casa.";
			link.l2.go = "Node_237_2";
		}
		if (makeint(pchar.money) >= 35000)
		{
			link.l3 = "Ya veo. Bien, toma 35000 pesos. Eso debería ser suficiente para comprar la mejor cabina en el barco.";
			link.l3.go = "Node_237_3";
		}
		break;

	case "Node_237_1":
		AddMoneyToCharacter(pchar, -5000);
		ChangeCharacterComplexReputation(pchar, "nobility", -5);
		dialog.text = "Gracias, " + GetSexPhrase("noble capitán", "chica noble") + ". Nunca olvidaré lo que has hecho por mí.";
		link.l1 = "Buena travesía, entonces. Adiós...";
		link.l1.go = "Node_238";
		pchar.GenQuest.EncGirl = "EncGirlFack_GetMoney";
		break;

	case "Node_237_2":
		AddMoneyToCharacter(pchar, -25000);
		ChangeCharacterComplexReputation(pchar, "nobility", 1);
		dialog.text = "Gracias, " + GetSexPhrase("noble capitán", "chica noble") + ". Nunca olvidaré lo que has hecho por mí.";
		link.l1 = "Buen viaje, entonces. Adiós...";
		link.l1.go = "Node_238";
		break;

	case "Node_237_3":
		AddMoneyToCharacter(pchar, -35000);
		ChangeCharacterComplexReputation(pchar, "nobility", 2);
		dialog.text = "Gracias, " + GetSexPhrase("noble capitán", "chica noble") + ". Nunca olvidaré lo que has hecho por mí.";
		link.l1 = "Buen viaje, entonces. Adiós...";
		link.l1.go = "Node_238";
		break;

	case "Node_238":
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
		npchar.lifeDay = 0;
		if (pchar.GenQuest.EncGirl == "EncGirlFack_GetMoney")
		{
			AddSimpleRumour(RandPhraseSimple("¿Te has enterado? Una ramera intentaba colarse a bordo de un barco sin documentos, pero la atraparon y la llevaron de vuelta al burdel. Dicen que le debía a la madame una buena suma.",
											 "¿Te has enterado? Una ramera sin documentos fue capturada en el puerto. Dicen que había limpiado las arcas de la madame antes de intentar huir del burdel. Yo digo que esa fuente de suciedad y robo debió cerrarse hace tiempo. Incluso nuestros hijos están viendo esto y ¿qué pueden aprender de semejante ejemplo?"),
							sti(pchar.GenQuest.EncGirl.nation), 3, 1);
		}
		DeleteAttribute(pchar, "GenQuest.EncGirl");
		DialogExit();
		break;

	case "Node_250":
		dialog.text = "¡No arruines mi vida, capitán! Mi padre quiere que me case con el hijo del usurero, ese lechón inmundo... ¡solo porque su papá tiene un montón de dinero en sus cofres! Bueno, preferiría quedarme en la selva para ser devorada por bestias salvajes ¡que tomar una condena de por vida con él!";
		link.l1 = "¿Cuál es el problema con tu matrimonio, " + GetSexPhrase("belleza", "querido") + "? Detén al que busca casarte y sé feliz. Después de un tiempo, estarías feliz de casarte con ese mamón, pero podría ser demasiado tarde...";
		link.l1.go = "Node_251";
		break;

	case "Node_251":
		pchar.GenQuest.EncGirl.sLoverId = GenerateRandomName(sti(npchar.nation), "man");
		dialog.text = "¡No! No, capitán, yo amo " + pchar.GenQuest.EncGirl.sLoverId + " ¡y no me casaré con ningún otro hombre! ¡Y mi padre no quiere escuchar nada! Dice que " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + " solo es un visitante aquí, ¡así que nunca encontrará trabajo aquí y está destinado a morir en la pobreza, y yo con él! ¡Y yo iría con él hasta el fin del mundo, solo para estar a su lado! Llévame a él, ¡te lo ruego!";
		link.l1 = "Bien, vámonos. Supongo que averiguaré qué hacer contigo...";
		link.l1.go = "Node_252";
		break;

	case "Node_252":
		Diag.TempNode = "Node_253";
		ReOpenQuestHeader("JungleGirl");
		AddQuestRecord("JungleGirl", "9");
		AddQuestUserData("JungleGirl", "sText", pchar.GenQuest.EncGirl.FatherGen);
		AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
		AddQuestUserData("JungleGirl", "sLover", pchar.GenQuest.EncGirl.sLoverId);
		pchar.GenQuest.EncGirl.MeetSoldiers = 2;
		Diag.CurrentNode = Diag.TempNode;
		AddDialogExitQuestFunction("EncGirl_GirlFollow");
		DialogExit();
		break;

	case "Node_253":
		Diag.TempNode = "Node_253";
		dialog.text = "Capitán, prometiste llevarme a la colonia de " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + ".";
		link.l1 = RandPhraseSimple("Recuerdo.", "No te preocupes, te llevaré allí.");
		link.l1.go = "exit";
		break;

	case "Node_260":
		chrDisableReloadToLocation = false;
		if (rand(1) == 0)
		{
			dialog.text = RandPhraseSimple("Gracias, " + GetSexPhrase("capitán", "señorita") + ", una vez más. Realmente, te estoy tan agradecido.", "Muchas gracias, " + GetSexPhrase("capitán", "señorita") + ". No tengo idea de qué haría sin tu ayuda.");
			link.l1 = RandPhraseSimple("Esa debería ser una lección para ti. Bueno, mucha suerte...", "La próxima vez deberías tener más cuidado... Ahora corre a casa, tengo cosas que hacer.");
			link.l1.go = "Node_260End";
			link.l2 = "¿Cómo podrías ser tan imprudente? ¿Por qué te has adentrado en la jungla solo?";
			link.l2.go = "Node_13";
		}
		else
		{
			dialog.text = "Oh, " + GetSexPhrase("capitán", "joven dama") + ", realmente no tengo idea de cómo agradecerte.";
			link.l1 = "No fue nada. Siempre feliz de ayudar...";
			link.l1.go = "Node_261";
		}
		break;

	case "Node_260End":
		sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "", "OpenTheDoors", -1.0);
		npchar.lifeDay = 0;
		DeleteAttribute(pchar, "GenQuest.EncGirl");
		DialogExit();
		AddDialogExitQuest("pchar_back_to_player");
		break;

	case "Node_261":
		dialog.text = "¿Puedes llevarme a la taberna? Necesito esperar a mi tía y descansar un poco, esta 'aventura' ha drenado toda mi energía...";
		link.l1 = "No, " + GetSexPhrase("belleza", "cariño") + ", eso ciertamente es suficiente para mí. Tengo mucho que hacer.";
		link.l1.go = "Node_262";
		link.l2 = "" + GetSexPhrase("¡Oh, mujeres! ¿Hay algo que puedan hacer sin la ayuda de un hombre?", "¿Por qué eres tan impotente?") + "Vamos...";
		link.l2.go = "Node_263";
		break;

	case "Node_262":
		sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "", "", -1.0);
		npchar.lifeday = 0;
		DeleteAttribute(pchar, "GenQuest.EncGirl");
		DialogExit();
		AddDialogExitQuest("pchar_back_to_player");
		break;

	case "Node_263":
		Diag.TempNode = "Node_224";
		pchar.GenQuest.EncGirl = "HorseToTavern";
		pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
		pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
		pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";
		Diag.CurrentNode = Diag.TempNode;
		AddDialogExitQuestFunction("EncGirl_GirlFollow");
		DialogExit();
		AddDialogExitQuest("pchar_back_to_player");
		break;

	case "ThanksForHelp_1":
		Diag.TempNode = "ThanksAgain";
		if (makeint(Pchar.reputation.nobility) >= 80)
		{
			dialog.text = "Tengo algo de dinero... Por favor, acéptalo como muestra de mi gratitud!";
			Link.l1 = "Gracias. Intenta ser más cuidadoso la próxima vez.";
			Link.l1.go = "exit";
		}
		else
		{
			if (hrand(1) == 0)
			{
				dialog.text = "¡Le contaré a todos que me has salvado! ¡Que todos sepan " + GetSexPhrase("lo valiente y corajudo que eres", "la valiente y audaz dama que eres") + "!";
				Link.l1 = "Gracias. Y ahora deberías irte a casa.";
				Link.l1.go = "exit";
			}
			else
			{
				addMoneyToCharacter(Pchar, makeint(PChar.rank) * 100);
				dialog.text = "Tengo algo de dinero... Por favor, acéptalo como una muestra de mi gratitud!";
				Link.l1 = "Gracias. Intenta ser más cuidadoso la próxima vez.";
				Link.l1.go = "exit";
			}
		}
		break;

	case "ThanksAgain":
		Diag.TempNode = "ThanksAgain";
		dialog.text = "¡Le diré a todos que me has salvado! ¡Que todo el mundo sepa " + GetSexPhrase("lo valiente y corajudo que eres", "la valiente y audaz dama que eres") + "!";
		Link.l1 = "Gracias. Y ahora deberías irte a casa.";
		Link.l1.go = "exit";
		break;
	}
}
