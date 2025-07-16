// Jason общий диалог дворянок
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// вызов диалога по городам -->
	NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c ";
						 if (LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	// вызов диалога по городам <--

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		// первая встреча
		if (NPChar.quest.meeting == "0")
		{
			if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY) // проверка межнациональных отношений
			{
				dialog.text = "Hm. Navegas bajo la bandera de " + NationNameGenitive(sti(pchar.nation)) + ", capitán. No tengo deseo de hablar con el enemigo de mi país. ¡Hm!";
				link.l1 = "Ah, sí. Un verdadero patriota...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple("¿Qué quieres de mí, " + GetAddress_Form(NPChar) + "¿No es apropiado que un marinero común hable con una dama noble, pero te estoy escuchando?", "Oh, ¿y qué quiere de mí un capitán tan valiente?");
				link.l1 = TimeGreeting() + ", " + GetAddress_FormToNPC(NPChar) + ". No tomaré mucho de tu tiempo, solo quiero preguntar...";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("Necesito saber qué está pasando en tu colonia.", "Necesito información.");
				link.l2.go = "quests"; //(перессылка в файл города)
			}
			npchar.quest.meeting = "1";

			//==> прибыла инспекция на Святом Милосердии
			if (pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_town")
			{
				dialog.Text = LinkRandPhrase(LinkRandPhrase("La ciudad entera está en tensión, don Fernando de Alamida, el inspector real, ha llegado. Sabes, he visto mucho aquí, pero esto... No es el dolor lo que cambia a las personas, sino cómo lo enfrentan. Dicen que se convirtió en un hombre diferente después de la muerte de su padre. Ahora no encontrarás un servidor más incorruptible y... despiadado de la Corona en todo el Archipiélago.", "¡Solo mira el 'Santa Misericordia'! Dicen que el mismo rey ordenó construirlo según diseños especiales. Y fíjate, ni un solo rasguño. Como si la Virgen María misma lo protegiera. Aunque he oído rumores... tal vez no sea la Virgen en absoluto.", "¿Sabes cuántas veces han intentado matar a don Fernando? ¡Doce ataques en aguas abiertas, y eso solo en el último año! Bueno, con una tripulación tan leal y entrenada, y bajo la protección del Señor, ¡sobrevivirá al decimotercer intento también!"), LinkRandPhrase("¿Has oído? Don Fernando de Alamida ha llegado a nuestra ciudad, y dicen que está en alguna calle ahora mismo. Me encantaría verlo con mis propios ojos...", "Un hombre complicado, este don Fernando. Algunos dicen que es un salvador, limpiando a la Madre Patria de la escoria. Otros susurran que algo se rompió en él después de la muerte de su padre y pronto todos estaremos llorando. Pero te diré esto: no le temas a él. Teme a aquellos que lo hicieron lo que es.", "¡Qué hombre tan apuesto, este don Fernando! Pero ¿sabes qué es extraño? Es como si no notara a nadie. Todo es deber y servicio. Escuché que había una chica... pero después de reunirse con un sacerdote, rechazó por completo los placeres mundanos. Como si hubiera hecho un voto."), RandPhraseSimple(RandPhraseSimple("¡Maldito inspector! Mientras él está aquí, la ciudad parece muerta. Sin comercio, sin diversión. Incluso respirar, parece, debe ser más silencioso. ¿Y sabes qué es lo más aterrador? Es lo mismo en cada puerto. Como un reloj. ¡Su Real Majestad no podría haber inventado deliberadamente esta tortura para todos nosotros!", "Don Fernando visitó el orfanato de nuevo. Dona generosamente, reza durante horas. ¡Un hombre tan digno debería ser un ejemplo para esos malditos malversadores!"), RandPhraseSimple("¡Ja! 'San' Fernando cerró todos los burdeles otra vez. Bueno, no importa, pronto se irá y los volverán a abrir.", "¡El insp... inspector ha llegado, eso es! Don Fernando de Almeyda, o, ¿cómo se llama, Alamida? Tan importante que el propio gobernador anda de puntillas a su alrededor. Dicen que te mira a los ojos y ve todos tus pecados de inmediato. ¡Aterrador!")));
				link.l1 = "...";
				link.l1.go = "exit";
				DeleteAttribute(link, "l2");
			}
			//<== прибыла инспекция на Святом Милосердии
			//==> Леди Бет в порту города
				if (CheckAttribute(pchar, "questTemp.LadyBeth.CaptainInColony") && pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_town")
				{
					dialog.Text = findLedyBethRumour(npchar);
					link.l1 = "...";
					link.l1.go = "exit";
					DeleteAttribute(link, "l2");
				}
				//<== Леди Бет в порту города
		}
		else
		{
			// повторные обращения
			if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
				dialog.text = "¿Debería repetirme? No quiero que me sospechen como amigo de " + NationNameAblative(sti(pchar.nation)) + "¡Lárgate o llamaré a los guardias! Estarán encantados de hablar contigo.";
				link.l1 = "Está bien, está bien, cálmate. Me voy.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = NPCStringReactionRepeat("¿Qué? ¿Tú otra vez? Busca a alguien más para hablar. Hay muchos plebeyos dando vueltas, son más de tu tipo. Tengo que irme ahora, habrá un banquete esta noche en la residencia del gobernador y mi copete aún no está listo.", "¡No, ahora estás siendo realmente molesto! ¿No lo entiendes? ¿O eres lento de mente?", "Señor, empiezo a sospechar que no solo es un idiota, sino también un sinvergüenza y un patán. ¡Le advierto que llamaré a mi esposo si no deja de molestarme con sus estúpidas preguntas!", "¡Una palabra más y le diré al comandante que haga algo contigo!", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Ya veo. Adiós.", "Sí-sí, recuerdo, solo olvidé preguntar...", "Me has entendido mal...", "Tranquila, señora, ya me voy...", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
			}
		}
		NextDiag.TempNode = "First time";
		break;

	// сюда вставляем любые проверки и направления на квесты
	case "question":
		dialog.text = LinkRandPhrase("Está bien, escuchemos.", "Oh, bien. ¿Qué quieres?", "¿Preguntas? Bien, marinero, estoy escuchando.");
		link.l1 = LinkRandPhrase("¿Puedes contarme los últimos chismes de este pueblo?", "¿Ha ocurrido algo interesante por aquí últimamente?", "¿Alguna noticia del Caribe, mi señora?");
		link.l1.go = "rumours_noblegirl";
		NextDiag.TempNode = "First time";
		break;

	// замечание по обнажённому оружию от персонажей типа citizen
	case "CitizenNotBlade":
		dialog.text = NPCharSexPhrase(NPChar, "¿Estás loco?! ¡Me asustas! ¡Envaina tu arma o le diré al comandante que te cuelgue en el fuerte!", "¿Estás loco?! ¡Me asustas! ¡Enfunda tu arma o le diré al comandante que te ahorque en el fuerte!");
		link.l1 = LinkRandPhrase("Bien.", "Como desees.", "Bien.");
		link.l1.go = "exit";
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}
