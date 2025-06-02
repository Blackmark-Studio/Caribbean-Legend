void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sGroup;
	bool bOk, bOk1;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	int iTemp = sti(npchar.EncQty);
	string sTemp = "Gang" + locations[FindLocation(npchar.location)].index + "_";

	switch (Dialog.CurrentNode)
	{
	case "exit":
		Diag.CurrentNode = Diag.TempNode;
		DialogExit();
		break;

	case "exit_Robbed":
		int iMoney = makeint(makeint(Pchar.money) / 20) * 10;
		AddMoneyToCharacter(pchar, -iMoney);
		AddSimpleRumour(LinkRandPhrase("¿Te has enterado? El ladrón " + GetFullName(npchar) + " encontró una nueva víctima. Un capitán se asustó y le timó. Dicen que le dio " + FindRussianMoneyString(iMoney) + ", he-he... ",
									   "Sí, capitán. " + GetFullName(pchar) + ", Ya he oído que tuviste que pagar " + FindRussianMoneyString(iMoney) + ", para comprar a un bandido, " + GetFullName(npchar) + ". ¡Eso es lo que yo llamo mala suerte! ¡Ja, ja, ja!",
									   "¿Has oído que los bandidos de la zona atacaron a un capitán? ¡Se lo robaron todo, perdió " + FindRussianMoneyString(iMoney) + "!"),
						sti(npchar.nation), 5, 1);
		for (i = 0; i < iTemp; i++)
		{
			sld = CharacterFromID(sTemp + i);
			sld.LifeDay = 0;
			LAi_SetWarriorTypeNoGroup(sld);
			sld.Dialog.CurrentNode = "OnceAgain";
			LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld) - 1, true, "LandEnc_RaidersBeforeDialog");
		}
		DialogExit();
		break;

	case "exit_fight":
		sGroup = "RaidersGroup_" + locations[FindLocation(npchar.location)].index;
		for (i = 0; i < iTemp; i++)
		{
			sld = CharacterFromID(sTemp + i);
			LAi_SetWarriorTypeNoGroup(sld);
			LAi_group_MoveCharacter(sld, sGroup);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, false);
		}
		LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck(sGroup, "LandEnc_RaidersAfrer");
		DialogExit();
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "exit_RunFight":
		AddSimpleRumour(LinkRandPhrase(RandPhraseSimple("¿Te has enterado? Ese bandido " + GetFullName(npchar) + " por fin ha encontrado justicia. Él y sus chicos trataron de robar " + GetSexPhrase("a cierto capitán, pero resultó ser", "a cierta dama capitana, pero resultó ser") + " un hueso duro de roer. ¡Así que nuestro querido ladrón se cagó en los pantalones, ja, ja! Eso le servirá de lección. Robar a los granjeros locales es una cosa, ¡pero un capitán valiente es una historia diferente!",
														"Gracias, capitán " + GetFullName(pchar) + ". Te has ocupado finalmente de la banda de ese bandido " + GetFullName(npchar) + ". Los bribones de esa banda eran realmente como un grano en el culo de todos. Teníamos miedo incluso de enviar mensajeros a la granja a por leche, podían interceptarlos y robarnos todo el dinero."),
									   "¿Te has enterado? " + GetSexPhrase("Finalmente, cierto capitán", "Por fin, cierta señora capitana") + " detuvo al bribón " + GetFullName(npchar) + ", que estaba campando por la selva, aterrorizando a todos los granjeros. Espero, que esos les impida maquinar sus sucias acciones durante el tiempo suficiente...",
									   "¿Has oído que el bandido " + GetFullName(npchar) + " y sus chicos intentaron robar " + GetSexPhrase("a cierto capitán", "a cierta dama capitana") + "? ¡Bah! ¡Nada de eso! Ese capitán resultó ser un hueso duro de roer. Dicen que persiguió a esos ladrones por toda la selva como un tiburón persigue a un banco de sardinas. Gracias a Dios, todavía hay gente que puede dar la cara por nosotros cuando las autoridades no hacen nada, están demasiado ocupadas con sus oscuras hazañas..."),
						sti(npchar.nation), 5, 1);
		for (i = 0; i < iTemp; i++)
		{
			sld = CharacterFromID(sTemp + i);
			LAi_type_actor_Reset(sld);
			LAi_ActorAfraid(sld, Pchar, true);
			sld.Dialog.CurrentNode = "GetTheHellOut";
		}
		DialogExit();
		break;

	case "exit_noFight":
		for (i = 0; i < iTemp; i++)
		{
			sld = CharacterFromID(sTemp + i);
			sld.LifeDay = 0;
			LAi_SetWarriorTypeNoGroup(sld);
			sld.Dialog.CurrentNode = "GetLost";
			LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld) - 1, true, "LandEnc_RaidersBeforeDialog");
		}
		DialogExit();
		break;

	case "First Time":
		for (i = 0; i < iTemp; i++)
		{
			sld = CharacterFromID(sTemp + i);
			LAi_type_actor_Reset(sld);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, false);
		}
		dialog.text = LinkRandPhrase(LinkRandPhrase("¡Quédate donde estás y suelta tu arma! ¡Tu dinero o tu vida!", "Quédate donde estás, " + GetSexPhrase("viajero", "chica") + "!) ¡No toques tu arma y no hagas movimientos bruscos!", "Quédate donde estás, " + GetSexPhrase("viajero", "chica") + "¡Esta es una carretera de peaje. Si quieres pasar, pagas el peaje."), LinkRandPhrase("Oye, " + GetSexPhrase("compañero", "chica") + "¡ No tan rápido! Quiero ver cuán pesada es tu bolsa.", "¿Podrías acercarte, amigo? Quiero escuchar el tintineo del oro en tu bolsa.", "Espera, " + GetSexPhrase("compañero", "chica") + ". Yo y los chicos apostamos sobre cuánto oro cabrá en tu bolsa. Ahora debemos comprobarlo antes de que las cosas se pongan violentas."), "No te apresures, " + GetSexPhrase("viajero", "querida") + "¡ Tengamos una charla de corazón a corazón, lo haremos?");
		Link.l1 = LinkRandPhrase(LinkRandPhrase("¿Por qué estás diciendo estas tonterías?", "¿Qué pasa?", "¿De qué estás hablando?"), "¿Qué quieres decir?", "¿Justo qué estás insinuando?");
		Link.l1.go = "Node_2";
		Link.l2 = LinkRandPhrase(LinkRandPhrase("¡¿Bandidos?! ¡Excelente, estaba deseando una pelea!", "¡Oh, sois bandidos! ¿Escondiéndoos de la justicia, supongo? Bueno, parece que la justicia acaba de llegar para vosotros...", "¿No te han enseñado que molestar a los extraños con tus tonterías es una señal de malos modales? Parece que tengo que enseñarte esa lección..."), LinkRandPhrase("¡Oh, eres un insolente, no es así?! ¡Espero que tu espada sea tan afilada como tu lengua!", "Veo que eres un maestro de tu lengua, espero que también seas un maestro de tu espada.", "¡Oh, bandidos! A tantos de los tuyos se les ha colgado, pero aún así no puedes dejar de caminar directamente hacia la horca."), LinkRandPhrase(RandPhraseSimple("¡Oh, bandidos! Sabes, normalmente no pierdo palabras con tu tipo!", "¡Qué atrevido! Huele como un montón de mierda humeante y aún se atreve a dirigirse a una persona decente " + GetSexPhrase("chico", "chica") + "."), "No perderé palabras contigo, ¡pero encontrarás que mi pistola es muy elocuente!", "¡Bandidos otra vez! Bueno, no te prometo la horca, pero seguro que puedo hacerte un par de agujeros en la barriga!"));
		Link.l2.go = "CheckSkills";
		Link.l3 = LinkRandPhrase("¿Y sabes que un grupo de patrulla me sigue de cerca? Solo tengo que darles un silbido y tú estás acabado.", RandPhraseSimple("¿Sabes?, puedo llamar a la patrulla, ¿no te da miedo eso? Están cerca. Supongo, buscándote a ti.", "Una patrulla ha sido enviada recientemente para encontrarte, y estarán aquí en cualquier momento. Estás corriendo un gran riesgo."), RandPhraseSimple("Te aconsejaría que corras tan rápido como puedas. Una patrulla se dirige hacia aquí, acabo de hablar con su oficial.", "Con gusto continuaría nuestra conversación, pero me temo que la patrulla con la que acabo de encontrarme, no permitirá que nuestro conocimiento se convierta en una amistad cercana."));
		Link.l3.go = "Node_3";
		break;

	case "Node_2":
		dialog.text = LinkRandPhrase(LinkRandPhrase("¡No te hagas el tonto! ¡Dinero contante y sonante y tal vez entonces te dejaré ir!", "¿No has oído hablar del pago de viaje? Si no te separas de tu oro, te separarás de tu cabeza!", "Je, esta aventura ordinaria te costará una bolsa... si no me enfado."), RandPhraseSimple("Es muy simple. Nos das todo tu oro y luego eres libre de irte, o te quedas aquí, y nos llevamos todo tu oro, de todos modos. Pero creo que lo último no es lo que te gustaría, je-je.", "¡No finjas que no entiendes! ¡Dame tu bolsa si no quieres que la tome de tu cadáver!"), "Te lo explicaré, si eres tan torpe. Me das todo tu dinero, si valoras tu vida.");
		Link.l1 = "¡Maldita sea, granuja! Solo tengo " + makeint(makeint(Pchar.money) / 20) * 10 + " pesos.";
		Link.l1.go = "CheckMoney";
		Link.l2 = LinkRandPhrase(LinkRandPhrase("¿Quieres mi dinero? ¡Ven a buscarlo y veré cuánto vales!", "¡Cómo te atreves, patán! ¡Te enseñaré una lección de buenos modales!", "¡Qué confianza en sí mismo! Bueno, veamos cómo te defiendes contra un verdadero " + GetSexPhrase("lobo de mar", "Loba de los mares") + "¡!"), LinkRandPhrase("¡Deberías ser azotado por tal ultraje!", "¡Vosotros granujas! Rezad a vuestros demonios por un lugar cálido en el infierno!", "¡Deberías haber sido colgado hace mucho tiempo, pajarraco de horca! Bueno, parece que tendré que manchar mi sable con tu sangre!"), RandPhraseSimple("¿Y qué te hace pensar que te daré mi dinero?", "¿Y no has notado que estoy bien armado y que no vine aquí para un simple paseo?"));
		Link.l2.go = "CheckSkills";
		break;

	case "Node_3":
		bOk = makeint(pchar.reputation.nobility) < 11 || makeint(pchar.reputation.nobility) > 90;
		if (bOk || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) == 100 || CheckCharacterPerk(pchar, "Trustworthy") || CheckCharacterPerk(pchar, "SeaDogProfessional"))
		{
			dialog.text = RandPhraseSimple("¡Maldita sea! Está bien, puedes irte. ¡Pero ni siquiera pienses en hacer ruido mientras estás aquí!", "Esta vez tuviste suerte, ¡pero la próxima vez nos deberás el doble! No olvides recordárnoslo, je-je.");
			Link.l1 = RandPhraseSimple("Pero por supuesto.", "Corre ya, mientras aún puedas.");
			Link.l1.go = "Exit_NoFight";
		}
		else
		{
			bOk = makeint(pchar.reputation.nobility) < 51 && makeint(pchar.reputation.nobility) > 41; // Captain Beltrop, 23.01.21 - жесть!!! Надо было всего лишь убрать единичку!
			if (!bOk || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 35)
			{
				dialog.text = RandPhraseSimple("Te mataremos en silencio, ni siquiera soltarás un chillido.", "¡Maldita sea! Tendremos que matarte rápido antes de que puedas dar la alarma.");
				Link.l1 = "Bueno, este es tu funeral. Te lo advertí.";
				Link.l1.go = "Exit_Fight";
			}
			else
			{
				dialog.text = RandPhraseSimple("¿Y por qué debería importarme tu patrulla? Les estoy pagando. Así que, dame tu bolsa y deja de abrir tu boca.", "¿Crees que puedes asustarme? Yo mismo soy 'la patrulla' para los como tú en esta selva. ¡Nadie aún ha salido sin pagar una tarifa!");
				Link.l1 = "¡Maldita sea, granuja! Solo tengo " + makeint(makeint(Pchar.money) / 20) * 10 + " pesos.";
				Link.l1.go = "CheckMoney";
				Link.l2 = RandPhraseSimple(LinkRandPhrase("He-h, no voy a obedecer órdenes de un cobarde como tú.", "¡Haré un par de agujeros nuevos en tu calavera por tal impertinencia! Solo para ventilar un poco tu cerebro.", "¡Tal descaro no quedará impune!"), "No deberías haber hecho eso...");
				Link.l2.go = "CheckSkills";
			}
		}
		break;

	case "CheckSkills":
		bool isStrong = (GetCharacterSkillToOld(Pchar, "FencingL") >= 7) || (GetCharacterSkillToOld(Pchar, "FencingS") >= 7) || (GetCharacterSkillToOld(Pchar, "FencingH") >= 7);
		bool z_ok = (isStrong) && (makeint(Pchar.Rank) >= 8) && (Makeint(PChar.reputation.nobility) <= 30); // Captain Beltrop & mitrokosta, 23.01.21 проверяем на оружие (новый вариант)
		if (z_ok || CheckCharacterPerk(pchar, "SeaDogProfessional"))
		{
			Diag.TempNode = "GetLost";
			dialog.text = LinkRandPhrase(RandPhraseSimple("Eh, no te emociones tanto, " + GetSexPhrase("compañero", "muchacha") + "¡Solo estaba bromeando! ¡Puedes seguir tu camino!", "Está bien, he cambiado de opinión. Puedes irte, si eres tan formidable."), "¿Qué, un " + GetSexPhrase("'valiente capitán'", "'chica militante'") + "¿Otra vez? Bueno, ve en paz...", "Relájate, " + GetSexPhrase("compañero", "chica") + ". Verás, nos equivocamos, " + GetSexPhrase("pensábamos que eras un comerciante", "pensábamos que eras un mercader") + ". Puedes irte.");
			Link.l1 = LinkRandPhrase(LinkRandPhrase("¡Bueno, hasta que nos encontremos de nuevo!", "Deberías dejar de robar a la gente, mientras aún puedes.", "Está bien, pero si alguna vez te veo de nuevo..."), RandPhraseSimple("La próxima vez presta atención a quién estás amenazando, canalla.", "Gracias a Dios que hoy estoy de buen humor."), RandPhraseSimple("Este comercio criminal seguramente te matará al final. Adiós.", "Esa es una decisión sabia. Bueno, ¡buena suerte!"));
			Link.l1.go = "Exit_NoFight";
			Link.l99 = LinkRandPhrase("¡No, compañero. Ahora te enseñaré algunas buenas maneras!", "¿Oh, te asustaste? Bueno, uno debe responder por sus actos, ¿verdad?", "¡No! ¡Ahora no me calmaré hasta que te despelleje vivo!");
			Link.l99.go = "GetTheHellOut";
		}
		else
		{
			dialog.text = LinkRandPhrase("¡Y podrías haber ido en paz! ¡Ahora solo puedes culparte a ti mismo!", "¡No deberías haberlo empezado, granuja! ¡Ahora vas a morir como un perro!", "¡Ah bien! ¡Te desgarraré en pedazos! ¡Cortaré el hígado y lo daré de comer a los perros!");
			Link.l1 = RandPhraseSimple("¡Meteré tus palabras de vuelta en tu garganta!", "¿A quién amenazas, escoria?!");
			Link.l1.go = "Exit_Fight";
		}
		break;

	case "CheckMoney":
		if (makeint(makeint(Pchar.money) / 20) * 10 >= makeint(Pchar.rank) * 100)
		{
			Diag.TempNode = "OnceAgain";
			dialog.text = LinkRandPhrase(RandPhraseSimple("¡Bien! Dámelo y lárgate!", "No mucho, pero aún mejor que nada. ¡Es bueno tratar con una persona inteligente! Eres libre de irte."), "¡Esa es una historia diferente! Como decía mi amigo 'siempre es bueno escuchar a alguien que es listo, pero hablar con el tonto es mucho mejor'! ¡Je-je!", "A cambio de tu oro te daré un consejo, no deberías caminar en la selva, si eres " + GetSexPhrase("tal cobarde. Bebe tu ron en la taberna, para que tú y tu bolsa permanezcan seguros!", "una moza. Ser robado no es lo peor que te podría haber pasado.") + ".");
			Link.l1 = "¡Maldito seas!";
			Link.l1.go = "Exit_Robbed";
		}
		else
		{
			dialog.text = "Supongo que estás intentando engañarme. ¡No te preocupes, te haré cosquillas con mi cuchillo, y quizás algo caiga!";
			Link.l1 = "¡Maldita sea!";
			Link.l1.go = "Exit_Fight";
		}
		break;

	case "OnceAgain":
		Diag.TempNode = "OnceAgain";
		dialog.text = LinkRandPhrase("¿Tú otra vez? ¡Vuelve a casa con tu madre, antes de que me enoje contigo!", "¿Qué? ¿Aún no me has dado todo tu oro? ¡Ja-ja!", "Mira, " + GetSexPhrase("compañero", "chica") + ", ¡Estoy harto de ti! ¡Vete de mi vista mientras aún estás vivo!");
		Link.l1 = "Sí, ya me estoy yendo.";
		Link.l1.go = "Exit";
		Link.l2 = "Pensé que no sería justo. Por lo tanto, decidí poner las cosas en orden...";
		Link.l2.go = "Exit_Fight";
		break;

	case "GetLost":
		Diag.TempNode = "GetLost";
		dialog.text = LinkRandPhrase("¿Qué más necesitas? ¡Ya hemos acordado que te vas!", "Déjame en paz, " + GetSexPhrase("camarada", "muchacha") + ". Yo me ocupo de mis propios asuntos, y tú tienes los tuyos, ¡y no deberíamos intentar llevarnos bien!", "Vete ahora, " + GetSexPhrase("compañero", "chica") + "¡Maldita sea, realmente estás dispuesto a regalar todo tu dinero?");
		Link.l1 = "Sí, ya me estoy yendo.";
		Link.l1.go = "Exit";
		Link.l2 = "¡He recordado que no dijiste adiós! Así que digamos un adiós como es debido...";
		Link.l2.go = "Exit_Fight";
		break;

	case "GetTheHellOut":
		Diag.TempNode = "GetTheHellOut";
		dialog.text = LinkRandPhrase("¡Dejadme en paz! ¡Ayudadme! ¡Quiero vivir!", "¡Ayúdame! " + GetSexPhrase("Él es un maniaco", "Ella es una maníaca") + "¡No me mates!", "¡Perdóname! ¡Solo soy un humilde bandido! ¡Soy demasiado joven para morir!");
		Link.l1 = LinkRandPhrase(LinkRandPhrase("¡Si te hubieras quedado en casa, habrías vivido!", "¡Deberías haber pensado en eso antes!", "¡Deberías haber sabido que siempre hay consecuencias!"), "Tarde o temprano, esto tenía que suceder.", "¡Demasiado tarde para arrepentirse, ahora lucha, escoria!");
		Link.l1.go = "exit_Fight";
		break;
	}
}
