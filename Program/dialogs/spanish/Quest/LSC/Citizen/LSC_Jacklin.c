// Жаклин Тьюрам - торговый капитан
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "No quiero hablar contigo. Atacas a civiles pacíficos sin razón alguna y los provocas a pelear. ¡Piérdete!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Buen día, monsieur. Eres nuevo aquí, ¿verdad?";
				link.l1 = TimeGreeting()+"Sí, supongo que soy el más nuevo aquí. Mi nombre es "+GetFullName(pchar)+"¿Y cuál es el tuyo?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"¡ "+TimeGreeting()+"¡¿Quieres algo?!";
				link.l1 = LinkRandPhrase("¿Tienes algo interesante que decir?","¿Ha pasado algo nuevo en la isla?","¿Me contarás los últimos chismes?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Quiero hacerte unas preguntas sobre la isla.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Solo quería saber cómo estás. ¡Nos vemos!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Jacqueline Turam. Hace dos años era una comerciante decente y adinerada, propietaria y capitana de mi propio filibote. Ay, ahora soy tan pobre como una rata de iglesia y no puedo esperar que mi situación cambie de alguna manera.\nAlgunas personas tienen suerte aquí: encuentran joyas, oro, barcos llenos de tesoros, pero yo no soy una de ellas. Solo encontré un cofre con doblones y algunos abalorios\nAl menos eso es suficiente para comprar comida, así que no me muero de hambre... Un placer conocerle, señor, no me importa charlar...";
			link.l1 = "Me alegra conocerte también, Jacqueline. ¡Nos vemos!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("¿Tienes algo interesante que decir?","¿Ha sucedido algo nuevo en la isla?","¿Me contarás los últimos chismes?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Quiero hacerte unas preguntas sobre la isla.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Soy todo oídos.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "¿Cómo llegaste aquí?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "¿Qué haces aquí?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Dime, veo que hay chicas y mujeres en la Isla...";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "¿Quieres volver al gran mundo?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "No es nada.";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "¿Quieres escuchar mi historia? Bien. Yo era un capitán mercante. Un día zarpé de Tortuga a Belice en mi buen y viejo filibote. Mis bodegas estaban llenas con madera negra y cacao, había gastado todas mis monedas en la carga.\nArreglé un trato muy lucrativo con un hombre, quería comprar mi carga por un precio extremadamente alto. Podría hacerme una fortuna con ese trato. Todo iba bien, ni una sola nube en el cielo, mi barco era tan rápido como un pájaro. No esperábamos problemas\nNavegaba cerca de Cuba, manteniéndome alejado de las patrullas españolas, pero de repente fuimos atacados por un galeón pirata. ¿Qué hacían ahí, en medio del territorio español? Intentamos huir, pero fracasamos, el galeón era sorprendentemente rápido\nLos piratas nos persiguieron y atacaron. Sus coulverinas estaban cargadas con metralla, la primera salva dañó gravemente a mi tripulación y la desmoralizó. Quería darles una buena pelea, pero mis propios marineros y oficiales me detuvieron. Nos rendimos\nLos piratas rápidamente tomaron nuestra carga y tiraron nuestros cañones. Pensé que era el fin. Perder la carga fue un golpe duro, pero aún podía ganar dinero con fletes y algún día volver a ponerme de pie.\nPero resultó de manera diferente. Los malditos piratas abrieron fuego contra mi filibote indefenso. Éramos un blanco perfecto\nTodavía puedo recordar sus risas... El galeón se alejó y nosotros estábamos naufragando, agarrados a los restos. Luego vino un fuerte vendaval con olas y nunca más he visto a nadie de mi tripulación desde entonces. Logré atarme a una parte del mástil y mantenerme a flote.\nTe ahorraré los detalles adicionales sobre el ataque de tiburones. Después de un período de tiempo eterno, fui llevado aquí por una corriente marina. Así es como sobreviví.";
			link.l1 = "Sí, es realmente una historia triste.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Vivo como el resto de los lugareños - simplemente vivo. Busco objetos valiosos en el anillo exterior y los cambio por comida. Sueño con encontrar el cofre de un rey indio lleno de tesoros... O al menos un galeón con oro español, je-je. No prestes mucha atención, solo soy yo\nSueño con comer algo diferente a carne en conserva y pescado. Eh, había un hombre aquí, cazaba esos cangrejos gigantes. Solía pagar cinco doblones por una garra y alimentarme de ella durante varios días\nLástima que el cazador muriera... aunque no puedo decir que no era de esperarse - cazar esas cosas es una actividad muy peligrosa.";
			link.l1 = "Veo...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Veo a lo que estás insinuando. Sí, aquí existen el amor y las intrigas. ¿Y por qué no existirían? El hombre está hecho para la mujer y la mujer está hecha para el hombre. Naturaleza. Puedes intentar con Gillian y Tanneke. Son jóvenes, bonitas y no les importa cortejar. Me he encontrado una mujer - Natalia. Es una camarera en la taberna de Sancho. Una gran chica, te lo digo. Creo que es la única razón por la que no perdí la cabeza durante los primeros meses de vivir aquí. Ella ha ayudado mucho y ahora estamos juntos.";
			link.l1 = "Mm... ¡Lo tengo!";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Buena pregunta. Me gustaría, por supuesto. Pero al pensarlo... Estoy destrozado. He invertido todo en la carga y mi barco se ha hundido. No me queda nada para vivir. La única forma de ganar dinero para mí es trabajar para la Compañía Holandesa de las Indias Occidentales si me contratan, por supuesto.\nSi tan solo tuviera suficiente dinero para comprar un bergantín y suficientes suministros... Así que será mejor que me quede en la Isla. Al menos aquí no tengo que trabajar de sol a sol por un mendrugo de pan.";
			link.l1 = "Veo...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("¿Qué haces ahí, eh? ¡Ladrón!","¡Solo mira eso! ¡Tan pronto como me perdí en la contemplación, decidiste revisar mi cofre!","¿Has decidido revisar mis cofres? ¡No te saldrás con la tuya!");
			link.l1 = "¡Maldita sea!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "¿Qué?! ¿Decidiste revisar mis cofres? ¡No te saldrás con la tuya!";
			link.l1 = "¡Chica tonta!";
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
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Escucha, será mejor que guardes tu arma. Me pone nervioso.","Sabes, correr con la hoja no se tolera aquí. Guárdala.","Escucha, no te hagas el caballero medieval corriendo con una espada por ahí. Guárdala, no te queda bien...");
			link.l1 = LinkRandPhrase("Bien.","Bien.","Como dices...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Escucha, soy ciudadano de la ciudad y te pediría que mantuvieras tu espada enfundada.","Escucha, soy ciudadano de la ciudad y te pediría que mantuvieras tu espada en su lugar.");
				link.l1 = LinkRandPhrase("Bien.","Lo que sea entonces.","Como tú digas...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ten cuidado, camarada, al correr con un arma. Puedo ponerme nervioso...","No me gusta cuando los hombres caminan frente a mí con sus armas preparadas. Me asusta...");
				link.l1 = RandPhraseSimple("Entendido.","Me lo estoy llevando.");
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
