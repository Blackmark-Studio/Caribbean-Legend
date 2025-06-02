void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "First time":
		dialog.text = "¿Qué queréis?";
		link.l1 = "Nada.";
		link.l1.go = "exit";
		break;

	case "startoff":
		dialog.text = "¡Capitán de Mor! ¡Bienvenido a Tortuga!";
		link.l1 = "Buen día, Teniente. ¿Disfrutando de la vista al mar con tus amigos?";
		link.l1.go = "startoff_joke";
		link.l2 = "Retrocede, Teniente.";
		link.l2.go = "startoff_silence";

		AddDialogExitQuestFunction("Tonzag_Arrested");
		break;

	case "startoff_joke":
		dialog.text = "Capitán, su reputación le precede, y los de arriba decidieron organizar un pequeño recorrido por las bellezas de nuestra encantadora Isla Tortuga. Comenzamos ahora mismo, con las celdas de la prisión del pueblo. Sus oficiales también están invitados.";
		link.l1 = "Teniente, no soy algún contrabandista sarnoso que atrapaste en la playa. No bromees, por favor. Explica los asuntos adecuadamente.";
		link.l1.go = "startoff_joke_1";
		link.l2 = "¡Entonces no perdamos tiempo! ¡Guía el camino, Teniente!";
		link.l2.go = "startoff_joke_2";
		break;

	case "startoff_silence":
		dialog.text = "Veo que tratar con vosotros, marineros, requiere un enfoque diferente. ¡Soldados, preparaos para la batalla! Capitán de Maure, usted y sus oficiales están arrestados. ¡Rindan sus armas!";
		link.l1 = "Puedo darte una bala, ¿dónde la quieres, teniente? Con ustedes, ratas de tierra, no hay otra manera.";
		link.l1.go = "startoff_silence_1";
		link.l2 = "¿Por qué ley? Si quieres arrestar a un grupo armado sin derramamiento de sangre, teniente, tendrás que esforzarte más.";
		link.l2.go = "startoff_silence_2";
		break;

	case "startoff_joke_1":
		dialog.text = "Para mí, todos sois iguales... Lo siento, pero no habrá explicaciones, Capitán. Órdenes de arriba. Entregue sus armas, si es tan amable.";
		link.l1 = "No necesito problemas... no ahora. Haz lo que dicen.";
		link.l1.go = "exit";

		AddCharacterExpToSkill(pchar, "Leadership", 100);
		ChangeCharacterComplexReputation(pchar, "nobility", +5);
		break;

	case "startoff_joke_2":
		dialog.text = "Eh... Supongo que no me entendiste del todo. ¡Capitán, usted y sus oficiales están arrestados! ¡Entreguen sus armas y vengan con nosotros!";
		link.l1 = "No necesito problemas... no ahora. Haz lo que dicen.";
		link.l1.go = "exit";

		AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

	case "startoff_silence_1":
		dialog.text = "Una palabra más, capitán, y te enterraremos aquí mismo. ¡Armas al suelo, ahora mismo!";
		link.l1 = "No necesito problemas... no ahora. Haz lo que dicen.";
		link.l1.go = "exit";

		AddComplexSelfExpToScill(100, 100, 100, 100);
		ChangeCharacterComplexReputation(pchar, "nobility", -5);
		break;

	case "startoff_silence_2":
		dialog.text = "No le temo a la sangre, Capitán. Incluso si sobrevives milagrosamente, nunca volverás a pisar Tortuga. Y nuestra inteligencia militar cree que valoras mucho tu acceso a esta isla.";
		link.l1 = "No necesito problemas... no ahora. Haz lo que dicen.";
		link.l1.go = "exit";

		AddCharacterExpToSkill(pchar, "Leadership", 100);
		ChangeCharacterComplexReputation(pchar, "authority", 5);
		break;

	case "tonzag_after_boarding":
		dialog.text = "¡Capitán, las cosas están jodidas! El enemigo nos tiene bien agarrados, me temo que no nos soltarán hasta que estemos muertos. ¡Nuestra gente está en un verdadero aprieto ahora mismo, y la mayoría de las tripulaciones de cañones están fuera de combate!";
		link.l1 = "Les ayudaré. ¡Toma el mando y sáquenos de aquí!";
		link.l1.go = "tonzag_after_boarding_1";
		DelLandQuestMark(npchar);
		break;

	case "tonzag_after_boarding_1":
		dialog.text = "¡Sí, señor!";
		link.l1 = "";
		link.l1.go = "exit";

		AddDialogExitQuestFunction("Tonzag_GoToGunDeck");
		break;

	case "tonzag_after_victory":
		dialog.text = "¡Victoria, Capitán! El grupo de desembarco ha sido destruido, el enemigo optó por retirarse y se dirigió al sur. La condición del barco es aceptable. Tripulación viva: " + GetCrewQuantity(pchar) + " gente. ¡Informe completado!";
		link.l1 = "¡Gracias! ¡Ron para todos y refuercen la guardia hasta que lleguemos al puerto!";
		link.l1.go = "tonzag_after_victory_1";
		break;

	case "tonzag_after_victory_1":
		dialog.text = "¡Hurra! ¡Sí, señor!";
		link.l1 = "";
		link.l1.go = "exit";

		AddDialogExitQuestFunction("Tonzag_AlonsoBoardingDialog");
		break;

	case "killer":
		dialog.text = "¡Y ahí está el hombre mismo! ¿Viste la sangrienta masacre afuera? ¡Es todo obra tuya, traidor! Pero responderás por todo: por Portobello, por Gruoh, ¡y por esta mina!";
		link.l1 = "Espera, ¿qué se supone que...?";
		link.l1.go = "exit";

		AddDialogExitQuestFunction("Tonzag_FightInMine");
		break;

	case "mine_head":
		dialog.text = "";
		link.l1 = "¡Agh! Esto no presagia nada bueno...";
		link.l1.go = "mine_head_1";
		break;

	case "mine_head_1":
		dialog.text = "¡San Santiago, protégeme! ¡Villanía! ¿Qué monstruo podría cometer tal acto? ¡Responde, señor!";
		link.l1 = "¡Cálmate, señor! ¡Preséntate primero! Sí, aquí ocurrió una carnicería monstruosa, pero las personas que la cometieron ya están muertas. Personalmente 'decoré' las minas con sus restos...";
		link.l1.go = "mine_head_2";
		break;

	case "mine_head_2":
		dialog.text = "Yo soy " + GetFullName(npchar) + ", ingeniero jefe de la mina real de Los Teques. Acabo de regresar de una misión que duró meses y... ¡qué veo! ¡Lo que ha sucedido aquí es un crimen contra Dios y la humanidad, así que le pido que entregue sus armas de inmediato! ¡Las autoridades de Caracas investigarán esta villanía!";
		link.l1 = "No puedo cumplir, señor, ¡y juro que no tuve nada que ver con esta masacre! Pero si insistes, tu propio cuerpo se sumará a la pila.";
		link.l1.go = "mine_head_3";
		break;

	case "mine_head_3":
		dialog.text = "No temo a la muerte, pero siempre sé cuándo retirarme. ¡Vete, pero recuerda, reportaré lo que sucedió aquí, y no omitiré ni un solo detalle!";
		link.l1 = "No puedo aceptar eso, señor. Lamento que haya llegado a esto. ¡A la batalla!";
		link.l1.go = "mine_head_fight";
		link.l2 = "Parece que buscas la muerte, señor. Pero hoy, nadie más morirá. Nos vamos, y espero que este detalle también figure en tu informe. ";
		link.l2.go = "mine_head_peace";
		break;

	case "mine_head_peace":
		DialogExit();

		AddDialogExitQuestFunction("Tonzag_LetMineHeadGo");
		break;

	case "mine_head_fight":
		DialogExit();

		AddDialogExitQuestFunction("Tonzag_FightMineHead");
		break;

	case "alonso":
		dialog.text = "¿Qué deberíamos hacer con el prisionero, Capitán?";
		link.l1 = "No es nada especial, solo no dejes que muera o escape.";
		link.l1.go = "alonso_1";
		break;

	case "alonso_1":
		dialog.text = "¡Aye aye! ¿Supongo que no necesitaré participar en el interrogatorio de hoy, Capitán?";
		link.l1 = "¿Por qué no? ¿Decidiste cambiar de profesión, Alonso?";
		link.l1.go = "alonso_2";
		break;

	case "alonso_2":
		dialog.text = "Ja-ja, no, Capitán. ¡Me encanta este trabajo, pero parece que tienes un nuevo maestro del oficio a bordo!";
		link.l1 = "¿Hercule? ¿De dónde sacaste esa idea?";
		link.l1.go = "alonso_3";
		break;

	case "alonso_3":
		dialog.text = "Bueno, Capitán, el viejo trajo su caja de herramientas justo para la ocasión y la puso en uso. Ni siquiera tendré que sacar la mía. ¡Ja!";
		link.l1 = "Ya veo... ¡Como estabas!";
		link.l1.go = "exit";

		AddDialogExitQuestFunction("Tonzag_DrinkAgain");
		break;

	case "captive":
		dialog.text = "Ah... Charles de Maure. Permíteme ofrecer mis disculpas en nombre de toda la Liga. La orden de dejarte en paz nos llegó demasiado tarde. Nuestra organización no tiene reclamaciones contra ti, Capitán. En cuanto a este animal calvo... ¡Uf! Mientras esté en tu correa, está a salvo, pero mi consejo para ti es no mantenerlo y dejarlo pudrirse en el arroyo donde pertenece.";
		link.l1 = "Gracias por la recomendación, pero estoy más interesado en por qué alguien me está protegiendo de tus mercenarios.";
		link.l1.go = "captive_1";
		break;

	case "captive_1":
		dialog.text = "No puedo saberlo, Capitán. Supongo que las instrucciones vinieron de nuestro nuevo patrón. ¿Has oído hablar de él, traidor? ¡La Liga está de nuevo en la cima ahora!";
		link.l1 = "¿Y quién es él?";
		link.l1.go = "captive_2";
		break;

	case "captive_2":
		dialog.text = "No puedo saber, Capitán, y aunque lo supiera, tales cosas no revelamos.";
		link.l1 = "En ese caso, dime algo más, y puedes ir adonde quieras. Tienes mi palabra.";
		link.l1.go = "captive_3";
		break;

	case "captive_3":
		dialog.text = "¿Así nomás? Bien, Capitán, haz tus preguntas y déjame ir. Prometo que no volveré a la Liga, aunque pudiera.";
		link.l1 = "¿Por qué estás tan obsesionado con Hércules? Demasiados problemas por un solo desertor.";
		link.l1.go = "captive_4";
		break;

	case "captive_4":
		dialog.text = "¿Qué le dijiste, perro? ¡No todo es lo que parece, capitán! La Liga está en constante movimiento, los códigos cambian, los empleadores varían. ¿Quieres irte? ¡Por supuesto! La salida está cerrada solo para los oficiales de alto rango, y esta escoria nunca lo ha sido. Su esposa, claro, pero respetábamos demasiado a Madame Tonzag como para no hacer una excepción por ella.";
		link.l1 = "¿Entonces por qué?";
		link.l1.go = "captive_5";
		break;

	case "captive_5":
		dialog.text = "Hubo un asunto en Portobello... Fue grande. Verás, tu amigo no solo se fue, no solo rompió el contrato, no solo mató al grupo que vino a terminar su trabajo. Provocó una verdadera masacre en las calles, complicando significativamente nuestra relación con los castellanos. Rara vez una incursión pirata siembra tanto terror como el que experimentaron los buenos católicos ese día. Maldita sea, incluso podría haberme impresionado si alguien más lo hubiera hecho.";
		link.l1 = "¿Otra masacre? Qué interesante. Sigue adelante.";
		link.l1.go = "captive_6";
		break;

	case "captive_6":
		dialog.text = "El entonces vicedirector de la Compañía, Rodenburg, intervino. De alguna manera logró silenciar todo el asunto, pero no antes de que perdiéramos a muchos de nuestros mejores hombres en las operaciones punitivas españolas. Sin embargo, después de que pasó algún tiempo, estábamos nuevamente haciendo negocios con ellos... ¡Ah! Pero no olvidamos nada, y tan pronto como surgió la oportunidad, intentamos vengarnos. El instigador de todo, Tonzag, tenía que ser eliminado.";
		link.l1 = "No tuviste éxito en eso. ¿Qué hay de la mina?";
		link.l1.go = "captive_7";
		break;

	case "captive_7":
		dialog.text = "Nos vimos obligados a hacerlo. Deshacernos de esa escoria requería demasiados gastos; necesitábamos oro. Todo por su culpa... Pero el intento de asesinato fracasó, y regresé a Los Teques para poner un poco de orden... ¿Cómo supiste dónde buscar?";
		link.l1 = "No importa. Necesito reunirme con tu líder. Quiero resolver el malentendido personalmente, ya que las garantías de tu misterioso patrón pueden expirar en cualquier momento.";
		link.l1.go = "captive_8";
		break;

	case "captive_8":
		dialog.text = "Estoy seguro de que ya te están esperando en Caracas, Capitán. Mira, no te oculto nada.";
		link.l1 = "";
		link.l1.go = "exit";

		AddDialogExitQuestFunction("Tonzag_HoldDialog");
		break;

	case "captive_9":
		dialog.text = "El comandante Arno murió, Austin está a cargo ahora.";
		link.l1 = "";
		link.l1.go = "exit";

		AddDialogExitQuestFunction("Tonzag_HoldDialog2");
		break;

	case "captive_10":
		dialog.text = "He respondido a todas tus preguntas, Capitán. Cumple tu palabra.";
		link.l1 = "Te dejo ir. Baja de mi barco, y reza para que no haya una emboscada esperándome en Caracas.";
		link.l1.go = "captive_spare";
		link.l2 = "Gracias por la interesante charla. Acusar a Hércules de causar una masacre después de lo que vi en la mina fue un poco exagerado, sin embargo. Al infierno, donde perteneces.";
		link.l2.go = "captive_execute";
		break;

	case "captive_execute":
		DialogExit();

		AddDialogExitQuestFunction("Tonzag_ExecuteCaptive");
		break;

	case "captive_spare":
		DialogExit();

		AddDialogExitQuestFunction("Tonzag_ReturnToCabin2");
		break;

	case "cureer":
		dialog.text = "Caballeros, están invitados a una reunión. Les esperan en la iglesia, así que la seguridad está garantizada.";
		link.l1 = "Eso fue rápido...";
		link.l1.go = "exit";

		AddDialogExitQuestFunction("Tonzag_CureerGoAway");
		break;

	case "ostin":
		StartQuestMovie(true, false, true);
			PlaySound("VOICE\" + LanguageGetLanguage() + "\hambit\Ercule Tongzag-10.wav");
			dialog.text = "Charles de Maure. Hércules. No saldrás de aquí con vida.";
			link.l1 = "Siempre es una buena manera de empezar una conversación. ¿Realmente necesitas todo esto?";
			link.l1.go = "ostin_1";
		break;
		
		case "ostin_1":
			dialog.text = "Contigo, Capitán, las cosas no son tan simples. Verás, nuestro nuevo patrón insistió en que te dejaran en paz... ¡y puede meterse sus peticiones por el culo! ¡Odio a los de tu calaña con toda mi alma! Navegan bajo sus bonitas velas blancas, pensando que el hielo no se derretirá en su boca. Pero cuando el acero de mi espada los atraviesa, gritan todos como niñas. ¡Eso me encanta, Charles, déjame decirte! Hace tiempo que no lo hacía... y ahora te tengo justo frente a mí, guapito.";
			link.l1 = "Estás enfermo, camarada.";
			link.l1.go = "ostin_2";
		break;
		
		case "ostin_2":
			dialog.text = "No, no puedo dejarte ir. Con tu amigo, por otro lado, es mucho más sencillo - a mis muchachos no les hace falta, pero todavía hay algunos de sus viejos camaradas de la Liga que no están del todo convencidos de la eficacia de mis métodos... Demasiado acostumbrados a trabajar limpio, por los limpios doblones, de la limpia Compañía. Pero sé justo lo que cambiará sus mentes, ¡la cabeza de un pecador audaz en una bandeja, ja-ja!";
			link.l1 = "Has elegido el lugar equivocado para eso, lunático. ¿Realmente vas a comenzar una batalla en una iglesia?";
			link.l1.go = "ostin_3";
		break;
		
		case "ostin_3":
			dialog.text = "Claro, ¿por qué no? ¿Te sientes mal por la gente? Puede que no sea tan lucrativo como en Los Teques, pero aún así lo pasaremos bien. ¡Pintaremos las paredes de la casa de Dios, ja-ja! Capitán, tú proporcionarás mucha pintura.";
			link.l1 = "Lo entiendo. ¿Nos envidias, no es así, rata loca? ¿Envidias nuestra libertad? ¿Que las chicas están felices de vernos y que las monedas tintinean en nuestros bolsillos? Mírate a ti mismo: ¿de dónde te desenterraron tus patrones, cerdo? ¿Quién te dejó entrar a la iglesia?";
			link.l1.go = "ostin_4";
		break;
		
		case "ostin_4":
			dialog.text = "¡Come tierra, maldita sabandija!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ChurchVystrel");
		break;
	}
}
