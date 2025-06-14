// Фадей Московит
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int rate;
	string sTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		if (CheckAttribute(pchar, "questTemp.Sharlie"))
		{
			if (pchar.questTemp.Sharlie == "fadey")
			{
				dialog.text = "¿Qué puedo hacer por usted, monsieur? No hablo con personas que no conozco. Si ha venido para charlar, o para preguntar a qué hora del mes llega el Flota de Plata Española a Maracaibo en 1640, entonces debo decepcionarlo. No pierdo mi tiempo en charlas ociosas.";
				link.l1 = "Buenas tardes, monsieur Fadey. Usted, por supuesto, puede que aún no me conozca, pero sí conoce a mi hermano. Permítame presentarme, soy Charles de Maure, hermano de Michel de Monper.";
				link.l1.go = "Sharlie";
				break;
			}
			if (pchar.questTemp.Sharlie == "takeknife" && !CheckAttribute(pchar, "questTemp.Persian"))
			{
				dialog.text = "¡Ajá, tú otra vez, Charles! ¿Kak dela? ¿Qué es esta vez?";
				link.l1 = "Dijiste que te han robado... ¿Has encontrado a los culpables?";
				link.l1.go = "Sharlie_8";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "fadey")
			{
				dialog.text = "Entonces, Charles, ¿has ido a hablar con ese salvaje?";
				link.l1 = "Así es... Por eso he vuelto a ti.";
				link.l1.go = "Tichingitu";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "dublon")
			{
				dialog.text = "¡Ah, eres tú de nuevo, mi querido amigo! Bueno, ¿has traído el rescate de doblones para el indio?";
				if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu80"))
				{
					if (PCharDublonsTotal() >= 80) // belamour legendary edition
					{
						link.l1 = "Sí. Aquí tienes tus 80 doblones.";
						link.l1.go = "Tichingitu_7";
					}
					else
					{
						link.l1 = "No, no he recolectado suficiente aún.";
						link.l1.go = "exit";
					}
				}
				else
				{
					if (PCharDublonsTotal() >= 100) // belamour legendary edition
					{
						link.l1 = "Sí. aquí están tus cien doblones.";
						link.l1.go = "Tichingitu_7";
					}
					else
					{
						link.l1 = "No, no he reunido lo suficiente todavía.";
						link.l1.go = "exit";
					}
				}
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "begin")
			{
				dialog.text = "¡Ja, pues es el mismo monsieur de Maure! ¡Dije que entres, no te quedes ahí parado! ¿Qué te trajo a mi morada?";
				link.l1 = TimeGreeting() + ", Fadey. Mi hermano me dijo que te viera. Dijo que me ayudarías a encontrar trabajo.";
				link.l1.go = "trial";
				// опоздал
				if (CheckAttribute(pchar, "questTemp.Trial.late"))
				{
					link.l1.go = "trial_late";
				}
				break;
			}
			if (pchar.questTemp.Sharlie == "trial" && !CheckAttribute(npchar, "quest.vodka"))
			{
				dialog.text = "¡Ja, eres tú! ¿Qué te trae por aquí, monsieur de Maure?";
				link.l1 = TimeGreeting() + ", Fadey. Mi hermano insistió en que no debería hablar contigo sobre esto, pero no pude mantenerme alejado... ";
				link.l1.go = "vodka";
				break;
			}
			// belamour legendary edition пиратская линейка -->
			if (CheckAttribute(pchar, "questTemp.Mtraxx.GiveMeSlaves") && pchar.questTemp.Mtraxx.GiveMeSlaves == "Baster")
			{
				dialog.text = "¡Ah, viejo amigo! Adelante, adelante, " + pchar.name + ". ¿Cómo estás?";
				link.l1 = TimeGreeting() + ", Fadey. Me alegra verte. En realidad, tengo un asunto importante que discutir. Oro negro.";
				link.l1.go = "Slaves";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.GiveMeSlaves") && pchar.questTemp.Mtraxx.GiveMeSlaves == "FindGold")
			{
				dialog.text = "¡Ah, eres tú otra vez, mi querido amigo! ¿Tienes el botín? ¿Encontraste suficientes doblones?";
				if (PCharDublonsTotal() >= 150)
				{
					link.l1 = "¡Sí, monsieur Fadey! Aquí está tu oro.";
					link.l1.go = "Slaves_2";
				}
				else
				{
					link.l1 = "No, sólo pasaba por aquí. Todavía estoy buscando la cantidad correcta.";
					link.l1.go = "exit";
				}

				link.l2 = "Fadey, se me acaba de ocurrir una idea. Ya no necesito a los esclavos. Debes disculparme, ¡te veré más tarde!";
				link.l2.go = "Slaves_3";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "Baster")
			{
				dialog.text = "¡Ah, mi viejo amigo! Entra, entra, " + pchar.name + ". ¿Cómo estás?";
				if (CheckAttribute(pchar, "questTemp.Mtraxx.GiveMeSlaves"))
				{
					if (pchar.questTemp.Mtraxx.GiveMeSlaves == "Deal" || pchar.questTemp.Mtraxx.GiveMeSlaves == "WithoutSlaves")
					{
						link.l1 = TimeGreeting() + ", necesito tu ayuda de nuevo.";
					}
				}
				else
				{
					link.l1 = TimeGreeting() + ", Fadey. Me alegra verte. Tengo asuntos contigo.";
				}
				link.l1.go = "pistols";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "FindMoney")
			{
				dialog.text = "¡Ah, eres tú otra vez, mi querido amigo! Bueno, ¿encontraste el dinero?";
				if (PCharDublonsTotal() >= 300)
				{
					link.l1 = "He cumplido, monsieur Fadey. Aquí tienes tus 300 doblones.";
					link.l1.go = "pistols_4D";
				}
				if (sti(Pchar.money) >= 40000)
				{
					link.l2 = "¡Los tengo, monsieur Fadey! Aquí están tus 40,000 pesos.";
					link.l2.go = "pistols_4P";
				}
				if (PCharDublonsTotal() < 300 || sti(Pchar.money) < 40000)
				{
					link.l3 = "No, solo de visita. Todavía estoy buscando la cantidad adecuada.";
					link.l3.go = "exit";
				}
				link.l4 = "Disculpa, Fadey, pero no puedo permitírmelo. Intentaré arreglármelas por mi cuenta. ¡Nos vemos!";
				link.l4.go = "pistols_x";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "Today")
			{
				dialog.text = "Entra, entra, " + pchar.name + "¡Puedo ver en tus ojos que quieres escuchar sobre mi éxito!";
				link.l1 = "Exactamente, Fadey. Confío en que tienes lo que quiero.";
				link.l1.go = "pistols_5";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "FindMoney")
			{
				dialog.text = "¡Ah, eres tú otra vez, mi querido amigo! Entonces, ¿encontraste el dinero?";
				if (PCharDublonsTotal() >= 300)
				{
					link.l1 = "Toma 300 doblones. Pediré a los marineros que lleven esta caja a mi barco. Oh, ¿qué haría sin ti, Fadey? ¡No tienes idea de cuánto me has ayudado!";
					link.l1.go = "pistols_5D";
				}
				if (sti(Pchar.money) >= 40000)
				{
					link.l2 = "Toma 40.000 pesos. Pediré a los marineros que lleven esta caja a mi barco. Oh, ¿qué haría sin ti, Fadey? ¡No tienes idea de cuánto me has ayudado!";
					link.l2.go = "pistols_5P";
				}
				if (PCharDublonsTotal() < 300 || sti(Pchar.money) < 40000) // возможность найти без отказа
				{
					link.l3 = "No, solo pasé por aquí. Todavía estoy tratando de reunir lo suficiente.";
					link.l3.go = "exit";
				}
				link.l4 = "Disculpa, Fadey, estoy completamente arruinado. Quédate con el depósito, espero que sea suficiente para compensar tus gastos con este trato, y trataré de arreglármelas por mi cuenta. ¡Nos vemos!";
				link.l4.go = "pistols_x";
				break;
			}
			// <-- legendary edition
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Baster_church") && pchar.questTemp.Guardoftruth.Baster_church == "seek")
			{
				dialog.text = "Ah, ¡marcado! Quiero decir, " + pchar.name + ", ¡vamos, dime qué tienes para mí!";
				link.l1 = TimeGreeting() + ", Fadey. Encantado de verte. He venido a hablar contigo sobre negocios.";
				link.l1.go = "guardoftruth";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Baster_church") && pchar.questTemp.Guardoftruth.Baster_church == "find" && !CheckAttribute(npchar, "quest.utensil"))
			{
				dialog.text = TimeGreeting() + ", " + pchar.name + ". Apuesto a que estás ansioso por descubrir los resultados de mi conversación introspectiva con el sacerdote.";
				link.l1 = "¡Por supuesto que sí! ¿Cómo te fue?";
				link.l1.go = "guardoftruth_9";
				break;
			}
			if (CheckAttribute(npchar, "quest.utensil") && PCharDublonsTotal() >= 250)
			{
				dialog.text = "¡Ah, perdóname, estoy tan distraído por el tintineo en tus bolsillos!";
				link.l1 = "¡Qué avaricia, Fadey! Aquí está tu oro.";
				link.l1.go = "guardoftruth_11";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "guadeloupe")
			{
				dialog.text = "¡Ajá, mi viejo amigo! Entra, entra, " + pchar.name + ". Entonces, ¿tienes algo nuevo?";
				link.l1 = "Hola, Fadey. Una vez más, estoy pidiendo tu apoyo.";
				link.l1.go = "guardoftruth_14";
				break;
			}
			dialog.text = "¿Qué eres tú? ¿Una estatua? Si tienes algo, suelta la lengua, si no, ¡piérdete " + pchar.name + "!";
			if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "start" && CheckNCountPersian() > 0)
			{ // персидские клинки
				link.l2 = "Echa un vistazo, Fadey. Supongo que esto es un shamshir persa, ¿posiblemente uno de esos robados de tu colección?";
				link.l2.go = "persian";
			}
			if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "one" && CheckNCountPersian() > 0)
			{
				link.l2 = "Tengo buenas noticias para ti. Tengo aquí otro shamshir persa para ti.";
				link.l2.go = "persian_6";
			}
			if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "two" && CheckNCountPersian() > 0)
			{
				link.l2 = "Tengo un tercer shamshir persa. Tal como me pediste, lo traje de vuelta tan pronto como pude.";
				link.l2.go = "persian_9";
			}
			if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "cirass")
			{
				link.l2 = "Estoy aquí por la armadura ligera de la que hablamos.";
				link.l2.go = "persian_13";
			}
			if (CheckAttribute(npchar, "quest.ropes") && GetDataDay() == 20) // торговля канатами
			{
				link.l3 = "Fadey, me gustaría comprar algo de tu famosa cuerda.";
				link.l3.go = "ropes";
			}
			link.l1 = "Fadey, necesito tu ayuda.";
			link.l1.go = "help";
			link.l9 = "No, nada en este momento.";
			link.l9.go = "exit";
		}
		else
		{
			dialog.text = "¿Qué puedo hacer por usted, monsieur? No hablo con personas que no conozco.";
			link.l1 = "Ah, solo pasé por aquí para ver quién vive aquí.";
			link.l1.go = "exit";
		}
		NextDiag.TempNode = "First time";
		break;

	case "Sharlie":
		DelLandQuestMark(npchar);
		QuestPointerDelLoc("baster_town", "reload", "houseSp1");
		dialog.text = "¡Ah, entonces eres el hermanito del buen viejo Michel! ¡Eso cambia la situación! Adelante, adelante, monsieur, siéntese. ¿Le gustaría levantar una copa de vodka por nuestro encuentro? Todavía me quedan algunas botellas, y sería un placer compartir una de ellas con el hermano de un buen amigo, ¡da!";
		link.l1 = "Perdóname, monsieur Fadey, pero beber no está en los planes de esta noche. Preferiría ir directo al grano.";
		link.l1.go = "Sharlie_1";
		break;

	case "Sharlie_1":
		dialog.text = "¡Qué dices! ¡Este ron es agua de orina débil comparado con el vodka ruso! ¡No sabes de lo que te estás perdiendo, que me lleve el mar si miento! Bien, al grano entonces. Soy todo oídos, Charles.";
		link.l1 = "Monsieur, sospecho que lo que estoy a punto de decirle le resultará bastante desagradable, pero, ¡ay!, estoy obligado por el deber a decírselo. Michel me ha dicho que le debe una buena cantidad de dinero por jugar con él. También ha indicado que me entregue el dinero a mí, porque mi hermano está... incapaz de venir a verle personalmente en este momento.";
		link.l1.go = "Sharlie_2";
		break;

	case "Sharlie_2":
		dialog.text = "¡Oh, joven! Por supuesto, recuerdo todo y admito que le debo a tu hermano. Una deuda de juego es sagrada, honrar ese deber es lo único que nos salva de la anarquía mortal y de los peligrosos bandidos. Pero te ruego, por favor, que entiendas mi situación. Me sucedió recientemente una historia desagradable: ¡fui robado de la manera más descarada!\n¡Malditos ladrones! Se llevaron todo lo que pudieron, todo lo que había ganado en años de trabajo, ¡mi dinero y mi invaluable colección! Simplemente no puedo saldar una deuda ahora, nyet.\nPero, monsieur de Maure, ¡no abandono mis obligaciones! Solo te pido que nos encontremos a mitad de camino. Como no tengo ninguna moneda en mi posesión ahora mismo, te ofrezco este excelente y raro puñal. ¡Échale un vistazo!\nEs una verdadera obra maestra de acero, el orgullo de mi colección robada. Además, fue encantado por chamanes indios y tiene fuertes poderes ocultos. Los indios lo llamaban la Garra del Jefe.\nNunca hubiera aceptado regalarlo porque pagué una gran suma por el puñal, mucho bolshe que mi deuda, pero considerando las circunstancias y mi relación con tu hermano mayor, estoy dispuesto a dártelo. ¡Beri, es un trato muy bueno!";
		link.l1 = "Realmente preferiría el dinero en lugar de un cuchillo...";
		link.l1.go = "Sharlie_3";
		break;

	case "Sharlie_3":
		dialog.text = "¡Pero no tengo el dinero y sí tengo este raro artefacto encantado! ¿Realmente piensas, droga moy, que te ofrecería este magnífico puñal mágico en lugar de algunas monedas de plata en otras circunstancias? ¡Puedes encontrar pesos en cualquier lugar, incluso tirados en la calle! Tienes que admitir, estoy en un pequeño aprieto aquí. Mi corazón sangra cuando siquiera pienso en separarme de esta increíble obra de artesanía, pero una deuda de juego es una deuda de honor, así que estoy dispuesto a darte solo a ti, aunque es muy valioso para mí, porque eres un verdadero hombre de honor y un verdadero amigo.";
		link.l1 = "Está bien, ya que juras que no tienes dinero, me llevaré este puñal mágico tuyo. Espero poder venderlo a buen precio...";
		link.l1.go = "Sharlie_4";
		break;

	case "Sharlie_4":
		dialog.text = "¿¡'Venderlo'!? ¡Sal de aquí, mald-I quiero decir, Charles! ¡Nyet, apenas puedo creer lo que escucho! Estoy regalando mi posesión más preciada, por la que obtendría al menos diez veces más en Europa, ¿y te atreves a decir impertinentemente que simplemente vas a empeñarla? ¡Este puñal, joven, salvó la vida de un hombre! Déjame contarte...";
		link.l1 = "¿Y cuál es ese poder oculto que mencionaste?";
		link.l1.go = "Sharlie_5";
		break;

	case "Sharlie_5":
		dialog.text = "¡Oh, ho ho! Ahora, Charles, soy un buen cristiano, no un chamán indio. No tengo manera de conocer todas las propiedades ocultas de esta hoja. ¡Pero existen, oh sí! ¡Sujeta este puñal en tu mano y sentirás el poder dentro de ti mismo! ¡Tómalo, beri! ¿Qué tal eso? ¿Sientes algo?";
		link.l1 = "Mm... No siento nada. Aunque se ajusta cómodamente a mi mano.";
		link.l1.go = "Sharlie_6";
		break;

	case "Sharlie_6":
		dialog.text = "¡Ah ja! ¡Ahí lo tienes! Pero eso es solo la menor de sus cualidades. Si blandes este puñal en batalla, ¡estoy seguro de que mostrará su poder de muchas maneras dramáticas! Bueno, entonces, ¿te lo llevas?";
		link.l1 = "Bueno, ¿tengo otra opción? Lo tomaré ya que no tienes el dinero...";
		link.l1.go = "Sharlie_7";
		break;

	case "Sharlie_7":
		GiveItem2Character(pchar, "knife_01");
		PlaySound("interface\important_item.wav");
		// Log_Info("¡Has recibido la Garra del Jefe!");
		sld = ItemsFromID("knife_01");
		sld.Weight = 1.5;
		sld.price = 0;
		AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
		AddMapQuestMarkCity("FortFrance", false);
		dialog.text = "Spasibo, Charles. No te arrepentirás, ¡oh, ciertamente no lo harás! Aquí tienes. Y asegúrate de saludar a Michel de mi parte. ¡Dile que venga a visitarme, en cuanto tenga la oportunidad!";
		link.l1 = "Oh, le diré...";
		link.l1.go = "exit";
		link.l2 = "Dijiste que te habían robado... ¿Has encontrado a los culpables?";
		link.l2.go = "Sharlie_8";
		pchar.questTemp.Sharlie = "takeknife";
		AddQuestRecord("Sharlie", "18-1");
		sld = characterFromId("Mishelle");
		sld.greeting = "mishelle_2";

		// Sinistra - Старт квеста "Деньги на деревьях"
		PChar.quest.MOT_BarbieSpawn.win_condition.l1 = "location";
		PChar.quest.MOT_BarbieSpawn.win_condition.l1.location = "BasTer_town";
		PChar.quest.MOT_BarbieSpawn.win_condition = "MOT_BarbieSpawn";
		// убрать запрет боёвок на Мартинике
		LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_town")], false);
		LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_townhall")], false);
		LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_prison")], false);
		LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_fort")], false);
		LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_ammo")], false);
		LAi_LocationFightDisable(&Locations[FindLocation("LeFransua_town")], false);
		LocatorReloadEnterDisable("FortFrance_townhall", "reload2", false);
		LocatorReloadEnterDisable("FortFrance_townhall", "reload3", false);
		sld = &Locations[FindLocation("FortFrance_prison")];
		sld.locators_radius.item.detector1 = 0.5;
		break;

	case "Sharlie_8":
		dialog.text = "El problema es que no lo he hecho. Esos rufianes arrasaron con toda la casa, se llevaron toda la plata, el oro, mis ahorros de años de trabajo agotador. Ahora, eso usualmente no me molesta, después de todo, un verdadero caballero, incluso si pierde todo lo que posee, ¡no debe mostrar emoción alguna! El dinero debe estar tan por debajo de un caballero que apenas vale la pena preocuparse por ello. Pero la peor parte es que se llevaron mi magnífica colección de shamshirs persas. No hay una colección como esa en todo el Nuevo o Viejo Mundo combinados. Verdaderamente notables espadas de caballería persas...";
		link.l1 = "¿Espadas persas, dices? Suena bastante interesante. Entonces, ¿eres un coleccionista?";
		link.l1.go = "Sharlie_9";
		break;

	case "Sharlie_9":
		dialog.text = "Bueno, me gusta coleccionar cosas raras... Escucha, Charles, tal vez podrías ayudarme en este asunto...";
		link.l1 = "¿Ayuda? ¿Pero cómo? ¿Te refieres a atrapar a los ladrones?";
		link.l1.go = "Sharlie_10";
		break;

	case "Sharlie_10":
		dialog.text = "No. No estoy particularmente interesado en los ladrones. Me gustaría recuperar mis sables de caballería persas. Si los encuentras, definitivamente te recompensaré, lo prometo.";
		link.l1 = "Mm. Pero, ¿dónde debería buscarlos? ¿Por el Caribe? ¿O quizás por todo el mundo?";
		link.l1.go = "Sharlie_11";
		break;

	case "Sharlie_11":
		dialog.text = "Bueno, tal vez los veas en las islas con algunos mercaderes callejeros, esos canallas ni siquiera pueden comprender el valor de esos sables de caballería y seguramente los venderán por migajas. Así que si ves las espadas persas en alguna parte, tráemelas. ¿Podrás reconocerlas?";
		link.l1 = "Creo que lo haré. Está bien, mantendré los ojos bien abiertos y si veo alguna hoja inusual que coincida con la descripción, definitivamente te la traeré.";
		link.l1.go = "Sharlie_12";
		link.l2 = "Sabes, no soy un experto en armas finas. Me temo que no podré ayudar. Así que sería deshonesto de mi parte dar falsas esperanzas.";
		link.l2.go = "Sharlie_13";
		break;

	case "Sharlie_12":
		dialog.text = "¡Horosho! Espero que tengas suerte y encuentres esos artefactos, y haré que valga la pena. Buena caza, acosador- quiero decir capitán. ¡Da, Charles, puedes imaginarlo, tuve otro intento de robo recientemente!\nUn ladrón intentó entrar a mi casa hace solo unos días\n¡Eso fue demasiado para mí! Sin embargo, esta vez no escapó de mí, logré atraparlo, le di una buena paliza y lo entregué a los guardias en la prisión de la ciudad. ¡Espero que lo cuelguen pronto!";
		link.l1 = "¿Crees que es uno de los ladrones que se llevaron tus shamshirs?";
		link.l1.go = "Sharlie_14";
		pchar.questTemp.Persian = "start";
		// --> скимитар 021012
		pchar.questTemp.Persian.skimitar = "true";
		pchar.quest.Persian.win_condition.l1 = "item";
		pchar.quest.Persian.win_condition.l1.item = "blade_23";
		pchar.quest.Persian.function = "Persian_FindSkimitar";
		break;

	case "Sharlie_13":
		dialog.text = "Lástima, pero no sirve de nada llorar por la luna. ¡Da, Charles, imagínate, hace poco tuve otro intento de robo!\nUn ladrón intentó entrar a mi casa hace solo unos días.\n¡Eso fue demasiado para mí! Sin embargo, no escapó de mí: logré atraparlo, le di una buena paliza y lo envié a la prisión. No puedes ser feliz a expensas de la desgracia ajena. ¡Espero que lo cuelguen pronto!";
		link.l1 = "¿Crees que es uno de los ladrones que se llevaron tus shamshirs?";
		link.l1.go = "Sharlie_14";
		pchar.questTemp.Persian = "end";
		break;

	case "Sharlie_14":
		dialog.text = "No, no lo creo. Estaba tras el dinero. Lo pillé en mi habitación, hurgando en mis cofres. Un indio de alguna selva profunda del Continente Español. Se ve ridículo, diferente de los locales de aquí. Todo cubierto de pintura de guerra y vestido con un traje colorido... Deberías visitar la mazmorra, y ver a ese bufón tú mismo si quieres, mientras aún vive.";
		link.l1 = "Mm... Quizás pase a verlo.";
		link.l1.go = "Sharlie_15";
		break;

	case "Sharlie_15":
		dialog.text = "Adelante, échale un vistazo al espectáculo de fenómenos... Horosho, Charles, fue una charla agradable. Que los vientos te acompañen de regreso a Martinica, poputniy veter!";
		link.l1 = "Todo lo mejor para ti, Fadey.";
		link.l1.go = "exit";
		SetQuestHeader("Tichingitu");
		AddQuestRecord("Tichingitu", "1");
		pchar.questTemp.Sharlie.Tichingitu = "true";
		AddDialogExitQuestFunction("SetTichingituJail");
		SetFunctionTimerCondition("FreeTichingituOver", 0, 0, 10, false);
		pchar.questTemp.Sharlie = "takeknife";
		break;

	case "Tichingitu":
		DelLandQuestMark(npchar);
		dialog.text = "¡Qué interesante! Estoy escuchando.";
		link.l1 = "Fadey, he hablado con ese indio. Y vine a ti para pedirte ayuda para sacarlo. El pobre desgraciado solo quería algo de comer...";
		link.l1.go = "Tichingitu_1";
		break;

	case "Tichingitu_1":
		dialog.text = "Ja-ja-ja, ¿y creíste esa historia? Los jóvenes de hoy en día son tan crédulos...";
		link.l1 = "Fadey, puedo ser más joven que tú, pero incluso yo puedo notar cuándo me dicen la verdad y cuándo me están mintiendo. Además, ¿de verdad crees que la horca es un castigo apropiado para ese tipo de delito? Parece excesivo. En casa solo recibirías unos cuantos latigazos o una marca para un reincidente.";
		link.l1.go = "Tichingitu_2";
		break;

	case "Tichingitu_2":
		dialog.text = "¡¿Excesivo!? ¡Irrumpió en mi casa! ¡Ese salvaje nunca debería haber venido aquí! ¿Qué harías tú si estuvieras en mi situación? ¡Estoy seguro de que le convertirías las entrañas en exteriores y lo harías comida para gusanos, ¿da?!";
		link.l1 = "No, no lo haría, Fadey, aún estás enojado por tu colección de shamshir robada. Si eso no hubiera pasado, estarías más inclinado a darle a este tonto piel roja una buena paliza y una patada en el trasero, ¿me equivoco?";
		link.l1.go = "Tichingitu_3";
		break;

	case "Tichingitu_3":
		dialog.text = "Ahhhh, Charles... Eres igual que tu hermano... Horosho. Arreglaremos esto como hombres de negocios honestos. Ya que deseas tanto a este indio, compénsame por el daño moral y los daños a la propiedad que ha causado y, a cambio, le diré al comandante que no deseo presentar cargos. ¿Cómo suena eso?";
		link.l1 = "¿Cuánto?";
		link.l1.go = "Tichingitu_4";
		break;

	case "Tichingitu_4":
		dialog.text = "Ja, ya estás empezando a aprender los caminos del Caribe, Charles. Ciento cincuenta doblones de oro, ni un kopek menos.";
		link.l1 = "Fadey, que Dios tenga piedad...";
		link.l1.go = "Tichingitu_5";
		break;

	case "Tichingitu_5":
		dialog.text = "Horosho, horosho. Cien doblones de oro. Pero esa es mi oferta final. Y estamos hablando de doblones, no de pesos. Nuestro banquero seguramente podrá reunir esa cantidad para el intercambio.";
		if (PCharDublonsTotal() >= 100) // belamour legendary edition
		{
			link.l1 = "Tengo la cantidad que necesitas ahora mismo. Aquí tienes, aquí están tus cien doblones.";
			link.l1.go = "Tichingitu_7";
		}
		if (CheckCharacterPerk(pchar, "Trustworthy"))
		{
			notification("Trustworthy", "Trustworthy");
			link.l2 = "Fadey, escucha... Entiendo tu frustración, pero soy el único dispuesto a compensarte con dinero real por este inconveniente.";
			link.l2.go = "Tichingitu_7_TW";
		}
		else
			notification("Perk Check Failed", "Trustworthy");
		link.l3 = "Está bien, iré a buscar lo que necesitas.";
		link.l3.go = "Tichingitu_6";
		break;

	case "Tichingitu_7_TW":
		dialog.text = "Tienes un futuro aquí, amigo mío, eso te lo puedo asegurar. ¡Está bien! Ochenta de oro, y ni una moneda menos.";
		link.l1 = "";
		link.l1.go = "Tichingitu_6";
		pchar.questTemp.Sharlie.Tichingitu80 = true;
		break;

	case "Tichingitu_6":
		dialog.text = "¡Y date prisa, Charles! Solo tienes diez días hasta que lo ejecuten.";
		link.l1 = "Lo tendré en cuenta. ¡Adiós!";
		link.l1.go = "exit";
		pchar.questTemp.Sharlie.Tichingitu = "dublon";
		break;

	case "Tichingitu_7":
		if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu80"))
		{
			RemoveDublonsFromPCharTotal(80);
			DeleteAttribute(pchar, "questTemp.Sharlie.Tichingitu80");
		}
		else
			RemoveDublonsFromPCharTotal(100); // belamour legendary edition
		PlaySound("interface\important_item.wav");
		dialog.text = "Muy bien. Escribiré una nota ahora mismo y le pondré mi sello, espera un segundo... aquí tienes. Dale esto al comandante y puedes llevarte a tu indio contigo. No estoy seguro de por qué exactamente te preocupas tanto por él, pero ese es tu problema. ¿Qué vas a hacer, ponerlo en exhibición en un mascarada? Ja-ja, ¡qué ocurrencia!";
		link.l1 = "Dios lo ve todo, Fadey. Salvar la vida de un hombre es una obra noble.";
		link.l1.go = "Tichingitu_8";
		break;

	case "Tichingitu_8":
		GiveItem2Character(pchar, "letter_1");
		ChangeItemDescribe("letter_1", "itmdescr_letter_1_Fadey");
		PlaySound("interface\important_item.wav");
		dialog.text = "Estoy de acuerdo con tu primera afirmación, pero la segunda es discutible, Charles. ¿Qué pasa si salvas a un asesino o un violador de la justicia que le espera al final de una soga?  Bah, lo que sea, ya no es mi problema. Que Dios esté contigo. Ve al comandante antes de que tu amigo de piel roja se ponga pálido por una soga alrededor de su cuello...";
		link.l1 = "Estoy en camino. Nos vemos luego, Fadey.";
		link.l1.go = "exit";
		pchar.questTemp.Sharlie.Tichingitu = "pay";
		SetFunctionLocationCondition("Tichingitu_AddQuestMark", "baster_prison", false);
		QuestPointerToLoc("BasTer_town", "reload", "reload_jail");
		QuestPointerDelLoc("baster_town", "reload", "houseSp1");
		break;

	case "vodka":
		dialog.text = "¡Pareces sombrío, amigo mío! ¿Supongo que estás a punto de darme malas noticias?";
		link.l1 = "Eso es todo, sí. Seré franco contigo, Fadey: Michel dijo que me engañaste con esta mierda de 'Garra del Jefe'. Dijo que esto no es un artefacto, y que podría comprarlo a cualquier comerciante callejero por un par de cientos de pesos. Pregunté entre los vendedores callejeros que tratan con artículos de metal. Me dieron exactamente ese precio.";
		link.l1.go = "vodka_1";
		npchar.quest.vodka = "true";
		break;

	case "vodka_1":
		dialog.text = "¡Oh, monsieur de Maure... estoy herido! Me sorprende tu hermano. Esos charlatanes medio tontos en la calle pueden decir lo que quieran, ¡pero él! Dime, Charles, si alguien te trajera una vieja espada de caballero de dos manos de los tiempos de Carlomagno y te ofreciera venderla, ¿qué darías por ella?";
		link.l1 = "¿Una mandoble? ¿Te burlas de mí, Fadey? ¿Para qué me serviría una vieja espada de verdugo oxidada? ¡Este es el siglo diecisiete del Señor Jesucristo! ¡No daría ni un solo peso por ella!";
		link.l1.go = "vodka_2";
		break;

	case "vodka_2":
		dialog.text = "¡Ah, ahora ves tu miopía, amigo mío! Nunca lo lograrás con esa actitud. Y si me trajeras tal artefacto, te pagaría trescientas monedas de oro por él. ¿Preguntas por qué? ¡Porque es una antigüedad, un tesoro histórico difícil de encontrar en estos tiempos! ¡No entiendes, pero juzgas! \nCon Dios y Su Bendita Madre como testigos, la Garra del Jefe es un puñal magistral, mis fuentes me dicen que el mismo Cortés lo poseía. ¡EL Hernán Cortés! ¡El legendario conquistador que saqueó Tenochtitlán y capturó al emperador de los aztecas! ¡Y tú te burlas y dices que es basura común!\nAdemás, ya te he dicho que no es cualquier puñal, ¡es un puñal encantado! ¿Todavía eres tan novato que no has visto todas las maravillas del Caribe? ¿Hechizos y magia, rituales y maldiciones? ¡Charles, este es el Nuevo Mundo, la tierra natal de los mayas y aztecas cuyo conocimiento de tales artes diabólicas alcanzó alturas inconcebibles para nosotros, los cristianos!\nEste puñal tiene poderes ocultos. Lamentablemente, nadie sabe todavía qué tipo de poderes. Tienes una oportunidad única e increíble de descubrir por ti mismo de qué es capaz y sin embargo sigues afirmando que es una 'porquería' y que tu querido y pobre viejo amigo Fadey intentó engañarte.\nSi tan solo tuviera suficiente dinero para cubrir mi deuda con tu hermano, lo cambiaría inmediatamente contigo por tu despreciable moneda... Este es un objeto muy valioso y su costo se valora en más que solo dinero, ¡da!";
		link.l1 = "Está bien, está bien, cálmate Fadey. Te creo. Tus argumentos son bastante convincentes y el ardor ardiente que demuestras es un testimonio de tu sinceridad, o de tu engaño sin igual.";
		link.l1.go = "vodka_3";
		break;

	case "vodka_3":
		dialog.text = "¡Gracias! Has hecho bien, Charles, por no ofenderte y venir directamente a mí por una explicación. ¿Confío en que ahora el asunto está resuelto?";
		link.l1 = "Sí, monsieur Fadey. Completamente. Ahora, por favor, permítame retirarme...";
		link.l1.go = "vodka_4";
		break;

	case "vodka_4":
		PlaySound("Voice\Spanish\sharlie\Fadey Moskovit-03.wav");
		dialog.text = "¡Detente, Charles! Seré honesto, me gusta tu estilo. Tal vez tú y yo podríamos llegar a ser los mejores amigos algún día. ¿Y por qué no dar el primer paso hacia esa amistad ahora mismo? He estado enfriando dos botellas de excelente vodka ruso en agua de manantial helada abajo en la bodega. ¿Qué dices si abrimos una botella a la salud de tu hermano?";
		link.l1 = "Mm. Lo siento, Monsieur Fadey, pero ya es hora de que me embarque al mar. Estoy un poco apurado.";
		link.l1.go = "vodka_no";
		link.l2 = "La última vez ofreciste y me negué... Sería descortés negarme dos veces. Está bien, Fadey. ¡Estoy dentro!";
		link.l2.go = "vodka_5";
		break;

	case "vodka_no":
		dialog.text = "Eso es una pena. En comparación con el vodka, el ron es solo agua, un brebaje barato y aguado. Pero ya que tienes prisa, no te retendré más. ¡Buena caza, Charles!";
		link.l1 = "Lo mismo para usted, monsieur Fadey...";
		link.l1.go = "exit";
		break;

	case "vodka_5":
		dialog.text = "¡Eso es lo que me gusta oír! ¡Espléndido! ¡Toma asiento y descansa los pies! Por favor, monsieur, siéntete como en casa mientras voy a buscar el vodka. ¡Oh, cuánto he echado de menos estas reuniones vespertinas con amigos! Ah, el vodka está bien frío, seguro que lo disfrutarás, ¡na zdorovie! Permíteme poner unos encurtidos y jamón ahumado.";
		link.l1 = "...";
		link.l1.go = "vodka_6";
		break;

	case "vodka_6":
		DialogExit();
		sld = ItemsFromID("potionrum");
		sld.shown = true;
		sld.startLocation = "BasTer_houseSp1";
		sld.startLocator = "bottle";
		sld = ItemsFromID("lcheer");
		sld.shown = true;
		sld.startLocation = "BasTer_houseSp1";
		sld.startLocator = "sit2";
		DoQuestReloadToLocation("BasTer_houseSp1", "sit", "sit2", "Sharlie_DrinkWithFadey");
		NextDiag.CurrentNode = "vodka_7";
		break;

	case "vodka_7":
		dialog.text = "";
		link.l1 = "Vaya... Entonces, d-dime, Fadey, ¿c-cómo funciona e-eso? ¡Hic! Hemos bebido... d-dos botellas de v-vodka... ¡por cierto! - pareces t-tan s-sobrio como una piedra y yo estoy... borracho como una cuba. ¿C-cómo es eso, eh?";
		link.l1.go = "vodka_8";
		break;

	case "vodka_8":
		dialog.text = "Charles, drug moy, relájate. ¿Qué tiene que ver un zorrillo con todo esto? Acabamos de tomar un excelente vodka. Duerme un poco y estarás fresco como una lechuga al despertar. Incluso tu cabeza estará despejada sin resaca. Ya verás.";
		link.l1 = "Sí, sí, vodka... es... es absolutamente magnífico, este vodka. Nunca he bebido algo parecido.";
		link.l1.go = "vodka_9";
		break;

	case "vodka_9":
		dialog.text = "¡Ja! ¡Tienes razón! Este tipo de vodka se hace según recetas secretas y se envía desde mi madre patria, Rusia, y ni siquiera allí todos saben cómo hacerlo correctamente. ¡Yo compro solo lo mejor! Como este brebaje que tú y yo hemos tenido la oportunidad de probar.";
		link.l1 = "¿P-pero dime, Fadey: c-cómo p-puedes beber t-tanto y no emborracharte? ¿C-cómo lo haces, eh? Comparte el secreto conmigo. Q-quizás me sirva de algo más tarde... ¡Hip!";
		link.l1.go = "vodka_10";
		break;

	case "vodka_10":
		dialog.text = "¡Ja! Bueno, no puedes compararte conmigo, joven Charles. Solo mírate, flaco como un látigo. Además, no estás acostumbrado a beber en serio, ¡ha! Pero como somos verdaderos amigos, te compartiré algunos secretos sobre cómo beber y no orinarte encima.";
		link.l1 = "Po-favor h-ha... ¡hip!";
		link.l1.go = "vodka_11";
		break;

	case "vodka_11":
		dialog.text = "Bueno, si quieres beber y no terminar borracho al instante, debes seguir unas cuantas reglas clave. Lo más importante, nunca bebas si tu estómago está vacío. Come algo sustancioso antes de que empiece la sesión de bebida.\nEn segundo lugar, no olvides comer algo después de cada copa. La carne o el pescado serán lo mejor, algo rico y salado. En tercer lugar, no enjuagues el interior de tu boca con el vodka, trágatelo de una vez.\nAdemás, beber un pequeño trago, no más de media pinta, antes del plato principal preparará tu cuerpo para recibir dosis serias de alcohol. No exageres con este aperitivo, de lo contrario el efecto será todo lo contrario y te destrozarás antes de zarpar.\nFinalmente, el entrenamiento disciplinado es clave, beber cantidades moderadas de ron u otros tipos de alcohol de manera regular te hará más resistente a ellos.";
		link.l1 = "Hm-mm... A-así es como se hace. D-definitivamente... ¡hip!.. recordaré todas tus in-strucciones, Fadey. Gr-gracias. Y a-ahora creo que sería una b-buena idea que me t-tomara una siesta, porque no me siento muy bien ahora.";
		link.l1.go = "vodka_12";
		break;

	case "vodka_12":
		dialog.text = "Descansa un poco, Charles. ¡Hemos tenido una agradable velada, tú y yo! ¡Buena caza para ti!";
		link.l1 = "¡A-a-adiós, Fadey! Me voy al, ¡hip! - el Concededor de Deseos!";
		link.l1.go = "vodka_13";
		break;

	case "vodka_13":
		DialogExit();
		sld = ItemsFromID("potionrum");
		sld.shown = false;
		sld = ItemsFromID("lcheer");
		sld.shown = false;
		pchar.questTemp.CanDrink = true; // Шарль теперь знает секреты выпивки, это ему потом пригодится
		LAi_SetSitType(npchar);
		LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
		NextDiag.CurrentNode = "First time";
		break;

	case "trial":
		DelLandQuestMark(npchar);
		DelMapQuestMarkCity("BasTer");
		pchar.quest.Sharlie_TrialOver.over = "yes"; // снять таймер
		dialog.text = "¿Qué? ¿Realmente dijo que te ayudaría?";
		link.l1 = "Pues, más o menos. ¿Le echarás una mano al hermano de tu viejo amigo? No es que te esté pidiendo limosna como un mendigo. Te estoy pidiendo que me des una oportunidad para ganar algo de dinero.";
		link.l1.go = "trial_1";
		break;

	case "trial_late":
		dialog.text = "¡Oh, Charles! Llegas tarde. Si hubieras venido antes, habría encontrado lo adecuado para ti, pero ahora, prosti. No te preocupes, pasea por las ciudades, charla con la gente. Hay mucho trabajo que hacer en el Caribe.";
		link.l1 = "Entiendo, eso es lamentable. ¡Adiós!";
		link.l1.go = "trial_late_1";
		break;

	case "trial_late_1":
		DialogExit();
		DeleteAttribute(pchar, "questTemp.Trial");
		break;

	case "trial_1":
		dialog.text = "Mmm. Nyet, por supuesto que no te rechazaré. Si quieres alimentar a un hombre, no le des un pez, sino una caña de pescar. ¿No es cierto, monsieur de Maure? Así que necesitas un trabajo... Bastante sencillo. Hablaré con un hombre que conozco y te recomendaré a él. Y todo lo demás dependerá de lo bien que hagas el trabajo.";
		link.l1 = "Maravilloso. ¿Con quién debo hablar?";
		link.l1.go = "trial_2";
		break;

	case "trial_2":
		dialog.text = "Ve a la tienda mañana. Un hombre llamado Gerard LeCroix te estará esperando allí. Te dará algo de trabajo. Estará en esta colonia solo hasta mañana por la noche. Ve a verlo pronto y haz el trabajo correctamente. No me pongas en una posición incómoda.";
		link.l1 = "Trato hecho. ¡Gracias, Fadey!";
		link.l1.go = "trial_3";
		break;

	case "trial_3":
		DialogExit();
		SetFunctionTimerCondition("Trial_StartLine", 0, 0, 1, false); // таймер
		pchar.questTemp.Trial = "start";
		AddQuestRecord("Trial", "1");
		break;
	// belamour legendary edition пиратская линейка -->
	case "Slaves":
		DelMapQuestMarkCity("baster");
		DelLandQuestMark(npchar);
		dialog.text = "Ah, ¿cómo puedo ayudarte, mi amigo?";
		link.l1 = "Fadey, escucha, realmente necesito comprar cincuenta esclavos de los contrabandistas. El problema es que soy un desconocido para ellos, y necesito que me hagas una presentación. Sin ti, ni siquiera me escucharán, y esto es una cuestión de vida o muerte para una persona muy importante.";
		link.l1.go = "Slaves_1";
		break;

	case "Slaves_1":
		dialog.text = "¡Oh, ho! ¡Veo que expandes tu negocio! ¡Qué rentable! Te ayudaré, querido amigo. Pero como sabes, no trabajo gratis. Costará 150 doblones de oro convencer al vendedor de tus buenas intenciones para comprar los negros y, por supuesto, un poco extra por mis diligentes esfuerzos...";
		if (PCharDublonsTotal() >= 150)
		{
			link.l1 = "¡No esperaba menos, monsieur Fadey! Aquí está tu oro.";
			link.l1.go = "Slaves_2";
		}
		else
		{
			link.l1 = "¡Voy al usurero inmediatamente! ¡Espera, monsieur Fadey, ya regreso!";
			link.l1.go = "exit";
			pchar.questTemp.Mtraxx.GiveMeSlaves = "FindGold";
		}

		link.l2 = "Fadey, parece que se me ha ocurrido algo y ya no necesito a los negros. Lo siento. ¡Nos vemos!";
		link.l2.go = "Slaves_3";
		break;

	case "Slaves_2":
		RemoveDublonsFromPCharTotal(150);
		pchar.questTemp.Mtraxx.GiveMeSlaves = "kapster";
		locations[FindLocation("Shore29")].DisableEncounters = true; // энкаутеры закрыть
		pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l1 = "Hour";
		pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l1.start.hour = 22.00;
		pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l1.finish.hour = 23.00;
		pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2 = "Timer";
		pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2.date.day = GetAddingDataDay(0, 0, 1);
		pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2.date.month = GetAddingDataMonth(0, 0, 1);
		pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2.date.year = GetAddingDataYear(0, 0, 1);
		pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l3 = "location";
		pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l3.location = "Shore29";
		pchar.quest.Mtraxx_GiveMeSlavesKapster.function = "MtraxxGiveMeSlavesKapsterInShore"; // прибыли
		pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1 = "Timer";
		pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.hour = 23.0; // не пришли, значит гудбай
		pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
		pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
		pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
		pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.function = "MtraxxGiveMeSlavesKapsterInShoreLate"; // опоздание
		AddQuestRecord("Roger_3", "23");
		dialog.text = "Excelente, amigo. Pero si deseas engañarme con la necesidad de tu compra y es con propósitos inútiles, me harás enfadar mucho. No quieres eso. Mañana a las diez en punto al atardecer en la Playa de Capster, te arreglaré una reunión, no me falles.";
		link.l1 = "No tienes nada de qué preocuparte, regresaré por la mercancía.";
		link.l1.go = "exit";
		break;

	case "Slaves_3":
		DialogExit();
		AddQuestRecord("Roger_3", "22");
		pchar.questTemp.Mtraxx.GiveMeSlaves = "WithoutSlaves";
		break;

	case "pistols":
		DelMapQuestMarkCity("baster");
		DelLandQuestMark(npchar);
		dialog.text = "¡Hola, hola! Dime, buen amigo, ¿qué te trae a mi modesta casa?";
		link.l1 = "Necesito armas. Los comerciantes locales no pueden encontrar la cantidad que necesito, pero creo que tú puedes ayudarme.";
		link.l1.go = "pistols_1";
		break;

	case "pistols_1":
		dialog.text = "Primero que nada, dime, querido amigo, qué es exactamente lo que necesitas. Luego te diré exactamente si puedo ayudarte.";
		link.l1 = "Necesito 30 pistolas de soldado, dos mosquetes de mecha, 70 cartuchos para ellos y 90 pociones curativas.";
		link.l1.go = "pistols_2";
		break;

	case "pistols_2":
		if (CheckAttribute(pchar, "questTemp.Mtraxx.GiveMeSlaves"))
		{
			if (pchar.questTemp.Mtraxx.GiveMeSlaves == "Deal" || pchar.questTemp.Mtraxx.GiveMeSlaves == "WithoutSlaves")
			{
				dialog.text = pchar.name + ", me estás asustando. Primero cincuenta negros, luego armas. ¿Estás tratando de iniciar una revuelta de esclavos, amigo mío?";
				link.l1 = "Muy perspicaz, Fadey. Como dije antes, todo esto es necesario para la salvación de una persona importante. No te preocupes, será rescatado de las garras de los españoles, así que tu reputación aquí no sufrirá.";
				link.l1.go = "pistols_3";
				break;
			}
		}
		dialog.text = "Eso es bueno de escuchar. Puedo ayudar.";
		link.l1 = "Me alegra oírlo. ¿Cuánto?";
		link.l1.go = "pistols_4";
		break;

	case "pistols_3":
		dialog.text = "Me alegra que te hayas explicado. Y si esto realmente tiene que ver con los españoles, entonces te ayudaré. Pero si resulta que me has engañado, me enfadaré mucho.";
		link.l1 = "Ten algo de fe en mí, Fadey. ¿Cuánto?";
		link.l1.go = "pistols_4";
		break;

	case "pistols_4":
		dialog.text = "Horosho, entonces ... pistolas y un par de mosquetes, con pólvora y bala para cada uno... Por lo tanto, no puedo prometer que conseguiré absolutamente todo lo que pediste, pero haré todo lo que esté en mi poder. Mientras tanto, necesito un depósito de 40,000 pesos, o 300 doblones si prefieres.";
		if (PCharDublonsTotal() >= 300)
		{
			link.l1 = "Toma doblones, Fadey. Resulta que llevo algunos conmigo ahora mismo.";
			link.l1.go = "pistols_4D";
		}
		if (sti(Pchar.money) >= 40000)
		{
			link.l2 = "Todos mis doblones se han agotado, toma pesos, Fadey.";
			link.l2.go = "pistols_4P";
		}
		if (PCharDublonsTotal() < 300 || sti(Pchar.money) < 40000) // возможность найти без отказа
		{
			link.l3 = "Necesito hablar con mi banquero. ¡Regreso enseguida!";
			link.l3.go = "exit";
			pchar.questTemp.Mtraxx.MagicBox = "FindMoney";
		}
		link.l4 = "Disculpa, Fadey, pero no puedo permitírmelo. Intentaré arreglármelas solo. ¡Nos vemos!";
		link.l4.go = "pistols_x";
		break;

	case "pistols_4D":
		SetFunctionTimerCondition("Mtraxx_MagicBoxready", 0, 0, 1, false);
		RemoveDublonsFromPCharTotal(300);
		pchar.questTemp.Mtraxx.MagicBox = "Tomorow";
		dialog.text = "Ven mañana, " + pchar.name + ", y tendré el material que necesitas.";
		link.l1 = "Entonces no me interpondré. ¡Nos vemos mañana!";
		link.l1.go = "exit";
		break;

	case "pistols_4P":
		AddMoneyToCharacter(pchar, -40000);
		SetFunctionTimerCondition("Mtraxx_MagicBoxready", 0, 0, 1, false);
		pchar.questTemp.Mtraxx.MagicBox = "Tomorow";
		dialog.text = "Ven mañana, " + pchar.name + ", y tendré el material que necesitas.";
		link.l1 = "Entonces no me interpondré. ¡Nos vemos mañana!";
		link.l1.go = "exit";
		break;

	case "pistols_X":
		DialogExit();
		DeleteAttribute(pchar, "questTemp.Mtraxx.MagicBox");
		if (CheckAttribute(pchar, "questTemp.Mtraxx.GiveMeSlaves"))
			DeleteAttribute(pchar, "questTemp.Mtraxx.GiveMeSlaves");
		break;

	case "pistols_5":
		dialog.text = "Bueno, muchacho, tuve suerte de encontrar todo lo que pediste bajo tales restricciones de tiempo. ¡Deberías estar agradecido! Ahora, el pago final. Dame exactamente tanto como se dio como depósito, y toma tus armas.";
		if (PCharDublonsTotal() >= 300)
		{
			link.l1 = "Toma 300 doblones. Haré que mis hombres lleven las armas a mi barco. ¿Qué haría sin ti, Fadey? ¡No tienes idea de cuánto me has ayudado!";
			link.l1.go = "pistols_5D";
		}
		if (sti(Pchar.money) >= 40000)
		{
			link.l2 = "Toma 40 000 pesos. Haré que mis hombres lleven las armas a mi barco. ¿Qué haría yo sin ti, Fadey? ¡No tienes idea de cuánto me has ayudado!";
			link.l2.go = "pistols_5P";
		}
		if (PCharDublonsTotal() < 300 || sti(Pchar.money) < 40000) // возможность найти без отказа
		{
			link.l3 = "Pues maldición, ¿cómo pude olvidar el dinero? Volveré pronto.";
			link.l3.go = "exit";
			pchar.questTemp.Mtraxx.MagicBox = "FindMoney";
		}
		link.l4 = "Disculpa, Fadey, estoy arruinado. Quédate con el depósito, espero que sea suficiente para compensar tus gastos con este trato, y trataré de arreglármelas solo. ¡Nos vemos!";
		link.l4.go = "pistols_x";
		break;

	case "pistols_5D":
		Log_Info("¡Las armas de Fadey están en el barco!");
		RemoveDublonsFromPCharTotal(300);
		pchar.questTemp.Mtraxx.MagicBox = "Full";
		if (CheckAttribute(pchar, "questTemp.Mtraxx.GiveMeSlaves"))
			DeleteAttribute(pchar, "questTemp.Mtraxx.GiveMeSlaves");
		dialog.text = "Ayudar a los necesitados es un honor. Ayudar a los que pagan es un placer. La próxima vez que estés en Basse-Terre, asegúrate de visitarme para saludarme.";
		link.l1 = "Eso es absurdo, ¡estar en Basse-Terre y no ver a mi amigo Fadey! ¡Hasta la próxima!";
		link.l1.go = "exit";
		break;

	case "pistols_5P":
		Log_Info("¡Las armas de Fadey están en el barco!");
		AddMoneyToCharacter(pchar, -40000);
		pchar.questTemp.Mtraxx.MagicBox = "Full";
		if (CheckAttribute(pchar, "questTemp.Mtraxx.GiveMeSlaves"))
			DeleteAttribute(pchar, "questTemp.Mtraxx.GiveMeSlaves");
		dialog.text = "Ayudar a los necesitados es un honor. Ayudar a los que pagan es un placer. La próxima vez que estés en Basse-Terre, asegúrate de visitarme para saludarme.";
		link.l1 = "Eso es absurdo, ¡estar en Basse-Terre y no ver a mi amigo Fadey! ¡Hasta la próxima!";
		link.l1.go = "exit";
		break;
		// <-- legendary edition

	case "guardoftruth":
		dialog.text = "¡Vaya, quién dudaría que vendrías por negocios, amigo mío! Lamentablemente, no tengo vodka para ofrecerte en este momento, me lo bebí todo. Dime en qué tipo de problema te has metido ahora.";
		link.l1 = "Un corsario ofreció a la parroquia una cruz pectoral de oro con lazurita para el perdón de sus pecados. Es un objeto único y valioso. El problema es que esta cruz fue robada de otra parroquia. No solo eso, sino que un sacerdote fue asesinado durante el robo.";
		link.l1.go = "guardoftruth_1";
		break;

	case "guardoftruth_1":
		dialog.text = "¡Oh, inmaculada Theotokos! ¡No me digas!";
		link.l1 = "Pues así son las cosas. Estoy representando a los feligreses robados e intentando devolver la cruz a sus dueños originales.";
		link.l1.go = "guardoftruth_2";
		break;

	case "guardoftruth_2":
		dialog.text = "Una acción noble y muy piadosa. ¿Intentando ganarte puntos con el Todopoderoso?";
		link.l1 = "El problema es que el padre se niega a devolvérmelo, a pesar de todo lo que le he dicho. No lo entiendo. ¿Cómo se puede colocar tranquilamente una cruz robada con la sangre de un hombre inocente en la Casa de Dios? ¡Eso es blasfemia!";
		link.l1.go = "guardoftruth_3";
		break;

	case "guardoftruth_3":
		dialog.text = "Bueno, ahora, técnicamente cada cáliz consagrado lleva la sangre del Cristo Inocente... pero divago. ¿Supongo que quieres que te ayude?";
		link.l1 = "¡Así es! Tienes bastante influencia en Basse-Terre. Eres muy respetado, así que quizás el sacerdote escuche tus amonestaciones.";
		link.l1.go = "guardoftruth_4";
		break;

	case "guardoftruth_4":
		dialog.text = "" + pchar.name + ", ¿le has contado la historia exacta de esta cruz robada a nuestro sacerdote?";
		link.l1 = "¡Por supuesto! He apelado a sus sentimientos religiosos, a la solidaridad cristiana, a su maldita conciencia por el amor de Dios, pero cerró los oídos.";
		link.l1.go = "guardoftruth_5";
		break;

	case "guardoftruth_5":
		dialog.text = "Mm... ¿Has intentado usar otros métodos para convencerle?";
		link.l1 = "¿Te refieres a sobornarlo? No voy a sobornar a un sacerdote. Si fuera un banquero, o un comerciante, o incluso un gobernador, intentaría resolver el asunto de esa manera, ¡pero no a un sacerdote!";
		link.l1.go = "guardoftruth_6";
		break;

	case "guardoftruth_6":
		dialog.text = "Mi querido amigo ingenuo, si los oídos del sacerdote realmente están cerrados a las proclamaciones de conciencia, entonces seguramente sus manos estarán abiertas al oro... O al revés. Te ayudaré, creo que mantener un tesoro tan mancillado aquí seguramente causará problemas mayores más adelante. Sin embargo, requerirá ciertos gastos." 
                link.l1 = "¿Por qué no me sorprende? ¿Cuánto esta vez?";
		link.l1.go = "guardoftruth_7";
		break;

	case "guardoftruth_7":
		dialog.text = "Ven mañana, " + pchar.name + ", aún no puedo mencionar el precio. Pero tendrás esa cruz robada, tenlo por seguro.";
		link.l1 = "Muy bien, Fadey, entonces no te molestaré más. ¡Nos vemos mañana!";
		link.l1.go = "guardoftruth_8";
		break;

	case "guardoftruth_8":
		DialogExit();
		pchar.questTemp.Guardoftruth.Baster_church = "wait";
		SetFunctionTimerCondition("GuardOT_FadeyTimer", 0, 0, 1, false);
		AddQuestRecord("Guardoftruth", "29");
		break;

	case "guardoftruth_9":
		dialog.text = "Tal como prometí, tengo la cruz. En cuanto a los detalles... oh, olvídalos... todas las tonterías son perdonadas por la sangre derramada de nuestro 'Precioso Salvador'.";
		link.l1 = "¿Cuánto te debo?";
		link.l1.go = "guardoftruth_10";
		break;

	case "guardoftruth_10":
		dialog.text = "Doscientos cincuenta doblones. Como cobertura de mis gastos, y por supuesto agradecería un poco extra por mi justa ayuda...";
		if (PCharDublonsTotal() >= 250) // belamour legendary edition
		{
			link.l1 = "Sí, sí, monsieur Fadey. Aquí está tu oro.";
			link.l1.go = "guardoftruth_11";
		}
		else
		{
			link.l1 = "Debo recoger el oro de mi camarote. Ahora vuelvo.";
			link.l1.go = "exit";
			npchar.quest.utensil = "true";
		}
		break;

	case "guardoftruth_11":
		DeleteAttribute(npchar, "quest.utensil");
		dialog.text = "Horosho. Aquí está la cruz robada.";
		link.l1 = "Gracias, Fadey. ¡Ni siquiera puedes imaginar cuánto has hecho por mí!";
		link.l1.go = "guardoftruth_12";
		break;

	case "guardoftruth_12":
		RemoveDublonsFromPCharTotal(250); // belamour legendary edition
		GiveItem2Character(pchar, "jewelry34");
		// Log_Info("¡Has recibido una cruz dorada con lazurita!");
		PlaySound("interface\important_item.wav");
		dialog.text = "Siempre me alegra ayudar a un amigo amable y, lo que es más importante, generoso. Pásate más a menudo. Quizás tenga un poco de vodka cuando me lo traigan de la madre patria.";
		link.l1 = "¡Con gusto!";
		link.l1.go = "guardoftruth_13";
		break;

	case "guardoftruth_13":
		DialogExit();
		DeleteAttribute(pchar, "questTemp.Guardoftruth.Baster_church");
		AddQuestRecord("Guardoftruth", "30");
		break;

	case "guardoftruth_14":
		dialog.text = "Vaya vaya, ¡el mar aún no te ha reclamado! Cuéntame. ¿Qué desgracias te han traído a mi puerta esta vez?";
		link.l1 = "No sé si llamarlas desgracias o no, pero de todos modos estoy aquí. Fadey, el primer día que nos conocimos me diste una daga rara, la Garra del Jefe. Ahora sé que antes pertenecía a un hombre llamado Archibald Calhoun. Por favor, dime lo que sabes sobre este hombre.";
		link.l1.go = "guardoftruth_15";
		break;

	case "guardoftruth_15":
		dialog.text = "Nada se te puede ocultar, " + pchar.name + ". Ves a través de todo, al igual que tu hermano. Sí, gané este puñal en un juego de dados con Calhoun. ¿Quién es él? Yo mismo no tengo ni idea. Nos encontramos por casualidad en la taberna, comenzamos a charlar, bebimos un poco, y él empezó a contarme sobre algunos pecados de su pasado que lo agobiaban...";
		link.l1 = "¿Qué eres tú? ¿Su confesor? ¿Qué pecados?";
		link.l1.go = "guardoftruth_16";
		break;

	case "guardoftruth_16":
		dialog.text = "Archibald estaba consumido por el recuerdo de un hombre que fue torturado hasta la muerte por la Inquisición por su culpa, y por otras almas inocentes que mató. No dejaba de llamarse a sí mismo Judas. Decía que Dios lo estaba castigando por sus pecados y que la Inquisición lo estaba cazando.\nMencionó que el propio inquisidor español Vincento lo quería muerto, y envió mercenarios a perseguirlo por todo el Caribe. Luego, el alcohol venció su mejor juicio y apostamos por este viejo puñal.";
		link.l1 = "¿Eso es todo? ¿Nunca lo volviste a ver?";
		link.l1.go = "guardoftruth_17";
		break;

	case "guardoftruth_17":
		dialog.text = "Por supuesto que no, ahora está muerto. Una banda de malditos piratas envió su filibote al Reino de Davy Jones, y a toda la tripulación a Mictlantecuhtli. La verdad sea dicha, los rumores decían que fueron atacados por profesionales disfrazados de piratas... agentes de la Inquisición. El Padre Vincento siempre atrapa a su presa, dicen.";
		link.l1 = "Archibald Calhoun está vivo. Lo vi no hace mucho junto con un tal William Paterson. Sirve como su primer oficial.";
		link.l1.go = "guardoftruth_18";
		break;

	case "guardoftruth_18":
		dialog.text = "¡Oh-ho, qué sorpresa! Archibald al menos puede tomar un respiro bajo el ala del Capitán Paterson. Está en buena compañía. Los españoles temen a Patterson como a la peste. No se atreverán a conspirar contra Archibald mientras esté bajo la protección de Patterson.";
		link.l1 = "¿Conoces a Patterson?";
		link.l1.go = "guardoftruth_19";
		break;

	case "guardoftruth_19":
		dialog.text = "¿Quién no conoce a William Patterson!? Es un recién llegado al Caribe, al igual que tú. Y al igual que tú, ya ha forjado una reputación imponente. El Sr. Patterson es el amigo más cercano del Coronel Fox, y está bien relacionado con el propio Lord Windsor, el Gobernador General de todas las colonias inglesas en el Caribe. A menudo visita el palacio del gobernador en Port Royal, en Jamaica.";
		link.l1 = "Entendido. ¡Gracias por la información, Fadey!";
		link.l1.go = "guardoftruth_20";
		break;

	case "guardoftruth_20":
		dialog.text = "¡Oh, no lo menciones, amigo. ¡Ven a visitarme alguna vez! ¡Buena caza!";
		link.l1 = "¡Definitivamente!";
		link.l1.go = "guardoftruth_21";
		break;

	case "guardoftruth_21":
		DialogExit();
		pchar.questTemp.Guardoftruth.Archy = "portroyal";
		AddQuestRecord("Guardoftruth", "62");
		// эскадру Патерсона - в Порт-Рояль
		Group_SetAddress("Willy_group", "Jamaica", "quest_ships", "quest_ship_1");
		pchar.quest.GuardOT_jamaica.win_condition.l1 = "location";
		pchar.quest.GuardOT_jamaica.win_condition.l1.location = "Jamaica";
		pchar.quest.GuardOT_jamaica.function = "GuardOT_PortRoyalArrive";
		break;

	// персидские клинки
	case "persian":
		dialog.text = "Echemos un vistazo, " + pchar.name + "¡... Da! ¡Es uno de ellas! ¡Ese es mi chico, me has alegrado el día! ¿Dónde la encontraste?";
		link.l1 = "No importa. Lo importante es que ha encontrado su camino de regreso a ti.";
		link.l1.go = "persian_1";
		break;

	case "persian_1":
		dialog.text = "Pagaré bien por tu exhaustiva investigación. Trescientos doblones de oro deberían ser una recompensa suficiente por tus molestias...";
		link.l1 = "¿Me estás pagando con algunos de los doblones que me exprimiste antes? Aunque, por supuesto, no los rechazaré. Aquí está tu cimitarra.";
		link.l1.go = "persian_2";
		break;

	case "persian_2":
		sTemp = CheckNIdentifyPersian();
		RemoveItems(pchar, sTemp, 1);
		PlaySound("interface\important_item.wav");
		pchar.questTemp.Persian = "one";
		dialog.text = "¡Spasiba, mi amigo! Gracias por la espada y por tus palabras sardónicas. Eres sabio más allá de tus años, " + pchar.name + ", pero los lazos humanos de amistad superan el valor del oro. Hablando de oro, te pagaré por completo. Aquí, toma tus doblones.";
		link.l1 = "Gracias.";
		link.l1.go = "persian_3";
		break;

	case "persian_3":
		TakeNItems(pchar, "gold_dublon", 300);
		// Log_Info("¡Has recibido 300 doblones!");
		PlaySound("interface\important_item.wav");
		AddCharacterExpToSkill(pchar, "Leadership", 400);
		AddCharacterExpToSkill(pchar, "Fortune", 200);
		ChangeCharacterComplexReputation(pchar, "authority", 2);
		ChangeCharacterComplexReputation(pchar, "nobility", 2);
		ChangeCharacterNationReputation(pchar, FRANCE, 2);
		dialog.text = "Y hablando de los lazos de amistad, los tuyos y los míos en particular, " + pchar.name + ". Tengo algo que te interesará bastante.";
		link.l1 = "Déjame adivinar, ¿más vodka?";
		link.l1.go = "persian_4";
		break;

	case "persian_4":
		dialog.text = "¡Ja! El vodka es bueno, pero no es lo único por lo que mi país es conocido. Hay un material especial que solo Rusia produce. Consigo que este material me lo entreguen mis contactos en casa para comerciar aquí. Todo capitán lo quiere, porque mejora cualquier barco. Estoy hablando de cuerdas de cáñamo. Cuerdas inmunes a la humedad y a la sal marina por igual. Dicen que es el mejor material para el aparejo. Cada mes, recibo una cierta cantidad enviada desde Reval. Normalmente, mi almacén tiene unos cientos de bobinas alrededor de la mitad de cada mes. Así que, " + pchar.name + ", te ofrezco venderte un lote de cincuenta bobinas. Diez doblones la bobina.\nSólo tengo dos condiciones: en primer lugar, te guardaré las cuerdas hasta el día 20 de cada mes; en segundo lugar, puedes comprar sólo el lote completo. Cincuenta bobinas por quinientos doblones. Confidencialmente hablando, " + pchar.name + ", dicen que hay ciertos sitios donde se pueden revender esas cuerdas por un precio mucho mayor, ¡pero yo qué sé!\nEstoy completamente satisfecho con el estado actual de mi operación y no necesito buscar revendedores por mi cuenta. Si encuentras un buen comerciante, puedes obtener buenos beneficios.";
		link.l1 = "Entendido. ¡Es una oferta estupenda, Fadey! Creo que aprovecharé la oportunidad que me has presentado. Entonces, ¿cada vigésimo día del mes, quinientos doblones por cincuenta piezas?";
		link.l1.go = "persian_5";
		break;

	case "persian_5":
		AddQuestRecordInfo("Unique_Goods", "2");
		dialog.text = "Da. Ve a recoger tu compra. ¡Pero espera, espera, querido amigo! Además de este shamshir, que me devolviste por pura benevolencia, había otras dos espadas. Te ruego, por favor, si los encuentras, tráemelos de vuelta y te pagaré más que un precio justo por su devolución.";
		link.l1 = "Definitivamente, Fadey. Si los encuentro, los traeré de vuelta.";
		link.l1.go = "exit";
		if (CheckNCountPersian() > 0)
		{
			link.l2 = "Buenas noticias para ti. Tengo otro shamshir persa.";
			link.l2.go = "persian_6";
		}
		npchar.quest.ropes = "true";
		break;

	case "persian_6":
		dialog.text = "¡Oh, mi buen amigo! ¡Acabas de enjugar mis lágrimas! Déjame echar un vistazo... ¡Da! ¡Este es, mi precioso shamshir! Aquí tienes, tal como te prometí, trescientos doblones de recompensa por él.";
		link.l1 = "¡Spasibo!";
		link.l1.go = "persian_7";
		break;

	case "persian_7":
		TakeNItems(pchar, "gold_dublon", 300);
		// Log_Info("¡Has recibido 300 doblones!");
		sTemp = CheckNIdentifyPersian();
		RemoveItems(pchar, sTemp, 1);
		PlaySound("interface\important_item.wav");
		pchar.questTemp.Persian = "two";
		AddCharacterExpToSkill(pchar, "Leadership", 400);
		AddCharacterExpToSkill(pchar, "Fortune", 200);
		ChangeCharacterComplexReputation(pchar, "authority", 2);
		ChangeCharacterComplexReputation(pchar, "nobility", 2);
		ChangeCharacterNationReputation(pchar, FRANCE, 2);
		dialog.text = "Por favor, acepta mi gratitud y un modesto, pero muy útil regalo. No lo necesito, pero tú o tu carpintero de barco lo encontrarán bastante útil. \n¡Mira, observa este fino anillo! Ahora es tuyo. Pero no es un anillo cualquiera, es un anillo encantado. Ayuda en la carpintería y en la reparación de barcos. Muchos artesanos desearían tenerlo, pero lo he estado guardando para una ocasión especial. Tómalo, amigo mío, ¡deseo que alivie tu carga!";
		link.l1 = "Sin duda llevas muchos artefactos interesantes. ¡Gracias, Fadey!";
		link.l1.go = "persian_8";
		break;

	case "persian_8":
		GiveItem2Character(pchar, "talisman7");
		// Log_Info("¡Has recibido el amuleto del escarabajo!");
		PlaySound("interface\important_item.wav");
		dialog.text = "Solo queda un shamshir de mi colección perdida por encontrar. Estoy contando contigo, " + pchar.name + ", y en tu suerte. Si lo encuentras, no dudes en regresar rápidamente a mí.";
		link.l1 = "¡Definitivamente! Hasta pronto...";
		link.l1.go = "exit";
		if (CheckNCountPersian() > 0)
		{
			link.l2 = "¿Por qué debería apresurarme? La espada está conmigo.";
			link.l2.go = "persian_9";
		}
		break;

	case "persian_9":
		dialog.text = "¡Oh, gracias a Dios que pedí ayuda precisamente a ti!" + pchar.name + "¡Eres un hombre milagroso, amigo mío! Muéstrame... ¡Ohooo! Es, es ella. ¡Mi querida! ¡Krasavitsa! ¡Gramercy, buen hombre, me inclino ante ti! Aquí, aquí está tu dinero. ¡Cuatrocientos doblones y ni un kopek menos! No seré tacaño.";
		link.l1 = "Gracias, Fadey. Un placer ayudar.";
		link.l1.go = "persian_10";
		break;

	case "persian_10":
		TakeNItems(pchar, "gold_dublon", 400);
		// Log_Info("¡Has recibido 400 doblones!");
		sTemp = CheckNIdentifyPersian();
		RemoveItems(pchar, sTemp, 1);
		PlaySound("interface\important_item.wav");
		AddCharacterExpToSkill(pchar, "Leadership", 500);
		AddCharacterExpToSkill(pchar, "Fortune", 250);
		ChangeCharacterComplexReputation(pchar, "authority", 2);
		ChangeCharacterComplexReputation(pchar, "nobility", 2);
		ChangeCharacterNationReputation(pchar, FRANCE, 3);
		Achievment_Set("ach_65");
		dialog.text = "¡Mi colección de shamshirs está de nuevo completa! ¡Nadie se atreverá a robarme otra vez, me aseguraré de eso! Tengo una recompensa muy especial para ti, buen hombre. En dos semanas, un comerciante me traerá un juego de excelente armadura de esgrima desde Europa. Por encargo de un noble, es una pieza bastante única de armadura. Así que, si quieres, puedes comprarla por solo setecientos doblones de oro. Le diré al noble que se perdió en tránsito.";
		link.l1 = "¿Qué tiene de bueno esta armadura?";
		link.l1.go = "persian_11";
		break;

	case "persian_11":
		dialog.text = "Es muy cómoda y duradera, pero aún así funciona tan bien como el coracero de hierro. ¡Y además se ve estupenda! Deberías volver en un par de semanas y echarle un vistazo. Pero no tardes más de un mes, o se lo venderé al cliente original.";
		link.l1 = "Trato hecho. Pasaré por tu casa en dos semanas.";
		link.l1.go = "persian_12";
		break;

	case "persian_12":
		DialogExit();
		pchar.questTemp.Persian = "time";
		SetFunctionTimerCondition("Persian_CirassLamport", 0, 0, 14, false); // таймер
		break;

	case "persian_13":
		dialog.text = "Sí, ya ha sido entregado y te está esperando. ¿Trajiste el dinero?";
		if (PCharDublonsTotal() >= 700) // belamour legendary edition
		{
			link.l1 = "Sí. Aquí tienes setecientos doblones.";
			link.l1.go = "persian_14";
		}
		else
		{
			link.l1 = "Maldición. Olvidé el dinero en el barco. Lo traeré en un segundo.";
			link.l1.go = "exit";
		}
		break;

	case "persian_14":
		RemoveDublonsFromPCharTotal(700); // belamour legendary edition
		PlaySound("interface\important_item.wav");
		GiveItem2Character(pchar, "cirass8");
		// Log_Info("¡Has recibido una armadura de mimbre!");
		AddCharacterExpToSkill(pchar, "Sneak", 300);
		dialog.text = "¡Sí, buen hombre! Aquí, ten. Esta armadura de mimbre te servirá bien, te lo aseguro. ¡No hay nada igual en todo el Caribe!";
		link.l1 = "Sí, puedo ver eso. ¡Gracias! No puedo esperar para probármela...";
		link.l1.go = "persian_15";
		break;

	case "persian_15":
		dialog.text = "¿Por qué necesitas esperar? Adelante. Veamos cómo encaja.";
		link.l1 = "Lo haré. ¡Hasta luego, monsieur Fadey!";
		link.l1.go = "persian_16";
		break;

	case "persian_16":
		DialogExit();
		pchar.questTemp.Persian = "end";
		pchar.quest.Persian_CirassLamportOver.over = "yes"; // снять прерывание
		break;

	// торговля канатами
	case "ropes":
		if (CheckAttribute(pchar, "questTemp.UpgradeRopes"))
		{
			dialog.text = "Entra, mi querido amigo. La mercancía está lista para que la compres. 2 125 doblones por doscientas cincuenta piezas.";
			if (PCharDublonsTotal() >= 2125)
			{
				link.l1 = "Todo está como acordamos. Toma el dinero.";
				link.l1.go = "ropes_1";
			}
			else
			{
				link.l1 = "Déjame traer las monedas de mi camarote.";
				link.l1.go = "exit";
			}
		}
		else
		{
			dialog.text = "Entra, mi querido amigo. La mercancía está lista para que la compres. Quinientos doblones por cincuenta piezas.";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Todo está como acordamos. Toma el dinero.";
				link.l1.go = "ropes_1";
			}
			else
			{
				link.l1 = "Déjame traer las monedas de mi camarote.";
				link.l1.go = "exit";
			}
		}
		if (sti(pchar.questTemp.FadeyRopes) >= 1 && !CheckAttribute(pchar, "questTemp.FadeyRopesBlock")) // увеличить объём поставок канатами
		{
			link.l4 = "Fadey, ¿podríamos aumentar el volumen de nuestros tratos? ¡Estoy listo para comprar cinco veces más mercancías de ti! Creo que esto nos beneficiaría a ambos. ¿Qué dices?";
			link.l4.go = "UpgradeRopes";
		}
		if (sti(pchar.questTemp.FadeyRopes) >= 1 && CheckAttribute(pchar, "questTemp.FadeyRopesPotom") && PCharDublonsTotal() >= 3000) // увеличить объём поставок канатами, если в первый раз не принесли
		{
			link.l4 = "¡Fadey, he traído el dinero! Tres mil doblones de oro, como acordamos.";
			link.l4.go = "UpgradeRopes_Agreed";
		}
		break;

	case "ropes_1":
		if (CheckAttribute(pchar, "questTemp.UpgradeRopes"))
			RemoveDublonsFromPCharTotal(2125);
		else
			RemoveDublonsFromPCharTotal(500); // belamour legendary edition
		PlaySound("interface\important_item.wav");
		dialog.text = "Un placer hacer negocios contigo, " + pchar.name + ". Ordenaré a mis hombres que lleven las cuerdas a tu barco.";
		link.l1 = "¡Gracias!";
		link.l1.go = "ropes_2";
		break;

	case "ropes_2":
		dialog.text = "Si aún necesitas más cuerdas, vuelve en un mes.";
		link.l1 = "¡Muy bien, Fadey! ¡Hasta luego!";
		link.l1.go = "exit";
		if (CheckAttribute(pchar, "questTemp.UpgradeRopes"))
			AddCharacterGoods(pchar, GOOD_ROPES, 250);
		else
			AddCharacterGoods(pchar, GOOD_ROPES, 50);
		DeleteAttribute(npchar, "quest.ropes");
		SetFunctionTimerCondition("Ropes_FadeyAttrReturn", 0, 0, 1, false); // таймер
		AddCharacterExpToSkill(pchar, "Commerce", 200);
		pchar.questTemp.FadeyRopes = sti(pchar.questTemp.FadeyRopes) + 1; // счётчик покупок
		break;

	// уменьшение НЗГ
	case "help":
		if (!CheckAttribute(npchar, "quest.relation_info"))
		{
			dialog.text = "¿Qué puedo hacer por ti, mi querido amigo?";
			link.l1 = "Eres un hombre influyente, Fadey. Amigo del gobernador y, según dicen los rumores, tienes conexiones en la corte. ¿Podrías interceder ante las autoridades en caso de que tenga problemas con la ley?";
			link.l1.go = "relation_info";
			break;
		}
		dialog.text = "¿Cómo puedo ayudarte, mi amigo?";
		if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
		{
			link.l1 = "Tengo un problema con las autoridades inglesas.";
			link.l1.go = "relation";
			pchar.GenQuest.FadeyNation = ENGLAND;
		}
		if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
		{
			link.l2 = "Me he topado con problemas con las autoridades francesas.";
			link.l2.go = "relation";
			pchar.GenQuest.FadeyNation = FRANCE;
		}
		if (ChangeContrabandRelation(pchar, 0) <= 5)
		{
			Link.l5 = "Tengo un enorme problema con los contrabandistas.";
			Link.l5.go = "contraband";
		}
		link.l9 = "Lo siento, creo que puedo manejarlo yo mismo.";
		link.l9.go = "exit";
		break;

	case "relation_info":
		dialog.text = "¡Oh-ho-ho! Buen hombre, ¿quién te dijo eso? Todos mienten. Pero como eres hermano de Michel y un buen amigo mío, puedo intentar arreglar las cosas para ti. Solo puedo interceder ante las autoridades inglesas y francesas, aunque mis conexiones tienen límites. No hago negocios con los españoles ni con los holandeses. También te advierto que mi influencia solo es suficiente para salvarte de infracciones menores. Puedo persuadirles de reconsiderar su actitud hacia ti en caso de leves faltas, o para calmar alguna ira leve. ¡Así que no te pongas a empezar una guerra y esperes que te saque las castañas del fuego! Además de eso, solo puedo apaciguar a una nación a la vez: Francia o Inglaterra. No puedo partirme por la mitad para hacer dos trabajos a la vez. Por supuesto, también se requerirá dinero para hacer sobornos. No dudes en acudir a mí por ayuda si encuentras aceptables mis términos.";
		link.l1 = "Gracias, Fadey. Lo tendré en cuenta.";
		link.l1.go = "exit";
		npchar.quest.relation_info = "true";
		break;

	case "relation":
		rate = abs(ChangeCharacterNationReputation(pchar, sti(pchar.GenQuest.FadeyNation), 0));
		if (rate <= 10)
		{
			dialog.text = "Por supuesto. Seguro que he oído hablar de tus aventuras, o desventuras. Puedo encargarme de tu pequeño problema, nada que la cantidad adecuada de oro engrasando las palmas adecuadas no pueda arreglar. Trescientos doblones de oro y te sacaré del caldero.";
			if (PCharDublonsTotal() >= 300) // belamour legendary edition
			{
				link.l1 = "¡Estupendo! Aquí está el oro.";
				link.l1.go = "agree";
				iTotalTemp = 300;
			}
			link.l2 = "Entonces es el momento justo para ir a buscar el dinero.";
			link.l2.go = "exit";
		}
		else
		{
			if (rate <= 20)
			{
				dialog.text = "Por supuesto. He oído hablar de tus aventuras, o desventuras. Puedo encargarme de tu pequeño problema, nada que la cantidad adecuada de oro engrasando las palmas adecuadas no pueda solucionar. Seiscientos doblones de oro y te sacaré de la sartén.";
				if (PCharDublonsTotal() >= 600) // belamour legendary edition
				{
					link.l1 = "¡Estupendo! Aquí está el oro.";
					link.l1.go = "agree";
					iTotalTemp = 600;
				}
				link.l2 = "Entonces, es justo el momento adecuado para ir a buscar las monedas.";
				link.l2.go = "exit";
			}
			else
			{
				dialog.text = "¡Sí, estás en un buen lío! No puedo resolver completamente esta situación. Sin embargo, puedo suavizar el golpe del rayo que está a punto de descender sobre tu pecadora cabeza. Y más tarde, en cualquier momento, podemos presentar un soborno nuevamente si tienes el dinero y el deseo. Setecientos doblones de oro y puedo empezar a suavizar tus problemas.";
				if (PCharDublonsTotal() >= 700) // belamour legendary edition
				{
					link.l1 = "Estoy cansado de que los cazadores de piratas me persigan. Aquí está el oro.";
					link.l1.go = "agree";
					iTotalTemp = 700;
				}
				link.l2 = "Entonces es el momento justo para ir a buscar las monedas.";
				link.l2.go = "exit";
			}
		}
		break;

	case "agree":
		RemoveDublonsFromPCharTotal(iTotalTemp); // belamour legendary edition
		PlaySound("interface\important_item.wav");
		dialog.text = "Está bien, dame unos diez a quince días. Mientras tanto, haré una cita, y me ocuparé de esto y aquello. Todo estará listo en unas dos semanas.";
		link.l1 = "¡Gracias, Fadey! Estaré esperando...";
		link.l1.go = "agree_1";
		break;

	case "agree_1":
		DialogExit();
        rate = 10 + rand(5);
        rate = GetIntByCondition(HasShipTrait(pchar, "trait23"), rate, rate / 2);
        SetFunctionTimerCondition("ChangeNationRelationFromFadeyComplete", 0, 0, rate, false);
		pchar.GenQuest.FadeyNation.Rate = abs(ChangeCharacterNationReputation(pchar, sti(pchar.GenQuest.FadeyNation), 0));
		npchar.quest.relation = "true";
		break;

	case "contraband":
		dialog.Text = "¿Por qué fuiste y los enfureciste, buen hombre? Los contrabandistas no son la peor calaña en esta parte del mundo, y pueden darte buenas ganancias. Está bien, te ayudaré, sé cómo congraciarme con ellos... Eso serán setecientos doblones, sin regateos.";
		if (PCharDublonsTotal() >= 700) // belamour legendary edition
		{
			Link.l1 = "Muy bien, Fadey, estoy de acuerdo. Toma tu oro.";
			Link.l1.go = "Contraband_Agreed";
		}
		Link.l2 = "Ahora no tengo tanto oro conmigo. ¡Volveré más tarde!";
		Link.l2.go = "exit";
		break;

	case "Contraband_Agreed":
		dialog.Text = "Bien, arreglaré la disputa, no te preocupes. Harán negocios contigo nuevamente, como en los viejos tiempos.";
		Link.l1 = "¡Gracias!";
		Link.l1.go = "exit";
		ChangeContrabandRelation(pchar, 25);
		RemoveDublonsFromPCharTotal(700); // belamour legendary edition
		PlaySound("interface\important_item.wav");
		break;

	case "UpgradeRopes":
		dialog.text = "¡Ja-ja, veo que tu negocio está prosperando y los apetitos creciendo! Tienes razón, nuestros productos son excelentes y los precios no son demasiado altos. Pero ten en cuenta que se necesitan inversiones. ¡Un negocio así requiere un enfoque serio para que todo sea perfecto!";
		link.l1 = "¿Vendría a ti con tal oferta sin tener un par de cientos de doblones en reserva?";
		link.l1.go = "UpgradeRopes_1";
		break;

	case "UpgradeRopes_1":
		dialog.text = "Sé que tienes monedas en tu cofre, y no sólo un par, ¡seguro que cabrían cincuenta! Pero nuestro negocio no es ordinario, no se trata solo de mover mercancías, sino de encontrar un camino... digamos, discreto. Para tal escala, necesitarás invertir en grande, no solo pagar, ¡para que sea rentable! Y para asegurar que tu dinero no se desvanezca en el aire. Si estás dispuesto a desprenderte de tres mil doblones de oro, entonces toma mi palabra de que todo se hará bien para ti, como buen amigo, y no te escatimaremos en el precio.";
		if (PCharDublonsTotal() >= 3000)
		{
			Link.l1 = "¡Tres mil doblones! Bueno, debo admitir, una oferta tan generosa rara vez es escuchada incluso por los comerciantes más prósperos, ¡incluso en los cuentos más fantásticos! Pocos están dispuestos a invertir tan generosamente en tal empresa. Pero yo, afortunadamente, estoy entre ellos. Aquí está tu dinero, monsieur Fadey.";
			Link.l1.go = "UpgradeRopes_Agreed";
		}
		Link.l2 = "¡Tres mil doblones de oro! No estoy listo para tal suma, Fadey. Desafortunadamente. Volveré más tarde.";
		Link.l2.go = "UpgradeRopes_Potom";
		link.l3 = "¿Tres mil, dices? Bueno... A decir verdad, tal suma impone respeto a tu ambición. Pero debo admitir, esto no es para mí.";
		link.l3.go = "UpgradeRopes_2";
		break;

	case "UpgradeRopes_2":
		dialog.text = "¡Qué giro! Vienes con una oferta, ¡y luego te echas atrás de inmediato! Lo admito, estoy decepcionado, pero no dejaré caer nuestra amistad. Mantengámosla como antes: nuestro acuerdo previo se mantiene - cincuenta bobinas a diez doblones cada una, cada mes, el día 20.";
		link.l1 = "Me alegra que me entiendas, Fadey. Me encantaría cambiar de opinión, pero tales gastos están más allá de mis posibilidades. Ay, mis medios son limitados en este asunto.";
		link.l1.go = "UpgradeRopes_3";
		break;

	case "UpgradeRopes_3":
		dialog.text = "Bueno, si esa es tu decisión, no hay más que discutir. Este cambio no afectará nuestra amistad. Vuelve a visitarme, " + GetSexPhrase("buen señor", "bella dama") + ".";
		link.l1 = "Adiós.";
		link.l1.go = "exit";
		pchar.questTemp.FadeyRopesBlock = true;
		break;

	case "UpgradeRopes_Potom":
		DialogExit();
		pchar.questTemp.FadeyRopesBlock = true;
		pchar.questTemp.FadeyRopesPotom = true;
		break;

	case "UpgradeRopes_Agreed":
		dialog.text = "¡Eso es sensato! No eres de los que hablan por hablar, sino que sabes actuar. Para personas de negocios como tú, siempre hay un descuento disponible. ¡Quince por ciento de descuento en todos los futuros envíos! Aquí está nuestro trato: 250 bobinas de cuerda de cáñamo que tendré listas para ti cada mes. Puedes recogerlas, como antes, el día 20, pagando 2 125 doblones por todo, sin resto.";
		link.l1 = "¡Perfecto, Fadey! Es notablemente fácil hacer negocios contigo. Estoy seguro de que el éxito nos espera. ¡Hasta la próxima!";
		link.l1.go = "exit";
		RemoveDublonsFromPCharTotal(3000);
		AddQuestRecordInfo("Unique_Goods", "2_1");
		pchar.questTemp.UpgradeRopes = true;
		pchar.questTemp.FadeyRopesBlock = true;
		DeleteAttribute(pchar, "questTemp.FadeyRopesPotom");
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}