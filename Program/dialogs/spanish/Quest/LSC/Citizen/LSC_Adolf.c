// Адольф Барбье - авантюрист
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
		{
			dialog.text = "No quiero hablar contigo. Atacas a civiles pacíficos sin razones y los provocas a pelear. ¡Piérdete!";
			link.l1 = "Mm...";
			link.l1.go = "exit";
			break;
		}
		if (npchar.quest.meeting == "0")
		{
			dialog.text = "Hola, hola... No te he visto antes. ¿Recientemente?";
			link.l1 = "¿Te refieres a recientemente en la Isla? Sí, tienes razón. Mi nombre es " + GetFullName(pchar) + ", un marinero y un aventurero.";
			link.l1.go = "meeting";
			npchar.quest.meeting = "1";
		}
		else
		{
			dialog.text = "¡Ah, " + GetFullName(pchar) + "! " + TimeGreeting() + ". ¿Quieres algo?";
			link.l1 = LinkRandPhrase("¿Tienes algo interesante que decir?", "¿Ha ocurrido algo nuevo en la isla?", "¿Me contarás los últimos chismes?");
			link.l1.go = "rumours_LSC";
			link.l2 = "Quiero hacerte unas preguntas sobre la isla.";
			link.l2.go = "int_quests"; // информационный блок
			link.l5 = "Solo quería saber cómo te va. ¡Nos vemos!";
			link.l5.go = "exit";
		}
		NextDiag.TempNode = "First time";
		break;

	case "meeting": // первая встреча
		dialog.text = "Ja, igual que yo. Aunque yo no soy marinero, mi pasión por las aventuras me ha llevado aquí. Ahora tengo que pudrirme en este cementerio de barcos como los demás. Por cierto, me llamo Adolf Barbier.";
		link.l1 = "Fue un placer conocerte, Adolf. Nos vemos.";
		link.l1.go = "exit";
		link.l2 = LinkRandPhrase("¿Tienes algo interesante que decir?", "¿Ha sucedido algo nuevo en la isla?", "¿Me contarás los últimos chismes?");
		link.l2.go = "rumours_LSC";
		link.l3 = "Quiero hacerte algunas preguntas sobre la isla.";
		link.l3.go = "int_quests"; // информационный блок
		NextDiag.TempNode = "First time";
		break;

	//----------------------------------Адольф Барбье----------------------------------------
	case "Adolf":
		dialog.text = "¿Por qué demonios has invadido mi morada sin mi permiso?";
		link.l1 = "Estás mostrando malos modales a tu invitado, Adolf. Y tengo un negocio para ti.";
		link.l1.go = "Adolf_1";
		break;

	case "Adolf_1":
		dialog.text = "¡No hago negocios con personas que no conozco! ¡Fuera!";
		link.l1 = "¿Así nomás? ¿Entonces haces negocios con los Narvales, pero no conmigo? Vergüenza...";
		link.l1.go = "Adolf_2";
		break;

	case "Adolf_2":
		dialog.text = "¿De qué hablas, bufón? ¿Qué asunto tienes con los Narvales? ¡Es tu última oportunidad para largarte de aquí o tendré que echarte yo mismo!";
		link.l1 = "No tienes agallas para hacerlo, 'maestro del lanzamiento'... Escúchame ahora. ¿Dónde está el stutzen que vas a usar para disparar al almirante? ¿Me lo dirás tú mismo o debería ser más persuasivo?";
		link.l1.go = "Adolf_3";
		break;

	case "Adolf_3":
		dialog.text = "¿Qué? ¿Qué stutzen? ¿Qué almirante? ¿Estás loco, camarada? He vendido mi stutzen y ya no lo tengo. Y no es asunto tuyo a quién se lo vendí. Me importa un carajo lo que hagan con él. Y no voy a disparar a nadie, ni almirantes, ni generales. ¿Me entiendes, cabrón?";
		link.l1 = "Solo entiendo que eres un mentiroso y un asesino, Adolf. Sé que no lo vendiste, sino que lo redimiste. También sé que has recibido una gran suma para pagar tus deudas y comprar esta cabaña...";
		link.l1.go = "Adolf_4";
		break;

	case "Adolf_4":
		dialog.text = "¡Este es mi dinero, imbécil! ¡Lo he ganado! ¡Y he vendido mi stutzen!";
		link.l1 = "Eres un mentiroso, Adolf. Fuiste contratado por los Narvales para disparar al almirante. Te han dado dinero para redimir tu stutzen. También han pagado por este lugar. Sabes mejor que yo que el bauprés detrás de esta puerta es el único lugar en la isla desde donde se puede disparar al balcón trasero de la residencia dShark.";
		link.l1.go = "Adolf_5";
		break;

	case "Adolf_5":
		dialog.text = "¡Estás loco, imbécil! ¡Debes ser aislado de inmediato! He estado esperando por esta cabaña durante medio año antes de que Sessile se fuera de aquí...";
		link.l1 = "Basta. Te registraré a ti y a tu camarote, encontraré el stutzen y algunas pruebas más, estoy seguro de ello. Y luego iremos juntos al Shark. Se alegrará de mirarte a los ojos.";
		link.l1.go = "Adolf_6";
		break;

	case "Adolf_6":
		dialog.text = "¡Ah, eres un bastardo enfermo! ¡Prefiero morir antes que dejar que alguna escoria loca toque mis pertenencias!";
		link.l1 = "Entonces los tocaré sin tu permiso...";
		link.l1.go = "Adolf_7";
		break;

	case "Adolf_7":
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // разрешить драться
		chrDisableReloadToLocation = true;										   // закрыть локацию
		DialogExit();
		LAi_SetWarriorType(npchar);
		ChangeCharacterAddressGroup(npchar, pchar.location, "barmen", "stay");
		LAi_group_MoveCharacter(npchar, "EnemyFight");
		LAi_SetImmortal(npchar, false);
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "LSC_AdolfDie");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

		//--------------------------------------- блок вопросов и ответов ---------------------------------------------
	case "int_quests":
		dialog.text = "Bueno, hablemos. ¿Qué quieres saber?";
		if (!CheckAttribute(npchar, "quest.answer_1"))
		{
			link.l1 = "¿Cómo llegaste aquí?";
			link.l1.go = "ansewer_1";
		}
		if (!CheckAttribute(npchar, "quest.answer_2"))
		{
			link.l2 = "¿Qué puedes contarme sobre los clanes locales?";
			link.l2.go = "ansewer_2";
		}
		if (!CheckAttribute(npchar, "quest.answer_3"))
		{
			link.l3 = "¿Has explorado el anillo exterior de barcos?";
			link.l3.go = "ansewer_3";
		}
		if (!CheckAttribute(npchar, "quest.answer_4"))
		{
			link.l4 = "¿La isla tiene alguna conexión con Cuba o el Continente?";
			link.l4.go = "ansewer_4";
		}
		link.l10 = "Sin preguntas. Perdón...";
		link.l10.go = "exit";
		break;

	case "ansewer_1":
		dialog.text = "Encontré un manuscrito de un marinero - Alvarado, era español. Describió la Isla con muchos detalles. Mencionó algunos barcos interesantes - San Agustín, San Gerónimo y Tártaro. Todos ellos formaban parte del escuadrón de Betancourt, desaparecido hace más de cincuenta años.\nHice una investigación sobre esa expedición. Resulta que había un cuarto barco llamado Santa Ana que transportaba el tesoro del escuadrón, ¡una pila de doblones! Además, los barcos tenían mineral de oro en sus bodegas. Decidí encontrar la Isla.\nHice un trato con un capitán que conocía y zarpamos en su goleta. Está claro cómo terminó la historia, supongo. Encontramos la Isla, los barcos de Betancourt, incluso a su descendencia - vive aquí, se llama Antonio de Betancourt. Pero no logré dejar este lugar.\nLa goleta fue destrozada por los arrecifes, mi compañero murió y yo, junto con otros sobrevivientes, logramos llegar aquí. La peor parte es que no encontré lo que buscaba - ni el tesoro de Santa Ana, ni el mineral de oro.";
		link.l1 = "También he leído las notas de Alvarado. Historia intrigante.";
		link.l1.go = "int_quests";
		npchar.quest.answer_1 = "true";
		break;

	case "ansewer_2":
		dialog.text = "Los Rivados son condenados paganos escoria. Son descendientes de esclavos negros, traídos aquí por de Betancourt desde África. Aunque han aprendido a usar espadas y mosquetes de los blancos, siguen siendo salvajes\nLos Narvales son buena gente, inteligentes y decentes luchadores. Entre ellos hay artesanos destacados. Conozco a muchos de ellos. Quizás algún día me una a su clan\nLos piratas son un dolor en el trasero, maldición para ellos. No los llamamos, pero han llegado, capturaron nuestros suministros y se atrevieron a vendernos nuestra propia comida. ¡Bastardos!, ¿verdad? Qué pena que no podamos echarlos y tengamos que convivir con su presencia.";
		link.l1 = "Interesante...";
		link.l1.go = "int_quests";
		npchar.quest.answer_2 = "true";
		break;

	case "ansewer_3":
		dialog.text = "Claro. Un hombre tiene que ganar dinero. Malditos piratas exigen oro, pesos o diferentes objetos de valor por la comida. La venden mucho más barata a locales como yo que a los clanes, pero no es una obra de caridad de todas formas. Gracias a Dios, hay suficientes barcos en el anillo exterior para saquear, muchos de ellos aún permanecen intactos desde su naufragio. Una actividad interesante, aunque peligrosa: puedes caer en la bodega inundada, romperte los huesos, quedarte atrapado en las cuerdas, ser aplastado por partes de madera o encontrarte con cangrejos gigantes - a menudo visitan las bodegas allí afuera.";
		link.l1 = "Veo...";
		link.l1.go = "int_quests";
		npchar.quest.answer_3 = "true";
		break;

	case "ansewer_4":
		dialog.text = "Ay, no es así. Dicen que hace mucho tiempo los bucaneros y contrabandistas de Cuba solían visitar este lugar, intercambiando provisiones por oro y bienes. Incluso los Narvales visitaban los asentamientos. Pero eso es historia ahora. Nadie se arriesgaría a navegar en frágiles y pequeñas embarcaciones. Las tormentas destruyen pequeñas embarcaciones en un segundo y no tenemos mejores barcos aquí.";
		link.l1 = "Veo...";
		link.l1.go = "int_quests";
		npchar.quest.answer_4 = "true";
		break;
		// <-- блок вопросов и ответов

		//----------------------------------------- специальные реакции -----------------------------------------------
		// обнаружение ГГ в сундуках
	case "Man_FackYou":
		dialog.text = LinkRandPhrase("¿Qué estás haciendo ahí, eh? ¡Ladrón!", "¡Solo mira eso! En cuanto me perdí en la contemplación, ¡decidiste revisar mi cofre!", "¿Has decidido revisar mis cofres? ¡No te saldrás con la tuya!");
		link.l1 = "¡Mierda!";
		link.l1.go = "fight";
		break;

	case "Woman_FackYou":
		dialog.text = "¿Qué?! ¿Decidiste revisar mis cofres? ¡No te saldrás con la tuya!";
		link.l1 = "¡Chiquilla tonta!";
		link.l1.go = "exit_setOwner";
		LAi_group_Attack(NPChar, Pchar);
		break;

	case "fight":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		LAi_SetOwnerTypeNoGroup(npchar);
		LAi_group_Attack(NPChar, Pchar);
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "exit_setOwner":
		LAi_SetOwnerTypeNoGroup(npchar);
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	// замечание по обнажённому оружию
	case "LSCNotBlade":
		dialog.text = LinkRandPhrase("Escucha, será mejor que guardes tu arma. Me pone nervioso.", "Sabes, correr con una hoja no se tolera aquí. Llévatela.", "Escucha, no juegues al caballero medieval corriendo con una espada. Guárdala, no te queda bien...");
		link.l1 = LinkRandPhrase("Bien.", "Está bien.", "Como dices...");
		link.l1.go = "exit";
		NextDiag.TempNode = "First Time";
		break;

	case "CitizenNotBlade":
		if (loadedLocation.type == "town")
		{
			dialog.text = NPCharSexPhrase(NPChar, "Escucha, soy ciudadano de la ciudad y te pediría que mantuvieras la espada en su lugar.", "Escucha, soy ciudadano de la ciudad y te pediría que guardes tu hoja.");
			link.l1 = LinkRandPhrase("Bien.", "Bien.", "Como usted diga...");
		}
		else
		{
			dialog.text = NPCharSexPhrase(NPChar, "Ten cuidado, camarada, al correr con un arma. Yo me puedo poner nervioso...", "No me gusta cuando los hombres caminan delante de mí con sus armas listas. Me asusta...");
			link.l1 = RandPhraseSimple("Entendido.", "Me lo estoy llevando.");
		}
		link.l1.go = "exit";
		NextDiag.TempNode = "First Time";
		break;
		// <-- специальные реакции

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}
