// Addon-2016 Jason, французские миниквесты (ФМК) Последний урок
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Um bug óbvio. Avise os desenvolvedores sobre isso.";
			link.l1 = "Ah, eu vou.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "greguar":
			PlaySound("Voice\English\LE\Greguar\Greguar_04.wav");
			pchar.quest.FMQL_delete_guide.over = "yes";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Fortfrance");
			if (CheckAttribute(pchar, "questTemp.HWIC") || pchar.Ship.Type == SHIP_NOTUSED)
			{
				dialog.text = "Oh, "+GetFullName(pchar)+"! Você está diferente, meu amigo, e está tendo sucesso! Já estão começando a falar de você, sabia? Você aprende rápido, monsieur, fico realmente orgulhoso de você. Desejo ainda mais fortuna e sorte no seu caminho! Foi um prazer reencontrá-lo!";
				link.l1 = "Monsenhor Gregoire Valinnie, que encontro! Devo muito ao senhor pelas minhas humildes conquistas. Prazer em conhecê-lo também! Boa sorte!";
				link.l1.go = "greguar_exit_1";
			}
			else
			{
				dialog.text = "Oh, "+GetFullName(pchar)+"! Você está diferente, meu amigo, e está tendo sucesso! Já estão começando a falar de você, sabia? Você aprende rápido, monsieur, devo dizer que me deixou orgulhoso.";
				link.l1 = "Monsieur Gregoire Valinnie, que encontro! Devo muito a você pelas minhas humildes conquistas. Prazer em vê-lo! Deixe-me adivinhar, você tem uma proposta de negócio para mim?";
				link.l1.go = "greguar_1";
			}
		break;
		
		case "greguar_1":
			dialog.text = "Sim! Eu sei sim. Vou ser direto, tempo é dinheiro. Então, um esquadrão holandês navegando do Brasil para Curaçao com uma carga de mercadorias de valor estratégico foi emboscado pelos ingleses entre Trinidad e o continente. Um fluyt da Companhia conseguiu escapar e atracar na Costa da Boca de la Serpienta. Eles salvaram parte da carga, mas não por muito tempo – foram atacados por uma tribo indígena local\nPelas minhas informações, eles mataram todos os holandeses daquela costa e levaram a carga para a aldeia deles. Os índios também pegaram as armas de fogo dos holandeses, mas tiveram muitas baixas. Essa é a nossa chance! Ingleses e holandeses ainda estão brigando naquela região e estão ocupados demais para se importar com o fluyt perdido. Por enquanto... Você tem um navio e uma tripulação. Podemos navegar até lá, desembarcar e acabar com os índios. A carga é extremamente valiosa e tem bastante coisa lá\nJá mandei uma pequena expedição para fazer o reconhecimento – foi o máximo que consegui bancar, problemas de dinheiro, lembra? Tenho um comprador de confiança, pode contar com minha espada e meus mercenários. Metade para cada um, temos uma semana para chegar lá. E então, meu amigo, topa?";
			link.l1 = "Me perdoe, monsieur, mas vou recusar. Acabei de voltar de uma viagem difícil, não temos tempo suficiente para consertos e recrutamento. Mesmo neste lugar esquecido por Deus, um homem não pode ter tudo.";
			link.l1.go = "greguar_exit";
			link.l2 = "Parece um negócio perigoso, mas com promessa de bom lucro e aventura. Claro que eu topo! Não vamos perder tempo!";
			link.l2.go = "greguar_2";
		break;
		
		case "greguar_exit":
			dialog.text = "Que pena. Então a decisão é sua. Boa sorte, monsieur, vou pra lá de qualquer jeito. Um homem tem que tentar, né?";
			link.l1 = "Boa sorte, Monsieur Valinnie!";
			link.l1.go = "greguar_exit_1";
		break;
		
		case "greguar_exit_1":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload5_back", "none", "", "", "", 20.0);
		break;
		
		case "greguar_2":
			dialog.text = "Boa escolha, meu amigo! Um dinheiro a mais não faz mal, né? E o seu irmão, como vai?";
			link.l1 = "Dinheiro extra nunca é demais. Michel? Meu irmão está com saúde e entediado. Às vezes até invejo ele... Hora de zarpar!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQL_Begin");
		break;
		
		case "greguar_3":
			PlaySound("Voice\English\QuestMan02.wav");
			dialog.text = "Fácil demais! Esses eram os novatos que sobreviveram ao confronto com os holandeses. Temos que seguir mais para o interior, minha expedição deve estar lá!";
			link.l1 = "Parecia fácil demais... mas ainda é cedo pra comemorar, monsieur Valinnie. Dê uma olhada ali...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQL_SecondCoastBattle");
		break;
		
		case "greguar_4":
			PlaySound("Voice\English\LE\Greguar\Greguar_05.wav");
			dialog.text = "Malditos índios! Eles quase pegaram a gente! Agora tenho certeza de que só restaram mulheres e crianças na aldeia. Vamos embora!";
			link.l1 = "Não tenho tanta certeza de que você mencionou mosquetes, não vi nenhum... Ah, tanto faz. Vamos logo!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQL_GoToJungle");
		break;
		
		case "greguar_5":
			PlaySound("Voice\English\LE\Greguar\Greguar_06.wav");
			dialog.text = "Como assim? Os holandeses e nós devemos ter matado todos eles!";
			link.l1 = "";
			link.l1.go = "greguar_6";
		break;
		
		case "greguar_6":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Prosper_fmql")) sld = CharacterFromID("FMQL_Prosper");
			else sld = CharacterFromID("FMQL_mercen");
			sld.dialog.currentnode = "prosper_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "greguar_7":
			dialog.text = "Fugir? Você ficou louco? Já estamos quase lá! Está com medo de um bando de selvagens pintados?";
			link.l1 = "";
			link.l1.go = "greguar_8";
		break;
		
		case "greguar_8":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Prosper_fmql")) sld = CharacterFromID("FMQL_Prosper");
			else sld = CharacterFromID("FMQL_mercen");
			sld.dialog.currentnode = "prosper_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "greguar_9":
			dialog.text = "O mais baixo dos baixos, capitão. Estou voltando para a Europa. Estou decepcionado! Com você, com esses covardes e com esta maldita região!";
			link.l1 = "...";
			link.l1.go = "greguar_10";
		break;
		
		case "greguar_10":
			DialogExit();
			DoQuestReloadToLocation("shore18", "goto", "goto8", "FMQL_JungleExit");
		break;
		
		case "greguar_11":
			dialog.text = "Ufa! Conseguimos!";
			link.l1 = "Mas a que preço! Olhe! Quase todo mundo do nosso grupo está morto. Devíamos recuar, Gregoire, não há garantia de que não haja mais guerreiros esperando por nós. Além disso, simplesmente não temos gente suficiente para carregar o saque.";
			link.l1.go = "greguar_12";
		break;
		
		case "greguar_12":
			dialog.text = "Droga! É triste, mas você está certo, "+pchar.name+": mesmo que os selvagens estejam todos mortos, não vamos conseguir levar a carga antes que os holandeses ou os ingleses desembarquem aqui. Temos que partir agora! Que se dane esta costa maldita!";
			link.l1 = "...";
			link.l1.go = "greguar_10";
		break;
		
		case "greguar_13":
			dialog.text = "Ufa! Conseguimos! Muito bem feito, "+pchar.name+"! Agora vamos para o covil dos selvagens buscar nosso prêmio! Nada pode nos deter agora!";
			link.l1 = "É melhor a gente se apressar enquanto britânicos e holandeses ainda estão ocupados um com o outro. Vamos!";
			link.l1.go = "greguar_14";
		break;
		
		case "greguar_14":
			DialogExit();
			DoQuestCheckDelay("FMQL_RunToGrabbing", 1.0);
		break;
		
		case "greguar_15":
			dialog.text = "Mandamos bem, "+pchar.name+". Agora só precisamos vender a carga sem levantar suspeitas. Tenho um comprador de confiança, ele vai nos esperar na Baía de Lamentin à meia-noite. Não traga nenhum oficial e evite o local antes do encontro, o cliente é um sujeito bem nervoso.";
			link.l1 = "Negócios são negócios. A carga precisa ser vendida, e isso tem que ser feito com segurança, senão minha dívida com Poincy só vai aumentar. Tudo bem, estarei lá antes da meia-noite.";
			link.l1.go = "greguar_16";
		break;
		
		case "greguar_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.quest.FMQL_goods_timer.win_condition.l1 = "Timer";
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.hour  = 0.0;
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQL_goods_timer.function = "FMQL_MeetingOnLamanten";
			AddQuestRecord("FMQ_Lesson", "7");
			LAi_LocationDisableOfficersGen("Shore38", true); // may-16
			LAi_LocationFightDisable(&Locations[FindLocation("Shore38")], true);
			locations[FindLocation("Shore38")].DisableEncounters = true;
			Pchar.GenQuest.Hunter2Pause = true;
		break;
		
		case "greguar_17":
			PlaySound("Voice\English\Master_01.wav");
			pchar.quest.FMQL_goods_over.over = "yes";// лесник снято прерывание на встречу.
			dialog.text = "Está feito. A carga foi descarregada, o cliente está aqui. Vamos conversar.";
			link.l1 = "...";
			link.l1.go = "greguar_18";
		break;
		
		case "greguar_18":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("FMQL_contra_"+i);
				if (i == 2) 
				{
					LAi_CharacterEnableDialog(sld);
					AddLandQuestMark(sld, "questmarkmain");
				}
			}
		break;
		
		case "greguar_19":
			dialog.text = "Surpresa, seus desgraçados!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQL_LookOnGuards");
		break;
		
		case "greguar_20":
			PlaySound("Voice\English\OliverTrast01.wav");
			dialog.text = "Ah, Johnny, que sujeito! Excelente! Tem algo a dizer, "+pchar.name+"?";
			link.l1 = "Não. Na verdade, sim! Que diabos?!";
			link.l1.go = "greguar_21";
		break;
		
		case "greguar_21":
			dialog.text = "Não zombe do defunto, monsieur. Onde estão seus modos?.. O dinheiro está aqui, a carga está sendo cuidada por mim e meus amigos. Não mandei eles pra costa, teria sido um desperdício. Principalmente mandar o Johnny pra lá. Tá vendo aquele índio ali com uma culverina nas mãos? Sabe, o Johnny nunca gostou muito da própria tribo.";
			link.l1 = "Entendi... E agora? Vai me matar também?";
			link.l1.go = "greguar_22";
		break;
		
		case "greguar_22":
			dialog.text = "Bem, eu deveria. Mas sou sentimental. Vá embora e leve um quarto do dinheiro. A carga e o resto ficam comigo. Não tente bancar o herói, aqui não é a selva do continente. Você não tem chance.";
			link.l1 = "E onde estão sua nobreza e seus modos, Gregoire? Não esperava isso de você. Estou indo embora, mas não vou esquecer disso.";
			link.l1.go = "greguar_23";
			link.l2 = "Eu não estou bancando o herói, nunca estive. Eu simplesmente vou matar todos vocês! Primeiro essas senhoras, depois o macaco com o lança-granadas, e então você!";
			link.l2.go = "greguar_25";
		break;
		
		case "greguar_23":
			dialog.text = "Não há nobres nem bandidos nesta praia, monsieur. Só há cinco homens, um canhão grande e uma vítima. Isso acontece aqui o tempo todo, mas você fez a única escolha certa. Muito bem. Você sabia que, no seu lugar, poderiam estar outros dois agora mesmo, exatamente aqui? Eles são quase iguais a você. Mas é você quem está aqui, não eles, e acho que vão acabar se perdendo por causa disso.";
			link.l1 = "Não entendi...";
			link.l1.go = "greguar_24";
		break;
		
		case "greguar_24":
			dialog.text = "Um dia você vai. Eles não receberam a última lição. Você recebeu. De nada. Adeus, monsieur. Bem-vindo ao Caribe!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQL_PeaceFinal");
		break;
		
		case "greguar_25":
			dialog.text = "Ahh... Você não é o aluno mais brilhante que já tive. Muito bem... cada um com o seu jeito!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQL_BattleOnBeach");
		break;
		
		case "mercen":
			PlaySound("Voice\English\pirat_guard_4.wav");
			dialog.text = "Chegou na hora certa! Mal conseguimos escapar da horda de caribes, eles estavam indo na sua direção e, pelo seu estado, já cruzaram o seu caminho. A aldeia deles fica aqui perto, mas nossos problemas estão só começando.";
			link.l1 = "";
			link.l1.go = "prosper_2";
		break;
		
		case "prosper":
			dialog.text = ""+GetFullName(pchar)+"! Você está aqui! E por que eu não estou surpreso! Chegou na hora certa, meu amigo. Mal conseguimos escapar da horda de caribes, eles estavam indo na sua direção e, pelo seu estado, já cruzaram com você.";
			link.l1 = "Prosperar! E eu estou surpreso! Furando os índios de novo? Espero que a Selina esteja bem?";
			link.l1.go = "prosper_1";
		break;
		
		case "prosper_1":
			dialog.text = "Foi tolice minha entrar nessa expedição. Será que minha filha vai me ver de novo algum dia? Selina? Ah, ela está em casa, sonhando com você! Os jovens da Martinica já perderam toda a esperança... Sabe, não me arrependo mais de ter comprado esse mosquete. Uma arma sólida. Confiável. E também é mais um motivo pra me meter em outra missão suicida, embora agora ela pareça um pouco menos suicida desde que você apareceu. A aldeia deles fica aqui perto, mas nossos problemas só estão começando.";
			link.l1 = "";
			link.l1.go = "prosper_2";
		break;
		
		case "prosper_2":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "prosper_3":
			dialog.text = "Nem todos eles. Nosso batedor foi baleado, mas ainda conseguiu chegar até o esconderijo deles. O chefe está vindo pra cá com os guardas dele. E eles têm mosquetes holandeses. Eles têm vantagem no número e estão furiosos como o diabo. O chefe é o melhor guerreiro da tribo, e os homens dele são demônios em pessoa. Precisamos decidir rápido, aqui e agora. Ou enfrentamos eles ou fugimos. Eu, sinceramente, prefiro a segunda opção...";
			link.l1 = "";
			link.l1.go = "prosper_4";
		break;
		
		case "prosper_4":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_7";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "prosper_5":
			dialog.text = "Você não viu eles, meu bom homem! Esses 'selvagens' têm mosquetes e são surpreendentemente bons com eles. Alguém andou dando aulas pra eles, disso não tenho dúvida! Então não me chame de covarde de novo!";
			link.l1 = "Vamos nos acalmar e decidir o que fazer. Ainda temos tempo.";
			link.l1.go = "prosper_6";
		break;
		
		case "prosper_6":
			int n = 0;
			for (i=1; i<=5; i++)
			{
				if (GetCharacterIndex("FMQL_sailor_"+i) != -1) n++;
			}
			dialog.text = "Estou ouvindo, "+pchar.name+".";
			if (n > 2 && GetSummonSkillFromName(pchar, SKILL_SNEAK) > 30)
			{
				Notification_Skill(true, 31, SKILL_SNEAK);
				link.l1 = "Vamos mostrar pra eles como se luta, rapazes! Tem mercadoria e dinheiro logo atrás desse morro! Viemos por isso e não vamos sair daqui. Não é um bando de índios, nem com mosquetes, que vai nos parar! Vamos enterrar esses desgraçados e terminar o serviço! Temos homens suficientes, dá pra armar uma emboscada. Quatro vão recebê-los com fogo pelos flancos e o resto fica aqui. Vamos diminuir o número deles e acabar com tudo!";
				link.l1.go = "prosper_8";
			}
			else
			{
				if (GetCharacterSkill(pchar, SKILL_SNEAK) < 31) Notification_Skill(false, 31, SKILL_SNEAK);
				if (n < 3) notification("Not enough people", "X");
				if (n > 0)
				{
					link.l1 = "Vamos mostrar pra eles, rapazes! Tem mercadoria e dinheiro logo ali atrás daquela colina! Viemos por isso e não vamos embora. Não tem jeito desses índios, nem com mosquetes, pararem a gente! Vamos enterrar esses desgraçados e terminar o serviço!";
					link.l1.go = "prosper_7";
				}
				else
				{
					link.l1 = "As chances estão contra nós de todas as formas possíveis. Não se esqueça dos holandeses logo atrás de nós.";
					link.l1.go = "prosper_9";
				}
			}
		break;
		
		case "prosper_9":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "prosper_7":
			DialogExit();
			pchar.questTemp.FMQL = "battle";
			AddDialogExitQuestFunction("FMQL_PrepareAttack");
		break;
		
		case "prosper_8":
			DialogExit();
			pchar.questTemp.FMQL = "sneak";
			AddDialogExitQuestFunction("FMQL_PrepareSneakAttack");
		break;
		
		case "prosper_9x":
			dialog.text = "Estamos vivos e estamos em casa! Juro, já tive aventuras demais... pelos próximos meses, ha-ha! Preciso ir ver minha filha, por favor, venha nos visitar, "+pchar.name+". E por favor, tome cuidado.";
			link.l1 = "Sem promessas, Prosper. Boa sorte!";
			link.l1.go = "prosper_10";
		break;
		
		case "prosper_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 10.0);
		break;
		
		case "prosper_11":
			pchar.quest.FMQL_prosper_dead.over = "yes";
			LAi_RemoveCheckMinHP(npchar);
			PlaySound("Voice\English\pirat_guard_4.wav");
			dialog.text = "Eu te avisei, capitão, pra tomar cuidado! Eu já desconfiava desse canalha.";
			link.l1 = "Prosperar! Obrigado! Mas como?";
			link.l1.go = "prosper_12";
		break;
		
		case "prosper_12":
			sTemp = "";
			if (CheckAttribute(pchar, "questTemp.FMQL.PirateDead")) sTemp = "Poor lad, even though he was a pirate.";
			dialog.text = "O Johnny falou demais. Aquele índio na areia. Ele foi até um bordel e tentou ficar com uma das moças. Não quiseram atendê-lo, o Johnny ficou furioso, começou a gritar que logo estaria rico, assim que ele e os amigos matassem um capitão na selva. Eu percebi o que ia acontecer e corri até seu oficial, que também já tinha ficado um pouco conhecido na cidade. "+sTemp+" Eu te devo muito, "+pchar.name+", então não precisa me agradecer tanto assim.";
			link.l1 = "E ainda assim, muito obrigado, Prosper! Foi difícil aqui... difícil demais. Quer se juntar à minha tripulação? Preciso de um oficial como você. Hoje em dia é difícil encontrar homens leais, ainda mais bons atiradores.";
			link.l1.go = "prosper_13";
		break;
		
		case "prosper_13":
			dialog.text = "Não, meu amigo. Tenho responsabilidades com minha filha. Ela me fez jurar que eu deixaria minhas aventuras para trás. Aquela foi a última. Droga, que pena, mas eu amo minha filha mais do que tudo nesse mundo. Adeus, "+pchar.name+". E... Selina fala de você o tempo todo. Quem sabe você não nos faz uma visita qualquer dia desses?";
			link.l1 = "Vai saber, talvez eu faça isso... Adeus, Prosper! Espero que sua filha encontre um bom marido... (para si mesmo) Lições aprendidas, monsieur Gregoire, lições aprendidas... cada um com seus problemas, ele disse... Vou me lembrar disso.";
			link.l1.go = "prosper_14";
		break;
		
		case "prosper_14":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 15.0);
			chrDisableReloadToLocation = false;
			InterfaceStates.Buttons.Save.enable = true; // разрешим сохраняться
			AddQuestRecord("FMQ_Lesson", "15");
			CloseQuestHeader("FMQ_Lesson");
			pchar.questTemp.FMQL = "end";
		break;
		
		case "contra":
			DelLandQuestMark(npchar);
			dialog.text = "Quem diabos é você?";
			link.l1 = "Estamos com a carga. Interessado?";
			link.l1.go = "contra_1";
		break;
		
		case "contra_1":
			dialog.text = "Ha. Muito interessado. Meu cliente então, nem se fala. Qual é o lucro?";
			link.l1 = ""+FindRussianQtyString(sti(pchar.questTemp.FMQL.Sanl))+" de pau-ferro, "+FindRussianQtyString(sti(pchar.questTemp.FMQL.Silk))+" de seda de navio, "+FindRussianQtyString(sti(pchar.questTemp.FMQL.Rope))+" de corda e "+FindRussianQtyString(sti(pchar.questTemp.FMQL.Oil))+" de resina.";
			link.l1.go = "contra_2";
		break;
		
		case "contra_2":// Addon 2016-1 Jason пиратская линейка
			iTotalTemp = 2200*sti(pchar.questTemp.FMQL.Sanl)+1600*sti(pchar.questTemp.FMQL.Silk)+1000*sti(pchar.questTemp.FMQL.Rope)+900*sti(pchar.questTemp.FMQL.Oil);
			dialog.text = "Muito bem. 2200 pesos por cada peça de madeira de ferro, 900 pesos pela resina, 1600 pesos pela seda naval e 1000 pesos pelas cordas. O que temos aqui... Ora, ora. "+iTotalTemp+" pesos. Fechado?";
			link.l1 = "Fechado!";
			link.l1.go = "contra_3";
		break;
		
		case "contra_3":
			LAi_Fade("", "");
			FMQL_CreateGuidesWarriors();
			dialog.text = "Excelente! Traga mais. Os holandeses nunca deixam de ser generosos com os peles-vermelhas... E quem são esses convidados? Mas que diabos?!";
			link.l1 = "";
			link.l1.go = "contra_4";
		break;
		
		case "contra_4":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_19";
			AddMoneyToCharacter(sld, iTotalTemp);
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "FMQL_beach":
			pchar.quest.FMQL_pirate_dead.over = "yes";
			LAi_RemoveCheckMinHP(npchar);
			dialog.text = "É, capitão. Eu bebi demais antes de zarpar, e foi por um motivo.";
			link.l1 = "Você? Como?!";
			link.l1.go = "FMQL_beach_1";
		break;
		
		case "FMQL_beach_1":
			dialog.text = "Me desculpe, capitão. Precisei beber um ou dois copos depois daquela confusão com os índios. Tinha uma moça, aluguei um quarto por cem pesos e ela... ela...";
			link.l1 = "O quê? Te roubaram?";
			link.l1.go = "FMQL_beach_2";
		break;
		
		case "FMQL_beach_2":
			sld = CharacterFromID("FMQL_Prosper");
			dialog.text = "Não! Ela se apaixonou! Droga, eu devia ter fugido dali! Mas aí seu amigo aparece, gritando comigo por causa desse canalha, seu ex-companheiro, que quer te ferrar e te matar.";
			if (LAi_GetCharacterHP(sld) > 0)
			{
				link.l1 = "Muito bem, Prosper...";
				link.l1.go = "FMQL_beach_3";
			}
			else
			{
				link.l1 = "Prosper... Me desculpe mesmo. Vou cuidar da sua filha. Aprendi a lição, monsieur Gregoire... O que você disse? Cada um com o seu? Preciso lembrar disso.";
				link.l1.go = "FMQL_beach_3";
			}
		break;
		
		case "FMQL_beach_3":
			dialog.text = "Vamos, capitão?";
			link.l1 = "É. Obrigado pelo seu serviço. Fique longe do copo e vamos te salvar daquela beleza. Vamos.";
			if (CheckAttribute(pchar, "questTemp.FMQL.ProsperDead")) link.l1.go = "FMQL_beach_5";
			else link.l1.go = "FMQL_beach_4";
		break;
		
		case "FMQL_beach_4": // Проспер жив
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload_sea", "none", "", "", "FMQL_PirateNormal", 10.0);
			sld = CharacterFromID("FMQL_Prosper");
			sld.Dialog.currentnode = "prosper_11";
			sld.MusketerDistance = 20;
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0); 
		break;
		
		case "FMQL_beach_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "FMQL_PirateNormal", 10.0);
			if (sti(pchar.money) >= 20000) DoQuestFunctionDelay("FMQL_MoneyForSelina", 0.5);
			else
			{
				pchar.quest.FMQL_money_20k.win_condition.l1 = "Money";
				pchar.quest.FMQL_money_20k.win_condition.l1.value = 20000;
				pchar.quest.FMQL_money_20k.win_condition.l1.operation = ">=";
				pchar.quest.FMQL_money_20k.function = "FMQL_MoneyForSelina";
			}
			chrDisableReloadToLocation = false;
			InterfaceStates.Buttons.Save.enable = true; // разрешим сохраняться
			AddQuestRecord("FMQ_Lesson", "10");
			CloseQuestHeader("FMQ_Lesson");
			pchar.questTemp.FMQL = "end";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
