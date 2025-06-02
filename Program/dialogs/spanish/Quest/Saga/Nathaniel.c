// Натаниэль Хоук - пиратский барон Марун-Тауна
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		dialog.text = "¿Quieres algo?";
		link.l1 = "No, es nada.";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	case "diffindoor":
		PlaySound("Voice\Spanish\saga\Nataniel Hawk-05.wav");
		dialog.text = "Ah... ¿quién eres tú, maldita sea?.. Khe... (tos severa con ronquera) Esa maldita estatua vieja me succionó toda la vida...";
		link.l1 = "Saludos, Nathaniel. Tú eres Nathaniel Hawk, ¿no es así?";
		link.l1.go = "diffindoor_1";
		break;

	case "diffindoor_1":
		dialog.text = "Sí, soy yo, si aún puedo llamarme así. Una vez fui Nathaniel Hawk, pero ahora soy solo un triste saco de mierda. ¡Al diablo con esa estatua! Me ha quitado toda la vitalidad.";
		link.l1 = "Es segunda vez que mencionas la estatua. Y créeme, también estoy familiarizado con ese sentimiento...";
		link.l1.go = "diffindoor_2";
		break;

	case "diffindoor_2":
		dialog.text = "¿Cómo podrías, muchacho, si ni siquiera te das cuenta de lo que estoy hablando? A-kha... ¿Sabes cómo se siente convertirse en un viejo medio muerto cuando hace un minuto estaba sano y fuerte?\nHe visto muchas cosas, pensé que este antiguo templo indio que visité en mi juventud habría matado mi capacidad de sorprenderme, ¡pero esto... por qué no lo vi venir! ¡Esa maldita estatua se veía igual que el viejo ídolo que abrió la puerta al templo!";
		link.l1 = "Está bien, Nathan, hablemos. Permíteme presentarme, soy " + GetFullName(pchar) + ". Primero, te entiendo muy bien porque vine aquí de la misma manera que tú, usando el portal de Kukulcán.";
		link.l1.go = "diffindoor_3";
		break;

	case "diffindoor_3":
		dialog.text = "¿De veras?! Entonces, ¿por qué te ves tan bien? ¿O acaso ese... Kukulcán solo me ha hecho daño a mí?";
		link.l1 = "Snake Eye, el chamán Miskito, quien te ayudó a escapar, me ha dado una poción muy fuerte. La bebí en cuanto desperté en el San Agustín. Me curó por completo. Estoy seguro de que Snake Eye puede ayudarte también. Solo necesitamos llevarte a él.";
		link.l1.go = "diffindoor_4";
		break;

	case "diffindoor_4":
		dialog.text = "¡Ah, ese indio! ¿Una poción? ¿Y por qué no me dio una a mí también?";
		link.l1 = "Dijo que no había tiempo. Te estaban persiguiendo y lo único que podía hacer era mostrarte el camino para escapar: el portal.";
		link.l1.go = "diffindoor_5";
		break;

	case "diffindoor_5":
		PlaySound("Voice\Spanish\saga\Nataniel Hawk-06.wav");
		dialog.text = "¿Escapar? Oh... ¿No ves mi condición actual? Intenté salvarme, pero lo único que encontré fue esta isla de ovejas podridas. Gracias a Dios, todavía hay buenas personas en este mundo. Ole, Dios lo bendiga... ¿Conoces a Ole?";
		link.l1 = "Sí. En realidad, fue él quien me habló de ti, me contó cómo te alimentaba con ratas y cómo sigues bebiendo, botella tras botella...";
		link.l1.go = "diffindoor_6";
		break;

	case "diffindoor_6":
		dialog.text = "Moriré más rápido que una vela encendida si no bebo ron. Es lo único que me mantiene vivo. Ron...";
		link.l1 = "¿Sigues sintiéndote tan mal? ¿Igual que después de la teletransportación?";
		link.l1.go = "diffindoor_7";
		break;

	case "diffindoor_7":
		dialog.text = "Bueno, no me siento del todo igual... Pero tampoco realmente mejor. Amigo, dime, ¿por qué necesitabas ver al viejo Nathan? ¿Por qué diablos viniste aquí, a este viejo y podrido bote? ¿Para charlar conmigo?";
		link.l1 = "En realidad, sí. No me creerás, pero la razón por la que pasé por todos esos problemas con la teleportación fue para encontrarte. Trabajo para la Cofradía de los Hermanos de la Costa y represento a Jan Svenson.";
		link.l1.go = "diffindoor_8";
		break;

	case "diffindoor_8":
		dialog.text = "Maldición... ¿Forest Devil? Argh... ¿Viniste aquí para acabar conmigo? ¿En realidad, no? Eres demasiado hablador para ser un asesino. Por favor, no me tortures. Si te ordenaron sacarme algo, te lo diré todo yo mismo, no tengo nada que esconder.";
		link.l1 = "¿Qué quieres decir? A-ah, ya veo. Tú, al igual que Danielle, piensas que Svenson fue quien organizó esa emboscada contra tu vida en la selva. Te puedo asegurar que Jan no lo hizo. Al contrario, él está de tu lado y se preocupa mucho por tu desaparición.";
		link.l1.go = "diffindoor_9";
		break;

	case "diffindoor_9":
		dialog.text = "¿De veras? Me alegra mucho escuchar eso. Y ya he estado pensando... pero ¿quién lo hizo? Mi destacamento fue destruido en minutos. Nos estaban esperando. ¡Incluso tenían cañones de barco! Derribaron a la mitad de mis hombres con metralla y luego nos remataron con sus mosquetes...";
		link.l1 = "Para ser honesto, no sé los detalles, pero estoy seguro de que Jackman está detrás de todo esto. Demasiadas coincidencias, primero Blaze, luego tú... Jackman quiere apoderarse del poder y elimina a todos los que se interponen en su camino. Él gobierna Maroon Town ahora en lugar de ti.";
		link.l1.go = "diffindoor_10";
		break;

	case "diffindoor_10":
		dialog.text = "¿Jackman? ¡Bastardo! Eh... los Hermanos se han dividido en los últimos años, todo era diferente antes. Zachariah se ha vuelto loco con sus asuntos religiosos, a Tyrex le importa un comino todo y a Barbazon solo le interesan los doblones. Todo era diferente hace veinte años...";
		link.l1 = "¿Cómo te capturaron? Cuéntame más.";
		link.l1.go = "diffindoor_11";
		break;

	case "diffindoor_11":
		dialog.text = "¡No hay nada interesante que contar! Como dije, esos bandidos planearon todo. Actuaban con precisión, estaban coordinados y claramente seguían las órdenes de alguien. Podrían haberme matado cien veces, pero no lo hicieron. Me querían vivo. Me llevaron a una mina abandonada y me encerraron en una de las chozas. 'Hasta que llegue el jefe', decían.\nPensé que Svenson era el jefe, pero parece que Jackman está al mando. No sé qué podría haber querido de mí, pero estoy seguro de que no habría vivido mucho después de charlar con él.";
		link.l1 = "No tengo duda de ello. Svenson está seguro de que Jackman ha matado a Blaze Sharp... ¿Cómo pudiste escapar?";
		link.l1.go = "diffindoor_12";
		break;

	case "diffindoor_12":
		dialog.text = "De alguna manera, ese indio Ojo de Serpiente logró colarse en la mina. Por lo que entiendo, a los miskitos no les gustan los bandidos. De todos modos, Ojo de Serpiente arregló mi escape por alguna razón. Cavó un túnel hacia mí, entró, cortó mis cuerdas y huimos a la jungla.\nQuería llevarme a su aldea, a los miskitos. Pero parece que Jackman me quería mucho, ya que organizaron una gran cacería. Estaban pisándonos los talones. Ojo de Serpiente hizo todo lo posible por engañarlos, pero siempre lograban encontrar nuestro rastro. Tenían buenos rastreadores, sin duda.\nEstábamos cerca de la aldea de Ojo de Serpiente cuando finalmente nos encontraron. En ese punto mi estómago llevaba vacío dos días y estaba completamente agotado ya que también me había lastimado la pierna gravemente. Era medianoche y aún recuerdo lo brillante que era la estrella sobre la estatua... Ojo de Serpiente dijo que mi única oportunidad era llegar al ídolo y tocarlo.\nPensé que el hombre estaba loco, pero ya sabes lo que dicen sobre agarrarse a un clavo ardiendo. Me arrastré hasta la estatua, la toqué... ¡y entonces empezaron a suceder cosas locas!";
		link.l1 = "No necesitas continuar, sé lo que ha ocurrido después.";
		link.l1.go = "diffindoor_13";
		break;

	case "diffindoor_13":
		dialog.text = "Me encontré dentro de la húmeda bodega de algún barco naufragado. Estaba medio muerto. No podía caminar, solo arrastrarme. Cada minuto mi estado empeoraba. Ole apareció justo a tiempo. Me vertió una mezcla caribeña que sabía a porquería, una mezcla de antídoto y esencia curativa. Luego me dio ron.\nMe mejoré de inmediato. Luego encontró y usó un tronco viejo para moverme aquí. He estado viviendo aquí por algún tiempo, no sé cuánto exactamente, he perdido la noción del tiempo.";
		link.l1 = "Todo estará bien, Nathan. Svenson y yo tenemos grandes planes y tu papel en ellos es muy significativo. Debes regresar a tu posición en Maroon Town y nos encargaremos de ese sinvergüenza de Jackman.";
		link.l1.go = "diffindoor_14";
		break;

	case "diffindoor_14":
		dialog.text = "¿Maroon Town? ¿Y cómo exactamente te imaginas que esto funcionará? ¡Mírame, soy un naufragio empapado de ron! Inútil... No, los años de mi autoridad sobre Maroon Town se han ido para siempre. Estoy atrapado en este maldito cementerio de barcos. ¿Cuánto tiempo duraré? ¿Un mes, dos, un año?\nY luego terminaré tendido en estas maderas podridas y Ole arrojará lo que queda de Nathaniel Hawk al mar. Lo peor es que no volveré a ver a mi Dannie. Eh, se acabó, amigo.";
		link.l1 = "No seas tan pesimista. Te sacaré de aquí.";
		link.l1.go = "diffindoor_15";
		break;

	case "diffindoor_15":
		dialog.text = "¿Cómo me sacarás de aquí? ¿Y cómo vamos a salir de este lugar? No hay barcos. ¿Quieres construir una balsa?";
		link.l1 = "No. Dejaré este lugar de la misma manera que llegué aquí. Sé dónde está la estatua... bueno, más o menos. La encontraré y luego volveré por ti y Shark Dodson. Después te llevaremos a Snake Eye. Él te curará.";
		link.l1.go = "diffindoor_16";
		break;

	case "diffindoor_16":
		dialog.text = "¿Qué dijiste? ¿Shark Dodson? ¿Steve también está aquí? Qué lugar tan extraño...";
		link.l1 = "Sí, él está aquí. Es el 'gobernador' de esta isla, por así decirlo. Le he preguntado por ti, pero no sabe nada.";
		link.l1.go = "diffindoor_17";
		break;

	case "diffindoor_17":
		dialog.text = "Y no debería. No quiero que me vea en este estado. Has dicho que el chamán me sanará... Apenas puedo creerlo. También mencionaste a Dannie... ¿La viste?";
		link.l1 = "Sí. Ella misma me encontró en Blueweld. Había escuchado mi conversación con Svenson y entendió que Jan no tenía intención de matarte y que está trabajando contra Jackman. Se unió a mi barco como oficial para ayudarme a encontrarte.";
		link.l1.go = "diffindoor_18";
		break;

	case "diffindoor_18":
		dialog.text = "¡Eh, mi querida Dannie! Ella no ha cambiado... tan temeraria como en su juventud... ¡No puedes imaginar cuánto deseo verla y abrazarla ahora! He reflexionado mucho mientras yacía aquí. Mira, amigo, empiezas a ver las cosas de una manera diferente cuando estás cerca de la muerte. ¡He pasado tan poco tiempo con mi esposa!\nIncursiones marinas, los asuntos oficiales de los Hermanos, gobernar Maroon Town. Y ella siempre me apoyó en todo: se quedaba sola durante semanas, tenía disputas con otros piratas mientras yo estaba ausente, comandaba nuestro barco... ¡Mi Dannie es la mejor mujer del mundo! Y yo... ¡Debería haberle dicho más a menudo que la amo!\n¡Recuerdo el día en que decidimos estar juntos! De hecho, ese fue el día en que conocí y luché contra cosas sobrenaturales por primera vez. Todo sucedió por culpa de ese maldito ídolo que se parecía mucho a las estatuas. ¿No te importa escuchar una historia? Es bastante interesante.";
		link.l1 = "¡En absoluto! ¡Dímelo!";
		link.l1.go = "story";
		link.l2 = "Nathan, no tenemos tiempo para recuerdos agradables. Cuéntamelo más tarde, cuando estemos sentados en el pueblo Miskito con una botella de vino.";
		link.l2.go = "diffindoor_19";
		break;

	case "story":
		dialog.text = "Fue hace veinticinco años... Yo era joven, ardiente e inquieto. El Caribe era mi patio de recreo. Ya conocía a Dannie en ese entonces. Me gustaba, de verdad, y el sentimiento era mutuo. Pero peleábamos a menudo, discutíamos y nos lanzábamos pullas. Juventud tonta... ¡Creo que éramos un gran entretenimiento para los respetados marineros de entonces!\nDe todos modos, de alguna manera Dannie y yo nos involucramos en la misma historia. Habíamos encontrado un mapa de Khael Roa y nos dijeron que era EL lugar para encontrar oro indio. También habíamos encontrado un ídolo dorado de aspecto extraño, una copia más pequeña de la parte superior de las estatuas.\nEl ídolo era peligroso, absorbía la vitalidad de aquellos que lo llevaban. Pero necesitábamos ese maldito objeto para llegar al tesoro dentro del templo. El único problema era que no teníamos idea de cómo usarlo correctamente. Dannie y yo navegamos hacia la isla. Había un antiguo templo, cubierto de hierba y árboles. Una vez que entramos, nos encontramos dentro de un enorme laberinto.\nLogramos encontrar el camino correcto y llegamos a la parte central del laberinto. Pensamos que era un callejón sin salida, pero cuando la desesperación comenzaba a vencernos, vimos una extraña plataforma con un pequeño receptáculo y una imagen en ella. Puse el ídolo en el receptáculo y...";
		link.l1 = "...";
		link.l1.go = "exit";
		pchar.questTemp.LSC.Natanstory = "idol";
		AddDialogExitQuest("Video_story");
		NextDiag.TempNode = "story_1";
		break;

	case "story_1":
		dialog.text = "La plataforma de piedra bajó unos centímetros y una de las paredes resultó ser un pasaje secreto. El ídolo quedó dentro de la plataforma, no pude sacarlo de nuevo. Finalmente llegamos a un salón gigante. ¡Qué vista tan hermosa!\nLa estructura más magnífica que he visto. Tallados en las paredes, enormes estatuas... Registramos todo el salón, pero no encontramos señales de tesoros.";
		link.l1 = "Je, eso sí que les pasa a menudo a personas como nosotros. Mucho esfuerzo y ningún resultado al final...";
		link.l1.go = "story_2";
		break;

	case "story_2":
		dialog.text = "No fue en vano. Después de todo, entramos en una sala del trono con una estatua gigante de un pájaro al final de esta. Había una luz mística cerca de la estatua, se veía igual que la luz sobre el ídolo a medianoche. Nos acercamos y vimos una hermosa esfera voladora. ¡Lo juro, te estoy diciendo la pura verdad!\nEra real, pero al mismo tiempo se sentía como si no lo fuera. Mientras pensaba, Dannie - oh, ese diablillo imprudente, tocó la esfera. Comenzó a brillar aún más y finalmente se convirtió en un pequeño objeto en sus manos...";
		link.l1 = "... ";
		link.l1.go = "exit";
		pchar.questTemp.LSC.Natanstory = "temple";
		AddDialogExitQuest("Video_story");
		NextDiag.TempNode = "story_3";
		break;

	case "story_3":
		dialog.text = "Parecía que habíamos cometido un sacrilegio. El templo cobró vida: todo a nuestro alrededor comenzó a moverse, las paredes temblaban y todo se desmoronaba. Era como si hubiéramos despertado a todos los demonios indios y ellos nos lanzaran toda su ira de vuelta...";
		link.l1 = "¡Vaya!";
		link.l1.go = "story_4";
		break;

	case "story_4":
		dialog.text = "Es difícil de creer, lo sé. Pero...";
		link.l1 = "Te habría llamado mentiroso hace medio año. Pero he estado viviendo en el Caribe lo suficiente como para saber que no tengo razones para desconfiar de ti. Continúa. ¿Cómo sobreviviste?";
		link.l1.go = "story_5";
		break;

	case "story_5":
		dialog.text = "Salimos corriendo del templo y tuvimos la suerte de subir a nuestro barco a tiempo. Ordené izar el ancla, queríamos zarpar de ese lugar lo antes posible.";
		link.l1 = "¡Je! ¿Así que al final solo encontraste algún artefacto raro en lugar de tesoros? Qué bonito y equivalente reemplazo, je-je... ¿Y averiguaste cómo usarlo? ¿O fue inútil?";
		link.l1.go = "story_6";
		break;

	case "story_6":
		dialog.text = "Espera un momento. La historia aún no ha terminado. Dannie tenía el artefacto y tan pronto como decidimos ir a la cabaña para estudiarlo, el cielo se oscureció y apareció un barco. ¡Oh Dios! Era...";
		link.l1 = "...";
		link.l1.go = "exit";
		pchar.questTemp.LSC.Natanstory = "blackpearl";
		AddDialogExitQuest("Video_story");
		NextDiag.TempNode = "story_7";
		break;

	// вот тут делаем развилку, в зависимости прошёл ли игрок Калеуче
	case "story_7":
		dialog.text = "¡... Van der Decken en persona!!";
		if (CheckAttribute(pchar, "questTemp.KhaelRoa"))
		{
			link.l1 = "¿Van der Decken? Hm...";
			link.l1.go = "story_8_1";
		}
		else
		{
			link.l1 = "¿Y quién es él?";
			link.l1.go = "story_8";
		}
		break;

	case "story_8":
		dialog.text = "¿Nunca has oído hablar del Holandés Errante?";
		link.l1 = "¿Quién no ha oído hablar del Holandés Errante? Ya me encontré con un holandés y envié a su capitán al fondo del mar. Solo era un pirata común que decoró su barco con algún disfraz de mascarada como algas y velas rasgadas.";
		link.l1.go = "story_9";
		break;

	case "story_8_1":
		dialog.text = "Sí, pero este era Van der Decken en persona, ¡el capitán del Holandés Errante!";
		link.l1 = "Interesante. Por favor, continúa. ¿Cómo lograste salir adelante?";
		link.l1.go = "story_11";
		break;

	case "story_9":
		dialog.text = "Eh-heh, amigo... Hundiste a algún bufón, pero yo hablo del verdadero Holandés Errante. Un enorme navío de guerra. Que Dios te salve de encontrarla alguna vez en mar abierto. Su capitán Van der Decken y su tripulación fueron una vez malditos para navegar incansablemente por el mar para siempre. \nRecuerdo sus velas negras desgarradas, la tripulación de hombres muertos de pie en cubierta con sus espadas desenvainadas y el capitán mismo - un esqueleto espeluznante con un sombrero negro de ala ancha... Jesús...";
		link.l1 = "¿Estás diciendo la verdad?";
		link.l1.go = "story_10";
		break;

	case "story_10":
		dialog.text = "Puedo jurar sobre la Biblia que no estoy mintiendo... Encontrarse con el 'Holandés Errante' solo significa una muerte segura. Es poderosa, muy poderosa, una descarga de sus cañones puede hundir incluso a una fragata pesada y su tripulación... pero aún peor, ¿cómo se supone que debes luchar contra los no muertos?";
		link.l1 = "¡Pero sobreviviste a esta pesadilla!";
		link.l1.go = "story_11";
		break;

	case "story_11":
		dialog.text = "Todo es gracias a mi encantadora Dannie y al artefacto indio que tomamos del templo. Había ordenado prepararse para luchar, pero sabía que era el final del camino. El 'Holandés Errante' navegaba hacia nosotros y veía a su espantosa tripulación y al propio Van der Decken en cubierta. El barco comenzó a apuntar sus cañones hacia nosotros, pero...";
		link.l1 = "...";
		link.l1.go = "exit";
		pchar.questTemp.LSC.Natanstory = "artefact";
		AddDialogExitQuest("Video_story");
		NextDiag.TempNode = "story_12";
		break;

	case "story_12":
		dialog.text = "Dannie levantó el artefacto y lo dejó volar. No tenía idea de por qué habría hecho eso. Dijo algo sobre su intuición femenina... El artefacto se transformó de nuevo en una esfera brillante y explotó, dañando críticamente el barco fantasma y desmoralizando a su tripulación. Ordené abrir fuego contra el Holandés.\nLa primera andanada los hizo estremecerse. Atacamos de nuevo y disparamos contra su casco podrido una segunda vez, justo antes de que pudieran recuperarse de la influencia del artefacto y comenzaran a devolver el fuego...";
		link.l1 = "¿Entonces, tuviste que luchar contra ellos de todos modos?";
		link.l1.go = "story_13";
		break;

	case "story_13":
		dialog.text = "En efecto. Y juro que fue la pelea más dura de mi vida. Su maldita bañera apenas se mantenía a flote, sin embargo, aún pudieron destruir la mitad de mi casco antes de que los mandáramos por los aires haciendo volar por los cielos su maldita santabárbara.";
		link.l1 = "¿Entonces lo hundiste? ¿Hundiste al Holandés Errante?";
		link.l1.go = "story_14";
		break;

	case "story_14":
		dialog.text = "¡Sí, maldita sea! ¡Lo hice!..";
		link.l1 = "...";
		link.l1.go = "exit";
		pchar.questTemp.LSC.Natanstory = "ending";
		AddDialogExitQuest("Video_story");
		NextDiag.TempNode = "story_15";
		break;

	case "story_15":
		dialog.text = "Ese maldito barco se hundió. El sol volvió a brillar y el cielo se despejó. Y finalmente comenzamos a sentirnos felices... oh, ni siquiera puedes imaginar lo felices que estábamos. Habíamos vencido a la misma muerte. Momentos como esos unen a las personas. Y hicimos lo que deberíamos haber hecho mucho antes de ese encuentro: nos abrazamos, nos besamos, dijimos que nos amábamos y juramos quedarnos juntos para siempre.";
		link.l1 = "Y todavía estáis juntos...";
		link.l1.go = "story_16";
		break;

	case "story_16":
		dialog.text = "Sí, lo estamos. Dannie y yo nos casamos y nunca me he arrepentido. No encontrarás una mejor esposa y hermana de armas.";
		if (CheckAttribute(pchar, "questTemp.KhaelRoa"))
		{
			link.l1 = "Entonces, ahora finalmente sé quién es realmente ese misterioso capitán, que logró hundir el 'Holandés Errante'... ¡Eres un verdadero héroe!";
			link.l1.go = "story_17_1";
		}
		else
		{
			link.l1 = "Entonces, ¿vosotros dos sois verdaderos héroes? Lograsteis hundir el famoso barco fantasma. ¡Espera! Dijiste que el 'Holandés Errante' aún navega... ¿Cómo puede ser eso posible si yace en el fondo del mar?";
			link.l1.go = "story_17";
		}
		break;

	case "story_17":
		dialog.text = "Eh, compadre, no sabes nada... Puedes hundir a Van der Decken, pero no puedes matarlo. La maldición sobre él y su tripulación es demasiado fuerte, mucho más fuerte que la muerte...";
		link.l1 = "...";
		link.l1.go = "exit";
		pchar.questTemp.LSC.Natanstory = "VDDrepair";
		AddDialogExitQuest("Video_story");
		NextDiag.TempNode = "story_18";
		break;

	case "story_17_1":
		dialog.text = "Un héroe podría ser, pero a Van der Decken no se le puede matar. La maldición que pesa sobre él, su tripulación y su barco es más fuerte que la muerte...";
		link.l1 = "...";
		link.l1.go = "exit";
		pchar.questTemp.LSC.Natanstory = "VDDrepair";
		AddDialogExitQuest("Video_story");
		NextDiag.TempNode = "story_18";
		break;

	case "story_18":
		dialog.text = "Cada vez que hundes el barco, su tripulación lo repara, lo pone a flote y continúa su eterno viaje.";
		if (CheckAttribute(pchar, "questTemp.KhaelRoa"))
		{
			link.l1 = "Lo sé, Nathaniel, lo sé. Aun así, el Holandés Errante ya no molestará a nadie.";
			link.l1.go = "story_22";
		}
		else
		{
			link.l1 = "Bueno, esto suena como una fábula. Reparar un barco partido y hundido...";
			link.l1.go = "story_19";
		}
		break;

	case "story_19":
		dialog.text = "La gente ha visto el barco muchas veces después de que lo hundimos... Tú decides si creer en los avistamientos.";
		link.l1 = "¿Y dónde se encuentra esa isla con el templo, de donde obtuviste el artefacto?";
		link.l1.go = "story_20";
		break;

	case "story_20":
		dialog.text = "Está sin cartografiar y se encuentra en algún lugar al este del mar Caribe. Dejé un mapa de la isla en Maroon Town, pero como bien sabes, no puedo navegar allí ahora. Y para ser honesto, no quiero hacerlo. Lo único que recuerdo es su nombre: Khael Roa...";
		link.l1 = "¡Qué historia tan interesante! ¡Me gustaría encontrar esa isla!";
		link.l1.go = "story_21";
		break;

	case "story_21":
		dialog.text = "Oh, no lo recomiendo... No voy a hacerle otra visita, eso seguro.";
		link.l1 = "Me gustaría visitarlo de todos modos... Bien, ¡gracias por tu interesante historia! Ahora sé más sobre tu esposa. ¡Ambos sois leyendas vivientes!";
		link.l1.go = "diffindoor_19";
		DeleteAttribute(pchar, "questTemp.LSC.Natanstory");
		pchar.questTemp.NatanStory = "true";
		break;

	case "story_22":
		dialog.text = "¿Qué insinúas, camarada? ¿No te acabo de decir que no se le puede matar?";
		link.l1 = "Nathaniel, navegué a Khael Roa. Y visité el templo de los Chavins, donde tú, Danielle y un viejo estuvieron hace un cuarto de siglo. El artefacto que tomaste del templo en aquel entonces se llamaba 'orbe del sol naciente'. Ese artefacto fue lo que atrajo la atención del 'Holandés Errante' hacia ti. Su capitán era aficionado a los artefactos de los Chavins.";
		link.l1.go = "story_23";
		break;

	case "story_23":
		dialog.text = "¿Has estado en Khael Roa? ¡Pero eso no puede ser! ¿Me estás diciendo la verdad?";
		link.l1 = "Lo juro. Cuando me hablaste del laberinto y la estatua del pájaro gigante, inmediatamente supe dónde estaba ese lugar. El chamán caribeño Tuttuathapak me habló de tus aventuras. Fue él quien me dirigió a esa isla. Está ubicada al este de San Cristóbal. Es muy pequeña, con forma de anillo. Hay rocas alrededor y una pequeña cala dentro. Y solo hay un sendero cubierto de maleza que lleva a un templo, que está construido en forma de pirámide.";
		link.l1.go = "story_24";
		break;

	case "story_24":
		dialog.text = "¡Sí! Esto es Khael Roa. Pero, ¿por qué fuiste allí?";
		link.l1 = "Para eliminar la maldición del Caleuche... bueno, del 'Holandés Errante'. En realidad, su nombre era 'Corazón Errante', y el nombre de su capitán era 'Balthazar de Cordes'. Hace cincuenta años, fue maldecido por Yum Cimil, un dios indio de la muerte. Tomé el cráneo de jade de Yum Cimil, que había sido robado del templo por Balthazar hace algún tiempo, y lo coloqué de nuevo en el pedestal frente a esa estatua de cóndor...";
		link.l1.go = "story_25";
		break;

	case "story_25":
		dialog.text = "";
		link.l1 = "... al devolver la calavera, quité la maldición del Caleuche. Y como tenía otros dos amuletos Chavins conmigo, ella me atacó cerca de la isla, igual que te pasó a ti en aquel entonces. Pero sin la maldición, Balthazar ya no era inmortal, tal como dijo Tuttuathapak. Así que... el 'Holandés Errante' ya no existe. Yo personalmente me encargué de ella.";
		link.l1.go = "story_26";
		break;

	case "story_26":
		dialog.text = "¡Rayos y truenos! ¡Estoy asombrado! Tú... No estás bromeando al viejo Nathan, ¿verdad? No, puedo ver en tus ojos que estás diciendo la verdad. ¡Eres un verdadero héroe!";
		link.l1 = "Un héroe o no, pero he vivido mi buena dosis de aventuras, al igual que tú. Bueno, seguramente hablaremos del pasado muchas más veces, porque ahora tenemos un tema en común.";
		link.l1.go = "diffindoor_19";
		DeleteAttribute(pchar, "questTemp.LSC.Natanstory");
		break;

	case "diffindoor_19":
		dialog.text = "¿Vas a dejarme ahora, amigo?";
		link.l1 = "Sí, Nathan. Por favor, aguanta hasta que yo regrese. Cuídate. Y lo más importante, mantente vivo hasta que yo vuelva y todo estará bien. La Hermandad de la Costa te necesita, Danielle te necesita.";
		link.l1.go = "diffindoor_20";
		break;

	case "diffindoor_20":
		dialog.text = "¿Está Dannie ahora en tu tripulación? Te lo ruego, cuídala. No ha cambiado nada desde su juventud, sigue siendo una temeraria y no dudará en atravesar el infierno. Dile que la quiero mucho...";
		link.l1 = "Claro que sí. Regresaremos juntos por ti, te lo prometo, Nathan. Aguanta, y mantén la cabeza en alto. Ole te cuidará. ¡Nos vemos pronto!";
		link.l1.go = "diffindoor_21";
		break;

	case "diffindoor_21":
		DialogExit();
		LAi_SetGroundSitTypeNoGroup(npchar);
		NextDiag.CurrentNode = "diffindoor_wait";
		pchar.questTemp.LSC.NatanTalk = "true"; // атрибут - разговор с Натаном состоялся
		AddQuestRecord("BaronReturn", "10");
		npchar.greeting = "nathaniel_1";
		break;

	case "diffindoor_wait":
		dialog.text = "Ah, eres tú, " + pchar.name + ". ¿Aún no has dejado la isla?";
		link.l1 = "No te preocupes, Nathan, todo va según lo previsto. Descansa ahora.";
		link.l1.go = "exit";
		NextDiag.TempNode = "diffindoor_wait";
		break;

	case "danny":
		PlaySound("Voice\Spanish\saga\Nataniel Hawk-03.wav");
		dialog.text = "¿Dannie?.. ¡Dannie! ¡Mi amor!..";
		link.l1 = "... ";
		link.l1.go = "danny_1";
		break;

	case "danny_1": // перекидываем pchar
		DialogExit();
		LAi_SetActorType(pchar);
		SetMainCharacterIndex(GetCharacterIndex("Nathaniel"));
		PChar = GetMainCharacter();
		LAi_SetPlayerType(PChar);
		sld = characterFromId("Danielle");
		sld.dialog.currentnode = "nathaniel_6";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		NextDiag.CurrentNode = "danny_2";
		break;

	case "danny_2":
		dialog.text = "Gracias, mi amigo. Gracias por todo y especialmente por mi Dannie...";
		link.l1 = "De nada, Nathan.";
		link.l1.go = "exit";
		NextDiag.TempNode = "danny_2";
		break;

	// в Марун-Тауне
	case "marun_town":
		dialog.text = "¡Mira quién acaba de llegar! Es " + GetFullName(pchar) + "  ¡él mismo! ¡Entra, entra, amigo! ¿Cómo estás?";
		link.l1 = "Estoy bien. ¿Y tú, Nathan? Veo que no queda tristeza. Te ves bien. ¡Ojo de Serpiente lo ha hecho realmente bien!";
		link.l1.go = "marun_town_1";
		break;

	case "marun_town_1":
		ChangeCharacterComplexReputation(pchar, "fame", 3);
		dialog.text = "Sí, tu chamán es un hacedor de milagros. ¡Me siento incluso mejor que antes de esa maldita teleportación! ¡Me siento como si tuviera diez años menos!" + pchar.name + ", te debo mucho. Y estoy impresionado: ¡ayudaste a un completo desconocido, atravesaste el portal maldito, me arrebataste de las manos de la muerte y me devolviste a mi esposa!\n¡Y aún más! Nos has traído de vuelta nuestro barco y hogar. Ahora eres nuestro mejor amigo. Para siempre. Si alguna vez necesitas algo, ¡sabes a quién preguntar! Maroon Town siempre te proporcionará protección, apoyo y un santuario en caso de que lo necesites.\nToda la aldea luchará por ti si estás en peligro. Durante los tiempos de paz encontrarás aquí amistad, el mejor ron, una cama suave y un buen lugar para descansar. Dannie y yo nos aseguraremos de ello.";
		link.l1 = "¡Gracias, barón! Estoy sinceramente contento de verte con buena salud y... con Dannie.";
		link.l1.go = "marun_town_2";
		break;

	case "marun_town_2":
		dialog.text = "He estado esperando tu visita, " + pchar.name + ", y he preparado un regalo - un arma rara y poderosa. Tal vez, algún día necesites derribar a numerosos enemigos de un solo golpe y este mortero de mano te ayudará a hacerlo. La 'Sclopetta' dispara granadas especiales, así que también he preparado instrucciones sobre cómo fabricarlas. Aquí, tómalo.";
		link.l1 = "¡Qué excelente arma! ¡Gracias!";
		link.l1.go = "marun_town_3";
		break;

	case "marun_town_3":
		GiveItem2Character(pchar, "grape_mushket");
		GiveItem2Character(pchar, "recipe_grenade");
		Log_Info("Has recibido un mortero de mano");
		Log_Info("Has recibido instrucciones para granadas");
		PlaySound("interface\important_item.wav");
		dialog.text = "Ven a vernos más a menudo, " + pchar.name + "¡Dannie y yo siempre estaremos encantados de verte en cualquier momento!";
		link.l1 = "Será un placer para mí. ¡Espera verme pronto!";
		link.l1.go = "exit";
		NextDiag.TempNode = "marun_town_4";
		break;

	case "marun_town_4":
		dialog.text = "Ah, mi amigo " + GetFullName(pchar) + "¡Entra, entra, Capitán! ¿Cómo estás? ¿Necesitas ayuda?";
		// калеуче
		if (CheckAttribute(pchar, "questTemp.Caleuche.NatanInfo"))
		{
			link.l2 = "Nathan, he venido a ti por un asunto muy importante. ¿Recuerdas cuando me dijiste en la Isla de los Barcos Abandonados que tú y Dannie se colaron en un templo indio y hundieron al 'Holandés Errante'?";
			link.l2.go = "caleuche";
		}
		link.l1 = "Gracias, estoy bien. Solo quería verlos a ambos.";
		link.l1.go = "exit";
		NextDiag.TempNode = "marun_town_4";
		break;

	case "caleuche":
		dialog.text = "Por supuesto, lo hago.";
		link.l1 = "Necesito llegar a esa isla con el templo. Necesito encontrarla con urgencia. Dijiste que tenías un mapa de ella. ¿Puedes darme las coordenadas?";
		link.l1.go = "caleuche_1";
		break;

	case "caleuche_1":
		dialog.text = "Oh, amigo, esto es una empresa muy peligrosa, sabes... el templo de Khael Roa está maldito. Si supieras quién habita en sus pasillos...";
		link.l1 = "En este momento está habitado por monstruos mucho más aterradores en comparación con los que viste en aquel entonces. Y aun así iré allí.";
		link.l1.go = "caleuche_2";
		break;

	case "caleuche_2":
		dialog.text = "No me perdonaré si pereces allí. " + pchar.name + ", te lo suplico: ¡abandona esta empresa! Además, es donde se ve más a menudo al 'Holandés Errante'...";
		link.l1 = "Ya me he encontrado con eso, y sé cómo dejarlo atrás. Nathan, por favor, dame las coordenadas de Khael Roa y dime todo lo que sepas sobre ese templo, aparte de que está habitado por indios no muertos.";
		link.l1.go = "caleuche_3";
		break;

	case "caleuche_3":
		dialog.text = "Bueno... No puedo rechazaros, pero... ¡no tenéis idea de lo que Dannie y yo experimentamos allí! Khael Roa se encuentra al este de Antigua. Encontré su mapa justo cuando regresé a Maroon Town, está en... (mirando) las coordenadas: 19 grados 32' Norte, 62 grados 25' Oeste.";
		link.l1 = "Anotaré su ubicación en mi diario... ¡Gracias, Nathan!";
		link.l1.go = "caleuche_4";
		break;

	case "caleuche_4":
		dialog.text = "Puedes agradecérmelo más tarde. Ahora los detalles. La isla de Khael Roa es un anillo de rocas con una cala en su interior. Busca el paso entre los peñascos - es bastante profundo allí. En la cala, hay que echar el ancla y desembarcar en la playa. Busca un viejo sendero que se adentra en la isla: sólo hay uno. Te conducirá a una pirámide india: este es el templo que buscas.\nLa isla en sí es tranquila, pero el templo está plagado de abominaciones de todo tipo. La entrada se encuentra en la cima de la pirámide. Dentro habrá tres pasadizos; debes tomar el del medio. Luego avanza por el pasillo y encontrarás una plataforma con cuatro entradas o salidas. Aquí es donde las criaturas del templo me atacaron por primera vez, así que debes tener cuidado.\nLuego hay un laberinto. Es muy complejo, y yo, por mi vida, no puedo recordar la ruta correcta. Hay multitud de criaturas repugnantes en el laberinto. Debes matarlas a todas y luego caminar hasta una sala con dos entradas, seis columnas y una plataforma con nueve losas de piedra. Este es el vestíbulo del santuario. Su muro de piedra está cerrado, y no tengo ni idea de cómo vas a abrirlo.\nHay algún tipo de mecanismo, ¡pero juro por Dios que no tengo ni idea de cómo funciona! Usé un ídolo como llave. Lo introduje en la losa central, y la puerta se abrió. Pero tú no tienes ese ídolo, así que tendrás que averiguar cómo funciona este mecanismo.";
		link.l1 = "Está bien, haré lo mejor que pueda para resolverlo. ¿Qué hay del santuario?";
		link.l1.go = "caleuche_5";
		break;

	case "caleuche_5":
		dialog.text = "El santuario es un gran salón con un techo muy alto y grandes escaleras de piedra. No puedes usarlas - son demasiado viejas y en su mayoría están derrumbadas. Pero los constructores del templo, al parecer, también eran grandes hechiceros. Hay portales, como los de Kukulcán, y te llevarán de un lugar a otro.\nLos reconocerás fácilmente - parecen remolinos de colores. Habrá dos portales en el primer piso, pero uno de ellos es una trampa, ¡así que ten cuidado! El portal correcto te llevará al segundo piso. Allí debes encontrar otro portal para subir aún más alto, ¡y luego directamente al corazón del templo!\nAllí, junto a la gran estatua del pájaro, fue colocado ese artefacto mágico, que Dannie y yo habíamos llevado con nosotros. Y ya te conté lo que sucedió después.";
		link.l1 = "Recordaré lo que acabas de decirme. Gracias, Nathaniel. Me has ayudado enormemente.";
		link.l1.go = "caleuche_6";
		break;

	case "caleuche_6":
		dialog.text = "Cuídate, " + pchar.name + "El laberinto y los pasillos del templo están llenos de peligros. Un solo paso en falso y te quedarás allí para siempre.";
		link.l1 = "Praemonitus praemunitus, amigo. Fui advertido, eso significa que estoy preparado. Debo irme ahora. ¡Nos vemos!";
		link.l1.go = "caleuche_7";
		break;

	case "caleuche_7":
		dialog.text = "Buena suerte, " + pchar.name + ".";
		link.l1 = "¡Gracias!";
		link.l1.go = "caleuche_8";
		break;

	case "caleuche_8":
		DialogExit();
		DeleteAttribute(pchar, "questTemp.NatanStory");
		DeleteAttribute(pchar, "questTemp.Caleuche.NatanInfo");
		AddQuestRecord("Caleuche", "35");
		NextDiag.CurrentNode = "marun_town_4";
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}
